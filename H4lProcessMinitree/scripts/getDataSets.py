#!/usr/bin/env python
#
# $Id: getDataSets.py 798613 2017-02-25 14:24:30Z sabidi $
#
# This script downloads H4l miniTree output files from the grid
#

import os
import sys 
import commands
import string
import os.path
import time
from time import strftime, localtime, gmtime
from email.MIMEText import MIMEText
import smtplib
import subprocess
import argparse
import datetime
import shlex

parser = argparse.ArgumentParser()
parser.add_argument("--inputStr",       type=str, default="group.phys-higgs.user.sabidi.*H4l_Oct15_RP", help="Pattern for download")
parser.add_argument("--outputDir",      type=str, default="./", help="Path to output directory")
parser.add_argument('--checkLocalRSE',  action='store_true', default=False)
parser.add_argument("--maxProcs",       type=int, default=5, help="Number of parallel processed")
parser.add_argument("--logFile",        type=str, default='logFile_Download.txt', help="Name of the log file")
parser.add_argument("--tmpDir",         type=str, default='tmpDir', help="Directory for temporary saving of the log files")
args = parser.parse_args()


# for sending email
def SendTextMail(sSubject,sText):
    sFrom = os.environ["USER"]+" <"+os.environ["USER"]+"@cern.ch>"
    sTo=""
    sMailingList = [os.environ["USER"]+"@cern.ch"]
    for x in sMailingList: sTo=sTo+x+";"

    mail = MIMEText(sText)
    mail['From'] = sFrom
    mail['Subject'] = sSubject
    mail['To'] = sTo

    smtp = smtplib.SMTP()
    smtp.connect()
    smtp.sendmail(sFrom, sMailingList, mail.as_string())
    smtp.close()

# get the list of datasets
def get_datasets(expression):

    # first get all the nominal ones
    command = 'rucio list-dids %s*Event*.root' %expression
    #command = 'rucio list-dids %s*hist' %expression
    process = subprocess.Popen(command.split(' '), stdout=subprocess.PIPE)
    out, err = process.communicate()
    # print to terminal
    print command
    print out
    # split the output line by line
    outTemp = out.split('\n')[:-1]
    outTemp.sort()
    finalList = []

    # pick out the dataset names
    for fileName in outTemp:
        if 'user' in fileName:
            temp = fileName.replace('[COLLECTION]','')
            tempList = temp.split('| ')
            temp = tempList[1].strip()
            finalList.append(temp)

    # getting the list for systematics
    command = 'rucio list-dids %s*Event*.root.tgz' %expression
    process = subprocess.Popen(command.split(' '), stdout=subprocess.PIPE)
    out, err = process.communicate()

    # print to terminal    
    print command
    print out
    # split the output line by line    
    outTemp = out.split('\n')[:-1]
    outTemp.sort()
    # pick out the dataset names    
    for fileName in outTemp:
        if 'user' in fileName:
            temp = fileName.replace('[COLLECTION]','')
            tempList = temp.split('| ')
            temp = tempList[1].strip()
            finalList.append(temp)
    finalList.sort()
    return finalList 

# construct the download command
def downloadCommand(fileName, checkLocalRSE = False):
    useLocal      = False
    useLocalHIGGS = False
    if(checkLocalRSE):
        # Test if file is found a local RSE:
        command = 'rucio list-dataset-replicas %s' %fileName
        status,output = commands.getstatusoutput(command)
        useLocal      = False
        useLocalHIGGS = False
        if 'IN2P3-CC_PHYS-HIGGS' in output:
            useLocalHIGGS = True
            print "Found", fileName, "at IN2P3-CC_PHYS-HIGGS"
            pass
        elif 'IN2P3-CC_LOCALGROUPDISK' in output:
            useLocal = True
            print "Found", fileName, "at IN2P3-CC_LOCALGROUPDISK"
            pass
        pass

    if useLocalHIGGS:
        command = 'rucio download --rse IN2P3-CC_PHYS-HIGGS ' 
    elif useLocal:
        command = 'rucio download --rse IN2P3-CC_LOCALGROUPDISK '
    else:
        command = 'rucio download ' 
        pass
    command += ' --dir %s ' %args.outputDir
    command += fileName

    return command

def main():
    startTime=strftime("%Y-%m-%d %H:%M:%S", localtime())

    #getting the datasets
    print args.inputStr
    files = get_datasets(args.inputStr)
    
    # create the list of input commands
    commandList = []

    # If we are reading from local RSE, then run twice in case not all files have been transferred
    if(args.checkLocalRSE):
        for fileName in files:
            commandList.append(downloadCommand(fileName, True))
            pass
        pass

    for fileName in files:
        commandList.append(downloadCommand(fileName))
        pass
    
    #for command in commandList:
    #    print command

    # actually start the download process
    processes = set()
    procList = []
    max_processes = args.maxProcs


    # check if the temp directory exists, if it doesn't create it
    createdTmpDir = False
    if not os.path.exists(args.tmpDir):
        os.makedirs(args.tmpDir)
        createdTmpDir = True

    # logfile
    i = 0;
    for command in commandList:
        print 'Running ', command
        i = i + 1
        if(i%5 == 0):
            precentDone = float(i)/len(commandList) * 100
            print 'Running command i: ',i, ' percentage done: ' , float("{0:.1f}".format(precentDone))
            pass
        # get the arguments
        arguments = shlex.split(command)

        tmpLogFile = args.tmpDir+'/tmpLogFile_download_'+str(i)+args.inputStr.replace('*', '')+'.txt'
        
        w = open(tmpLogFile,'w')
        # start the process
        p = subprocess.Popen(arguments, stdout=w, stderr=w)

        # store for backup and for the queue
        processes.add(p)

        procToSave = {}
        procToSave['args'] = command
        procToSave['logFile'] = tmpLogFile
        procList.append(procToSave)
       
        # check if the current number of processes exceed the maximum number
        if len(processes) >= max_processes:
            #print 'holding since max process exceeded limit'            
            while True:
                processes.difference_update([p for p in processes if p.poll() is not None])
                if len(processes) < max_processes:
                    break
                # sleep for a bit to save polling time
                time.sleep(10)
                pass
            pass
        pass
    # poll till all the processes are done
    #for proc in processes:
    #    print proc.poll()
    #    if (proc.poll() is not None):
    #        proc.wait()
    while True:
        processes.difference_update([p for p in processes if p.poll() is not None])
        if len(processes) == 0:
            break
        pass
        # sleep for a bit to save polling time
        time.sleep(5)
    pass
    
    # to wait for the last few files to be written
    time.sleep(5)
    # write to log file and for error checking
    nFile = 0;
    nDownloadFailed = 0;
    nDone = 0;
    listFailed = []
    logFailed  = ""
    
    listDownloadFailed = []
    logDownloadFailed  = ""
    log = open(args.logFile, "w", 1)

    for proc in procList:
        nFile += 1;
        
        log.write(proc['args'])
        
        # read the log file
        tmpLogFile = open(proc['logFile'],  "r")
        output = tmpLogFile.read()
        tmpLogFile.close()
        # delete the log file
        # os.remove(proc['logFile'])

        log.write(output)
        log.write('\n\n')    
    
        outputList = output.split('\n')
        nFiles = 0
        nDownloaded = 0
        nFound = 0
        nFaliure = 0  
        for outputText in outputList:
            if 'DID ' in outputText:
                print "processed ", outputText
            if 'Total files :' in outputText:
                nFiles = int((outputText.split(':')[1]).strip())
            if 'Downloaded files :' in outputText:
                nDownloaded = int((outputText.split(':')[1]).strip())
            if 'Files already found locally :' in outputText:
                nFound = int((outputText.split(':')[1]).strip())
            if 'Files that cannot be downloaded :' in outputText:
                nFaliure = int((outputText.split(':')[1]).strip())
                pass
            pass
        if nFiles == (nFound + nDownloaded):
            nDone += 1
            pass
        
        if nFiles != (nFound + nDownloaded) or nFaliure > 0:
            nDownloadFailed += 1
            listDownloadFailed = listDownloadFailed + [proc['args']]
            logDownloadFailed += command
            logDownloadFailed += "\n\n\n"
            logDownloadFailed += output
            pass
        pass
    
    log.close()
    
    endTime=strftime("%Y-%m-%d %H:%M:%S", localtime())
   

    print "----- Submission completed -----"
    print "Summary"
    print "startTime", startTime
    print "endTime", endTime
    print "nDataset", nFile
    print "nDownload Failure", nDownloadFailed
    print "nDownload Already present", nDone
    
    
    # composing email message
    textMail = "Log for dataSet download \n\n"
    textMail += "Summary \n"
    textMail += "startTime %s \n" %startTime
    textMail += "endTime %s \n" %endTime
    textMail += "nFiles %s \n" %nFile
    textMail += "nDownload Failure %s \n" %nDownloadFailed
    textMail += "nDownload Already present %s \n" %nDone
    
    if nDownloadFailed > 0:
        textMail += "\n\n"
        textMail += "n File Download fail log \noutput \n"
        textMail += logDownloadFailed
        textMail += "\nSample List for above\n"
        for name in listDownloadFailed:
            textMail +=  name
            textMail +=  "\n"
    
    subjectMail = "Download log start time %s" %startTime
    
    SendTextMail(subjectMail, textMail)


if __name__ == "__main__":
    start_time = time.time()
    main()
    ex_time = time.time() - start_time
    print "Execution time ",str(datetime.timedelta(seconds=ex_time))


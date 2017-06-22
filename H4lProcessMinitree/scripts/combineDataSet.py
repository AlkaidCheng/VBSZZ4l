#!/usr/bin/env python
#
# $Id: combineDataSet.py 777504 2016-10-10 15:20:00Z schaffer $
#
# This script combines the downloaded minitree files after downloading and untarring
#
import os
import subprocess
import time
import argparse
import datetime
import shlex
import time

# input arguments
parser = argparse.ArgumentParser()
parser.add_argument("--inputDir" , type=str, required=True, help="Path to input directory")
parser.add_argument("--outputDir", type=str, default="EventSummaryCombined", help="Path to output directory")
parser.add_argument("--maxProcs",  type=int, default=5, help="Number of parallel processed")
parser.add_argument("--logFile",   type=str, default='logFile_combine.txt', help="Name of the log file")
parser.add_argument("--tmpDir",         type=str, default='tmpDir', help="Directory for temporary saving of the log files")

args = parser.parse_args()

# gets the list of folder to loop over
def getFileNameList(path):
    fileListTemp = os.listdir(path)
    fileList = []
    for filename in fileListTemp:
        if 'user' in filename :
            fileList.append(filename)
    fileList.sort()
    return fileList

## Gets the unique DSID that will be used for combinations 
def getUniqueMCNumber(fileList):
    MCNum = []
    for fileName in fileList:
        # this for production with higgs production status
        i1 = 2
        i2 = 3
        iData = 2
        if "group.phys-higgs." in fileName:
            i1 = 4
            i2 = 5
            iData = 4
        # Actually get the mc nuber
        if "user" in fileName :
            mcNumberTemp = fileName.split(".")[i1]+"."+fileName.split(".")[i2]
            if "data" in fileName:
                mcNumberTemp = fileName.split(".")[iData]+"."+(fileName.split(".")[i2])[0:8]
            MCNum.append(mcNumberTemp)
    # sort and only keep the unique ones
    MCNum.sort()
    return list(set(MCNum))

## Gets the unique ID for systematic combination
def getSysList(pathName, folderList):
    sysList = []
    # find all the files inside all the folder
    for folderName in folderList:
        folderName = pathName + "/" + folderName
        if(not os.path.isdir(folderName)):
            continue
        for fileName in os.listdir(folderName):
            # continue if not a root file
            if ".root" not in fileName:
                continue
            if ("group.phys-higgs." in fileName or 'EventSummary' in fileName):
                # find for the file name.... sometimes we have .root.2 that can mess up the index
                for uniqueId in fileName.split('.'):
                    if('EventSummary' in uniqueId and 'EventSummaryXYZ' not in uniqueId):
                        uniqueId += '.'
                        sysList.append(uniqueId)
                        break
                    pass
                pass
            pass
            ## bkg files
            #if ("BkgCR" in fileName or "Zplusl" in fileName or "bkgCR" in fileName):
            #    # are the bkg combined?
            #    if ("group.phys-higgs." in fileName):
            #        # find for the file name.... sometimes we have .root.2 that can mess up the index
            #        for uniqueId in fileName.split('.'):
            #            if('EventSummary' in uniqueId):
            #                uniqueId += '.'
            #                sysList.append(uniqueId)
            #                break
            #    # they are not combined
            #    else:
            #        uniqueId =  fileName.split('.')[0] + '.'
            #        sysList.append(uniqueId)
            #        pass
            #    pass
            # Most likely this type of file is a systematic one
            #elif "EventSummary_" in fileName:
            #    uniqueId =  fileName.split('.')[0]
            #    sysList.append(uniqueId)
            #    pass
            ## Most likely this is a nominal file that has been combined
            #elif ("EventSummary." in fileName):
            #    uniqueId = 'EventSummary.'
            #    sysList.append(uniqueId)
            #    pass
            #pass
        pass
    sysList.sort();

    return list(set(sysList));

## find files in a directory of a given pattern 
def findFile(dirName, pattern):
    fileList = []
    for files in os.listdir(dirName):
        #if pattern in files:
        if ".root" in files and "Plot" not in files and pattern in files:
            fileList.append(dirName + "/" + files)
    return fileList

## To combine .root Files
def combineRootFiles(fileList, saveFile):
    # building the command for combining the files
    command = "hadd -f"
    command += " %s" %saveFile
    for fileName in fileList:
        command += " %s" %fileName
        pass
    # print "command", command
    if len(fileList) is 0:
        return
    return command

# gets the list of commands
def getCommandList():
    ## Gets the unique MC number from the list
    path = args.inputDir
    folderList = getFileNameList(path);
    mcNumber = getUniqueMCNumber(folderList)
    mcNumber.sort()
    print 'mcNumber', mcNumber
    
    fileIDList = getSysList(path,folderList);
    fileIDList.sort()
    print 'fileIDList', fileIDList
    
    # save input for the commands
    commandList = []
    # for each systematic, loop over each sample and combine each individual systematic file
    for uniqueID in fileIDList:
        for mcNum in mcNumber:
            saveFileName = "" # output fileName
            fileList = [] # list of files found
            lastFolderAccessed = '' # last folder access - used for figuring out the output name

            # loop over all the folder to file the folders with the right name 
            # and file the files from inside them with the ID
            for folderName in folderList:
                if mcNum not in folderName:
                    continue
                lastFolderAccessed = folderName
                fileList.extend(findFile(path + "/" + folderName, uniqueID))
                
            # this for production with higgs production status
            i1 = 0
            i2 = 4

            if "group.phys-higgs." in lastFolderAccessed:
                i1 = 2
                i2 = 6

            # figure out the folder
            saveFolderTemp = lastFolderAccessed.split(".") [i1:i2]
            saveFolder = args.outputDir+'/'+'.'.join(saveFolderTemp)
            # if the folder doesn't exist, create it
            if(not os.path.exists(saveFolder)):
                os.mkdir(saveFolder)
            # output file name
            saveFileNameTemp = lastFolderAccessed.split(".") [i1:i2]
            saveFileName = saveFolder + '/' + '.'.join(saveFileNameTemp) + '_' + uniqueID + ".root"
            
            fileList.sort()
            # save the inforamation
            commandCurr = {}
            commandCurr['fileList'] = fileList
            commandCurr['saveName'] = saveFileName
            commandList.append(commandCurr)
        pass

    commandList.sort()
    return commandList


# Gets the modification time for the file
def modification_date(filename):
    # default time is zero
    t = 0
    # if the file exist, update the modification time 
    if os.path.isfile(filename):
        t = os.path.getmtime(filename)
    return t 

def main():
    # all the commands
    commandListFull = getCommandList()
    commandList = []

    # remove all commands where the output file is newer than the inputs file
    # also remove all commands that have zero input files
    for command in commandListFull:
        # get the creation/modification for the saveFile
        saveFileTime = modification_date(command['saveName'])
        # loop over all the input files and see if there is a newer version of the file
        skipFile = True
        for inputFile in command['fileList']:
            if saveFileTime <= modification_date(inputFile):
                skipFile = False
                break
        # if not skipping this command, append it to another list
        if not skipFile:
            commandList.append(command)


    # actually start the combine process
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
        i = i + 1
        if(i%5 == 0):
            precentDone = float(i)/len(commandList) * 100
            print 'Running command i: ',i, ' percentage done: ' , precentDone

        # get the arguments
        shellCommand = combineRootFiles(command['fileList'], command['saveName'])
        arguments = shlex.split(shellCommand)
        tmpLogFile = args.tmpDir+'/tmpLogFile_combine_'+str(i)+'.txt'

        w = open(tmpLogFile,'w')
        # start the process
        p = subprocess.Popen(arguments, stdout=w, stderr=w)


        # store for backup and for the queue
        processes.add(p)

        procToSave = {}
        procToSave['args'] = shellCommand
        procToSave['logFile'] = tmpLogFile
        procList.append(procToSave)
       
        # check if the current number of processes exceed the maximum number
        if len(processes) >= max_processes:
            #print 'holding since max process exceeded limit'            
            while True:
                processes.difference_update([p for p in processes if p.poll() is not None])
                if len(processes) < max_processes:
                    break

    print 'Polling for the last few jobs'
    # poll till all the processes are done
    while True:
        processes.difference_update([p for p in processes if p.poll() is not None])
        if len(processes) == 0:
            break
        pass
        # sleep for a bit to save polling time
        time.sleep(5)
    pass

    print 'Waiting for output files to get written to disk'
    # to wait for the last few files to be written
    time.sleep(5)

    # for quick error checking
    errorInDownload = False
    # write to log file
    log = open(args.logFile, "w", 1)
    for proc in procList:
        log.write(proc['args'])
        # read the log file
        tmpLogFile = open(proc['logFile'],  "r")
        out = tmpLogFile.read()
        tmpLogFile.close()
        # delete the log file
        # os.remove(proc['logFile'])

        log.write(out)

        # basic error check
        if('Target path' not in out):
            errorInDownload = True
            log.write("ERROR - no output Target file... check the job above\n")
        log.write('\n\n')
    log.close()

    if errorInDownload:
        print "Potential errors found in output, please check the log file"    


if __name__ == "__main__":
    start_time = time.time()
    main()
    ex_time = time.time() - start_time
    print "Execution time ",str(datetime.timedelta(seconds=ex_time))


    

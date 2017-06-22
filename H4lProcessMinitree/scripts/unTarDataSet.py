#!/usr/bin/env python
#
# $Id: unTarDataSet.py 783887 2016-11-13 14:51:17Z sabidi $
#
# This script untars the downloaded H4l miniTree output files
#
import os
import subprocess
import re
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("--tarDir",      type=str, default=".", help="Path to directory with tar files")
args = parser.parse_args()



# Gets the folder name of where we have to unTar the files
def getFileNameList(pathName):
    tempList = os.listdir(pathName)
    fileList = [];
    for fileName in tempList:
        if(os.path.isdir(pathName + "/" + fileName)):
            fileList.append(fileName)
    fileList.sort()
    return fileList

## find files in a directory of a given patter 
def findFile(dirName, pattern):
    fileList = []
    for files in os.listdir(dirName):
        if pattern in files:
            fileList.append(dirName + "/" + files)
    return fileList

## To untar files
def unTarFile(fileList, folderPath):

    # print "fileList, folderPath", fileList, folderPath

    # Temporary 'hack' for file number for RD. Set to true if needed. Should be removed with new
    # processing. 2016/09/18
    doRenumbering = False
    # doRenumbering = True
    
    # building the command for combining the files
    for fileName in fileList:

        
        if doRenumbering:
            # print 'fileName', fileName
            m = re.search('/(.+?).root.tgz', fileName)
            if m:
                found = m.group(1)
                l = len(found)
                found = fileName[l:]
                # print "found", found
                m = re.search('_.(.+?).EventSummary', found)
                if m:
                    found = m.group(1)
                    pass
                pass
            pass

        # print "found", found
        # print 'fileName', fileName
        # print "found", found
        
        # build the command for untaring each file
        command = "tar xvfz"
        command += " %s" %fileName
        # save the current directory
        currDir = os.getcwd()
        # go into the folder for untar

        # print "go to ", folderPath
        
        os.chdir(folderPath)
        
        print "command", command

        # untar
        os.system(command)

        if doRenumbering:
            rename = "rename .root .root"
            rename += "%s" %found
            rename += " *.root"

            print rename

            os.system(rename)
        
        # delete the tar file

        # print "remove", fileName
        os.remove(fileName)

        # come back to the original path
        os.chdir(currDir)
        pass
    pass

def main():
    ## Gets the unique MC number from the list
    path = os.path.abspath(args.tarDir)
    folderList = getFileNameList(path);

    print 'folderList', folderList
    
    # looping over the list, and trying to find all the relevant files and then merging them
    for folderName in folderList:

        # print 'folderName', folderName
        
        fileList = []
        # fileList.extend(findFile(path + "/" + folderName, "EventSummaryXYZ.root.tgz"))
        dir   = path + "/" + folderName

        # print 'dir', dir
        
        files = findFile(dir, "EventSummaryXYZ.root.tgz")

        # print "files", files
        
        if len(files) != 0:
            fileList.extend(files)

            # print "fileList", fileList
            
            unTarFile(fileList, path + "/" + folderName )
        else:
            print 'Aleady processed files in ', dir
            pass
        pass
    pass

if __name__ == "__main__":
    # execute only if run as a script
    main()

#!/usr/bin/env python
#
# $Id: createFileList.py 798613 2017-02-25 14:24:30Z sabidi $
#
# This script creates a fileList.txt file after having run combineDataSet.py. This file list should
# be used with the combineMinitree.exe post-processing as the files to be processed.
#
import os
import subprocess
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("--inputDir" , type=str, required=True, help="Path to input directory")
args = parser.parse_args()

# samples to go over
def getFileNameList(path):
    fileListTemp = os.listdir(path)
    fileList = []
    for filename in fileListTemp:
        if 'user' in filename or 'higgs' in filename:
            fileList.append(filename)
    fileList.sort()
    return fileList

## find files in a directory of a given patter 
def findFile(dirName):
    fileList = []
    for files in os.listdir(dirName):
        #if pattern in files:
        if ".root" in files and "Plot" not in files:
            fileList.append(dirName + "/" + files)

    return fileList


def main():
    ## Gets the unique MC number from the list
    path = args.inputDir
    FolderList = getFileNameList(path);
    fileList = [] # list of files founc

    for folderName in FolderList:
        fileList.extend(findFile(path + "/" + folderName))
    f = open('fileList.txt', 'w')
    for item in fileList:
        f.write("%s\n" % item)
    f.close()
    print "Created fileList.txt"
    
if __name__ == "__main__":
    # execute only if run as a script
    main()



    

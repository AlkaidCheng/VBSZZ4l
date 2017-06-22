#!/usr/bin/env python
#
# $Id: checkForCompleteness.py 805210 2017-05-21 21:38:42Z schaffer $
#
# This script checks whether a minitree file has run over the full number of events found in AMI
#
import sys, os
import ROOT 

# pyAMI
import pyAMI.client
import pyAMI.atlas.api as AtlasAPI
client = pyAMI.client.Client('atlas')
AtlasAPI.init()

def getNumberAmi(dsName):
    try:
        InfoDict = AtlasAPI.get_dataset_info(client, dsName) 
    except pyAMI.exception.Error as bla:
        print "Failed to query DS %s on AMI: Exception was \"%s\""%(dsName, bla)
        return -1 
    try:
        n_Events=InfoDict[0]["totalEvents"]
    except KeyError:
        print "Unable to decipher the InfoDict: "
        print InfoDict
        return -1
    return int(n_Events)

def getShortName(dsName):
    elements=dsName.split(".")
    return ".".join(elements[:3])

def getMiniTreeName(dsName):
    return getShortName(dsName)+".root"

def getDSName(miniTree):
    try:
        thefile   = ROOT.TFile.Open(miniTree,"READ")
        # print "opened", miniTree
        # thefile.Print()
        theMDtree = thefile.Get("MetaData")
        # print "tree", theMDtree
        theMDtree.GetEntry(0)
        # print "tree entries", theMDtree.GetEntries()
        result = str(theMDtree.sampleName)
        thefile.Close()
        # print "result", result
        return result
    except:
        print "Failed to get the data set name from the MetaData from ",miniTree
        return -1

# check the number of processed DxAOD events in a reco MiniTree. Used to check consistency of inputs
def getProcDAODevt(filename):
    try: 
        thefile = ROOT.TFile.Open(filename,"READ")
        thehist = thefile.Get("CountingHist")
        result = thehist.GetBinContent(2)
        thefile.Close()
        return int(result)
    except:
        print "Failed to get the number of processed DxAOD events from ",filename
        return -1

def getListOfMiniTrees(it):
    found = []
    if os.path.isdir(it):
        for X in os.listdir(it):
            if X.find(".root") > -1:         
                found.append(it+"/"+X)
    elif os.path.isfile(it) and it.find(".root") != -1:
            found.append(it)
    else: 
        print "Could not make sense of input %s - please provide a dir with MiniTrees or a single root file "%it
    return found



def main(args):

    if len(args)==0:
        dirs=[os.getcwd()]
    else:
        dirs = args
    allMiniFiles=[]
    allMiniFilesFound={}
    problems = {}
    for dir in dirs:
        allMiniFiles += getListOfMiniTrees(dir)
    for mini in allMiniFiles:
        # Get data set name from MetaData
        # print "mini", mini
        dsName = getDSName(mini)
        # print "Found ds name:", dsName
        n_DAOD = getNumberAmi(dsName)
        # print "Found n_DAOD", n_DAOD
        n_mini = getProcDAODevt(mini)
        # print "Found n_mini", n_mini
        if n_mini == n_DAOD:
            print "OK: %s has the correct number of processed events, indicating a successful production!"%mini
        else:
            print mini, n_mini,n_DAOD
            print "****** CAREFUL! %s has %i processed events, where we would expect %i from AMI for a successful prod!"%(mini,n_mini, n_DAOD)
            problems[mini] = (n_mini,n_DAOD)
            pass
        pass
    print " "
    blahaaaa = ""
    if len(problems) > 0: 
        blahaaaa = "Problems were found with the following MiniTrees: "
    else:
        blahaaaa = "No problems found!"
        pass
    print " "
    print "==== All done. %s ==============="%blahaaaa
    for k,v in problems.iteritems():
        print k,":   ",v[0],"/",v[1]


if __name__ == "__main__":

    main(sys.argv[1:])

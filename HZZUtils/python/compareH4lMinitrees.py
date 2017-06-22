import user
import math
from ROOT import *
#import PyCintex

#  To compare two miniTree files, just set fileName1 and fileName2 to point to the two files, and
#  run:
#
#  python compareH4lHinitrees.py
#
#  If the files have different number of events, there will be a printout at the beginning of the
#  output with the list of missing events in either file. You can suppress this output with:
#   comment the line:  skipEventCheck = False
#  You may want to do this if one file has only processed the first N events of the other file.
#  Missing events will still be printed as they are encountered.
#
#  If you are checking systematics, you will want to loop over the systematics names (sysNames) and
#  call compareFile(fileName1, fileName2)
#  This you can do by uncommenting the code below, and commenting out the single call to compareFile.
#
#  If you want to skip the comparison of some branches, add then into the list brsToSkip[]
#
#  NOTE: the following comparison relies on each tree have 'run' and 'event' as minTree variables
#  which are used to compare two trees in different files. So this is a requirement. Or one can also
#  change 'run' and 'event' to correspond to other names.
#  In addition, it is possible to more than one event with the same run/event number. In this case,
#  the miniTree variable 'cand_index' should be used to number the candidates.
#
#  RD Schaffer 03/2016



# tolerance for error
epsilon = 0.001

# If you are checking two files with different numbers of event, you can turn off the 'missing
# events' check:
skipEventCheck = True
skipEventCheck = False

# tree to check over
treeNames = ["tree_ZplusEl", "tree_ZplusMu", "tree_ss", "tree_incl_all", "tree_relaxee", "tree_relaxIsoD0", "tree_emu"]

# function call when the script is run
def main():

    systNames = [ "EG_RESOLUTION_ALL__1down/", "EG_RESOLUTION_ALL__1up/", "EG_SCALE_ALL__1down/", "EG_SCALE_ALL__1up/", "JET_GroupedNP_1__1down/", "JET_GroupedNP_1__1up/", "JET_GroupedNP_2__1down/", "JET_GroupedNP_2__1up/", "JET_GroupedNP_3__1down/", "JET_GroupedNP_3__1up/", "JET_JER_SINGLE_NP__1up/", "MUONS_ID__1down/", "MUONS_ID__1up/", "MUONS_MS__1down/", "MUONS_MS__1up/", "MUONS_SCALE__1down/", "MUONS_SCALE__1up/", "NormSystematic/" ]
    
    # CR Z+X:
    fileName1 = '/sps/atlas/groups/H4l/outputNtuples/rds/quads/AccCh/bkg_20160321/EventSummary_bkgCRZpl.root'
    fileName2 = '/afs/cern.ch/work/s/sabidi/public/ForRD/bkgMinitree/v12/mc15_13TeV.341293.PowhegPythia8EvtGen_CT10_AZNLOCTEQ6L1_VBFH200NW_ZZ4lep_bkgCRZpl.root'

    
    compareFile(fileName1, fileName2)

    # Replace the above call to compareFile with the lines below for systematics checks
    # for syst in systNames:
    #     fileName1 = '<first file name>'
    #     fileName2  = '<second file name>'
    #     compareFile(fileName1, fileName2)
    #     pass
    # pass

# compares the two files together
def compareFile(fileName1, fileName2):
    
    evtTypes = [ "4mu", "4e", "2mu2e", "2e2mu", "4tau", "2e2tau", "2tau2e", "2mu2tau", "2tau2mu", "emu2mu",
                 "2mumu", "2mue", "2emu", "2ee" ]

    print 'File1: ', fileName1
    print 'File2: ', fileName2
    # open the file
    file1 = TFile.Open(fileName1)
    file2 = TFile.Open(fileName2)

    # If you want to skip the comparison of some branches, add then into the list brsToSkip[]
    brsToSkip = [  ]
    # brsToSkip = [ 'weight_lumi', 'weight', 'w_lumi', 'w_pileup', 'weight_corr' ]

    foundFirstTree = False
    
    # loop over the trees
    for tree in treeNames:
        tree_f1 = file1.Get(tree)
        tree_f2 = file2.Get(tree)

        print "Looking for tree", tree
        
        tn = ""
        try:
            tn = tree_f1.GetName()
        except:
            pass
        foundTree = len(tn) > 0
        if not foundTree:
            print "tree", tree, " not found. Skip to next one."
            continue
            pass
        
        if not foundFirstTree:
            branchNames1 = getBranchNames(file1.Get(tree))
            branchNames2 = getBranchNames(file2.Get(tree))
            # the commmon branches
            commonBranch = intersect(branchNames1, branchNames2)
            commonBranch.sort()
            # missing branch
            # missingBr = difference(branchNames1, branchNames2)
            # print(missingBr)
            print('Missing Branches in file1:')
            print (list(set(branchNames2)-set(branchNames1)))
            print('Missing Branches in file2:')
            print (list(set(branchNames1)-set(branchNames2)))
            foundFirstTree = True
            pass
        

        n_f1 = tree_f1.GetEntries()
        n_f2 = tree_f2.GetEntries()

        print 'Got tree:', tree
        print 'nEvent - file1:', n_f1, 'file2:', n_f2

        # Check if we need to treat multiQuads
        hasMultiQuads = False
        if tree == "tree_ZplusEl" or tree == "tree_relaxee":
            tree_f1.GetEntry(0)
            tree_f2.GetEntry(0)
            try:
                tree_f1.cand_index
                tree_f2.cand_index
                hasMultiQuads = True
            except:
                pass
            pass
        if hasMultiQuads:
            print "hasMultiQuads - allowing for comparison of more than one quadruplet(triplet) per event"
        else:
            print "Comparing on ONE quadruplet(triplet) per event"
            pass
        

        # building index to help with finding events later
        if hasMultiQuads:
            tree_f2.BuildIndex("event", "cand_index")
        else:
            tree_f2.BuildIndex("run", "event")

        
        # figure out the events that are missing
        # if(n_f1 != n_f2):
        if(not skipEventCheck and n_f1 != n_f2):
            print '\033[91m'+'CutFlow Mismatch'+'\033[0m'
            event_f1 = set()
            event_f2 = set()
            run      = 0
            
            for iEvt in range(n_f1):
                tree_f1.GetEntry(iEvt)
                if hasMultiQuads:
                    event_f1.add((tree_f1.event, tree_f1.cand_index))
                else:
                    event_f1.add((tree_f1.run, tree_f1.event))
                    pass
                pass
            
            for iEvt in range(n_f2):
                tree_f2.GetEntry(iEvt)
                if hasMultiQuads:
                    event_f2.add((tree_f2.event, tree_f2.cand_index))
                else:
                    event_f2.add((tree_f2.run, tree_f2.event))
                    pass
                pass
            

            eventInF1 = event_f1 - event_f2    
            eventInF2 = event_f2 - event_f1;

            print 'Event(s) only in file 1:'
            for event in eventInF1:
                if hasMultiQuads:
                    print event[0], '/', event[1], ",",
                else:
                    print event[1],
            print ''

            print 'Event(s) only in file 2:'
            for event in eventInF2:
                if hasMultiQuads:
                    print event[0], '/', event[1], ",",
                else:
                    print event[1],
            print ''

            pass

        # save indexes to events in f2 in a dictionary - needed for data because the
        # GetEntryWithIndex doesn't work with 64-bit event numbers
        f2_indexes = {}

        for iEvt in range(n_f2):
            tree_f2.GetEntry(iEvt)
            if hasMultiQuads:
                f2_indexes[(tree_f2.event, tree_f2.cand_index)] = iEvt
            else:
                f2_indexes[(tree_f2.run, tree_f2.event)] = iEvt
                pass
            pass
            

        nCompare       = [0] * len(commonBranch)
        nMatch         = 0
        for iEvt in range(n_f1):
            tree_f1.GetEntry(iEvt)

            # find the corresponding event in the 2nd file
            if hasMultiQuads:
                found = (tree_f1.event, tree_f1.cand_index) in f2_indexes
                if found:
                    tree_f2.GetEntry(f2_indexes[(tree_f1.event, tree_f1.cand_index)])
                    pass
                # print 'f1/f2 event cand_index', found, tree_f1.event, tree_f1.cand_index, tree_f2.event, tree_f2.cand_index
            else:
                found = (tree_f1.run, tree_f1.event) in f2_indexes
                if found:
                    tree_f2.GetEntry(f2_indexes[(tree_f1.run, tree_f1.event)])
                    pass
                    
            if not found:
                evtType = ""
                try:
                    evtType = evtTypes[tree_f1.event_type]
                except:
                    pass
                if hasMultiQuads:
                    print 'Cutflow mismatch: Event', tree_f1.event, 'multiQuad', tree_f1.cand_index, \
                        'not found in file 2 entry', iEvt, 'type', evtType
                else:
                    print 'Cutflow mismatch: Event', tree_f1.event, 'not found in file 2 entry', iEvt, 'type', evtType
                continue

            # if tree_f1.run != tree_f2.run and tree_f1.event != tree_f2.event:
            #     # print 'Cutflow still not matching'
            #     continue

            # print 'f1/f2 event cand_index', tree_f1.event, tree_f1.cand_index, tree_f2.event, tree_f2.cand_index
            
            nMatch += 1
            nBr = -1
            for iBr in commonBranch:
                if iBr in brsToSkip: continue
                val_f1 = getattr(tree_f1, iBr)
                val_f2 = getattr(tree_f2, iBr)
                nBr += 1

                size = 1
                try:
                    size = len(val_f1)
                except:
                    pass

                if size > 1:

                    for i in range(size):
                        diff = 0
                        if val_f1[i] != 0:
                            diff = math.fabs((val_f1[i]-val_f2[i])/val_f1[i])
                        elif val_f2[i] != 0:
                            diff = math.fabs((val_f1[i]-val_f2[i])/val_f2[i])
                        else:
                            diff = math.fabs(val_f1[i]-val_f2[i])
            
                        if (diff > epsilon):
                            if hasMultiQuads:
                                print "mismatch: ",iBr.ljust(50), i, str(tree_f1.event).ljust(8), str(tree_f1.cand_index).ljust(2), str(tree_f2.event).ljust(8), str(tree_f2.cand_index).ljust(2), val_f1[i], val_f2[i], diff, iEvt
                            else:
                                print "mismatch: ",iBr.ljust(50), i, str(tree_f1.event).ljust(8), val_f1[i], val_f2[i], diff, iEvt
                                pass
                            pass
                        else:
                            nCompare[nBr] += 1
                        pass
                    pass
                else:
                    diff = 0
                    if val_f1 != 0:
                        diff = math.fabs((val_f1-val_f2)/val_f1)
                    elif val_f2 != 0:
                        diff = math.fabs((val_f1-val_f2)/val_f2)
                    else:
                        diff = math.fabs(val_f1-val_f2)
        
                    if (diff > epsilon):
                        if hasMultiQuads:
                            print "mismatch: ",iBr.ljust(50), str(tree_f1.event).ljust(6), str(tree_f1.cand_index).ljust(2), str(tree_f2.event).ljust(6), str(tree_f2.cand_index).ljust(2), val_f1, val_f2, diff, iEvt
                        else:
                            print "mismatch: ",iBr.ljust(50), str(tree_f1.event).ljust(6), val_f1, val_f2, diff, iEvt
                            pass
                        pass
                    else:
                        nCompare[nBr] += 1
                    pass

            pass


        print 'Check ok for vars: ',
        for i in range(len(commonBranch)):
            if(nMatch == nCompare[i]):
                print commonBranch[i], nCompare[i],
            else:
                print '\033[91m'+commonBranch[i]+'\033[0m', nCompare[i],
        print '\n\n'

        
    file1.Close()
    file2.Close()



## get the name of the branches from the TTRrr
def getBranchNames(tree):
    branchNames = [];
    list_of_branches= tree.GetListOfBranches()
    for i in range(list_of_branches.GetEntries()):
        branch = list_of_branches.At(i)
        tempName = branch.GetName()
        #if 'truth' in tempName:
        #    continue
        branchNames.append(tempName)
        continue
    return branchNames

# returns the common element between two sets
def intersect(a, b):
    return list(set(a) & set(b))

## returns the difference between two list
def difference(a, b):
    diffList = []
    diffList = diffList + list(set(a)-set(b))
    diffList = diffList + list(set(b)-set(a))
    return diffList



if __name__ == '__main__':
    main()

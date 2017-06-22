#include "H4lCutFlow/CutEventTrigger.h"
using namespace std;

CutEventTrigger::CutEventTrigger(EventContainer* eventcont):
    CutEventBase(eventcont)
{
    m_tdt = ToolHandle<Trig::ITrigDecisionTool>("TrigDecisionTool");
    if(m_tdt.retrieve().isFailure())
    {
        LOG(logERROR) <<"CutEventTrigger::CutEventTrigger() - cannot retrieve ITrigDecisionTool";
        exit(1);
    }

    overWriteTrig = false;
    m_doTriMu = true;
    m_doTriEl = true;
    m_doElMu = true;
    m_doTrigStudy = false;

    m_printDebug = true;

}

CutEventTrigger::~CutEventTrigger()
{
}

void CutEventTrigger::initialize()
{
    singleMuTrigList = getTriggerString(getSingleMuTrig());
    diMuTrigList = getTriggerString(getDiMuTrig());
    triMuTrigList = getTriggerString(getTriMuTrig());

    singleElTrigList = getTriggerString(getSingleElTrig());
    diElTrigList = getTriggerString(getDiElTrig());
    triElTrigList = getTriggerString(getTriElTrig());

    elMuTrigList = getTriggerString(getElMuTrig());
}

void CutEventTrigger::clearVars()
{
    m_printDebug = true;
}


Bool_t CutEventTrigger::passCut() const
{
    // LOG(logDEBUG)<<"Trigger period: "<<m_eventCont->m_trigPeriod;
    // For triggers
    int runNumber = -1;
    if(m_eventCont->isMC)
    {
        runNumber =  m_eventCont->eventInfo->auxdecor<unsigned int>("RandomRunNumber");
    }
    else
    {
        runNumber = m_eventCont->eventInfo->runNumber();
    }
    LOG(logDEBUG)<<"Random run number: "<<runNumber;


    //// For debugging
    if(m_printDebug && m_eventCont->isDebug)
    {
        vector<TString> trigName = getSingleMuTrig();
        vector<TString> temp = getDiMuTrig();
        trigName.insert(trigName.end(), temp.begin(), temp.end());

        temp = getTriMuTrig();
        trigName.insert(trigName.end(), temp.begin(), temp.end());

        temp = getSingleElTrig();
        trigName.insert(trigName.end(), temp.begin(), temp.end());

        temp = getDiElTrig();
        trigName.insert(trigName.end(), temp.begin(), temp.end());

        temp = getTriElTrig();
        trigName.insert(trigName.end(), temp.begin(), temp.end());

        temp = getElMuTrig();
        trigName.insert(trigName.end(), temp.begin(), temp.end());


        for(Int_t i = 0; i < (Int_t) trigName.size(); i++)
        {
            LOG(logDEBUG)<<"Trigger "<<trigName[i]<<" : "<<m_tdt->isPassed(trigName[i].Data());
        }
        m_printDebug = false;
    }


    // Get the trigger list again... Needed for run dependant trigger list
    TString t_singleMuTrigList  = getTriggerString(getSingleMuTrig());
    TString t_diMuTrigList      = getTriggerString(getDiMuTrig());
    TString t_triMuTrigList     = getTriggerString(getTriMuTrig());
    TString t_singleElTrigList  = getTriggerString(getSingleElTrig());
    TString t_diElTrigList      = getTriggerString(getDiElTrig());
    TString t_triElTrigList     = getTriggerString(getTriElTrig());
    TString t_elMuTrigList      = getTriggerString(getElMuTrig());

    //// Debug information
    //LOG(logDEBUG)<<"singleMuonTrigger: "<<passTrigger(t_singleMuTrigList);
    //LOG(logDEBUG)<<"singleElectronTrigger: "<<passTrigger(t_singleElTrigList);
    //LOG(logDEBUG)<<"diMuonTrigger: "<<passTrigger(t_diMuTrigList);
    //LOG(logDEBUG)<<"diElectronTrigger: "<<passTrigger(t_diElTrigList);
    //LOG(logDEBUG)<<"TriMuonTrigger: "<<passTrigger(t_triMuTrigList);
    //LOG(logDEBUG)<<"TriElectronTrigger: "<<passTrigger(t_triElTrigList);
    //LOG(logDEBUG)<<"elMuTrigger: "<<passTrigger(t_elMuTrigList);


    // Actual Trigger
    if(passTrigger(t_singleMuTrigList)) return true;
    if(passTrigger(t_singleElTrigList)) return true;

    if(passTrigger(t_diMuTrigList)) return true;
    if(passTrigger(t_diElTrigList)) return true;

    if(m_doTriMu) if(passTrigger(t_triMuTrigList)) return true;
    if(m_doTriEl) if(passTrigger(t_triElTrigList)) return true;

    if(m_doElMu) if(passTrigger(t_elMuTrigList)) return true;

    return false;

}

Bool_t CutEventTrigger::passTrigger(const TString& trigList) const
{
    if(overWriteTrig) return true;

    if (m_tdt->isPassed(trigList.Data()))
    {
        return true;
    }
    else if (m_doTrigStudy) return true;
    else return false;

}

// Single Muon Trigger
Bool_t CutEventTrigger::singleMuonTrigger() const
{
    if(overWriteTrig) return true;

    if (m_tdt->isPassed(singleMuTrigList.Data()))
    {
        return true;
    }
    else if (m_doTrigStudy) return true;
    else return false;
}

// Di Muon Trigger
Bool_t CutEventTrigger::diMuonTrigger() const
{
    if(overWriteTrig) return true;

    if (m_tdt->isPassed(diMuTrigList.Data()))
    {
        return true;
    }
    else if (m_doTrigStudy) return true;
    else return false;

}

// TriMuon Trigger
Bool_t CutEventTrigger::triMuonTrigger() const
{
    if(overWriteTrig) return true;

    if (m_tdt->isPassed(triMuTrigList.Data()))
    {
        return true;
    }
    else if (m_doTrigStudy) return true;
    else return false;

}

// Single Electron Trigger
Bool_t CutEventTrigger::singleElectronTrigger() const
{
    if(overWriteTrig) return true;

    if (m_tdt->isPassed(singleElTrigList.Data()))
    {
        return true;
    }
    else if (m_doTrigStudy) return true;
    else return false;
}

// Di Electron Trigger
Bool_t CutEventTrigger::diElectronTrigger() const
{
    if(overWriteTrig) return true;

    if (m_tdt->isPassed(diElTrigList.Data()))
    {
        return true;
    }
    else if (m_doTrigStudy) return true;
    else return false;
}

// Tri Electron Trigger
Bool_t CutEventTrigger::triElectronTrigger() const
{
    if(overWriteTrig) return true;

    if (m_tdt->isPassed(triElTrigList.Data()))
    {
        return true;
    }
    else if (m_doTrigStudy) return true;
    else return false;
}


// Electron muon Trigger
Bool_t CutEventTrigger::elMuTrigger() const
{
    if(overWriteTrig) return true;

    if (m_tdt->isPassed(elMuTrigList.Data()))
    {
        return true;
    }
    else if (m_doTrigStudy) return true;
    else return false;
}

// List of single muon trigger name
vector<TString> CutEventTrigger::getSingleMuTrig() const
{
    vector<TString> triggerName;
    // 2015
    if(m_eventCont->m_trigPeriod == TrigPeriods::trig_2015_D || m_eventCont->m_trigPeriod == TrigPeriods::trig_2015_EtoJ)
    {
        triggerName.push_back("HLT_mu20_iloose_L1MU15");
        triggerName.push_back("HLT_mu50");
        triggerName.push_back("HLT_mu60_0eta105_msonly");
    }
    // 2016
    else
    {
        if(m_eventCont->m_dataPeriod == Periods::periodA2016)
        {
            // Data MC difference
            if(m_eventCont->isMC)
            {
                triggerName.push_back("HLT_mu24_ivarloose_L1MU15");
                triggerName.push_back("HLT_mu24_iloose_L1MU15");
            }
            else
            {
                triggerName.push_back("HLT_mu24_ivarloose");
                triggerName.push_back("HLT_mu24_iloose");
            }

            // Period A
            triggerName.push_back("HLT_mu40");
            triggerName.push_back("HLT_mu50");            
        }
        else if(m_eventCont->m_dataPeriod <= Periods::periodC2016)
        {
            triggerName.push_back("HLT_mu24_ivarmedium");
            triggerName.push_back("HLT_mu24_imedium");
            triggerName.push_back("HLT_mu50");
        }
        else if(m_eventCont->m_dataPeriod == Periods::periodD2016)
        {
            // Period D has trigger change in the middle 
            if(m_eventCont->eventInfo->auxdecor<unsigned int>("trigRunNumber") <= 302872)
            {
                triggerName.push_back("HLT_mu24_ivarmedium");
                triggerName.push_back("HLT_mu24_imedium");
                triggerName.push_back("HLT_mu50");
            }
            else
            {
                triggerName.push_back("HLT_mu24_ivarmedium");
                triggerName.push_back("HLT_mu24_imedium");
                triggerName.push_back("HLT_mu26_ivarmedium");
                triggerName.push_back("HLT_mu26_imedium");
                triggerName.push_back("HLT_mu50");
            }
        }
        else if(m_eventCont->m_dataPeriod <= Periods::periodE2016) 
        {
            triggerName.push_back("HLT_mu24_ivarmedium");
            triggerName.push_back("HLT_mu24_imedium");
            triggerName.push_back("HLT_mu26_ivarmedium");
            triggerName.push_back("HLT_mu26_imedium");
            triggerName.push_back("HLT_mu50");
        }
        else if(m_eventCont->m_dataPeriod <= Periods::periodF2016) 
        {
            triggerName.push_back("HLT_mu26_ivarmedium");
            triggerName.push_back("HLT_mu26_imedium");
            triggerName.push_back("HLT_mu50");
        }
	else if(m_eventCont->m_dataPeriod <= Periods::periodG2016)
	{
	    if(m_eventCont->eventInfo->auxdecor<unsigned int>("trigRunNumber") <= 305293)
	    {
	    	triggerName.push_back("HLT_mu26_ivarmedium");
                triggerName.push_back("HLT_mu26_imedium");
                triggerName.push_back("HLT_mu50");
	    }
	    else
	    {
		triggerName.push_back("HLT_mu26_ivarmedium");
		triggerName.push_back("HLT_mu50");
	    }
	}
	else
	{
	    triggerName.push_back("HLT_mu26_ivarmedium");
            triggerName.push_back("HLT_mu50");
	}
    }
    return triggerName;
}

// List of di muon trigger name
std::vector<TString> CutEventTrigger::getDiMuTrig() const
{
    vector<TString> triggerName;
    // 2015
    if(m_eventCont->m_trigPeriod == TrigPeriods::trig_2015_D || m_eventCont->m_trigPeriod == TrigPeriods::trig_2015_EtoJ)
    {
        triggerName.push_back("HLT_2mu10");
        triggerName.push_back("HLT_mu18_mu8noL1");
    }
    // 2016
    else
    {
        if(m_eventCont->m_dataPeriod == Periods::periodA2016)
        {
            triggerName.push_back("HLT_2mu10");
            triggerName.push_back("HLT_2mu10_nomucomb");
            triggerName.push_back("HLT_mu20_mu8noL1");
            triggerName.push_back("HLT_mu20_nomucomb_mu6noL1_nscan03");
        }
        else if(m_eventCont->m_dataPeriod <= Periods::periodC2016)
        {
            triggerName.push_back("HLT_2mu14");
            triggerName.push_back("HLT_2mu14_nomucomb");
            triggerName.push_back("HLT_mu20_mu8noL1");
            triggerName.push_back("HLT_mu20_nomucomb_mu6noL1_nscan03");
        }
        else if(m_eventCont->m_dataPeriod == Periods::periodD2016)
        {
            // Period D has trigger change in the middle in D3
            if(m_eventCont->eventInfo->auxdecor<unsigned int>("trigRunNumber") <= 302872)
            {
                triggerName.push_back("HLT_2mu14");
                triggerName.push_back("HLT_2mu14_nomucomb");
                triggerName.push_back("HLT_mu20_mu8noL1");
                triggerName.push_back("HLT_mu20_nomucomb_mu6noL1_nscan03");
            }
            else
            {
                triggerName.push_back("HLT_2mu14");
                triggerName.push_back("HLT_mu20_mu8noL1");
                triggerName.push_back("HLT_mu22_mu8noL1");
            }
        }
        else if(m_eventCont->m_dataPeriod == Periods::periodE2016)
        {
            triggerName.push_back("HLT_2mu14");
            triggerName.push_back("HLT_mu20_mu8noL1");            
            triggerName.push_back("HLT_mu22_mu8noL1");
        }
	else
	{
            triggerName.push_back("HLT_2mu14");
            triggerName.push_back("HLT_mu22_mu8noL1");
        }


    }

    return triggerName;
}

// List of tri muon trigger name
std::vector<TString> CutEventTrigger::getTriMuTrig() const
{
    vector<TString> triggerName;
    // 2015
    if(m_eventCont->m_trigPeriod == TrigPeriods::trig_2015_D || m_eventCont->m_trigPeriod == TrigPeriods::trig_2015_EtoJ)
    {
        triggerName.push_back("HLT_3mu6");
        triggerName.push_back("HLT_mu18_2mu4noL1");
        triggerName.push_back("HLT_3mu6_msonly");
    }
    // 2016
    else
    {
        if(m_eventCont->m_dataPeriod == Periods::periodA2016)
        {
            triggerName.push_back("HLT_mu20_2mu4noL1");
            triggerName.push_back("HLT_3mu4");
            triggerName.push_back("HLT_mu6_2mu4");
            triggerName.push_back("HLT_mu11_nomucomb_2mu4noL1_nscan03_L1MU11_2MU6");
            triggerName.push_back("HLT_mu20_msonly_mu10noL1_msonly_nscan05_noComb");
        }
        else if(m_eventCont->m_dataPeriod <= Periods::periodC2016)
        {
            triggerName.push_back("HLT_mu20_2mu4noL1");
            triggerName.push_back("HLT_3mu6");
            triggerName.push_back("HLT_mu6_2mu4");
            triggerName.push_back("HLT_mu11_nomucomb_2mu4noL1_nscan03_L1MU11_2MU6");
            triggerName.push_back("HLT_mu20_msonly_mu10noL1_msonly_nscan05_noComb");
        }
        else if(m_eventCont->m_dataPeriod == Periods::periodD2016)
        {
            // Period D has trigger change in the middle in D3
            if(m_eventCont->eventInfo->auxdecor<unsigned int>("trigRunNumber") <= 302872)
            {
                triggerName.push_back("HLT_mu20_2mu4noL1");
                triggerName.push_back("HLT_3mu6");
                triggerName.push_back("HLT_mu6_2mu4");
                triggerName.push_back("HLT_mu11_nomucomb_2mu4noL1_nscan03_L1MU11_2MU6");
                triggerName.push_back("HLT_mu20_msonly_mu10noL1_msonly_nscan05_noComb");
            }
            else
            {
                triggerName.push_back("HLT_mu20_2mu4noL1");
                triggerName.push_back("HLT_3mu6_msonly");
            }
        }
        else
        {
	    triggerName.push_back("HLT_mu20_2mu4noL1");
            triggerName.push_back("HLT_3mu6_msonly");
            if (m_eventCont->eventInfo->auxdecor<unsigned int>("trigRunNumber") >= 307619)
	    {
		triggerName.push_back("HLT_3mu4");
	    }
	}
    }
    return triggerName;
}

// List of single electron trigger name
std::vector<TString> CutEventTrigger::getSingleElTrig() const
{
    vector<TString> triggerName;

    // 2015
    if(m_eventCont->m_trigPeriod == TrigPeriods::trig_2015_D) 
    {
        triggerName.push_back("HLT_e24_lhmedium_L1EM18VH");
        triggerName.push_back("HLT_e60_lhmedium");
        triggerName.push_back("HLT_e120_lhloose");
    }
    else if(m_eventCont->m_trigPeriod == TrigPeriods::trig_2015_EtoJ)
    {
        triggerName.push_back("HLT_e24_lhmedium_L1EM20VH");
        triggerName.push_back("HLT_e60_lhmedium");
        triggerName.push_back("HLT_e120_lhloose");
    }
    // 2016
    else
    {
        if(m_eventCont->m_dataPeriod <= Periods::periodC2016)
        {
            // Prescaler issue
            if(m_eventCont->eventInfo->auxdecor<unsigned int>("trigRunNumber") == 298687) 
                triggerName.push_back("HLT_e24_lhmedium_nod0_L1EM20VH");

            triggerName.push_back("HLT_e24_lhtight_nod0_ivarloose");
            triggerName.push_back("HLT_e60_lhmedium_nod0");
            triggerName.push_back("HLT_e60_medium");
            triggerName.push_back("HLT_e140_lhloose_nod0");
            triggerName.push_back("HLT_e300_etcut");
        }
        else if(m_eventCont->m_dataPeriod == Periods::periodD2016)
        {
            // Period D has trigger change in the middle in D3
            if(m_eventCont->eventInfo->auxdecor<unsigned int>("trigRunNumber") <= 302872)
            {
                // Prescaler issue
                if(m_eventCont->eventInfo->auxdecor<unsigned int>("trigRunNumber") == 298687) 
                    triggerName.push_back("HLT_e24_lhmedium_nod0_L1EM20VH");

                triggerName.push_back("HLT_e24_lhtight_nod0_ivarloose");
                triggerName.push_back("HLT_e60_lhmedium_nod0");
                triggerName.push_back("HLT_e60_medium");
                triggerName.push_back("HLT_e140_lhloose_nod0");
                triggerName.push_back("HLT_e300_etcut");
            }
            else
            {
                triggerName.push_back("HLT_e26_lhtight_nod0_ivarloose");
                triggerName.push_back("HLT_e60_lhmedium_nod0");
                triggerName.push_back("HLT_e60_medium");
                triggerName.push_back("HLT_e140_lhloose_nod0");
                triggerName.push_back("HLT_e300_etcut");
            }
        }
        else
        {
            triggerName.push_back("HLT_e26_lhtight_nod0_ivarloose");
            triggerName.push_back("HLT_e60_lhmedium_nod0");
            triggerName.push_back("HLT_e60_medium");
            triggerName.push_back("HLT_e140_lhloose_nod0");
            triggerName.push_back("HLT_e300_etcut");

        }

    }

    return triggerName;
}

// List of di electron trigger name
std::vector<TString> CutEventTrigger::getDiElTrig() const
{
    vector<TString> triggerName;
    // 2015
    if(m_eventCont->m_trigPeriod == TrigPeriods::trig_2015_D || m_eventCont->m_trigPeriod == TrigPeriods::trig_2015_EtoJ)
    {
        triggerName.push_back("HLT_2e12_lhloose_L12EM10VH");
    }
    // 2016
    else
    {
        if(m_eventCont->m_dataPeriod <= Periods::periodC2016)
        {
            triggerName.push_back("HLT_2e15_lhvloose_nod0_L12EM13VH");

            // Prescaler issue
            if(m_eventCont->eventInfo->auxdecor<unsigned int>("trigRunNumber") == 300540) 
                triggerName.push_back("HLT_2e17_lhvloose_nod0");
        }
        else if(m_eventCont->m_dataPeriod == Periods::periodD2016)
        {
            // Period D has trigger change in the middle in D3
            if(m_eventCont->eventInfo->auxdecor<unsigned int>("trigRunNumber") <= 302872)
            {
                triggerName.push_back("HLT_2e15_lhvloose_nod0_L12EM13VH");
            }
            else
            {
                triggerName.push_back("HLT_2e17_lhvloose_nod0");
            }
        }
        else
        {
            triggerName.push_back("HLT_2e17_lhvloose_nod0");
        }

    }


    return triggerName;
}

// List of tri electron trigger name
std::vector<TString> CutEventTrigger::getTriElTrig() const
{
    vector<TString> triggerName;    
    // 2015
    if(m_eventCont->m_trigPeriod == TrigPeriods::trig_2015_D || m_eventCont->m_trigPeriod == TrigPeriods::trig_2015_EtoJ)
    {
        triggerName.push_back("HLT_e17_lhloose_2e9_lhloose");
    }
    // 2016
    else
    {
        triggerName.push_back("HLT_e17_lhloose_nod0_2e9_lhloose_nod0");
    }

    return triggerName;
}

// List of electron-muon trigger name
std::vector<TString> CutEventTrigger::getElMuTrig() const
{
    vector<TString> triggerName;
    // 2015
    if(m_eventCont->m_trigPeriod == TrigPeriods::trig_2015_D || m_eventCont->m_trigPeriod == TrigPeriods::trig_2015_EtoJ)
    {
        triggerName.push_back("HLT_e17_lhloose_mu14");
        triggerName.push_back("HLT_2e12_lhloose_mu10");
        triggerName.push_back("HLT_e12_lhloose_2mu10");
        triggerName.push_back("HLT_e24_medium_L1EM20VHI_mu8noL1");
        triggerName.push_back("HLT_e7_medium_mu24");
    }
    // 2016
    else
    {
        if(m_eventCont->m_dataPeriod <= Periods::periodC2016)
        {
            triggerName.push_back("HLT_e17_lhloose_nod0_mu14");
            triggerName.push_back("HLT_e24_lhmedium_nod0_L1EM20VHI_mu8noL1");
            triggerName.push_back("HLT_e7_lhmedium_nod0_mu24");
            triggerName.push_back("HLT_e12_lhloose_nod0_2mu10");
            triggerName.push_back("HLT_2e12_lhloose_nod0_mu10");

        }
        else if(m_eventCont->m_dataPeriod == Periods::periodD2016)
        {
            // Period D has trigger change in the middle in D3
            if(m_eventCont->eventInfo->auxdecor<unsigned int>("trigRunNumber") <= 302872)
            {
                triggerName.push_back("HLT_e17_lhloose_nod0_mu14");
                triggerName.push_back("HLT_e24_lhmedium_nod0_L1EM20VHI_mu8noL1");
                triggerName.push_back("HLT_e7_lhmedium_nod0_mu24");
                triggerName.push_back("HLT_e12_lhloose_nod0_2mu10");
                triggerName.push_back("HLT_2e12_lhloose_nod0_mu10");

            }
            else
            {
                triggerName.push_back("HLT_e7_lhmedium_mu24");
                triggerName.push_back("HLT_e12_lhloose_2mu10");
                triggerName.push_back("HLT_2e12_lhloose_mu10");
                triggerName.push_back("HLT_e12_lhloose_nod0_2mu10");
                triggerName.push_back("HLT_2e12_lhloose_nod0_mu10");
            }
        }
        else
        {
            triggerName.push_back("HLT_e7_lhmedium_mu24");
            triggerName.push_back("HLT_e12_lhloose_2mu10");
            triggerName.push_back("HLT_2e12_lhloose_mu10");
            triggerName.push_back("HLT_e12_lhloose_nod0_2mu10");
            triggerName.push_back("HLT_2e12_lhloose_nod0_mu10");
        }
    }


    return triggerName;
}

// Get a trigger name that is readable by TDT
TString CutEventTrigger::getTriggerString(const std::vector<TString>& trigName) const
{
    TString trigString = "";
    if(trigName.size() == 0) return trigString;

    trigString = trigName[0];

    for(Int_t i = 0; i < (Int_t) trigName.size(); i++)
    {
        trigString += (" || " + trigName[i]);
    }

    return trigString;
}

Int_t CutEventTrigger::singleTrigger(TString singleTrigName) const
{
    if(m_tdt->isPassed(singleTrigName.Data())) return 1;
    else return 0;
}


#ifndef SAMPLESHOWERINFO_H
#define SAMPLESHOWERINFO_H

#include <string>


namespace SampleShowerInfo
{
    // This gets the efficiency map for btagging SF tool
    void fillEffMapForBTag(std::string& effMap);

    // Return backs the MC used for showering
    void fillSampleShowerInfo(const std::string& containerName, std::string& showerMCName);

    void fillIndexForBTag(const std::string& containerName, int& index);
}
#endif//SAMPLESHOWERINFO_H

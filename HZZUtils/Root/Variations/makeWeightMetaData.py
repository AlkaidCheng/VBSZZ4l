def makeWeightMetaData(infile,DSID,outfile):
    Names = []
    Indices = []
    i=0
    for line in open(infile,"r"):
        line = line.strip()
        if line.find('HepMCWeightNames') > -1 :
            meta = line.split("{")
            allweights = meta[1]
            weights = allweights.split(",")
            keepText=""
            for j in range(len(weights)):
                w = weights[j].strip("}")
                if(":" not in w):
                    w = w.strip(" ' ")
                    keepText+=w+", "
                    continue
                i=i+1
                w = w.strip(" ' ")
                pair = w.split("':")
                tempName=keepText+pair[0].strip(" ")
                Names.append(tempName)
                Indices.append(pair[1])
                keepText=""

    output = open(outfile,'w')
    output.write("// Mapping of Weights for DSID "+str(DSID)+"\n")
    output.write("// Generating by the python scriot makeWeightMetaData.py\n")
    output.write("//    by parsing the input file"+infile+"\n")
    output.write("\n")
    collection = 'm_variations_'+str(DSID)
    output.write("  std::map<std::string, int> "+collection+";\n")
    output.write("\n")
    for j in range(i):
        output.write("  "+collection+'.insert(std::make_pair("'+Names[j]+'",'+Indices[j]+'));\n')

    output.write("\n")
    output.write("m_variations.insert(std::make_pair("+str(DSID)+","+collection+"));\n")
    output.close()

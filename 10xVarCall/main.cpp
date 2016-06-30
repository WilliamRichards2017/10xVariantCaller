
//
//  main.cpp
//  10xVarCall
//
//  Created by Will Richards  on 6/16/16.
//  Copyright © 2016 WillRichards. All rights reserved.
//

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <set>
#include <vector>
#include <utility>
#include <unordered_map>
#include <string>


#include <shared/bamtools_global.h>
#include <api/api_global.h>
#include "api/BamMultiReader.h"
#include "api/BamWriter.h"
#include <api/SamReadGroupDictionary.h>

int SIZE = 91579;


using namespace std;
using namespace BamTools;



typedef std::unordered_map<std::string,int> hashmap_t;



void hashMaptoFile(hashmap_t &hashmap) {
    hashmap_t::iterator hashIt;
    
    ofstream barCodeCSV;
    barCodeCSV.open("barCodeFreq.csv");
    
    for (hashIt = hashmap.begin(); hashIt != hashmap.end(); hashIt++) {
        barCodeCSV << hashIt->first << ","  << hashIt->second << "\n" ;
    }
}

void printHashMap(hashmap_t &hashmap) {
    hashmap_t::iterator hashIt;
    
    for (hashIt = hashmap.begin(); hashIt != hashmap.end(); hashIt++) {
        cout << "barcode is: "  << hashIt->first << "frequency is: "  << hashIt->second << "\n" ;
    }
}





int main() {
    
    const std::string &filename = "/uufs/chpc.utah.edu/common/home/u0401321/TenX/bams/HG00512_WGS_phased_possorted_bam.bam";
    
    string outputFilename;
    
    BamTools::BamReader reader;
    reader.Open(filename);
    cout << filename << "\n";
    if(!reader.IsOpen()) {
        cout<<"{\"status\":\"error\", \"message\":\"Cannot open the specified file\"}"<<endl;
        exit(1);
    }
    
    const BamTools::RefVector refVector = reader.GetReferenceData();
    //cout << refVector.size() << "\n";
    map<int32_t, string> chromIDNameMap;
    for(size_t i=0; i<refVector.size(); i++) {
        chromIDNameMap[reader.GetReferenceID(refVector[i].RefName)] = refVector[i].RefName;
        cout << refVector[i].RefName  << "\n";
    }
    
    const SamHeader header = reader.GetHeader();
    const RefVector references = reader.GetReferenceData();
    
    BamAlignment al;
    int i = 0;
    hashmap_t hashMap;
    
    // iterate though alignnets, only keeping one with a high-ish quality
    
    // Generates a multiset of all barcodes
    
    while ( reader.GetNextAlignment(al)) {
        
        if ( al.MapQuality >= 10 ) {
            
            string  bx;
            
            if (al.GetTag("BX", bx)) {
                
                // barCodes.insert(bx);
                
                if (hashMap.count(bx) == 1) {
                    
                    // cout << "key already exists";
                    
                    hashMap.find(bx)->second++;
                    
                }
                
                else {
                    
                    //hashMap.insert(bx, 1);
                    
                    hashMap[bx] = 1;
                    
                }
                
            }
            
        }
        
        i++;
        
    }
    
    
    
    printHashMap(hashMap);
    
    hashMaptoFile(hashMap);
    
    // close the reader & writer                                                                                                                       
    
    reader.Close();
    
    return 0;




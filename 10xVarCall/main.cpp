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


#include <shared/bamtools_global.h>
#include <api/api_global.h>
#include "api/BamMultiReader.h"
#include "api/BamWriter.h"
#include <api/SamReadGroupDictionary.h>

#define SIZE 91579;


using namespace std;
using namespace BamTools;


typedef std::multiset<string> multiset_t;



// Returns a Vector of pairs (allocated on heap)
// first element of pair contains a barcode
// second elemnt of pair returns a count of the barcode
std::vector<std::pair<string, unsigned long>> getFreqCount(multiset_t &multiset)
{
    std::vector<std::pair<string, unsigned long>> pairList;
     for (multiset_t::iterator  it = multiset.begin(); it!=multiset.end(); it++) {
        std::pair<string, unsigned long> barCodeCount = std::make_pair(*it, multiset.count(*it));
        //std::cout << barCodeCount.first << ":" << barCodeCount.second << " ";
        pairList.push_back(barCodeCount);
     }
    return pairList;
}


// This function removes duplicates by converting it to a set, then dump set back into vector
// Because number of duplicates is large, this approach is more efficient than manually converting data to
// a set or by removing non-unique elements directly fomr a vector
//
std::vector<std::pair<string, unsigned long>> removeDuplicates(std::vector<std::pair<string, unsigned long>>  &freqCountList) {
    
    set<pair<string, unsigned long>> uniqueSet;
    unsigned long size = freqCountList.size();
    for( unsigned i = 0; i < size; ++i ) uniqueSet.insert( freqCountList[i] );
    freqCountList.assign( uniqueSet.begin(), uniqueSet.end() );
    
    //std::cout << "Number of elements in set:" << freqCountList.size() << "\n" ;
    
    return freqCountList;
    
}

void printSet(std::vector<std::pair<string, unsigned long>> &set) {
    
    std::vector<std::pair<string, unsigned long>>::size_type sz = set.size();
    
    for (unsigned i=0; i<sz; i++) {
        std::cout << "barcode is: " << set[i].first << "," << " frequency is " << set[i].second << "\n" ;
     }
}

void setToFile(std::vector<std::pair<string, unsigned long>> &set) {
    
    std::vector<std::pair<string, unsigned long>>::size_type sz = set.size();
    
    ofstream barCodeCSV;
    barCodeCSV.open("barCodeFreq.csv");
    
    for (unsigned i=0; i<sz; i++) {
        barCodeCSV << set[i].first << ","  << set[i].second << "\n" ;
    }
    
    barCodeCSV.close();
}


int main() {
    
    const std::string &filename = "/Users/awr/Desktop/10xVariantCaller/10xVarCall/Bams/bam1.bam";
    
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

    // iterate through all alignments, only keeping ones with high map quality
    BamAlignment al;
    SamReadGroup srg;
    int i = 0;
    multiset_t barCodes;

    // generates a multiset of all of the allignemnet map qualities
    // allignment map quality is a place holder till I can get the barcodes
    while ( reader.GetNextAlignment(al) ) {
        if ( al.MapQuality >= 90 ) {
            barCodes.insert(al.TagData);
       
      //cannot get tag with sample dataset because allignment is core only
      //    uint32_t bx;
      //  if (al.GetTag("BX", bx)) {
      //      barCodes.insert(bx)
      //  }
        }
            i++;
        }
    
    std::vector<std::pair<string, unsigned long>> freqCount = getFreqCount(barCodes);
    std::vector<std::pair<string, unsigned long>> uniqueSet = removeDuplicates(freqCount);
    //printSet(uniqueSet);
    //setToFile(uniqueSet);
    

    
    // close the reader & writer
    reader.Close();
    return 0;
    
}







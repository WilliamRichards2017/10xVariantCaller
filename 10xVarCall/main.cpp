//
//  main.cpp
//  10xVarCall
//
//  Created by Will Richards  on 6/16/16.
//  Copyright © 2016 WillRichards. All rights reserved.
//

#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <set>
#include <vector>
#include <utility>


#include <shared/bamtools_global.h>
#include <api/api_global.h>
#include "api/BamMultiReader.h"
#include "api/BamWriter.h"

#define SIZE 95725;



using namespace std;
using namespace BamTools;


typedef std::multiset<int> multiset_t;



// Returns a Vector of pairs (allocated on heap)
// first element of pair contains a barcode
// second elemnt of pair returns a count of the barcode
std::vector<std::pair<int, unsigned long>> getFreqCount(multiset_t &multiset)
{

    std::vector<std::pair<int, unsigned long>> pairList{};
    for (auto element: multiset) {
        std::pair<int, unsigned long> barCodeCount = std::make_pair(element, multiset.count(element));
        std::cout << barCodeCount.first << ":" << barCodeCount.second << " ";
        pairList.push_back(barCodeCount);
    }
    
    std::vector<std::pair<int, unsigned long>>::size_type sz = pairList.size();
    
    for (unsigned i=0; i<sz; i++) {
        std::cout << "first is:" << pairList[i].first << "\n";
    }
    return pairList;
}


// This function removes duplicates by converting it to a set, then dump set back into vector
// Because number of duplicates is large, this approach is more efficient than manually converting data to
// a set or by removing non-unique elements directly fomr a vector
//
std::vector<std::pair<int, unsigned long>> removeDuplicates(std::vector<std::pair<int, unsigned long>>  &freqCountList) {
    
   // set<int> s;
   // unsigned size = vec.size();
   // for( unsigned i = 0; i < size; ++i ) s.insert( vec[i] );
   // vec.assign( s.begin(), s.end() );
    
    return freqCountList;
    
}




int main() {
    
    const std::string &filename = "/Users/awr/Desktop/10xVarCall/10xVarCall/Bams/bam1.bam";
    
    string outputFilename;
    
    BamTools::BamReader reader;
    reader.Open(filename);
    cout << filename << "\n";
        if(!reader.IsOpen()) {
            cout<<"{\"status\":\"error\", \"message\":\"Cannot open the specified file\"}"<<endl;
            exit(1);
        }
    
    const BamTools::RefVector refVector = reader.GetReferenceData();
    cout << refVector.size() << "\n";
    map<int32_t, string> chromIDNameMap;
    for(size_t i=0; i<refVector.size(); i++) {
        chromIDNameMap[reader.GetReferenceID(refVector[i].RefName)] = refVector[i].RefName;
        cout << refVector[i].RefName;
    }
    
    const SamHeader header = reader.GetHeader();
    const RefVector references = reader.GetReferenceData();

    // iterate through all alignments, only keeping ones with high map quality
        BamAlignment al;
        int i = 0;
       multiset_t barCodes;
        // generates a multiset of all of the allignemnet map qualities
        //
        while ( reader.GetNextAlignment(al) ) {
            if ( al.MapQuality >= 90 )
                
                barCodes.insert(al.MapQuality);
                i++;
        }
    

     std::vector<std::pair<int, unsigned long>> freqCount = getFreqCount(barCodes);
    
    
    
    
        // close the reader & writer
        reader.Close();
    return 0;
    
}







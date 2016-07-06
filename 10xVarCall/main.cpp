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

#include <vector>

#include <utility>

#include <unordered_map>

#include <string>

#include <iomanip>

#include <numeric>

#include <algorithm>





#include <shared/bamtools_global.h>

#include <api/api_global.h>

#include "api/BamMultiReader.h"

#include "api/BamWriter.h"

#include <api/SamReadGroupDictionary.h>





using namespace std;

using namespace BamTools;





typedef std::unordered_map<std::string,std::pair<int32_t, vector<int32_t>>> hashmap_t;

typedef vector< vector<int32_t > > cluster_t;

typedef vector< pair<string, cluster_t> > clusterList_t;





void hashMaptoFile(hashmap_t &hashmap) {
    
    hashmap_t::iterator hashIt;
    
    vector<int32_t>::iterator vecIt;
    
    int i;
    
    
    
    ofstream barCodeCSV;
    
    barCodeCSV.open("barCodeFreq.csv");
    
    
    
    for (hashIt = hashmap.begin(); hashIt != hashmap.end(); hashIt++) {
        
        barCodeCSV << hashIt->first << ","  << hashIt->second.first;
        
        for (vecIt = hashIt->second.second.begin(); vecIt != hashIt->second.second.end(); vecIt++) {
            
            barCodeCSV << ","  << vecIt[i];
            
        }
        
        barCodeCSV << "\n";
        
    }
    
}

void printHashMap(hashmap_t &hashmap) {
    
    hashmap_t::iterator hashIt;
    
    vector<int32_t>::iterator vecIt;
    
    int i;
    
    for (hashIt = hashmap.begin(); hashIt != hashmap.end(); hashIt++) {
        
        cout << "barcode is: "  << hashIt->first << "  frequency is: "  << hashIt->second.first  << "  barcode positions are ";
        
        for (vecIt = hashIt->second.second.begin(); vecIt != hashIt->second.second.end(); vecIt++) {
            
            cout << vecIt[i] << ", ";
            
        }
        
        cout << "\n";
        
    }
    
    
    
}



void barCodeStats(hashmap_t &hashmap) {
    
    int i;
    
    hashmap_t::iterator hashIt;
    
    std::vector<int32_t> freqList;
    
    vector<int32_t>::iterator vecIt;
    
    
    
    
    
    for (hashIt = hashmap.begin(); hashIt != hashmap.end(); hashIt++) {
        
        freqList.push_back(hashIt->second.first);
        
    }
    
    
    
    int averageFreq = accumulate(freqList.begin(), freqList.end(), 0.0 )/ freqList.size();
    
    vecIt = max_element(freqList.begin(), freqList.end());
    
    cout << "averge freq is: " << averageFreq << endl;
    
    cout << "max freq is:  "  << *vecIt << endl;
    
    
    
}

clusterList_t clusters(hashmap_t &hashmap) {
    
    hashmap_t::iterator hashIt;
    
    vector<int32_t>::iterator vecIt;
    
    int i;
    
    vector< pair<string, cluster_t> > clusterList;
    
    
    
    for (hashIt = hashmap.begin(); hashIt != hashmap.end(); hashIt++) {
        
        pair<string, cluster_t> barCodeCluster;
        
        vector<int32_t> initCluster;
        
        int32_t initInt = hashIt->second.second[0];
        
        initCluster.push_back(initInt);
        
        barCodeCluster.first = hashIt->first;
        
        barCodeCluster.second.push_back(initCluster);
        
        for (vecIt = hashIt->second.second.begin(); vecIt != hashIt->second.second.end(); vecIt++) {
            
            
            
            if ((vecIt[i] < (barCodeCluster.second.back().back() + 500)) && (vecIt[i] > (barCodeCluster.second.back().back() - 500))) {
                
                barCodeCluster.second.back().push_back(vecIt[i]);
                
                barCodeCluster.first = hashIt->first;
                
                // clusterList.push_back(barCodeCluster);
                
                //  cout << "vector is is: " << vecIt[i] << endl;
                
                //cout << "cluster is : " << clusterList.back()[0] << endl;
                
                
                
            }
            
            
            else {
                
                vector<int32_t> cluster;
                
                cluster.push_back(vecIt[i]);
                
                barCodeCluster.second.push_back(cluster);
                
                // clusterList.push_back(barCodeCluster);
                
                //      cout << "create new cluster here: " << endl;
                
            }
            
        }
        
        clusterList.push_back(barCodeCluster);
        
        
        
        
        
        // vector<vector<int32_t> >::iterator clustIt;
        
        // vector<int32_t>::iterator readIt;
        
        // for (clustIt = barCodeCluster.second.begin(); clustIt!=barCodeCluster.second.end(); clustIt++) {
        
        //      cout << "barcode:  " << hashIt->first << ",  cluster positions:"  ;
        
        // for (readIt = clustIt->begin(); readIt != clustIt->end(); readIt++) {
        
        //  cout << " " << *readIt << ",";
        
        //  }
        
        //     cout << endl;
        
        //  }
        
    }
    
    return clusterList;
    
}

void printClusters(vector< pair<string, cluster_t> >  &clusterList) {
    
    
    
    vector<pair<string, cluster_t> >::iterator vecIt;
    
    // pair<string, cluster_t>::iterator pairIt;
    
    cluster_t::iterator clustIt;
    
    vector<int32_t>::iterator readIt;
    
    
    
    for (vecIt = clusterList.begin(); vecIt!= clusterList.end(); vecIt++) {
        
        
        
        cout << "barcode : " << vecIt->first << ", cluster(s): ";
        
        for (clustIt = vecIt->second.begin(); clustIt!= vecIt->second.end(); clustIt++) {
            
            cout << "||";
            
            for (readIt = clustIt->begin(); readIt!=clustIt->end(); readIt++) {
                
                cout  << *readIt << ", ";
                
                
                
            }
            
        }
        
        cout << "||" << endl;
        
    }
    
    // for (clustIt = .second.begin(); clustIt!=barCodeCluster.second.end(); clustIt++) {
    
    //    cout << "barcode:  " << clusterList.first << ",  cluster positions:"  ;
    
    // for (readIt = clustIt->begin(); readIt != clustIt->end(); readIt++) {
    
    //  cout << " " << *readIt << ",";
    
    //  }
    
    //     cout << endl;
    
    // }
    
    //  }
    
    
    
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
    while ( reader.GetNextAlignment(al) && i < 100000) {
        if ( al.MapQuality >= 10) {
            string  bx;
            
            if (al.GetTag("BX", bx)) {
                //if key already exists, add to freq count and position list
                if (hashMap.count(bx) == 1) {
                    hashMap.find(bx)->second.second.push_back(al.Position);
                    hashMap.find(bx)->second.first++;
                }
                //if new key, create new pair of frequency count and position list
                else {
                    
                    std::vector<int32_t> positionList;
                    
                    positionList.push_back(al.Position);
                    
                    hashMap[bx] = make_pair(1, positionList);
                    
                }
                
            }
            
            i++;
            
        }
        
    }
    
    
    
    // printHashMap(hashMap);                                                                                                                                               
    
    // hashMaptoFile(hashMap);                                                                                                                                              
    
    // barCodeStats(hashMap);                                                                                                                                               
    
    
    
    // printClusters(clusters);                                                                                                                                             
    
    clusterList_t clusterList =  clusters(hashMap);
    
    printClusters(clusterList);
    
    // close the reader & writer                                                                                                                                              
    
    
    
    reader.Close();
    
    return 0;
    
    
    
}





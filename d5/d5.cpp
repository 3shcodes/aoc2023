#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


vector<string> splitString( char c, string ques ) {
    

    vector<string> res;
    string currString = "";

    for ( char cInd : ques ) {
        if ( cInd == c ) {
            if ( currString != "" ) {
                res.push_back(currString);
                currString = "";
            }
        } else {
            currString += cInd;
        }
    }

    res.push_back(currString);

    return res;
}
struct RangeItem {

    long destStart;
    long sourceStart;
    long rangeLen;

};

struct Almanac {

    vector<RangeItem> seedToSoil;
    vector<RangeItem> soilToFert;
    vector<RangeItem> fertToWater;
    vector<RangeItem> waterToLight;
    vector<RangeItem> lightToTemp;
    vector<RangeItem> tempToHumid;
    vector<RangeItem> humidToLocation;

};

Almanac alm;

void printAlm() {
    
    cout << "seed-to-soil map:" << endl;
    for ( RangeItem ri: alm.seedToSoil ) {
        cout << ri.destStart << " " << ri.sourceStart << " " << ri.rangeLen << endl;
    }
    cout << endl;

    cout << "soil-to-fertilizer map:" << endl;
    for ( RangeItem ri: alm.soilToFert ) {
        cout << ri.destStart << " " << ri.sourceStart << " " << ri.rangeLen << endl;
    }
    cout << endl;

    cout << "fertilizer-to-water map:" << endl;
    for ( RangeItem ri: alm.fertToWater ) {
        cout << ri.destStart << " " << ri.sourceStart << " " << ri.rangeLen << endl;
    }
    cout << endl;

    cout << "water-to-light map:" << endl;
    for ( RangeItem ri: alm.waterToLight ) {
        cout << ri.destStart << " " << ri.sourceStart << " " << ri.rangeLen << endl;
    }
    cout << endl;

    cout << "light-to-temperature map:" << endl;
    for ( RangeItem ri: alm.lightToTemp ) {
        cout << ri.destStart << " " << ri.sourceStart << " " << ri.rangeLen << endl;
    }
    cout << endl;

    cout << "temperature-to-humidity map:" << endl;
    for ( RangeItem ri: alm.tempToHumid ) {
        cout << ri.destStart << " " << ri.sourceStart << " " << ri.rangeLen << endl;
    }
    cout << endl;

    cout << "humidity-to-location map:" << endl;
    for ( RangeItem ri: alm.humidToLocation ) {
        cout << ri.destStart << " " << ri.sourceStart << " " << ri.rangeLen << endl;
    }
    cout << endl;
}


long getLocation( long seed ) {

    long currVal = seed;
    for ( RangeItem rItem: alm.seedToSoil ) {
        if ( rItem.sourceStart <= currVal && currVal <= rItem.sourceStart + rItem.rangeLen - 1 ) {
            currVal = rItem.destStart + currVal - rItem.sourceStart;
            break;
        }
    }

    for ( RangeItem rItem: alm.soilToFert ) {
        if ( rItem.sourceStart <= currVal && currVal <= rItem.sourceStart + rItem.rangeLen - 1 ) {
            currVal = rItem.destStart + currVal - rItem.sourceStart;
            break;
        }
    }

    for ( RangeItem rItem: alm.fertToWater ) {
        if ( rItem.sourceStart <= currVal && currVal <= rItem.sourceStart + rItem.rangeLen - 1 ) {
            currVal = rItem.destStart + currVal - rItem.sourceStart;
            break;
        }
    }

    for ( RangeItem rItem: alm.waterToLight ) {
        if ( rItem.sourceStart <= currVal && currVal <= rItem.sourceStart + rItem.rangeLen - 1 ) {
            currVal = rItem.destStart + currVal - rItem.sourceStart;
            break;
        }
    }

    for ( RangeItem rItem: alm.lightToTemp ) {
        if ( rItem.sourceStart <= currVal && currVal  <= rItem.sourceStart + rItem.rangeLen - 1 ) {
            currVal = rItem.destStart + currVal - rItem.sourceStart;
            break;
        }
    }

    for ( RangeItem rItem: alm.tempToHumid ) {
        if ( rItem.sourceStart <= currVal && currVal <= rItem.sourceStart + rItem.rangeLen - 1 ) {
            currVal = rItem.destStart + currVal - rItem.sourceStart;
            break;
        }
    }

    for ( RangeItem rItem: alm.humidToLocation ) {
        if ( rItem.sourceStart <= currVal && currVal <= rItem.sourceStart + rItem.rangeLen - 1 ) {
            currVal = rItem.destStart + currVal - rItem.sourceStart;
            break;
        }
    }

    return currVal;

}

long part1( vector<long>& seeds ) {


    long ans = seeds[0];

    for ( long seed: seeds ) {
        long location = getLocation(seed);

        ans = location < ans ?  location : ans;
    }

    return ans;
}

long part2( vector<long>& seeds ) {


    long ans = seeds[0];
    for ( long i = 0; i < seeds.size(); i+=2  ) {
        
        long seedVal = seeds[i];
        long seedRange = seeds[i+1];
        for ( int val = 0; val < seedRange; val++ ) {
            long location = getLocation(seedVal++);

            ans = location < ans ?  location : ans;
        }
        cout << i + 1 << endl;
    }

    return ans;
}


vector<long> seedsParser( vector<string> stringNums ) {


    vector<long> res;
    for ( string seedString : stringNums ) {
        // cout << seedString << " " << stol(seedString) << endl;
        long seedVal = stol( seedString );
        res.push_back( seedVal );
    } 
    return res;
}



int main(){


    fstream qf;
    qf.open("allInput");

    string currLine = "";
    vector<long> seeds;

    long init = true;
    while ( getline(qf, currLine)) {
        if ( init == true ) {
            init = false;
            vector<string> splByCol = splitString( ':', currLine );
            vector<string> stringNums = splitString(' ', splByCol[1]);

            seeds = seedsParser( stringNums );
        }

        if ( currLine == "" ) {
            continue;
        }

        if ( currLine == "seed-to-soil map:" ) {
            
            while (getline(qf, currLine)) {

                if ( currLine == "" ) {
                    break;
                }

                vector<string> stringNums = splitString(' ', currLine);
                RangeItem currRange;
                currRange.destStart = stol(stringNums[0]);
                currRange.sourceStart = stol(stringNums[1]);
                currRange.rangeLen = stol(stringNums[2]);
                alm.seedToSoil.push_back(currRange);

                currLine = "";
            }
        }
        if ( currLine == "soil-to-fertilizer map:" ) {
            
            while (getline(qf, currLine)) {

                if ( currLine == "" ) {
                    break;
                }

                vector<string> stringNums = splitString(' ', currLine);
                RangeItem currRange;
                currRange.destStart = stol(stringNums[0]);
                currRange.sourceStart = stol(stringNums[1]);
                currRange.rangeLen = stol(stringNums[2]);
                alm.soilToFert.push_back(currRange);

                currLine = "";
            }
        }
        if ( currLine == "fertilizer-to-water map:" ) {
            
            while (getline(qf, currLine)) {

                if ( currLine == "" ) {
                    break;
                }

                vector<string> stringNums = splitString(' ', currLine);
                RangeItem currRange;
                currRange.destStart = stol(stringNums[0]);
                currRange.sourceStart = stol(stringNums[1]);
                currRange.rangeLen = stol(stringNums[2]);
                alm.fertToWater.push_back(currRange);

                currLine = "";
            }
        }
        if ( currLine == "water-to-light map:" ) {
            
            while (getline(qf, currLine)) {

                if ( currLine == "" ) {
                    break;
                }

                vector<string> stringNums = splitString(' ', currLine);
                RangeItem currRange;
                currRange.destStart = stol(stringNums[0]);
                currRange.sourceStart = stol(stringNums[1]);
                currRange.rangeLen = stol(stringNums[2]);
                alm.waterToLight.push_back(currRange);

                currLine = "";
            }
        }
        if ( currLine == "light-to-temperature map:" ) {
            
            while (getline(qf, currLine)) {

                if ( currLine == "" ) {
                    break;
                }

                vector<string> stringNums = splitString(' ', currLine);
                RangeItem currRange;
                currRange.destStart = stol(stringNums[0]);
                currRange.sourceStart = stol(stringNums[1]);
                currRange.rangeLen = stol(stringNums[2]);
                alm.lightToTemp.push_back(currRange);

                currLine = "";
            }
        }
        if ( currLine == "temperature-to-humidity map:" ) {
            
            while (getline(qf, currLine)) {

                if ( currLine == "" ) {
                    break;
                }

                vector<string> stringNums = splitString(' ', currLine);
                RangeItem currRange;
                currRange.destStart = stol(stringNums[0]);
                currRange.sourceStart = stol(stringNums[1]);
                currRange.rangeLen = stol(stringNums[2]);
                alm.tempToHumid.push_back(currRange);

                currLine = "";
            }
        }
        if ( currLine == "humidity-to-location map:" ) {
            
            while (getline(qf, currLine)) {

                if ( currLine == "" ) {
                    break;
                }

                vector<string> stringNums = splitString(' ', currLine);
                RangeItem currRange;
                currRange.destStart = stol(stringNums[0]);
                currRange.sourceStart = stol(stringNums[1]);
                currRange.rangeLen = stol(stringNums[2]);
                alm.humidToLocation.push_back(currRange);

                currLine = "";
            }
        }
    }


    // printAlm();
    
    cout << part2(seeds) << endl;

    return 0;
}

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;


unordered_map<char, int> dic;
unordered_map<char, int> jk;
struct CamelCard {
    string hands;
    int bid;
};

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

int sayType( string hands, bool isPart2 ) {
    
    int res = 0;
    unordered_map<char, int> charCount;

    for ( char c: hands ) {
        charCount[c]++;
    }


    vector<pair<int, char>> charPairs;

    for ( pair<char, int> p: charCount ) {
        charPairs.push_back(pair<int, char>( { p.second, p.first } ));
    }


    sort( charPairs.begin(), charPairs.end() );

    int pairsSize;

    if ( isPart2 && charCount['J'] > 0 && charCount['J'] != 5 ) {


        int idx = 0;
        for ( int i = 0; i < charPairs.size(); i++ ) {
            if ( charPairs[i].second == 'J' ) {
                idx = i;
                break;
            }
        }

        charPairs.erase(charPairs.begin()+idx);

        charPairs[charPairs.size()-1].first+= charCount['J'];

    } 
    pairsSize = charPairs.size();



    switch( pairsSize ) {
        case 1:
            // cout << hands << " " << 7 << endl;
            return 7;
        case 2:
            if ( charPairs[0].first == 1 ) {
                // cout << hands << " " << 5 << endl;
                return 6;
            } else {
                // cout << hands << " " << 6 << endl;
                return 5;
            }
        case 3:
            if ( charPairs[1].first == 1 ) {
                // cout << hands << " " << 4 << endl;
                return 4;
            } else {
                // cout << hands << " " << 3 << endl;
                return 3;
            }
        case 4:
            // cout << hands << " " << 2 << endl;
            return 2;
        default:
            // cout << hands << " " << 1 << endl;
            return 1;
    }

}


bool cmp( string a, string b, unordered_map<char, int> ref ) {


    for ( int i = 0; i < 5; i++ ) {

        if ( ref[a[i]] < ref[b[i]] ) {
            return true;
        } else if ( ref[a[i]] > ref[b[i]] ) {
            return false;
        }
    }

    return true;

}




int part1( vector<CamelCard>& qSet ) {

    int ans = 0;

    vector<vector<CamelCard>> ref( 7, vector<CamelCard>());

    for ( CamelCard q: qSet ) {
        
        int currType = sayType(q.hands, false);
        ref[currType-1].push_back(q);
    }


    for ( int i = 0; i < 7; i++ ) {

        if ( ref[i].size() <= 1 ) continue;

        for ( int o = 0; o < ref[i].size(); o++ ) {
            for ( int j = o+1; j < ref[i].size(); j++ ) {
                if ( !cmp(ref[i][o].hands, ref[i][j].hands, dic ) ) {
                    CamelCard temp  = ref[i][j];
                    ref[i][j] = ref[i][o];
                    ref[i][o] = temp;
                }
            }
        }

    }


    int rank = 1;
    for ( vector<CamelCard> cats: ref ) {

        for ( CamelCard cc: cats ) {
            ans += ( rank++ * cc.bid );
        }
    }

    return ans;
}

int part2 ( vector<CamelCard>& qSet ) {

    int ans = 0;

    vector<vector<CamelCard>> ref( 7, vector<CamelCard>());

    for ( CamelCard q: qSet ) {
        
        int currType = sayType(q.hands, true);
        ref[currType-1].push_back(q);
    }


    for ( int i = 0; i < 7; i++ ) {

        if ( ref[i].size() <= 1 ) continue;

        for ( int o = 0; o < ref[i].size(); o++ ) {
            for ( int j = o+1; j < ref[i].size(); j++ ) {
                if ( !cmp(ref[i][o].hands, ref[i][j].hands, jk ) ) {
                    CamelCard temp  = ref[i][j];
                    ref[i][j] = ref[i][o];
                    ref[i][o] = temp;
                }
            }
        }

    }


    int rank = 1;
    for ( vector<CamelCard> cats: ref ) {

        for ( CamelCard cc: cats ) {
            ans += ( rank++ * cc.bid );
        }
    }

    return ans;

}


int main() {


    fstream qf;
    qf.open("allInput");

    string currLine = "";
    vector<CamelCard> qSet;

    while ( getline( qf, currLine ) ) {
        
        vector<string> splitBySpace = splitString(' ', currLine);

        CamelCard newCard;
        newCard.hands = splitBySpace[0];
        newCard.bid = stoi( splitBySpace[1] );

        qSet.push_back( newCard );

    }

    string allCards = "23456789TJQKA";
    string jkCards = "J23456789TQKA";

    for ( int i = 0; i < allCards.size(); i++ ) {

        dic[allCards[i]] = i;
        jk[jkCards[i]] = i;
    }


    cout << part1( qSet ) << endl;
    cout << part2( qSet ) << endl;



    return 0;
}

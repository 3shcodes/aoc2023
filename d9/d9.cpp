#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

typedef long long ll;
using namespace std;

string trimString( string q ) {


    string res = "";
    long st = 0;
    long en = q.size() - 1;
    while ( q[st] == ' ' ) st++;
    while ( q[en] == ' ' ) en--;

    for ( long i = st; i <= en; i++ )  res+=q[i];

    return res;
}
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

    res.push_back( trimString(currString) );

    return res;
}

vector<ll> splitToNums( char c, string ques ) {


    vector<ll> res;
    string currString = "";

    for ( char cInd : ques ) {
        if ( cInd == c ) {
            if ( currString != "" ) {
                res.push_back( stoll(trimString(currString)) );
                currString = "";
            }
        } else {
            currString += cInd;
        }
    }

    res.push_back( stoll(trimString(currString)) );

    return res;
}

ll nextNum( vector<ll> qSet ) {

    bool isFinal = true;
    int N = qSet.size();
    ll lastDif = qSet[1] - qSet[0];
    vector<ll> nextSet;

    for ( int i = 0; i < N - 1; i++ ) {

        ll currDif = qSet[i+1] - qSet[i];
        nextSet.push_back(currDif);
        if ( isFinal == true && currDif != lastDif ) {
            isFinal = false;
        }
    }

    if ( isFinal ) {
        return qSet[N-1] + lastDif;
    } else {
        return qSet[N-1] + nextNum(nextSet);
    }

}

ll prevNum( vector<ll> qSet ) {

    bool isFinal = true;
    int N = qSet.size();
    ll lastDif = qSet[1] - qSet[0];
    vector<ll> nextSet;

    for ( int i = 0; i < N - 1; i++ ) {

        ll currDif = qSet[i+1] - qSet[i];
        nextSet.push_back(currDif);
        if ( isFinal == true && currDif != lastDif ) {
            isFinal = false;
        }
    }

    if ( isFinal ) {
        return qSet[0] - lastDif;
    } else {
        return qSet[0] - prevNum(nextSet);
    }

}

ll part1( vector<string> numsStrings ) {


    int ans = 0;
    int c = 0;

    for ( string st: numsStrings ) {

        vector<ll> qSet = splitToNums(' ', st );
        int nxt = nextNum(qSet);
        // cout << ++c << " " << nxt << endl;
        ans += nxt;
    }

    return ans;

}




int part2( vector<string> numsStrings ) {

    int ans = 0;
    int c = 0;

    for ( string st: numsStrings ) {

        vector<ll> qSet = splitToNums(' ', st );
        int nxt = prevNum(qSet);
        // cout << ++c << " " << nxt << endl;
        ans += nxt;
    }

    return ans;

}

int main(){


    fstream qf;
    // qf.open("sampleInput1");
    qf.open("allInput");

    string currLine = "";
    vector<string> numsStrings;


    while (getline(qf, currLine)) {

        numsStrings.push_back(currLine);
        currLine = "";
    }


    cout << part1( numsStrings ) << endl;
    cout << part2( numsStrings ) << endl;



    return 0;
}

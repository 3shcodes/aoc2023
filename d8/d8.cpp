#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

typedef long long ll;

struct Entity {

    string name;
    string left;
    string right;
};

unordered_map<string, Entity> dic;
unordered_map<string, string> startNodes;

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

    res.push_back(currString);

    return res;
}

int part1( string dirs ) {

    int ans = 0;
    string currName = "AAA";
    int ind = 0;
    int N = dirs.size();


    while ( true ) {

        char c = dirs[ ind++ % N ];

        ans += 1;

        if ( c == 'R' ) {

            if ( dic[currName].right == "ZZZ" ) {
                break;
            } 
            else currName = dic[currName].right;

        } else {

            if ( dic[currName].left == "ZZZ" ) {
                break;
            } 
            else currName = dic[currName].left;

        }

    }


    return ans;

}


int findSteps( string dirs, string currName ) {

    int ans = 0;
    int ind = 0;
    int N = dirs.size();


    while ( true ) {

        char c = dirs[ ind++ % N ];

        ans += 1;

        if ( c == 'R' ) {

            if ( dic[currName].right[2] == 'Z') {
                break;
            } 
            else currName = dic[currName].right;

        } else {

            if ( dic[currName].left[2] == 'Z' ) {
                break;
            } 
            else currName = dic[currName].left;

        }

    }


    return ans;

}

int gcd( ll a, ll b ) {

    if ( b == 0 ) return a;

    return gcd(b,  a % b );

}

ll findLCM( vector<ll> nums ) {

    
    ll ans = nums[0];
    int N = nums.size();

    for ( int i = 1; i < N; i++ ) {

        ans = ( nums[i] * ans ) / ( gcd( nums[i], ans ) ) ;
    }

    return ans;
}

ll part2( string dirs ) {


    vector<ll> nums;

    for ( pair<string, string> p: startNodes ) {

        ll newNum = findSteps( dirs, p.first );
        nums.push_back( newNum );

    }

    return findLCM( nums );

}

int main(){


    fstream qf;
    // qf.open("sampleInput3");
    qf.open("allInput");

    string currLine = "";
    getline(qf, currLine);

    string dirs = currLine;

    currLine = "";
    getline(qf, currLine);

    while (getline(qf, currLine)) {

        vector<string> splitByEq = splitString('=', currLine);
        Entity newEntity;

        newEntity.name = trimString( splitByEq[0] );
        string leftString = "";
        string rightString = "";

        string trimmedDirs = trimString(splitByEq[1]);
        for ( int i = 1; i < splitByEq[1].size()-1; i++ ) {
            
            if ( i >= 1 && i <= 3 ) leftString += trimmedDirs[i];
            if ( i >= 6 && i <= 8 ) rightString += trimmedDirs[i];
        }

        newEntity.left = leftString;
        newEntity.right = rightString;

        dic[newEntity.name] = newEntity;
        if ( newEntity.name[2] == 'A' ) startNodes[newEntity.name] = newEntity.name;

    }

    // for ( pair<string, string> p: startNodes ) {
    //     cout << p.first <<" " << p.second << endl;
    // }

    cout << part1( dirs ) << endl;
    cout << part2( dirs ) << endl;



    return 0;
}

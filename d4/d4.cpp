#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
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

string trimString( string q ) {


    string res = "";
    int st = 0;
    int en = q.size() - 1;
    while ( q[st] == ' ' ) st++;
    while ( q[en] == ' ' ) en--;

    for ( int i = st; i <= en; i++ )  res+=q[i];

    return res;
}

int part1( vector<string>& quesSet ) {
    
    int ans = 0;

    for ( string qs: quesSet ) {
        int curr = 0;
        unordered_map<int, bool> lp;

        auto splitByCol = splitString( ':', qs );
        auto winsAndAll = splitString( '|', splitByCol[1] );


        auto winNums = splitString(' ', winsAndAll[0]);
        auto allNums = splitString(' ', winsAndAll[1]);

        for ( string num: winNums ) {
            string tr = trimString(num);
            if ( tr != "" ) {
                lp[stoi(tr)] = true;
            } 
        }

        for ( string num: allNums ) {
            string tr = trimString(num);
            if ( tr != "" && lp.find(stoi(tr)) != lp.end() ) {
                
                curr = curr == 0 ? 1 : curr * 2;
            }
        }
        ans += curr;


    }

    return ans;

}

struct Card {
    int id;
    int matches = 0;
};

Card getPoints( string qs ) {

    int curr = 0;
    unordered_map<int, bool> lp;
    
    auto splitByCol = splitString( ':', qs );
    auto winsAndAll = splitString( '|', splitByCol[1] );


    auto winNums = splitString(' ', winsAndAll[0]);
    auto allNums = splitString(' ', winsAndAll[1]);

    for ( string num: winNums ) {
        string tr = trimString(num);
        if ( tr != "" ) {
            lp[stoi(tr)] = true;
        } 
    }

    for ( string num: allNums ) {
        string tr = trimString(num);
        if ( tr != "" && lp.find(stoi(tr)) != lp.end() ) {
            curr++;
        }
    }

    Card res; 
    res.id = stoi(( splitString( ' ', splitByCol[0] )[1] ));
    res.matches = curr;
    return res;
}

int part2( vector<string> quesSet ) {

    int ans = 0;
    unordered_map<int, int> lp;
    queue<int> q;

    for ( string qs: quesSet ) {
        Card currCard = getPoints(qs);
        lp[currCard.id] = currCard.matches;
        q.push(currCard.id);
    }

    while( !q.empty() ) {
        
        ans++;
        int currId = q.front();
        q.pop();
        if( lp.find(currId) == lp.end() ) {
            lp[currId] = 0;
            continue;
        }

        for ( int i = currId + 1; i <= currId + lp[currId]; i++ ) {
            q.push(i);
        }
    }

    return ans;
}

int main () {


    fstream ques;

    ques.open("allInput");
    vector<string> quesSet;

    string currLine = "";
    while ( getline( ques, currLine ) ) {
        quesSet.push_back(currLine);
        currLine = "";
    }


    // cout << part1( quesSet ) << endl;
    cout << part2( quesSet ) << endl;

    return 0;
}

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
struct Race{

    long time;
    long distance;

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

vector<long> strArrToNum( string strArr ) {

    vector<string> splitted = splitString(' ', strArr);

    vector<long> res;
    for ( string s: splitted ) {
        res.push_back(stol(s));
    }

    return res;

}


long findWays( Race raceItem ) {


    long res = 0;
    long idx = 0;

    while ( idx * ( raceItem.time - idx ) <= raceItem.distance ) {
        idx++;
    }


    return (raceItem.time + 1) - (2 * idx);

}


long part1( vector<Race>& qSet ) {

    vector<long> eachWays;
    long res = 0;

    long c = 0;
    for ( Race itRace : qSet ) {

        long noOfWays = findWays( itRace );
        if ( res == 0 ) {
            res = noOfWays;
        } else {
            res *= noOfWays == 0 ? 1 : noOfWays;
        }
        eachWays.push_back(noOfWays);
    }

    return res;

}

string spaceLess( string someString ) {

    string res = "";
    for ( char c: someString ) {
        if ( c != ' ') {
            res += c;
        }
    }

    return res;
}

long part2( string timeString, string distString ) {

    Race onlyRace;
    onlyRace.time = stol(spaceLess( timeString ));
    onlyRace.distance = stol(spaceLess( distString ));
    
    return findWays(onlyRace);
}


int main(){

    fstream qf;
    qf.open("allInput");

    vector<Race> qSet;

    string currStr = "";
    getline(qf, currStr);
    string timeString = trimString(splitString(':', currStr)[1]);
    vector<long> times = strArrToNum(timeString);

    currStr = "";
    getline(qf, currStr);
    string distString = trimString(splitString(':', currStr)[1]);
    vector<long> distances = strArrToNum(distString);
    


    for ( long i = 0; i < distances.size(); ++i ) {

        Race newRace;
        newRace.time = times[i];
        newRace.distance = distances[i];

        qSet.push_back(newRace);

    }




    cout << part1( qSet ) << endl;
    cout << part2( timeString, distString );


    return 0;
}

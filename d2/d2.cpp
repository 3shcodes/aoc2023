#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;


unordered_map<string, int> dic;
struct Details {
    int blue;
    int red;
    int green;
};

struct Game {
    int ID;
    vector<Details> gameDets;
};

vector<string> splitString( char c, string ques ) {
    

    vector<string> res;
    string currString = "";

    for ( char cInd : ques ) {
        if ( cInd == c ) {
            res.push_back(currString);
            currString = "";
        } else {
            currString += cInd;
        }
    }

    res.push_back(currString);

    return res;
}

vector<Details> makeDetails( string detsString ) {

    vector<Details> res;

    vector<string> allDets = splitString(';', detsString);

    for ( string det: allDets ) {

        vector<string> currBalls = splitString(',', det);
        Details currDetail;
        currDetail.blue = 0;
        currDetail.red = 0;
        currDetail.green = 0;
        for( string indv: currBalls ) {

            vector<string> valAndBall = splitString(' ', indv);

            if ( valAndBall[2] == "blue" ) {
                currDetail.blue = stoi(valAndBall[1]);
            } else if ( valAndBall[2] == "green" ) {
                currDetail.green = stoi(valAndBall[1]);
            } else if ( valAndBall[2] == "red" ) {
                currDetail.red = stoi(valAndBall[1]);
            }

        }
        res.push_back( currDetail );
    }

    return res;

}

Game makeGame( string ques ) {
    
    vector<string> gameAndDets = splitString(':', ques);

    Game res;
    res.ID = stoi(splitString(' ', gameAndDets[0])[1] );
    res.gameDets = makeDetails(gameAndDets[1]);

    return res;

}

int isGameValid( string ques ) {
    // 12 red cubes, 13 green cubes, and 14 blue cubes?

    Game thisGame = makeGame(ques);
    int res = 0;
    for ( Details det: thisGame.gameDets ) {
        if ( det.red > 12 || det.green > 13 || det.blue > 14  ) {
            return 0;
        }
    }

    return thisGame.ID;
    
}

int powerSets( string ques ) {

    Game thisGame = makeGame(ques);

    Details minDetail;
    minDetail.red = 0;
    minDetail.green = 0;
    minDetail.blue = 0;
    for ( Details det: thisGame.gameDets ) {
        minDetail.red = minDetail.red > det.red ? minDetail.red : det.red;
        minDetail.blue = minDetail.blue > det.blue ? minDetail.blue : det.blue;
        minDetail.green = minDetail.green > det.green ? minDetail.green : det.green;
    }

    int res = ( minDetail.red > 0 ? minDetail.red : 1 ) * ( minDetail.green > 0 ? minDetail.green : 1 ) * ( minDetail.blue > 0 ? minDetail.blue : 1 );
    cout << thisGame.ID << " " << res << endl;

    return res;

}

int main() {
    
    fstream qFile;

    qFile.open("allInput");
    string currLine;
    vector<string> qSets;
    while ( getline(qFile, currLine) ) {
        qSets.push_back( currLine );
    }

    qFile.close();

    int ans = 0;

    for ( string ques: qSets ) {
        
        int validGameId = powerSets(ques);
        ans += validGameId;
    }

    cout << ans << endl;

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int dirs[8][2] = { { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 0, -1 }, { 1, -1 }, { 1, 0 }, { 1, 1 }  };

bool isNum( char c ) {
    return 48 <= c && c <= 57;
}

int checkDirs( int x, int y, int horiLen, int vertiLen, vector<string>& quesSet, vector<vector<int>>& visited ) {
    
    int res = 0;
    
    for ( int i = 0; i < 8; i++ ) {
        
        int dx = x + dirs[i][0];
        int dy = y + dirs[i][1];
        
        if ( 0 <= dx && dx < horiLen && 0 <= dy && dy < vertiLen && isNum(quesSet[dx][dy]) && visited[dx][dy] == 0 ) {
            string numString = "";
            numString += quesSet[dx][dy];

            int ey = dy - 1;

            bool isVisited = false;

            while ( ey >= 0 && quesSet[dx][ey] != '.' && isNum(quesSet[dx][ey]) ) {
                if ( visited[dx][ey] ) {
                    isVisited = true;
                    break;
                } 
                visited[dx][ey] = 1;
                numString = quesSet[dx][ey] + numString;
                ey--;
            }
            ey = dy + 1;
            while ( ey < vertiLen && quesSet[dx][ey] != '.'  && isNum(quesSet[dx][ey]) ) {
                if ( visited[dx][ey] ) {
                    isVisited = true;
                    break;
                } 
                visited[dx][ey] = 1;
                numString += quesSet[dx][ey];
                ey++;
            }

            

            if ( isVisited == true ) {
                continue;
            } else {
                res += stoi( numString );
            }
        }

    }

    return res;
}

int part1( vector<string>& quesSet, int horiLen, int vertiLen, vector<vector<int>>& visited ) {
    
    int ans = 0;
    for ( int i = 0; i < vertiLen; i++ ) {
        for ( int j = 0; j < horiLen; j++ ) {

            char c = quesSet[i][j];
            
            if ( ( 48 <= c && c <= 57 ) || c == '.' || visited[i][j] != 0 ) {
                continue;
            }
            
            ans += checkDirs( i, j, horiLen, vertiLen, quesSet, visited );
        }
    }

    return ans;
}

int checkGears( int x, int y, int horiLen, int vertiLen, vector<string>& quesSet, vector<vector<int>>& visited ) {


    vector<int> res;
    int resSum = 1;
    
    for ( int i = 0; i < 8; i++ ) {
        
        int dx = x + dirs[i][0];
        int dy = y + dirs[i][1];
        
        if ( 0 <= dx && dx < horiLen && 0 <= dy && dy < vertiLen && isNum(quesSet[dx][dy]) && visited[dx][dy] == 0 ) {
            string numString = "";
            numString += quesSet[dx][dy];

            int ey = dy - 1;

            bool isVisited = false;

            while ( ey >= 0 && quesSet[dx][ey] != '.' && isNum(quesSet[dx][ey]) ) {
                if ( visited[dx][ey] ) {
                    isVisited = true;
                    break;
                } 
                visited[dx][ey] = 1;
                numString = quesSet[dx][ey] + numString;
                ey--;
            }
            ey = dy + 1;
            while ( ey < vertiLen && quesSet[dx][ey] != '.'  && isNum(quesSet[dx][ey]) ) {
                if ( visited[dx][ey] ) {
                    isVisited = true;
                    break;
                } 
                visited[dx][ey] = 1;
                numString += quesSet[dx][ey];
                ey++;
            }

            

            if ( isVisited == true ) {
                continue;
            } else {
                int currNum = stoi( numString );
                res.push_back( currNum );
                resSum *= currNum;
            }
        }

    }

    if ( res.size() == 2 ) {
        return resSum;
    } else {
        return 0;
    }


}

int part2( vector<string>& quesSet, int horiLen, int vertiLen, vector<vector<int>>& visited ) {

    int ans = 0;

    for ( int i = 0; i < vertiLen; i++ ) {
        for ( int j = 0; j < horiLen; j++ ) {

            char c  = quesSet[i][j];
            if ( c == '*' ) {
                ans += checkGears( i, j, horiLen, vertiLen, quesSet, visited );
            }
        }
    }
    return ans;

}


int main() {

    fstream ques;
    ques.open("allInput");

    vector<string> quesSet;

    string currLine = "";
    while ( getline( ques, currLine)) {
        quesSet.push_back(currLine);
        currLine = "";
    }

    ques.close();

    int vertiLen = quesSet.size();
    int horiLen = quesSet[0].size();

    vector<vector<int>> visited( vertiLen, vector( horiLen, 0 ));

    // cout << part1( quesSet, horiLen, vertiLen, visited ) << endl;
    cout << part2( quesSet, horiLen, vertiLen, visited ) << endl;

    return 0;

}

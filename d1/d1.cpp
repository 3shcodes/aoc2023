#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;


unordered_map<string, int> dic;
string vals[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

int thisTwoDigitNumber( string someString ) {

    int firstNum = -1, secondNum = -1;
    string currString = "";
    
    for ( int i = 0; i < someString.size(); i++ ) {

        char c = someString[i];
        if ( c >= 48 && c <= 57 ) {
            currString = "";

            if ( firstNum == -1 ) {
                firstNum = (int)c - 48;
                continue;
            }

            secondNum = (int)c - 48;

            continue;
        }
        
        for ( string num: vals ) {
            int valLen = num.size();

            string currVal = "";
            for (int q = i; q < i+valLen; q++ ) {
                currVal += someString[q];
            }

            if ( dic.find(currVal) != dic.end() ) {

                if ( firstNum == -1 ) {
                    firstNum = dic[currVal];
                } else {
                    secondNum = dic[currVal];
                }
            }

        }

    }

    if ( secondNum == -1 ) {
        secondNum = firstNum;
    }


    return firstNum * 10 + secondNum;


}

int main(){


    for ( int i = 0; i < 9; i++ ) {
        dic[vals[i]] = i+1;
    }

    fstream fs;
    fs.open("allInputs");

    string currLine;
    vector<string> quesSet;

    while ( getline(fs, currLine) ) {
        quesSet.push_back( currLine );
    }

    fs.close();
    
    int ans = 0;
    for ( string someString: quesSet ) {
        ans += thisTwoDigitNumber(someString);
    }

    cout << ans;
    

    return 0;
}

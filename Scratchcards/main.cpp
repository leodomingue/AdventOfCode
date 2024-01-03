#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;



int SumFoundMatches(pair<vector<int>,vector<int>>& list){
    int matches = 0;
    vector<int> winningNumbers = list.first;
    vector<int> myNumbers = list.second;

    sort(myNumbers.begin(), myNumbers.end());

    for(int number: winningNumbers){
        if(binary_search(myNumbers.begin(), myNumbers.end(), number)){
            matches++;
        }
    }

    if (matches == 0){
        return 0;
    } else {
        return pow(2,matches-1);
    }

}


pair<vector<int>, vector<int>> separateLists(string& line) {
    vector<int> winningNumberVector;
    vector<int> myNumbersVector;

    istringstream ss(line);

    string winningNumbersStr, myNumbersStr;
    getline(ss, winningNumbersStr, '|'); // Lee los números hasta el pipe
    getline(ss, myNumbersStr); // Lee los números después del pipe

    istringstream winningNumbersStream(winningNumbersStr);
    int number;
    while (winningNumbersStream >> number) {

        winningNumberVector.push_back(number);
    }

    istringstream myNumbersStream(myNumbersStr);
    while (myNumbersStream >> number) {
        myNumbersVector.push_back(number);
    }

    return make_pair(winningNumberVector, myNumbersVector);
}


int main() {

    ifstream file("/home/leo/CLionProjects/untitled2/Scratchcards/test.txt");
    string line;

    int points = 0;

    if (file.is_open()) {
        while (getline(file, line, '\n')) {
            size_t colonPos = line.find(":");
            string trimmed_line = line.substr(colonPos + 1);
            pair<vector<int>,vector<int>> listScratchCard = separateLists(trimmed_line);
            points += SumFoundMatches(listScratchCard);
        }
    }
    file.close();


    cout<< points;
    return 0;
}
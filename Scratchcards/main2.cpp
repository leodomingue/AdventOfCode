#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

int sumAllCards(map<int,int>& diccCard, int totalCards){
    int cards = 0;
    for(auto pair: diccCard){
        if(pair.first < totalCards ){
            cards += pair.second;
        }
    }
    return cards;
}

void refillDiccCards(map<int,int>& diccCard, int matches, int actualCard){
    //Si no existe, lo creo
    for(int i = actualCard; i <= actualCard + matches; i++){
        if(diccCard.find(i)==diccCard.end()){
            diccCard[i] = 1;
        }
    }

    //SUmo las nuevas cartas
    for(int j = actualCard+1; j <= actualCard + matches; j++){
        if (j <= diccCard.size()){
            for(int z= 0; z < diccCard[actualCard]; z++){
                diccCard[j] = diccCard[j]+1;
            }
        }
    }
}


int FoundMatches(pair<vector<int>,vector<int>>& list){
    int matches = 0;
    vector<int> winningNumbers = list.first;
    vector<int> myNumbers = list.second;

    sort(myNumbers.begin(), myNumbers.end());

    for(int number: winningNumbers){
        if(binary_search(myNumbers.begin(), myNumbers.end(), number)){
            matches++;
        }
    }

    return matches;
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
    map<int, int> diccCards;


    if (file.is_open()) {

        int actualCard = 1;

        while (getline(file, line, '\n')) {

            size_t colonPos = line.find(":");
            string trimmed_line = line.substr(colonPos + 1);

            pair<vector<int>, vector<int>> listScratchCard = separateLists(trimmed_line);

            int matches = FoundMatches(listScratchCard);


            refillDiccCards(diccCards, matches, actualCard);
            actualCard++;
        }
        cout << sumAllCards(diccCards, actualCard);
    }
    file.close();





    return 0;
}
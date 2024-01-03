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

void addToVector(string& line, vector<tuple<string,int>> handsBid){
    string hand;
    int bid;
    istringstream handGame(line);

    handGame >> hand >> bid;

    handsBid.push_back(make_pair(hand,bid));
}

int main() {
    ifstream file("/home/leo/CLionProjects/untitled2/Camel Cards/test.txt");
    string line;

    vector<tuple<string,int>> handsBid;

    int quantCards = 0;

    if (file.is_open()) {
        while(getline(file, line, ':')){
            addToVector(line, handsBid);
            quantCards++;
        }
    }
    file.close();

    //radix sort
    radixSort(handsBid);


    //Group for type
    map<string,vector<int>> bidGroup = {
            {"Five of a kind", vector<int>{}},
            {"Four of a kind",vector<int>{}},
            {"Full house",vector<int>{}},
            {"Three of a kind",vector<int>{}},
            {"Two pair",vector<int>{}},
            {"One pair",vector<int>{}},
            {"High card",vector<int>{}}
    };

    groupingBids(handsBid, bidGroup);


    //multiply
    int totalWinnings = 0;


    cout << totalWinnings;
    return 0;
}
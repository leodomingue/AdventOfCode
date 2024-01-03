#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;


//Time is hiher y lower
int findMinimumMoreThan(long long int lower, long long int higher, long long int distance, long long int time){
    if(lower+1 == higher){
        return (time - higher)-higher+1;
    }
    int mid = (lower + higher) / 2;

    if((time-mid) * mid > distance){
        findMinimumMoreThan(lower, mid, distance,time);
    } else{
        return findMinimumMoreThan(mid, higher, distance, time);
    }
}

vector<long long int> getTime(string& line){
    vector<int> vectorTime;
    istringstream TimeString(line);
    int time;

    while (TimeString >> time) {
        vectorTime.push_back(time);
        TimeString >> std::ws;
    }

    stringstream concatenated;
    for (int num : vectorTime) {
        concatenated << num;
    }

    string result_str = concatenated.str();
    long long int result_int = stoll(result_str);

    vector<long long int> TIME;
    TIME.push_back(result_int);



    return TIME;
}

vector<long long int> getDistance(string& line){
    vector<int> vectorDistance;
    istringstream DistanceString(line);
    int distance;

    while( DistanceString >> distance){
        vectorDistance.push_back(distance);
    }

    stringstream concatenated;
    for (int num : vectorDistance) {
        concatenated << num;
    }

    string result_str = concatenated.str();
    long long int result_int = stoll(result_str);

    vector<long long int> Distance;
    Distance.push_back(result_int);



    return Distance;
}


void timedistanceUnion(vector<long long int>& times, vector<long long int> distances, vector<vector<long long int>>& vectorunion){
    vectorunion.resize(2, vector<long long int>(distances.size()));
        vectorunion[0] = times;
        vectorunion[1] = distances;
}

int main() {
    ifstream file("/home/leo/CLionProjects/untitled2/Wait For It/input.txt.txt");
    string line;

    vector<vector<long long int>> listRecord;


    if (file.is_open()) {
        getline(file, line, ':');
        getline(file, line, '\n');
        vector<long long int> listTime = getTime(line);

        getline(file, line, ':');
        getline(file, line, '\n');
        vector<long long int> listDistance = getDistance(line);

        timedistanceUnion(listTime, listDistance, listRecord);
    }
    file.close();

    int multiply = 1;

    for(int i = 0; i < listRecord[0].size(); i++){
        int asd= listRecord.size();
        int num = findMinimumMoreThan(0, listRecord[0][i] ,listRecord[1][i], listRecord[0][i]);
        multiply *= num;

    }

    cout << multiply;

    return 0;
}
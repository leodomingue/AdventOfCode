#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

tuple<long long int,long long int,long long int> createTuple(string& line){
    istringstream infoLine(line);

    long long int destination, source, range;

    infoLine >> destination >> source >> range;

    return tuple<long long int,long long int,long long int>(destination, source, range);
}


void findMapped(long long int info, vector<vector<tuple<long long int,long long int,long long int>>>& maps, int actualMap,  vector<long long int>& localizationSeeds){
    if (actualMap == maps.size()){
        localizationSeeds.push_back(info);
        return; // Termina la recursión cuando alcanzamos el final de los mapas
    }

    bool in_range = false;
    for(int i = 0; i < maps[actualMap].size(); i++){
        if(info >= get<1>(maps[actualMap][i]) &&  info < get<1>(maps[actualMap][i]) + get<2>(maps[actualMap][i]) ){
            in_range = true;
            long long int new_info = get<0>(maps[actualMap][i]) + abs(info -  get<1>(maps[actualMap][i]));
            findMapped(new_info, maps, actualMap + 1, localizationSeeds);
            // No es necesario seguir buscando si ya encontramos un mapeo en este nivel
            return; //IMPORTANTE, PORQUE SINO ME VA AL IF
        }
    }
    if (!in_range){
        // Si no encontramos un mapeo en este nivel, pasamos al siguiente nivel
        findMapped(info, maps, actualMap + 1, localizationSeeds);
    }
}



void obtainSeeds(string& line, vector<long long int>& vector){
    size_t colonPos = line.find(':');
    string trimmed_line = line.substr(colonPos + 1);

    istringstream seedsString(trimmed_line);
    long long int seedID;

    while (seedsString >> seedID){
        vector.push_back(seedID);
    }
}


int main() {
    ifstream file("/home/leo/CLionProjects/untitled2/If You Give A Seed A Fertilizer/input.txt.txt");
    string line;

    vector<long long int> seeds;

    vector<vector<tuple<long long int,long long int,long long int>>> maps;
    int actualMap = 0;


    if (file.is_open()) {
        getline(file, line, '\n');
        obtainSeeds(line, seeds);

        while (getline(file, line, '\n')) {
            if(line.find("map") != string::npos){
                maps.push_back(vector<tuple<long long int,long long int,long long int>>());
                bool in_map = true;
                while(in_map && getline(file, line, '\n')){
                    if (line.empty()){
                        in_map = false;
                    } else {
                        tuple<long long int,long long int,long long int>tuple_info = createTuple(line);
                        maps[actualMap].push_back(tuple_info);
                    }
                }
                actualMap++;
            }

        }
        

    }
    file.close();

    vector<long long int> localizationSeeds;


    for(auto seed: seeds){
        actualMap = 0;
        findMapped(seed, maps, actualMap, localizationSeeds);
    }

    cout << *min_element(localizationSeeds.begin(),localizationSeeds.end());


    return 0;
}
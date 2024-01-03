#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <sstream>

using namespace std;

/*Divido por salto de linea, divido por , y divivod por ;*/
bool isValidCube(string& cube, map<string,int>& dicc_cubes){
    istringstream iss(cube);

    int cant;
    string color;

    iss >> cant >> color;


    return dicc_cubes[color] >= cant;
}

int minimumCube(string& line){
    int minimult = 1;
    map<string, int> dicc_cubes_minimum = {
            { "red", 0 },
            { "green", 0 },
            { "blue", 0 },
            };

    istringstream ss(line);
    string set;
    string cube;
    while (getline(ss, set, ';')){
        istringstream ss(set);
        while(getline(ss, cube, ',')){
            istringstream iss(cube);


            int cant;
            string color;

            iss >> cant >> color;

            if(dicc_cubes_minimum[color]< cant){
                dicc_cubes_minimum[color] = cant;

            }
        }
    }
    for(const auto& pair: dicc_cubes_minimum){
        minimult *= pair.second;
    }

    return minimult;
};


bool isValidSet(string& set, map<string,int>& dicc_cubes){
    istringstream ss(set);
    string cube;
    bool valid_set = true;

    while(getline(ss, cube, ',')){
        if (!isValidCube(cube, dicc_cubes)){
            valid_set = false;
        }
    }
    return valid_set;
}

bool ValidationGame(string& line, map<string,int>& dicc_cubes){
    istringstream ss(line);
    string set;
    bool valid_game = true;
    while (getline(ss, set, ';')) {
        if(!isValidSet(set, dicc_cubes)){
            valid_game = false;
        }
    }
    return valid_game;
}



int main() {
    int sumIdGame = 0;
    int miniMultSum = 0;

    map<string,int> dicc_cubes = {
            {"red",12},
            {"green",13},
            {"blue",14},
    };


    ifstream file("/home/leo/CLionProjects/untitled2/Cube Conundrum/input.txt.txt");
    string line;

    if (file.is_open()){
        while(getline(file, line)){
            size_t colonPos = line.find(":");
            int ID_Game = stoi(line.substr(5, colonPos));
            string trimmed_line = line.substr(colonPos+1);
            if(ValidationGame(trimmed_line, dicc_cubes)){
                sumIdGame += ID_Game;
            }
            miniMultSum += minimumCube(trimmed_line);
        }
    }
    file.close();

    cout<< sumIdGame;
    cout<< " ";
    cout<<miniMultSum;

    return 0;
}
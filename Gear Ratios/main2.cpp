//
// Created by leo on 12/12/23.
//
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <utility>

//Me fijo numero por numero en el texto y me fijo si tiene signo de multiplicar,
//SI lo tiene me guardo la posicion del mismo en un set/conjunto
//Luego a cada conjunto lo añado a un dioccionio, un una clave contiene 2 numeros los debo de multiplicar

using namespace std;

bool isNumber(char c){
    return c >= '0' && c <= '9';
}

void addPossibleGear(set<pair<int,int>>& positionGear, int number, map<tuple<int,int>, vector<int>>& diccPostionsGear){
    //Debo fijarme si existe, si no existe lo creo
    //Si existe entonces agrego
    for(auto position: positionGear){
        if(diccPostionsGear.find(position)==diccPostionsGear.end()){
            diccPostionsGear[position] = vector<int>{number};
        } else {
            diccPostionsGear[position].push_back(number);
        }
    }
}

int multiplyGearValue(map<tuple<int,int>, vector<int>>& diccPostionsGear){
    int sumMultiply = 0;
    for(auto pair: diccPostionsGear){
        if(pair.second.size() == 2){
            sumMultiply += pair.second[0] * pair.second[1];
        }
    }
    return sumMultiply;
}

void symbolVerify(vector<vector<char>>& text, map<tuple<int,int>, vector<int>>& possibleGearNumbers){
    vector<int> numbersFound;

    int rows = text.size();
    int columns = text[0].size();

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            if(isNumber(text[i][j])){
                set<pair<int,int>> postionGear;
                vector<int> positions;
                positions.push_back(j);

                //Me fijo si los que siguen son numeros y guardo su posicion y el numero formado
                string number(1, text[i][j]);
                for(j=j+1; isNumber(text[i][j]) && j != columns; j++){
                    number += text[i][j];
                    positions.push_back(j);
                }


                //Ya tengo el numero formado y sus posiciones
                for (int z = 0; z < positions.size(); z++){

                    for(int x = -1; x <= 1; x++){
                        for(int y = -1; y <= 1; y++){
                            if (i + x >= 0 && i + x < rows && positions[z] + y >= 0 && positions[z] + y < columns){

                                if(text[i + x][positions[z] + y] == '*'){
                                    postionGear.insert(make_pair(i+x,positions[z] + y));
                                }
                            }


                        }
                    }

                }
                addPossibleGear(postionGear, stoi(number), possibleGearNumbers);
            }
        }
    }
}


int sumVector(vector<int>& vector){
    int sum = 0;
    for(int number: vector){
        cout<<number;
        cout<<endl;
        sum += number;
    }
    return sum;
}

vector<char> passToMatrix(string& line, vector<vector<char>>& matrix){
    vector<char> charVector;
    for(char character: line){
        charVector.push_back(character);
    }
    return charVector;
}


int main() {

    ifstream file("/home/leo/CLionProjects/untitled2/Gear Ratios/input.txt.txt");
    string line;

    vector<vector<char>> matrixChar;

    map<tuple<int,int>, vector<int>>possibleGearNumbers;


    if (file.is_open()) {
        while (getline(file, line)) {
            vector<char> charVector = passToMatrix(line, matrixChar);
            matrixChar.push_back(charVector);
        }
    }
    file.close();

    symbolVerify(matrixChar, possibleGearNumbers);


    cout<< multiplyGearValue(possibleGearNumbers);
    return 0;
}
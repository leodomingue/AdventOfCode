//
// Created by leo on 12/12/23.
//
#include <iostream>
#include <string>
#include <fstream>
#include <vector>


using namespace std;

bool isNumber(char c){
    return c >= '0' && c <= '9';
}

vector<int> symbolVerify(vector<vector<char>>& text){
    vector<int> numbersFound;

    int rows = text.size();
    int columns = text[0].size();

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            if(isNumber(text[i][j])){
                vector<int> positions;
                positions.push_back(j);

                //Me fijo si los que siguen son numeros y guardo su posicion y el numero formado
                string number(1, text[i][j]);
                for(j=j+1; isNumber(text[i][j]) && j != columns; j++){
                    number += text[i][j];
                    positions.push_back(j);
                }

                bool isValue = false;

                //Ya tengo el numero formado y sus posiciones
                for (int z = 0; z < positions.size(); z++){

                    for(int x = -1; x <= 1; x++){
                        for(int y = -1; y <= 1; y++){
                            if (i + x >= 0 && i + x < rows && positions[z] + y >= 0 && positions[z] + y < columns){

                                if(!isNumber(text[i + x][positions[z] + y]) && (text[i + x][positions[z] + y]) != '.'){
                                    isValue = true;
                                }
                            }


                        }
                    }

                }

                if(isValue){
                    int missingNumber = stoi(number);
                    numbersFound.push_back(missingNumber);
                }



            }
        }
    }
    return numbersFound;
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


    if (file.is_open()) {
        while (getline(file, line)) {
            vector<char> charVector = passToMatrix(line, matrixChar);
            matrixChar.push_back(charVector);
        }
    }
    file.close();

    vector<int> numbersInText = symbolVerify(matrixChar);

    cout<< sumVector(numbersInText);
    return 0;
}
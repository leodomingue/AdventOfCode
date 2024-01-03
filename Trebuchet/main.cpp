#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

void get_number(string& line, vector<pair<string, string>>& number_in_line, vector<string>& key_words){
    int minPos = 10000;
    int maxPos = -1;
    string first_number ="";
    string second_number = "";

    for(const string& word: key_words){
        int pos = line.find(word);

        if(pos != string::npos && pos < minPos){
            minPos = pos;
            first_number = word;
        }
    }

    for(const string& word: key_words){
        int pos = line.rfind(word);

        if(pos != string::npos && pos > maxPos){
            maxPos = pos;
            second_number = word;
        }
    }

    number_in_line.push_back({first_number, second_number});
}

int sum_numbers(vector<pair<string, string>>& numbers){
    map<string,int> dicc_numbers = {
            {"one",1},
            {"two",2},
            {"three",3},
            {"four",4},
            {"five",5},
            {"six",6},
            {"seven",7},
            {"eight",8},
            {"nine",9}
    };


    int total_sum = 0;
    for (const auto& number: numbers){
        if (number.first.length() == 1){
            total_sum += (number.first[0] - '0') * 10;
        }else{
            total_sum += dicc_numbers[number.first] * 10;
        }

        if (number.second.length() == 1){
            total_sum += (number.second[0] - '0');
        }else{
            total_sum += dicc_numbers[number.second];


        }
    }
    return total_sum;
}

int main() {
    vector<string> key_words = {"zero","one","two","three","four","five","six","seven","eight","nine","1","2","3","4","6","7","8","9","5"};
    vector<pair<string, string>> numbers_per_line;

    ifstream file("/home/leo/CLionProjects/untitled2/Trebuchet/input.txt.txt");
    string line;

    if (file.is_open()){
        while(getline(file, line)){
            get_number(line, numbers_per_line, key_words);
        }
    }
    file.close();

    int number = sum_numbers(numbers_per_line);

    cout << number;
    return 0;
}
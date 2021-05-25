#include <iostream>
#include "json.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using namespace P;


void Json::create(string filename) {
    fstream fout;
    fout.open("C:\\Users\\denis\\CLionProjects\\jsonxml17\\" + filename, ios::out | ios::app);
    this->filename = filename;
    fout.close();
}

void Json::read_keys() {
    fstream fin;
    ifstream file("C:\\Users\\denis\\CLionProjects\\jsonxml17\\" + filename, ios::in);
    for (auto &row: JsonRange(file))
        cout << row.getKey() << endl;
    fin.close();
}
void Json::read(string key) {
    fstream fin;
    ifstream file("C:\\Users\\denis\\CLionProjects\\jsonxml17\\" + filename, ios::in);
    for (auto &row: JsonRange(file)){
        if (row.getKey() == key)
            cout << row.getValue() << endl;
    }
    fin.close();
}
void Json::getPair() {
    fstream fin;
    ifstream file("C:\\Users\\denis\\CLionProjects\\jsonxml17\\" + filename, ios::in);
    for (auto &row: JsonRange(file)){
        cout << row.getKey() << " : " << row.getValue() << endl;
    }
    fin.close();
}

void Json::add(JsonPair jsonPair) {
    fstream fin;
    fstream fout;

    fin.open("C:\\Users\\denis\\CLionProjects\\jsonxml17\\" + filename, ios::in);
    fout.open("C:\\Users\\denis\\CLionProjects\\jsonxml17\\add_" + filename, ofstream::out);

    string line;
    while (getline(fin, line)) {
        if (line.find('}') != std::string::npos){
            fout << line.substr(0, line.size()-1) << "," << endl;
            fout << "  \"" << jsonPair.getKey() << "\" : \"" << jsonPair.getValue() << "\"}" << endl;
        } else{
            fout << line << endl;
        }
    }
    fout.close();
    fin.close();
}


void Json::update(JsonPair jsonPair) {
    fstream fin;
    fstream fout;

    fin.open("C:\\Users\\denis\\CLionProjects\\jsonxml17\\" + filename, ios::in);
    fout.open("C:\\Users\\denis\\CLionProjects\\jsonxml17\\update_" + filename, ofstream::out);

    string line;
    while (getline(fin, line)) {
        if (line.find(jsonPair.getKey()) != std::string::npos){
            fout << "  \"" << jsonPair.getKey() << "\" : \"" << jsonPair.getValue() << "\"," << endl;
        } else{
            fout << line << endl;
        }
    }
    fout.close();
    fin.close();
}

void Json::delete_key(string key) {
    fstream fin;
    fstream fout;

    fin.open("C:\\Users\\denis\\CLionProjects\\jsonxml17\\" + filename, ios::in);
    fout.open("C:\\Users\\denis\\CLionProjects\\jsonxml17\\delete_" + filename, ofstream::out);

    string line;
    while (getline(fin, line)) {
        if (line.find(key) != std::string::npos){
            if (line.find('}') != std::string::npos)
                fout << "}" << endl;
            if (line.find('{') != std::string::npos)
                fout << "{" << endl;
        } else{
            fout << line << endl;
        }
    }
    fout.close();
    fin.close();
}


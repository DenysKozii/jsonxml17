#include <iostream>
#include "xml.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using namespace P;


void Xml::create(string filename) {
    fstream fout;
    fout.open("C:\\Users\\denis\\CLionProjects\\jsonxml17\\" + filename, ios::out | ios::app);
    this->filename = filename;
    fout.close();
}

void Xml::read_keys() {
    fstream fin;
    ifstream file("C:\\Users\\denis\\CLionProjects\\jsonxml17\\" + filename, ios::in);
    for (auto &row: XmlRange(file)) {
        if (!row.getKey().empty())
            cout << row.getKey() << endl;
    }
    fin.close();
}
void Xml::read(string key) {
    fstream fin;
    ifstream file("C:\\Users\\denis\\CLionProjects\\jsonxml17\\" + filename, ios::in);
    for (auto &row: XmlRange(file)){
        if (row.getKey() == key)
            cout << row.getValue() << endl;
    }
    fin.close();
}
void Xml::getPair() {
    fstream fin;
    ifstream file("C:\\Users\\denis\\CLionProjects\\jsonxml17\\" + filename, ios::in);
    for (auto &row: XmlRange(file)){
        if (!row.getKey().empty())
        cout << row.getKey() << " : " << row.getValue() << endl;
    }
    fin.close();
}

void Xml::add(XmlPair xmlPair) {
    fstream fin;
    fstream fout;

    fin.open("C:\\Users\\denis\\CLionProjects\\jsonxml17\\" + filename, ios::in);
    fout.open("C:\\Users\\denis\\CLionProjects\\jsonxml17\\add_" + filename, ofstream::out);

    string line;
    int lineIndex = 0;
    while (getline(fin, line)) {
        if (lineIndex == 1){
            fout << "    <" << xmlPair.getKey() << ">" << xmlPair.getValue() << "</" << xmlPair.getKey() << ">"<< endl;
            fout << line << endl;
        } else{
            fout << line << endl;
        }
        lineIndex++;
    }
    fout.close();
    fin.close();
}


void Xml::update(XmlPair xmlPair) {
    fstream fin;
    fstream fout;

    fin.open("C:\\Users\\denis\\CLionProjects\\jsonxml17\\" + filename, ios::in);
    fout.open("C:\\Users\\denis\\CLionProjects\\jsonxml17\\update_" + filename, ofstream::out);

    string line;
    while (getline(fin, line)) {
        if (line.find(xmlPair.getKey()) != std::string::npos){
            fout << "    <" << xmlPair.getKey() << ">" << xmlPair.getValue() << "</" << xmlPair.getKey() << ">"<< endl;
        } else{
            fout << line << endl;
        }
    }
    fout.close();
    fin.close();
}

void Xml::delete_key(string key) {
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


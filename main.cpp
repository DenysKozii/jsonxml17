#include <iostream>
#include "json.h"
#include "xml.h"

using namespace P;

void test_json(){
    Json json;
    json.create("test.json");

    cout << "read keys" << endl;
    json.read_keys();

    cout << "read value by key" << endl;
    json.read("b");

    cout << "read all pairs" << endl;
    json.getPair();

    cout << "update pair" << endl;
    JsonPair jsonPair;
    jsonPair.setKey("b");
    jsonPair.setValue("4");
    json.update(jsonPair);

    cout << "add new pair" << endl;
    JsonPair jsonPairAdd;
    jsonPairAdd.setKey("d");
    jsonPairAdd.setValue("5");
    json.add(jsonPairAdd);

    cout << "delete by key" << endl;
    json.delete_key("b");
}

void test_xml(){
    Xml xml;
    xml.create("test.xml");

    cout << "read keys" << endl;
    xml.read_keys();

    cout << "read value by key" << endl;
    xml.read("year");

    cout << "read all pairs" << endl;
    xml.getPair();

    cout << "update pair" << endl;
    XmlPair xmlPair;
    xmlPair.setKey("price");
    xmlPair.setValue("666");
    xml.update(xmlPair);

    cout << "add new pair" << endl;
    XmlPair xmlPairAdd;
    xmlPairAdd.setKey("author");
    xmlPairAdd.setValue("Giada De Laurentiis");
    xml.add(xmlPairAdd);

    cout << "delete by key" << endl;
    xml.delete_key("title");
}

int main() {
//    test_json();
    test_xml();
    return 0;
}

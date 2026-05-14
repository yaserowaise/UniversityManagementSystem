// University Management System
// Developed by Yaser
// All rights reserved.

#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
using namespace std;

class Person {
private:
    string name;
    string id;
    int age;

public:
    Person();
    Person(string n, string i, int a);

    void setname(string n);
    void setid(string i);
    void setage(int a);

    string getname();
    string getid();
    int getage();

    virtual void displayinfo();

    bool operator==(const Person& other);
    friend ostream& operator<<(ostream& os, const Person& p);
};

#endif

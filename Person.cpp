// University Management System
// Developed by Yaser
// All rights reserved.

#include "Person.h"

Person::Person() {
    name = "";
    id = "";
    age = 0;
}

Person::Person(string n, string i, int a) {
    name = n;
    id = i;
    age = a;
}

void Person::setname(string n) {
    name = n;
}

void Person::setid(string i) {
    id = i;
}

void Person::setage(int a) {
    age = a;
}

string Person::getname() {
    return name;
}

string Person::getid() {
    return id;
}

int Person::getage() {
    return age;
}

void Person::displayinfo() {
    cout << "Name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Age: " << age << endl;
}

bool Person::operator==(const Person& other) {
    return id == other.id;
}

ostream& operator<<(ostream& os, const Person& p) {
    os << "Name: " << p.name << ", ID: " << p.id << ", Age: " << p.age;
    return os;
}

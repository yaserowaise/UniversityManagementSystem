// University Management System
// Developed by Yaser
// All rights reserved.

#include "Instructor.h"

Instructor::Instructor() : Person() {}

Instructor::Instructor(string n, string i, int a) : Person(n, i, a) {}

void Instructor::addcourse(string coursecode) {
    taughtcoursecodes.push_back(coursecode);
}

vector<string> Instructor::gettaughtcoursecodes() {
    return taughtcoursecodes;
}

void Instructor::displayinfo() {
    Person::displayinfo();
    cout << "Type: Instructor" << endl;
    cout << "Courses Teaching: " << (int)taughtcoursecodes.size() << endl;
    for (int i = 0; i < (int)taughtcoursecodes.size(); i++) {
        cout << "  - " << taughtcoursecodes[i] << endl;
    }
}

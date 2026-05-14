// University Management System
// Developed by Yaser
// All rights reserved.

#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "Person.h"
#include <vector>
using namespace std;

class Instructor : public Person {
private:
    vector<string> taughtcoursecodes;

public:
    Instructor();
    Instructor(string n, string i, int a);

    void addcourse(string coursecode);
    vector<string> gettaughtcoursecodes();

    void displayinfo();
};

#endif

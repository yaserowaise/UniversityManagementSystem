// University Management System
// Developed by Yaser
// All rights reserved.

#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <vector>
#include <map>
using namespace std;

class Student : public Person {
private:
    vector<string> enrolledcoursecodes;
    map<string, float> grades;

public:
    Student();
    Student(string n, string i, int a);

    void enrollcourse(string coursecode);
    bool isenrolledin(string coursecode);
    void setgrade(string coursecode, float grade);
    float getgrade(string coursecode);

    vector<string> getenrolledcoursecodes();
    map<string, float> getgrades();

    void displayinfo();
};

#endif

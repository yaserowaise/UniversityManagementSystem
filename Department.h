// University Management System
// Developed by Yaser
// All rights reserved.

#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Department {
private:
    string name;
    vector<string> studentids;
    vector<string> instructorids;
    vector<string> coursecodes;

public:
    Department();
    Department(string n);

    void setname(string n);
    string getname();

    void addstudent(string id);
    void addinstructor(string id);
    void addcourse(string code);

    vector<string> getstudentids();
    vector<string> getinstructorids();
    vector<string> getcoursecodes();

    void displayinfo();
    bool operator==(const Department& other);
    friend ostream& operator<<(ostream& os, const Department& d);
};

#endif

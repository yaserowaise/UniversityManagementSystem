// University Management System
// Developed by Yaser
// All rights reserved.

#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

class Course {
private:
    string coursecode;
    string coursename;
    int credits;
    string instructorid;
    vector<string> enrolledstudentids;
    map<string, float> grades;

public:
    Course();
    Course(string code, string name, int cr);

    void setcoursecode(string code);
    void setcoursename(string name);
    void setcredits(int cr);
    void setinstructorid(string id);

    string getcoursecode();
    string getcoursename();
    int getcredits();
    string getinstructorid();

    bool enrollstudent(string studentid);
    void setgrade(string studentid, float grade);
    float getgrade(string studentid);
    bool isstudentenrolled(string studentid);

    vector<string> getenrolledstudentids();
    map<string, float> getgrades();

    void displayinfo();
    bool operator==(const Course& other);
    friend ostream& operator<<(ostream& os, const Course& c);
};

#endif

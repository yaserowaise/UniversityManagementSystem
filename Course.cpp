// University Management System
// Developed by Yaser
// All rights reserved.

#include "Course.h"

Course::Course() {
    coursecode = "";
    coursename = "";
    credits = 0;
    instructorid = "";
}

Course::Course(string code, string name, int cr) {
    coursecode = code;
    coursename = name;
    credits = cr;
    instructorid = "";
}

void Course::setcoursecode(string code) {
    coursecode = code;
}

void Course::setcoursename(string name) {
    coursename = name;
}

void Course::setcredits(int cr) {
    credits = cr;
}

void Course::setinstructorid(string id) {
    instructorid = id;
}

string Course::getcoursecode() {
    return coursecode;
}

string Course::getcoursename() {
    return coursename;
}

int Course::getcredits() {
    return credits;
}

string Course::getinstructorid() {
    return instructorid;
}

bool Course::enrollstudent(string studentid) {
    if (isstudentenrolled(studentid)) {
        return false;
    }
    enrolledstudentids.push_back(studentid);
    return true;
}

void Course::setgrade(string studentid, float grade) {
    grades[studentid] = grade;
}

float Course::getgrade(string studentid) {
    for (auto it = grades.begin(); it != grades.end(); it++) {

        if (it->first == studentid) {
            return it->second;
        }

    }
    return -1;
}

bool Course::isstudentenrolled(string studentid) {
    for (int i = 0; i < (int)enrolledstudentids.size(); i++) {
        if (enrolledstudentids[i] == studentid) {
            return true;
        }
    }
    return false;
}

vector<string> Course::getenrolledstudentids() {
    return enrolledstudentids;
}

map<string, float> Course::getgrades() {
    return grades;
}

void Course::displayinfo() {
    cout << "Course Code: " << coursecode << endl;
    cout << "Course Name: " << coursename << endl;
    cout << "Credits: " << credits << endl;
    if (instructorid != "") {
        cout << "Instructor ID: " << instructorid << endl;
    } else {
        cout << "Instructor: None" << endl;
    }
    cout << "Enrolled Students: " << (int)enrolledstudentids.size() << endl;
    for (int i = 0; i < (int)enrolledstudentids.size(); i++) {
        cout << "  - " << enrolledstudentids[i];
        float g = getgrade(enrolledstudentids[i]);
        if (g >= 0) {
            cout << " Grade: " << g;
        } else {
            cout << " Grade: Not entered";
        }
        cout << endl;
    }
}

bool Course::operator==(const Course& other) {
    return coursecode == other.coursecode;
}

ostream& operator<<(ostream& os, const Course& c) {
    os << "Code: " << c.coursecode << ", Name: " << c.coursename << ", Credits: " << c.credits;
    return os;
}

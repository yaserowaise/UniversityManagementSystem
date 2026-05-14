// University Management System
// Developed by Yaser
// All rights reserved.

#include "Student.h"

Student::Student() : Person() {}

Student::Student(string n, string i, int a) : Person(n, i, a) {}

void Student::enrollcourse(string coursecode) {
    enrolledcoursecodes.push_back(coursecode);
}

bool Student::isenrolledin(string coursecode) {
    for (int i = 0; i < (int)enrolledcoursecodes.size(); i++) {
        if (enrolledcoursecodes[i] == coursecode) {
            return true;
        }
    }
    return false;
}

void Student::setgrade(string coursecode, float grade) {
    grades[coursecode] = grade;
}

float Student::getgrade(string coursecode) {
    for (map<string, float>::iterator it = grades.begin(); it != grades.end(); it++) {
        if (it->first == coursecode) {
            return it->second;
        }
    }
    return -1;
}

vector<string> Student::getenrolledcoursecodes() {
    return enrolledcoursecodes;
}

map<string, float> Student::getgrades() {
    return grades;
}

void Student::displayinfo() {
    Person::displayinfo();
    cout << "Type: Student" << endl;
    cout << "Enrolled Courses: " << (int)enrolledcoursecodes.size() << endl;
    for (int i = 0; i < (int)enrolledcoursecodes.size(); i++) {
        cout << "  - " << enrolledcoursecodes[i];
        float g = getgrade(enrolledcoursecodes[i]);
        if (g >= 0) {
            cout << " Grade: " << g;
        } else {
            cout << " Grade: Not entered";
        }
        cout << endl;
    }
}

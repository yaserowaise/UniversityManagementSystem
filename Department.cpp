// University Management System
// Developed by Yaser
// All rights reserved.

#include "Department.h"

Department::Department() {
    name = "";
}

Department::Department(string n) {
    name = n;
}

void Department::setname(string n) {
    name = n;
}

string Department::getname() {
    return name;
}

void Department::addstudent(string id) {
    studentids.push_back(id);
}

void Department::addinstructor(string id) {
    instructorids.push_back(id);
}

void Department::addcourse(string code) {
    coursecodes.push_back(code);
}

vector<string> Department::getstudentids() {
    return studentids;
}

vector<string> Department::getinstructorids() {
    return instructorids;
}

vector<string> Department::getcoursecodes() {
    return coursecodes;
}

void Department::displayinfo() {
    cout << "Department: " << name << endl;
    cout << "  Students: " << (int)studentids.size() << endl;
    cout << "  Instructors: " << (int)instructorids.size() << endl;
    cout << "  Courses: " << (int)coursecodes.size() << endl;
}

bool Department::operator==(const Department& other) {
    return name == other.name;
}

ostream& operator<<(ostream& os, const Department& d) {
    os << d.name;
    return os;
}

// University Management System
// Developed by Yaser
// All rights reserved.

#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include "Department.h"
#include "Student.h"
#include "Instructor.h"
#include "Course.h"
#include "Version.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class University {
private:
    vector<Department> departments;
    vector<Student> allstudents;
    vector<Instructor> allinstructors;
    vector<Course> allcourses;

    Department* finddepartment(string name);
    Student* findstudentbyid(string id);
    Instructor* findinstructorbyid(string id);
    Course* findcoursebycode(string code);

    float calcgpa(string studentid);

public:
    University();

    bool adddepartment(string name);
    bool addstudent(string name, string id, int age, string deptname);
    bool addinstructor(string name, string id, int age, string deptname);
    bool addcourse(string code, string name, int credits, string instructorid, string deptname);
    bool enrollstudent(string studentid, string coursecode);
    bool entergrade(string studentid, string coursecode, float grade);

    void displayallstudents();
    void displayallcourses();
    void displayalldepartments();
    void displayabout();

    void savedata();
    void loaddata();

    void showmenu();
    void run();
};

#endif

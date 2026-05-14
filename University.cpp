// University Management System
// Developed by Yaser
// All rights reserved.

#include "University.h"
#include <sstream>
#include <cstdlib>

University::University() {
    loaddata();
}

Department* University::finddepartment(string name) {
    for (int i = 0; i < (int)departments.size(); i++) {
        if (departments[i].getname() == name) {
            return &departments[i];
        }
    }
    return nullptr;
}

Student* University::findstudentbyid(string id) {
    for (int i = 0; i < (int)allstudents.size(); i++) {
        if (allstudents[i].getid() == id) {
            return &allstudents[i];
        }
    }
    return nullptr;
}

Instructor* University::findinstructorbyid(string id) {
    for (int i = 0; i < (int)allinstructors.size(); i++) {
        if (allinstructors[i].getid() == id) {
            return &allinstructors[i];
        }
    }
    return nullptr;
}

Course* University::findcoursebycode(string code) {
    for (int i = 0; i < (int)allcourses.size(); i++) {
        if (allcourses[i].getcoursecode() == code) {
            return &allcourses[i];
        }
    }
    return nullptr;
}

float University::calcgpa(string studentid) {
    for (int i = 0; i < (int)allstudents.size(); i++) {
        if (allstudents[i].getid() == studentid) {
            vector<string> codes = allstudents[i].getenrolledcoursecodes();
            if (codes.size() == 0) return 0;

            float totalpoints = 0;
            int totalcredits = 0;

            for (int j = 0; j < (int)codes.size(); j++) {
                Course* c = findcoursebycode(codes[j]);
                if (c == nullptr) continue;

                float grade = allstudents[i].getgrade(codes[j]);
                if (grade < 0) continue;

                float gpapoint;
                if (grade >= 90) gpapoint = 4.0;
                else if (grade >= 80) gpapoint = 3.0;
                else if (grade >= 70) gpapoint = 2.0;
                else if (grade >= 60) gpapoint = 1.0;
                else gpapoint = 0.0;

                totalpoints = totalpoints + gpapoint * c->getcredits();
                totalcredits = totalcredits + c->getcredits();
            }

            if (totalcredits == 0) return 0;
            return totalpoints / totalcredits;
        }
    }
    return 0;
}

bool University::adddepartment(string name) {
    if (finddepartment(name) != nullptr) {
        cout << "Department already exists!" << endl;
        return false;
    }
    Department d(name);
    departments.push_back(d);
    return true;
}

bool University::addstudent(string name, string id, int age, string deptname) {
    if (findstudentbyid(id) != nullptr) {
        cout << "Error: Student ID already exists!" << endl;
        return false;
    }
    Department* d = finddepartment(deptname);
    if (d == nullptr) {
        cout << "Error: Department not found!" << endl;
        return false;
    }
    Student s(name, id, age);
    allstudents.push_back(s);
    d->addstudent(id);
    return true;
}

bool University::addinstructor(string name, string id, int age, string deptname) {
    if (findinstructorbyid(id) != nullptr) {
        cout << "Error: Instructor ID already exists!" << endl;
        return false;
    }
    Department* d = finddepartment(deptname);
    if (d == nullptr) {
        cout << "Error: Department not found!" << endl;
        return false;
    }
    Instructor ins(name, id, age);
    allinstructors.push_back(ins);
    d->addinstructor(id);
    return true;
}

bool University::addcourse(string code, string name, int credits, string instructorid, string deptname) {
    if (findcoursebycode(code) != nullptr) {
        cout << "Error: Course code already exists!" << endl;
        return false;
    }
    Department* d = finddepartment(deptname);
    if (d == nullptr) {
        cout << "Error: Department not found!" << endl;
        return false;
    }
    Instructor* ins = findinstructorbyid(instructorid);
    if (ins == nullptr) {
        cout << "Error: Instructor not found!" << endl;
        return false;
    }

    Course c(code, name, credits);
    c.setinstructorid(instructorid);
    ins->addcourse(code);
    allcourses.push_back(c);
    d->addcourse(code);
    return true;
}

bool University::enrollstudent(string studentid, string coursecode) {
    Student* s = findstudentbyid(studentid);
    if (s == nullptr) {
        cout << "Error: Student not found!" << endl;
        return false;
    }
    Course* c = findcoursebycode(coursecode);
    if (c == nullptr) {
        cout << "Error: Course not found!" << endl;
        return false;
    }
    if (s->isenrolledin(coursecode)) {
        cout << "Error: Student is already enrolled in this course!" << endl;
        return false;
    }
    c->enrollstudent(studentid);
    s->enrollcourse(coursecode);
    return true;
}

bool University::entergrade(string studentid, string coursecode, float grade) {
    Student* s = findstudentbyid(studentid);
    if (s == nullptr) {
        cout << "Error: Student not found!" << endl;
        return false;
    }
    Course* c = findcoursebycode(coursecode);
    if (c == nullptr) {
        cout << "Error: Course not found!" << endl;
        return false;
    }
    if (!s->isenrolledin(coursecode)) {
        cout << "Error: Student is not enrolled in this course!" << endl;
        return false;
    }
    s->setgrade(coursecode, grade);
    c->setgrade(studentid, grade);
    return true;
}

void University::displayallstudents() {
    if (allstudents.size() == 0) {
        cout << "No students in the system." << endl;
        return;
    }
    cout << "\n========== ALL STUDENTS ==========" << endl;
    for (int i = 0; i < (int)allstudents.size(); i++) {
        cout << "----------------------------------------" << endl;
        allstudents[i].displayinfo();

        vector<string> codes = allstudents[i].getenrolledcoursecodes();
        cout << "  Course Details:" << endl;
        for (int j = 0; j < (int)codes.size(); j++) {
            Course* c = findcoursebycode(codes[j]);
            if (c != nullptr) {
                cout << "    " << codes[j] << " - " << c->getcoursename();
            } else {
                cout << "    " << codes[j] << " - Unknown Course";
            }
            float g = allstudents[i].getgrade(codes[j]);
            if (g >= 0) {
                cout << " Grade: " << g;
            } else {
                cout << " Grade: Not entered";
            }
            cout << endl;
        }

        float gpa = calcgpa(allstudents[i].getid());
        cout << "  GPA: " << gpa << endl;
    }
    cout << "=========================================" << endl;
}

void University::displayallcourses() {
    if (allcourses.size() == 0) {
        cout << "No courses in the system." << endl;
        return;
    }
    cout << "\n========== ALL COURSES ==========" << endl;
    for (int i = 0; i < (int)allcourses.size(); i++) {
        cout << "----------------------------------------" << endl;
        cout << "Course Code: " << allcourses[i].getcoursecode() << endl;
        cout << "Course Name: " << allcourses[i].getcoursename() << endl;
        cout << "Credits: " << allcourses[i].getcredits() << endl;

        string insid = allcourses[i].getinstructorid();
        if (insid != "") {
            Instructor* ins = findinstructorbyid(insid);
            if (ins != nullptr) {
                cout << "Instructor: " << ins->getname() << " (" << insid << ")" << endl;
            } else {
                cout << "Instructor ID: " << insid << endl;
            }
        } else {
            cout << "Instructor: None" << endl;
        }

        vector<string> ids = allcourses[i].getenrolledstudentids();
        cout << "Enrolled Students: " << (int)ids.size() << endl;
        for (int j = 0; j < (int)ids.size(); j++) {
            Student* s = findstudentbyid(ids[j]);
            if (s != nullptr) {
                cout << "  - " << s->getname() << " (" << ids[j] << ")";
            } else {
                cout << "  - " << ids[j];
            }
            float g = allcourses[i].getgrade(ids[j]);
            if (g >= 0) {
                cout << " Grade: " << g;
            } else {
                cout << " Grade: Not entered";
            }
            cout << endl;
        }
    }
    cout << "=========================================" << endl;
}

void University::displayalldepartments() {
    if (departments.size() == 0) {
        cout << "No departments in the system." << endl;
        return;
    }
    cout << "\n========== ALL DEPARTMENTS ==========" << endl;
    for (int i = 0; i < (int)departments.size(); i++) {
        cout << "----------------------------------------" << endl;
        departments[i].displayinfo();

        vector<string> sids = departments[i].getstudentids();
        if (sids.size() > 0) {
            cout << "  Student List:" << endl;
            for (int j = 0; j < (int)sids.size(); j++) {
                Student* s = findstudentbyid(sids[j]);
                if (s != nullptr) {
                    cout << "    - " << s->getname() << " (" << sids[j] << ")" << endl;
                }
            }
        }

        vector<string> iids = departments[i].getinstructorids();
        if (iids.size() > 0) {
            cout << "  Instructor List:" << endl;
            for (int j = 0; j < (int)iids.size(); j++) {
                Instructor* ins = findinstructorbyid(iids[j]);
                if (ins != nullptr) {
                    cout << "    - " << ins->getname() << " (" << iids[j] << ")" << endl;
                }
            }
        }

        vector<string> ccodes = departments[i].getcoursecodes();
        if (ccodes.size() > 0) {
            cout << "  Course List:" << endl;
            for (int j = 0; j < (int)ccodes.size(); j++) {
                Course* c = findcoursebycode(ccodes[j]);
                if (c != nullptr) {
                    cout << "    - " << ccodes[j] << " " << c->getcoursename() << endl;
                }
            }
        }
    }
    cout << "=========================================" << endl;
}

void University::displayabout() {
    cout << "\n=========================================" << endl;
    cout << "   About " << PROJECT_NAME << endl;
    cout << "=========================================" << endl;
    cout << "  Version: " << PROJECT_VERSION << endl;
    cout << "  Developed by: " << PROJECT_AUTHOR << endl;
    cout << "  Year: " << PROJECT_YEAR << endl;
    cout << "=========================================" << endl;
}

void University::savedata() {
    system("if not exist Data mkdir Data");

    ofstream deptfile("Data/departments.txt");
    if (deptfile.is_open()) {
        for (int i = 0; i < (int)departments.size(); i++) {
            deptfile << departments[i].getname() << endl;
        }
        deptfile.close();
    }

    ofstream insfile("Data/instructors.txt");
    if (insfile.is_open()) {
        for (int i = 0; i < (int)allinstructors.size(); i++) {
            string deptname = "";
            for (int j = 0; j < (int)departments.size(); j++) {
                vector<string> ids = departments[j].getinstructorids();
                for (int k = 0; k < (int)ids.size(); k++) {
                    if (ids[k] == allinstructors[i].getid()) {
                        deptname = departments[j].getname();
                        break;
                    }
                }
                if (deptname != "") break;
            }
            insfile << allinstructors[i].getid() << "|"
                    << allinstructors[i].getname() << "|"
                    << allinstructors[i].getage() << "|"
                    << deptname << endl;
        }
        insfile.close();
    }

    ofstream coursefile("Data/courses.txt");
    if (coursefile.is_open()) {
        for (int i = 0; i < (int)allcourses.size(); i++) {
            string deptname = "";
            for (int j = 0; j < (int)departments.size(); j++) {
                vector<string> codes = departments[j].getcoursecodes();
                for (int k = 0; k < (int)codes.size(); k++) {
                    if (codes[k] == allcourses[i].getcoursecode()) {
                        deptname = departments[j].getname();
                        break;
                    }
                }
                if (deptname != "") break;
            }
            coursefile << allcourses[i].getcoursecode() << "|"
                      << allcourses[i].getcoursename() << "|"
                      << allcourses[i].getcredits() << "|"
                      << allcourses[i].getinstructorid() << "|"
                      << deptname << endl;
        }
        coursefile.close();
    }

    ofstream stufile("Data/students.txt");
    if (stufile.is_open()) {
        for (int i = 0; i < (int)allstudents.size(); i++) {
            string deptname = "";
            for (int j = 0; j < (int)departments.size(); j++) {
                vector<string> ids = departments[j].getstudentids();
                for (int k = 0; k < (int)ids.size(); k++) {
                    if (ids[k] == allstudents[i].getid()) {
                        deptname = departments[j].getname();
                        break;
                    }
                }
                if (deptname != "") break;
            }
            stufile << allstudents[i].getid() << "|"
                   << allstudents[i].getname() << "|"
                   << allstudents[i].getage() << "|"
                   << deptname << endl;
        }
        stufile.close();
    }

    ofstream enrfile("Data/enrollments.txt");
    if (enrfile.is_open()) {
        for (int i = 0; i < (int)allstudents.size(); i++) {
            vector<string> codes = allstudents[i].getenrolledcoursecodes();
            for (int j = 0; j < (int)codes.size(); j++) {
                enrfile << allstudents[i].getid() << "|" << codes[j] << "|";
                float g = allstudents[i].getgrade(codes[j]);
                if (g >= 0) {
                    enrfile << g;
                }
                enrfile << endl;
            }
        }
        enrfile.close();
    }

    cout << "Data saved successfully!" << endl;
}

void University::loaddata() {
    departments.clear();
    allinstructors.clear();
    allcourses.clear();
    allstudents.clear();

    ifstream deptfile("Data/departments.txt");
    if (deptfile.is_open()) {
        string line;
        while (getline(deptfile, line)) {
            if (line != "") {
                Department d(line);
                departments.push_back(d);
            }
        }
        deptfile.close();
        cout << "Loaded " << departments.size() << " departments." << endl;
    }

    ifstream insfile("Data/instructors.txt");
    if (insfile.is_open()) {
        string line;
        while (getline(insfile, line)) {
            if (line == "") continue;
            stringstream ss(line);
            string id, name, agestr, deptname;
            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, agestr, '|');
            getline(ss, deptname, '|');

            int age = atoi(agestr.c_str());

            Department* d = finddepartment(deptname);
            if (d == nullptr) continue;

            Instructor ins(name, id, age);
            allinstructors.push_back(ins);
            d->addinstructor(id);
        }
        insfile.close();
        cout << "Loaded " << allinstructors.size() << " instructors." << endl;
    }

    ifstream coursefile("Data/courses.txt");
    if (coursefile.is_open()) {
        string line;
        while (getline(coursefile, line)) {
            if (line == "") continue;
            stringstream ss(line);
            string code, name, credstr, insid, deptname;
            getline(ss, code, '|');
            getline(ss, name, '|');
            getline(ss, credstr, '|');
            getline(ss, insid, '|');
            getline(ss, deptname, '|');

            int credits = atoi(credstr.c_str());

            Department* d = finddepartment(deptname);
            if (d == nullptr) continue;

            Course c(code, name, credits);

            Instructor* ins = findinstructorbyid(insid);
            if (ins != nullptr && insid != "") {
                c.setinstructorid(insid);
                ins->addcourse(code);
            }

            allcourses.push_back(c);
            d->addcourse(code);
        }
        coursefile.close();
        cout << "Loaded " << allcourses.size() << " courses." << endl;
    }

    ifstream stufile("Data/students.txt");
    if (stufile.is_open()) {
        string line;
        while (getline(stufile, line)) {
            if (line == "") continue;
            stringstream ss(line);
            string id, name, agestr, deptname;
            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, agestr, '|');
            getline(ss, deptname, '|');

            int age = atoi(agestr.c_str());

            Department* d = finddepartment(deptname);
            if (d == nullptr) continue;

            Student s(name, id, age);
            allstudents.push_back(s);
            d->addstudent(id);
        }
        stufile.close();
        cout << "Loaded " << allstudents.size() << " students." << endl;
    }

    ifstream enrfile("Data/enrollments.txt");
    if (enrfile.is_open()) {
        string line;
        while (getline(enrfile, line)) {
            if (line == "") continue;
            stringstream ss(line);
            string stuid, coursecode, gradestr;
            getline(ss, stuid, '|');
            getline(ss, coursecode, '|');
            getline(ss, gradestr, '|');

            Student* s = findstudentbyid(stuid);
            Course* c = findcoursebycode(coursecode);

            if (s != nullptr && c != nullptr) {
                c->enrollstudent(stuid);
                s->enrollcourse(coursecode);
                if (gradestr != "") {
                    stringstream gs(gradestr);
                    float grade;
                    gs >> grade;
                    s->setgrade(coursecode, grade);
                    c->setgrade(stuid, grade);
                }
            }
        }
        enrfile.close();
        cout << "Loaded enrollments." << endl;
    }
}

void University::showmenu() {
    cout << "\n=========================================" << endl;
    cout << "   " << PROJECT_NAME << endl;
    cout << "   Version " << PROJECT_VERSION << " by " << PROJECT_AUTHOR << endl;
    cout << "=========================================" << endl;
    cout << "1.  Add Department" << endl;
    cout << "2.  Add Student" << endl;
    cout << "3.  Add Instructor" << endl;
    cout << "4.  Add Course" << endl;
    cout << "5.  Enroll Student in Course" << endl;
    cout << "6.  Enter Grade" << endl;
    cout << "7.  View All Students" << endl;
    cout << "8.  View All Courses" << endl;
    cout << "9.  View All Departments" << endl;
    cout << "10. Search Student by ID" << endl;
    cout << "11. Search Course by Code" << endl;
    cout << "12. Save Data" << endl;
    cout << "13. About" << endl;
    cout << "14. Exit" << endl;
    cout << "=========================================" << endl;
    cout << "Enter your choice: ";
}

void University::run() {
    int choice;
    do {
        showmenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number." << endl;
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1: {
                string name;
                cout << "Enter department name: ";
                cin.ignore();
                getline(cin, name);
                if (adddepartment(name)) {
                    cout << "Department added successfully!" << endl;
                }
                break;
            }
            case 2: {
                string name, id, deptname;
                int age;
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter student ID: ";
                getline(cin, id);
                cout << "Enter age: ";
                cin >> age;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid age!" << endl;
                    break;
                }
                cout << "Enter department name: ";
                cin.ignore();
                getline(cin, deptname);
                if (addstudent(name, id, age, deptname)) {
                    cout << "Student added successfully!" << endl;
                }
                break;
            }
            case 3: {
                string name, id, deptname;
                int age;
                cout << "Enter instructor name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter instructor ID: ";
                getline(cin, id);
                cout << "Enter age: ";
                cin >> age;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid age!" << endl;
                    break;
                }
                cout << "Enter department name: ";
                cin.ignore();
                getline(cin, deptname);
                if (addinstructor(name, id, age, deptname)) {
                    cout << "Instructor added successfully!" << endl;
                }
                break;
            }
            case 4: {
                string code, name, insid, deptname;
                int credits;
                cout << "Enter course code: ";
                cin.ignore();
                getline(cin, code);
                cout << "Enter course name: ";
                getline(cin, name);
                cout << "Enter credits: ";
                cin >> credits;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid credits!" << endl;
                    break;
                }
                cout << "Enter instructor ID: ";
                cin.ignore();
                getline(cin, insid);
                cout << "Enter department name: ";
                getline(cin, deptname);
                if (addcourse(code, name, credits, insid, deptname)) {
                    cout << "Course added successfully!" << endl;
                }
                break;
            }
            case 5: {
                string studentid, coursecode;
                cout << "Enter student ID: ";
                cin.ignore();
                getline(cin, studentid);
                cout << "Enter course code: ";
                getline(cin, coursecode);
                if (enrollstudent(studentid, coursecode)) {
                    cout << "Student enrolled successfully!" << endl;
                }
                break;
            }
            case 6: {
                string studentid, coursecode;
                float grade;
                cout << "Enter student ID: ";
                cin.ignore();
                getline(cin, studentid);
                cout << "Enter course code: ";
                getline(cin, coursecode);
                cout << "Enter grade (0-100): ";
                cin >> grade;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid grade!" << endl;
                    break;
                }
                if (grade < 0 || grade > 100) {
                    cout << "Grade must be between 0 and 100!" << endl;
                    break;
                }
                if (entergrade(studentid, coursecode, grade)) {
                    cout << "Grade entered successfully!" << endl;
                }
                break;
            }
            case 7: {
                displayallstudents();
                break;
            }
            case 8: {
                displayallcourses();
                break;
            }
            case 9: {
                displayalldepartments();
                break;
            }
            case 10: {
                string id;
                cout << "Enter student ID: ";
                cin.ignore();
                getline(cin, id);
                Student* s = findstudentbyid(id);
                if (s != nullptr) {
                    cout << "----------------------------------------" << endl;
                    s->displayinfo();
                    cout << "----------------------------------------" << endl;
                } else {
                    cout << "Student not found!" << endl;
                }
                break;
            }
            case 11: {
                string code;
                cout << "Enter course code: ";
                cin.ignore();
                getline(cin, code);
                Course* c = findcoursebycode(code);
                if (c != nullptr) {
                    cout << "----------------------------------------" << endl;
                    c->displayinfo();
                    cout << "----------------------------------------" << endl;
                } else {
                    cout << "Course not found!" << endl;
                }
                break;
            }
            case 12: {
                savedata();
                break;
            }
            case 13: {
                displayabout();
                break;
            }
            case 14: {
                cout << "Saving data before exit..." << endl;
                savedata();
                cout << "Exiting system. Goodbye!" << endl;
                break;
            }
            default: {
                cout << "Invalid choice! Please enter 1-14." << endl;
                break;
            }
        }
    } while (choice != 14);
}

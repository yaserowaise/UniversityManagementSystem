// University Management System
// Developed by Yaser
// All rights reserved.

#include "University.h"

int main() {
    system("if not exist Data mkdir Data");

    cout << "=========================================" << endl;
    cout << "   " << PROJECT_NAME << endl;
    cout << "   Version " << PROJECT_VERSION << endl;
    cout << "   Developed by " << PROJECT_AUTHOR << endl;
    cout << "   " << PROJECT_YEAR << endl;
    cout << "=========================================" << endl;
    cout << endl;

    University uni;
    uni.run();

    return 0;
}

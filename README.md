# University Management System

**Version 1.0.0 | Developed by Yaser**

A simple C++ console-based University Management System built with Object-Oriented Programming concepts.

## Features

- Add and manage departments, students, instructors, and courses
- Enroll students in courses
- Enter and view grades
- Calculate GPA for each student
- Search for students by ID and courses by code
- Save all data to text files
- Load data from files when the program starts
- About screen with version and developer information

## OOP Concepts Used

| Concept | How it is used |
|---|---|
| **Inheritance** | `Student` and `Instructor` inherit from `Person` |
| **Polymorphism** | Virtual `displayinfo()` function overridden in derived classes |
| **Encapsulation** | All data members are private, accessed through public functions |
| **Composition** | `University` contains `Department`s, `Department` contains students/instructors/courses |
| **Operator Overloading** | `<<` and `==` operators overloaded for `Person`, `Course`, `Department` |
| **File Handling** | Data is saved to and loaded from `.txt` files using `fstream` |

## Class Hierarchy

```
Person
├── Student     (enrolled courses, grades)
└── Instructor  (taught courses)

Course          (course info, enrolled students, grades)
Department      (holds students, instructors, courses by name)
University      (manages everything, file I/O, menu system)
```

## Project Structure

```
UniversityManagementSystem/
├── Version.h         # Project version and author metadata
├── Person.h/cpp      # Base class
├── Student.h/cpp     # Student class (inherits Person)
├── Instructor.h/cpp  # Instructor class (inherits Person)
├── Course.h/cpp      # Course class
├── Department.h/cpp  # Department class
├── University.h/cpp  # University class (main logic)
├── main.cpp          # Entry point with startup banner
├── AUTHORS.md        # Author credits
├── LICENSE           # MIT License
├── README.md         # This file
└── Data/             # Text files for data persistence
    ├── departments.txt
    ├── students.txt
    ├── instructors.txt
    ├── courses.txt
    └── enrollments.txt
```

## How to Compile

### Using g++ (MinGW / Linux / macOS):

```bash
g++ -std=c++11 Person.cpp Course.cpp Student.cpp Instructor.cpp Department.cpp University.cpp main.cpp -o university
```

## How to Run

```bash
./university
```

On first run, the `Data/` folder will be created automatically if it does not exist.

## Menu Options

| Option | Description |
|---|---|
| 1  | Add a new department (e.g., "CS", "AI", "Physics") |
| 2  | Add a new student |
| 3  | Add a new instructor |
| 4  | Add a new course |
| 5  | Enroll a student in a course |
| 6  | Enter a grade for a student (0-100) |
| 7  | View all students with course details and GPA |
| 8  | View all courses with instructor and student info |
| 9  | View all departments with their members |
| 10 | Search for a student by ID |
| 11 | Search for a course by code |
| 12 | Save all data to files |
| 13 | About — version and developer information |
| 14 | Save and exit |

## Author

**Yaser** — Developer  
Copyright © 2026 Yaser. All rights reserved.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Protection Against Unauthorized Use

When uploading to GitHub, consider these practices to protect your work:

1. **Choose a clear license** — The MIT License included in this project defines what others can and cannot do with the code.

2. **Add a `README` badge** — Use GitHub badges to display the license type prominently at the top of this file.

3. **Use GitHub's "Releases" feature** — Tag stable versions so there is a clear release history with timestamps.

4. **Keep the copyright notice in source headers** — All source files in this project include a copyright header identifying Yaser as the developer. Do not remove these.

5. **Enable GitHub security features** — Under repository Settings > Security, enable Dependabot alerts and push protection.

6. **Add a `SECURITY.md` file** — Explain how you want to be contacted about security issues.

7. **Monitor forks** — GitHub's Insights > Forks page lets you see who has forked the repository.

8. **Watermark your work** — In a console project like this, the startup banner and About screen display the developer name as a visible watermark.

9. **Use Git tags** — Tag commits with version numbers (`git tag v1.0.0`) to create a verifiable chain of ownership.

10. **Register the copyright** — For additional legal protection in some jurisdictions, consider registering the copyright officially.

## Data File Format

All files use `|` as a delimiter and are stored in the `Data/` folder.

**departments.txt**
```
CS
AI
Cyber Security
```

**students.txt**
```
id|name|age|department
S001|John Doe|20|CS
```

**instructors.txt**
```
id|name|age|department
I001|Dr. Brown|45|CS
```

**courses.txt**
```
code|name|credits|instructorId|department
CS101|Programming 1|3|I001|CS
```

**enrollments.txt**
```
studentId|courseCode|grade
S001|CS101|85.5
```

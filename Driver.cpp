// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: Lazy Balanced Trees - Driver.cpp class

#include <iostream>
#include "Driver.h"
#include "DblList.h"
#include <fstream>
#include <cstdio>

// Driver class - simulates the entire database system, contains BSTs for both StudentDatabase and FacultyDatabase

/*
a. overloaded constructor
b. no return
c. no params
d. no known exeptions thrown
*/
Driver::Driver(){
  StudentDatabase = new LazyBST<Student>();
  FacultyDatabase = new LazyBST<Faculty>();

  Faculty* x = new Faculty(50, "erik", "lecturer", "CS");
  Faculty* y = new Faculty(20, "elia", "lecturer", "CS");
  Faculty* z = new Faculty(60, "elizabeth", "lecturer", "CS");

  FacultyDatabase -> insert(*x);
  FacultyDatabase -> insert(*y);
  FacultyDatabase -> insert(*z);

  // Student* a = new Student(200, "bob", "sophomore", 3.8, 50);
  // Student* b = new Student(100, "alice", "freshman", 4.0, 20);
  // Student* c = new Student(300, "may", "sophomore", 3.2, 60);

  // StudentDatabase -> insert(*a);
  // StudentDatabase -> insert(*b);
  // StudentDatabase -> insert(*c);
}

/*
a. destructor
b. no return
c. no params
d. no known exeptions thrown
*/
Driver::~Driver(){
}

/*
a. simulate method
b. returns void
c. no params
d. no known exeptions thrown
*/
void Driver::simulate(){
  int userInput;
  userInput = 0;
  while (userInput != 11){

    std::cout << "Select an option from the menu below (enter number): " << std::endl << std::endl;
    std::cout << "1. Print all students" << std::endl;
    std::cout << "2. Print all faculty" << std::endl;
    std::cout << "3. Find and display student information given the student id" << std::endl;
    std::cout << "4. Find and display faculty information given the faculty id" << std::endl;
    std::cout << "5. Add a new student" << std::endl;
    std::cout << "6. Delete a student given the id" << std::endl;
    std::cout << "7. Add a new faculty member" << std::endl;
    std::cout << "8. Delete a faculty member given the id" << std::endl;
    std::cout << "9. Change a student’s advisor given the student id and the new faculty id" << std::endl;
    std::cout << "10. Remove an advisee from a faculty member given the ids" << std::endl;
    std::cout << "11. Exit" << std::endl << std::endl;

    std::cout << "Select an option (numerical): ";
    cin >> userInput;
    switch(userInput){
      case 1:
        printStudents();
        break;

      case 2:
        printFaculty();
        break;

      case 3:
        displayStudentInfo();
        break;

      case 4:
        displayFacultyInfo();
        break;

      case 5:
        addStudent();
        break;

      case 6:
        deleteStudent();
        break;

      case 7:
        addFaculty();
        break;

      case 8:
        deleteFaculty();
        break;

      case 9:
        changeStudentAdvisor();
        break;

      case 10:
        removeAdvisee();
        break;

      default:
        break;
    }
    // if broken out of while loop, case 11
  }
  exit();
}

/*
a. printStudents method
b. returns void
c. no params
d. no known exeptions thrown
*/
// 1. Print all students and their information (sorted by ascending id #)
void Driver::printStudents(){
  StudentDatabase -> printInOrder();
}

/*
a. printFaculty method
b. returns void
c. no params
d. no known exeptions thrown
*/
// 2. Print all faculty and their information (sorted by ascending id #)
void Driver::printFaculty(){
  FacultyDatabase -> printInOrder();
}

/*
a. displayStudentInfo method
b. returns void
c. no params
d. no known exeptions thrown
*/
// 3. Find and display student information given the student id
void Driver::displayStudentInfo(){
  int id;
  std::cout << "Please enter ID number of the student you wish to access: ";
  cin >> id;
  Student* temp = new Student(id);
  if(StudentDatabase -> contains(*temp)){
    StudentDatabase -> getObject(*temp).printInfo();
  }else{
    std::cout << "Database doesn't contain this student ID. Exit Program" << std::endl;
  }
}

/*
a. displayFacultyInfo method
b. returns void
c. no params
d. no known exeptions thrown
*/
// 4. Find and display faculty information given the faculty id
void Driver::displayFacultyInfo(){
  int id;
  std::cout << "Please enter ID number of the faculty you wish to access: ";
  cin >> id;
  Faculty* temp = new Faculty(id);
  if(FacultyDatabase -> contains(*temp)){
    FacultyDatabase -> getObject(*temp).printInfo();
  }else{
    std::cout << "Database doesn't contain this faculty ID. Exiting command..." << std::endl;
  }
}

/*
a. addStudent method
b. returns void
c. no params
d. no known exeptions thrown
*/
// 5. Add a new student
void Driver::addStudent(){
  int id;
  std::string name;
  std::string lvl;
  double gpa;
  int advisor;

  std::cout << "Enter student ID: ";
  cin >> id;
  std::cout << "Enter student name: ";
  cin >> name;
  std::cout << "Enter student grade level: ";
  cin >> lvl;
  std::cout << "Enter student GPA: ";
  cin >> gpa;
  std::cout << "Enter student advisor ID: ";
  cin >> advisor;

  Faculty* temp = new Faculty(advisor);
  if(FacultyDatabase -> contains(*temp)){
    FacultyDatabase -> getObject(*temp).addStudentID(id); // add student to advisor's student list
    Student* s = new Student(id,name,lvl,gpa,advisor);
    StudentDatabase -> insert(*s);
  }else{
    std::cout << "Faculty database doesn't contain the entered advisor ID. Exiting command..." << std::endl;
  }
}

/*
a. deleteStudent method
b. returns void
c. no params
d. no known exeptions thrown
*/
// 6. Delete a student given the id
void Driver::deleteStudent(){
  int id;
  std::cout << "Please enter ID number of the student you wish to delete: ";
  cin >> id;

  Student* temp = new Student(id);
  if(StudentDatabase -> contains(*temp)){
    // remove student from StudentDatabase BST
    // we also need to delete this student from the assigned faculty's studentIDs list
    Student studentToDelete = StudentDatabase -> getObject(*temp);
    int advisorID = studentToDelete.getAdvisorID();
    Faculty* f = new Faculty(advisorID);
    if(FacultyDatabase -> contains(*f)){
      FacultyDatabase -> getObject(*f).removeStudentID(id); // remove student id from their advisor's student list
    }
    StudentDatabase -> remove(StudentDatabase -> getObject(*temp)); // remove student from StudentDatabase
  }else{
    std::cout << "Student database doesn't contain the entered student ID. Exiting command..." << std::endl;
  }
}

/*
a. addFaculty method
b. returns void
c. no params
d. no known exeptions thrown
*/
// 7. Add a new faculty member
void Driver::addFaculty(){
  int id;
  std::string name;
  std::string lvl;
  std::string dept;

  std::cout << "Enter faculty ID: ";
  cin >> id;
  std::cout << "Enter faculty name: ";
  cin >> name;
  std::cout << "Enter faculty level: ";
  cin >> lvl;
  std::cout << "Enter faculty department: ";
  cin >> dept;

  Faculty* f = new Faculty(id,name,lvl,dept);
  FacultyDatabase -> insert(*f);
}

/*
a. deleteFaculty method
b. returns void
c. no params
d. no known exeptions thrown
*/
// 8. Delete a faculty member given the id.
void Driver::deleteFaculty(){
  int id;
  std::cout << "Please enter ID number of the faculty you wish to delete: ";
  cin >> id;

  Faculty* f = new Faculty(id);
  if(FacultyDatabase -> contains(*f)){
    int facultyNum;
    std::cout << "Which faculty would you like to reassign students to: " << std::endl;
    cin >> facultyNum;
    Faculty* holder = new Faculty(facultyNum);
    if(FacultyDatabase -> contains(*holder)){
      Faculty facultyToDelete = FacultyDatabase -> getObject(*f); // get faculty with the inputted facultyNum
      int param = facultyToDelete.sizeofStudentIDsList(); // size of DBLlist
      FacultyDatabase -> remove(FacultyDatabase -> getObject(*f)); // remove from FacultyDatabase
      for (int i=0; i<param; ++i){
        int studentIDtoReassign = facultyToDelete.returnStudentID(); // returns id of student in faculty's student list
        Student* temp = new Student(studentIDtoReassign);
        StudentDatabase -> getObject(*temp).setAdvisorID(facultyNum); // set student's advisor to a new advisor
        FacultyDatabase -> getObject(*holder).addStudentID(studentIDtoReassign);// add student id to new advisor
      }
    }else{
      std::cout << "Faculty database doesn't contain the entered faculty ID. Exiting command..." << std::endl;
    }
  }else{
    std::cout << "Faculty database doesn't contain the entered faculty ID. Exiting command..." << std::endl;
  }
}

/*
a. changeStudentAdvisor method
b. returns void
c. no params
d. no known exeptions thrown
*/
// 9. Change a student’s advisor given the student id and the new faculty id
void Driver::changeStudentAdvisor(){
  int studentID;
  int newFacultyID;

  std::cout << "Please enter ID number of the student you wish to reassign faculty to: ";
  cin >> studentID;
  Student* temp = new Student(studentID);
  if(StudentDatabase -> contains(*temp)){
    std::cout << std::endl << "Please enter ID number of the new faculty you wish to assign: ";
    cin >> newFacultyID;
    Faculty* newAdvisorHolder = new Faculty(newFacultyID);
    Faculty* oldAdvisorHolder = new Faculty(StudentDatabase -> getObject(*temp).getAdvisorID());
    if(FacultyDatabase -> contains(*newAdvisorHolder)){
      //remove student ID from old advisor list
      FacultyDatabase -> getObject(*oldAdvisorHolder).removeStudentID(studentID);
      // add student ID to new advisor list
      StudentDatabase -> getObject(*temp).setAdvisorID(newFacultyID); //sets advisorID of student
      FacultyDatabase -> getObject(*newAdvisorHolder).addStudentID(studentID);
    }else{
      std::cout << "Faculty database doesn't contain the entered faculty ID. Exiting command..." << std::endl;
    }
  }else{
    std::cout << "Student database doesn't contain the entered student ID. Exiting command..." << std::endl;
  }
}

/*
a. removeAdvisee method
b. returns void
c. no params
d. no known exeptions thrown
*/
// 10. Remove an advisee from a faculty member given the ids
void Driver::removeAdvisee(){
  int studentID;
  int newFacultyID;

  std::cout << "Please enter ID number of the new faculty you wish to assign: ";
  cin >> newFacultyID;
  Faculty* newAdvisorHolder = new Faculty(newFacultyID);
  if(FacultyDatabase -> contains(*newAdvisorHolder)){
    std::cout << std::endl << "Please enter ID number of the student you wish to reassign faculty to: ";
    cin >> studentID;
    Student* temp = new Student(studentID);
    if(StudentDatabase -> contains(*temp)){
      Faculty* oldAdvisorHolder = new Faculty(StudentDatabase -> getObject(*temp).getAdvisorID());
      //remove student ID from old advisor list
      FacultyDatabase -> getObject(*oldAdvisorHolder).removeStudentID(studentID);
      // add student ID to new advisor list
      StudentDatabase -> getObject(*temp).setAdvisorID(newFacultyID); //sets advisorID of student
      //adds studentID to new faculty
      FacultyDatabase -> getObject(*newAdvisorHolder).addStudentID(studentID);
    } else{
      std::cout << "Student database doesn't contain the entered student ID. Exiting command..." << std::endl;
    }
  }else{
    std::cout << "Faculty database doesn't contain the entered faculty ID. Exiting command..." << std::endl;
  }
}

/*
a. exit method
b. returns void
c. no params
d. no known exeptions thrown
*/
void Driver::exit(){
  // create a file named runLog.txt, which contains the information of
  // both tables at the time the program was terminated
  ofstream {"runLog.txt"}; // create runLog.txt
  std::cout << "Printing StudentDatabase and FacultyDatabase BSTs to runLog.txt..." << std::endl;
  freopen("runLog.txt","w",stdout); // redirect output to file
  printStudents();
  printFaculty();
}

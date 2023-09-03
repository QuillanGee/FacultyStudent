// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: Lazy Balanced Trees - Driver.h class

#ifndef Driver_H
#define Driver_H
#include "LazyBST.h"
#include "Student.h"
#include "Faculty.h"
#include "DblList.h"
#include <iostream>

// Driver class - simulates the entire database system, contains BSTs for both StudentDatabase and FacultyDatabase

class Driver{
    public:
      Driver();
      ~Driver();
      void simulate();
      void printStudents(); // option 1
      void printFaculty(); // option 2
      void displayStudentInfo(); // option 3
      void displayFacultyInfo(); // option 4
      void addStudent(); // option 5
      void deleteStudent(); // option 6
      void addFaculty(); // option 7
      void deleteFaculty(); // option 8
      void changeStudentAdvisor(); // option 9
      void removeAdvisee(); // option 10
      void exit(); // option 11

    private:
      LazyBST<Student>* StudentDatabase; // Student BST
      LazyBST<Faculty>* FacultyDatabase; // Faculty BST
};
#endif

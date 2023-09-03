// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: Lazy Balanced Trees - Student.cpp class

#include "Student.h"
#include <iostream>

// Student class - represents a Student and their attributes

/*
a. constructor
b. no return
c. no params
d. no known exeptions thrown
*/
Student::Student(){
  id = -1;
  name = "";
  level = "";
  gpa = 0.0;
  advisor = -1;
}

/*
a. constructor
b. no return
c. takes in int i (id)
d. no known exeptions thrown
*/
Student::Student(int i){
  id = i;
  name = "";
  level = "";
  gpa = 0.0;
  advisor = -1;
}

/*
a. overloaded constructor
b. no return
c. takes in int i, std::string n, std::string l, double g, int a
d. no known exeptions thrown
*/
Student::Student(int i, std::string n, std::string l, double g, int a){
  id = i;
  name = n;
  level = l;
  gpa = g;
  advisor = a;
}

/*
a. destructor
b. no return
c. takes in int i, std::string n, std::string l, double g, int a
d. no known exeptions thrown
*/
Student::~Student(){
}

/*
a. printInfo method
b. no return
c. no params
d. no known exeptions thrown
*/
void Student::printInfo(){
  std::cout << "Student ID: " << id << std::endl;
  std::cout << "Student name: " << name << std::endl;
  std::cout << "Student grade level: " << level << std::endl;
  std::cout << "Student GPA: " << gpa << std::endl;
  std::cout << "Student advisor ID: " << advisor << std::endl << std::endl;
}

/*
a. getAdvisorID method
b. returns int advisor
c. no params
d. no known exeptions thrown
*/
int Student::getAdvisorID(){
  return advisor;
}

/*
a. setAdvisorID method
b. no return
c. takes in int& newAdvisorID
d. no known exeptions thrown
*/
void Student::setAdvisorID(int& newAdvisorID){
  std::cout << "New advisor ID" <<newAdvisorID << std::endl;
  std::cout << "Older advisor ID: " << advisor << std::endl;
  advisor = newAdvisorID;
}

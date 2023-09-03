// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: Lazy Balanced Trees - Faculty.cpp class

#include "Faculty.h"
#include <iostream>

// Faculty class - represents a Faculty member and their attributes

/*
a. constructor
b. no return
c. no params
d. no known exeptions thrown
*/
Faculty::Faculty(){
  id = -1;
  name = "";
  level = "";
  department = "";
  studentIDs = new DblList<int>();
}

/*
a. constructor
b. no return
c. takes in int i (id)
d. no known exeptions thrown
*/
Faculty::Faculty(int i){
  id = i;
  name = "";
  level = "";
  department = "";
  studentIDs = new DblList<int>();
}

/*
a. overloaded constructor
b. no return
c. takes in int i, std::string n, std::string l, std::string d
d. no known exeptions thrown
*/
Faculty::Faculty(int i, std::string n, std::string l, std::string d){
  id = i;
  name = n;
  level = l;
  department = d;
  studentIDs = new DblList<int>();
}

/*
a. destructor
b. no return
c. no params
d. no known exeptions thrown
*/
Faculty::~Faculty(){
}

/*
a. printInfo method
b. no return
c. no params
d. no known exeptions thrown
*/
void Faculty::printInfo(){
  std::cout << "Faculty ID: " << id << std::endl;
  std::cout << "Faculty name: " << name << std::endl;
  std::cout << "Faculty level: " << level << std::endl;
  std::cout << "Faculty department: " << department << std::endl;
  std::cout << "Students assigned to this faculty: ";
  if (studentIDs -> size() > 0){
    for (int i=0; i<studentIDs -> size(); ++i){
      std::cout << studentIDs -> get(i) << " ";
    }
  }
  std::cout << std::endl << std::endl;
}

/*
a. addStudentID method
b. no return
c. takes in int id
d. no known exeptions thrown
*/
void Faculty::addStudentID(int id){
  studentIDs -> addBack(id);
}

/*
a. removeStudentID method
b. no return
c. takes in int id
d. no known exeptions thrown
*/
void Faculty::removeStudentID(int id){
  int pos;
  for (int i=0; i<studentIDs -> size(); ++i){ // loop thru list until id matches
    if (studentIDs -> get(i) == id){
      pos = i;
      break;
    }
  }
  studentIDs -> remove(pos);
}

/*
a. sizeofStudentIDsList method
b. returns int
c. no params
d. no known exeptions thrown
*/
int Faculty::sizeofStudentIDsList(){
  return studentIDs -> size();
}

/*
a. returnStudentID method
b. returns int
c. no params
d. no known exeptions thrown
*/
int Faculty::returnStudentID(){
  return studentIDs -> removeBack();
}

/*
a. getFacultyID method
b. returns int
c. no params
d. no known exeptions thrown
*/
int Faculty::getFacultyID(){
  return id;
}

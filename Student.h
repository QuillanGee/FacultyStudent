// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: Lazy Balanced Trees - Student.h class

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

// Student class - represents a Student and their attributes

class Student{
    public:
      Student();
      Student(int i);
      Student(int i, std::string n, std::string l, double g, int a);
      ~Student();
      void printInfo();
      int getAdvisorID();
      void setAdvisorID(int& newAdvisorID);
      int id;
      int advisor; // faculty ID of advisor

      // overloaded methods
      friend bool operator==(const Student& s1, const Student& s2){
        return s1.id == s2.id;
      }
      friend bool operator!=(const Student& s1, const Student& s2){
        return s1.id != s2.id;
      }
      friend bool operator<(const Student& s1, const Student& s2){
        return s1.id < s2.id;
      }
      friend bool operator>(const Student& s1, const Student& s2){
        return s1.id > s2.id;
      }

    private:
      std::string name;
      std::string level; // grade level
      double gpa;

};
#endif

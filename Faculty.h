// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: Lazy Balanced Trees - Faculty.h class

#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
#include "DblList.h"

// Faculty class - represents a Faculty member and their attributes

class Faculty{
    public:
      Faculty();
      Faculty(int i);
      Faculty(int i, std::string n, std::string l, std::string d);
      ~Faculty();
      void printInfo();
      void addStudentID(int id);
      void removeStudentID(int id);
      int sizeofStudentIDsList();
      int returnStudentID(); // returns the back most id in studentIDs
      int getFacultyID();
      DblList<int>* studentIDs;

      // overloaded methods
      friend bool operator==(const Faculty& s1, const Faculty& s2){
        return s1.id == s2.id;
      }
      friend bool operator!=(const Faculty& s1, const Faculty& s2){
        return s1.id != s2.id;
      }
      friend bool operator<(const Faculty& s1, const Faculty& s2){
        return s1.id < s2.id;
      }
      friend bool operator>(const Faculty& s1, const Faculty& s2){
        return s1.id > s2.id;
      }

    private:
      int id;
      std::string name;
      std::string level; // job title
      std::string department;

};
#endif

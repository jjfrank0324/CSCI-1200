#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
using namespace std;
#include "Person.h"

Person::Person(){
vector<int> L;
fname = "";
lname = "";
scores = L;
total_score = 0;
}

Person::Person(std::string afname, std::string alname, std::vector<int> ascores, int atotal_score){
fname = afname;
lname = alname;
scores = ascores;
total_score = atotal_score;
}

std::string Person::getfname() const{
  return fname;
}

std::string Person::getlname() const{
  return lname;
}

std::string Person::getname() const{
  return lname+" "+fname;
}

std::vector<int> Person::getscores() const{
  return scores;
}

int Person::gettotal_scores() const{
return total_score;
}

void Person::set_totalscores(int total){
  total_score=total;
}

bool lower_score(const Person& p1, const Person& p2){
  if (p1.gettotal_scores()<p2.gettotal_scores())
  return false;
  else
  return true;
}
bool lower_name(const Person& p1, const Person& p2){
  if(p1.getfname()==p2.getfname())
  return p1.getlname()<p2.getlname();
  else
  return p1.getfname()<p2.getfname();
}

#include <iostream>
#include <vector>
#include "Time.h"
#include <algorithm>
int main() {

  Time t1(11,11,11); // calls the non-default constructor w/ 3 integer arguments
  Time t2(1,12,11);
  Time t4(11,13,11);
  Time t5(18,11,16);
  Time t3;
  std::vector<Time> time_list;
  time_list.push_back(t1);
  time_list.push_back(t2);
  time_list.push_back(t3);
  time_list.push_back(t4);
  time_list.push_back(t5);
  t1.sethour(6);
  std::cout<<t1.gethour()<<std::endl;
  t1.printAmPm();
  std::cout<<"TESTING FUNCION"<<std::endl;
  if (IsEarlierThan (t1,t3))  std::cout<<"666";
  else std::cout<<"999";

  for (unsigned int i=0; i< time_list.size();i++)
  {time_list[i].printAmPm();}
  std::cout<<"LLLLLLLLLLLLLLLLLLLLL"<<std::endl;
  sort(time_list.begin(),time_list.end(),IsEarlierThan);
  for (unsigned int i=0; i< time_list.size();i++)
  {time_list[i].printAmPm();}
return 0;
}

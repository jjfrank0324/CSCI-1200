#include <iostream>
#include "Time.h"

Time::Time() { //default constructor
hour=0;
minute=0;
second=0;
}

Time::Time(int ahour, int aminute, int asecond) { //default constructor
hour=ahour;
minute=aminute;
second=asecond;
}

int Time::gethour() const{
  return hour;
}

int Time::getminute() const{
  return minute;
}

int Time::getsecond() const{
  return second;
}

void Time::sethour(int h) {
  hour = h;
}

void Time::setminute(int m) {
  minute = m;
}

void Time::setsecond(int s) {
  second = s;
}

void Time::printAmPm() const{
  if (hour <   13 && hour !=0)
  { std::cout<<hour<<":";}
  if (hour > 12 )
  {std::cout<<hour-12<<":"; }
  if (hour == 0)
  {std::cout<<12<<":"; }
  if (minute<10)
  {std::cout<<'0'<<minute<<":";}
  if (minute>10)
  {std::cout<<minute<<":";}
  if (second<10)
  {std::cout<<'0'<<second;}
  if (second>10)
  {std::cout<<second;}
  if (hour <   13)
  { std::cout<<"AM";}
  if (hour >   12)
  {std::cout<<"PM";}
  std::cout<<"\n";

}

  bool IsEarlierThan (const Time& t1, const Time& t2)
  {
    if (t1.gethour()<t2.gethour())
    return true;
    else if(t1.gethour()==t2.gethour()&& t1.getminute()<t2.getminute())
    return true;
    else if(t1.getminute()==t2.getminute() && t1.getsecond() <t2.getsecond() )
    return true;
    else return false;
  }

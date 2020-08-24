#ifndef __TIMEQ_H_
#define __TIMEQ_H_
//You can change/add to these #includes
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;
typedef unsigned int tq_hook; //Used to point to a location in the heap, fill in the "???"
#include "Job.h"
//Forward declaration of Job class, do not remove this line, do not change.
class Job;

//Promise to declare stream output operator for internal vector heap representation
std::ostream& operator<<(std::ostream& out, const std::vector<Job*>& heap);


//this is the class that we construct
// we only add the function which is needed
class TimeQueue{
public:
  //return the first elements of the Job
  const  Job* top(){return m_heap[0];}
  //remove an elements from the job
  Job* pop();
  //add an element
  void push(Job* entry);
  // helper function to help us do the adding andremoving
  void percolate_down();
    // helper function to help us do the adding andremoving
  void percolate_up();
  //the required function which help us
  //formatting the output properly
  ostream& printHeap(ostream& outfile);
  //remove an job from specific index
  void remove_from_index(unsigned int index);
//////////FILL THIS IN///////////
private:
  //this the private variable, we only declare
  // an heap over here
  vector<Job*> m_heap;
};


#endif

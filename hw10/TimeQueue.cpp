//You can change/add to these #includes
#include <ctime>
#include <iostream>
#include <vector>
#include "Job.h"

using namespace std;
typedef unsigned int tq_hook; //Used to point to a location in the heap, fill in the "???"

//this function remove the first element in the heap
//remove and rearrange
Job* TimeQueue::pop()
{
  Job* a;
    //exchange the first and the last
  m_heap[0] = m_heap[m_heap.size()-1];
  a = m_heap[m_heap.size()-1];
  //delete the "first" one
  m_heap.pop_back();
  //rearrange the order
  percolate_down();
  return a;
}

void TimeQueue::percolate_down()
{
  //percolate from the top
  unsigned int i =0;

  //this is simpify from  version of  the index
  // it guatuantee that the child exist
  while(i < m_heap.size()/2+1)
  {
        //find out the bigger child and use j to indicate it
    unsigned int j =0;
    if( 2*i+2 < m_heap.size() && m_heap[2*i+2]->getTime() < m_heap[2*i+1]->getTime() )
       j = 2*i+2;
    else
      j = 2*i+1;
  // if the child is smaller than the parent change position"
    //exchange it
    if(m_heap[j]->getTime() < m_heap[i]->getTime())
      {
        std::swap(m_heap[i], m_heap[j]);
        i=j;
      }
        //is the order is right, we can stop percolating
    else
      break;
  }
}

//push the element into the quere, properly arrange the hook,
// then rearrange the element order in theq queue
void TimeQueue::push(Job* entry)
{  m_heap.push_back(entry);

    //hnadle the hook of the job we just push in
  m_heap[m_heap.size()-1]->time_hook= m_heap.size()-1;
  m_heap[m_heap.size()-1]->time_ptr = this;

    //rearrange the lelemnts in the que
  percolate_up();
}

void TimeQueue::percolate_up()
{

    //start from the last elemets, we need to make sure the it end
    // at the first elemts
  int i =m_heap.size()-1;
  while (i >= 0)
  {
    //if the children is smaller than the parent
    // we need to swap it
    if (m_heap[i]->getTime() < m_heap[(i - 1)/2]->getTime()){
      std::swap(m_heap[i], m_heap[(i - 1)/2]);
          i = (i - 1)/2;
    }
    else
      break;
  }
}



//print out the heap in proper fomat
ostream& TimeQueue::printHeap(ostream& outfile)
{ outfile<<"TQ "<<m_heap.size()<<" jobs:"<<"\n";
  for(unsigned int i =0; i<m_heap.size();i++)
  outfile<<"\t"<<m_heap[i];
  return outfile;
}

//remove the elements from specific index
//remove and rearrange the elements
void TimeQueue::remove_from_index(unsigned int index)
{
    //put the elements in back and pop it
    m_heap[m_heap.size()-1] = m_heap[index] ;
    m_heap.pop_back();


    //start from the index, we need do an revised version
    // of percolate down
    unsigned int i = index;

    //while the childern exist
    while(i < m_heap.size()/2-1)
    {
      //find out the bigger child and use j to indicate it
      unsigned int j =0;
      if( 2*i+2 < m_heap.size() && m_heap[2*i+2]->getPriority() < m_heap[2*i+1]->getPriority() )
         j = 2*i+2;
      else
        j = 2*i+1;


        // if the child is smaller than the parent change position"
        //exchange it

      if(m_heap[j]->getPriority() < m_heap[i]->getPriority())
        {
          std::swap(m_heap[i], m_heap[j]);
          i=j;
        }

                //is the order is right, we can stop percolating
      else
        break;
    }

}

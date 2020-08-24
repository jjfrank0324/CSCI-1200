//You can change/add to these #includes
#include <ctime>
#include <iostream>
#include <vector>
#include "Job.h"
using namespace std;
//typedef unsigned int uq_hook; //Used to point to a location in the heap, fill in the "???"

Job* UrgentQueue::pop()
{
  Job* a;
  m_heap[0] = m_heap[m_heap.size()-1];
  a = m_heap[m_heap.size()-1];
  m_heap.pop_back();
  percolate_down();
  return a;
}

void UrgentQueue::percolate_down()
{
  unsigned int i =0;
  while(i < m_heap.size()/2+1)
  {
    unsigned int j =0;
    if( 2*i+2 < m_heap.size() && m_heap[2*i+2]->getPriority() < m_heap[2*i+1]->getPriority() )
       j = 2*i+2;
    else
      j = 2*i+1;

    if(m_heap[j]->getPriority() < m_heap[i]->getPriority())
      {
        std::swap(m_heap[i], m_heap[j]);
        i=j;
      }
    else
      break;
  }
}

void UrgentQueue::push(Job* entry)
{
      m_heap.push_back(entry);
  m_heap[m_heap.size()-1]->urgent_hook= m_heap.size()-1;
  m_heap[m_heap.size()-1]->priority_ptr = this;
  percolate_up();
}

void UrgentQueue::percolate_up(){
for(int i = m_heap.size()-1; i >= 0;){
  if (m_heap[i]->getPriority() < m_heap[(i - 1)/2]->getPriority()){
    std::swap(m_heap[i], m_heap[(i - 1)/2]); // value and other non-pointer member vars
    i = (i - 1)/2;
  }
  else
    break;
}
}



ostream& UrgentQueue::printHeap(ostream& outfile)
{
  for(unsigned int i =0; i<m_heap.size();i++)
  outfile<<m_heap[i]->getID()<<"\n";
}

void UrgentQueue::remove_from_index(unsigned int index)
{
  m_heap[index] = m_heap[m_heap.size()-1] ;
  m_heap.pop_back();
  unsigned int i =index;
  while(i < m_heap.size()/2+1)
  {
    unsigned int j =0;
    if( 2*i+2 < m_heap.size() && m_heap[2*i+2]->getPriority() < m_heap[2*i+1]->getPriority() )
       j = 2*i+2;
    else
      j = 2*i+1;

    if(m_heap[j]->getPriority() < m_heap[i]->getPriority())
      {
        std::swap(m_heap[i], m_heap[j]);
        i=j;
      }
    else
      break;
  }
}
























//You can change/add to these #includes
#include <ctime>
#include <iostream>
#include <vector>
#include "Job.h"

using namespace std;
typedef unsigned int tq_hook; //Used to point to a location in the heap, fill in the "???"

Job* TimeQueue::pop()
{
  Job* a;
  m_heap[0] = m_heap[m_heap.size()-1];
  a = m_heap[m_heap.size()-1];
  m_heap.pop_back();
  percolate_down();
  return a;
}

void TimeQueue::percolate_down()
{
  unsigned int i =0;
  while(i < m_heap.size()/2+1)
  {
    unsigned int j =0;
    if( 2*i+2 < m_heap.size() && m_heap[2*i+2]->getTime() < m_heap[2*i+1]->getTime() )
       j = 2*i+2;
    else
      j = 2*i+1;

    if(m_heap[j]->getTime() < m_heap[i]->getTime())
      {
        std::swap(m_heap[i], m_heap[j]);
        i=j;
      }
    else
      break;
  }
}

void TimeQueue::push(Job* entry)
{     m_heap.push_back(entry);
  m_heap[m_heap.size()-1]->time_hook= m_heap.size()-1;
  m_heap[m_heap.size()-1]->time_ptr = this;
  percolate_up();
}

void TimeQueue::percolate_up(){
for(int i = m_heap.size()-1; i >= 0;){
  if (m_heap[i]->getTime() < m_heap[(i - 1)/2]->getTime()){
    std::swap(m_heap[i], m_heap[(i - 1)/2]); // value and other non-pointer member vars
    i = (i - 1)/2;
  }
  else
    break;
}
}

ostream& TimeQueue::printHeap(ostream& outfile)
{
  outfile<<"lol";
}

void TimeQueue::remove_from_index(unsigned int index)
{

    m_heap[index] = m_heap[m_heap.size()-1] ;
    m_heap.pop_back();
    unsigned int i =index;
    while(i < m_heap.size()/2+1)
    {
      unsigned int j =0;
      if( 2*i+2 < m_heap.size() && m_heap[2*i+2]->getPriority() < m_heap[2*i+1]->getPriority() )
         j = 2*i+2;
      else
        j = 2*i+1;

      if(m_heap[j]->getPriority() < m_heap[i]->getPriority())
        {
          std::swap(m_heap[i], m_heap[j]);
          i=j;
        }
      else
        break;
    }

}

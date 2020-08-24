// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "traincar.h"


/*
This is the pushing back function. All we need to be careful over here is the conrner cases
To Avoid possible error,  I made several if statements to make sure that all this code Will
work at corner cases: Like when it pass in an NULL train.

*/
void PushBack(TrainCar* &trains, TrainCar* car){
  TrainCar* origin = trains;
  if (trains == NULL){
    trains = car;
    trains->prev = NULL;
    trains->next = NULL;
    return;
  }
  else if(trains->next != NULL){
    PushBack(trains->next, car);
  }
  else if(trains->next == NULL) {
    trains->next =car;
    car->prev = trains;
    car->next = NULL;
    trains = origin;
    return;
  }
}
/*
I deleted the train from the begining and one by ONE
the while loop make sure that the train reach the end when we finshed all the deleting function
*/
void DeleteAllCars(TrainCar* &trains){
  TrainCar* T = NULL;
  while(trains != NULL){
    T = trains->next;
    delete(trains);
    if (T != NULL)
      T->prev = NULL;
    trains = T;
  }

}
/*
This is the helper function that we must ti add to make the helper function WORK
I go though the trains, if that is specific parts, the number for it will add one.
*/

void TotalWeightAndCountCars(TrainCar* train, int& total_weight,int& num_engines, int& num_freight_cars, int& num_passenger_cars, int& num_dining_cars, int& num_sleeping_cars){
total_weight = 0;
num_engines=0;
num_freight_cars=0;
num_passenger_cars=0;
num_dining_cars=0;
num_sleeping_cars=0;
while(train != NULL){
  if(train->isEngine()){
    num_engines+=1;
  }
  if(train->isFreightCar()){
    num_freight_cars+=1;
  }
  if(train->isPassengerCar()){
    num_passenger_cars+=1;
  }
  if(train->isDiningCar()){
    num_dining_cars+=1;
  }
  if(train->isSleepingCar()){
    num_sleeping_cars+=1;
  }
  total_weight+= train->getWeight();

  train = train->next;

}



}
/*
This is the helper function that we must ti add to make the helper function WORK
I go though the trains, calculate the total wright, than calculate the speed according to the given formular.
*/

float CalculateSpeed(TrainCar* train){
  float result =0;
  float total_E, total_W, total_H;
  total_E=0; total_W=0; total_H =0;
  while(train != NULL){
    if(train->isEngine()){
      total_E +=1;
    }
    total_W += train->getWeight();
    train = train->next;
  }
  total_H = total_E*3000;
  result = (total_H/total_W)*9.375;
  //since if we directly use the function in the pdf, overflow will happen
  //so, we calculate the coefficient and use it over here
  return result;
}

/*
This is the helper function that we must ti add to make the helper function WORK
I go though the trains, calculate the total distance, then compute the average
*/
float AverageDistanceToDiningCar(TrainCar* train){
  std::vector<int> all_distance;
  std::vector<int> all_engine;
  int index = 0;
  int dinning =0;
  float sum = 0;
  float result=0;
  while(train != NULL){
    if(train->isDiningCar())
    dinning = index;
    if(train->isPassengerCar()){
      all_distance.push_back(index);
    }
    if(train->isEngine()){
      all_engine.push_back(index);
    }
    index +=1;
    train = train->next;
  }
  for(unsigned int e=0;e<all_engine.size();e++){
    if(all_engine[e]>all_distance[0] && all_engine[e]<all_distance[all_distance.size()-1])
    return -1;
  }

  for(unsigned int i=0;i<all_distance.size();i++){
    all_distance[i]= std::abs(dinning-all_distance[i]);
    sum += all_distance[i];
  }
  result = sum/(all_distance.size());
  return result;

}


/*
This is the helper function that we must ti add to make the helper function WORK
I go though the trains, if we find a number is less than te min distance, we will store it in min
*/
int ClosestEngineToSleeperCar(TrainCar* train){
  int index = 0;
  std::vector<int> all_engine;
  std::vector<int> all_sleep;
  while(train != NULL){
    if(train->isEngine()){
      all_engine.push_back(index);
    }
    if(train->isSleepingCar()){
      all_sleep.push_back(index);
    }

    train = train->next;
    index += 1;
  }
  int  MIN = 999;
  for(unsigned int i = 0; i< all_sleep.size(); i++){
    for(unsigned int t = 0; t< all_engine.size();t++){
      if (std::abs(all_sleep[i]-all_engine[t])<MIN)
      MIN = std::abs(all_sleep[i]-all_engine[t]);
    }
  }

return MIN;
}
/*
This is the ship Frieight function that I wrote.
Each train I created will have only one engine.
I will keep adding it till it reach the max speecd
if it reach the max speed, I will store the train into the vector of train
finally we will return the train.
This solution is the best because it can optimazing the one_eingine train.
It can make sure the spped of each train is just around the min speed requirement, which means optimazing

*/
std::vector<TrainCar*> ShipFreight(TrainCar* &all_engines,TrainCar* &all_freight,int min_S,int max_T){
  int current_L = 0;
  int total_weight = 0;
  std::vector<TrainCar*> TRAIN;
  int F_weight = 0;

  while(all_engines != NULL && all_freight != NULL){
    total_weight = 0;
    current_L =0;
    TrainCar* OUT = NULL;


    TrainCar* IN = all_engines;

    all_engines = all_engines->next;;
    if(all_engines != NULL)
      all_engines->prev = NULL;
    IN->next = NULL;
    PushBack(OUT, IN);

    current_L += 1;
    total_weight += 150;
    if (all_freight != NULL)
    F_weight = all_freight->getWeight();
    float max_weight = (3000*9.375)/min_S;


    while (all_freight != NULL && max_weight> (total_weight+F_weight) && (((9.375*3000)/((float)total_weight+F_weight))>(float)min_S)  && current_L<=max_T){

      current_L += 1;
      total_weight += all_freight->getWeight();

      TrainCar* IN = all_freight;
      all_freight = all_freight->next;;
      if(all_freight != NULL)
        all_freight->prev = NULL;
      IN->next = NULL;
      PushBack(OUT, IN);
      if (all_freight!= NULL)
      F_weight = all_freight->getWeight();


    }



    TRAIN.push_back(OUT);

  }
    return TRAIN;
}

/*
This is the Seperate function I wrote;
At first, I go though all  the  list and compute and gethering the data that we need
Then, we do the optimainzg things.
Since engines are the most hesviest things,  I will take engines as the priority.
 We used the datas that we gather  to make sure that the enginees on each side is balancees.
if  not, we wil see the conditions , and use my own helper function switch_train to do the switching things

This solution is optimal because the emgines on each side is balaneces( Since engine is the most heavy thing and it can boost speed of  the trains)
*/


void Separate(TrainCar* &train1,TrainCar* &train2,TrainCar* &train3){
    int num_engines = 0;
    TrainCar* Fir_head = train1;
    while(train1 != NULL){
      num_engines += 1;
      train1 = train1->next;
    }
    train1 = Fir_head;

    int num_to_sep =num_engines/2;

    int index = 1;
    while( index != num_to_sep){
      train1 = train1->next;
      index += 1;
    }

    TrainCar* Sec_head = train1->next;
    train2 = Fir_head;
    train3 = Sec_head;
    train1 = NULL;


    TrainCar* Fir_tail = train3->prev;
    train3->prev->next = NULL;
    if (Fir_head->prev == NULL)
    train3->prev = NULL;

    int Snum_E = 0;
    int Fnum_E = 0;
    while(train2 != NULL){
      if(train2->isEngine())
      Fnum_E += 1;
      train2 = train2->next;

    }
    train2 = Fir_head;

    while(train3 != NULL){
      if(train3->isEngine())
      Snum_E += 1;
      train3 = train3->next;

    }
    train3 = Sec_head;

    TrainCar* First_const_tail = Fir_tail;


    std::cout<<"TTTTTTEEEEEEEEESSSSSSSTTTTTTTTTt"<<Snum_E<<"LLLLLLLOOOOOOLLLLLLL"<<Fnum_E<<std::endl;
    if(Sec_head->isEngine()){
      std::cout<<"ISISSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS"<<std::endl;
    }
    if(Fir_tail->isEngine()){
      std::cout<<"ISISSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS"<<std::endl;
    }
    if (Snum_E-Fnum_E == 2 && Sec_head->isEngine() && Sec_head->next-> isEngine()){
      train3= train3->next;
      train3->prev = NULL;
      Sec_head->prev = Fir_tail;
      Fir_tail->next = Sec_head;
      Sec_head->next = NULL;
      return;

    }

    while(Fir_tail != NULL && Sec_head != NULL && std::abs(Fnum_E-Snum_E)>1 ){
      if(Fnum_E < Snum_E){
        while(Fir_tail != NULL && Fir_tail->isEngine()){
          Fir_tail = Fir_tail->prev;
        }
        while(Sec_head != NULL && !Sec_head->isEngine() ){
          Sec_head = Sec_head->next;
        }
        switch_train (  Fir_tail,  Sec_head,  train3,  First_const_tail);
        Fnum_E += 1 ; Snum_E -= 1;
      }

      if(Snum_E < Fnum_E){
        while(Fir_tail != NULL && !Fir_tail->isEngine()){
          Fir_tail = Fir_tail->prev;
        }
        while(Sec_head != NULL && Sec_head->isEngine() ){
          Sec_head = Sec_head->next;
        }

       switch_train (  Fir_tail,  Sec_head,  train3,  First_const_tail);
      Snum_E += 1;  Fnum_E -= 1;

      }



    }




}
/*
This is my helper funcion to do the swtiching funcion on Seperate funcion
*/


void switch_train ( TrainCar* &Fir_tail, TrainCar* &Sec_head, TrainCar* &train3, TrainCar* &First_const_tail){
      if(Fir_tail->next == NULL && Fir_tail->prev!= NULL && Sec_head->next != NULL && Sec_head->prev != NULL){
      Fir_tail->prev->next = Sec_head;
      Sec_head->next->prev = Fir_tail;
      Sec_head->prev->next = Fir_tail;
      TrainCar* temp_p = Sec_head->prev;
      TrainCar* temp_n = Sec_head->next;
      Sec_head->prev = Fir_tail->prev;
      Sec_head->next = NULL;
      Fir_tail->next = temp_n;
      Fir_tail->prev = temp_p;
      First_const_tail = Sec_head;
}
    else  if(Fir_tail->next != NULL && Fir_tail->prev == NULL && Sec_head->next != NULL && Sec_head->prev != NULL){
      Fir_tail->next->prev = Sec_head;
      Sec_head->next->prev = Fir_tail;
      Sec_head->prev->next = Fir_tail;
      TrainCar* temp_p = Sec_head->prev;
      TrainCar* temp_n = Sec_head->next;
      Sec_head->prev = NULL;
      Sec_head->next = Fir_tail->next;
      Fir_tail->next = temp_n;
      Fir_tail->prev = temp_p;
}
    else  if(Fir_tail->next == NULL && Fir_tail->prev!= NULL && Sec_head->next != NULL && Sec_head->prev == NULL){
      Fir_tail->prev->next = Sec_head;
      Sec_head->next->prev = Fir_tail;
      TrainCar* temp_n = Sec_head->next;
      Sec_head->prev = Fir_tail->prev;
      Sec_head->next = NULL;
      Fir_tail->next = temp_n;
      Fir_tail->prev = NULL;
     train3 = Fir_tail;
      First_const_tail = Sec_head;
}
    else  if(Fir_tail->next != NULL && Fir_tail->prev!= NULL && Sec_head->next != NULL && Sec_head->prev == NULL){
      Fir_tail->next->prev = Sec_head;
      Fir_tail->prev->next = Sec_head;
      Sec_head->next->prev = Fir_tail;
      TrainCar* temp_n = Sec_head->next;
      Sec_head->prev = Fir_tail->prev;
      Sec_head->next = Fir_tail->next;
      Fir_tail->next = temp_n;
      Fir_tail->prev = NULL;
      train3 = Fir_tail;
}
    else  if(Fir_tail->next != NULL && Fir_tail->prev!= NULL && Sec_head->next != NULL && Sec_head->prev != NULL){
      Fir_tail->next->prev = Sec_head;
      Fir_tail->prev->next = Sec_head;
      Sec_head->next->prev = Fir_tail;
      Sec_head->prev->next = Fir_tail;
      TrainCar* temp_p = Sec_head->prev;
      TrainCar* temp_n = Sec_head->next;
      Sec_head->prev = Fir_tail->prev;
      Sec_head->next = Fir_tail->next;
      Fir_tail->next = temp_n;
      Fir_tail->prev = temp_p;
    }
}
// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//

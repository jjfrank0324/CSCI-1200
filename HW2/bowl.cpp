
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <algorithm>
using namespace std;
#include "Person.h"

int strike(std::vector<int> scores){
  int count =0;
  for (int i =0;i<scores.size();i++){
  if(scores[i]==10)
  count+=1;}
  return count;
}

bool AllNum(string str)//I create a method over here to see how to help me edit the later complicage code
 {
     for (unsigned int i = 0; i < str.size(); i++)
     {
         int tmp = (int)str[i];
         if (tmp >= 48 && tmp <= 57)
        {
            continue;
        }
        else
         {
             return false;
         }
     }
     return true;
}

//this is for  creating an well formated string for those scores
//to make it easier comput, I make several variables in this function to help me compute it
//since frame 10 is silghtly different, I will calculate it in different way
std::string compute_score(std::vector<int> scores){//a bunck of formatting things to make output easier
  int frame = 1;
  int count = 1;
  int hit = 0;
  std::string out;
  out +=' ';
  for(unsigned int i = 0; i< scores.size();i++)
  {  int num = scores[i];//over here, I concert the number into a String copied to make it easier to add
    std::stringstream ss;
    std::string NUM;
    ss<<num;
    ss>>NUM;

    if (hit + num< 10 && count ==1 && frame!= 10 && num == 0)
    {
      count+=1;
      hit+=num;
      out += '-';
      out += " ";
      continue;
    }
    if (hit + num< 10 && count ==1 && frame!= 10 && num != 0)
    {
      count+=1;
      hit+=num;
      out += NUM;
      out += " ";
      continue;
    }


    if (num == 10 && count ==1 && frame!= 10)
    {
      hit=0;
      out += "  X | ";
      frame +=1;
      continue;
    }

    if (hit + num< 10 && count ==2 && frame!= 10 && num != 0)
    {
      count=1;
      hit=0;
      out += NUM;
      out += " | ";
      frame +=1;
      continue;
    }
    if (hit + num< 10 && count ==2 && frame!= 10 && num == 0)
    {
      count=1;
      hit=0;
      out += '-';
      out += " | ";
      frame +=1;
      continue;
    }

    if (hit + num == 10 && count ==2 && frame!= 10 && num != 0)
    {
      count=1;
      hit=0;
      out += '/';
      out += " | ";
      frame +=1;
      continue;
    }






    if (hit + num< 10 && count ==1 && frame== 10 && num !=0)
    {
      count+=1;
      hit+=num;
      out += NUM;
      out += " ";
      continue;
    }
    if (hit + num< 10 && count ==1 && frame== 10 && num ==0)
    {
      count+=1;
      hit+=num;
      out += '-';
      out += " ";
      continue;
    }

    if (num == 10 && count ==1 && frame== 10)
    {
      hit=0;
      out += "X ";
      count +=1;
      continue;
    }

    if (hit + num< 10 && count ==2 && frame== 10 && num !=0)
    {
      hit=0;
      out += NUM;
      out += "   |";
      continue;
    }
    if (hit + num< 10 && count ==2 && frame== 10 && num ==0)
    {
      hit=0;
      out += "-";
      out += "   |";
      continue;
    }

    if (hit + num == 10 &&  num != 10 && count ==2 && frame== 10 && num !=0)
    {
      hit=0;
      out += "/ ";
      count +=1;
      continue;
    }

    if (hit + num == 10 &&  num == 10 && count ==2 && frame== 10)
    {
      hit=0;
      out += "X ";
      count +=1;
      continue;
    }
    if (hit + num == 10 &&  num == 10 && count ==3 && frame== 10)
    {
      hit=0;
      out += "X |";
      continue;
    }
    if (hit + num != 10 &&  num != 10 && count ==3 && frame== 10 && num !=0)
    {
      hit=0;
      out += NUM;
      out += " |";
      continue;
    }

  }
  return out;
}

// this fuction compute and return the total score
int compute_total(std::vector<int> scores){
   int frame = 1;
  int count = 1;
  int hit = 0;
  int out = 0;
  for(unsigned int i = 0; i< scores.size();i++)
  {  int num = scores[i];

    if (hit + num< 10 && count ==1 && frame!= 10)
    {
      count+=1;
      hit+=num;
      out += num;
      continue;
    }


    if (num == 10 && count ==1 && frame!= 10)
    {
      hit=0;
      out +=  (num+scores[i+1]+scores[i+2]);
      frame +=1;
      continue;
    }

    if (hit + num< 10 && count ==2 && frame!= 10)
    {
      count=1;
      hit=0;
      out += num;
      frame +=1;
      continue;
    }

    if (hit + num == 10 && count ==2 && frame!= 10)
    {
      count=1;
      hit=0;
      out += (num+scores[i+1]);
      frame +=1;
      continue;
    }

    if (frame== 10)
    {
      count+=1;
      hit+=num;
      out += num;
      continue;
    }

  }
  return out;
}

//this is for  creating the output string for the total
//to make it easier comput, I make several variables in this function to help me compute it
//since frame 10 is silghtly different, I will calculate it in different way
std::string output_total(std::vector<int> scores){
  int frame = 1;
  int count = 1;
  int hit = 0;
  int out = 0;
  std::string OUTPUT;
  for(unsigned int i = 0; i< scores.size();i++)
  {  int num = scores[i];

    if (hit + num< 10 && count ==1 && frame!= 10)
    {
      count+=1;
      hit+=num;
      out += num;
      continue;
    }


    if (num == 10 && count ==1 && frame!= 10)
    {
      hit=0;
      out +=  (num+scores[i+1]+scores[i+2]);
      frame +=1;
      std::stringstream ss;
      std::string NUM;
      ss<<out;
      ss>>NUM;

      int space_num = (4-NUM.size());
      std::string space (space_num,' ');



    OUTPUT += (space+NUM+" |");
      continue;
    }

    if (hit + num< 10 && count ==2 && frame!= 10)
    {
      count=1;
      hit=0;
      out += num;
      frame +=1;
        std::stringstream ss;
        std::string NUM;
        ss<<out;
        ss>>NUM;
        int space_num = (4-NUM.size());
        std::string space (space_num,' ');



      OUTPUT += (space+NUM+" |");
      // OUTPUT += ("   "+NUM+" |");

      continue;
    }

    if (hit + num == 10 && count ==2 && frame!= 10)
    {
      count=1;
      hit=0;
      out += (num+scores[i+1]);
      frame +=1;

      std::stringstream ss;
      std::string NUM;
      ss<<out;
      ss>>NUM;
      int space_num = (4-NUM.size());
      std::string space (space_num,' ');

    OUTPUT += (space+NUM+" |");
      continue;
    }

    if (frame== 10 )
    {
      count+=1;
      hit+=num;
      out += num;

      continue;
    }


  }

    std::stringstream ss;
    std::string NUM;
    ss<<out;
    ss>>NUM;
    int space_num = (6-NUM.size());
    std::string space (space_num,' ');



    OUTPUT += (space+NUM+" |");
  //OUTPUT += ("   "+NUM+" |");
  return OUTPUT;


}



int main(int argc, char* argv[])
{   ifstream infile;// at the begining, I put all the things in the file into a list
    std::string txt;
    std::string t1;
    infile.open(argv[1]);
    vector<std::string> all_words;
    vector<std::string> f_name;
    vector<std::string> l_name;

    while(infile>>t1)
    {
    all_words.push_back(t1);
    }

    vector<std::string> all_name;
    vector<std::string> name_l;
    vector< vector<int> > all_stat;
    vector<int> indi_stat;//this is the statistics vectors for all the players
    for(unsigned int i =0;i< all_words.size();i++){
      if(! AllNum(all_words[i]))
      {all_name.push_back(all_words[i]);}
      if (AllNum(all_words[i]) && AllNum(all_words[i+1]) )
      {int num;
        num = atoi(all_words[i].c_str());
      indi_stat.push_back(num);
      }
      if (AllNum(all_words[i]) && !AllNum(all_words[i+1]) )
      {int num;
      num = atoi(all_words[i].c_str());
      indi_stat.push_back(num);
      all_stat.push_back(indi_stat);
      indi_stat.clear();
      }
    }
    all_stat.push_back(indi_stat);

    int count = 1;//putting all the name into the name_list, first_namelist and the last_name list
    std::string indi_name;
    for(unsigned int i=0; i<all_name.size(); i++)
    {
      if (count ==1)
      {indi_name = all_name[i];
      indi_name += ' ';
       count +=1;
      l_name.push_back(all_name[i]);
    }
      else
      {indi_name += all_name[i];
       name_l.push_back(indi_name);
       indi_name="";
       count -=1;
      f_name.push_back(all_name[i]);
       }
    }

    vector<Person> Person_list;// creating the person vector and store all the info into the person
    for(unsigned int i=0;i<f_name.size();i++)
    {
      Person PP(f_name[i],l_name[i],all_stat[i],0);
      Person_list.push_back(PP);
    }


    sort(Person_list.begin(),Person_list.end(),lower_name);//sort their name

    int max_name = name_l[0].size();
    for(int i =0; i<name_l.size();i++)
    {
      if(name_l[i].size()>max_name)
      max_name=name_l[i].size();
    }


    ofstream OUT;//Here we create an output file to output those string
    OUT.open(argv[2]);
    std::string heading(4+max_name+compute_score(Person_list[0].getscores()).size(),'-');

    OUT<<heading<<"\n";
    for(int i=0;i<Person_list.size();i++)
    {
      std::string name_space(max_name-Person_list[i].getname().size(),' ');
      std::string empty_space(max_name,' ');
      OUT<<"| "<<Person_list[i].getname()<<name_space<<" |";

      OUT<<compute_score(Person_list[i].getscores())<<"\n";

      OUT<<"| "<<empty_space<<" |";
      OUT<<output_total(Person_list[i].getscores())<<"\n";
      OUT<<heading<<"\n";

      Person_list[i].set_totalscores(compute_total(Person_list[i].getscores()));
    }

    OUT<<"\n";
    sort(Person_list.begin(),Person_list.end(),lower_score);
    for(int i=0;i<Person_list.size();i++){
    std::string name_space(max_name-Person_list[i].getname().size(),' ');
    if(Person_list[i].gettotal_scores()>100)
    OUT<<Person_list[i].getname()<<name_space<<"  "<<Person_list[i].gettotal_scores()<<"\n";
    else if(Person_list[i].gettotal_scores()>10)
    OUT<<Person_list[i].getname()<<name_space<<"   "<<Person_list[i].gettotal_scores()<<"\n";
    else
    OUT<<Person_list[i].getname()<<name_space<<"    "<<Person_list[i].gettotal_scores()<<"\n";
    }
    std::string word = argv[3];
    if(word=="custom")
{ cout<<"here";
  std::string MOST;
  int stk=0;
  for(int i=0;i<Person_list.size();i++){
    cout<<(strike(Person_list[i].getscores()))<<endl;
  if (strike(Person_list[i].getscores())>stk){
    cout<<"it is in it "<<endl;
    stk=strike(Person_list[i].getscores());
    cout<<stk<<endl;
    MOST=Person_list[i].getname();
  }
}
cout<<stk<<endl;
OUT<<"WOW "<<MOST<<" is really go at this!"<<"he/she got "<<stk<<" strike!!"<<". He/she actually get the most strike!";
  }
  infile.close();
  OUT.close();
}

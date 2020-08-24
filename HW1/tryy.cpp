#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[])
{
    std::string order = argv[4];
    int Len = atoi(argv[3])+4;
    std::string Head(Len, '-');
//Over here, take it all the inputs and save it somewhere

    ofstream OUT;
    OUT.open(argv[2]);
    OUT<<Head<<"\n";
    //print the headline of the program
    //take all the inputs and save them all into a vector array
    ifstream infile;
    std::string txt;
    std::string t1;
    infile.open(argv[1]);
    vector<std::string> words_L;
    while(infile>>t1)             //?????,???????
{
    words_L.push_back(t1);
}

//this is the first part of the work. flush flush_left
//I write into the file line by Line
//I use for loops for the words array and check the proper conditions
//using words to form a line first, then write the into the file, then continue use the rest of the words
if (order == "flush_left")
{
  int total_L = 4;
  std::string Line ;

  for (int i = 0; i<words_L.size();i++)
  {
    if ((3+Line.size()+words_L[i].size())<Len)
    {
      Line += (words_L[i]+' ');
    }
    else
    {

        std::string Space (Len-3-Line.size(),' ');
        Line += Space;
        OUT<<"| "<<Line<<"|"<<"\n";
        Line=words_L[i]+' ';
    }
  }
  std::string Space (Len-3-Line.size(),' ');
  Line += Space;
  OUT<<"| "<<Line<<"|"<<"\n";
}



//This is similar to the flush_left except for several minor formating setting change
if (order == "flush_right")
{
  int total_L = 4;
  std::string Line ;

  for (int i = 0; i<words_L.size();i++)
  {
    if ((4+Line.size()+words_L[i].size())<Len)
    {
      Line += (words_L[i]+' ');
    }
    else
    {
      std::string Space (Len-4-Line.size()+1,' ');
      Line = Space+Line;
      OUT<<"| "<<Line<<"|"<<"\n";
      Line=words_L[i]+' ';
    }
  }
  std::string Space (Len-4-Line.size()+1,' ');
  Line = Space+Line;
  OUT<<"| "<<Line<<"|"<<"\n";
}

//this is the last and the hardeset part
//I use if statement to seperate the super-long words cases from the normal _Jv_RegisterClasses
//if i meet the super long word, I will seperate it, write part of it on the file, then store it back to the word words array(that's why i use 1-- in line 132)
// It looks kind of complicate, but all the things i am donig over here is adjusting, adjusting, and adjusting
//everthing is for the perfect format

if (order == "full_justify")
{ std::string Line;
  std::string new_word;
  vector<std::string> words;
  int sentence_L= 0;
  for (int i = 0; i<words_L.size();i++)
  { if(words_L[i].size()> Len-4)
    {

      if (words.size()>0)
      {  for (int j = 0; j<words.size();j++)
              {Line += (words[j]+' ') ;}
              std::string Space (Len-4-Line.size(),' ');
              Line += Space;
              OUT<<"| "<<Line<<" |"<<"\n";
              words.clear();
              Line="";}
        new_word="";
        Line+="| ";
        for (int j =0;j<Len-4-1;j++)
        {
          Line+=words_L[i][j];
        }
        Line +="- |" ;
        OUT<<Line<<"\n";
        Line = "";
        for (int k=Len-4-1;k<words_L[i].size();k++)
        {
          new_word+=words_L[i][k];
        }
        words_L[i]=new_word;
        i-=1;
    }

    else{
      //std::cout<<words[0]<<"FIRSR INN WORDS0"<<words_L[i]<<"  sentence_L  "<<std::endl;
    if ((3+  sentence_L+words_L[i].size()+words.size())<Len)
    {
      words.push_back(words_L[i]);
      sentence_L += (words_L[i].size());
    }
    else
    {if (words.size()==1)
      {
        std::string Space(Len-3-words[0].size(),' ');
        Line+= words[0]+Space;
        OUT<<"| "<<Line<<" |"<<"\n";
      }
                if (words.size()>1){
                int Space_num = (Len - 4 - sentence_L)/(words.size()-1);
                std::cout<<"Space_num is"<<Space_num<<words[0]<<std::endl;
                int Diff = Len-Space_num*(words.size()-1)-sentence_L-4;
                  std::cout<<"Diff is"<<Diff<<words[0]<<std::endl;
                for (int j = 0; j< words.size();j++)
                {if (Diff!=0)
                  {words[j]+=' ';
                  Diff-=1;}
                if (j==(words.size()-1))
                {
                  words[j]+= "";
                }
                 else{
                   std::string Space(Space_num,' ');
                   words[j]+= Space;
                 }
                }

                for (int o = 0; o< words.size();o++)
                { Line += words[o];}
                OUT<<"| "<<Line<<" |"<<"\n";}
      words.clear();
      words.push_back(words_L[i]);
      Line="";
      sentence_L = (words_L[i].size());
      int Space_num=0;
      }
    }
  }
  if(words.size()>0)
          {for (int j = 0; j<words.size();j++)
          {Line += (words[j]+' ') ;}
          std::string Space (Len-3-Line.size(),' ');
          Line += Space;
        OUT<<"| "<<Line<<"|"<<"\n";}
}


  OUT<<Head;
infile.close();
OUT.close();
return 0;
}

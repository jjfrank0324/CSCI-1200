
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


//I create a method over here to see how to help me edit the later complicage code

bool AllNum(string str)
{     for (unsigned int i = 0; i < str.size(); i++)
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

string int_to_str(int a)
{
  stringstream ss;
  ss << a;
  string str = ss.str();
  return str;

}

// this funcion is used to help us quickly determine the len of the ship
int LEN( string ship)
{
  if (ship == "submarine")
    return 1;
  if (ship == "destroyer")
    return 2;
  if (ship == "cruiser")
    return 3;
  if (ship == "battleship")
    return 4;
  if (ship == "carrier")
    return 5;
  if (ship == "cargo")
    return 6;
  if (ship == "tanker")
    return 7;
  if (ship == "unknown")
    return 999;
}

int get_Ver_ship(vector<vector<string> >  board, int col)
{ int out = 0;
  for(unsigned int i =0; i< board.size(); i++)
  {
    if(board[i][col] != " ")
      out += 1;
  }
  return out;
}

int get_Hor_ship(vector<vector<string> >  board, int row)
{ int out = 0;
  for(unsigned int i =0; i< board[0].size(); i++)
  {
    if(board[row][i] != " ")
      out += 1;
  }
  return out;
}
// // void P_board(string** board)
// {
//   for(unsigned int i =0; i< board.size(); i++)
//     for(unsigned int j =; j<board.size(),j++)
//       {
//         cout<< board[i][j];
//       }
//     cout<<endl;
// }

bool check_around(vector<vector<string> >  board, int i, int j)
{
  int row = board.size();
  int col = board[0].size();

  bool judge = true;
  if(i-1>=0)
  {
    if(board[i-1][j] != " ")
      return false;
  }
  if(i-1>=0 && j-1 >= 0)
  {
    if(board[i-1][j-1] != " ")
      return false;
  }
  if(i-1>=0 && j<= col-2)
  {
    if(board[i-1][j+1]!= " ")
      return false;
  }
  if( j-1 >= 0)
  {
    if(board[i][j-1]!= " ")
      return false;
  }
  if(j <= col-2)
  {
    if(board[i][j+1]!= " ")
      return false;
  }
  if(i  <= row-2 )
  {
    if(board[i+1][j] != " ")
      return false;
    if(j-1>= 0 )
    {
      if(board[i+1][j-1]!= " ")
        return false;
    }
    if(j <= col-2)
      {
        if(board[i+1][j+1] != " ")
          return false;
      }
  }
  return judge;
}



bool check_neighbor_ver(string ship,  vector<vector<string> >  board, int i, int j)
{
  int Len = LEN(ship);
  int row = board.size();
  int col = board[0].size();
  bool judge = true;

  for(unsigned int o = 0; o<Len; o++)
  {
    if(! check_around(board, i+o , j))
      return false;

  }
  return judge;
}



bool check_neighbor_hor(string ship,  vector<vector<string> >  board, int i, int j)
{
  int Len = LEN(ship);
  int  row = board.size();
  int col = board[0].size();
  bool judge = true;

  for(unsigned int o = 0; o<Len; o++)
  {
    if(! check_around(board, i , j+o))
      return false;
  }

  return judge;
}


// the return things is a list of ID of the grid which cannot be directly used
vector<int> find_ver_point(string ship, vector<int> row_ship, vector<int> col_ship, int rows, int cols, vector<vector<string> >  board)
{
  vector<int> result;
  int ship_L= LEN(ship);
  //cout<<"Len of the ship is"<<ship_L<<endl;
  for ( unsigned int i = 0; i<board.size(); i++)
    {
      for(unsigned int j =0; j< board[0].size(); j++)
      {
        bool judge = true;
        if ((i+ship_L)>rows)
          judge = false;
        if(judge == true)
        {
          for(unsigned int k = 0; k<ship_L; k++)
          {
            if(board[i+k][j] != " ")
              judge = false;
          }
        }
        if(judge == true)
        {
          //cout<<get_Ver_ship(board,j)+ship_L<<"current num of ship is"<<endl;
          if((get_Ver_ship(board,j)+ship_L)> col_ship[j])
            judge = false;
        }
        if(judge == true)
        {
          for(unsigned int k = 0; k<ship_L; k++)
          {
            if(get_Hor_ship(board, i+k)+1 > row_ship[i+k])
              judge = false;
          }
        }
        if(judge == true)
        {
          if(!check_neighbor_ver(ship, board, i, j ))
            judge = false;
        }
        if (judge == true)
          {
            result.push_back(i*cols+j);
            //cout<<i*cols+j<<"<- ID is an valid place for adding the ship"<<endl;
          //  cout<<i<<j<<endl;
          }
      }
    //  cout<<"to the next row"<<endl;
    }
  return result;
}

vector<int> find_hor_point(string ship, vector<int> row_ship, vector<int> col_ship, int rows, int cols, vector<vector<string> >  board)
{
  vector<int> result;
  int ship_L= LEN(ship);
  //cout<<"Len of the ship is"<<ship_L<<endl;
  for ( unsigned int i = 0; i<board.size(); i++)
    {
      for(unsigned int j =0; j< board[0].size(); j++)
      {
        bool judge = true;
        if ((j+ship_L)>cols)
          judge = false;
        if(judge == true)
        {
          for(unsigned int k = 0; k<ship_L; k++)
          {
            if(board[i][j+k] != " ")
              judge = false;
          }
        }
        if(judge == true)
        {
          //cout<<get_Ver_ship(board,j)+ship_L<<"current num of ship is"<<endl;
          if((get_Hor_ship(board,i)+ship_L)> row_ship[i])
            judge = false;
        }
        if(judge == true)//start here
        {
          for(unsigned int k = 0; k<ship_L; k++)
          {
            if(get_Ver_ship(board, j+k)+1 > col_ship[j+k])
              judge = false;
          }
        }
        if(judge == true)
        {
          if(!check_neighbor_hor(ship, board, i, j ))
            judge = false;
        }
        if (judge == true)
          {
            result.push_back(i*cols+j);
          //  cout<<i*cols+j<<"<- ID is an valid place for adding the ship"<<endl;
          //  cout<<i<<j<<endl;
          }
      }
    //  cout<<"to the next row"<<endl;
    }
  return result;
}


void print_board(vector<vector<string> >  board, vector<int> row_ship, vector<int> col_ship)
{
  int row = board.size();
  int col = board[0].size();
  string head(col,'-');
  head='+'+head+'+';
  cout<<head<<endl;
  for(unsigned int i =0; i < board.size(); i++)
  { cout<<"|";
    for(unsigned int j = 0; j< board[0].size(); j++)
    {
        cout<<board[i][j];
    }
    cout<<"|"<<row_ship[i]<<endl;
  }
  cout<<head<<endl;
  cout<<" ";
  for(unsigned int j = 0; j< board[0].size(); j++)
  {
    cout<<col_ship[j];
  }
  cout<<" "<<endl;
}




void add_hor_ship(string ship ,int ID, vector<vector<string> > & board)
{
  int ship_L = LEN(ship);
  int row_num = ID/board[0].size();
  int col_num = ID-(row_num*board[0].size());
  if(ship_L == 1 )
  {
    board[row_num][col_num] = 'o';
  }
  if(ship_L == 2 )
  {
    board[row_num][col_num]='<';
    board[row_num][col_num+1]='>';
  }
  if(ship_L == 3 )
  {
    board[row_num][col_num]='<';
    board[row_num][col_num+1]='X';
    board[row_num][col_num+2]='>';
  }
  if(ship_L == 4 )
  {
    board[row_num][col_num]='<';
    board[row_num][col_num+1]='X';
    board[row_num][col_num+2]='X';
    board[row_num][col_num+3]='>';
  }
  if(ship_L == 5 )
  {
    board[row_num][col_num]='<';
    board[row_num][col_num+1]='X';
    board[row_num][col_num+2]='X';
    board[row_num][col_num+3]='X';
    board[row_num][col_num+4]='>';
  }
  if(ship_L == 6 )
  {
    board[row_num][col_num]='<';
    board[row_num][col_num+1]='X';
    board[row_num][col_num+2]='X';
    board[row_num][col_num+3]='X';
    board[row_num][col_num+4]='X';
    board[row_num][col_num+5]='>';
  }
  if(ship_L == 7 )
  {
    board[row_num][col_num]='<';
    board[row_num][col_num+1]='X';
    board[row_num][col_num+2]='X';
    board[row_num][col_num+3]='X';
    board[row_num][col_num+4]='X';
    board[row_num][col_num+5]='X';
    board[row_num][col_num+6]='>';
  }
}

void add_ver_ship(string ship ,int ID, vector<vector<string> > & board)
{
  int ship_L = LEN(ship);
  int row_num = ID/board[0].size();
  int col_num = ID-(row_num*board[0].size());
  // int row_num = ID/board.size();
  // int col_num = ID-(row_num*board[0].size());
  if(ship_L == 1 )
  {
    board[row_num][col_num] = 'o';
  }
  if(ship_L == 2 )
  {
    board[row_num][col_num]='^';
    board[row_num+1][col_num]='v';
  }
  if(ship_L == 3 )
  {
    board[row_num][col_num]='^';
    board[row_num+1][col_num]='X';
    board[row_num+2][col_num]='v';
  }
  if(ship_L == 4 )
  {
    board[row_num][col_num]='^';
    board[row_num+1][col_num]='X';
    board[row_num+2][col_num]='X';
    board[row_num+3][col_num]='v';
  }
  if(ship_L == 5 )
  {
    board[row_num][col_num]='^';
    board[row_num+1][col_num]='X';
    board[row_num+2][col_num]='X';
    board[row_num+3][col_num]='X';
    board[row_num+4][col_num]='v';
  }
  if(ship_L == 6 )
  {
    board[row_num][col_num]='^';
    board[row_num+1][col_num]='X';
    board[row_num+2][col_num]='X';
    board[row_num+3][col_num]='X';
    board[row_num+4][col_num]='X';
    board[row_num+5][col_num]='v';
  }
  if(ship_L == 7 )
  {
    board[row_num][col_num]='^';
    board[row_num+1][col_num]='X';
    board[row_num+2][col_num]='X';
    board[row_num+3][col_num]='X';
    board[row_num+4][col_num]='X';
    board[row_num+5][col_num]='X';
    board[row_num+6][col_num]='v';
  }
}

bool equal_board(vector<vector<string> >  a, vector<vector<string> >  b)
{
  for(unsigned int i =0; i< a.size(); i++)
    {
      for(unsigned int j =0; j < a[0].size();j++)
        {
          if(a[i][j] != b[i][j])
            return false;
        }
    }
    return true;
}

void erase_duplicate(vector<vector<vector<string> > > &solutions,vector<vector<string> > &all_sol)
{
  for(unsigned int i =0; i< solutions.size()-1; i++)
  {
    for(unsigned int j =i+1; j< solutions.size(); j++)
    {
      if(equal_board(solutions[i],solutions[j]))
      {
        solutions.erase(solutions.begin()+i);
        all_sol.erase(all_sol.begin()+i);
        i-=1;
        break;

      }
      // if(judge == false)
      // { //cout<<"BIIIIIIIIIIIIIIIII erasing!"<<endl;
      //   solutions.erase(solutions.begin()+i);
      //   all_sol.erase(all_sol.begin()+i);
      //   i-=1;
      //   break;
      // //  cout<<"SUCCESSFULLY errase! "<<endl;
      // }
    }
    // if(judge == true)
    // { //cout<<"BIIIIIIIIIIIIIIIII erasing!"<<endl;
    //   solutions.erase(solutions.begin()+i);
    //   all_sol.erase(all_sol.begin()+i);
    //   i-=1;
    //  cout<<"SUCCESSFULLY errase! "<<endl;
    }

}



void find_solutions(vector<vector<vector<string> > > &solutions,
    vector<vector<string> > board,
    const vector<int> row_ship, const vector<int> col_ship,   vector<string> all_ship,
    int ID, vector<string> temp_sol, vector<vector<string> > &all_sol, string marking
    , int direction_indicator)
    {
      int rows = board.size();
      int cols = board[0].size();

      if(direction_indicator == 1) // should be added horizontall
      {
        add_hor_ship(all_ship[0], ID, board);
        all_ship.erase(all_ship.begin());
      }

      if(direction_indicator == 0)// should be added vertically
      {
        add_ver_ship(all_ship[0], ID, board);
        all_ship.erase(all_ship.begin());
      }
      //print_board(board, row_ship, col_ship);


      if(marking != "")
      {
        temp_sol.push_back(marking);
      }



      if (all_ship.size() != 0)
      {
        vector<int> hor_point = find_hor_point(all_ship[0], row_ship, col_ship,rows, cols ,board);
      //  cout<<"finish finding horozontal points"<<endl;
        vector<int> ver_point;
        if(all_ship[0] != "submarine")
        ver_point = find_ver_point(all_ship[0], row_ship, col_ship,rows, cols ,board);
        if(all_ship[0] != "submarine")
        {
          if( hor_point.size() == 0 && ver_point.size() == 0)
            {
              return;
            }
        }
        if(all_ship[0] == "submarine")
        {
          if(hor_point.size() == 0 )
            {
              return;
            }
        }

        for(unsigned int i = 0; i<hor_point.size(); i++)
          {
            string marking = all_ship[0];
            for(unsigned int k =0; k< 11-all_ship[0].size(); k++)
              marking += " ";
            ID = hor_point[i];
            int row_num = ID/board[0].size();
            int col_num = ID-(row_num*board[0].size());
            marking += (int_to_str(row_num) + " "+ int_to_str(col_num) + " horizontal");

            find_solutions(solutions, board, row_ship, col_ship, all_ship, ID, temp_sol, all_sol, marking,1);
          }
          if(all_ship[0] != "submarine")
          {
          for(unsigned int i = 0; i<ver_point.size()  ; i++)
            {
              string marking = all_ship[0];
              for(unsigned int k =0; k< 11-all_ship[0].size(); k++)
                marking += " ";
              ID = ver_point[i];
              int row_num = ID/board[0].size();
              int col_num = ID-(row_num*board[0].size());
              marking += (int_to_str(row_num) + " "+ int_to_str(col_num) + " vertical" );

              find_solutions(solutions, board, row_ship, col_ship, all_ship, ID, temp_sol, all_sol, marking,0);
            }

          }
      }
      else
      {
        all_sol.push_back(temp_sol);
        solutions.push_back(board);

      }



    }


bool sorting_helper(string shipa, string shipb)
{
 int a_len = LEN(shipa);
 int b_len = LEN(shipb);
 return a_len > b_len;
}


int main(int argc, char* argv[])
{
  string order;
  if (argc>2)
  order = argv[2];


  ifstream infile;
  string text;
  vector<string> all_words;
  vector<int> row_ship;
  vector<int> col_ship;
  vector<string> all_ship;
  vector<int> ship_len;
  vector<vector<string> > constrain;
  int rows = 0;
  int cols = 0;
  infile.open(argv[1]);
  infile>>text;
  infile>>rows;
  infile>>cols;
  infile>>text;
  int num = 0;
  for(unsigned int i = 0; i<rows; i++ )
  {
    infile>>text;
    if(!AllNum(text))
    {
      num = -1;
    }
    else
    {
      num =  atoi(text.c_str());
    }
    row_ship.push_back(num);
  //  cout<<num<<endl;
  }
  infile>>text;
  //cout<<"finish phase one; WoW, good for frank"<<endl;
  for(unsigned int j = 0; j<cols; j++ )
  {
    infile>>text;
    if(!AllNum(text))
    {
      num = -1;
    }
    else
    {
      num =  atoi(text.c_str());
    }
    col_ship.push_back(num);
    //cout<<num<<endl;
  }

  while(infile>>text)
  {
    if(text == "constraint")
    break;
    else
    all_ship.push_back(text);
  //  cout<<text<<endl;
  }
  if(text =="constraint")
  { vector<string> temp_constrain;
    int count = 0;
    while(infile>>text)
    {
      if(count<3)
        {
          temp_constrain.push_back(text);
          count += 1;
        //  cout<<text<<endl;
        }
      else
      {
        count = 0;
        constrain.push_back(temp_constrain);
        temp_constrain.clear();
      }
    }
    constrain.push_back(temp_constrain);
  }
  //cout<<constrain.size()<<"the size is"<<endl;
// all the code above is doing the things taking in all the inputs



vector<vector<string> > board; //creates a 9*9 matrix or a 2d array.
//string board[rows][cols];

for(int i=0; i<rows; i++)    //This loops on the rows.
{
  vector <string> TEMP ;
  for(int j=0; j<cols; j++) //This loops on the columns
  {
    TEMP.push_back( " "); //you can also connect to the file
    //and place the name of your ifstream in the input after opening the file will
    //let you read from the file.
  }
  board.push_back(TEMP);
}
// P_board(board);

// for(unsigned int i =0; i< rows; i++)
// {
//   for(unsigned int j =0 ; j<cols;j++)
//     {
//       cout<< board[i][j];
//     }
//   cout<<endl;
// }

// cout<<all_ship[1]<< " length is" << LEN(all_ship[1])<<endl;
//    cout<<"WoW: here is the constrain"<<endl;

// {
//   for(unsigned int i=0; i<3; i++)
//     {
//       infile>>text
//       temp_constrain.push_back(text);
//     }
// // }
// board[0][0] = 'A';
// vector<int> LOL = find_hor_point(all_ship[2], row_ship, col_ship,rows, cols ,board);
// cout<<board.size()<<board[0][0]<<endl;
// print_board(board, row_ship, col_ship);
// add_hor_ship("cargo",8,board);
// add_ver_ship("carrier",16,board);
// print_board(board, row_ship, col_ship);
// vector<vector<vector<string> > > all_sol;
// cout<<"LLLLLLLLLLLIIIIIIINNNNNNNNNNNNNNNNEEEEEEEE";
// all_sol.push_back(board);
// all_sol.push_back(board);
// all_sol.push_back(board);
// all_sol.push_back(board);
// all_sol.push_back(board);
// all_sol[1][0][0]="F";
// all_sol[2][0][0]="U";
// all_sol[3][0][0]="C";
// erase_duplicate(all_sol);
// for(unsigned int i = 0; i< all_sol.size();i++)
// {
//   print_board(all_sol[i], row_ship, col_ship);
// }
// cout<<"the board size after we clear it is"<< board.size()<<endl;
// std::string AAA(10,'1');
// cout<<AAA;
// cout<< "finished all the testing! start solving the puzzle"<<endl;
//
//
vector<vector<vector<string> > > solutions;



int ID = -1;
vector<string> temp_sol;
vector<vector<string> > all_sol;
string marking = "";
int direction_indicator = -1;
std::sort(all_ship.begin(),all_ship.end(),sorting_helper);
find_solutions(solutions, board, row_ship, col_ship, all_ship
              , ID, temp_sol, all_sol, marking, direction_indicator );

// cout<<all_ship[0];
//cout<<"EEEEEEENNNNNNNDDDDDDDDDD"<<endl;
//cout<<"there is so mamy solutions->"<< solutions.size();

erase_duplicate(solutions, all_sol);
if (order == "find_all_solutions")
{
    for(unsigned int i =0; i< solutions.size();i++)
  {
    cout<< "Solution: "<<endl;
    for(unsigned int k =0; k< all_sol[0].size();k++)
      cout<<all_sol[i][k]<<endl;
    print_board(solutions[i], row_ship, col_ship);
   cout<<endl;
  }

    cout<<"Found "<<solutions.size()<<" solution(s)";
}
else
  {
    cout<< "Solution: "<<endl;
    for(unsigned int k =0; k< all_sol[0].size();k++)
      cout<<all_sol[0][k]<<endl;
    print_board(solutions[0], row_ship, col_ship);
  }

// print_board(solutions[6], row_ship, col_ship);
// cout<<equal_board(solutions[0],solutions[])<<endl;
//

return 1;

}

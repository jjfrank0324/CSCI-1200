
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <algorithm>
#include <ctime>
using namespace std;

//Reading tips,the main recursing function is start from Line 671


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
//this is the helper function which mark all the grid around [i][j] as N,
 // (N means that we cannot add points at those point, and we will stop checking
 //the adding conditions if the points is already being marked as N)
void mark_around(vector<vector<string> > &board, int i, int j )
{
  int row = board.size();
  int col = board[0].size();

  bool judge = true;
  if(i-1>=0)
  {
    board[i-1][j] = "N";
  }
  if(i-1>=0 && j-1 >= 0)
  {
    board[i-1][j-1] = "N";
  }
  if(i-1>=0 && j<= col-2)
  {
    board[i-1][j+1] = "N";
  }
  if( j-1 >= 0)
  {
    board[i][j-1]= "N";

  }
  if(j <= col-2)
  {
    board[i][j+1]= "N";
  }
  if(i  <= row-2 )
  {
    board[i+1][j] = "N";
    if(j-1>= 0 )
    {
      board[i+1][j-1]= "N";
    }
    if(j <= col-2)
      {
        board[i+1][j+1] = "N";
      }
  }
}

//this is the helper function which convert int to string
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
//this is the helper function which return the number of the vertical ship
int get_Ver_ship(vector<vector<string> >  board, int col)
{ int out = 0;
  for(unsigned int i =0; i< board.size(); i++)
  {
    if(board[i][col] != " "  &&  board[i][col] != "N")
      out += 1;
  }
  return out;
}

//this is the helper function which return the number of the horizon ship
int get_Hor_ship(vector<vector<string> >  board, int row)
{ int out = 0;
  for(unsigned int i =0; i< board[0].size(); i++)
  {
    if(board[row][i] != " " &&  board[row][i] != "N")
      out += 1;
  }
  return out;
}

//I used an special technic over over_here
// The invalid point will be marked as N, which will not be checked to see that
//is ok to add or not
void mark_none(vector<vector<string> >  &board, vector<int> row_ship, vector<int> col_ship)
{
  for(unsigned int i=0; i<board.size(); i++)
    if(get_Hor_ship(board, i) == row_ship[i])
    {
      for(unsigned int j=0; j< board[0].size(); j++)
        {
          if(board[i][j] == " ")
            board[i][j]= "N";
        }
    }
    for(unsigned int j=0; j< board[0].size(); j++)
    if(get_Ver_ship(board, j) == col_ship[j])
    {
      for(unsigned int i=0; i< board.size(); i++)
        {
          if(board[i][j] == " ")
            board[i][j]= "N";
        }
    }
}
//this is the helper function which help us see that if there is any ship around us

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


// this is the helper function of the helper funcion which check if there is any ship around the ship
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


// this is the helper function which check if there is any ship around the ship
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
//This is the helper function which help us find all the solutions in the ship
/*
1. We will go though each grid of the board
2. check the the conditions that we must to qualify to add the ship in to the board
3. if the conditions is proper, calculate the ID of the grid(we combine the row and col
  number and convert it into an int)
4. adding the into the vector, and return the vector which store all the valid value at the end*/
vector<int> find_ver_point(string ship, vector<int> row_ship, vector<int> col_ship,
  int rows, int cols, vector<vector<string> >  board)
{
  vector<int> result;
  int ship_L= LEN(ship);
  for ( unsigned int i = 0; i<board.size(); i++)
    {
      for(unsigned int j =0; j< board[0].size(); j++)
      {
        if(board[i][j]== "N")
          continue;

        bool judge = true;
        if ((i+ship_L)>rows)
          judge = false;
        if(judge == true)
        {
          for(unsigned int k = 0; k<ship_L; k++)
          {
            if(board[i+k][j] != " " )
              judge = false;
          }
        }
        if(judge == true)
        {
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
        if (judge == true)
          {
            result.push_back(i*cols+j);
          }
      }
    }
  return result;
}

//This is the helper function which help us find all the solutions in the ship
/*
1. We will go though each grid of the board
2. check the the conditions that we must to qualify to add the ship in to the board
3. if the conditions is proper, calculate the ID of the grid(we combine the row and col
  number and convert it into an int)
4. adding the into the vector, and return the vector which store all the valid value at the end*/
vector<int> find_hor_point(string ship, vector<int> row_ship, vector<int> col_ship,
   int rows, int cols, vector<vector<string> >  board)
{
  vector<int> result;
  int ship_L= LEN(ship);
  for ( unsigned int i = 0; i<board.size(); i++)
    {
      for(unsigned int j =0; j< board[0].size(); j++)
      {
        if(board[i][j] != " ")
        {
          continue;

        }

        bool judge = true;
        if ((j+ship_L)>cols)
          judge = false;
        if(judge == true)
        {
          for(unsigned int k = 0; k<ship_L; k++)
          {
            if(board[i][j+k] != " " )
              judge = false;
          }
        }
        if(judge == true)
        {
          if((get_Hor_ship(board,i)+ship_L)> row_ship[i])
            {judge = false;}
        }
        if(judge == true)
        {
          for(unsigned int k = 0; k<ship_L; k++)
          {
            if(get_Ver_ship(board, j+k)+1 > col_ship[j+k])
              judge = false;
          }
        }
        if (judge == true)
          {
            result.push_back(i*cols+j);
          }
      }
    }
  return result;
}

// this is the helper function which help us print the well_formattd board
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
    {   if(board[i][j] == "N")
          cout<<" ";
        else
        cout<<board[i][j];
    }
    if (row_ship[i] == 999)
    cout<<"|"<<"?"<<endl;
    else
    cout<<"|"<<row_ship[i]<<endl;
  }
  cout<<head<<endl;
  cout<<" ";
  for(unsigned int j = 0; j< board[0].size(); j++)
  {
    if (col_ship[j] == 999)
    cout<<"?";
    else
    cout<<col_ship[j];
  }
  cout<<" "<<endl;
}



//this is an helper funciton which help us adding the ship into the board horizontally
void add_hor_ship(string ship ,int ID, vector<vector<string> > & board)
{
  int ship_L = LEN(ship);
  int row_num = ID/board[0].size();
  int col_num = ID-(row_num*board[0].size());
  if(ship_L == 1 )
  {
    board[row_num][col_num] = 'o';
    mark_around(board, row_num, col_num);
    return;
  }
  if(ship_L == 2 )
  { mark_around(board, row_num, col_num);
    mark_around(board, row_num, (col_num+1) );
    board[row_num][col_num]='<';
    board[row_num][col_num+1]='>';
    return;
  }
  if(ship_L == 3 )
  { mark_around(board, row_num, col_num);
    mark_around(board,row_num, (col_num+1) );
    mark_around(board,row_num, (col_num+2) );
    board[row_num][col_num]='<';
    board[row_num][col_num+1]='X';
    board[row_num][col_num+2]='>';
    return;
  }
  if(ship_L == 4 )
  {
    mark_around(board, row_num, col_num);
    mark_around(board,row_num, (col_num+1) );
    mark_around(board,row_num, (col_num+2) );
    mark_around(board,row_num, (col_num+3) );
    board[row_num][col_num]='<';
    board[row_num][col_num+1]='X';
    board[row_num][col_num+2]='X';
    board[row_num][col_num+3]='>';
    return;
  }
  if(ship_L == 5 )
  {
    mark_around(board, row_num, col_num);
    mark_around(board,row_num, (col_num+1) );
    mark_around(board,row_num, (col_num+2) );
    mark_around(board,row_num, (col_num+3) );
    mark_around(board,row_num, (col_num+4) );
    board[row_num][col_num]='<';
    board[row_num][col_num+1]='X';
    board[row_num][col_num+2]='X';
    board[row_num][col_num+3]='X';
    board[row_num][col_num+4]='>';
    return;
  }
  if(ship_L == 6 )
  {
    mark_around(board, row_num, col_num);
    mark_around(board,row_num, (col_num+1) );
    mark_around(board,row_num, (col_num+2) );
    mark_around(board,row_num, (col_num+3) );
    mark_around(board,row_num, (col_num+4) );
    mark_around(board,row_num, (col_num+5) );
    board[row_num][col_num]='<';
    board[row_num][col_num+1]='X';
    board[row_num][col_num+2]='X';
    board[row_num][col_num+3]='X';
    board[row_num][col_num+4]='X';
    board[row_num][col_num+5]='>';
    return;
  }
  if(ship_L == 7 )
  {
    mark_around(board, row_num, col_num);
    mark_around(board,row_num, (col_num+1) );
    mark_around(board,row_num, (col_num+2) );
    mark_around(board,row_num, (col_num+3) );
    mark_around(board,row_num, (col_num+4) );
    mark_around(board,row_num, (col_num+5) );
    mark_around(board,row_num, (col_num+6) );
    board[row_num][col_num]='<';
    board[row_num][col_num+1]='X';
    board[row_num][col_num+2]='X';
    board[row_num][col_num+3]='X';
    board[row_num][col_num+4]='X';
    board[row_num][col_num+5]='X';
    board[row_num][col_num+6]='>';
    return;
  }
}

//this is an helper funciton which help us adding the ship into the board vertically
void add_ver_ship(string ship ,int ID, vector<vector<string> > & board)
{
  int ship_L = LEN(ship);
  int row_num = ID/board[0].size();
  int col_num = ID-(row_num*board[0].size());
  // int row_num = ID/board.size();
  // int col_num = ID-(row_num*board[0].size());
  if(ship_L == 1 )
  {
    mark_around(board, row_num, col_num);
    board[row_num][col_num] = 'o';
    return;
  }
  if(ship_L == 2 )
  {
    mark_around(board, row_num, col_num);
    mark_around(board, (row_num+1), col_num);
    board[row_num][col_num]='^';
    board[row_num+1][col_num]='v';
    return;
  }
  if(ship_L == 3 )
  {
    mark_around(board, row_num, col_num);
    mark_around(board, (row_num+1), col_num);
    mark_around(board, (row_num+2), col_num);
    board[row_num][col_num]='^';
    board[row_num+1][col_num]='X';
    board[row_num+2][col_num]='v';
    return;
  }
  if(ship_L == 4 )
  {
    mark_around(board, row_num, col_num);
    mark_around(board, (row_num+1), col_num);
    mark_around(board, (row_num+2), col_num);
    mark_around(board, (row_num+3), col_num);
    board[row_num][col_num]='^';
    board[row_num+1][col_num]='X';
    board[row_num+2][col_num]='X';
    board[row_num+3][col_num]='v';
    return;
  }
  if(ship_L == 5 )
  {
    mark_around(board, row_num, col_num);
    mark_around(board, (row_num+1), col_num);
    mark_around(board, (row_num+2), col_num);
    mark_around(board, (row_num+3), col_num);
    mark_around(board, (row_num+4), col_num);
    board[row_num][col_num]='^';
    board[row_num+1][col_num]='X';
    board[row_num+2][col_num]='X';
    board[row_num+3][col_num]='X';
    board[row_num+4][col_num]='v';
    return;
  }
  if(ship_L == 6 )
  {
    mark_around(board, row_num, col_num);
    mark_around(board, (row_num+1), col_num);
    mark_around(board, (row_num+2), col_num);
    mark_around(board, (row_num+3), col_num);
    mark_around(board, (row_num+4), col_num);
    mark_around(board, (row_num+5), col_num);
    board[row_num][col_num]='^';
    board[row_num+1][col_num]='X';
    board[row_num+2][col_num]='X';
    board[row_num+3][col_num]='X';
    board[row_num+4][col_num]='X';
    board[row_num+5][col_num]='v';
    return;
  }
  if(ship_L == 7 )
  {
    mark_around(board, row_num, col_num);
    mark_around(board, (row_num+1), col_num);
    mark_around(board, (row_num+2), col_num);
    mark_around(board, (row_num+3), col_num);
    mark_around(board, (row_num+4), col_num);
    mark_around(board, (row_num+5), col_num);
    mark_around(board, (row_num+6), col_num);
    board[row_num][col_num]='^';
    board[row_num+1][col_num]='X';
    board[row_num+2][col_num]='X';
    board[row_num+3][col_num]='X';
    board[row_num+4][col_num]='X';
    board[row_num+5][col_num]='X';
    board[row_num+6][col_num]='v';
    return;
  }
}
//This is the helper function to help us see is the two boards are the same or not
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

//This is the helper function that earse tje duplicate board
void erase_duplicate(vector<vector<vector<string> > > &solutions,vector<vector<string> > &all_sol)
{ if(solutions.size()<=1)
    return;
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
    }

    }

}

bool check_qualify_board(vector<vector<string> > board,vector<int> row_ship, vector<int> col_ship)
{
  for ( unsigned int i = 0; i<board.size(); i++)
    {   if(row_ship[i] == 999) continue;
        else if(get_Hor_ship(board, i) != row_ship[i])
          return false;
    }
  for ( unsigned int j =0; j< board[0].size(); j++)
    { if(col_ship[j] == 999) continue;
      else  if(get_Ver_ship(board,j) != col_ship[j])
        return false;
    }
  return true;
}

//This is the helper function which convert the string to the int
int str_to_int( string str)
{
  istringstream buffer(str);
  int value;
  buffer >> value;
return value;
}

//This funcion check the constrain and erase the unqualify one
void erase_unqualify(vector<vector<vector<string> > > &solutions,vector<vector<string> > &all_sol, vector<vector<string> > &constrain)
{ if(solutions.size() == 0)
    return;
  for(unsigned int i =0; i< solutions.size()-1; i++)
  {
    for(unsigned int j = 0; j< constrain.size(); j++)
    {
      if(constrain[j][2] == "_")
        {
        if(  solutions[i][str_to_int(constrain[j][0])][str_to_int(constrain[j][1])] != " "
          && solutions[i][str_to_int(constrain[j][0])][str_to_int(constrain[j][1])] != "N")
          {
            solutions.erase(solutions.begin()+i);
            all_sol.erase(all_sol.begin()+i);
            i-=1;
          }
        }
      else if(constrain[j][2]!= solutions[i][str_to_int(constrain[j][0])][str_to_int(constrain[j][1])])
      {
        solutions.erase(solutions.begin()+i);
        all_sol.erase(all_sol.begin()+i);
        i-=1;
      }
    }

    }

}

//this is the helper funcion to help us see that our solution is u
bool check_constrain(vector<vector<string> > board, vector<vector<string> > &constrain)
{ if(constrain.size() == 0)
    return true;

    for(unsigned int j = 0; j< constrain.size(); j++)
    {
      if(constrain[j][2] == "_")
        {
        if(  board[str_to_int(constrain[j][0])][str_to_int(constrain[j][1])] != " "
          && board[str_to_int(constrain[j][0])][str_to_int(constrain[j][1])] != "N")
          {
            return false;
          }
        }
      else if(constrain[j][2]!= board[str_to_int(constrain[j][0])][str_to_int(constrain[j][1])])
      {
        return false;
      }
    }

return true;

}


//This is my main recursing function
/* its function is descridbed below
1. check the remaining ship
2. if there are ship remaining, use function to to find the find_all_solutions
  the solution that we fund will returned as an int which means an position in the grib
3. then we will go tough all the list, forming a string, make a copy of a new board,
  and recurse back to the find_solutions function
4. at the begging of our function, we need to use the function that we need to store the
  previous ship from the recursion, and store it into the new board.
5. if there is no more ship, this means that we found a valid solution, So, we will
  store it into and reference 3D vector, which is the vector of the board
6. If there is no more solutions, we will return nothing, and recurse back.
*/
void find_solutions(vector<vector<vector<string> > > &solutions,
    vector<vector<string> > board,
    const vector<int> row_ship, const vector<int> col_ship,   vector<string> all_ship,
    int ID, vector<string> temp_sol, vector<vector<string> > &all_sol, string marking
    , int direction_indicator, string order,   vector<vector<string> > constrain)
    {


      int rows = board.size();
      int cols = board[0].size();

      // one means horizontal, zero means vertical
      if(direction_indicator == 1)
      {
        add_hor_ship(all_ship[0], ID, board);
        all_ship.erase(all_ship.begin());
      }

      if(direction_indicator == 0)
      {
        add_ver_ship(all_ship[0], ID, board);
        all_ship.erase(all_ship.begin());
      }

      mark_none(board, row_ship, col_ship);
      //pushing the well formatted solution string into the reference vector
      if(marking != "")
      {
        temp_sol.push_back(marking);
      }
      if(all_ship[0] == "unknown")
      {all_ship[0] = "submarine";
      find_solutions(solutions, board, row_ship, col_ship, all_ship, ID, temp_sol, all_sol, marking,-1, order,constrain);
      }

      //if the ship is unkown we have to try it from the biggest to the smallest

      if( (all_ship.size() != 0 && order== "find_all_solutions" )
        || (solutions.size()==0 && all_ship.size() != 0 && order== ""  ))
        {
         vector<int> hor_point = find_hor_point(all_ship[0], row_ship, col_ship,rows, cols ,board);

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
             marking += (int_to_str(row_num) + " "+ int_to_str(col_num) );
             if(all_ship[0] != "submarine")
             marking += " horizontal";
        //     cout<<"marking is"<<marking<< endl;
          //   cout<<"over_here"<<endl;
             find_solutions(solutions, board, row_ship, col_ship, all_ship, ID, temp_sol, all_sol, marking,1,order,constrain);
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
               marking += (int_to_str(row_num) + " "+ int_to_str(col_num)  );
               if(all_ship[0] != "submarine")
               marking += " vertical";

               find_solutions(solutions, board, row_ship, col_ship, all_ship, ID, temp_sol, all_sol, marking,0, order,constrain);
             }

           }

     }
      else
      {if(check_qualify_board(board, row_ship, col_ship) && check_constrain(board, constrain))
        {all_sol.push_back(temp_sol);
        solutions.push_back(board);
        return;}
      else
        return;
      }



    }

//This is an helper function which enable me to sort the list from
//the biggest len to the shortest length
bool sorting_helper(string shipa, string shipb)
{
 int a_len = LEN(shipa);
 int b_len = LEN(shipb);
 return a_len > b_len;
}





int main(int argc, char* argv[])
{ int start_s=clock();
  string order ="";
  if (argc>2)
  order = argv[2];

  //at the begeing of our code, we will read those data
  //create an 2D vector as the board which help us do the formatting things
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
      num = 999;
    }
    else
    {
      num =  atoi(text.c_str());
    }
    row_ship.push_back(num);


  }
  infile>>text;

  for(unsigned int j = 0; j<cols; j++ )
  {
    infile>>text;
    if(!AllNum(text))
    {
      num = 999;
    }
    else
    {
      num =  atoi(text.c_str());
    }
    col_ship.push_back(num);

  }

  while(infile>>text)
  {
    if(text == "constraint")
    break;
    else
    all_ship.push_back(text);

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

// all the code above is doing the things taking in all the inputs



vector<vector<string> > board;


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



/*

1. we find all the solutions and store it into an 3D vector which is the vector
of the board

2. Then, we erase the duplicate answer and the answer that do not meet the constrain

3. At last, we will print the board and format it properly
*/
vector<vector<vector<string> > > solutions;



int ID = -1;
vector<string> temp_sol;
vector<vector<string> > all_sol;
string marking = "";
int direction_indicator = -1;

std::sort(all_ship.begin(),all_ship.end(),sorting_helper);
find_solutions(solutions, board, row_ship, col_ship, all_ship
              , ID, temp_sol, all_sol, marking, direction_indicator, order, constrain );
int stop_s=clock();

//
erase_duplicate(solutions, all_sol);
erase_unqualify(solutions, all_sol, constrain);
//
// // //the following codes are doing the printing things

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

  if(solutions.size() == 0)
    cout<<"No Solution."<<endl;
}
 else
  {
    if(solutions.size() == 0)
      cout<<"No Solution."<<endl;
    else
    {
    cout<< "Solution: "<<endl;
    for(unsigned int k =0; k< all_sol[0].size();k++)
      cout<<all_sol[0][k]<<endl;
    print_board(solutions[0], row_ship, col_ship);
  }
  }
//
//The below line is my testing function for measuing time
// cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
return 1;

}

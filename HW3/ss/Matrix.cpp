#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
using namespace std;
#include "Matrix.h"

Matrix::Matrix(){
  rows= 0;
  cols = 0;
  data = NULL ;
}

//nothing too much to say...Just do what I have to do....This HW is insane for the noob like me.
Matrix::Matrix (unsigned int arows, unsigned int acols, double num){
rows= arows;
cols = acols;
data = new double* [rows];
for(unsigned int i =0; i<rows; i++)
  {  data[i] = new double[cols];
    {for(unsigned int j =0;j<cols;j++)
        data[i][j]=num;
    }
  }
}

Matrix::Matrix(const Matrix& M2)
{//This function is extremely similar to the copy function below. So, I diretly used the copy fuction below
copy(M2);


}



Matrix::~Matrix(){
  clear();
  //same reason, same for clearing function, so I diectly use the clear function
}


double** Matrix::get_data()const{

return data;//simple accessor

}

void Matrix::operator= (const Matrix& m){
  copy(m);
//work in the same way as the copy function, so I use the copy funcion


}

bool Matrix::operator== (const Matrix& M2){
  //if theor rows and cols are the same, it will equial and return true. Otherwise, it will be false
  bool judge = true;
  if(rows!=M2.rows || cols != M2.cols){judge = false;}
  for(unsigned int i =0; i<rows; i++)
    {for(unsigned int j =0;j<cols;j++)
      {
        if (data[i][j]!=M2.get_data()[i][j])
        judge = false;
      }
    }
  return judge;
}

bool Matrix::operator!= (const Matrix& M2){
  bool judge = true;
  if(rows!=M2.rows || cols != M2.cols){judge = false;}
  for(unsigned int i =0; i<rows; i++)
    {for(unsigned int j =0;j<cols;j++)
      {
        if (data[i][j]!=M2.get_data()[i][j])
        judge = false;
      }
    }
  //work similarly with the == operator except for an ! at the end
  return !judge;
}

ostream& operator<< (ostream& OUTT,const Matrix& m){
//a bunch of formating thing, putting everything into the string OUT, and convert
//it to an ostream at the end

  string OUT = "\n";
    std::stringstream SS1;
    std::string ROW;
    SS1<<m.num_rows();
    SS1>>ROW;
  OUT += ROW;
  OUT += " x ";
    std::stringstream SS2;
    std::string COLS;
    SS2<<m.num_cols();
    SS2>>COLS;
  OUT += COLS;
  OUT += " matrix:\n[ ";
  for(unsigned int i =0; i<m.num_rows(); i++)
    { if(i!=0)
      OUT +="  ";
      for(unsigned int j =0;j<m.num_cols();j++)
      {   std::stringstream SS3;
          std::string NUM;
          SS3<<m.get_data()[i][j];
          SS3>>NUM;

          OUT += NUM;
          OUT +=' ';

      }
      if( i != (m.num_rows()-1))
      OUT +="\n";
    }

  OUT += "]\n";
  OUTT<<OUT;
  return OUTT;
}


//mutiplication operator
Matrix Matrix::operator*(const Matrix& temp) const
{

    if((*this).cols==temp.rows)
    {
        Matrix m((*this).rows,temp.cols,0);
        for(int i=0; i<(*this).rows; i++)
            for(int j=0; j<temp.cols; j++)
                for(int k=0; k<(*this).cols; k++)
                    m.data[i][j] += (*this).data[i][k] * temp.data[k][j];
        return m;
    }

    else {
        cerr << "cannot be mutiplied" << endl;
        return Matrix(0,0,0);
    }

}



//simple assessor
unsigned int Matrix::num_rows()const{
  return rows;
}
//simple assessor
unsigned int Matrix::num_cols()const{
  return cols;
}

//simple assessor
bool Matrix::get(unsigned int ROW, unsigned int COLS, double& num){
    bool judge= true;
    if(ROW>rows || COLS >cols)
    judge = false;

    if (judge==true)
    num=data[ROW][COLS];

    return judge;
  }
//help us set the specific number in the Matrix which is helpful in the later matrix funcion
bool Matrix::set(unsigned int ROW, unsigned int COLS, double num){
    bool judge= true;
    if(ROW>rows || COLS >cols)
    judge = false;

    if (judge==true)
    data[ROW][COLS]=num;

    return judge;
  }


void Matrix::multiply_by_coefficient(double num){
  for(unsigned int i=0;i<rows;i++)
  {for(unsigned int j=0;j<cols;j++)
    data[i][j] *= num;//nothing too much to say, just mutiply the number in it

  }

}



bool Matrix::swap_row(unsigned int row1, unsigned int row2){
  bool judge = true;
  if(row1>rows || row2>rows)
  judge=false;
  if(judge==true)
    {double* media = new double[rows];

    for(unsigned int i=0;i<cols;i++)
      {media[i]=data[row1][i];}

    data[row1]=data[row2];
    delete  []data[row2];
    data[row2]=media;}
    //just putting it into a third double array, copy it, and delete the origin one
  return judge;
}

void Matrix::transpose(){
  //creating a new matrix which is invert to the origin one
  double** new_data= new double*[cols];
  for(unsigned int i=0;i<rows;i++)
  {new_data[i]= new double[rows];
    for(unsigned int j=0;j<cols;j++)
    {new_data[j][i]=data[i][j];}//copying the inverse index into the new double array
  }
  for(unsigned int i=0;i<rows;i++)
  {delete []data[i];}
  delete []data;
  data=new_data;
}

bool Matrix::add(Matrix& M2){
  bool judge = false;
  if(rows==M2.num_rows() && cols==M2.cols)
  judge = true;// use judge to see if they have the same row/cols or not
   if(judge==true)
  { for(unsigned int i=0;i<rows;i++)
     {for(unsigned int j=0;j<cols;j++)
       {data[i][j]+=M2.data[i][j];}
     }
   }

  return judge;
}
//extremely similar to the add function
bool Matrix::subtract(Matrix& M2){
  bool judge = false;
  if(rows==M2.num_rows() && cols==M2.num_cols())
  judge = true;
   if(judge==true)
  { for(unsigned int i=0;i<rows;i++)
     {for(unsigned int j=0;j<cols;j++)
       {data[i][j]-=M2.get_data()[i][j];}
     }
   }

  return judge;
}

//create new double array,put the element into it, and return it.
double* Matrix::get_row(unsigned int num){
  double* a = new double[cols];
  for(unsigned int i=0;i<cols;i++)
  {
    a[i]=data[num][i];
  }
  return a;
}

//similar to the get_row function
double* Matrix::get_col(unsigned int num){
  double* a = new double[rows];
  for(unsigned int i=0;i<rows;i++)
  {
    a[i]=data[num][i];
  }
  return a;
}

Matrix* Matrix::quarter(){

  Matrix * OUT;
  OUT = new Matrix[4];
  unsigned int n_rows, n_cols;//1st calculte the index and the size of the four matrix
  if(rows % 2)
    n_rows = rows/2 +1;
  else
    n_rows = rows/2 ;
  if(cols % 2)
    n_cols = cols/2 +1;
  else
    n_cols = cols/2 ;
  for(unsigned int n=0; n< 4; n++){
    OUT[n] = Matrix(n_rows,n_cols,0);//2nd, initialize all foir matrix
  }
for(unsigned int r=0;r<n_rows;r++)
{ for(unsigned int c=0;c<n_cols;c++)
  { OUT[0].set(r,c,data[r][c]);
    OUT[1].set(r,c,data[r][cols-n_cols+c]);
    OUT[2].set(r,c,data[rows-n_rows+r][c]);
    OUT[3].set(r,c,data[rows-n_rows+r][cols-n_cols+c]);
//3rd putting the index into the funcion
  }

}


  return OUT;
}

void Matrix::copy(const Matrix& m){
  //copy constuctor, use it to copy whole
  rows = m.num_rows();
  cols = m.num_cols();
  data = new double*[rows];
  for (unsigned int i =0;i<rows;i++){
    data[i] = new double[cols];
    for(unsigned int j = 0; j<cols;j++){
      data[i][j]= m.get_data()[i][j];
    }
  }
}



void Matrix::clear(){
  //delete all the matrix in the array
  if (data != NULL ) {
    for(unsigned int i=0; i< rows;i++) {
      if(data[i]!= NULL)  delete [] data[i];
      data[i] = NULL;
    }
    delete [] data;
    data = NULL;
  }
  rows=0;
  cols=0;
}

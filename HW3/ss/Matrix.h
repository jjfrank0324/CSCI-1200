#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
using namespace std;


class Matrix{
public:
  Matrix();
  Matrix(const Matrix& M2);
  Matrix (unsigned int arows, unsigned int acols, double num);

  ~Matrix() ;//destructor

//operator
  double** get_data()const;
  void operator=(const Matrix& m);
  bool operator== (const Matrix& M2);
  bool operator!= (const Matrix& M2);
  Matrix operator*(const Matrix& that) const;

//assessor
  unsigned int num_rows() const;
  unsigned int num_cols() const;

  void clear();

  bool get(unsigned int ROW, unsigned int COLS, double& num);
  bool set(unsigned int ROW, unsigned int COLS, double num);

  void multiply_by_coefficient(double num);
  bool swap_row(unsigned int row1, unsigned int row2);
  void transpose();

  bool add(Matrix& M2);
  bool subtract(Matrix& M2);

  double* get_row(unsigned int num);
  double* get_col(unsigned int num);

  Matrix* quarter();//question


private:

  void copy(const Matrix& m);
  double** data;
  unsigned int rows;
  unsigned int cols;





};
  ostream& operator<< (ostream& OUTT,const Matrix& m);//printing funcion is putted outside the .h

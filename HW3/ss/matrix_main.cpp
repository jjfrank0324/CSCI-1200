#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include "Matrix.h"

#define __EPSILON 0.0000000001 //Need this to compare doubles because representation.

void Testingmuti(); //Write this if you write resize()


//Quick function that returns if two doubles are very similar to each other.
bool double_compare(double a, double b);

//Uses Gauss-Jordan elimination to create a Reduced Row Echelon Form matrix.
Matrix rref(const Matrix& m);

int main(){

	Testingmuti();
	std::cout << "Completed all mutiplication test." << std::endl;

	return 0;
}


void Testingmuti(){

  std::cout << "/////////////////////////////////////////"<< std::endl;
  std::cout << "CASE ONE: INDENTICLE MATRIX MUTIPLATION" << std::endl;

  std::cout << "Now start testing mutiplication" << std::endl;
  Matrix m5(2,2,2);
  Matrix m6(2,2,1);
  std::cout << "Matrix 1 is";
  std::cout<<m5<<std::endl;
  std::cout << "Matrix 2 is";
  std::cout<<m6<<std::endl;
  m6 = m5*m6;
  std::cout << "Matrix1 mutiply Matrix2 is";
  std::cout<<m6<<std::endl;
  std::cout << "/////////////////////////////////////////"<< std::endl;
  std::cout << "CASE TWO: ERROR TESTING" << std::endl;
  std::cout << "Matrix 1 is"<< std::endl;
  Matrix m1(1,1,2);
  std::cout<<m1<<std::endl;
  std::cout << "Matrix 2 is"<< std::endl;
  Matrix m2(2,2,1);
  std::cout<<m5<<std::endl;
  std::cout << "Matrix1 mutiply Matrix2 is: "<< std::endl;
  m1 = m1*m2;

  std::cout << "/////////////////////////////////////////"<< std::endl;
  std::cout << "CASE THREE: n*m mutiply m*n matrix testing" << std::endl;
  Matrix m9(1,3,0);
  m9.set(0,0,7);
  m9.set(0,1,8);
  m9.set(0,2,9);
  std::cout << "Matrix 1 is"<< std::endl;
  std::cout<<m9<<std::endl;
  Matrix m10(3,2,7);
  m10.set(0,0,3);
  m10.set(2,0,5);
  std::cout << "Matrix 2 is"<< std::endl;
  std::cout<<m10<<std::endl;

  m9 = m9*m10;
  std::cout << "Matrix1 mutiply Matrix2 is";
  std::cout<<m9<<std::endl;


  std::cout << "/////////////////////////////////////////"<< std::endl;


}




//Quick function that returns if two doubles are very similar to each other.
bool double_compare(double a, double b){
	return (fabs(a-b) < __EPSILON);
}

/*  Uses Gauss-Jordan elimination to create a Reduced Row Echelon Form matrix.
 *  These are some good and some bad variable names.
 *  See how much harder it makes it to follow the code?
 *  The lack of comments doesn't help either.
 */

Matrix rref(const Matrix& m){
	Matrix ret(m);
	unsigned int curr_col = 0;
	double dummy;
	for(unsigned int i=0; i<ret.num_rows(); i++){
		bool col_all_zeros = true;
		//while(col_all_zeros && col_all_zeros < ret.num_cols()){
		while(col_all_zeros && curr_col < ret.num_cols()){
			for(unsigned int scan_i = 0; scan_i < ret.num_rows(); scan_i++){
				ret.get(scan_i,curr_col,dummy);
				if (!double_compare(dummy,0.0)){
					col_all_zeros = false;
					break;
				}
			}
			if(col_all_zeros){
				curr_col += 1;
			}
		}
		if(curr_col>=ret.num_cols()){
			return ret;
		}

		ret.get(i,curr_col,dummy);
		if(double_compare(dummy,0.0)){
			//Swap with a nonzero row
			for(unsigned int scan_i = i+1; scan_i < ret.num_rows(); scan_i++){
				ret.get(scan_i,curr_col,dummy);
				if(!double_compare(dummy,0.0)){
					ret.swap_row(scan_i,i);
					break;
				}
			}
		}

		//Now we know ret i,curr_col is non-zero so we can use it as a pivot.
		double pivot;
		ret.get(i,curr_col,pivot);
		for(unsigned int j=0; j<ret.num_cols(); j++){
			ret.get(i,j,dummy);
			ret.set(i,j,dummy/pivot);
		}

		for(unsigned int row_i = 0; row_i < ret.num_rows(); row_i++){
			if (row_i == i){
				continue;
			}
			double row_leading_coeff;
			ret.get(row_i,curr_col,row_leading_coeff);
			for(unsigned int col_j = 0; col_j < ret.num_cols(); col_j++){
				double lhs_dummy,rhs_dummy;
				ret.get(row_i,col_j,lhs_dummy);
				ret.get(i,col_j,rhs_dummy);
				ret.set(row_i,col_j,lhs_dummy - (row_leading_coeff*rhs_dummy));
			}
		}
		curr_col +=1 ;
	}
	return ret;
}

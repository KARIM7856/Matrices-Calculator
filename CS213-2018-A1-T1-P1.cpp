/*
Course:  CS213 - Programming II  - 2018
Title:   Assignment I - Task 1 - Problem 1
Program: CS213-2018-A1-T1-P1
Purpose: Perform manipulation on matrix
Author: Karim Mohamed, Omar Hassan, Amr Alaa
Date: 
Version: 1.0
*/
#include <iostream>
#include <iomanip>

using namespace std;

struct matrix
{
  int* data;       // Pointer to 1-D array that will simulate matrix
  int row, col;
};

void createMatrix (int row, int col, int num[], matrix& mat);
//returns a matrix with the dimensions row and col and elements that exist in num[].

ostream& operator<< (ostream& out, matrix mat);
//precondition: matrix must have been initialized.
//return value: the output stream.
bool   operator== (matrix mat1, matrix mat2);
//Checks if the dimensions of the matrices are the same then compare element by element then retuns 0 if not equal 1 if equal.
bool   operator!= (matrix mat1, matrix mat2);
//Same as operator == but returns 1 if not equal and 0 if equal.
bool   isSquare   (matrix mat);
// Checks if the row and columns of a given matrix is equal to each other.
bool   isSymetric (matrix mat);
//Checks if the transpose of matrix is same as matrix.
bool   isIdentity (matrix mat);
//Checks if the main diagonal of the matrix is all 1 and all other elements are 0.
matrix transpose(matrix mat); 
//Returns the transpose of a matrix.
// Amr Alaa
istream& operator>> (istream& in,matrix& mat);
matrix operator+= (matrix& mat1, matrix mat3);
// Two matrices has to be of the same dimensions
matrix operator-= (matrix& mat1, matrix mat3);
// Two matrices has to be of the same dimensions
matrix operator+= (matrix& mat, int scalar);
matrix operator-= (matrix& mat, int scalar);
void   operator++ (matrix& mat);
void   operator-- (matrix& mat);
// Omar Hassan
matrix operator+  (matrix mat1, matrix mat2);
// Two matrices has to be of the same dimensions
matrix operator-  (matrix mat1, matrix mat2);
// Two matrices has to be of the same dimensions
matrix operator*  (matrix mat1, matrix mat2);
// columns in mat1 must equal columns in mat2 (or) vise versa.
matrix operator+  (matrix mat1, int scalar);
matrix operator-  (matrix mat1, int scalar);
matrix operator*  (matrix mat1, int scalar);

int main(){

    int scalar, matnum, scalar2, matnum2, matnum3, matnum4;
    int data1 [] = {1,2,3,4,5,6,7,8};
    int data2 [] = {13,233,3,4,5,6};
    int data3 [] = {10,100,10,100,10,100,10,100};

    matrix mat1, mat2, mat3, mat4;

    createMatrix (4, 2, data1, mat1);
    createMatrix (2, 3, data2, mat2);
    createMatrix (4, 2, data3, mat3);

    cout <<"mat1 (4*2) : "<<endl<< mat1 << endl;
    cout <<"mat2 (2*3) : "<<endl<< mat2 << endl;
    cout <<"mat3 (4*2) : "<<endl<< mat3 << endl;

    cout<<"creating matrix number 4 "<<endl;
    cin>>mat4;
    cout<<"fourth matrix (" << mat4.row << "*" << mat4.col << ") :" << endl << mat4 << endl << endl;

    cout << "\nmat1 += mat3\n\n";
    mat1 += mat3;
    cout << mat1;
    
    mat1 -= mat3;

    cout << "\nmat1 -= mat3\n\n";
    mat1 -= mat3;
    cout << mat1;
    mat1 += mat3;

    cout <<"\nmat4++\n\n";
    ++mat4;
    cout << mat4;
    --mat4;

    --mat4;
    cout <<"\n--mat4\n\n" << mat4;
    ++mat4;

    cout << "\nmat4 += 6\n\n";
    mat4 += 6;
    cout << mat4;
    mat4 -= 6;

    cout << "\nmat4 -= 4\n\n";

    mat4 -= 4;
    cout << mat4;
    mat4 += 4;

    cout << "\ntranspose of mat1\n\n";
    cout << transpose(mat1);

    cout << "\nCompare mat4 == mat1 " << (mat4 == mat1) << endl;
    cout << "\nCompare mat4 != mat1 " << (mat4 != mat1) << endl;

    cout << "\nis square mat2 " << isSquare(mat2) << endl;
    cout << "\nis symetric mat3 " << isSymetric(mat3) << endl;

    cout << "\nis Identity mat4 " << isIdentity(mat4) << endl;

    cout << "\nmat1 + mat2\n" << (mat1 + mat2);
    cout << "\nmat1 + 4\n" << (mat1 + 4);

    cout << "\nmat1 - mat2\n" << (mat1 - mat2);
    cout << "\nmat1 - 4\n" << (mat1 - 4);

    cout << "\nmat1 * mat2\n" << (mat1 * mat2);
    cout << "\nmat1 * 4\n" << (mat1 * 4);

    return 0;
}


void createMatrix (int row, int col, int num[], matrix& mat) {
  mat.row = row;
  mat.col = col;
  mat.data = new int [row * col];
  for (int i = 0; i < row * col; i++)
    mat.data [i] = num [i];
}

ostream& operator<< (ostream& out, matrix mat){
    int counter = 0;
    for(int i = 0; i < mat.row*mat.col; i++){
        cout << mat.data[i] << " ";
        counter++;
        if (counter == mat.col){
            cout << endl;
            counter = 0;
        }
    }
    return out;
}

bool  operator== (matrix mat1, matrix mat2){
    if ((mat1.col == mat2.col) && (mat1.row == mat2.row)){
        for(int i = 0; i<mat1.row*mat1.col; i++){
          if(mat1.data[i] != mat2.data[i]){
            return false;
          } 
        }
        return true;
    }
    else return false;
}

bool operator != (matrix mat1, matrix mat2){
    if ((mat1.row == mat2.row)&& (mat1.col == mat2.col)){
        for(int i=0; i<mat1.row*mat1.col; i++){
            if(mat1.data[i]!= mat2.data[i]) return true;
        }
    return false;
}
    else return true;
}

bool isSquare (matrix mat){
    if (mat.col == mat.row){
	    return true;
    }
	else return false;
}

bool   isSymetric (matrix mat){
  if (isSquare(mat)){
    for(int i = 0; i < mat.row*(mat.row-1); i++){
      if (mat.data[i] != mat.data[(i%mat.row)*mat.row + (i/mat.row)]){
        /*
        i % mat.row is responsible that the multiplier never gets more than
        number of rows. and give which column the iterator is at then multiplied by
        the number of rows in the matrix to give the row then plus i/mat.row to give which column
        at first row i/mat.row is always 0 this refer to the value compared is always at column0
        and so on.
        */
          return false;
      }
    }
    return true;
  }
  else return false;
}

bool   isIdentity(matrix mat) {
	if (isSquare(mat)) {
		int counter = 0;
		for (int i = 0; i < mat.row*mat.col; i++) {
			if ((i == counter) && (mat.data[i] != 1)) {
				return false;
			}
			else if ((i != counter) && (mat.data[i] != 0)) {
				return false;
			}
			else if (i == counter) {
				counter += (mat.row + 1);
			}

		}
		return true;
	}
	else return false;
}


matrix transpose(matrix mat) {
	int j = 0;
	matrix temp;
	createMatrix(mat.row, mat.col, mat.data, temp);
	for (int u = 0; u < mat.col; u++) {
		for (int i = u; i < mat.row * mat.col; i += mat.col, j++) {
			temp.data[j] = mat.data[i];
		}
	}
	swap(temp.col, temp.row);
	return temp;
}

istream& operator>> (istream& in,matrix& mat){
    cout<<"enter number of rows : ";
    cin>>mat.row;
    cout<<"enter number of columns : ";
    cin>>mat.col;
    mat.data = new int[mat.row*mat.col];
    for (int i=0; i<mat.row; i++){
        cout<<"enter data in row "<<i+1<<" : " ;
        for (int j=0; j<mat.col; j++){
            cin>>mat.data[i*mat.col+j];
        }
    }
}

matrix operator+= (matrix& mat1, matrix mat3){
    if(mat1.row==mat3.row&&mat1.col==mat3.col){
    for (int i=0;i<mat1.row*mat1.col;i++){
        mat1.data[i]=mat1.data[i]+mat3.data[i];

    }
    return mat1;
    }
    else {
        cout<<"cant add";
    }
}

matrix operator-= (matrix& mat1, matrix mat3){
    if(mat1.row==mat3.row&&mat1.col==mat3.col){
    for (int i=0;i<mat1.row*mat1.col;i++){
        mat1.data[i]=mat1.data[i]-mat3.data[i];

    }
    return mat1;
    }
    else {
        cout<<"cant subtract";
    }
}

matrix operator+= (matrix& mat, int scalar){
    for(int i=0;i<mat.row*mat.col;i++){
        mat.data[i]=mat.data[i]+scalar;
    }
}

matrix operator-= (matrix& mat, int scalar){
    for(int i=0;i<mat.row*mat.col;i++){
        mat.data[i]=mat.data[i]-scalar;
    }
}

void   operator++ (matrix& mat){
     for(int i=0;i<mat.row*mat.col;i++){
        mat.data[i]=mat.data[i]+1;
    }
}

void   operator-- (matrix& mat){
    for(int i=0;i<mat.row*mat.col;i++){
        mat.data[i]=mat.data[i]-1;
    }
}

matrix operator*  (matrix mat1, int scalar){
    matrix mat;
    mat.row = mat1.row;
    mat.col = mat1.col;
    mat.data = new int [mat.row * mat.col];
    for (int i = 0 ; i < mat.row * mat.col ; i++){
        mat.data[i] = mat1.data[i] * scalar ;
    }
    return mat;
}

matrix operator-  (matrix mat1, int scalar){
    matrix mat;
    mat.row = mat1.row;
    mat.col = mat1.col;
    mat.data = new int [mat.row * mat.col];
    for (int i = 0 ; i < mat.row * mat.col ; i++){
        mat.data[i] = mat1.data[i] - scalar ;
    }
    return mat;
}

matrix operator+  (matrix mat1, int scalar){
    matrix mat;
    mat.row = mat1.row;
    mat.col = mat1.col;
    mat.data = new int [mat.row * mat.col];
    for (int i = 0 ; i < mat.row * mat.col ; i++){
        mat.data[i] = mat1.data[i] + scalar ;
    }
    return mat;
}

matrix operator*  (matrix mat1, matrix mat2){
    if (mat1.row != mat2.col){
        matrix mat;
        cout << endl << "The matrices don't match." << endl;
        return mat;
    }

    matrix temp;
    temp.row = mat1.row;
    temp.col = mat2.col;
    temp.data = new int[mat1.row*mat2.col];

    int to = 0;

    for (int i = 0; i< mat2.col*mat1.row; i++){
        temp.data[i] = 0;
    }
    mat2 = transpose(mat2);
    cout << mat2 << endl;
    int u = 0;
    for(int i = 0; i<mat2.row * mat1.row; i++){
        if(to<i/temp.col){
            u = 0;
        }
        for(int j = i/temp.col,k = 0 ; k < mat2.col; j++,u++,k++){
            temp.data[i] += mat1.data[j] * mat2.data[u];
        to = i/temp.col;
        }
    }
    return temp;
}

matrix operator-  (matrix mat1, matrix mat2){

    if ((mat1.row != mat2.row) || (mat1.col != mat2.col)){
        matrix mat;
        cout << endl << "the dimensions of the two matrices don't match." << endl;
        return mat;
    }
    matrix mat;
    mat.row = mat1.row;
    mat.col = mat1.col;
    mat.data = new int [mat.row * mat.col];
    for (int i = 0 ; i < mat1.row * mat1.col ; i++){
        mat.data[i] = mat1.data[i] - mat2.data[i];
    }
    return mat;
}

matrix operator+  (matrix mat1, matrix mat2){

    if ((mat1.row != mat2.row) || (mat1.col != mat2.col)){
        matrix mat;
        cout << endl << "the dimensions of the two matrices don't match." << endl;
        return mat1, mat2;
    }
    matrix mat;
    mat.row = mat1.row;
    mat.col = mat1.col;
    mat.data = new int [mat.row * mat.col];
    for (int i = 0 ; i < (mat1.row * mat1.col) ; i++){
        mat.data[i] = mat1.data[i] + mat2.data[i];
    }
    return mat;
}
#include "Matrix.h"

Matrix::Matrix(int rows, int cols){
  this->rows = rows;
  this->cols = cols;
  this->MAX_LENGTH = rows*cols;
  this->values = new float[MAX_LENGTH];
}

/**
 * Takes a row and column number and puts the given value there.
 */
bool Matrix::set(int row, int col, float value){
  int index = this->cols*row + col;
  if(index < MAX_LENGTH){
    this->values[index] = value;
    return true;
  } else {
    return false; //error, out of bounds
  }
}

/**
 * Takes a row and column number and gets the value there.
 */
float Matrix::get(int row, int col){
  return this->values[this->cols*row + col];
}

/**
 * Wipes Matrix by making all values 0
 */
void Matrix::clear(){
  int i;
  for(i = 0; i < MAX_LENGTH; ++i)
    values[i] = 0;
}


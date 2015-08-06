#ifndef matrix_h
#define matrix_h

class Matrix
{
  public:
    Matrix(int rows, int cols);
    bool set(int row, int col, float value);
    float get(int row, int col);
    void clear(); //wipes matrix to all 0's
  private:
    float* values;
    int rows, cols, MAX_LENGTH;
};

#endif

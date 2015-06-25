/**
 *  Generic Buffer class
 */


#ifndef buffer_h
#define buffer_h

//TODO this probably doesnt even have to be generic.
template<typename T> //TODO limit this to Numerics, else average will break
class Buffer
{
  public:
    Buffer<T>(int size);
    void add(T newItem);
    float average(); //Only on numerics!!!
  private:
    T* items;
    int size;
    int mostRecentIndex;
};

//Generics must be inside the .h file, cant be in a separate cpp file
template<typename T>
Buffer<T>::Buffer(int size){
  this->items = new T[size];
  this->size = size;
  this->mostRecentIndex = 0;
}

/**
 * Adds an item to the buffer, overwriting the value on the end
 */
template<typename T>
void Buffer<T>::add(T newItem){
  this->items[(this->mostRecentIndex++)%this->size] = newItem;
}

//TODO prevent this being called if the type is a string
/**
 * Averages the values in the buffer and returns them.
 * TODO typechecking
 */
template<typename T>
float Buffer<T>::average(){
  int i, sum;
  for(i=0; i < this->size; ++i){
    sum += this->items[i];
  }
  return sum/this->size;
}

#endif

/**
 *  Generic Buffer class
 */


#ifndef buffer_h
#define buffer_h

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

template<typename T>
void Buffer<T>::add(T newItem){
  this->items[(this->mostRecentIndex++)%this->size] = newItem;
}

//TODO prevent this being called if the type is a string
template<typename T>
float Buffer<T>::average(){
  if(this->items[0]){
    
  }
  int i, sum;
  for(i=0; i < this->size; ++i){
    sum += this->items[i];
  }
  return sum/this->size;
}

#endif

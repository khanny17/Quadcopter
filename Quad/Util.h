#ifndef Util_H
#define Util_H


template <typename T>
struct XYZ {
    T x;
    T y;
    T z;
};


class Util
{
    public:
        template <typename T>
        static void print_xyz(XYZ<T> data) {
            Serial.print('[');
            Serial.print(data.x);
            Serial.print(", ");
            Serial.print(data.y);
            Serial.print(", ");
            Serial.print(data.z);
            Serial.println(']');
        };
};


#endif

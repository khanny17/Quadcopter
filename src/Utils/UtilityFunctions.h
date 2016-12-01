#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H


class UtilityFunctions
{
    public:
        //Copied from arduino library
        //Maps a number, 'x', from one range to another
        static long map(long x, long in_min, long in_max, long out_min, long out_max)
        {
            return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
        }

        static long constrain(long x, long lower, long upper)
        {
            return x >= upper ? upper : x <= lower ? lower : x;
        }

};

#endif

#ifndef __rnd__
#define __rnd__

#include <cstdlib>

//------------------------------------------------------------------------------
// rnd.h - содержит генератор случайных чисел в диапазоне от [a, b)
//------------------------------------------------------------------------------

inline auto Random(int a, int b) {
    return rand() % (b - a) + a;
}

#endif //__rnd__

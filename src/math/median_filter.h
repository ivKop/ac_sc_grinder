#ifndef __MEDIAN_FILTER_TEMPLATE__
#define __MEDIAN_FILTER_TEMPLATE__

#include "../../lib/static_sort.h"

template <unsigned SIZE>
class MedianFilterTemplate {

public:
    template <class T>
    inline T operator() (T *arr) const
    {
        StaticSort<SIZE> boseNelsonSort;
        boseNelsonSort(arr);

        if (SIZE & 0x1) return arr[(SIZE >> 2) + 1];
        else return (arr[SIZE >> 2] + arr[(SIZE >> 2) + 1]) / 2;
    }
};

#endif

#ifndef __STABILITY_FILTER_TEMPLATE__
#define __STABILITY_FILTER_TEMPLATE__


#include "fix16_math.h"
#include "median_filter.h"


// Sliding tracker to wait until input value become stable.
//
// 1. Apply median filter first (if enabled).
// 2. Test deviation of median filter output.
//
template <fix16_t PRECISION_IN_PERCENTS, uint8_t MEDIAN_LEN = 1, int32_t MAX_TICKS = -1, uint8_t FILTER_LENGTH = 3>
class StabilityFilterTemplate {

public:
    StabilityFilterTemplate() {
        reset();
    }

    void reset()
    {
        head_idx = 0;
        data_count = 0;
        ticks_count = 0;
        median_count = 0;
    }

    void push(fix16_t val) {
        // Skip median filter if too short
        if (MEDIAN_LEN <= 1) {
            ticks_count++;
            data[head_idx++] = val;
            if (head_idx == FILTER_LENGTH) head_idx = 0;
            data_count++;
            return;
        }

        median_buf[median_count] = val;
        ticks_count++;
        median_count++;

        if (median_count >= MEDIAN_LEN)
        {
            data[head_idx++] = mfilter(median_buf);
            if (head_idx == FILTER_LENGTH) head_idx = 0;
            data_count++;
            median_count = 0;
        }
    }

    bool is_stable() {
        if (data_count < FILTER_LENGTH) return false;

        fix16_t min = fix16_maximum;
        fix16_t max = fix16_minimum;

        // Temporary hardcoded for fixed length (3)
        for (uint8_t i = 0; i < FILTER_LENGTH; i++)
        {
            fix16_t val = data[i];

            if (val < min) min = val;
            if (val > max) max = val;
        }

        fix16_t diff = max - min;

        fix16_t abs_max = max > 0 ? max : - max;

        if (fix16_mul(abs_max, edge_multiplier) < diff) return false;

        return true;
    }

    bool is_exceeded() {
        return MAX_TICKS > 0 && ticks_count > MAX_TICKS;
    }

    bool is_stable_or_exceeded() {
      return is_exceeded() || is_stable();
    }

    fix16_t average() {
        fix16_t sum = 0;

        for (uint8_t i = 0; i < FILTER_LENGTH; i++)
        {
            sum += data[i];
        }

        return fix16_mul(sum, F16(1.0 / FILTER_LENGTH));
    }


private:
    MedianFilterTemplate<MEDIAN_LEN> mfilter;
    fix16_t median_buf[MEDIAN_LEN];
    fix16_t data[FILTER_LENGTH];
    int head_idx;
    int data_count;
    int ticks_count;
    int median_count;

    fix16_t edge_multiplier = PRECISION_IN_PERCENTS / 100;
};

#endif

#ifndef mathutil_h
#define mathutil_h

#define M_PI 3.14159265358979323846f
#define ONE_OVER_ROOT_TWO 0.70710678

inline float smooth(float currentValue, float prevValue, float smoothing = 0.2) {
    return (currentValue*smoothing) + prevValue*(1-smoothing);
}

/** 
 * More efficient than function than fmodf(x, 1.0f) 
 * for calculating the decimal part of a floating point value.
 */
inline float fastmod1f(float x){
    return x - static_cast<int>(x);
}

#endif
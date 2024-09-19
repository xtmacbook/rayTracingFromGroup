#pragma once
#include <stdlib.h>

inline float max(float x0, float x1) {
	return((x0 > x1) ? x0 : x1);
}

inline float min(float a, float b){
	return (a < b)? a : b;
}

inline float rand_float(){
	return (float) rand()/RAND_MAX;
}

inline float 						// for multi-jittered sampling
rand_float(int l, float h)
{
	return (rand_float() * (h - l) + l);
}


inline int rand_int(){
	return (int) rand();
}

inline int
rand_int(int l, int h) {
	return ((int)(rand_float(0, h - l + 1) + l));
}


inline float clamp(float x, float min, float max){
	return (x < min ? min : (x > max ? max : x));
}

int SolveCubic(double c[4], double s[3]);
int SolveQuartic(double c[5], double s[4]);
int SolveQuadric(double c[3], double s[2]);
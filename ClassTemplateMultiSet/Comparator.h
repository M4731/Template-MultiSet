#pragma once
#include <math.h>
template<typename T>
class Comparator
{
public:
	static bool less(T, T);
	static bool greater(T, T);
	//==
	static bool equals(T x, T y)
	{
		if (x == y)
			return true;
		return false;
	}
};


//>
template<typename T>
bool Comparator<T>::less(T x, T y)
{
	if (x < y)
		return true;
	return false;
}

//<
template<typename T>
bool Comparator<T>::greater(T x, T y)
{
	if (x > y)
		return true;
	return false;
}

//specializare pe double ==
template<>
bool Comparator<double>::equals(double x, double y)
{
	double frac1, frac2;
	frac1 = x - (int)x;
	frac2 = y - (int)y;
	if (frac1 == frac2)
		return true;
	return false;
}
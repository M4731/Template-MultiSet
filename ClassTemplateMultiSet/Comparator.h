#pragma once
template<typename T>
class Comparator
{
public:
	static bool less(T, T);
	static bool greater(T, T);
	static bool equals(T, T);
};

template<typename T>
bool Comparator<T>::less(T x, T y)
{
	if (x < y)
		return true;
	return false;
}

template<typename T>
bool Comparator<T>::greater(T x, T y)
{
	if (x > y)
		return true;
	return false;
}

template<typename T>
bool Comparator<T>::equals(T x, T y)
{
	if (x == y)
		return true;
	return false;
}
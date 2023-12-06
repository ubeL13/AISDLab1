#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>
#include <type_traits>


template<typename T>
struct Point {
	T x, y;
	Point() : x(0), y(0) {}
	Point(T x, T y) : x(x), y(y) {}
};

template<typename T>
class BrokenLine
{
private:
	Point<T>* _points;
	size_t _size;
public:
	BrokenLine() : _size(0), _points(nullptr) { }
	BrokenLine(const T x, const T y)
	{
		_points = new Point(x, y);
		_size = 1;
	}

	BrokenLine(const size_t size)
	{
		_size = size;
		_points = new Point<T>[_size];
	}

	BrokenLine(const BrokenLine& other)
	{
		_size = other.size();
		_points = new Point<T>[_size];
		for (int i = 0; i < _size; ++i)
		{
			_points[i] = other[i];
		}

	}
	BrokenLine(const T m1, const T m2, const size_t amount)
	{
		srand(time(NULL));
		_size = amount;
		_points = new Point<T>[_size];

		if constexpr (std::is_integral<T>::value)
		{
			for (int i = 0; i < _size; ++i)
			{
				_points[i] = Point(T(int(m1) + rand() % (int(m2) - int(m1) + 1)), T(int(m1) + rand() % (int(m2) - int(m1) + 1)));
			}
		}
		else
		{
			for (int i = 0; i < _size; ++i)
			{
				size_t precision = 2;
				double x = rand() % (int)pow(10, precision);
				double y = rand() % (int)pow(10, precision);
				_points[i] = Point(T(m1 + (x / pow(10, precision)) * (m2 - m1)), T(m1 + (y / pow(10, precision)) * (m2 - m1)));
			}
		}
	}






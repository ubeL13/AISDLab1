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


	Point<T>& operator[](const size_t index)
	{
		if (index >= size() || index < 0)
		{
			throw std::out_of_range("BrokenLine::operator[]  invalid index");
		}
		return _points[index];
	}

	const Point<T>& operator[](const size_t index) const
	{
		if (index >= size() || index < 0)
		{
			throw std::out_of_range("BrokenLine::operator[]  invalid index");
		}
		return _points[index];
	}

	size_t size() const
	{
		return _size;
	}


	BrokenLine<T> operator+(const BrokenLine<T>& other) const
	{
		BrokenLine<T> new_line = BrokenLine(*this);
		new_line += other;
		return	new_line;
	}
	friend BrokenLine<T> operator+(const Point<T>& point, const BrokenLine<T>& line)
	{
		BrokenLine<T> new_line = BrokenLine(line.size() + 1);
		new_line[0] = point;
		for (int i = 1; i < new_line.size(); ++i)
		{
			new_line[i] = line[i - 1];
		};
		return new_line;
	}
	friend BrokenLine<T> operator+(const BrokenLine<T>& line, const Point<T>& point)
	{
		BrokenLine<T> new_line = BrokenLine(line.size() + 1);
		for (int i = 0; i < line.size(); ++i)
		{
			new_line[i] = line[i];
		};
		new_line[new_line.size() - 1] = point;
		return new_line;
	}
	BrokenLine<T>& operator=(const BrokenLine<T>& other)
	{
		BrokenLine<T> copy(other);
		_size = other.size();
		std::swap(this->_points, copy._points);
		return *this;
	}

	BrokenLine<T>& operator+=(const BrokenLine<T>& other)
	{
		size_t tmp_size = _size;
		_size = _size + other._size;
		Point<T>* copy = _points;
		_points = new Point<T>[_size];
		for (int i = 0; i < _size; ++i)
		{
			if (i < tmp_size)
			{
				_points[i] = copy[i];
			}
			else
			{
				_points[i] = other[i - tmp_size];
			}
		}
		return *this;
	}
	BrokenLine<T>& operator+=(const Point<T>& point)
	{
		_size = _size + 1;
		Point<T>* copy = _points;
		_points = new Point<T>[_size];
		for (int i = 0; i < _size; ++i)
		{
			if (i < _size - 1)
			{
				_points[i] = copy[i];
			}
			else
			{
				_points[i] = point;
			}
		}
		return *this;
	}
	double length(size_t index1, size_t index2) const
	{
		if (index1 >= size() || index1 < 0)
		{
			throw std::out_of_range("BrokenLine::operator[]  invalid index");
		}
		if (index2 >= size() || index2 < 0)
		{
			throw std::out_of_range("BrokenLine::operator[]  invalid index");
		}
		double len = 0;
		for (int i = index1; i <= index2 - 1; ++i)
		{
			double dx = _points[index1].x - _points[index1 + 1].x;
			double dy = _points[index1].y - _points[index1 + 1].y;
			dx = pow(dx, 2);
			dy = pow(dy, 2);
			len += sqrt(dx + dy);
		}
		return len;
	}
};
template<typename T>
std::ostream& operator<<(std::ostream& out, const Point<T>& point)
{
	out << "(" << point.x << ", " << point.y << ")" << std::endl;
	return out;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const BrokenLine<T>& line)
{
	for (int i = 0; i < line.size(); ++i)
	{
		out << "(" << line[i].x << ", " << line[i].y << ")" << std::endl;
	}
	return out;
}
template<typename T>
Point<T> rotate(float angle, Point<T> point, Point<T> center)
{
	Point<T> newpoint;
	newpoint.x = (point.x - center.x) * cos(angle) - (point.y - center.y) * sin(angle) + center.x;//��-� �������� 
	newpoint.y = (point.x - center.x) * sin(angle) + (point.y - center.y) * cos(angle) + center.y;
	return newpoint;
}

double angle(int n)
{
	return 2 * acos(-1.0) / n;
}

template<typename T>
BrokenLine<T> polygon(int N, T radius)
{
	BrokenLine<T> polygon(N + 1);
	double a = angle(N);
	polygon[0] = Point<T>(radius, 0);
	for (int i = 1; i < polygon.size(); ++i)
	{
		polygon[i] = rotate(a, polygon[i - 1], Point<float>(0.f, 0.f));

	}
	return polygon;
}



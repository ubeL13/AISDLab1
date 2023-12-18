#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>
#include <type_traits>
#include <complex>


template<typename T>
struct Point {
	T x, y;
	Point() : x(0), y(0) {}
	Point(T x, T y) : x(x), y(y) {}
	double len(const Point<T>& other) const {

		return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
	}
};

template<typename T>
class BrokenLine
{
private:
	Point<T>* _points;
	size_t _size;
	const double epsilon = 0.0001;

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
				_points[i]= Point(T(int(m1) + rand() % (int(m2) - int(m1) + 1)), T(int(m1) + rand() % (int(m2) - int(m1) + 1)));
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
	friend bool operator==(const BrokenLine<T>& line_1, const BrokenLine<T>& line_2) {
		if (line_1.size() != line_2.size()) {
			return false;
		}

		for (size_t i = 0; i < line_1.size(); ++i) {
			if (!(line_1[i].x == line_2[i].x && line_1[i].y == line_2[i].y)) {
				return false;
			}
		}

		return true; 
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
	


	double length() const
	{
		double total_length = 0.0;
		for (size_t i = 1; i < _size; ++i) {
			total_length += _points[i].len(_points[i - 1]);
		}
		return total_length;
	}
	double length(const Point<T>& a, const Point<T>& b) {
		return a.len(b);
	}
	double length(const Point<std::complex<T>>& a, const Point<std::complex<T>>& b) {
		return sqrt(pow((a.x.real() - b.x.real()), 2) + pow((a.y.imag() - b.y.imag()), 2));
	}





};
template<typename T>
std::complex<T> RandomComplex(T min, T max) {
	T real_part = min + static_cast<T>(rand()) / (static_cast<T>(RAND_MAX / (max - min)));
	T imag_part = min + static_cast<T>(rand()) / (static_cast<T>(RAND_MAX / (max - min)));
	return std::complex<T>(real_part, imag_part);
}




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
	newpoint.x = (point.x - center.x) * cos(angle) - (point.y - center.y) * sin(angle) + center.x;//ур-е поворота 
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



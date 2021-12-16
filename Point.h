#pragma once
#include <vector>
#include<string>
#include<iostream>

const double EPS = 10e-10;

enum Orient
{
	Colinear, // 0
	Clock, // 1
	CounterClock // 2
};

class Point
{
private:
	double m_x;
	double m_y;

public:
	Point(double x = 0, double y = 0) :
		m_x{ x }, m_y{ y } {}

	Point(const Point& coordinate){
		this->m_x = coordinate.m_x;
		this->m_y = coordinate.m_y;
	}

	Point& operator=(const Point& coordinate){
		this->m_x = coordinate.m_x;
		this->m_y = coordinate.m_y;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& out, const Point& point){
		out << point.m_x << '\t' << point.m_y;
		return out;
	}

	bool operator== (const Point& coordinate) const {
		return (abs(coordinate.m_x - this->m_x) <= EPS && abs(coordinate.m_y - this->m_y) <= EPS);
	}

	bool operator!= (const Point& coordinate) const {
		return (!(*this == coordinate));
	}

	friend void swap(Point& coordinate1, Point& coordinate2){
		Point tempCoordinate(coordinate1);
		coordinate1 = coordinate2;
		coordinate2 = tempCoordinate;
	}

	friend Orient orientation(const Point& point, const Point& point1, const Point& point2) { 
		double detLine = (point1.m_x - point.m_x) * (point2.m_y - point.m_y) - (point1.m_y - point.m_y) * (point2.m_x - point.m_x);
		if (detLine == 0)
			return Colinear;
		return (detLine > 0) ? CounterClock : Clock;
	}
	
	friend int JarvisAlgorithm(int& numOfPoints, const std::vector<Point> &points, const std::string& writeFilePath, bool timeMode); // Метод перебором

	friend int comparePoints(const void* vPoint1, const void* vPoint2);
	friend void qsortxi(std::vector<Point>& points, size_t size);
	friend int GrahamAlgorithm(int& numOfPoints, std::vector<Point> &points, const std::string& writeFilePath, bool timeMode); // Алгоритм Грэхема

};
	
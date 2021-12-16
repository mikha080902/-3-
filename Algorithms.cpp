#include "Point.h"
#include "PointsFiles.cpp"
#include <ctime>

// Алгоритм Джарвиса ("Метод перебора")
int JarvisAlgorithm(int& numOfPoints, const std::vector<Point> &points, const std::string& writeFilePath, bool timeMode){
	if (numOfPoints < 3)
		exit(3);

	time_t start, end;
	time(&start); // Начало блока

	std::vector<Point> convexHullPoints;
	convexHullPoints.reserve(numOfPoints);
	int numOfConvexHullPoints = 0;

	Point startConvexHullPoint(points[0]);
	for (int i = 1; i < numOfPoints; ++i){
		if (startConvexHullPoint.m_x > points[i].m_x)
			startConvexHullPoint = points[i];
		else
			if (startConvexHullPoint.m_x == points[i].m_x && startConvexHullPoint.m_y > points[i].m_y)
				startConvexHullPoint = points[i];
	}

	unsigned int start_time = clock(); // Начальное время алгоритма алгоритма Джарвиса
	Point currentPoint(startConvexHullPoint);
	do{
		convexHullPoints.push_back(currentPoint);
		numOfConvexHullPoints++;
		Point potentialPoint(points[0]);
		for (int i = 1; i < numOfPoints; ++i)
		{
			if (orientation(currentPoint, points[i], potentialPoint) == CounterClock || potentialPoint == currentPoint)
				potentialPoint = points[i];
		}
		currentPoint = potentialPoint;

	} while (currentPoint != startConvexHullPoint);
	unsigned int end_time = clock(); // Конечное время алгоритма Джарвиса
	unsigned int search_time = end_time - start_time; // Длительность алгоритма Джарвиса
	std::cout << "Jarvis algoritm: " << search_time / 1000.0 << '\n';

	if (convexHullPoints.empty())
		return 0;

	time(&end); // Конец блока
	double seconds = difftime(end, start); // Длительность блока

	writePoints(numOfConvexHullPoints, convexHullPoints, writeFilePath, seconds, timeMode);

	return 1;
}


// Вспомогательная функция для быстрой сортировки через функцию std::qsort по степени левизны относительно точки startSortPoint элементов
Point startSortPoint;
int comparePoints(const void* vPoint1, const void* vPoint2){
	Point* point1 = (Point*)vPoint1;
	Point* point2 = (Point*)vPoint2;

	
	if (orientation(startSortPoint, *point1, *point2) == Colinear){
		if (point1->m_x == point2->m_x)
			return (point1->m_y < point2->m_y) ? -1 : 1;
		else
			return (point1->m_x < point2->m_x) ? -1 : 1;
	}

	return (orientation(startSortPoint, *point1, *point2) == CounterClock) ? -1 : 1;
}

// Алгоритм Грэхема
int GrahamAlgorithm(int& numOfPoints, std::vector<Point> &points, const std::string& writeFilePath, bool timeMode = 0){
	if (numOfPoints < 3)
		exit(3);

	time_t start, end;
	time(&start); // Начало блока

	Point startConvexHullPoint(points[0]);
	int startIndex = 0;
	for (int i = 0; i < numOfPoints; ++i){
		if (startConvexHullPoint.m_x > points[i].m_x){
			startConvexHullPoint = points[i];
			startIndex = i;
		}
		else
			if (startConvexHullPoint.m_x == points[i].m_x && startConvexHullPoint.m_y > points[i].m_y){
				startConvexHullPoint = points[i];
				startIndex = i;
			}
	}

	swap(points[0], points[startIndex]);

	startSortPoint = startConvexHullPoint;

	unsigned int start_time = clock(); // Начальное время сортировки
	//std::qsort(&points[1], numOfPoints - 1, sizeof(Point), comparePoints);
	qsortxi(points, numOfPoints);
	unsigned int end_time = clock(); // Конечное время сортировки
	unsigned int search_time = end_time - start_time; // Длительность сортировки
	std::cout << "Graham sort: " << search_time / 1000.0 <<'\n';

	unsigned int start_time1 = clock(); // Начальное время удаления одинаковых точек
	int i = 0;
	while (i < numOfPoints - 1) {
		if (points[i] == points[i + 1])
		{
			points.erase(points.begin() + i);
			numOfPoints--;
			i--;
		}
		i++;
	}
	unsigned int end_time1 = clock(); // Конечное время удаления одинаковых точек
	unsigned int search_time1 = end_time1 - start_time1; // Длительность удаления одинаковых точек
	std::cout << "Check same points: " << search_time1 / 1000.0 << '\n';

	std::vector<Point> convexHullPoints;
	convexHullPoints.reserve(numOfPoints);
	int numOfConvexHullPoints = 0;
	
	convexHullPoints.push_back(points[0]);
	numOfConvexHullPoints++;

	convexHullPoints.push_back(points[1]);
	numOfConvexHullPoints++;

	unsigned int start_time2 = clock(); // Начальное время алгоритма 
	for (int i = 2; i < numOfPoints; ++i){
		while (orientation(*(convexHullPoints.end() - 2), *(convexHullPoints.end() - 1), points[i]) == Clock){
			convexHullPoints.pop_back();
			numOfConvexHullPoints--;
		}
		convexHullPoints.push_back(points[i]);
		numOfConvexHullPoints++;
	}
	unsigned int end_time2 = clock(); // Конечное время алгоритма
	unsigned int search_time2 = end_time2 - start_time2; // Длительность алгоритма
	std::cout << "Graham algorithm:  " << search_time2 / 1000.0 << '\n';

	if (convexHullPoints.empty())
		return 0;
	
	time(&end); // Конец блока 
	double seconds = difftime(end, start); // Время, затраченное на весь блок

	writePoints(numOfConvexHullPoints, convexHullPoints, writeFilePath, seconds, timeMode);

	return 1;
}
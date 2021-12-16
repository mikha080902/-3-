#include"Point.h" 
#include"PointsFiles.cpp"
#include"FileNames.h"
#include"PRNG.h"
#include<cstdlib>
#include<ctime>

int main()
{
	PRNG generator;
	initGenerator(generator);

	int numOfPoints1 = 0;
	std::vector<Point> points1;

	int numOfPoints2 = 0;
	std::vector<Point> points2;

	int numOfPoints3 = 10000000;
	std::vector<Point> points3;
	generateRandomPoints(points3, generator, numOfPoints3, -1.234, 1.234);
	writePoints(numOfPoints3, points3, problem3);

	readPoints(numOfPoints1, points1, problem1);
	GrahamAlgorithm(numOfPoints1, points1, GSolution1, 1);
	JarvisAlgorithm(numOfPoints1, points1, JSolution1, 1);

	readPoints(numOfPoints2, points2, problem2);
	JarvisAlgorithm(numOfPoints2, points2, JSolution2, 1);
	GrahamAlgorithm(numOfPoints2, points2, GSolution2, 1);

	JarvisAlgorithm(numOfPoints3, points3, JSolution3, 1);
	GrahamAlgorithm(numOfPoints3, points3, GSolution3, 1);
	
	return 0;
}
#include<fstream> // Для файлового вывода/ ввода
#include <vector> // Для вектора точек
#include <iomanip> // Для установки точности вывода точек

template <typename T>
int readPoints(int& numOfPoints, std::vector<T>& points, const std::string &readFilePath){
	std::ifstream file;
	file.open(readFilePath);

	if (!file.is_open())
		exit(-1);

	file >> numOfPoints;
	points.reserve(numOfPoints);

	double x, y;
	for (int i = 0; i < numOfPoints; ++i){
		file >> x;
		file >> y;
		points.push_back(T(x, y));
	}

	file.close();

	if (points.empty())
		exit(-2);

	return 1;
}

template <typename T>
int writePoints(int numOfPoints, std::vector<T>& points, const std::string &writeFilePath, unsigned int time = 0, bool timeMode = 0){
	std::ofstream file;
	file.open(writeFilePath);

	if (!file.is_open())
		exit(-3);

	if (timeMode)
		file << "Total time: " << time << " seconds." << '\n';

	file << numOfPoints << '\n';

	for (int i = 0; i < numOfPoints; ++i)
		file << std::setprecision(17) << points[i] << '\n';

	file.close();

	return 1;
}

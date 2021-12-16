#pragma once
#include <random>
#include <cassert>
struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG& generator)
{
    // ������ ������-���������� ��� ��������� ���������� �����.
    std::random_device device;
    // �������� ��������� ����� ������������������
    generator.engine.seed(device());
}

// ���������� ����� ����� � ��������� [minValue, maxValue)
unsigned random(PRNG& generator, unsigned minValue, unsigned maxValue)
{
    // ��������� ������������ ����������
    assert(minValue < maxValue);

    // ������ �������������
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);

    // ��������� ��������������� �����: ������� ������������� ��� �������,
    //  ������� ��������� ������������ ����� ����� ��� ��������.
    return distribution(generator.engine);
}

// ���������� ����� � ��������� ������ � ��������� [minValue, maxValue)
float getRandomFloat(PRNG& generator, float minValue, float maxValue)
{
    // ��������� ������������ ����������
    assert(minValue < maxValue);

    // ������ �������������
    std::uniform_real_distribution<double> distribution(minValue, maxValue);

    // ��������� ��������������� �����: ������� ������������� ��� �������,
    //  ������� ��������� ������������ ����� ����� ��� ��������.
    return distribution(generator.engine);
}

template <typename T>
void generateRandomPoints(std::vector<T>& points, PRNG& generator, int numOfPoints, int minCoord, int maxCoord)
{
    points.reserve(numOfPoints);
    for (int i = 0; i < numOfPoints; ++i)
        points.push_back(T(getRandomFloat(generator, minCoord, maxCoord), getRandomFloat(generator, minCoord, maxCoord)));
}
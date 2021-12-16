#pragma once
#include <random>
#include <cassert>
struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG& generator)
{
    // Создаём псевдо-устройство для получения случайного зерна.
    std::random_device device;
    // Получаем случайное зерно последовательности
    generator.engine.seed(device());
}

// Генерирует целое число в диапазоне [minValue, maxValue)
unsigned random(PRNG& generator, unsigned minValue, unsigned maxValue)
{
    // Проверяем корректность аргументов
    assert(minValue < maxValue);

    // Создаём распределение
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);

    // Вычисляем псевдослучайное число: вызовем распределение как функцию,
    //  передав генератор произвольных целых чисел как аргумент.
    return distribution(generator.engine);
}

// Генерирует число с плавающей точкой в диапазоне [minValue, maxValue)
float getRandomFloat(PRNG& generator, float minValue, float maxValue)
{
    // Проверяем корректность аргументов
    assert(minValue < maxValue);

    // Создаём распределение
    std::uniform_real_distribution<double> distribution(minValue, maxValue);

    // Вычисляем псевдослучайное число: вызовем распределение как функцию,
    //  передав генератор произвольных целых чисел как аргумент.
    return distribution(generator.engine);
}

template <typename T>
void generateRandomPoints(std::vector<T>& points, PRNG& generator, int numOfPoints, int minCoord, int maxCoord)
{
    points.reserve(numOfPoints);
    for (int i = 0; i < numOfPoints; ++i)
        points.push_back(T(getRandomFloat(generator, minCoord, maxCoord), getRandomFloat(generator, minCoord, maxCoord)));
}
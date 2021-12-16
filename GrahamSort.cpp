#include"Point.h"
#include"Stack.h"

void qsortxi(std::vector<Point>& points, size_t size) {
	size_t i, j;
	Point tmp, pivot;
	Stack* lows = createStack();
	Stack* highs = createStack();
	size_t low, high;

	push(lows, 1);
	push(highs, size - 1);

	while (lows->size > 0) {
		low = pop(lows);
		high = pop(highs);
		i = low;
		j = high;
		pivot = points[(low + (high - low) / 2)];
		do {
			while (orientation(points[0], pivot, points[i]) == Clock) {
				i++;
			}
			while (orientation(points[0], pivot, points[j]) == CounterClock) {
				j--;
			}
			if (i <= j) {
				if (orientation(points[0], points[i], points[j]) == Clock) {
					swap(points[i], points[j]);
				}
				i++;
				if (j > 1) {
					j--;
				}
			}
		} while (i <= j);

		if (i < high) {
			push(lows, i);
			push(highs, high);
		}
		if (j > low) {
			push(lows, low);
			push(highs, j);
		}
	}

	freeStack(&lows);
	freeStack(&highs);
}


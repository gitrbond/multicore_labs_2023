#ifndef QSORT_SEQUENT_H
#define QSORT_SEQUENT_H

#include <iostream>
#include <vector>

int partition(std::vector<long int> &v, int start, int end) {
	int pivot = end;
	int j = start;
	for (int i = start; i < end; ++i) {
		if (v[i] < v[pivot]) {
			std::swap(v[i], v[j]);
			++j;
		}
	}
	std::swap(v[j], v[pivot]);
	return j; // return size of first part
}

void sequentialQsort(std::vector<long int> &v, int start, int end) {
	if (start < end) {
		int p = partition(v, start, end);
		sequentialQsort(v, start, p - 1);
		sequentialQsort(v, p + 1, end);
	}
}

#endif // QSORT_SEQUENT_H

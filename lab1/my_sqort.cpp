#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "qsort_sequent.h"
#include "qsort_parall.h"

#include <parlay/io.h>
#include <parlay/primitives.h>
//#include <parlay/internal/sequence_ops.h> // tabulate
#include <parlay/random.h>
#include <parlay/sequence.h> // sequence
#include <parlay/internal/get_time.h>

std::vector<long int> get_random_vector(long int n);
int partition(std::vector<long int> &v, int start, int end);
void sequentialQuicksort(std::vector<long int> &v, int start, int end);
void printVector(std::vector<long int> v);
void check_sorted(parlay::sequence<long> v);
void check_sorted(std::vector<long> v);

#define SIZE 30000000

int main() {
	srand((unsigned)time(0));

	std::cout << "sorting array of size " << SIZE << "\n";

	parlay::random_generator gen;
    std::uniform_int_distribution<long> dis(0, SIZE - 1);
    parlay::sequence<long> v1 = parlay::tabulate(SIZE, [&] (long i) {
      auto r = gen[i];
      return dis(r);
    });

	std::cout << "Parallel qsort" << std::endl;
	auto start = std::chrono::steady_clock::now();
	parlay::sequence<long> result = parallQsort(v1);
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds_p = end-start;
	std::cout << "elapsed time: " << elapsed_seconds_p.count()*1000 << " ms\n";
	check_sorted(result);

	std::cout << "\n";
	std::vector<long> v2 = get_random_vector(SIZE);

	std::cout << "Sequential qsort" << std::endl;
	auto start1 = std::chrono::steady_clock::now();
	sequentialQsort(v2, 0, v2.size() - 1);
	auto end1 = std::chrono::steady_clock::now();
	std::chrono::duration<double> elapsed_seconds_s = end1 - start1;
	std::cout << "elapsed time: " << elapsed_seconds_s.count()*1000 << " ms\n";
	check_sorted(v2);

	std::cout << "\n";
	std::cout << "Acceleration = " << elapsed_seconds_s / elapsed_seconds_p << " times\n";

	return 0;
}

std::vector<long> get_random_vector(long n) {
	std::vector<long> v(n);
	for (int i = 0; i < n; ++i)
		v[i] = rand() % SIZE;
	return v;
}

void printVector(std::vector<long int> v) {
	for(int i = 0; i < v.size(); ++i)
		std::cout << v[i] << " ";
	std::cout << "\n";
}

void check_sorted(parlay::sequence<long> v) {
	for(int i = 0; i < v.size() - 1; i++) {
		if(v[i] > v[i + 1]) {
			std::cout << "not sorted!\n";
			return;
		}
	}
	std::cout << "sorted!\n";
	return;
}

void check_sorted(std::vector<long> v) {
	for(int i = 0; i < v.size() - 1; i++) {
		if(v[i] > v[i + 1]) {
			std::cout << "not sorted!\n";
			return;
		}
	}
	std::cout << "sorted!\n";
	return;
}

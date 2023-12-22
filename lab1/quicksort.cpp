/*#include <iostream>
#include <string>
#include <random>

#include <parlay/io.h>
#include <parlay/primitives.h>
#include <parlay/random.h>
#include <parlay/sequence.h>
#include <parlay/internal/get_time.h>

//#include "quicksort.h"
#include "qsort_parall.h"

void check_sorted(parlay::sequence<long> v) {
	for(int i = 0; i < v.size() - 1; i++) {
		if(v[i] > v[i + 1]) {
			std::cout << "not sorted, " << v[i] << " > " << v[i+1] << "!\n";
			return;
		}
	}
	std::cout << "sorted!\n";
	return;
}

void print_sequence(parlay::sequence<long> v) {
	for(int i = 0; i < v.size(); ++i)
		std::cout << v[i] << " ";
	std::cout << "\n";
}

// **************************************************************
// Driver
// **************************************************************
int main(int argc, char* argv[]) {
  auto usage = "Usage: quicksort <n>";
  if (argc != 2) std::cout << usage << std::endl;
  else {
    long n;
    try { n = std::stol(argv[1]); }
    catch (...) { std::cout << usage << std::endl; return 1; }
    parlay::random_generator gen;
    std::uniform_int_distribution<long> dis(0, n-1);

    // generate random long values
    auto data = parlay::tabulate(n, [&] (long i) {
      auto r = gen[i];
      return dis(r);
    });

    parlay::internal::timer t("Time");
    parlay::sequence<long> result = parallQsort(data);;
    //for (int i=0; i < 5; i++) {
    //  result
    //  t.next("parallQsort");
    //}
    //print_sequence(result);
    check_sorted(result);

    auto first_ten = result.tail(10);

    //std::cout << "first 10 elements: " << parlay::to_chars(first_ten) << std::endl;
  }
}
     */

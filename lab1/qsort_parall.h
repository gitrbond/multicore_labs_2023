#ifndef QSORT_PARALL_H
#define QSORT_PARALL_H

#include <algorithm>
#include <functional>

#include <parlay/parallel.h>
#include <parlay/primitives.h>
#include <parlay/sequence.h>

#include "qsort_sequent.h" // partition

// **************************************************************
// Parallel Quicksort
// **************************************************************
template <typename Range, typename Less>
void sortParall(Range in, Range out, Less less) {
  long n = in.size();
  //std::cout << "size=" << n << "\n";
  //std::cout << "type(in)=" << typeid(in).name() << "\n";
  if (n < 10000) {
    parlay::copy(in, out);
    std::sort(out.begin(), out.end(), less);
  } else {
	//std::cout << "finding pivot\n";
    //auto pivot = parlay::sort(parlay::tabulate(101, [&] (long i) {
      //return in[i*n/101];}))[50];
    //long pivot = parlay::sort(parlay::tabulate(101, [&] (long i) {
      //return in[i*n/101];}))[50];
    long pivot = in[0];
	//std::cout << "pivot=" << pivot << " found\n";
	// TODO sequential partition
    auto [x, offsets] = parlay::counting_sort(in, 3, [&] (auto k) {
      return less(k, pivot) ? 0u : less(pivot, k) ? 2u : 1u;});
    //std::cout << "partition made\n";
    auto& split = x;
    long nl = offsets[1];
    long nm = offsets[2];
    try {
		parlay::copy(split.cut(nl,nm), out.cut(nl,nm));
	}
	catch (...) {
		std::cout << "Exception while parlay::copy()\n";
	}
    //std::cout << "copied\n";
    try {
		parlay::par_do(
			[&] { sortParall(split.cut(0,nl), out.cut(0,nl), less);},
			[&] { sortParall(split.cut(nm,n), out.cut(nm,n), less);});
	}
	catch (...) {
		std::cout << "Exception while parlay::par_do()\n";
	}
	//std::cout << "done\n";
  }
}

template <typename Range, typename Less = std::less<>>
auto parallQsort(Range& in) {
	long n = in.size();
	using T = typename Range::value_type;
	parlay::sequence<T> out(n);
	//std::cout << "debug-1\n";
	Less less = {};
	sortParall(in.cut(0,n), out.cut(0,n), less);
	return out;
}

#endif // QSORT_PARALL_H

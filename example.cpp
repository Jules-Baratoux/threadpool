#include <cstdlib>
#include <iostream>
#include <cassert>
#include <sstream>
#include <string>
#include "threadpool.hpp"
using std::stoi;
void stress(threadpool&, int);


// SIMPLIFIED DECLARATION ---------------------------------------------------------
#if 0

class threadpool
{
	constructor(size_type N);		 // creates a thread pool with N waiting threads

	std::future<R>	push(const T& function); // schedules a new task
};

#endif
// --------------------------------------------------------------------------------


int			A(void)
{
	return 'A';
}

int			B(int i)
{
	std::stringstream ss; ss << '[' << i << ']';
	std::cout <<  ss.str() << std::endl;
	return 'B';
}

int			main(const int argc, const char *argv[])
{
	const int	iterations = argc > 1 ? stoi(argv[1]) : 0;
	const int	amount	   = argc > 2 ? stoi(argv[2]) : 4;

	// EXAMPLE
	threadpool	pool(amount);

	auto		future1 = pool.push(A);
	auto		future2 = pool.push(B, 42);

	assert(future1.get() == 'A');
	assert(future2.get() == 'B');

	// STRESS TEST
	stress(pool, iterations);
}


void			stress(threadpool& pool, int max)
{
	vector< std::future<decltype(B(0))> >	futures;
	futures.resize(max);
	for (auto i = 0; i < max; ++i) futures[i] = pool.push(B, i);
	for (auto i = 0; i < max; ++i) assert(futures[i].get() == 'B');
}

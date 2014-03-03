threadpool
==========

A C++11 threadpool trivial implementation

	threadpool	pool(4); // 4 threads

	auto		future1 = pool.push(A);
	auto		future2 = pool.push(B, 42);

	out << future1.get()
		<< future2.get()
		<< endl

##Compilation

Compiles with CLANG with the following CXXFLAGS:

    -std=c++11 -pthread -Wall

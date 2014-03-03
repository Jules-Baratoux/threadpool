threadpool
==========

A C++11 threadpool trivial implementation

Simplified declaration
```c++
class threadpool
{
	constructor(size_type N);		 // creates a thread pool with N waiting threads

	std::future<R>	push(const T& function); // schedules a new task
};
```

Example
```c++
threadpool	pool(4); // 4 threads

auto		future1 = pool.push(A);
auto		future2 = pool.push(B, 42);

out << future1.get()
	<< future2.get()
	<< endl
```

##Compilation

Compiles with CLANG with the following CXXFLAGS:

```shell
-std=c++11 -pthread -Wall
```

threadpool
==========

A C++11 threadpool trivial implementation

**Simplified declaration**
```c++
class threadpool
{
	constructor(size_type N);		 // creates a thread pool with N waiting threads

	std::future			push<F>(const F& function); // schedules a new task
};
```

**Example**
```c++
int			main(void)
{
	threadpool	pool(4);

	auto		future1 = pool.push(A);
	auto		future2 = pool.push(B, 42);

	result1 = future1.get();
	result2 = future2.get();
}
```

##Compilation

Compiles with CLANG with the following CXXFLAGS:

```shell
-std=c++11 -pthread -Wall
```

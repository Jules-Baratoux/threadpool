threadpool
==========

A C++11 threadpool trivial implementation

**Simplified declaration**
```c++
class threadpool
{
	threadpool(size_type N); // creates a thread pool with N waiting threads


	std::future	push<F      >(const F& function); // schedules a new task
	std::future	push<F, A...>(const F& function, A... args);
};
```

**Example**
```c++
int			A(void)
{
	return 'A';
}

int			B(int val)
{
	return val;
}

int			main(void)
{
	threadpool	pool(4);

	auto		future1 = pool.push(A);
	auto		future2 = pool.push(B, 42);

	int		result1 = future1.get();
	int		result2 = future2.get();
}
```

##Compilation

Compiles with CLANG with the following CXXFLAGS:

```shell
-std=c++11 -pthread -Wall
```

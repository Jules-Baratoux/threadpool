threadpool
==========

A trivial threadpool implementation using C++11

**Simplified declaration**
```c++
class threadpool
{
	explicit threadpool(size_type N); // creates a thread pool with N waiting threads

	std::future	push(const F& function, A... args); // schedules a new task
};
```

**Example**
```c++
char A(void)
{
	return 'A';
}

int B(int val)
{
	return val;
}

int main(void)
{
	threadpool	pool(4);

	auto		future1 = pool.push(A);
	auto		future2 = pool.push(B, 42);

	char		result1 = future1.get();
	int		result2 = future2.get();
}
```

##Compilation

Compiles with CLANG with the following CXXFLAGS:

```shell
-std=c++11 -pthread -Wall
```

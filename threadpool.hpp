#pragma once
#include <chrono>
#include <vector>
#include <deque>
#include <functional>
#include <future>
#include <thread>
#include <condition_variable>
#include <algorithm>

using std::condition_variable;
using std::deque;
using std::function;
using std::future;
using std::mutex;
using std::packaged_task;
using std::thread;
using std::unique_lock;
using std::vector;

class threadpool
{
	using pool_type  = vector<thread>;
	using tasks_type = deque<function<void()>>;
	using size_type  = pool_type::size_type;

	bool			running = true;
	mutex			access;
	condition_variable	condition;
	tasks_type		tasks;
	pool_type		pool;

	public:
	explicit threadpool(size_type thread_amount)
	{
		assert(thread_amount > 0);
		while (thread_amount --> 0)
		{
			create_thread();
		}
	}


#define IMPL(PTR, LAMBDA)			\
	auto future = (PTR)->get_future();	\
	unique_lock<mutex> lock(access);	\
	tasks.push_back(LAMBDA);		\
	condition.notify_one();			\
	return std::move(future);

	template<typename Ret>
	auto push(packaged_task<Ret()>& task) -> future<Ret>
	{
		IMPL(&task, [&task]{task();});
	}

	template<typename Func, typename... Args>
	auto push(const Func& func, Args... args) -> future< decltype(func(args...)) >
	{
		const auto ptr	  = new packaged_task<Func>(func);

		IMPL(ptr, ([ptr, args...] { (*ptr)(args...); delete ptr; }) );
	}

#undef IMPL


	~threadpool(void)
	{
		running = false;
		condition.notify_all();
		for (auto &thread : pool)
		{
			thread.join();
		}
		pool.clear();
	}

	private:
	inline void create_thread(void)
	{
		auto start = [this](void)
		{
			while (running)
			{
				function<void()> task;
				{
					unique_lock<mutex> lock(access);

					if (tasks.empty())
					{
						condition.wait(lock);
						continue;
					}
					task = std::move(tasks.front());
					tasks.pop_front();
				}
				task();
			}
		};

		thread thread(start);
		pool.push_back(std::move(thread));
	}

	threadpool(const threadpool&)            = delete;
	threadpool& operator=(const threadpool&) = delete;
};


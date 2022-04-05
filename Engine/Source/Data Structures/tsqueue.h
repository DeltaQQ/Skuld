#pragma once
#include <deque>
#include <mutex>
#include <condition_variable>

template <typename T>
class tsqueue
{
public:
	tsqueue() = default;
	tsqueue(const tsqueue<T>&) = delete;
	~tsqueue() { clear(); }

	const T& front()
	{
		std::scoped_lock lock(m_deque_mutex);
		return m_deque.front();
	}

	const T& back()
	{
		std::scoped_lock lock(m_deque_mutex);
		return m_deque.back();
	}

	T pop_front()
	{
		std::scoped_lock lock(m_deque_mutex);
		auto value = std::move(m_deque.front());
		m_deque.pop_front();

		return value;
	}

	T pop_back()
	{
		std::scoped_lock lock(m_deque_mutex);
		auto value = std::move(m_deque.back());
		m_deque.pop_back();

		return value;
	}

	void push_back(const T& value)
	{
		std::scoped_lock lock(m_deque_mutex);
		m_deque.emplace_back(std::move(value));
	}

	void push_front(const T& value)
	{
		std::scoped_lock lock(m_deque_mutex);
		m_deque.emplace_front(std::move(value));
	}

	bool empty()
	{
		std::scoped_lock lock(m_deque_mutex);
		return m_deque.empty();
	}

	size_t size()
	{
		std::scoped_lock lock(m_deque_mutex);
		return m_deque.size();
	}

	void clear()
	{
		std::scoped_lock lock(m_deque_mutex);
		m_deque.clear();
	}

	void wait()
	{
		while (empty())
		{
			std::unique_lock<std::mutex> lock(m_blocking);
			m_condition_variable.wait(lock);
		}
	}

private:
	std::deque<T> m_deque;
	std::mutex m_deque_mutex;

	std::condition_variable m_condition_variable;
	std::mutex m_blocking;
};

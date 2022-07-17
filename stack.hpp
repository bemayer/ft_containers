#ifndef STACK_HPP
#define STACK_HPP

#include "utility.hpp"
#include "vector.hpp"

namespace ft
{
	/** @stack
	 * All required attributes and methods from:
	 * https://en.cppreference.com/w/cpp/container/stack
	 */
	template <typename T, typename Container = ft::vector<T> >
	struct stack
	{
		typedef Container                                container_type;
		typedef typename container_type::value_type      value_type;
		typedef typename container_type::size_type       size_type;
		typedef typename container_type::reference       reference;
		typedef typename container_type::const_reference const_reference;
		container_type                                   c;
		stack(const Container &cont = container_type()) : c(cont){};

		stack(const stack &other) : c(other.c)
		{
		}

		~stack(){};

		stack &operator=(const stack &other)
		{
			c = other.c;
			return *this;
		}

		reference top()
		{
			return c.back();
		}

		const_reference top() const
		{
			return c.back();
		}

		bool empty() const
		{
			return c.empty();
		}

		size_type size() const
		{
			return c.size();
		}

		void push(const value_type &value)
		{
			c.push_back(value);
		}

		void pop()
		{
			c.pop_back();
		}
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container> &lhs,
					const stack<T, Container> &rhs)
	{
		return lhs.c == rhs.c;
	}

	template <class T, class Container>
	bool operator<(const stack<T, Container> &lhs,
				   const stack<T, Container> &rhs)
	{
		return lhs.c < rhs.c;
	}

	template <class T, class Container>
	bool operator!=(const stack<T, Container> &lhs,
					const stack<T, Container> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<=(const stack<T, Container> &lhs,
					const stack<T, Container> &rhs)
	{
		return lhs < rhs || lhs == rhs;
	}

	template <class T, class Container>
	bool operator>(const stack<T, Container> &lhs,
				   const stack<T, Container> &rhs)
	{
		return !(lhs <= rhs);
	}

	template <class T, class Container>
	bool operator>=(const stack<T, Container> &lhs,
					const stack<T, Container> &rhs)
	{
		return !(lhs < rhs);
	}
}// namespace ft

#endif

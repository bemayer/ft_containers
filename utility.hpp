#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <cstddef>
#include <iostream>
#include <iterator>
#include <sstream>
#include <cstdlib>
#include <ctime>



#include <utility>

namespace ft
{
	struct input_iterator_tag
	{
	};

	struct output_iterator_tag
	{
	};

	struct forward_iterator_tag : public input_iterator_tag
	{
	};

	struct bidirectional_iterator_tag : public forward_iterator_tag
	{
	};

	struct random_access_iterator_tag : public bidirectional_iterator_tag
	{
	};

	template <typename T>
	struct iterator_traits
	{
		typedef std::ptrdiff_t             difference_type;
		typedef T                          value_type;
		typedef T						 *pointer;
		typedef T						 &reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T>
	{
		typedef std::ptrdiff_t             difference_type;
		typedef T                          value_type;
		typedef const T                   *pointer;
		typedef const T                   &reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template <typename T>
	struct iterator_traits<T *>
	{
		typedef std::ptrdiff_t             difference_type;
		typedef T                          value_type;
		typedef T						 *pointer;
		typedef T						 &reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T *>
	{
		typedef std::ptrdiff_t             difference_type;
		typedef T                          value_type;
		typedef const T                   *pointer;
		typedef const T                   &reference;
		typedef random_access_iterator_tag iterator_category;
	};

	/*
	 * https://en.cppreference.com/w/cpp/iterator/reverse_iterator
	 */
	template <typename T>
	class reverse_iterator : public T
	{
	public:
		// Member types
		typedef T							iterator_type;
		using typename T::difference_type;
		using typename T::iterator_category;
		using typename T::pointer;
		using typename T::reference;
		using typename T::value_type;

		// Constructors
		reverse_iterator() : _iterator(){}

		reverse_iterator(T &other): _iterator(other)
		{
		}

		template <typename U>
		reverse_iterator(const reverse_iterator<U> &other): _iterator(other.base())
		{
		}

		template <typename U>
		reverse_iterator operator=(const reverse_iterator<U> &u) {
			if (reinterpret_cast<const void *>(this) == reinterpret_cast<const void *>(&u))
				return (*this);
			this->_base = u.base();
			return (*this);
		};

		// Operators
		reference operator*()
		{
			T tmp = _iterator;
			tmp--;
			return *tmp;
		}

		pointer operator->()
		{
			T tmp = _iterator;
			tmp--;
			return tmp.operator->();
		}

		reference operator*() const
		{
			T tmp = _iterator;
			tmp--;
			return *tmp;
		}

		pointer operator->() const
		{
			T tmp = _iterator;
			tmp--;
			return tmp.operator->();
		}

		reference operator[](difference_type n) const
		{
			return reference(*this->operator+(n));
		}

		reverse_iterator &operator++()
		{
			T tmp = _iterator;
			_iterator--;
			return tmp;
		}

		reverse_iterator &operator--()
		{
			T tmp = _iterator;
			_iterator++;
			return tmp;
		}

		reverse_iterator operator++(int)
		{
			T tmp = _iterator;
			_iterator--;
			return tmp;
		}

		reverse_iterator operator--(int)
		{
			return _iterator++;
		}

		reverse_iterator operator+(difference_type n) const
		{
			return _iterator - n;
		}

		reverse_iterator operator-(difference_type n) const
		{
			return _iterator + n;
		}

		reverse_iterator &operator+=(difference_type n)
		{
			_iterator -= n;
			return *_iterator;
		}

		reverse_iterator &operator-=(difference_type n)
		{
			_iterator += n;
			return *_iterator;
		}

		T base()
		{
			return _iterator;
		}

		T base() const
		{
			return _iterator;
		}

	private:
		iterator_type _iterator;
	};

	template <typename T>
	void ft_swap(T &a, T &b)
	{
		T tmp(a);
		a = b;
		b = tmp;
	}

	template <bool Cond, class T = void>
	struct enable_if;

	template <typename T>
	struct is_integral;

	template <typename InputIterator1, typename InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2)
	{
		while ((first1 != last1) && (first2 != last2))
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
			first1++;
			first2++;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <typename InputIterator1, typename InputIterator2>
	bool	equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (true)
		{
			if ((first1 == last1) && (first2 == last2))
				return true;
			if (first1 == last1)
				return false;
			if (first2 == last2)
				return false;
			if (*first1 != *first2)
				return false;
			first1++;
			first2++;
		}
		return true;
	}


	template <typename T>
	typename iterator_traits<T>::difference_type distance(T first, T last)
	{
		typename iterator_traits<T>::difference_type result = 0;
		while (first != last)
		{
			first++;
			result++;
		}
		return result;
	}

	template <typename T>
	struct less
	{
		bool operator()(const T &x, const T &y) const
		{
			return x < y;
		}
	};

	template <typename T1, typename T2>
	struct pair
	{
		typedef T1  first_type;
		typedef T2  second_type;

		first_type  first;
		second_type second;

		pair(): first(first_type()), second(second_type()) {}

			  pair(const first_type &first, const second_type &second)
			: first(first), second(second)
		{
		}

		template <typename U1, typename U2>
		pair& operator=(const pair<U1, U2> &other)
		{
			first = other.first;
			second = other.second;
			return *this;
		}

		template <class U1, class U2>
		pair(const pair<U1, U2> &other)
			: first(other.first), second(other.second)
		{
		}
	};

	template <typename T1, typename T2>
	bool operator==(const pair<T1, T2> &x, const pair<T1, T2> &y)
	{
		return x.first == y.first && x.second == y.second;
	}

	template <typename T1, typename T2>
	bool operator<(const pair<T1, T2> &x, const pair<T1, T2> &y)
	{
		return x.first < y.first ||
			   (!(y.first < x.first) && x.second < y.second);
	}

	template <typename T1, typename T2>
	bool operator!=(const pair<T1, T2> &x, const pair<T1, T2> &y)
	{
		return !(x == y);
	}

	template <typename T1, typename T2>
	bool operator>(const pair<T1, T2> &x, const pair<T1, T2> &y)
	{
		return y < x;
	}

	template <typename T1, typename T2>
	bool operator<=(const pair<T1, T2> &x, const pair<T1, T2> &y)
	{
		return !(y < x);
	}

	template <typename T1, typename T2>
	bool operator>=(const pair<T1, T2> &x, const pair<T1, T2> &y)
	{
		return !(x < y);
	}

	template <typename T1, typename T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return pair<T1, T2>(x, y);
	}


}// namespace ft

#endif

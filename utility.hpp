#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>

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
		typedef T iterator_type;
		using typename T::difference_type;
		using typename T::iterator_category;
		using typename T::pointer;
		using typename T::reference;
		using typename T::value_type;

		// Constructors
		reverse_iterator() : _iterator()
		{
		}

		reverse_iterator(const T &other) : _iterator(other)
		{
		}

		template <typename U>
		reverse_iterator(const reverse_iterator<U> &other)
			: _iterator(other.base())
		{
		}

		operator reverse_iterator<const T>() const
		{
			return reverse_iterator<const T>(_iterator);
		}

		//		template <typename U>
		//		reverse_iterator operator=(const reverse_iterator<U> &other) {
		//			if (static_cast<const void *>(this) == static_cast<const void
		//*>(&other)) 				return *this; 			this->_base = other.base();
		//return (*this);
		//		};

		// Operators
		reference operator*()
		{
			iterator_type tmp = _iterator;
			tmp--;
			return *tmp;
		}

		pointer operator->()
		{
			iterator_type tmp = _iterator;
			tmp--;
			return tmp.operator->();
		}

		reference operator*() const
		{
			iterator_type tmp = _iterator;
			tmp--;
			return *tmp;
		}

		pointer operator->() const
		{
			iterator_type tmp = _iterator;
			tmp--;
			return tmp.operator->();
		}

		reference operator[](difference_type n) const
		{
			return reference(*this->operator+(n));
		}

		reverse_iterator &operator++()
		{
			_iterator--;
			return *this;
		}

		reverse_iterator &operator--()
		{
			_iterator++;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			return reverse_iterator(_iterator.operator--(0));
		}

		reverse_iterator operator--(int)
		{
			return reverse_iterator(_iterator.operator++(0));
		}

		reverse_iterator operator+(const difference_type n) const
		{
			return _iterator - n;
		}

		friend reverse_iterator operator+(difference_type  n,
										  reverse_iterator other)
		{
			return other.base() - n;
		}

		reverse_iterator operator-(const difference_type n) const
		{
			return _iterator + n;
		}

		reverse_iterator &operator+=(difference_type n)
		{
			_iterator -= n;
			return *this;
		}

		reverse_iterator &operator-=(difference_type n)
		{
			_iterator += n;
			return *this;
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

	template <class T, class U>
	reverse_iterator<U> operator+(T lhs, const reverse_iterator<U> &rhs)
	{
		return rhs + lhs;
	}

	template <class T, class U>
	typename reverse_iterator<T>::difference_type
	operator-(const reverse_iterator<T> &lhs, const reverse_iterator<U> &rhs)
	{
		return -(lhs.base() - rhs.base());
	}

	template <typename T, typename U>
	bool operator==(const reverse_iterator<T> &lhs,
					const reverse_iterator<U> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename T, typename U>
	bool operator>=(const reverse_iterator<T> &lhs,
				   const reverse_iterator<U> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename T, typename U>
	bool operator!=(const reverse_iterator<T> &lhs,
					const reverse_iterator<U> &rhs)
	{
		return !(lhs == rhs);
	};

		template <typename T, typename U>
	bool operator<(const reverse_iterator<T> &lhs,
				   const reverse_iterator<U> &rhs)
	{
		return !(lhs >= rhs);
	}

			template <typename T, typename U>
	bool operator<=(const reverse_iterator<T> &lhs,
					const reverse_iterator<U> &rhs)
	{
		return lhs < rhs || lhs == rhs;
	}

	template <typename T, typename U>
	bool operator>(const reverse_iterator<T> &lhs,
					const reverse_iterator<U> &rhs)
	{
		return !(lhs <= rhs);
	}


	// template<typename U, typename X>
	// bool operator<(const reverse_iterator<U> &lhs, const reverse_iterator<X> &rhs) { return lhs.base() > rhs.base(); }

	// template<typename U, typename X>
	// bool operator<=(const reverse_iterator<U> &lhs, const reverse_iterator<X> &rhs) { return lhs.base() >= rhs.base(); }

	// template<typename U, typename X>
	// bool operator>(const reverse_iterator<U> &lhs, const reverse_iterator<X> &rhs) { return lhs.base() < rhs.base(); }

	// template<typename U, typename X>
	// bool operator>=(const reverse_iterator<U> &lhs, const reverse_iterator<X> &rhs) { return lhs.base() <= rhs.base(); }




	//	template <typename T>
	//	void ft_swap(T &a, T &b)
	//	{
	//		T tmp;
	//		tmp = a;
	//		a = b;
	//		b = tmp;
	//	}

	template <bool B, class T = void>
	struct enable_if
	{
	};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <typename _Tp, _Tp __v>
	struct integral_constant
	{
		static const _Tp                    value = __v;
		typedef _Tp                         value_type;
		typedef integral_constant<_Tp, __v> type;
	};

	typedef integral_constant<bool, true>  true_type;

	typedef integral_constant<bool, false> false_type;

	template <typename>
	struct __is_integral_helper : public false_type
	{
	};

	template <>
	struct __is_integral_helper<bool> : public true_type
	{
	};

	template <>
	struct __is_integral_helper<char> : public true_type
	{
	};

	template <>
	struct __is_integral_helper<signed char> : public true_type
	{
	};

	template <>
	struct __is_integral_helper<unsigned char> : public true_type
	{
	};

	template <>
	struct __is_integral_helper<short> : public true_type
	{
	};

	template <>
	struct __is_integral_helper<unsigned short> : public true_type
	{
	};

	template <>
	struct __is_integral_helper<int> : public true_type
	{
	};

	template <>
	struct __is_integral_helper<unsigned int> : public true_type
	{
	};

	template <>
	struct __is_integral_helper<long> : public true_type
	{
	};

	template <>
	struct __is_integral_helper<unsigned long> : public true_type
	{
	};

	template <typename T>
	struct is_integral : public __is_integral_helper<T>
	{
	};

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
	bool equal(InputIterator1 first1, InputIterator1 last1,
			   InputIterator2 first2, InputIterator2 last2)
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

		pair() : first(first_type()), second(second_type())
		{
		}

		pair(const first_type &first, const second_type &second)
			: first(first), second(second)
		{
		}

		template <typename U1, typename U2>
		pair &operator=(const pair<U1, U2> &other)
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

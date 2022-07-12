//
// Created by BenoîtMayer on 4/17/2022.
//

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "utility.hpp"

namespace ft
{
	/** @generic_iterator
	 * All required attributes and methods from:
	 * https://www.cplusplus.com/reference/iterator/iterator/
	 */
	template <typename T>
	class generic_iterator
	{
	public:
		// Member types
		typedef T iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category
				iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type value_type;
		typedef typename iterator_traits<iterator_type>::difference_type
				difference_type;
		typedef typename iterator_traits<iterator_type>::pointer   pointer;
		typedef typename iterator_traits<iterator_type>::reference reference;

	private:
		pointer _pointer;

	public:
		/// Constructors and destructor
		generic_iterator() : _pointer()
		{
		}
		generic_iterator(pointer ptr) : _pointer(ptr)
		{
		}
		generic_iterator(const generic_iterator &other)
			: _pointer(other._pointer)
		{
		}
		template <typename U>
		generic_iterator(const generic_iterator<U> &other)
			: _pointer(other.base())
		{
		}
		~generic_iterator()
		{
		}

		/// Operators
		generic_iterator &operator=(const generic_iterator &other)
		{
			this->_pointer = other._pointer;
			return *this;
		}
		reference operator*()
		{
			return *this->_pointer;
		}
		pointer operator->()
		{
			return this->_pointer;
		}
		reference operator[](difference_type n) const
		{
			return reference(*(_pointer + n));
		}
		generic_iterator operator++(int)
		{
			generic_iterator tmp(*this);
			++this->_pointer;
			return tmp;
		}
		generic_iterator &operator++()
		{
			++this->_pointer;
			return *this;
		}
		generic_iterator operator--(int)
		{
			generic_iterator tmp(*this);
			--this->_pointer;
			return tmp;
		}
		generic_iterator &operator--()
		{
			--this->_pointer;
			return *this;
		}
		generic_iterator operator+=(difference_type n)
		{
			_pointer += n;
			return generic_iterator(_pointer);
		}
		generic_iterator operator+(difference_type n) const
		{
			return generic_iterator(_pointer + n);
		}
		generic_iterator operator-=(difference_type n)
		{
			_pointer -= n;
			return generic_iterator(_pointer);
		}
		generic_iterator operator-(difference_type n) const
		{
			return generic_iterator(_pointer - n);
		}
		difference_type operator-(const generic_iterator &other) const
		{
			return this->_pointer - other._pointer;
		}
		pointer base()
		{
			return _pointer;
		}
		pointer base() const
		{
			return _pointer;
		}
	};

	/** @vector
	 * All required attributes and methods from:
	 * https://www.cplusplus.com/reference/vector/vector/
	 */
	template <typename T, typename Allocator = std::allocator<T> >
	class vector
	{
	public:
		// Member types
		typedef T                                        value_type;
		typedef Allocator                                allocator_type;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		typedef generic_iterator<value_type>             iterator;
		typedef generic_iterator<const value_type>       const_iterator;
		typedef ft::reverse_iterator<iterator>           reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;
		typedef typename generic_iterator<iterator>::difference_type
							difference_type;
		typedef std::size_t size_type;

	protected:
		allocator_type _alloc;
		size_t         _capacity;
		T			 *_data;
		size_t         _size;

	public:
		// Constructors
		explicit vector(const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _capacity(0), _data(0), _size(0)
		{
		}

		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _capacity(0), _data(0), _size(0)
		{
			this->assign(n, val);
		}

		template <typename U>
		vector(U first, U last, const allocator_type &alloc = allocator_type(),
			   typename ft::enable_if<!ft::is_integral<U>::value, U>::type * = 0)
			: _alloc(alloc), _capacity(0), _data(0), _size(0)
		{
			this->template assign(first, last);
		}

		vector(const vector &val)
			: _alloc(val._alloc), _capacity(0), _data(0), _size(0)
		{
			this->template assign(val.begin(), val.end());
		}

		vector &operator=(const vector &val)
		{
			this->template assign(val.begin(), val.end());
			return *this;
		}

		~vector()
		{
			this->clear();
			this->deallocate();
		}

		// Iterators
		iterator begin()
		{
			return iterator(_data);
		}

		const_iterator begin() const
		{
			return const_iterator(_data);
		}

		iterator end()
		{
			return iterator(_data + _size);
		}

		const_iterator end() const
		{
			return const_iterator(_data + _size);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		// Capacity
		size_t size() const
		{
			return _size;
		}

		size_t max_size() const
		{
			return _alloc.max_size();
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n <= _size)
			{
				for (size_type i = n; i < _size; ++i)
					_alloc.destroy(_data + i);
				_size = n;
			}
			this->reserve(n);
			if (n > _size)
			{
				for (size_type i = _size; i < n; ++i)
					_alloc.construct(_data + i, val);
				_size = n;
			}
		}

		size_t capacity() const
		{
			return _capacity;
		}

		bool empty() const
		{
			return _size == 0;
		}

		void reserve(size_t newmalloc)
		{
			if (newmalloc < _size)
				return;
			size_t new_capacity = newmalloc;
			size_t new_size = _size;
			T     *new_data = _alloc.allocate(newmalloc);
			for (size_t i = 0; i < _size; i++)
			{
				_alloc.construct(new_data + i, _data[i]);
			}
			swap(new_capacity, _capacity);
			swap(new_size, _size);
			swap(new_data, _data);
			for (size_t i = 0; i < new_size; i++)
			{
				_alloc.destroy(new_data + i);
			}
			_alloc.deallocate(new_data, new_capacity);
		}

		// Element access
		reference operator[](size_type n)
		{
			if (n >= _size)
				return *end();
			return _data[n];
		}

		const_reference operator[](size_type n) const
		{
			if (n >= _size)
				return *end();
			return _data[n];
		}

		T &at(size_type n)
		{
			if (n >= _size)
			{
				std::ostringstream o;
				o << "_n (which is " << n << ") >= this->size() (which is "
				  << _size << ")";
				throw std::out_of_range(o.str());
			}
			return _data[n];
		}

		const T &at(size_type n) const
		{
			if (n >= _size)
			{
				std::ostringstream o;
				o << "_n (which is " << n << ") >= this->size() (which is "
				  << _size << ")";
				throw std::out_of_range(o.str());
			}
			return _data[n];
		}

		reference front()
		{
			return _data[0];
		}

		const_reference front() const
		{
			return _data[0];
		}

		reference back()
		{
			return _data[_size - 1];
		}

		const_reference back() const
		{
			return _data[_size - 1];
		}

		// Modifiers
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			swap(vector<value_type>(first, last));
		}

		void assign(size_type n, const value_type &val)
		{
			swap(vector<value_type>(n, val));
		}

		void push_back(const value_type &val)
		{
			if (_size + 1 > _capacity && _size + 1 <= max_size())
				reserve(_capacity * 2 > max_size() ? max_size() :
													 _capacity * 2);
			_data[_size] = val;
			_size++;
		}

		void pop_back()
		{
			if (_size)
			{
				_data[_size] = 0;
				_size--;
			}
		}

		iterator insert(iterator position, const value_type &val)
		{
			size_type i = position - begin();
			this->insert(position, 1, val);
			return iterator(_data + i);
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			vector<T> tmp(*this);
			size_type i = position - begin();
			this->reserve(_size + n);
			for (size_type j = i; j < i + n; ++j)
				_alloc.construct(_data + j, val);
			for (size_type j = i + n; j < _size + n; ++j)
				_alloc.construct(_data + j, tmp[j - n]);
			_size += n;
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
			vector    tmp(*this);
			size_type n = 0;
			for (InputIterator it = first; it != last; it++)
				n++;
			size_type i = position - begin();
			this->reserve(_size + n);
			_size += n;
			for (size_type j = i; j < i + n; ++j)
				_alloc.construct(_data + j, *first++);
			for (size_type j = i + n; j < _size; ++j)
				_alloc.construct(_data + j, tmp[j - n]);
		}

		iterator erase(iterator position)
		{
			size_type i = ft::distance(begin(), position);
			while (i < _size)
			{
				_alloc.destroy(_data + i);
				if (i + 1 < _size)
					_alloc.construct(_data + i, _data + i + 1);
				i++;
			}
		}

		iterator erase(iterator first, iterator last)
		{
			size_type i = ft::distance(begin(), first);
			size_type j = ft::distance(first, last);
			for (size_type k = i; k < j; k++)
				_alloc.destroy(_data + i);
			for (size_type k = 0; k + j < _size; k++)
				_alloc.construct(_data + i + k, _data + i + j + k);
		}

		void swap(vector &other)
		{
			std::swap(_alloc, other._container);
			std::swap(_data, other._data);
			std::swap(_capacity, other._capacity);
			std::swap(_size, other._size);
		}

		void clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_data[i]);
			_size = 0;
		}

		// Allocator
		allocator_type get_allocator() const
		{
			return _alloc;
		}
	};

	// Non-member function overloads
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::vector<T>::const_iterator lhs_iter = lhs.begin();
		typename ft::vector<T>::const_iterator rhs_iter = rhs.begin();
		while (lhs_iter != lhs.end())
		{
			if (rhs_iter == rhs.end() || *lhs_iter != *rhs_iter)
				return (false);
			++lhs_iter;
			++rhs_iter;
		}
		return (true);
	}
	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}
	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
											rhs.end()));
	}
	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}
}// namespace ft

#endif
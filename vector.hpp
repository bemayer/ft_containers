#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "utility.hpp"

namespace ft
{
	/** @generic_iterator
	 * All required attributes and methods from:
	 * https://en.cppreference.com/w/cpp/iterator/iterator
	 */
	template <typename T>
	class generic_iterator
	{
	public:
		/// Member types
		typedef T                                                  iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category
		                                                           iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type
		                                                           value_type;
		typedef typename iterator_traits<iterator_type>::difference_type
		                                                           difference_type;
		typedef typename iterator_traits<iterator_type>::pointer   pointer;
		typedef typename iterator_traits<iterator_type>::reference reference;
		typedef generic_iterator<iterator_type>                    iterator;

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
		{
			*this = other;
		}

		template <typename U>
		generic_iterator(const generic_iterator<U> &other)
		{
			_pointer = other.base();
		}

		operator generic_iterator<const T>() const
		{
			return generic_iterator<const T>(_pointer);
		}

		~generic_iterator()
		{
		}

		template <typename U>
		generic_iterator &operator=(generic_iterator<U> &other)
		{
			_pointer = other.base();
			return *this;
		}

		/// Operators
		reference operator*()
		{
			return *_pointer;
		}

		reference operator*() const
		{
			return *_pointer;
		}

		pointer operator->()
		{
			return _pointer;
		}

		reference operator[](difference_type n) const
		{
			return reference(*(_pointer + n));
		}

		generic_iterator operator++(int)
		{
			generic_iterator tmp = *this;
			++_pointer;
			return tmp;
		}

		generic_iterator &operator++()
		{
			++_pointer;
			return *this;
		}

		generic_iterator operator--(int)
		{
			generic_iterator tmp(*this);
			--_pointer;
			return tmp;
		}

		generic_iterator &operator--()
		{
			--_pointer;
			return *this;
		}

		generic_iterator operator+=(difference_type n)
		{
			_pointer += n;
			return generic_iterator(_pointer);
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
			return _pointer - other.base();
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

	template <typename T>
	generic_iterator<T>
	operator+(typename generic_iterator<T>::difference_type const n,
			  generic_iterator<T> const                           iter)
	{
		return generic_iterator<T>(iter.base() + n);
	}

	template <typename T>
	generic_iterator<T>
	operator+(generic_iterator<T> const                           iter,
			  typename generic_iterator<T>::difference_type const n)
	{
		return generic_iterator<T>(iter.base() + n);
	}

	template <typename T, typename U>
	bool operator==(const generic_iterator<T> &lhs,
					const generic_iterator<U> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename T, typename U>
	bool operator<(const generic_iterator<T> &lhs,
				   const generic_iterator<U> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename T, typename U>
	bool operator!=(const generic_iterator<T> &lhs,
					const generic_iterator<U> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename U>
	bool operator<=(const generic_iterator<T> &lhs,
					const generic_iterator<U> &rhs)
	{
		return lhs == rhs || lhs < rhs;
	}

	template <typename T, typename U>
	bool operator>=(const generic_iterator<T> &lhs,
					const generic_iterator<U> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T, typename U>
	bool operator>(const generic_iterator<T> &lhs,
				   const generic_iterator<U> &rhs)
	{
		return !(lhs <= rhs);
	}

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
		typedef vector<value_type, allocator_type>       vector_type;
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
		typedef std::size_t                              size_type;

	protected:
		allocator_type _alloc;
		size_type      _capacity;
		value_type    *_data;
		size_type      _size;

	public:
		/// Constructors
		vector()
			: _alloc(allocator_type()), _capacity(0), _data(0), _size(0)
		{
		}

		explicit vector(const allocator_type &alloc)
			: _alloc(alloc), _capacity(0), _data(0), _size(0)
		{
		}

		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _capacity(0), _data(0), _size(0)
		{
			assign(n, val);
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last,
			   const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _capacity(0), _data(0), _size(0)
		{
			assign(first, last);
		}

		vector(const vector &val)
			: _alloc(val._alloc), _capacity(0), _data(0), _size(0)
		{
			assign(val.begin(), val.end());
		}

		vector &operator=(const vector &other)
		{
			clear();
			if (_data)
				_alloc.deallocate(_data, _capacity);
			_alloc = other._alloc;
			_data = _alloc.allocate(other._capacity);
			_capacity = other._capacity;
			_size = other._size;
			for (size_type i = 0; i < other._size; i++)
				_alloc.construct(_data + i, other._data[i]);
			return *this;
		}

		~vector()
		{
			clear();
			if (_data)
				_alloc.deallocate(_data, _capacity);
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

		/// Capacity
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
			if (n > _capacity)
			{
				size_type new_capacity = comp_capacity(n);
				pointer   tmp = _alloc.allocate(new_capacity);
				for (size_type i = 0; i < n; i++)
				{
					if (i < _size)
						_alloc.construct(tmp + i, _data[i]);
					else
						_alloc.construct(tmp + i, val);
				}
				clear();
				if (_data)
					_alloc.deallocate(_data, _capacity);
				_data = tmp;
				_capacity = new_capacity;
			}
			else
			{
				for (size_type i = _size; i < n; i++)
					_alloc.construct(_data + i, val);
				for (size_type i = n; i < _size; i++)
					_alloc.destroy(_data + i);
			}
			_size = n;
		}

		size_t capacity() const
		{
			return _capacity;
		}

		bool empty() const
		{
			return _size == 0;
		}

		void reserve(size_t new_cap)
		{
			if (new_cap <= _capacity)
				return;
			if (new_cap > max_size())
				throw std::length_error("vector::reserve");
			pointer tmp = _alloc.allocate(new_cap);
			for (size_type i = 0; i < _size; i++)
			{
				_alloc.construct(tmp + i, _data[i]);
				_alloc.destroy(_data + i);
			}
			if (_data)
				_alloc.deallocate(_data, _capacity);
			_capacity = new_cap;
			_data = tmp;
		}

		/// Element access
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

		/// Modifiers
		void assign(size_type n, const value_type &val)
		{
			clear();
			reserve(n);
			while (_size < n)
				_alloc.construct(_data + _size++, val);
		}

		template <typename U>
		void
		assign(typename ft::enable_if<!ft::is_integral<U>::value, U>::type first,
			   U                                                           last)
		{
			clear();
			difference_type size = ft::distance(first, last);
			reserve(size);
			while (first != last){
				_alloc.construct(_data + _size++, *first);
				++first;
			}
		}

		void push_back(const value_type &val)
		{
			reserve(comp_capacity(_size + 1));
			_alloc.construct(_data + _size++, val);
		}

		void pop_back()
		{
			if (_size)
			{
				_size--;
				_alloc.destroy(_data + _size);
			}
		}

		iterator insert(iterator position, const value_type &val)
		{
			size_type i = position - begin();
			insert(position, 1, val);
			return iterator(_data + i);
		}

		template <typename U>
		void insert(iterator position, size_type n, const U &val)
		{
			if (!n)
				return;
			size_type   new_size = _size + n;
			size_type   new_capacity = comp_capacity(new_size);
			value_type *tmp = _alloc.allocate(new_capacity);
			size_type   first_insert = position - begin();
			for (size_type i = 0; i < first_insert; i++)
				_alloc.construct(tmp + i, _data[i]);

			for (size_type i = first_insert; i < first_insert + n; i++)
				_alloc.construct(tmp + i, val);

			for (size_type i = first_insert + n; i < new_size; i++)
				_alloc.construct(tmp + i, _data[i - n]);
			clear();
			if (_data)
				_alloc.deallocate(_data, _capacity);
			_data = tmp;
			_size = new_size;
			_capacity = new_capacity;
		}

		template <typename U>
		void
		insert(iterator position,
			   typename ft::enable_if<!ft::is_integral<U>::value, U>::type first,
			   U                                                           last)
		{
			size_type   n = ft::distance(first, last);
			size_type   new_size = _size + n;
			size_type   new_capacity = comp_capacity(new_size);
			value_type *tmp = _alloc.allocate(new_capacity);
			size_type   first_insert = position - begin();
			for (size_type i = 0; i < first_insert; i++)
				_alloc.construct(tmp + i, _data[i]);
			for (size_type i = first_insert; i < first_insert + n; i++)
			{
				_alloc.construct(tmp + i, *first);
				++first;
			}
			for (size_type i = first_insert + n; i < new_size; i++)
				_alloc.construct(tmp + i, _data[i - n]);
			clear();
			if (_data)
				_alloc.deallocate(_data, _capacity);
			_data = tmp;
			_size = new_size;
			_capacity = new_capacity;
		}

		iterator erase(iterator position)
		{
			return erase(position, position + 1);
		}

		iterator erase(iterator first, iterator last)
		{
			iterator        tmp = first;
			iterator        lim = end();
			difference_type del = ft::distance(first, last);
			while (last != lim)
			{
				*first = *last;
				first++;
				last++;
			}
			while (del--)
				_alloc.destroy(_data + --_size);
			return tmp;
		}

		void swap(vector &other)
		{
			std::swap(_alloc, other._alloc);
			std::swap(_data, other._data);
			std::swap(_capacity, other._capacity);
			std::swap(_size, other._size);
		}

		void clear()
		{
			while (_size)
				_alloc.destroy(_data + --_size);
		}

		// Allocator
		allocator_type get_allocator() const
		{
			return _alloc;
		}

	private:
		size_type comp_capacity(size_type new_size)
		{
			if (new_size > max_size())
				throw std::length_error("vector::reserve");
			if (new_size <= _capacity)
				return _capacity;
			if (new_size < _capacity * 2)
			{
				if (_capacity * 2 > max_size())
					return max_size();
				else
					return _capacity ? _capacity * 2 : 1;
			}
			return new_size;
		}
	};

	template <typename T1, typename A1, typename T2, typename A2>
	bool operator==(const vector<T1, A1> &lhs, const vector<T2, A2> &rhs)
	{
		return lhs.size() == rhs.size() &&
			   ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T1, typename A1, typename T2, typename A2>
	bool operator<(const vector<T1, A1> &lhs, const vector<T2, A2> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
										   rhs.end());
	}

	template <typename T1, typename A1, typename T2, typename A2>
	bool operator!=(const vector<T1, A1> &lhs, const vector<T2, A2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T1, typename A1, typename T2, typename A2>
	bool operator<=(const vector<T1, A1> &lhs, const vector<T2, A2> &rhs)
	{
		return lhs == rhs || lhs < rhs;
	}

	template <typename T1, typename A1, typename T2, typename A2>
	bool operator>=(const vector<T1, A1> &lhs, const vector<T2, A2> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T1, typename A1, typename T2, typename A2>
	bool operator>(const vector<T1, A1> &lhs, const vector<T2, A2> &rhs)
	{
		return !(lhs <= rhs);
	}
}// namespace ft

namespace std
{
	template <typename T, typename Allocator>
	void swap(ft::vector<T, Allocator> &lhs, ft::vector<T, Allocator> &rhs)
	{
		lhs.swap(rhs);
	}
}// namespace std

#endif

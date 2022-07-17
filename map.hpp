#ifndef MAP_HPP
#define MAP_HPP

#include "tree.hpp"
#include "utility.hpp"

namespace ft
{
	/** @map
	 * All required attributes and methods from:
	 * http://en.cppreference.com/w/cpp/c/map
	 */
	template <typename Key, typename T, typename Compare = ft::less<Key>,
			  typename Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key                               key_type;
		typedef T                                 mapped_type;
		typedef ft::pair<const Key, T>            value_type;
		typedef Compare                           key_compare;
		typedef Allocator                         allocator_type;
		typedef value_type                       &reference;
		typedef const value_type                 &const_reference;
		typedef typename Allocator::pointer       pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef std::ptrdiff_t                    difference_type;
		typedef std::size_t                       size_type;
		typedef map<key_type, mapped_type, key_compare, allocator_type>
		                                          map_type;

		/** @value_compare
		 * Description of the nested class at
		 * http://en.cppreference.com/w/cpp/c/map/value_compare
		 */
		class value_compare
		{
		protected:
			key_compare comp;

		public:
			value_compare() : comp(key_compare())
			{
			}
			value_compare(key_compare c) : comp(c)
			{
			}
			bool operator()(const value_type &lhs, const value_type &rhs) const
			{
				return comp(lhs.first, rhs.first);
			}
		};

		typedef node<value_type>                               node_type;
		typedef node_type                                     *node_pointer;
		typedef tree_iterator<value_type, value_compare>       iterator;
		typedef tree_iterator<const value_type, value_compare> const_iterator;
		typedef ft::reverse_iterator<iterator>                 reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>           const_reverse_iterator;
		typedef std::allocator<node_type>                      node_allocator;
		typedef RB_tree<value_type, value_compare, node_allocator>
		                                                       tree_type;
		typedef tree_type                                     *tree_pointer;
		typedef std::allocator<tree_type> tree_allocator;

	protected:
		key_compare    _comp;
		allocator_type _alloc;
		tree_type      _tree;

	public:
		/// Constructors
		map(const key_compare    &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
			: _comp(comp), _alloc(alloc), _tree()
		{
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare    &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
			: _comp(comp), _alloc(alloc), _tree()
		{
			while (first != last){
				insert(*first);
				++first;
			}
		}

		map(const map &x)
			: _comp(x.key_comp()), _alloc(x.get_allocator()), _tree()
		{
			const_iterator it = x.begin();
			while (it != x.end())
				insert(*it++);
		}

		~map()
		{
		};

		map &operator=(const map &other)
		{
			_tree.clear();
			insert(other.begin(), other.end());
			return *this;
		}

		/// Member functions
		allocator_type get_allocator() const
		{
			return _alloc;
		}

		mapped_type &operator[](const key_type &k)
		{
			return insert(ft::make_pair(k, mapped_type())).first->second;
		}

		iterator begin()
		{
			return iterator(_tree.begin());
		}

		const_iterator begin() const
		{
			return const_iterator(_tree.begin());
		}

		iterator end()
		{
			return iterator(_tree.end());
		}

		const_iterator end() const
		{
			return const_iterator(_tree.end());
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(_tree.end());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(_tree.end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(_tree.begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(_tree.begin());
		}

		void clear()
		{
			_tree.clear();
		}

		bool empty() const
		{
			return !_tree.size();
		}

		size_type size() const
		{
			return _tree.size();
		}

		size_type max_size() const
		{
			return _tree.max_size();
		}

		pair<iterator, bool> insert(const value_type &val)
		{
			node_pointer found = _tree.find(val);
			if (found->color != nill)
				return ft::make_pair(iterator(found), false);
			node_pointer inserted = _tree.insert(val);
			return ft::make_pair(iterator(inserted), true);
		}

		iterator insert(iterator position, const value_type &val)
		{
			(void)position;
			return insert(val).first;
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first);
				++first;
			}
		}

		void erase(iterator position)
		{
			_tree.remove(*position);
		}

		size_type erase(const key_type &k)
		{
			return _tree.remove(ft::make_pair(k, mapped_type()));
		}

		void erase(iterator first, iterator last)
		{
			iterator	tmp;
			while (first != last)
			{
				tmp = first;
				++first;
				erase(tmp);
			}
		}

		void swap(map &x)
		{
			std::swap(_comp, x._comp);
			std::swap(_alloc, x._alloc);
			std::swap(_tree._allocator, x._tree._allocator);
			std::swap(_tree._root, x._tree._root);
			std::swap(_tree._end, x._tree._end);
			std::swap(_tree._compare, x._tree._compare);
			std::swap(_tree._size, x._tree._size);
		}

		size_type count(const key_type &k) const
		{
			node_pointer found = _tree.find(ft::make_pair(k, mapped_type()));
			if (found->color != nill)
				return 1;
			return 0;
		}

		iterator find(const key_type &k)
		{
			return iterator(_tree.find(ft::make_pair(k, mapped_type())));
		}

		const_iterator find(const key_type &k) const
		{
			return const_iterator(_tree.find(ft::make_pair(k, mapped_type())));
		}

		pair<iterator, iterator> equal_range(const key_type &k)
		{
			return ft::make_pair(iterator(lower_bound(k)),
								 iterator(upper_bound(k)));
		}

		pair<const_iterator, const_iterator>
		equal_range(const key_type &k) const
		{
			return ft::make_pair(const_iterator(lower_bound(k)),
								 const_iterator(upper_bound(k)));
		}

		iterator lower_bound(const key_type &k)
		{
			return iterator(_tree.lower_bound(ft::make_pair(k, mapped_type())));
		}

		const_iterator lower_bound(const key_type &k) const
		{
			return const_iterator(
					_tree.lower_bound(ft::make_pair(k, mapped_type())));
		}

		iterator upper_bound(const key_type &k)
		{
			return iterator(_tree.upper_bound(ft::make_pair(k, mapped_type())));
		}

		const_iterator upper_bound(const key_type &k) const
		{
			return const_iterator(
					_tree.upper_bound(ft::make_pair(k, mapped_type())));
		}

		key_compare key_comp() const
		{
			return Compare();
		}

		value_compare value_comp() const
		{
			return value_compare();
		}

#ifdef DEBUG
		void print_tree() const
		{
			_tree.print();
		}
#endif
	};

	/// Operators
	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		return lhs.size() == rhs.size() &&
			   ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs,
				   const map<Key, T, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
										   rhs.end());
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		return lhs < rhs || lhs == rhs;
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <typename Key, typename T, typename Compare, typename Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs,
				   const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs <= rhs);
	}
}// namespace ft

namespace std {
	template<class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key, T, Compare, Alloc> &lhs, ft::map<Key, T, Compare, Alloc> &rhs) {
		lhs.swap(rhs);
	}
}// namespace std

#endif

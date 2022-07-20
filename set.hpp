#ifndef SET_HPP
#define SET_HPP

#include "tree.hpp"
#include "utility.hpp"

namespace ft
{
	/** @set
	 * All required attributes and methods from:
	 * http://en.cppreference.com/w/cpp/c/set
	 */
	template <typename Key, typename Compare = ft::less<Key>,
			  typename Allocator = std::allocator<Key> >
	class set
	{
	public:
		typedef Key                                            key_type;
		typedef Key                                            value_type;
		typedef std::size_t                                    size_type;
		typedef std::ptrdiff_t                                 difference_type;
		typedef Compare                                        key_compare;
		typedef Compare                                        value_compare;
		typedef Allocator                                      allocator_type;
		typedef value_type                                    &reference;
		typedef const value_type                              &const_reference;
		typedef typename allocator_type::pointer               pointer;
		typedef typename allocator_type::const_pointer         const_pointer;
		typedef tree_iterator<const value_type, value_compare> iterator;
		typedef tree_iterator<const value_type, value_compare> const_iterator;
		typedef ft::reverse_iterator<iterator>                 reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>           const_reverse_iterator;
		typedef node<value_type>                               node_type;
		typedef node_type                                     *node_pointer;
		typedef std::allocator<node_type>                      node_allocator;
		typedef RB_tree<value_type, value_compare, node_allocator>
		                                                       tree_type;
		typedef tree_type                                     *tree_pointer;
		typedef std::allocator<tree_type> tree_allocator;

	protected:
		tree_type _tree;

	public:
		/// Constructors
		set(): _tree(key_compare(), node_allocator())
		{
		}

		explicit set(const key_compare& comp,
					 const allocator_type& alloc = allocator_type())
			: _tree(comp, node_allocator())
		{
			(void) alloc;
		}

		template <class InputIterator>
		set(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
			: _tree(comp, node_allocator())
		{
			(void) alloc;
			while (first != last)
				insert(*first++);
		}

		set(const set &x) : _tree()
		{
			const_iterator it = x.begin();
			while (it != x.end())
				insert(*it++);
		}

		~set(){};

		set &operator=(const set &other)
		{
			_tree.clear();
			insert(other.begin(), other.end());
			return *this;
		}

		allocator_type get_allocator() const
		{
			return allocator_type();
		}

		/// Member functions
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

		void clear()
		{
			_tree.clear();
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
				insert(*first++);
		}

		void erase(iterator position)
		{
			_tree.remove(position.base()->data);
		}

		size_type erase(const key_type &k)
		{
			return _tree.remove(k);
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
		}

		void swap(set &x)
		{
			ft::swap(_tree._allocator, x._tree._allocator);
			ft::swap(_tree._root, x._tree._root);
			ft::swap(_tree._end, x._tree._end);
			ft::swap(_tree._compare, x._tree._compare);
			ft::swap(_tree._size, x._tree._size);
		}

		size_type count(const key_type &k) const
		{
			node_pointer found = _tree.find(k);
			if (found->color != nill)
				return 1;
			return 0;
		}

		iterator find(const key_type &k)
		{
			return iterator(_tree.find(k));
		}

		const_iterator find(const key_type &k) const
		{
			return const_iterator(_tree.find(k));
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
			return iterator(_tree.lower_bound(k));
		}

		const_iterator lower_bound(const key_type &k) const
		{
			return const_iterator(_tree.lower_bound(k));
		}

		iterator upper_bound(const key_type &k)
		{
			return iterator(_tree.upper_bound(k));
		}

		const_iterator upper_bound(const key_type &k) const
		{
			return const_iterator(_tree.upper_bound(k));
		}

		key_compare key_comp() const
		{
			return value_compare();
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
	template <typename Key, typename Compare, typename Alloc>
	bool operator==(const set<Key, Compare, Alloc> &lhs,
					const set<Key, Compare, Alloc> &rhs)
	{
		return lhs.size() == rhs.size() &&
			   ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename Key, typename Compare, typename Alloc>
	bool operator<(const set<Key, Compare, Alloc> &lhs,
				   const set<Key, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
										   rhs.end());
	}

	template <typename Key, typename Compare, typename Alloc>
	bool operator!=(const set<Key, Compare, Alloc> &lhs,
					const set<Key, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename Key, typename Compare, typename Alloc>
	bool operator<=(const set<Key, Compare, Alloc> &lhs,
					const set<Key, Compare, Alloc> &rhs)
	{
		return lhs < rhs || lhs == rhs;
	}

	template <typename Key, typename Compare, typename Alloc>
	bool operator>(const set<Key, Compare, Alloc> &lhs,
				   const set<Key, Compare, Alloc> &rhs)
	{
		return !(lhs <= rhs);
	}

	template <typename Key, typename Compare, typename Alloc>
	bool operator>=(const set<Key, Compare, Alloc> &lhs,
					const set<Key, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}
}// namespace ft

namespace std {
	template<class Key, class Compare, class Alloc>
	void swap(ft::set<Key, Compare, Alloc> &lhs, ft::set<Key, Compare, Alloc> &rhs) {
		lhs.swap(rhs);
	}
}// namespace std

#endif

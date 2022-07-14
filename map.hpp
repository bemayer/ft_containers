#ifndef MAP_HPP
#define MAP_HPP

#define red 0
#define black 1
#define nill 2
#define _low _end->left
#define _high _end->right

#include "utility.hpp"

namespace ft
{
	template <typename T>
	struct node
	{
		typedef node<T>  node_type;
		typedef node<T> *node_pointer;
		T                data;
		node_pointer     parent;
		node_pointer     left;
		node_pointer     right;
		char             color;

		node() : data(T()), parent(NULL), left(NULL), right(NULL), color(black)
		{
		}

		node(T data, bool color = black)
			: data(data), parent(NULL), left(NULL), right(NULL), color(color)
		{
		}

		bool operator==(const node_type &other) const
		{
			return data == other.data;
		}

		bool operator<(const node_type &other) const
		{
			return data < other.data;
		}

		bool operator!=(const node_type &other) const
		{
			return !(*this == other);
		}

		bool operator<=(const node_type &other) const
		{
			return *this == other || *this < other;
		}

		bool operator>=(const node_type &other) const
		{
			return !(*this < other);
		}

		bool operator>(const node_type &other) const
		{
			return !(*this <= other);
		}
	};

	/** @RB_tree
	 * Red-black tree implementation based on "Introduction to Algorithms 3rd
	 * edition - Cormen, Leiserson, Rivest, Stein" (chapter 13)."
	 */
	template <typename T, typename Compare,
			  typename Alloc = std::allocator<node<T> > >
	struct RB_tree
	{
		typedef T                                                value_type;
		typedef const typename value_type::first_type            key_type;
		typedef const typename value_type::second_type           elem_type;
		typedef node<value_type>                                 node_type;
		typedef node_type									   *node_pointer;
		typedef typename Alloc::size_type                        size_type;
		typedef Compare                                          key_compare;
		typedef Alloc                                            allocator_type;
		typedef RB_tree<value_type, key_compare, allocator_type> tree_type;
		Alloc                                                    _allocator;
		node_pointer                                             _root;
		/// _end is the header, with:
		/// - _end->left, the first element
		/// - _end->right, the last element
		/// - _end is the only element with color == nill
		node_pointer                                             _end;
		Compare                                                  _compare;
		size_t                                                   _size;

		void left_rotate(node_pointer x)
		{
			/// turn y's left subtree into x's right subtree
			node_pointer y = x->right;
			x->right = y->left;
			if (y->left != _end)
				y->left->parent = x;
			/// link x's parent to y
			y->parent = x->parent;
			if (x->parent == _end)
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			/// put x on y's left
			y->left = x;
			x->parent = y;
		}

		void right_rotate(node_pointer y)
		{
			node_pointer x = y->left;
			y->left = x->right;
			if (x->right != _end)
				x->right->parent = y;
			x->parent = y->parent;
			if (y->parent == _end)
				_root = x;
			else if (y == y->parent->right)
				y->parent->right = x;
			else
				y->parent->left = x;
			x->right = y;
			y->parent = x;
		}

		void rb_insert(node_pointer z)
		{
			node_pointer y = _end;
			node_pointer x = _root;
			while (x != _end)
			{
				y = x;
				if (_compare(z->data, x->data))
					x = x->left;
				else
					x = x->right;
			}
			z->parent = y;
			if (y == _end)
				_root = z;
			else if (_compare(z->data, y->data))
				y->left = z;
			else
				y->right = z;
			z->left = _end;
			z->right = _end;
			z->color = red;
			rb_insert_fixup(z);
		}

		void rb_insert_fixup(node_pointer z)
		{
			while (z->parent->color == red)
			{
				if (z->parent == z->parent->parent->left)
				{
					node_pointer y = z->parent->parent->right;
					/// case 1: z uncle is red -> recolor
					if (y->color == red)
					{
						z->parent->color = black;
						y->color = black;
						z->parent->parent->color = red;
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->right)
						{
							/// case 2: z uncle is black and z is right child
							/// -> left_rotate z
							z = z->parent;
							left_rotate(z);
						}
						/// case 3: z uncle is black and z is left child
						/// -> recolor and right_rotate z
						z->parent->color = black;
						z->parent->parent->color = red;
						right_rotate(z->parent->parent);
					}
				}
				else
				{
					node_pointer y = z->parent->parent->left;
					if (y->color == red)
					{
						z->parent->color = black;
						y->color = black;
						z->parent->parent->color = red;
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->left)
						{
							z = z->parent;
							right_rotate(z);
						}
						z->parent->color = black;
						z->parent->parent->color = red;
						left_rotate(z->parent->parent);
					}
				}
			}
			_root->color = black;
			_end->color = nill;
		}

		void rb_transplant(node_pointer u, node_pointer v)
		{
			if (u->parent == _end)
				_root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		node_pointer tree_minimum(node_pointer x)
		{
			while (x->left != _end)
				x = x->left;
			return x;
		}

		node_pointer tree_maximum(node_pointer x)
		{
			while (x->right != _end)
				x = x->right;
			return x;
		}

		void rb_delete(node_pointer z)
		{
			node_pointer y = z;
			node_pointer x;
			bool         y_original_color = y->color;
			if (z->left == _end)
			{
				x = z->right;
				rb_transplant(z, z->right);
			}
			else if (z->right == _end)
			{
				x = z->left;
				rb_transplant(z, z->left);
			}
			else
			{
				y = tree_minimum(z->right);
				y_original_color = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					rb_transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				rb_transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			if (y_original_color == black)
				rb_delete_fixup(x);
		}

		void rb_delete_fixup(node_pointer x)
		{
			while (x != _root && x->color == black)
			{
				if (x == x->parent->left)
				{
					node_pointer w = x->parent->right;
					if (w->color == red)
					{
						w->color = black;
						x->parent->color = red;
						left_rotate(x->parent);
						w = x->parent->right;
					}
					if (w->left->color == black && w->right->color == black)
					{
						w->color = red;
						x = x->parent;
					}
					else
					{
						if (w->right->color == black)
						{
							w->left->color = black;
							w->color = red;
							right_rotate(w);
							w = x->parent->right;
						}
						w->color = x->parent->color;
						x->parent->color = black;
						w->right->color = black;
						left_rotate(x->parent);
						x = _root;
					}
				}
				else
				{
					node_pointer w = x->parent->left;
					if (w->color == red)
					{
						w->color = black;
						x->parent->color = red;
						right_rotate(x->parent);
						w = x->parent->left;
					}
					if (w->right->color == black && w->left->color == black)
					{
						w->color = black;
						x = x->parent;
					}
					else
					{
						if (w->left->color == black)
						{
							w->right->color = black;
							w->color = red;
							left_rotate(w);
							w = x->parent->left;
						}

						w->color = x->parent->color;
						x->parent->color = black;
						w->left->color = black;
						right_rotate(x->parent);
						x = _root;
					}
				}
			}
			x->color = black;
		}

		void clear_rec(node_pointer node)
		{
			if (node == _end)
				return;
			clear_rec(node->left);
			clear_rec(node->right);
			_allocator.deallocate(node, 1);
		}

		void init()
		{
			_end->color = nill;
			_root = _end;
			_low = _end;
			_size = 0;
		}

		RB_tree(): _allocator(), _root(NULL), _end(NULL), _compare(), _size(0)
		{
			_end = _allocator.allocate(1);
			_allocator.construct(_end, value_type());



		/// _end is the header, with:
		/// - _end->left, the first element
		/// - _end->right, the last element
		/// - _end is the only element with color == nill

			//			std::cout << "_end address = " << static_cast<void*>(_end)
			//<< std::endl;
			init();
		}

		//		RB_tree(node_pointer pointer) : _end(pointer), _size(0)
		//		{
		//			init();
		//		}

		~RB_tree()
		{
			clear();
			_allocator.destroy(_end);
			_allocator.deallocate(_end, 1);
		}

		//		bool isLess(value_type &less, value_type &more){
		//			return _compare(less, more);
		//		}

		node_pointer insert(const value_type &data)
		{
			node_pointer new_node = _allocator.allocate(1);
			//			std::cout << "new_node address = " <<
			//static_cast<void*>(new_node) << std::endl;
			_allocator.construct(new_node, data);
			if (!_size)
			{
				_low = new_node;
				_high = new_node;
			}
			else
			{
				if (_compare(data, _low->data))
					_low = new_node;
				if (_compare(_high->data, data))
					_high = new_node;
			}
			rb_insert(new_node);
			_size++;
			return (new_node);
		}

		//		node_pointer insert(const value_type *data)
		//		{
		//			if (!data)
		//				return 0;
		//			node_pointer new_node = _allocator.allocate(1);
		//			_allocator.construct(new_node, data);
		//			if (!_low->data || _compare(data, _low->data))
		//				_low = new_node;
		//			if (!_high->data || _compare(_high->data, data))
		//			{
		//				_high = new_node;
		//				_nill->parent = new_node;
		//			}
		//			rb_insert(new_node);
		//			return (new_node);
		//		}

		void clear()
		{
			clear_rec(_root);
			init();
		}

		node_pointer find(const value_type &data) const
		{
			node_pointer current = _root;
			while (current != _end)
			{
				if (_compare(data, current->data))
				{
					current = current->left;
					continue;
				}
				if (_compare(current->data, data))
				{
					current = current->right;
					continue;
				}
				return current;
			}
			return current;
		}

		node_pointer find(key_type &k) const
		{
			return find(ft::make_pair(k, elem_type()));
		}

		bool remove(const value_type &data)
		{
			node_pointer rem_node = find(data);
			if (rem_node->color == nill)
				return false;
			_size--;
			rb_delete(rem_node);
			if (_size)
			{
				if (rem_node->data == _low->data)
					_low = tree_minimum(_root);
				if (rem_node->data == _high->data)
					_high = tree_maximum(_root);
				_end->color = nill;
			}
			else
				init();
			_allocator.destroy(rem_node);
			_allocator.deallocate(rem_node, 1);
			return true;
		}

		bool remove(key_type &k)
		{
			return remove(ft::make_pair(k, elem_type()));
		}

		//		node_pointer next(const node_pointer pointer)
		//		{
		//			if (pointer->right)
		//			{
		//				pointer = pointer->right;
		//				while (pointer->left)
		//					pointer = pointer->left;
		//				return pointer;
		//			}
		//			while (pointer != _nill)
		//			{
		//				value_type &parent = pointer->parent;
		//				if (!_compare(parent->data, pointer->data))
		//					break;
		//				pointer = &parent;
		//			}
		//			return pointer;
		//		}
		//
		//		node_pointer previous(const node_pointer &pointer)
		//		{
		//			if (pointer == _nill)
		//			{
		//				return _nill.parent;
		//			}
		//			if (pointer->left)
		//			{
		//				pointer = pointer->left;
		//				while (pointer->right)
		//					pointer = pointer->right;
		//				return pointer;
		//			}
		//			while (pointer != _nill)
		//			{
		//				value_type &parent = pointer->parent;
		//				if (!_compare(pointer->data, parent->data))
		//					break;
		//				pointer = &parent;
		//			}
		//			return pointer;
		//		}

		//		node_pointer begin()
		//		{
		//			return static_cast<node_pointer>(this->_low);
		//		}
		//
		//		node_pointer begin() const
		//		{
		//			return static_cast<const node_pointer>(this->_low);
		//		}
		//
		node_pointer begin()
		{
			return _low;
		}

		node_pointer begin() const
		{
			return _low;
		}

		node_pointer end()
		{
			return _end;
		}

		node_pointer end() const
		{
			return _end;
		}

		size_type max_size() const
		{
			return _allocator.max_size();
		}

		size_type size() const
		{
			return _size;
		}

		node_pointer lower_bound(key_type &k) const
		{
			if (!_size)
				return NULL;
			node_type    node = node_type(ft::make_pair(k, elem_type()));
			node_pointer current = _root;
			node_pointer res = _end;
			while (current != _end)
			{
				if (!_compare(current->data, node.data))
				{
					res = current;
					current = current->left;
				}
				else
				{
					current = current->right;
				}
			}
			return res;
		}

		node_pointer lower_bound(key_type &k)
		{
			return const_cast<const RB_tree *>(this)->lower_bound(k);
		}

		node_pointer upper_bound(key_type &k) const
		{
			if (!_size)
				return NULL;
			node_type    node = node_type(ft::make_pair(k, elem_type()));
			node_pointer current = _root;
			node_pointer res = _end;
			while (current != _end)
			{
				if (_compare(node.data, current->data))
				{
					res = current;
					current = current->left;
				}
				else
				{
					current = current->right;
				}
			}
			return res;
		}

		node_pointer upper_bound(key_type &k)
		{
			return const_cast<const RB_tree *>(this)->upper_bound(k);
		}

		void print_rec(const std::string &prefix, node_pointer node,
					   bool isLeft) const
		{
			if (node != _end)
			{
				std::cout << prefix;
				std::cout << (isLeft ? "├── " : "└── ");
				std::cout << node->data.first << std::endl;
				print_rec(prefix + (isLeft ? "│    " : "     "), node->left,
						  true);
				print_rec(prefix + (isLeft ? "│    " : "     "), node->right,
						  false);
			}
		}

		void print() const
		{
			print_rec("", _root, false);
		}
	};

	template <typename T, typename Compare>
	class tree_const_iterator;

	/** @tree_iterator
	 * All required attributes and methods from:
	 * https://www.cplusplus.com/reference/iterator/iterator/
	 */
	template <typename T, typename Compare = ft::less<T> >
	class tree_iterator
	{
	public:
		typedef T                            iterator_type;
		typedef tree_iterator<iterator_type> iterator;
		typedef typename iterator_traits<iterator_type>::value_type value_type;
		typedef typename iterator_traits<iterator_type>::difference_type
				difference_type;
		typedef typename iterator_traits<iterator_type>::pointer   pointer;
		typedef typename iterator_traits<iterator_type>::reference reference;
		typedef typename iterator_traits<iterator_type>::iterator_category
								 iterator_category;
		typedef node<value_type> node_type;
		typedef node_type       *node_pointer;
		typedef tree_iterator<const iterator_type, Compare> const_iterator;

		node_pointer                                              _pointer;
		Compare                                                   compare;

		/// Constructors and destructor
		tree_iterator() : _pointer(), compare(Compare())
		{
		}

		tree_iterator(node_pointer pointer) : _pointer(pointer), compare(Compare())
		{
		}

		tree_iterator(const tree_iterator &other)
		{
			*this = other;
		}

		operator tree_iterator<const T, Compare>() const
		{
			return tree_iterator<const T, Compare>(_pointer);
		}

		//		operator const_iterator () const
		//		{ return const_iterator(const_cast<typename
		// const_iterator::node_pointer>(_pointer)); }

		/// Operators
		tree_iterator &operator=(const tree_iterator &other)
		{
			this->_pointer = other._pointer;
			return *this;
		}

		reference operator*()
		{
			return _pointer->data;
		}

		reference operator*() const
		{
			return _pointer->data;
		}

		pointer operator->() const
		{
			return &_pointer->data;
		}

		tree_iterator &operator++()
		{
			if (_pointer->right->color != nill)
			{
				_pointer = _pointer->right;
				while (_pointer->left->color != nill)
					_pointer = _pointer->left;
				return *this;
			}
			while (_pointer->color != nill)
			{
				node_pointer temp = _pointer;
				_pointer = _pointer->parent;
				if (!compare(_pointer->data, temp->data))
					break;
			}
			return *this;
		}

		tree_iterator operator++(int)
		{
			tree_iterator tmp = *this;
			++*this;
			return tmp;
		}

		tree_iterator &operator--()
		{
			if (_pointer->color == nill)
			{
				_pointer = _pointer->right;
				return *this;
			}
			if (_pointer->left->color != nill)
			{
				_pointer = _pointer->left;
				while (_pointer->right->color != nill)
					_pointer = _pointer->right;
				return *this;
			}
			while (_pointer->parent->color != nill)
			{
				node_pointer temp = _pointer;
				_pointer = _pointer->parent;
				if (!compare(temp->data, _pointer->data))
					break;
			}
			return *this;
		}

		tree_iterator operator--(int)
		{
			tree_iterator tmp = *this;
			--*this;
			return tmp;
		}

		template <class U>
		bool operator==(const U &other) const
		{
			return _pointer == other._pointer;
		}

		template <class U>
		bool operator!=(const U &other) const
		{
			return _pointer != other._pointer;
		}

		node_pointer base()
		{
			return _pointer;
		}

		node_pointer base() const
		{
			return _pointer;
		}

		Compare comparator()
		{
			return compare;
		}
	};

	//
	//	/** @tree_const_iterator
	//	 * All required attributes and methods from:
	//	 * https://www.cplusplus.com/reference/iterator/iterator/
	//	 */
	//	template <typename T, typename Compare = ft::less<T> >
	//	class tree_const_iterator
	//	{
	//	public:
	//		typedef T iterator_type;
	//		typedef tree_iterator<iterator_type> iterator;
	//		typedef typename iterator_traits<iterator_type>::value_type
	// value_type; 		typedef typename
	// iterator_traits<iterator_type>::difference_type
	// difference_type; 		typedef typename
	// iterator_traits<iterator_type>::pointer   pointer; 		typedef typename
	// iterator_traits<iterator_type>::reference reference; 		typedef
	// typename iterator_traits<iterator_type>::iterator_category
	//								 iterator_category;
	//		typedef const node<value_type> node_type;
	//		typedef node_type       *node_pointer;
	//
	//		node_pointer _pointer;
	//		Compare      _compare;
	//
	//		/// Constructors and destructor
	//		tree_const_iterator() : _pointer()
	//		{
	//		}
	//
	//		tree_const_iterator(node_pointer pointer) : _pointer(pointer)
	//		{
	//		}
	//
	//		operator iterator() const
	//		{ return iterator(const_cast<typename
	// iterator::node_pointer>(_pointer)); }
	//
	//		/// Operators
	//		tree_const_iterator &operator=(const tree_const_iterator &other)
	//		{
	//			this->_pointer = other._pointer;
	//			return *this;
	//		}
	//
	//		reference operator*()
	//		{
	//			return _pointer->data;
	//		}
	//
	//		reference operator*() const
	//		{
	//			return _pointer->data;
	//		}
	//
	//		pointer operator->() const
	//		{
	//			return &_pointer->data;
	//		}
	//
	//		tree_const_iterator &operator++()
	//		{
	//			if (_pointer->right->color != nill)
	//			{
	//				_pointer = _pointer->right;
	//				while (_pointer->left->color != nill)
	//					_pointer = _pointer->left;
	//				return *this;
	//			}
	//			while (_pointer->color != nill)
	//			{
	//				node_pointer temp = _pointer;
	//				_pointer = _pointer->parent;
	//				if (!_compare(_pointer->data, temp->data))
	//					break;
	//			}
	//			return *this;
	//		}
	//
	//		tree_const_iterator operator++(int)
	//		{
	//			tree_const_iterator tmp = *this;
	//			++*this;
	//			return tmp;
	//		}
	//
	//		tree_const_iterator &operator--()
	//		{
	//			if (_pointer->color == nill)
	//			{
	//				_pointer = _pointer->right;
	//				return *this;
	//			}
	//			if (_pointer->left->color != nill)
	//			{
	//				_pointer = _pointer->left;
	//				while (_pointer->right->color != nill)
	//					_pointer = _pointer->right;
	//				return *this;
	//			}
	//			while (_pointer->parent->color != nill)
	//			{
	//				node_pointer temp = _pointer;
	//				_pointer = _pointer->parent;
	//				if (!_compare(temp->data, _pointer->data))
	//					break;
	//			}
	//			return *this;
	//		}
	//
	//		tree_const_iterator operator--(int)
	//		{
	//			tree_const_iterator tmp = *this;
	//			--*this;
	//			return tmp;
	//		}
	//
	//		template <class U>
	//		bool operator==(const U &other)
	//		{
	//			return _pointer == other.base();
	//		}
	//
	//		template <class U>
	//		bool operator!=(const U &other)
	//		{
	//			return _pointer != other.base();
	//		}
	//
	//		node_pointer base()
	//		{
	//			return _pointer;
	//		}
	//
	//		node_pointer base() const
	//		{
	//			return _pointer;
	//		}
	//
	//		Compare comparator()
	//		{
	//			return _compare;
	//		}
	//	};

	/** @map
	 * All required attributes and methods from:
	 * https://cplusplus.com/reference/map/map/
	 */
	template <typename Key, typename T, typename Compare = ft::less<Key>,
			  typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key                           key_type;
		typedef T                             mapped_type;
		typedef ft::pair<const Key, T>        value_type;
		typedef Compare                       key_compare;
		typedef Alloc                         allocator_type;
		typedef value_type                   &reference;
		typedef const value_type             &const_reference;
		typedef typename Alloc::pointer       pointer;
		typedef typename Alloc::const_pointer const_pointer;
		typedef std::ptrdiff_t                difference_type;
		typedef std::size_t                   size_type;
		typedef map<key_type, mapped_type, key_compare, allocator_type> map_type;

		/** @value_compare
		 * Description of the nested class at
		 * https://cplusplus.com/reference/map/map/value_comp/
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
		typedef node_type									 *node_pointer;
		typedef tree_iterator<value_type, value_compare>       iterator;
		typedef tree_iterator<const value_type, value_compare> const_iterator;
		typedef ft::reverse_iterator<iterator>                 reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::allocator<node_type>            node_allocator;
		typedef RB_tree<value_type, value_compare, node_allocator> tree_type;
		typedef tree_type										 *tree_pointer;
		typedef std::allocator<tree_type> tree_allocator;

	protected:
		key_compare    _comp;
		allocator_type _alloc;
		//		node_allocator		_node_alloc;
		//		tree_allocator       _tree_alloc;
		tree_type      _tree;
		//		node_pointer         _node_end;

	public:
		/// Constructors
		map(const key_compare    &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
			: _comp(comp)
			, _alloc(alloc)
			, _tree()
		{
			//			_tree = _tree_alloc.allocate(1);
			//			_node_end = _node_alloc.allocate(1);
			//			_tree_alloc.construct(_tree, tree_type());
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare    &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
			: _comp(comp)
			, _alloc(alloc)
			, _tree(tree_type())
		{
			//			_tree = _tree_alloc.allocate(1);
			//			_tree = tree_type();
			while (first != last)
				insert(*first++);
		}

		map(const map &x)
			: _comp(x.key_comp()), _alloc(x.get_allocator()), _tree()
		{
			//			_tree = _tree_alloc.allocate(1);
			//			_tree_alloc.construct(_tree);
			const_iterator it = x.begin();
			while (it != x.end())
				insert(*it++);
		}

		map &operator=(const map &other)
		{
			//			_tree_alloc.destroy(_tree);
			//			_tree_alloc.deallocate(_tree, 1);
			//			_tree = _tree_alloc.allocate(1);
			//			_tree_alloc.construct(_tree);
			_tree.clear();
			insert(other.begin(), other.end());
			return *this;
		}

		~map(){
				//			_tree_alloc.destroy(_tree);
				//			_tree_alloc.deallocate(_tree, 1);

		};

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

		mapped_type &operator[](const key_type &k)
		{
			return insert(ft::make_pair(k, mapped_type())).first->second;
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

		void clear()
		{
			_tree.clear();
		}

		key_compare key_comp() const
		{
			return Compare();
		}

		value_compare value_comp() const
		{
			return value_compare();
		}

		iterator find(const key_type &k)
		{
			return iterator(_tree.find(k));
		}

		const_iterator find(const key_type &k) const
		{
			return const_iterator(_tree.find(k));
		}

		size_type count(const key_type &k) const
		{
			node_pointer found = _tree.find(k);
			if (found->color != nill)
				return 1;
			return 0;
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

		allocator_type get_allocator() const
		{
			return _alloc;
		}

		bool operator==(const map_type &other) const
		{
			return size() == other.size() &&
				   ft::equal(begin(), end(), other.begin(), other.end());
		}

		bool operator<(const map_type &other) const
		{
			return std::lexicographical_compare(begin(), end(), other.begin(),
												other.end());
		}

		bool operator!=(const map_type &other) const
		{
			return !(*this == other);
		}

		bool operator<=(const map_type &other) const
		{
			return *this == other || *this < other;
		}

		bool operator>=(const map_type &other) const
		{
			return !(*this < other);
		}

		bool operator>(const map_type &other) const
		{
			return !(*this <= other);
		}

#ifdef DEBUG
		void print_tree() const
		{
			_tree.print();
		}
#endif
	};
}// namespace ft

// template <typename T, typename Compare = ft::less<T>,
//		  typename Alloc = std::_allocator<node<T> > >
// class tree_iterator

#endif

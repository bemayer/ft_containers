#ifndef TREE_HPP
#define TREE_HPP

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
		typedef node<value_type>                                 node_type;
		typedef node_type                                       *node_pointer;
		typedef typename Alloc::size_type                        size_type;
		typedef Compare                                          key_compare;
		typedef Alloc                                            allocator_type;
		typedef RB_tree<value_type, key_compare, allocator_type> tree_type;
		node_pointer                                             _root;
		/// _end is the header, with:
		/// - _end->left, the first element
		/// - _end->right, the last element
		/// - _end is the only element with color == nill
		node_pointer                                             _end;
		Compare                                                  _compare;
		allocator_type                                           _allocator;
		size_t                                                   _size;

		RB_tree(const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) :
				_compare(comp), _allocator(alloc)
		{
			_end = _allocator.allocate(1);
			_allocator.construct(_end, value_type());
			init();
		}

		~RB_tree()
		{
			clear();
			_allocator.destroy(_end);
			_allocator.deallocate(_end, 1);
		}

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

		void init()
		{
			_end->color = nill;
			_root = _end;
			_low = _end;
			_size = 0;
		}

		node_pointer insert(const value_type &data)
		{
			node_pointer new_node = _allocator.allocate(1);
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

		void clear_rec(node_pointer node)
		{
			if (node == _end)
				return;
			clear_rec(node->left);
			clear_rec(node->right);
			_allocator.deallocate(node, 1);
		}

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

		bool remove(const value_type &data)
		{
			node_pointer rem_node = find(data);
			if (rem_node->color == nill)
				return false;
			remove(rem_node);
			return true;
		}

		void remove(const node_pointer &node)
		{
			_size--;
			rb_delete(node);
			if (_size)
			{
				if (node->data == _low->data)
					_low = tree_minimum(_root);
				if (node->data == _high->data)
					_high = tree_maximum(_root);
				_end->color = nill;
			}
			else
				init();
			_allocator.destroy(node);
			_allocator.deallocate(node, 1);
		}

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

		node_pointer lower_bound(const value_type &data) const
		{
			node_type    node = node_type(data);
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
					current = current->right;
			}
			return res;
		}

		node_pointer lower_bound(const value_type &data)
		{
			return const_cast<const RB_tree *>(this)->lower_bound(data);
		}

		node_pointer upper_bound(const value_type &data) const
		{
			node_type    node = node_type(data);
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
					current = current->right;
			}
			return res;
		}

		node_pointer upper_bound(const value_type &data)
		{
			return const_cast<const RB_tree *>(this)->upper_bound(data);
		}

		void print_rec(const std::string &prefix, node_pointer node,
					   bool isLeft) const
		{
			if (node != _end)
			{
				std::cout << prefix;
				std::cout << (isLeft ? "├── " : "└── ");
				std::cout << node->data << std::endl;
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
		typedef typename std::bidirectional_iterator_tag    iterator_category;
		typedef node<value_type>                            node_type;
		typedef node_type								  *node_pointer;
		typedef tree_iterator<const iterator_type, Compare> const_iterator;

		node_pointer                                        _pointer;
		Compare                                             compare;

		/// Constructors and destructor
		tree_iterator() : _pointer(), compare(Compare())
		{
		}

		tree_iterator(node_pointer pointer)
			: _pointer(pointer), compare(Compare())
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
	};

	template <typename T1, typename C1, typename T2, typename C2>
	bool operator==(const tree_iterator<T1, C1> &lhs,
					const tree_iterator<T2, C2> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename T1, typename C1, typename T2, typename C2>
	bool operator!=(const tree_iterator<T1, C1> &lhs,
					const tree_iterator<T2, C2> &rhs)
	{
		return !(lhs == rhs);
	}
}// namespace ft
#endif

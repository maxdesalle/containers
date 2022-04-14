/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 07:34:38 by mlazzare          #+#    #+#             */
/*   Updated: 2022/04/14 16:07:29 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iterator>
# include <algorithm>

# include "../utilities/RBTree.hpp"
# include "../utilities/type_traits.hpp"
# include "../utilities/iterator.hpp"
# include "../utilities/algorithm.hpp"
# include "../utilities/pair.hpp"

namespace ft
{
	template <	class Key,
                class T,
                class Compare = std::less< const Key >,
                class Alloc = std::allocator< ft::pair< const Key, T > >
             >
			 		 
	class map
	{
		// VAR TYPES
		public:
			class 												value_compare; // defined at the very end

			typedef	T			 								mapped_type;
            typedef Key                                         key_type;
            typedef ft::pair< const key_type, mapped_type >     value_type;
            typedef std::size_t									size_type;
            typedef std::ptrdiff_t							    difference_type;
            typedef Compare                                     key_compare;
			typedef Alloc										allocator_type;

		private:
			typedef RBTree<value_type, value_compare, allocator_type>		rbtree;

		public:
			typedef value_type&			                        reference;
			typedef const  	value_type&                     	const_reference;
			typedef typename Alloc::pointer			        	pointer;
			typedef typename Alloc::const_pointer		    	const_pointer;

			typedef typename rbtree::iterator						iterator;
			typedef typename rbtree::const_iterator					const_iterator;
			typedef ft::reverse_iterator< iterator >				reverse_iterator;
			typedef const ft::reverse_iterator< const_iterator >	const_reverse_iterator;
			typedef node< value_type >                          	treeNode;
			

		private:
			rbtree												_tree;
			key_compare											_compare;
			allocator_type										_alloc;

		
		public:
			// public classes
			class value_compare
			{   
				friend class map;
				protected:
					key_compare		comp;
					value_compare (key_compare c) : comp(c) {}  // constructed with map's comparison object
					
				public:
					typedef bool 			result_type;
					typedef value_type 		first_argument_type;
					typedef value_type 		second_argument_type;
					bool operator() ( const value_type& x, const value_type& y ) const { 		return comp(x.first, y.first);			};
			};
			// member functions
			explicit map( const key_compare & comp = key_compare(),
						const allocator_type & alloc = allocator_type()) :	_tree(comp, alloc),
																			_compare(comp),
																			_alloc(alloc) {};

			map( map const& m ):	_tree(m._tree),
									_compare(m._compare),
									_alloc(m._alloc) {};
			
			template < typename InputIterator >
			map(	InputIterator first, InputIterator last, 
					key_compare const & comp = key_compare(),
					allocator_type const & alloc = allocator_type()):		_tree(comp, alloc),
																			_compare(comp)				{	_tree.insert(first, last);	};

			virtual ~map() {};
			
			map& operator = ( map const& m)
			{
				if (this != &m)
				{
					_tree = m._tree;
					_compare = m._compare;
					_alloc = m._alloc ;
				}
				return *this;
			}

			// InputIteratorerators
			iterator begin()								{	return	_tree.begin();		};
			const_iterator begin() const					{	return	_tree.begin();		};
			iterator end()									{	return	_tree.end();		};
			const_iterator end() const						{	return	_tree.end();		};
			reverse_iterator rbegin()								{	return	_tree.rbegin();		};
			const_reverse_iterator rbegin() const					{	return	_tree.rbegin();		};
			reverse_iterator rend()									{	return	_tree.rend();		};
			const_reverse_iterator rend() const						{	return	_tree.rend();		};

			// capacity
			bool			empty( void ) const				{	return	_tree.empty();		};
			size_type 		size( void ) const				{	return	_tree.size();		};
			size_type 		max_size() const				{	return	_tree.max_size();	};


			// modifiers
			// [ INSERT ]
			ft::pair< iterator,bool > 	insert(value_type const & val)						{	return _tree.insert( val );			};
			iterator 					insert(iterator position, const value_type& val)	{	return _tree.insert( position, val );	};
			template <class InputIterator>
  			void 						insert (InputIterator first, InputIterator last) const	{	_tree.insert(first, last);	};

			// [ ERASE ]
			void 						erase(iterator position)							{	_tree.erase( position.node() );				};
			size_type 					erase(const key_type& k)							{	return _tree.erase( get_valuetype(k) );		};
			void 						erase(iterator first, iterator last)				{	_tree.erase( first, last );					};

			// [ SWAP ]
			void 					swap(map& x)					{	if (this != &x)	_tree.swap(x._tree);	};

			// [ CLEAR ]
			void 					clear()							{	printf("root value %d\n", _tree.get_root()->value.second); _tree.clear(_tree.get_root());	};
			
			// element access
			mapped_type& operator[] ( const key_type& k )			{	return (*(insert(ft::make_pair( k, mapped_type() )).first)).second;				};

			// observers
			key_compare 			key_comp() const				{	return this->_compare;					};
			value_compare 			value_comp() const				{	return value_compare(this->_compare);	};

			// operations

			// [ FIND ]
			iterator		find(const key_type& k)			{	return _tree.find(get_valuetype(k));	};
			const_iterator	find(const key_type& k) const	{	return _tree.find(get_valuetype(k));	};
			
			// [ COUNT ]
			size_type 		count(key_type const & k) const	{	return !(_tree.find(get_valuetype(k)) == _tree.end());	};

			// [ LOWER_BOUND ]
			iterator lower_bound(key_type const & k)		{	return _tree.lower_bound(get_valuetype(k));				};
			iterator lower_bound(key_type const & k) const	{	return _tree.lower_bound(get_valuetype(k));				};

			// [ UPPER_BOUND ]
			iterator upper_bound(key_type const & k)		{	return _tree.upper_bound(get_valuetype(k));				};
			iterator upper_bound(key_type const & k) const	{	return _tree.upper_bound(get_valuetype(k));				};

			// [ EQUAL_RANGE ]
			ft::pair< const_iterator, const_iterator > equal_range (const key_type& k) const	{	return (ft::make_pair(lower_bound(k), upper_bound(k)));	};
			ft::pair< iterator, iterator >             equal_range (const key_type& k)			{	return (ft::make_pair(lower_bound(k), upper_bound(k)));	};

			// allocator
			allocator_type			get_allocator( void ) const		{	return this->_alloc;	};

			// helper functions
			value_type				get_valuetype( const key_type& k )			{		return ft::make_pair( k, mapped_type() );					}
			void					inorder( void ) 							{		_tree.inorder(_tree.get_root());							}

	};

	template <class T, class Alloc>
	bool	operator == ( const map< T, Alloc >& l, const map< T, Alloc >& r ) 
	{
		if (l.size() != r.size())
			return false;
		return ft::equal(l.begin(), l.end(), r.begin());
	};

	template <class T, class Alloc>
	bool	operator !=  ( const map< T, Alloc >& l, const map< T, Alloc >& r )		{ return !(l == r); }

	template <class T, class Alloc>
	bool	operator <  ( const map< T, Alloc >& l, const map< T, Alloc >& r )		{ return ft::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end()); }

	template <class T, class Alloc>
	bool	operator <=  ( const map< T, Alloc >& l, const map< T, Alloc >& r )		{ return !(r < l); }

	template <class T, class Alloc>
	bool	operator >  ( const map< T, Alloc >& l, const map< T, Alloc >& r )		{ return r < l; }

	template <class T, class Alloc>
	bool	operator >=  ( const map< T, Alloc >& l, const map< T, Alloc >& r )		{ return !(l < r); }

	template <class T, class Alloc>
	void	swap( map< T, Alloc >& x, map< T, Alloc >& y) 							{ x.swap(y); }
};

#endif
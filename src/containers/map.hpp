/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 07:34:38 by mlazzare          #+#    #+#             */
/*   Updated: 2022/03/20 15:45:21 by mlazzare         ###   ########.fr       */
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
                class Compare = std::less< Key >,
                class Alloc = std::allocator< ft::pair< const Key, T > >
             >			 
	class map
	{
		// VAR TYPES
		public:
			class 												value_compare; // defined at the very end

			typedef	T											mapped_type;
            typedef Key                                         key_type;
            typedef std::pair<const Key, T>                     value_type;
            typedef std::size_t									size_type;
            typedef std::ptrdiff_t							    difference_type;
            typedef Compare                                     key_compare;
			typedef Alloc										allocator_type;

		private:
			typedef RBTree<value_type, key_compare, allocator_type>		rbtree;

		public:
			typedef value_type&			                        reference;
			typedef const  	value_type&                     	const_reference;
			typedef typename Alloc::pointer			        	pointer;
			typedef typename Alloc::const_pointer		    	const_pointer;

			typedef ft::rbtree::Iterator							iterator;
			typedef const ft::rbtree::Iterator						const_iterator;
			typedef ft::reverse_iterator< iterator >				reverse_iterator;
			typedef const ft::reverse_iterator< const_iterator >	const_reverse_iterator;
			

		private:
			RBTree												_tree;
			Compare												_compare;
			Allocator											_alloc;

		
		public:
			// member functions
			explicit map( key_compare& const comp = key_compare(),
						allocator_type& const alloc = allocator_type()) :	_tree(),
																			_compare(comp),
																			_alloc(alloc) {};

			map( map& const m ):	_tree(m._tree),
									_compare(m._compare),
									_alloc(m._alloc) {};

			~map() {}
			
			map& operator = ( map& const m)
			{
				if (this != &m)
				{
					_tree = m._tree;
					_compare = m._compare;
					_alloc = m._alloc ;
				}
				return *this;
			}

			// iterators
			iterator begin()								{	return	_tree.begin();		};
			const_iterator begin() const					{	return	_tree.begin();		};
			iterator end()									{	return	_tree.end();		};
			const_iterator end() const						{	return	_tree.end();		};
			iterator rbegin()								{	return	_tree.rbegin();		};
			const_iterator rbegin() const					{	return	_tree.rbegin();		};
			iterator rend()									{	return	_tree.rend();		};
			const_iterator rend() const						{	return	_tree.rend();		};

			// capacity
			bool			empty( void ) const				{	return	_tree.empty();		};
			size_type 		size( void ) const				{	return	_tree.height();		};
			size_type 		max_size() const				{	return	_tree.max_size();	};

			// element access
			mapped_type& operator[] ( const key_type& k )	{	return (*((this->insert(make_pair( k,mapped_type() ))).first)).second;			};

			// modifiers
			// [ INSERT ]
			pair< iterator,bool > 	insert(const value_type& val)						{	_tree.insert( val );			};
			iterator 				insert(iterator position, const value_type& val)	{	_tree.insert( get_nodeptr(position), val );	};
			template <class InputIterator>
  			void insert (InputIterator first, InputIterator last)						{	_tree.insert( first, last );	};

			// [ ERASE ]
			void 					erase(iterator position)							{	_tree.erase( get_nodeptr(position) );		};
			size_type 				erase(const key_type& k)							{	_tree.erase( k );				};
			void 					erase(iterator first, iterator last)				{	_tree.erase( first, last );		};

			// [ SWAP ]
			void 					swap(map& x)					{	if (this != &x)	_tree.swap(x._tree);	};

			// [ CLEAR ]
			void 					clear()							{	_tree.clear();	};
			
			// observers
			key_compare 			key_comp() const				{	return this->_compare;					};
			value_compare 			value_comp() const;				{	return value_compare(this->_compare);	};

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

			// public classes
			class value_compare
			{   
				protected:
					key_compare		comp;
					value_compare (key_compare c) : comp(c) {}  // constructed with map's comparison object
				public:
					// typedef bool 			result_type;
					// typedef value_type 		first_argument_type;
					// typedef value_type 		second_argument_type;
					bool operator() ( const value_type& x, const value_type& y ) const { 		return comp(x.first, y.first);			};
			}

			// helper functions
			value_type	get_valuetype( const key_type& k )				{		return value(k, mapped_type());		}
			treeNode	*get_nodeptr( iterator const & it )				{		return *reinterpret_cast<node * const *>(&it);	}

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
}

#endif
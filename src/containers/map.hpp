/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 07:34:38 by mlazzare          #+#    #+#             */
/*   Updated: 2022/03/17 12:08:50 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iterator>
# include <algorithm>

# include "RBTree.hpp"
# include "../utilities/type_traits.hpp"
# include "../utilities/iterator.hpp"
# include "../utilities/algorithm.hpp"

# define	MAX 461168601842738790;

namespace ft
{
	template < class Key,
                class T,
                class Compare = std::less<Key>,
                class Alloc = std::allocator< std::pair<const Key, T> >
            >
	class map
	{
		// all the var types we need
		public:
			class 												Iterator;
			class 												value_compare;

			typedef	T											mapped_type;
            typedef Key                                         key_type;
            typedef std::pair<const Key, T>                     value_type;
            typedef std::size_t									size_type;
            typedef std::ptrdiff_t							    difference_type;
            typedef Compare                                     key_compare;
			typedef Alloc										allocator_type;

			typedef value_type&			                        reference;
			typedef const  	value_type&                     	const_reference;
			typedef typename Alloc::pointer			        	pointer;
			typedef typename Alloc::const_pointer		    	const_pointer;

			typedef Iterator									iterator;
			typedef const iterator								const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef const ft::reverse_iterator<iterator>		const_reverse_iterator;
			

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

		// capacity
		bool			empty( void ) const				{	return	_tree.empty();	};
		size_type 		size( void ) const				{	return	_tree.height();	};
		size_type 		max_size() const				{	return	MAX;	};

		// element access
		mapped_type& operator[] ( const key_type& k )	{	(*((this->insert(make_pair(k,mapped_type()))).first)).second					};
		mapped_type& at (const key_type& k)				{	try {	} catch (std::out_of_range const& e) {	std::cout << e.what() << '\n';    }};
		const mapped_type& at (const key_type& k) const	{	try {	} catch (std::out_of_range const& e) {	std::cout << e.what() << '\n';    }};


		// allocator
		allocator_type	get_allocator( void ) const	{	return this->_alloc;	};

	};

	template <class T, class Alloc>
	bool	operator == ( const map< T, Alloc >& l, const map< T, Alloc >& r ) 
	{
		if (l.size() != r.size())
			return false;
		return ft::equal(l.begin(), l.end(), r.begin());
	};

	template <class T, class Alloc>
	bool	operator !=  ( const map< T, Alloc >& l, const map< T, Alloc >& r )	{ return !(l == r); }

	template <class T, class Alloc>
	bool	operator <  ( const map< T, Alloc >& l, const map< T, Alloc >& r )		{ return ft::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end()); }

	template <class T, class Alloc>
	bool	operator <=  ( const map< T, Alloc >& l, const map< T, Alloc >& r )	{ return !(r < l); }

	template <class T, class Alloc>
	bool	operator >  ( const map< T, Alloc >& l, const map< T, Alloc >& r )		{ return r < l; }

	template <class T, class Alloc>
	bool	operator >=  ( const map< T, Alloc >& l, const map< T, Alloc >& r )	{ return !(l < r); }

	template <class T, class Alloc>
	void	swap( map< T, Alloc >& x, map< T, Alloc >& y) 							{ x.swap(y); }
}

#endif
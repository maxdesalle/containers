/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 07:34:38 by mlazzare          #+#    #+#             */
/*   Updated: 2022/03/06 12:57:29 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iterator>
# include <algorithm>

# include "../utilities/type_traits.hpp"
# include "../utilities/iterator.hpp"
# include "../utilities/algorithm.hpp"

namespace ft
{
	template < class Key,
                class T,
                class Compare = std::less<Key>,
                class Alloc = std::allocator< std::pair<const Key, T> >
            >
	class map
	{
		public:

			class 												value_compare;

			typedef	T											mapped_type;
            typedef Key                                         key_type;
            typedef std::pair<const Key, T>                     value_type;
            typedef std::size_t									size_type;
            typedef std::ptrdiff_t							    difference_type;
            typedef Compare                                     key_compare;
			typedef Alloc									allocator_type;

			typedef value_type&			                        reference;
			typedef const  	value_type&                     	const_reference;
			typedef typename Alloc::pointer			        pointer;
			typedef typename Alloc::const_pointer		    const_pointer;

			typedef Iterator									iterator;
			typedef const iterator								const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef const ft::reverse_iterator<iterator>		const_reverse_iterator;
			

		private:
			BRTree			_tree;
			Compare			_compare;
			Allocator		_alloc;

		public:


			explicit map( key_compare& const comp = key_compare(),
						allocator_type& const alloc = allocator_type()) :	_tree(),
																			_compare(comp),
																			_alloc(alloc) {};

			map( map& const m ):	_data(m._data),
									_compare(m._compare),
									_alloc(m._alloc) {};

			~map() {}
			
			map& operator = ( map& const m)
			{
				if (this != &m)
				{
					_data = m._data;
					_compare = m._compare;
					_alloc = m._alloc ;
				}
				return *this;
			}
	};

	template <class T, class Alloc>
	bool	operator==(const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);

		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template <class T, class Alloc>
	bool	operator!= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs) { return !(lhs == rhs); }

	template <class T, class Alloc>
	bool	operator<(const map<T,Alloc>& lhs, const map<T,Alloc>& rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template <class T, class Alloc>
	bool	operator<=(const map<T,Alloc>& lhs, const map<T,Alloc>& rhs) { return !(rhs < lhs); }

	template <class T, class Alloc>
	bool	operator>(const map<T,Alloc>& lhs, const map<T,Alloc>& rhs) { return rhs < lhs; }

	template <class T, class Alloc>
	bool	operator>=(const map<T,Alloc>& lhs, const map<T,Alloc>& rhs) { return !(lhs < rhs); }

	template <class T, class Alloc>
	void	swap(map<T,Alloc>& x, map<T,Alloc>& y) { x.swap(y); }
}

#endif
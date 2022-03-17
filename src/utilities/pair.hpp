/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:41:03 by maxdesall         #+#    #+#             */
/*   Updated: 2022/03/17 18:21:36 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template < typename T1, typename T2 >
	struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		T1			first;
		T2			second;

		pair() {}
		template <class U, class V>
			pair(const pair<U,V>& pr): first(pr.first), second(pr.second) {}
		pair(const first_type& a, const second_type& b): first(a), second(b) {}

		pair&		operator = (const pair& pr)
		{
			this->first = pr.first;
			this->scond = pr.second;

			return (*this);
		}
	};

	template < class T1, class T2 >
	pair< T1, T2 > make_pair ( T1 x, T2 y )										{	return pair< T1, T2 >( x, y );	}

	template < class T1, class T2 >
	bool	operator == ( const pair< T1, T2 >& l, const pair< T1, T2 >& r )	{ return l.first == r.first && l.second == r.second; }

	template < class T1, class T2 >
	bool	operator != ( const pair< T1, T2 >& l, const pair< T1, T2 >& r )	{ return !(l == r); }

	template < class T1, class T2 >
	bool	operator < ( const pair< T1, T2 >& l, const pair< T1, T2 >& r )		{ return l.first < r.first || (!(r.first < l.first) && l.second < r.second); }

	template < class T1, class T2 >
	bool	operator <= ( const pair< T1, T2 >& l, const pair< T1, T2 >& r )	{ return !(r < l); }

	template < class T1, class T2 >
	bool	operator > ( const pair< T1, T2 >& l, const pair< T1, T2 >& r )		{ return r < l; }

	template < class T1, class T2 >
	bool	operator >= ( const pair< T1, T2 >& l, const pair< T1, T2 >& r )	{ return !(l < r); }
}

#endif

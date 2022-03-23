/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:41:03 by maxdesall         #+#    #+#             */
/*   Updated: 2022/03/23 09:02:43 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template < typename T1, typename T2 >
	struct pair
	{
		typedef T1	first_t;
		typedef T2	second_t;

		first_t				first;
		second_t			second;

		pair() : first(first_t()),
				 second(second_t())	{};
				 
		template < typename U, typename V >
		pair(const pair< U,V > & p):	first(p.first),
										second(p.second) {};

		pair(const first_t & a, const second_t & b):	first(a),
														second(b) {}

		pair&		operator = ( const pair & p )
		{
			if ( *this != p )
			{
				this->first = p.first;
				this->second = p.second;
			}
			return (*this);
		}
	};

	template < typename T1, typename T2 >
	pair< T1, T2 > make_pair ( T1 x, T2 y )										{	return pair< T1, T2 >( x, y );	}

	template < typename T1, typename T2 >
	bool	operator == ( const pair< T1, T2 > & l, const pair< T1, T2 > & r )	{ return l.first == r.first && l.second == r.second; }

	template < typename T1, typename T2 >
	bool	operator != ( const pair< T1, T2 > & l, const pair< T1, T2 > & r )	{ return !(l == r); }

	template < typename T1, typename T2 >
	bool	operator < ( const pair< T1, T2 > & l, const pair< T1, T2 > & r )	{ return l.first < r.first || (!(r.first < l.first) && l.second < r.second); }

	template < typename T1, typename T2 >
	bool	operator <= ( const pair< T1, T2 > & l, const pair< T1, T2 > & r )	{ return !(r < l); }

	template < typename T1, typename T2 >
	bool	operator > ( const pair< T1, T2 > & l, const pair< T1, T2 > & r )	{ return r < l; }

	template < typename T1, typename T2 >
	bool	operator >= ( const pair< T1, T2 > & l, const pair< T1, T2 > & r )	{ return !(l < r); }
};

#endif

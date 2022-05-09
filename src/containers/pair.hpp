/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:41:03 by maxdesall         #+#    #+#             */
/*   Updated: 2022/05/09 20:05:53 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template < typename T1, typename T2 >
	class pair
	{
		public: 
			typedef T1	first_type;
			typedef T2	second_type;

			first_type				first;
			second_type			second;

			pair()	:	first(),
						second()	{};
					
			template < typename U, typename V >
			pair(const pair< U,V > & p):	first(p.first),
											second(p.second) {};

			pair(const first_type & a, const second_type & b):	first(a),
																second(b) {}

			pair&		operator = ( pair const& p )
			{
				if ( this != &p )	{	first = p.first; second = p.second;		}
				return *this;
			}
			~pair() {};
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

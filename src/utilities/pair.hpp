/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxdesalle <mdesalle@student.s19.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:41:03 by maxdesall         #+#    #+#             */
/*   Updated: 2021/12/08 14:16:43 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template <class T1, class T2>
	pair<T1, T2> make_pair (T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	template <class T1, class T2>
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

		pair&		operator=(const pair& pr)
		{
			this->first = pr.first;
			this->scond = pr.second;

			return (*this);
		}
	};

	template <class T1, class T2>
	bool	operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (lhs.first == rhs.first && lhs.second == rhs.second); }

	template <class T1, class T2>
	bool	operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (!(lhs == rhs)); }

	template <class T1, class T2>
	bool	operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); }

	template <class T1, class T2>
	bool	operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (!(rhs < lhs)); }

	template <class T1, class T2>
	bool	operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (rhs < lhs); }

	template <class T1, class T2>
	bool	operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) { return (!(lhs < rhs)); }
}

#endif

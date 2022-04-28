/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 09:34:30 by maxdesall         #+#    #+#             */
/*   Updated: 2022/04/21 23:41:00 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS
# define TYPE_TRAITS

namespace ft
{
	template <bool Cond, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <class T, T v>
	struct integral_constant
	{
		static const T					value = v;
		T								value_type;
		typedef integral_constant<T, v>	type;
	};

	typedef integral_constant<bool, true>	true_type;
	typedef integral_constant<bool, false>	false_type;

	template <class T>
		struct is_integral : public false_type {};

	template <class T> struct
		is_integral<const T> : public is_integral<T> {};
	template <class T> struct
		is_integral<volatile const T> : public is_integral<T>{};
	template <class T> struct
		is_integral<volatile T> : public is_integral<T>{};

	template <> struct
		is_integral<unsigned char> : public true_type {};
	template <> struct
		is_integral<unsigned short> : public true_type{};
	template <> struct
		is_integral<unsigned int> : public true_type{};
	template <> struct
		is_integral<unsigned long> : public true_type{};
	template <> struct
		is_integral<unsigned long long> : public true_type{};
	template <> struct
		is_integral<signed char> : public true_type{};
	template <> struct
		is_integral<short> : public true_type{};
	template <> struct
		is_integral<int> : public true_type{};
	template <> struct
		is_integral<long> : public true_type{};
	template <> struct
		is_integral<long long> : public true_type{};
	template <> struct
		is_integral<char> : public true_type{};
	template <> struct
		is_integral<bool> : public true_type{};

	template<typename T>
		void	swap(T &first, T& second) {
			T	tmp = first;
			first = second;
			second = tmp;
		}
};

#endif

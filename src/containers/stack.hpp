/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxdesalle <mdesalle@student.s19.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:35:46 by maxdesall         #+#    #+#             */
/*   Updated: 2022/01/12 09:59:08 by maxdesall        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:

			typedef T			value_type;
			typedef Container	container_type;
			typedef ptrdiff_t	size_type;

			explicit			stack(const container_type& ctnr = container_type()): _ctnr(ctnr) {}

			bool				empty() const { return (_ctnr.empty()); }
			size_type			size() const { return (_ctnr.size()); }
			value_type&			top() { return (_ctnr.back()); }
			const value_type&	top() const { return (_ctnr.back()); }
			void				push(const value_type& val) { _ctnr.push_back(val); }
			void				pop() { _ctnr.pop_back(); }

			friend bool			operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._ctnr == rhs._ctnr); }

			friend bool			operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (lhs._ctnr < rhs._ctnr); }

		private:

			container_type		_ctnr;
	};

	template <class T, class Container>
	bool						operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (!(lhs == rhs)); }

	template <class T, class Container>
	bool						operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (!(rhs < lhs)); }

	template <class T, class Container>
	bool						operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (rhs < lhs); }

	template <class T, class Container>
	bool						operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return (!(lhs < rhs)); }
}

#endif

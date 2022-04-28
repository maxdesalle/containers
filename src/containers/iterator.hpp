/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:14:41 by maxdesall         #+#    #+#             */
/*   Updated: 2022/04/15 13:26:59 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <vector>
# include <cstddef>
# include <iterator>

namespace ft
{
	template < class Iterator >
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template < class T >
	struct iterator_traits< T* >
	{
		typedef ptrdiff_t								difference_type;
		typedef T										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef std::random_access_iterator_tag			iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t								difference_type;
		typedef T										value_type;
		typedef const T*								pointer;
		typedef const T&								reference;
		typedef std::random_access_iterator_tag			iterator_category;
	};

	/* template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&> */
	/* struct iterator */
	/* { */
	/* 	typedef T										value_type; */
	/* 	typedef Distance								difference_type; */
	/* 	typedef Pointer									pointer; */
	/* 	typedef Reference								reference; */
	/* 	typedef Category								iterator_category; */
	/* }; */

	template <class Iterator>
	class reverse_iterator
	{
		public:

			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
		
		private:
			Iterator		_it;

		public:
			reverse_iterator(): _it() {}
			explicit			reverse_iterator(iterator_type it): _it(it) {}

			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& rev_it): _it(rev_it.base()) {}

			reverse_iterator(const reverse_iterator& rev_it): _it(rev_it.base()) {}

			template <class U>
			reverse_iterator& operator=(const reverse_iterator<U>& other)
			{
				this->_it = other.base();
				return (*this);
			}

			iterator_type		base() const { return (_it); }

			reference			operator*() const
			{
				iterator_type	tmp = _it;
				return *(--tmp);
			}

			reverse_iterator	operator+(difference_type n) const { return (reverse_iterator(this->base() - n)); };

			reverse_iterator&	operator++()
			{
				--_it; // THIS IS TO CHECK WITH MAX
				return (*this);
			};

			reverse_iterator	operator++(int)
			{
				reverse_iterator temp = *this;
				--_it;
				return (temp);
			}

			reverse_iterator&	operator+=(difference_type n)
			{
				this->_it -= n;
				return (*this);
			}

			reverse_iterator	operator-(difference_type n) const { return (reverse_iterator(this->base() + n)); }

			reverse_iterator&	operator--()
			{
				++_it;
				return (*this);
			}

			reverse_iterator	operator--(int)
			{
				reverse_iterator temp = *this;
				--_it;
				return (temp);
			}

			reverse_iterator	operator-=(difference_type n)
			{
				this->_it += n;
				return (*this);
			}

			pointer				operator->() const { return &(operator*()); }

			reference			operator[] (difference_type n) const { return (this->base()[-n - 1]); }


	};

	template <class Iterator>
	bool	operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); }

	template <class Iterator>
	bool	operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() != rhs.base()); }

	template <class Iterator>
	bool	operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); }

	template <class Iterator>
	bool	operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() >= rhs.base()); }

	template <class Iterator>
	bool	operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() < rhs.base()); }

	template <class Iterator>
	bool 	operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() <= rhs.base()); }

	template <class Iterator>
	reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) { return (rev_it + n); }

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() - rhs.base()); }
};

#endif

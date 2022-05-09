/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:14:41 by maxdesall         #+#    #+#             */
/*   Updated: 2022/05/09 10:52:21 by mlazzare         ###   ########.fr       */
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


	/* credits go to @tderwedu: https://github.com/tderwedu/42cursus/blob/main/13_ft_containers/src/iterator.hpp#L83 */
	template<typename InputIterator>
		typename iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
		{
			typename iterator_traits<InputIterator>::difference_type n = 0;

			while (first != last)
			{
				++n;
				++first;
			}
			return n;
		}

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


			protected:
				Iterator		_it;

			public:
				reverse_iterator(): _it() {}
				reverse_iterator(iterator_type it): _it(it) {}

				template <class Iter>
					reverse_iterator(const reverse_iterator<Iter> & rev_it): _it(rev_it.base()) {}

				template <class Iter>
					reverse_iterator& operator=(const reverse_iterator<Iter>& other)
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

				reverse_iterator	operator+(difference_type n) const { return (reverse_iterator(_it - n)); };

				reverse_iterator&	operator++()
				{
					// std::cout << _it->second << std::endl;
					--_it;
					// std::cout << "AFTER" << std::endl;
					// std::cout << _it->second << std::endl;
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

				reverse_iterator	operator-(difference_type n) const { return (reverse_iterator(_it + n)); }

				reverse_iterator&	operator--()
				{
					++_it;
					return (*this);
				}

				reverse_iterator	operator--(int)
				{
					reverse_iterator temp = *this;
					++_it;
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

	template <class Iter1, class Iter2>
		bool	operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) { return (lhs.base() == rhs.base()); }

	template <class Iter1, class Iter2>
		bool	operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) { return (lhs.base() != rhs.base()); }

	template <class Iter1, class Iter2>
		bool	operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) { return (lhs.base() > rhs.base()); }

	template <class Iter1, class Iter2>
		bool	operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) { return (lhs.base() >= rhs.base()); }

	template <class Iter1, class Iter2>
		bool	operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) { return (lhs.base() < rhs.base()); }

	template <class Iter1, class Iter2>
		bool 	operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) { return (lhs.base() <= rhs.base()); }

	template <class Iter>
		reverse_iterator<Iter>	operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& rev_it) { return (rev_it + n); }

	template <class Iter1, class Iter2>
		typename reverse_iterator<Iter1>::difference_type operator-(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) { return (rhs.base() - lhs.base()); }
};

#endif

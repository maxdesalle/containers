/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxdesalle <mdesalle@student.s19.be>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:03 by maxdesall         #+#    #+#             */
/*   Updated: 2022/03/23 14:11:20 by mdesalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iterator>
# include <algorithm>

# include "../utilities/type_traits.hpp"
# include "../utilities/iterator.hpp"
# include "../utilities/algorithm.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:

			class 												Iterator;

			typedef	T											value_type;
			typedef Allocator									allocator_type;

			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			typedef Iterator									iterator;
			typedef const iterator								const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef const ft::reverse_iterator<iterator>		const_reverse_iterator;
			typedef size_t										size_type;
			typedef typename iterator::difference_type			difference_type;

			explicit	vector(const allocator_type& alloc = allocator_type()): _alloc(alloc), _capacity(0), _elem(NULL), _size(0) {}
			explicit	vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): _alloc(alloc), _capacity(0), _elem(NULL), _size(0) { insert(begin(), n, val); }
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0): _alloc(alloc), _capacity(0), _elem(NULL), _size(0) { insert(begin(), first, last); }

			vector(const vector& x): _alloc(x._alloc), _capacity(x._capacity), _elem(_alloc.allocate(x._capacity)), _size(x._size)
			{
				assign(x.begin(), x.end());
			}

			~vector()
			{
				clear();
				_alloc.deallocate(_elem, _capacity);
			}

			template <class InputIterator>
			void					assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				size_type	n = last - first;

				clear();
				if (n > _capacity)
					reserve(n);
				for (size_type i = 0; i < n; i += 1)
					_alloc.construct(_elem + i, *first++);
				_size = n;
			}

			void					assign(size_type n, const value_type& val)
			{
				clear();
				if (n > _capacity)
					reserve(n);
				for (size_type i = 0; i < n; i += 1)
					_alloc.construct(_elem + i, val);
				_size = n;
			}

			reference				at(size_type n)
			{
				if (n < _size)
					return (_elem[n]);
				else
					throw std::out_of_range("element out of range");
			}

			const_reference			at(size_type n) const
			{
				if (n < _size)
					return (_elem[n]);
				else
					throw std::out_of_range("element out of range");
			}

			reference				back() { return (_elem[_size - 1]); }
			const_reference			back() const { return (_elem[_size - 1]); }

			iterator				begin() { return (iterator(_elem)); }
			const_iterator			begin() const { return (const_iterator(_elem)); }

			size_type				capacity() const { return (_capacity); }

			void					clear() { erase(begin(), end()); }

			bool					empty() const { return (_size == 0); }

			iterator				end() { return (iterator(_elem + _size)); }
			const_iterator			end() const { return (const_iterator(_elem + _size)); }

			iterator				erase(iterator position)
			{
				size_type			val = position - begin();

				_size -= 1;
				_alloc.destroy(&_elem[val]);
				for (size_type i = val; i < _size; i += 1)
				{
					_alloc.construct(&_elem[i], _elem[i + 1]);
					_alloc.destroy(&_elem[i + 1]);
				}

				return (iterator(&_elem[val]));
			}

			iterator				erase(iterator first, iterator last)
			{
				size_type			diff = last - first;

				while (diff-- > 0)
					erase(begin() + diff);

				return (first);
			}

			reference				front() { return (_elem[0]); }
			const_reference 		front() const { return (_elem[0]); }

			allocator_type			get_allocator() const { return (_alloc); }

			iterator				insert(iterator position, const value_type& val)
			{
				size_type			i = position - begin();

				insert(position, 1, val);
				return (begin() + i);
			}

			void					insert(iterator position, size_type n, const value_type& val)
			{
				size_type			i = position - begin();

				if ((_size + n) > _capacity)
					reserve(_new_capacity(_size + n));
				for (size_type j = n + _size - 1; j > i + n - 1; j -= 1)
				{
					_alloc.construct(&_elem[j], _elem[j - n]);
					_alloc.destroy(&_elem[j - n]);
				}
				for (size_type k = i; k < i + n; k += 1)
				{
					_alloc.construct(&_elem[k], val);
					_size += 1;
				}
			}

			template <class InputIterator>
			void					insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				size_type			i = position - begin();
				size_type			j = last - first;

				if ((_size + j) > _capacity)
					reserve(_new_capacity(_size + j));

				for (size_type k = j + _size - 1; k > i + j - 1; k -= 1)
				{
					_alloc.construct(&_elem[k], _elem[k - j]);
					_alloc.destroy(&_elem[k - j]);
				}
				for (size_type l = i; l < i + j; l += 1)
				{
					_alloc.construct(&_elem[l], *first);
					first += 1;
					_size += 1;
				}
			}

			size_type				max_size() const { return (_alloc.max_size()); }

			vector&					operator=(const vector& x)
			{
				if (this != &x)
					assign(x.begin(), x.end());
				return (*this);
			}

			reference				operator[](size_type n) { return (_elem[n]); }
			const_reference			operator[](size_type n) const { return (_elem[n]); }

			void					pop_back() { _alloc.destroy(&_elem[--_size]); }

			void					push_back(const value_type& val)
			{
				if (_size == _capacity)
					reserve(_new_capacity(_size + 1));
				_alloc.construct(_elem + _size, val);
				_size += 1;
			}

			reverse_iterator		rbegin() { return (reverse_iterator(end())); }
			const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end())); }

			reverse_iterator		rend() { return (reverse_iterator(begin())); }
			const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }

			void					reserve(size_type n)
			{
				if (n <= _capacity)
					return ;
				n = _new_capacity(n);
				if (n > max_size())
					throw std::length_error("requested allocation size is greater than max size");

				value_type	*vec = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i += 1)
				{
					_alloc.construct(&vec[i], _elem[i]);
					_alloc.destroy(&_elem[i]);
				}
				_alloc.deallocate(_elem, _capacity);
				_elem = vec;
				_capacity = n;
			}

			void					resize(size_type n, value_type val = value_type())
			{
				while (n < _size)
					pop_back();
				while (n > _size)
					push_back(val);
			}

			size_type				size() const { return (_size); }

			void					swap(vector& x)
			{
				std::swap(_alloc, x._alloc);
				std::swap(_capacity, x._capacity);
				std::swap(_elem, x._elem);
				std::swap(_size, x._size);
			}

			class Iterator
			{
				public:

					typedef ptrdiff_t								difference_type;
					typedef T										value_type;
					typedef T*										pointer;
					typedef T&										reference;
					typedef std::random_access_iterator_tag			iterator_category;

					Iterator(void): _it() {}
					explicit	Iterator(pointer it): _it(it) {}

					Iterator(const Iterator& it): _it(it.base()) {}

					pointer			base() const { return (_it); }

					Iterator		operator=(const Iterator& rhs)
					{
						this->_it = rhs.base();
						return (*this);
					}

					Iterator		operator+(difference_type n) const { return (Iterator(this->base() + n)); }

					Iterator&	operator++()
					{
						this->_it += 1;
						return (*this);
					}

					Iterator	operator++(int)
					{
						Iterator(temp) = *this;
						this->_it += 1;
						return (temp);
					}

					Iterator&	operator+=(difference_type n)
					{
						this->_it += n;
						return (*this);
					}

					Iterator	operator-(difference_type n) const { return (Iterator(this->base() - n)); }

					Iterator&	operator--()
					{
						this->_it -= 1;
						return (*this);
					}

					Iterator	operator--(int)
					{
						reverse_iterator(temp) = *this;
						this->_it -= 1;
						return (temp);
					}

					Iterator	operator-=(difference_type n)
					{
						this->_it -= n;
						return (*this);
					}

					reference		operator*() { return (*_it); }
					const_reference	operator*() const { return (*_it); }

					pointer			operator->() { return &(operator*()); }
					const_pointer	operator->() const { return &(operator*()); }

					reference		operator[] (difference_type n) { return (this->base()[n]); }
					const_reference	operator[] (difference_type n) const { return (this->base()[n]); }

					friend difference_type	operator-(const Iterator& lhs, const Iterator& rhs) { return (&(*lhs) - &(*rhs)); }

					friend bool				operator==(const Iterator& lhs, const Iterator& rhs) { return (lhs.base() == rhs.base()); }
					friend bool				operator!=(const Iterator& lhs, const Iterator& rhs) { return (lhs.base() != rhs.base()); }
					friend bool				operator<(const Iterator& lhs, const Iterator& rhs) { return (lhs.base() < rhs.base()); }
					friend bool				operator<=(const Iterator& lhs, const Iterator& rhs) { return (lhs.base() <= rhs.base()); }
					friend bool				operator>(const Iterator& lhs, const Iterator& rhs) { return (lhs.base() > rhs.base()); }
					friend bool 			operator>=(const Iterator& lhs, const Iterator& rhs) { return (lhs.base() >= rhs.base()); }

				private:

					pointer	_it;
			};

		private:

			size_type		_new_capacity(size_type size)
			{
				size_type			n;

				n = 1;
				while (n < size)
					n *= 2;
				return (n);
			}

			allocator_type	_alloc;
			size_type		_capacity;
			value_type		*_elem;
			size_type		_size;
	};

	template <class T, class Alloc>
	bool	operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);

		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template <class T, class Alloc>
	bool	operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs == rhs)); }

	template <class T, class Alloc>
	bool	operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

	template <class T, class Alloc>
	bool	operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(rhs < lhs)); }

	template <class T, class Alloc>
	bool	operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (rhs < lhs); }

	template <class T, class Alloc>
	bool	operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (!(lhs < rhs)); }

	template <class T, class Alloc>
	void	swap(vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }
}

#endif

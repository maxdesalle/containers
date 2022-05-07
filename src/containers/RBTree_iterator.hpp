/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:47:47 by mlazzare          #+#    #+#             */
/*   Updated: 2022/05/07 16:26:21 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_ITERATOR_HPP
# define RBTREE_ITERATOR_HPP

# include <iostream>
# include <memory> // std::allocator
# include <cmath>

# include "RBTree_iterator.hpp"
# include "type_traits.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "pair.hpp"

enum        nodeColor {        RED, BLACK      };

template < typename T >
struct node {
    typedef T           value_type;
    value_type          value;
	node                *parent, *left, *right;
	int                color, leaf;

    node( void )    :   value( 0 ),
                            parent (0), left(0), right(0),
                            color( RED )        {};
    node( T const& value, node *parent, int leaf )   :      value(value),
                                                            parent (parent), left(0), right(0),
                                                            color( RED ), leaf(leaf)         {};
    node( node const& t )   :   value(t.value),
                                        parent (t.parent), left(t.left), right(t.right),
                                        color( t.color ), leaf(t.leaf) {};
    node const&     operator = ( node const& t )
    {
        this->value = t.value;
        this->parent = t.parent;
        this->left = t.left;
        this->right = t.right;
        this->color = t.color;
        this->leaf = t.leaf;
        return *this;
    }
    ~node () {};
};

template< typename U >
class treeIterator
{
    public:
        typedef U								value_type;
        typedef U*								pointer;
        typedef const U*						const_pointer;
        typedef U&								reference;
        typedef const U&                        const_reference;
        typedef std::ptrdiff_t					difference_type;
        typedef std::bidirectional_iterator_tag	iterator_category;
        typedef node< value_type >              treeNode;
        typedef node< const value_type >        const_treeNode;
        typedef treeIterator< U >               iterator;
        typedef treeIterator< const U >         const_iterator;

        treeIterator( void ) :  _node(NULL)                     {};
        treeIterator( treeNode * current ) : _node(current)      {};
        treeIterator( treeIterator const& t ) : _node(t.node())  {};
        treeIterator		operator = ( treeIterator t )       {       _node = t.node(); return *this;                             };
        template < class _it >
        treeIterator( treeIterator< _it > const& t ) : _node(reinterpret_cast<treeNode *>(t.node()))  {};

        // operator            treeIterator< const U >() const						    {   return treeIterator< const U >(reinterpret_cast<const_treeNode const *>(_node));    }

        treeNode            *node( void )                       {       return _node;                                               };
        treeNode            *node( void )   const               {       return _node;                                               };

        reference		operator* () 							{   return _node->value;    };
        const_reference	operator* () const						{   return _node->value;    };
        pointer			operator->()							{   return &_node->value;   };
        const_pointer	operator->() const						{   return &_node->value;   };

        treeIterator&		operator ++ ()
        {
            if (!_node || !_node->leaf)
                return *this;
            if (_node && _node->right && _node->right->leaf)
            {
                _node = _node->right;
                while (_node && _node->left && _node->left->leaf) _node = _node->left;
            }
            else
            {
                treeNode	*curr = _node;
                _node = _node->parent;
                while (_node && _node->leaf && _node->right == curr)
                {
                    curr = _node;
                    _node = _node->parent;
                };                   
            }
            return *this;
        }

        treeIterator&		operator -- ()
        {
            if (!_node || !_node->leaf)
                _node = _node->parent;
            else if (_node->left && _node->left->leaf)
            {
                _node = _node->left;
                while (_node->right && _node->right->leaf) _node = _node->right;
            }
            else
            {
                // std::cout << "minus\n";
                treeNode	*curr = _node;
                _node = _node->parent;
                while (_node && _node->leaf && _node->left == curr)
                {
                    // std::cout << "while" << std::endl;
                    // std::cout << curr->value.second << std::endl;
                    curr = _node;
                    _node = _node->parent;
                };
                _node = curr;
            }
            return *this;
        }
        treeIterator		operator ++ ( int )							{   treeIterator ptr(*this); operator++(); return ptr;  }
        treeIterator		operator -- ( int )							{   treeIterator ptr(*this); operator--(); return ptr;  }

        bool			    operator == ( treeIterator const& t )	const	{   return _node == t._node;    }
        bool			    operator != ( treeIterator const& t )	const	{   return _node != t._node;    }
        
        private:
            treeNode*			    _node;
};

#endif

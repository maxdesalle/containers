/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:47:47 by mlazzare          #+#    #+#             */
/*   Updated: 2022/04/10 22:51:54 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_ITERATOR_HPP
# define RBTREE_ITERATOR_HPP

# include <iostream>
# include <memory> // std::allocator
# include <cmath>

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
	int                color, end;

    node( void )    :   value( nullptr ),
                            parent (0), left(0), right(0),
                            color( RED )        {};
    node( T const& value, node *parent )   :    value(value),
                                                parent (parent), left(0), right(0),
                                                color( RED )         {};
    node( node const& t )   :   value(t.value),
                                        parent (t.parent), left(t.left), right(t.right),
                                        color( t.color ), end(t.end) {};
    node const&     operator = ( node const& t )
    {
        this->value = t.value;
        this->parent = t.parent;
        this->left = t.left;
        this->right = t.right;
        this->color = t.color;
        this->end = t.end;
        return *this;
    }
    ~node () {};
};

template< typename U>
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

        treeIterator( void ) :  _node(NULL)                     {};
        treeIterator( treeNode* current ) : _node(current)      {};
        treeIterator( treeIterator const& t ) : _node(t._node)  {};
        treeIterator		operator = ( treeIterator t )       {       _node = t._node; return *this;                              };
        treeNode            *node( void )                       {       return _node;                                               };
        treeNode            *node( void )   const               {       return _node;                                               };

        reference		operator* () 							{   return _node->value;    };
        const_reference	operator* () const						{   return _node->value;    };
        pointer			operator->()							{   return &_node->value;   };
        const_pointer	operator->() const						{   return &_node->value;   };

        treeIterator&		operator ++ ()
        {
            if (_node->right)
            {
                _node = _node->right;
                printf("piu piu\n");
                while (_node->left) _node = _node->left;
            }
            else
            {
                while (_node->parent && _node->parent->parent)  {   
                    if (_node->parent->left == _node) break ;
                    _node = _node->parent;    
                };
            }
            return *this;
        }

        treeIterator&		operator -- ()
        {
            if (_node->left)
            {
                while (_node->right->end == 0)  _node = _node->right;
            }
            else
            {
                while (_node->parent)  {   
                    if (_node->parent->right == _node) break ;
                    _node = _node->parent;    
                };
            }
            return *this;
        }
        treeIterator		operator ++ ( int )							{   treeIterator ptr(*this); operator++(); return ptr;  }
        treeIterator		operator -- ( int )							{   treeIterator ptr(*this); operator--(); return ptr;  }

        bool			    operator == ( treeIterator const& t )	const	{   return _node == t._node;    }
        bool			    operator != ( treeIterator const& t )	const	{   return _node != t._node;    }

        // operator            const_iterator () const						    {   return const_iterator(_node);    }
        
        private:
            treeNode*			    _node;
};

#endif

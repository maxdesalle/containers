/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:47:47 by mlazzare          #+#    #+#             */
/*   Updated: 2022/03/21 08:48:14 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP


# include <iostream>
# include <memory> // std::allocator
# include <cmath>

# include "../utilities/type_traits.hpp"
# include "../utilities/iterator.hpp"
# include "../utilities/algorithm.hpp"
# include "../utilities/pair.hpp"

enum nodeColor {    RED, BLACK  };

template < typename T >
struct treeNode {
	treeNode    *parent, *left, *right;
    T           *val;
	bool        color;

    treeNode(T  *value):    val(value),
                            parent (0), left(0), right(0),
                            color( BLACK ) {};
};

template <typename T, typename Compare, typename Alloc = std::allocator<T> >
class RBTree {

    public:
    // VAR TYPES
        template <class U>
        class	Iterator;

        typedef T												        value_type;
        typedef Allocator										        allocator_type;             // container allocator
        typedef typename allocator_type::pointer				        pointer;
        typedef typename allocator_type::const_pointer			        const_pointer;
        typedef typename allocator_type::reference				        reference;
        typedef typename allocator_type::const_reference		        const_reference;
        typedef Iterator<T>										        iterator;
        typedef Iterator<const T>								        const_iterator;
        typedef ft::reverse_iterator<iterator>					        reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>			        const_reverse_iterator;
        typedef std::size_t										        size_type;

        typedef typename Allocator::template rebind< treeNode >::other	node_allocator;             // container's element allocator 
    
    private:
        // TREE ELEMENTS
        treeNode                _root;
        size_type               _height;
        Compare                 _comp;
        node_allocator          _node_alloc;

    public:
        // CONSTRUCTORS
        RBTree( void ) : _root(nullptr),
                         _height(0),
                         _comp(),
                         _node_alloc()    {};
        RBTree( Compare const &comp = Compare(), Alloc const &alloc = allocator_type() ) :  _root(nullptr),
                                                                                            _height(0),
                                                                                            _comp(comp),
                                                                                            _node_alloc(alloc)    {};

        RBTree( RBTree const &t ) : _root(t._root),
                                    _height(t._height),
                                    _comp(t._comp),
                                    _alloc(t._alloc)    {};

        RBTree& operator = ( RBTree const &t )
        {
            if ( this != t)
            {
                if (this._root)
                    this.clear();
                _height(t._height);
                _comp(t._comp);
                _alloc(t._alloc);
            }
            return *this;
        }

        ~RBTree(void) { clear(); }

        // INSERT, DEL, CLEAR, SEARCH ELEMS
        void    insert( treeNode  value_type pair )
        {
            treeNode *newNode = new treeNode( pair );
            if (!_root)  
            {    _root = newNode; _height++; return ;
            else
            {
                treeNode *curr = _root;
                while (curr)
                {
                    if (_comp(newNode->value.first, curr->value.first))
                        curr = curr->left;
                    else
                        curr = curr->right;
                }
                if (_comp(newNode->value.first, curr->value.first))
                    curr->left = newNode;
                else
                    curr->right = newNode;
            }

        };
        

        bool    empty( void )   {   return !_root;      };
        size_t  size( void )    {   return _height;      };

		class EmptyTree : public std::exception {
			public:
				virtual const char* what() const throw() {
					return ( "Tree is empty" );
				}
		};

};

#endif

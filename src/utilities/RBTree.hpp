/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:47:47 by mlazzare          #+#    #+#             */
/*   Updated: 2022/03/24 00:33:53 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <iostream>
# include <memory> // std::allocator
# include <cmath>

# include "type_traits.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "pair.hpp"

enum nodeColor {    RED, BLACK  };

template < typename T >
struct node {
    typedef T           value_type;
    value_type          value;
	node    *parent, *left, *right;
	bool        color;

    node( void )    :   value( nullptr ),
                            parent (0), left(0), right(0),
                            color( BLACK ) {};
    node( T  *value )   :  value(value),
                                parent (0), left(0), right(0),
                                color( BLACK ) {};
    node( node const& t )   :   value(t.value),
                                        parent (t.parent), left(t.left), right(t.right),
                                        color( t.color ) {};
    node const&     operator = ( node const& t )
    {
        this->value = t.value;
        this->parent = t.parent;
        this->left = t.left;
        this->right = t.right;
        this->color = t.color;
        return *this;
    }
    ~node () {};
};

template < class T, class Compare = std::less< T >, class Alloc = std::allocator<T> >
class RBTree
{
    public:
    // VAR TYPES
        template <class U>
        class	treeIterator;

        typedef T												            value_type;
        typedef Alloc   										            allocator_type;                // container allocator
        typedef Compare                                                     value_compare;             
        typedef typename allocator_type::pointer				            pointer;
        typedef typename allocator_type::const_pointer			            const_pointer;
        typedef typename allocator_type::reference				            reference;
        typedef typename allocator_type::const_reference		            const_reference;
        typedef treeIterator< T >									        iterator;
        typedef treeIterator< const T >								        const_iterator;
        typedef ft::reverse_iterator< iterator >				            reverse_iterator;
        typedef ft::reverse_iterator< const_iterator >			            const_reverse_iterator;
        typedef std::size_t										            size_type;
        typedef node< value_type >                                          treeNode;
        typedef typename Alloc::template rebind< treeNode >::other	        node_allocator;             // container's element allocator 
    
    private:
        // TREE ELEMENTS
        treeNode                    *_root;
        size_type                   _height;
        Compare                     _comp;
        node_allocator              _node_alloc;

    public:
        // CONSTRUCTORS
        explicit RBTree( const value_compare &comp, const allocator_type &alloc) :  _root(nullptr),
                                                                                    _height(0),
                                                                                    _comp(comp),
                                                                                    _node_alloc(alloc)    {};

        RBTree( RBTree const &t ) : _root(t._root),
                                    _height(t._height),
                                    _comp(t._comp),
                                    _node_alloc(t._node_alloc)    {};

        RBTree& operator = ( RBTree const &t )
        {
            if ( this != &t)
            {
                if (_root)
                    this->clear(_root);
                _height = t._height;
                _comp = t._comp;
                _node_alloc = t._node_alloc;
            }
            return *this;
        };

        ~RBTree(void) { };

        // INSERT, DEL, CLEAR, SEARCH ELEMS
        // [INSERT]
        treeNode                    *newNode( value_type const& pair )
        {
            treeNode    *newnode = _node_alloc.allocate(1);
			newnode->parent = nullptr;
			newnode->left = nullptr;
			newnode->right = nullptr;
			newnode->color = BLACK;
            _node_alloc.construct(&(newnode->value), pair);
            _height++;
			return newnode;

        };

        ft::pair< iterator, bool>    insert( value_type const& pair )
        {
            if (!_root) { _root = newNode( pair ); return ft::make_pair(iterator(_root, this), true); }
            treeNode *curr = _root;
            treeNode *parent;
            while (curr)
            {
                parent = curr;
                if (_comp(pair, curr->value))   curr = curr->left;
                else                            curr = curr->right;
            }
            if (_comp(pair, parent->value))       curr = newNode( pair );
            else                                  curr = newNode( pair );
            // balanceTree(); TO DO
            return ft::make_pair(iterator(curr, this), true);
        };

        iterator 				insert(iterator position, const value_type& value)  {       return insert(value).first; (void)position;         }
		
    	template <class InputIterator>
	    void					insert(InputIterator first, InputIterator last)	    {       while (first != last)   insert(*first++);           };

        void 					erase( iterator position )							//{	_tree.erase( get_treeNodeptr(position) );		};
        {
            (void)position;
        //     try
        //     {
        //         treeNode *curr = _root;
        //         if (!curr)  curr = new treeNode( pair );
        //         else
        //         {
        //             while (curr)
        //             {
        //                 if (_comp(newNode->value.first, curr->value.first))
        //                     curr = curr->left;
        //                 else
        //                     curr = curr->right;
        //             }
        //             if (_comp(newNode->value.first, curr->value.first))
        //                 curr->left = new treeNode( pair );
        //             else
        //                 curr->right = new treeNode( pair );
        //         }
                    
        //     }
        //     catch( const RBTree::KeyNotFound & e )    {   std::cerr << e.what() << '\n';  }            
        }
        
		// size_type 				erase(const key_type& k)							{	_tree.erase( k );				};

		// void 					erase(treeIterator first, treeIterator last)				{	_tree.erase( first, last );		};

        // FIND


        // CLEAR
        void        delNode(treeNode *node)        {    _node_alloc.destroy(node);  _node_alloc.deallocate(node, 1);  --_height;      }
        void        clear(treeNode *root)
        {
            if (!root)  return ;
            clear(root->left);
            clear(root->right);
            delNode(root);
        }

        
        // capacity
        bool        empty( void ) const      {   return _height == 0;                     };
        size_type   size( void )  const      {   return _height;                          };
	    size_type	max_size() const	     {   return _node_alloc.max_size();           };

        // exceptions
		class EmptyTree : public std::exception {
			public:
				virtual const char* what() const throw() {
					return ( "Tree is empty" );
				}
		};

        class KeyNotFound : public std::exception {
			public:
				virtual const char* what() const throw() {
					return ( "Key not found" );
				}
		};

        // treeIterator
    public:
        template < class U >
        class treeIterator
        {
            public:
                typedef U								value_type;
                typedef U*								pointer;
                typedef U&								reference;
                typedef std::ptrdiff_t					difference_type;
                typedef std::bidirectional_iterator_tag	iterator_category;
                typedef node< value_type >              treeNode;

            private:
                treeNode*			    _node;
                const RBTree*	        _tree;

            public:
                treeIterator( void ) :  _node(NULL),
                                        _tree(NULL) {};
                treeIterator( treeNode* current, const RBTree *tree ) : _node(current),
                                                                        _tree(tree) {};
                treeIterator( treeIterator const& t ) : _node(t._node),
                                                        _tree(t._tree) {};
                treeIterator		operator = ( treeIterator t )
                { 
                    _node = t._node;
                    _tree = t._tree;
                    return *this;
                }

                reference		operator* () 							{   return _node->value;    }
                const_reference	operator* () const						{   return _node->value;    }
                pointer			operator->()							{   return &_node->value;   }
                const_pointer	operator->() const						{   return &_node->value;   }

                treeIterator&		operator ++ ()
                {
                    if (!_node) return *this;
                    if (_node->right)
                    {
                        _node = _node->right;
                        while (_node->left)
                            _node = _node->left;
                    }
                    else
                    {
                        treeNode	*ptr = _node->parent;
                        while (ptr && ptr->right == _node)
                        {   _node = ptr;  ptr = ptr->parent;    }
                        _node = ptr;
                    }
                    return *this;
                }

                treeIterator&		operator -- ()
                {
                    if (!_node)
                    {
                        _node = _tree->_root;
                        while (_node->right)  _node = _node->right;
                        return *this;
                    }
                    if (_node->left)
                    {
                        _node = _node->left;
                        while (_node->right)  _node = _node->right;
                    }
                    else
                    {
                        treeNode	*ptr = _node->parent;
                        while (ptr && ptr->left == _node)
                        {   _node = ptr;  ptr = ptr->parent;    }
                        _node = ptr;
                    }
                    return *this;
                }
                treeIterator		operator ++ ( int )							{   treeIterator ptr(*this); operator++(); return ptr;  }
                treeIterator		operator -- ( int )							{   treeIterator ptr(*this); operator--(); return ptr;  }

                bool			    operator == ( treeIterator const& t )	const	{   return _node == t._node;    }
                bool			    operator != ( treeIterator const& t )	const	{   return _node != t._node;    }

                operator            const_iterator () const						    {   return const_iterator(_node, _tree);    }
        };

        // iterators
        iterator				begin(void)
        {
            if (!_root)        return iterator(NULL, this);
            treeNode* first = _root;
            while (first->left) first = first->left;
            return iterator(first, this);
        }
        const_iterator			begin() const
        {
            if (!_root)        return const_iterator(NULL, this);
            treeNode* first = _root;
            while (first->left) first = first->left;
            return const_iterator(first, this);
        }
        iterator				end()				{       return iterator(NULL, this);                }
        const_iterator			end() const			{       return const_iterator(NULL, this);          }
        reverse_iterator		rbegin()			{       return reverse_iterator(end());             }
        const_reverse_iterator	rbegin() const		{       return const_reverse_iterator(end());       }
        reverse_iterator		rend()				{       return reverse_iterator(begin());           }
        const_reverse_iterator	rend() const		{       return const_reverse_iterator(begin());     }

};

#endif

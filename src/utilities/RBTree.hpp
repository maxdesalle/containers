/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:47:47 by mlazzare          #+#    #+#             */
/*   Updated: 2022/03/23 09:35:10 by mlazzare         ###   ########.fr       */
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
struct treeNode {
    T           *value;
	treeNode    *parent, *left, *right;
	bool        color;

    treeNode( void )    :   value( nullptr ),
                            parent (0), left(0), right(0),
                            color( BLACK ) {};
    treeNode( T  *value )   :  value(value),
                                parent (0), left(0), right(0),
                                color( BLACK ) {};
    treeNode( treeNode const& t )   :   value(t.value),
                                        parent (t.parent), left(t.left), right(t.right),
                                        color( t.color ) {};
    treeNode const&     operator = ( treeNode const& t )
    {
        this->value = t.value;
        this->parent = t.parent;
        this->left = t.left;
        this->right = t.right;
        this->color = t.color;
        return *this;
    }
    ~treeNode ();
};

template <typename T, typename Compare, typename Alloc = std::allocator<T> >
class RBTree
{
    public:
    // VAR TYPES
        template <class U>
        class	treeIterator;

        typedef T												        value_type;
        typedef Alloc   										        allocator_type;             // container allocator
        typedef typename allocator_type::pointer				        pointer;
        typedef typename allocator_type::const_pointer			        const_pointer;
        typedef typename allocator_type::reference				        reference;
        typedef typename allocator_type::const_reference		        const_reference;
        typedef treeIterator< T >									    iterator;
        typedef treeIterator< const T >								    const_iterator;
        typedef ft::reverse_iterator< iterator >				        reverse_iterator;
        typedef ft::reverse_iterator< const_iterator >			        const_reverse_iterator;
        typedef std::size_t										        size_type;
        typedef treeNode< value_type >                                  node;
        typedef typename allocator_type::template rebind< node >::other	node_allocator;             // container's element allocator 
    
    private:
        // TREE ELEMENTS
        node                    *_root;
        size_type               _height;
        Compare                 _comp;
        node_allocator          _node_alloc;

    public:
        // CONSTRUCTORS
        RBTree( Compare const &comp = Compare(), Alloc const &alloc = allocator_type() ) :  _root(nullptr),
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

        ~RBTree(void) { clear(_root); };

        // INSERT, DEL, CLEAR, SEARCH ELEMS
        ft::pair< iterator, bool>    insert( value_type pair )
        {
            node *curr = _root;
            if (!curr)  curr = new node( pair );
            else
            {
                while (curr)
                {
                    if (_comp(pair.first, curr->value.first))   curr = curr->left;
                    else                                        curr = curr->right;
                }
                if (_comp(pair.first, curr->value.first))       curr->left = new node( pair );
                else                                            curr->right = new node( pair );
            }
            // balanceTree(); TO DO
            _height++;
            return ft::make_pair(iterator(curr, this), true);
        };

		// [INSERT] : still TO DO
        //treeIterator 				insert(treeIterator position, const value_type& value)
		//void insert (InputIterator first, InputIterator last)

        void 					erase( iterator position )							//{	_tree.erase( get_nodeptr(position) );		};
        {
            (void)position;
        //     try
        //     {
        //         node *curr = _root;
        //         if (!curr)  curr = new node( pair );
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
        //                 curr->left = new node( pair );
        //             else
        //                 curr->right = new node( pair );
        //         }
                    
        //     }
        //     catch( const RBTree::KeyNotFound & e )    {   std::cerr << e.what() << '\n';  }            
        }
        
		// size_type 				erase(const key_type& k)							{	_tree.erase( k );				};

		// void 					erase(treeIterator first, treeIterator last)				{	_tree.erase( first, last );		};

        // FIND


        // CLEAR
        void        delNode(node *node)        {    _node_alloc.destroy(node);  _node_alloc.deallocate(node, 1);  --_height;      }
        void        clear(node *root)
        {
            if (!root)
                return ;
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
                typedef treeNode< value_type >          node;

            private:
                node*			    _node;
                const RBTree*	    _tree;

            public:
                treeIterator( void ) :  _node(NULL),
                                        _tree(NULL) {};
                treeIterator( node* current, const RBTree *tree ) : _node(current),
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
                pointer			operator->()							{   return _node->value;   }
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
                        node	*ptr = _node->parent;
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
                        node	*ptr = _node->parent;
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
            node*	first;

            if (!_root)
                return iterator(NULL, this);
            first = _root;
            while (first->left)
                first = first->left;
            return iterator(first, this);
        }
        const_iterator			begin() const
        {
            node*	first;

            if (!_root)
                return const_iterator(NULL, this);
            first = _root;
            while (first->left)
                first = first->left;
            return const_iterator(first, this);
        }
        iterator				end()				{ return iterator(NULL, this); }
        const_iterator			end() const			{ return const_iterator(NULL, this); }
        reverse_iterator		rbegin()			{ return reverse_iterator(end()); }
        const_reverse_iterator	rbegin() const		{ return const_reverse_iterator(end()); }
        reverse_iterator		rend()				{ return reverse_iterator(begin()); }
        const_reverse_iterator	rend() const		{ return const_reverse_iterator(begin()); }



};

#endif

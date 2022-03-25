/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:47:47 by mlazzare          #+#    #+#             */
/*   Updated: 2022/03/25 11:02:07 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <iostream>
# include <memory> // std::allocator
# include <cmath>

# include "type_traits.hpp"
# include "iterator.hpp"
# include "RBTree_iterator.hpp"
# include "algorithm.hpp"
# include "pair.hpp"

template < class T, class Compare = std::less< T >, class Alloc = std::allocator<T> >
class RBTree
{
    public:
    // VAR TYPES
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

        // [INSERT] ( + addNode() )
        treeNode                    *newNode( value_type const& pair, treeNode *parent )
        {
            treeNode    *newnode = _node_alloc.allocate(1);
            _node_alloc.construct(&(newnode->value), pair);
            newnode->left = nullptr;
            newnode->right = nullptr;
            newnode->parent = parent;
            newnode->color = BLACK;
            _height++;
			return newnode;

        };

        ft::pair< iterator, bool>    insert( value_type const& pair )
        {
                        // printf("begin\n");
            if (!_root) { _root = newNode( pair, nullptr ); return ft::make_pair(iterator(_root), true); }
            treeNode *curr = _root;
            treeNode *parent;
            while (curr)
            {
                printf("curr\n");
                parent = curr;
                if (_comp(pair, curr->value))   {curr = curr->left; printf("left\n");}
                else                            {curr = curr->right; printf("right\n");}
            }
            curr = newNode( pair, parent );
            if (_comp(pair, parent->value))       {     parent->left = curr;          }
            else                                  {     parent->right = curr;          }
            // balanceTree(); TO DO
            return ft::make_pair(iterator(curr), true);
        };

        iterator 				insert(iterator position, const value_type& value)      {       return insert(value).first; (void)position;         }
		
        template <class InputIterator>
	    void					insert(InputIterator first, InputIterator last)	        {       while (first != last)   insert(*first++);           };

        // [ERASE]
         size_type 				erase(treeNode *node)
        {
            try
            {
                (void)node;
                return 1;
            }
            catch( const RBTree::KeyNotFound & e )    {   std::cerr << e.what() << '\n'; return 0;  }       
        };
		void 					erase(iterator first, iterator last)                    {	while (first != last)   erase(*first++); 	        };

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

        // iterators
        iterator				begin( void )
        {
            if (!_root)        return iterator(nullptr);
            treeNode* first = _root;
            while (first->left) first = first->left;
            return iterator(first);
        }
        const_iterator			begin( void ) const
        {
            if (!_root)        return const_iterator(nullptr);
            treeNode* first = _root;
            while (first->left) first = first->left;
            return const_iterator(first);
        }
        iterator				end()				{       return iterator(max(_root));                         }
        const_iterator			end() const			{       return const_iterator(max(_root));                   }
        reverse_iterator		rbegin()			{       return reverse_iterator(end());                 }
        const_reverse_iterator	rbegin() const		{       return const_reverse_iterator(end());           }
        reverse_iterator		rend()				{       return reverse_iterator(begin());               }
        const_reverse_iterator	rend() const		{       return const_reverse_iterator(begin());         }

        // min, max

        treeNode    *min(treeNode*_root) const      {       while (_root)   { _root = _root->left; }  return _root;         };
        treeNode    *max(treeNode*_root) const      {       while (_root)   { _root = _root->right; }  return _root;        };

        void inorder(treeNode*_root) {
        if (_root != NULL) {
            inorder(_root->left);
        std::cout<<_root->value.second <<" ";
        inorder(_root->right);           }};

        treeNode    *get_root()         { return _root;     };
};

#endif

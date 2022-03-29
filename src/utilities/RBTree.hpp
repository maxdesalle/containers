/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:47:47 by mlazzare          #+#    #+#             */
/*   Updated: 2022/03/29 07:07:04 by mlazzare         ###   ########.fr       */
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

        // [INSERT] ( + newNode() )
        treeNode                    *newNode( value_type const& pair, treeNode *parent )
        {
            treeNode    *newnode = _node_alloc.allocate(1);
            _node_alloc.construct(&(newnode->value), pair);
            newnode->left = newnode->right = nullptr;
            newnode->parent = parent;
            newnode->color = RED;
            _height++;
			return newnode;

        };

        ft::pair< iterator, bool>    insert( value_type const& pair )
        {
            if (!_root) { _root = newNode( pair, nullptr ); _root->color = BLACK; return ft::make_pair(iterator(_root), true); }
            treeNode *curr = _root;
            treeNode *parent;
            while (curr)
            {
                printf("here\n");
                parent = curr;
                if (_comp(pair, curr->value))           {       curr = curr->left;             }
                else if (_comp(curr->value, pair))      {       curr = curr->right;            }
                else                                    ft::make_pair(iterator(curr), false);                          
            }
            curr = newNode( pair, parent );
            if (_comp(pair, parent->value))             {     parent->left = curr;           }
            else                                        {     parent->right = curr;          }
            rebalanceTree4insert(curr);
            return ft::make_pair(iterator(curr), true);
        };

        iterator 				insert(iterator position, const value_type& value)      {       return insert(value).first; (void)position;         }
		
        template <class InputIterator>
	    void					insert(InputIterator first, InputIterator last)	        {       while (first != last)   insert(*first++);           };

        // [ERASE] ( + delNode() )
        size_type 				erase(treeNode *node)
        {
            if (find(node)) //find(node)
            {
                bool originColor = node->color;
                if (node->left == nullptr)
                {
                    treeNode    *tmp = node->right;
                    transplantNode(node, tmp);
                }
                else if (node->right == nullptr)
                {
                    treeNode    *tmp = node->left;
                    transplantNode(node, tmp);
                }
                else
                {
                    treeNode    *tmp = min(node->right); //min
                    originColor = tmp->color;
                    treeNode    *sibling = tmp->right;
                    if (tmp->parent == node) sibling->parent = tmp;
                    else
                    {
                        transplantNode(tmp, tmp->right);
                        tmp->right = node->right;
                        tmp->right->parent = tmp;
                    }
                    transplantNode(node, tmp);
                    tmp->left = node->left;
                    tmp->left->parent = tmp;
                    tmp->color = node->color;
                }
                delNode(node);
                if (originColor == BLACK)
                    rebalanceTree4erase(node);
                --_height;
            }                                         {         delNode(node); rebalanceTree4erase(node); return 1;              }
            throw RBTree::KeyNotFound ();           return 0;
        };
		void 					erase(iterator first, iterator last)                    {	while (first != last)   erase(*first++); 	        };

        // FIND
        treeNode                *find(const value_type &val)
        {
            while (_root) 
	    {
		    if (_comp(val, _root->value))              	_root = _root->left;
		    else if (_comp(_root->value, val))         	_root = _root->right;
            	    else					return _root;
	    }
	    return nullptr;
        }

        // CLEAR
        void        delNode(treeNode *node)        {   if (!node) return ; _node_alloc.destroy(node);  _node_alloc.deallocate(node, 1);  --_height;     }
        // clear the tree in postorder trasversal (left, right, root)
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

        treeNode    *min(treeNode* node) const      {       while (node->left)   { node = node->left; }  return node;         };
        treeNode    *max(treeNode* node) const      {       while (node->right)   { node = node->right; }  return node;        };

        void inorder(treeNode*_root)
        {
            if (_root)
            {
                inorder(_root->left);
                std::cout<<_root->value.second <<" ";
                inorder(_root->right);          
            }
        };

        void    leftRotate(treeNode    *node)
        {
            treeNode    *tmp = node->right;
            node->right = tmp->left;
            if (tmp->left)
                tmp->left->parent = node;
            tmp->parent = node->parent;
            if (node->parent == nullptr)
                _root = tmp;
            else if (node == node->parent->left)
                node->parent->left = tmp;
            else
                node->parent->right = tmp;
            tmp->left = node;
            node->parent = tmp;
        }

        void    rightRotate(treeNode *node)
        {
            treeNode    *tmp = node->left;
            node->left = tmp->right;
            if (tmp->right)
                tmp->right->parent = node;
            tmp->parent = node->parent;
            if (node->parent == nullptr)
                _root = tmp;
            else if (node == node->parent->right)
                node->parent->right = tmp;
            else
                node->parent->left = tmp;
            tmp->right = node;
            node->parent = tmp;
        }
        
        void        recolorNode(treeNode *node)                     {          node->color == RED ? node->color = BLACK : node->color = RED;                        };
        void        transplantNode(treeNode *a, treeNode *b)
        {
            if (a->parent == nullptr)       _root = b;
            else if (a == a->parent->left)  a->parent->left = b;
            else                            a->parent->right = b;
            b->parent   = a->parent;
        };
        // find first node which has no left child
        treeNode    *successor(treeNode *n)                             {          treeNode *tmp = n; while (tmp->left != NULL) tmp = tmp->left;   return tmp;          };
  
        void    rebalanceTree4insert(treeNode *node)
        {
            while (node != _root && node->parent->color == RED)
            {
                treeNode    *grandmaNode = node->parent->parent;
                if (grandmaNode && node->parent == grandmaNode->right)
                {
                    treeNode    *uncleNode = grandmaNode->left;
                    if (uncleNode->color == RED)
                    {
                        recolorNode(uncleNode); // BLACK
                        recolorNode(node->parent); // BLACK
                        recolorNode(grandmaNode); // RED
                        node = grandmaNode;
                    }
                    else
                    {
                        if (node == node->parent->left)
                        {
                            node = node->parent;
                            rightRotate(node);
                        }
                        if (node->parent->color != BLACK)
                            recolorNode(node->parent);
                        if (grandmaNode->color != RED)
                            recolorNode(grandmaNode);
                        leftRotate(grandmaNode);
                    }
                }
                else
                {
                    treeNode    *uncleNode = node->parent->parent->right;
                    if (uncleNode->color == RED)
                    {
                        recolorNode(uncleNode);
                        recolorNode(node->parent);
                        recolorNode(grandmaNode);
                        node = grandmaNode;
                    }
                    else
                    {
                        if (node == node->parent->right)
                        {
                            node = node->parent;
                            leftRotate(node);
                        }
                        if (node->parent->color != BLACK)
                            recolorNode(node->parent);
                        if (grandmaNode->color != RED)
                            recolorNode(grandmaNode);
                        rightRotate(grandmaNode);
                    }
                }                
            }
            _root->color = BLACK;
        };

        void    rebalanceTree4erase(treeNode *node)
        {
            while (node != _root && node->color == BLACK)
            {
                if( node == node->parent->left)
                {
                    treeNode *sibling = node->parent->right;
                    if (sibling->color == RED)
                    {
                        recolorNode(sibling);
                        recolorNode(node->parent);
                        leftRotate(node->parent);
                        sibling = node->parent->right;
                        if (sibling->left->color == BLACK && sibling->right->color == BLACK)
                        {
                            recolorNode(sibling);
                            node = node->parent;
                        }
                        else
                        {
                            if (sibling->right->color == BLACK)
                            {
                                sibling->left->color = BLACK;
                                recolorNode(sibling);
                                rightRotate(sibling);
                                sibling = sibling->parent->right;
                            }
                            sibling->color = node->parent->color;
                            node->parent->color = BLACK;
                            sibling->right->color = BLACK;
                            leftRotate(node->parent);
                            node = _root;
                        }
                    }
                }
                else
                {
                    treeNode *sibling = node->parent->left;
                    if (sibling->color == RED)
                    {
                        recolorNode(sibling);
                        node->parent->color = RED;
                        rightRotate(node->parent);
                        sibling = node->parent->left;
                        if (sibling->right->color == BLACK && sibling->left->color == BLACK)
                        {
                            recolorNode(sibling);
                            node = node->parent;
                        }
                        else 
                        {
                            if (sibling->left->color == BLACK)
                            {
                                sibling->right->color = BLACK;
                                recolorNode(sibling); // RED
                                leftRotate(sibling);
                                sibling = sibling->parent->left;
                            }
                            sibling->color = node->parent->left;
                            node->parent->color = BLACK;
                            sibling->left->color = BLACK;
                            rightRotate(node->parent);
                            node = _root;
                        }
                    }
                }
            }
            node->color = BLACK;
        }

        treeNode    *get_root()                             {           return _root;     };
};

#endif

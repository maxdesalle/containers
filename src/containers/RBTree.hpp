/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:47:47 by mlazzare          #+#    #+#             */
/*   Updated: 2022/03/19 10:43:14 by mlazzare         ###   ########.fr       */
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

enum nodeColor {    RED, BLACK   };

template < typename T >
struct treeNode {
	treeNode    *parent, *left, *right;
    T           *val;
	bool        color;

    treeNode(T  *value):    val(value),
                            parent (0), left(0), right(0),
                            color(RED) {};
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

        // ADD, DEL, CLEAR ELEMS

        nodeTree    *addNode( value_type p )
        {
            
        }

       // initializes the nodes with appropirate values
        // all the pointers are set to point to the null pointer
        void initializeNULLNode(treeNode node, treeNode parent) {
            node->val = 0;
            node->parent = parent;
            node->left = nullptr;
            node->right = nullptr;
            node->color = 0;
        }

        void preOrderHelper(treeNode node) {
            if (node != TNULL) {
                cout<<node->val<<" ";
                preOrderHelper(node->left);
                preOrderHelper(node->right);
            } 
        }

        void inOrderHelper(treeNode node) {
            if (node != TNULL) {
                inOrderHelper(node->left);
                cout<<node->val<<" ";
                inOrderHelper(node->right);
            } 
        }

        void postOrderHelper(treeNode node) {
            if (node != TNULL) {
                postOrderHelper(node->left);
                postOrderHelper(node->right);
                cout<<node->val<<" ";
            } 
        }

        treeNode searchTreeHelper(treeNode node, int val) {
            if (node == TNULL || val == node->val) {
                return node;
            }

            if (val < node->val) {
                return searchTreeHelper(node->left, val);
            } 
            return searchTreeHelper(node->right, val);
        }

        // fix the rb tree modified by the delete operation
        void fixDelete(treeNode x) {
            treeNode s;
            while (x != root && x->color == 0) {
                if (x == x->parent->left) {
                    s = x->parent->right;
                    if (s->color == 1) {
                        // case 3.1
                        s->color = 0;
                        x->parent->color = 1;
                        leftRotate(x->parent);
                        s = x->parent->right;
                    }

                    if (s->left->color == 0 && s->right->color == 0) {
                        // case 3.2
                        s->color = 1;
                        x = x->parent;
                    } else {
                        if (s->right->color == 0) {
                            // case 3.3
                            s->left->color = 0;
                            s->color = 1;
                            rightRotate(s);
                            s = x->parent->right;
                        } 

                        // case 3.4
                        s->color = x->parent->color;
                        x->parent->color = 0;
                        s->right->color = 0;
                        leftRotate(x->parent);
                        x = root;
                    }
                } else {
                    s = x->parent->left;
                    if (s->color == 1) {
                        // case 3.1
                        s->color = 0;
                        x->parent->color = 1;
                        rightRotate(x->parent);
                        s = x->parent->left;
                    }

                    if (s->right->color == 0 && s->right->color == 0) {
                        // case 3.2
                        s->color = 1;
                        x = x->parent;
                    } else {
                        if (s->left->color == 0) {
                            // case 3.3
                            s->right->color = 0;
                            s->color = 1;
                            leftRotate(s);
                            s = x->parent->left;
                        } 

                        // case 3.4
                        s->color = x->parent->color;
                        x->parent->color = 0;
                        s->left->color = 0;
                        rightRotate(x->parent);
                        x = root;
                    }
                } 
            }
            x->color = 0;
        }


        void rbTransplant(treeNode u, treeNode v){
            if (u->parent == nullptr) {
                root = v;
            } else if (u == u->parent->left){
                u->parent->left = v;
            } else {
                u->parent->right = v;
            }
            v->parent = u->parent;
        }

        void deleteNodeHelper(treeNode node, int val) {
            // find the node containing val
            treeNode z = TNULL;
            treeNode x, y;
            while (node != TNULL){
                if (node->val == val) {
                    z = node;
                }

                if (node->val <= val) {
                    node = node->right;
                } else {
                    node = node->left;
                }
            }

            if (z == TNULL) {
                cout<<"Couldn't find val in the tree"<<endl;
                return;
            } 

            y = z;
            int y_original_color = y->color;
            if (z->left == TNULL) {
                x = z->right;
                rbTransplant(z, z->right);
            } else if (z->right == TNULL) {
                x = z->left;
                rbTransplant(z, z->left);
            } else {
                y = minimum(z->right);
                y_original_color = y->color;
                x = y->right;
                if (y->parent == z) {
                    x->parent = y;
                } else {
                    rbTransplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }

                rbTransplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
            delete z;
            if (y_original_color == 0){
                fixDelete(x);
            }
        }
        
        // fix the red-black tree
        void fixInsert(treeNode k){
            treeNode u;
            while (k->parent->color == 1) {
                if (k->parent == k->parent->parent->right) {
                    u = k->parent->parent->left; // uncle
                    if (u->color == 1) {
                        // case 3.1
                        u->color = 0;
                        k->parent->color = 0;
                        k->parent->parent->color = 1;
                        k = k->parent->parent;
                    } else {
                        if (k == k->parent->left) {
                            // case 3.2.2
                            k = k->parent;
                            rightRotate(k);
                        }
                        // case 3.2.1
                        k->parent->color = 0;
                        k->parent->parent->color = 1;
                        leftRotate(k->parent->parent);
                    }
                } else {
                    u = k->parent->parent->right; // uncle

                    if (u->color == 1) {
                        // mirror case 3.1
                        u->color = 0;
                        k->parent->color = 0;
                        k->parent->parent->color = 1;
                        k = k->parent->parent;	
                    } else {
                        if (k == k->parent->right) {
                            // mirror case 3.2.2
                            k = k->parent;
                            leftRotate(k);
                        }
                        // mirror case 3.2.1
                        k->parent->color = 0;
                        k->parent->parent->color = 1;
                        rightRotate(k->parent->parent);
                    }
                }
                if (k == root) {
                    break;
                }
            }
            root->color = 0;
        }

        void printHelper(treeNode root, string indent, bool last) {
            // print the tree structure on the screen
            if (root != TNULL) {
            cout<<indent;
            if (last) {
                cout<<"R----";
                indent += "     ";
            } else {
                cout<<"L----";
                indent += "|    ";
            }
                
            string sColor = root->color?"RED":"BLACK";
            cout<<root->val<<"("<<sColor<<")"<<endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
            }
            // cout<<root->left->val<<endl;
        }

    public:
        RBTree() {
            TNULL = new Node;
            TNULL->color = 0;
            TNULL->left = nullptr;
            TNULL->right = nullptr;
            root = TNULL;
        }

        // Pre-Order traversal
        // Node->Left Subtree->Right Subtree
        void preorder() {
            preOrderHelper(this->root);
        }

        // In-Order traversal
        // Left Subtree -> Node -> Right Subtree
        void inorder() {
            inOrderHelper(this->root);
        }

        // Post-Order traversal
        // Left Subtree -> Right Subtree -> Node
        void postorder() {
            postOrderHelper(this->root);
        }

        // search the tree for the val k
        // and return the corresponding node
        treeNode searchTree(int k) {
            return searchTreeHelper(this->root, k);
        }

        // find the node with the minimum val
        treeNode minimum(treeNode node) {
            while (node->left != TNULL) {
                node = node->left;
            }
            return node;
        }

        // find the node with the maximum val
        treeNode maximum(treeNode node) {
            while (node->right != TNULL) {
                node = node->right;
            }
            return node;
        }

        // find the successor of a given node
        treeNode successor(treeNode x) {
            // if the right subtree is not null,
            // the successor is the leftmost node in the
            // right subtree
            if (x->right != TNULL) {
                return minimum(x->right);
            }

            // else it is the lowest ancestor of x whose
            // left child is also an ancestor of x.
            treeNode y = x->parent;
            while (y != TNULL && x == y->right) {
                x = y;
                y = y->parent;
            }
            return y;
        }

        // find the predecessor of a given node
        treeNode predecessor(treeNode x) {
            // if the left subtree is not null,
            // the predecessor is the rightmost node in the 
            // left subtree
            if (x->left != TNULL) {
                return maximum(x->left);
            }

            treeNode y = x->parent;
            while (y != TNULL && x == y->left) {
                x = y;
                y = y->parent;
            }

            return y;
        }

        // rotate left at node x
        void leftRotate(treeNode x) {
            treeNode y = x->right;
            x->right = y->left;
            if (y->left != TNULL) {
                y->left->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == nullptr) {
                this->root = y;
            } else if (x == x->parent->left) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }
            y->left = x;
            x->parent = y;
        }

        // rotate right at node x
        void rightRotate(treeNode x) {
            treeNode y = x->left;
            x->left = y->right;
            if (y->right != TNULL) {
                y->right->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == nullptr) {
                this->root = y;
            } else if (x == x->parent->right) {
                x->parent->right = y;
            } else {
                x->parent->left = y;
            }
            y->right = x;
            x->parent = y;
        }

        // insert the val to the tree in its appropriate position
        // and fix the tree
        void insert(int val) {
            // Ordinary Binary Search Insertion
            treeNode node = new Node;
            node->parent = nullptr;
            node->val = val;
            node->left = TNULL;
            node->right = TNULL;
            node->color = 1; // new node must be red

            treeNode y = nullptr;
            treeNode x = this->root;

            while (x != TNULL) {
                y = x;
                if (node->val < x->val) {
                    x = x->left;
                } else {
                    x = x->right;
                }
            }

            // y is parent of x
            node->parent = y;
            if (y == nullptr) {
                root = node;
            } else if (node->val < y->val) {
                y->left = node;
            } else {
                y->right = node;
            }

            // if new node is a root node, simply return
            if (node->parent == nullptr){
                node->color = 0;
                return;
            }

            // if the grandparent is null, simply return
            if (node->parent->parent == nullptr) {
                return;
            }

            // Fix the tree
            fixInsert(node);
        }

        treeNode getRoot(){     return this->root;      }

        // delete the node from the tree
        void deleteNode(int val) {
            deleteNodeHelper(this->root, val);
        }

        // print the tree structure on the screen
        void prettyPrint() {
            if (root) {
                printHelper(this->root, "", true);
            }
        }

        bool    empty( void )   {   return !root;      };
        size_t  size( void )    {   return height;    };

};

#endif RBTREE_HPP

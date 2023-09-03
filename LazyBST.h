// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: Lazy Balanced Trees - LazyLazyBST.h class
#ifndef LazyBST_H
#define LazyBST_H

#include "TreeNodePA5.h"
#include <iostream>

// LazyBST header class from classwork Notion

template <typename T>
class LazyBST{
    public:
        // LECTURE 17
        LazyBST();
        virtual ~LazyBST();
        bool iterContains(T d);
        bool contains(T d); // recursive version that uses recContainsHelper
        void printInOrder(); // least to greatest
        void printTreePostOrder(); // left tree (from left leaf, right leaf, subtreeroot) then right tree (same) then root last
        // LECTURE 18
        void insert(T d); // insert T data to tree
        int size(); // number of nodes in tree
        // ^ getter bc m_size is private
        T max(); // right most child leaf node
        T min(); // left most child leaf node
        T median(); // root node as long as tree is balanced, else it will be off
        // LECTURE 19
        void remove(T d); // dont return bc we alr know the data to remove which is d
        bool isBalanced(TreeNode<T>*& subTreeRoot);
        int getHeight(TreeNode<T>*& node);
        void createSortedArray(TreeNode<T>*& subTreeRoot, T* arr); // creates sorted array of unbalanced BST
        TreeNode<T>* createBalancedBST(T* arr, int start, int end); // rebalances BST using createSortedArray
        T& getObject(T d); // returns object without removing it

    private:
        int idx;

        // LECTURE 17
        TreeNode<T>* m_root;
        int m_size;
        bool recContainsHelper(TreeNode<T>* n, T d);
        void printIOHelper(TreeNode<T>* n);
        // ^ helper method to make root node available
        void printTreePostOrderHelper(TreeNode<T>* subTreeRoot);
        // LECTURE 18
        void insertHelper(TreeNode<T>*& subTreeRoot, T& d);
        // ^ use & to take in subTreeRoot by reference bc we know a pointer is a mem address,
        // if we take in as a pointer (w/o &) into insertHelper we create a copy of the int val
        T getMaxHelper(TreeNode<T>* n);
        T getMinHelper(TreeNode<T>* n);
        void findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent);
        TreeNode<T>* getSuccessor(TreeNode<T>* rightChild);
        void RecursiveDestroy(TreeNode<T>*& subTreeRoot);

};

    // ***************************************************************** //
    // ****************** LECTURE  17 ********************************** //
    // ***************************************************************** //

   template <typename T>
        LazyBST<T>::LazyBST(){
        m_root = NULL;
        m_size = 0;
    }

    template <typename T>
    LazyBST<T>::~LazyBST(){
        RecursiveDestroy(m_root);
    }

    /*
    a. RecursiveDestroy method
    b. returns void
    c. takes in TreeNode<T>*& subTreeRoot
    d. no known exeptions thrown
    */
    template <typename T>
    void LazyBST<T>::RecursiveDestroy(TreeNode<T>*& subTreeRoot){
      if(subTreeRoot != NULL){
        RecursiveDestroy(subTreeRoot->m_left);
        RecursiveDestroy(subTreeRoot->m_right);
        delete subTreeRoot;
      }
    }

    template <typename T>
    bool LazyBST<T>::iterContains(T d){
        if (m_root == NULL){ // tree is empty
            return false;
        }
        if (m_root -> m_data == d){ // root is the key d
            return true;
        }

        // look for d
        bool found = false;
        TreeNode<T>* current = m_root;
        // current is the new "root" of a tree, i.e. after actual root is checked it makes the L or R child
        // the new root of a subtree
        while (!found){
            // check if d is greater than current go right
            if (d > current -> m_data){
                current = current -> m_right;
            } else { // if d is less than/ == current go left
                current = current -> m_left;
            }
            // check if current node is NULL -> we've reached a leaf and d was not found
            if (current == NULL){
                found =  false;
                break;
            }

            // check if the current node's data is d -> we found d
            if (current -> m_data == d){
                found = true;
            }
        }
        return found;
    }

    /*
    a. getObject method
    b. returns T& reference object
    c. takes in T data
    d. no known exeptions thrown
    */
    template <typename T>
    T& LazyBST<T>::getObject(T d) {
      TreeNode<T>* current = m_root;
      while (current != NULL) {
        if (current->m_data == d) {
            return current->m_data;
        } else if (d < current->m_data) {
            current = current->m_left;
        } else {
            current = current->m_right;
        }
      }
      // If we reach this point, we didn't find node with data d
    }

    // RECURSIVE CONTAINS
    template <typename T>
    bool LazyBST<T>::contains(T d){
        return recContainsHelper(m_root, d);
    }

    // RECURSIVE CONTAINS HELPER
    template <typename T>
    bool LazyBST<T>::recContainsHelper(TreeNode<T>* n, T d){
        if (n == NULL){ // if it is null then d is not in tree
            return false;
        }
        if (n -> m_data == d) { // if it is not null, is it here?
            return true;
        }
        if (d > n -> m_data){ // it's not null but it's also not here, check if it is > or <
            return recContainsHelper( n -> m_right, d);
        } else {
            return recContainsHelper( n -> m_left, d);
        }
    }

    template <typename T>
    void LazyBST<T>::printInOrder(){
        printIOHelper(m_root);
    }

    template <typename T>
    void LazyBST<T>::printIOHelper(TreeNode<T>* n){
        if (n != NULL){ // is the node null?
            printIOHelper(n -> m_left); // if not then print the left thing
            n->m_data.printInfo(); // then print the key of the curr node
            printIOHelper(n -> m_right); // then print the right thing
        }
    }

    template <typename T>
    void LazyBST<T>::printTreePostOrder(){
        printTreePostOrderHelper(m_root);
    }

    template <typename T>
    void LazyBST<T>::printTreePostOrderHelper(TreeNode<T>* subTreeRoot){
        if(subTreeRoot != NULL){
            printTreePostOrderHelper(subTreeRoot->m_left);
            printTreePostOrderHelper(subTreeRoot->m_right);
            subTreeRoot->m_data.printInfo();
        }
    }

    // ***************************************************************** //
    // ****************** LECTURE  18 ********************************** //
    // ***************************************************************** //

    template <typename T>
    void LazyBST<T>::insert(T d){
        insertHelper(m_root, d);
        if(!isBalanced(m_root)){
          // then we need to resize and make a new BST from scratch
          // step 1: add N values to array of size N in ascending order
          int numValues = size() + 1;
          T *arr = new T[numValues];
          idx = 0;
          // call method to create sorted array
          createSortedArray(m_root, arr);
          // call method to add sorted array to new balanced bst
          m_root = createBalancedBST(arr, 0, numValues-1);
        }
        ++ m_size;
    }

    template <typename T>
    void LazyBST<T>::insertHelper(TreeNode<T>*& subTreeRoot, T& d){
        if (subTreeRoot == NULL){ // tree empty
          subTreeRoot = new TreeNode<T>(d);
        }
        else if (d > subTreeRoot -> m_data){
          insertHelper(subTreeRoot -> m_right, d);

        } else { // d < or = to subTreeRoot -> m_data
          // usually repeated data isnt allowed but sometimes it's used
          // if repeats are allowed, keep consistent (== data is either always inserted left or right ONLY)
          // in this case we are inserting == data to the left of subTreeRoot
          insertHelper(subTreeRoot -> m_left, d);

        }
    }


    /*
    a. createSortedArray method
    b. no return
    c. takes in TreeNode<T>*& subTreeRoot, T* arr
    d. no known exeptions thrown
    */
    template <typename T>
    void LazyBST<T>::createSortedArray(TreeNode<T>*& subTreeRoot, T* arr){
      if (subTreeRoot == NULL){
        return;
      }
      createSortedArray(subTreeRoot -> m_left, arr);
      arr[idx++] = subTreeRoot -> m_data; // add to array
      createSortedArray(subTreeRoot -> m_right, arr);
    }

    /*
    a. createBalancedBST method
    b. returns pointer to TreeNode
    c. takes in T* arr, int start, int end
    d. no known exeptions thrown
    */
    template <typename T>
    TreeNode<T>* LazyBST<T>::createBalancedBST(T* arr, int start, int end){
      if (start > end){
        return NULL;
      }
      // step 2: get medianIdx and insert value at that idx as root of tree
      int median = (start + end) / 2; // get median
      TreeNode<T>* node = new TreeNode<T>(arr[median]); // create new root node

      // step 3: median value of everything less than the root/leaf is chosen and inserted as the root’s/leaf’s left child
      node->m_left = createBalancedBST(arr, start, median - 1);

      // step 4: median value of everything greater than the root/leaf is chosen and inserted as the root’s/leaf’s right child
      node->m_right = createBalancedBST(arr, median + 1, end);

      return node;
    }

    /*
    a. isBalanced method
    b. returns a bool
    c. takes in TreeNode<T>*& subTreeRoot
    d. no known exeptions thrown
    */
    template <typename T>
    bool LazyBST<T>::isBalanced(TreeNode<T>*& subTreeRoot){
      if (subTreeRoot == NULL) {
          return true;
      }
      int leftHeight = getHeight(subTreeRoot->m_left);
      int rightHeight = getHeight(subTreeRoot->m_right);

      if (abs(leftHeight - rightHeight) > 1){
        return false;
      }
      return isBalanced(subTreeRoot->m_left) && isBalanced(subTreeRoot->m_right);
    }

    /*
    a. getHeight method
    b. returns an int
    c. takes in TreeNode<T>*& node
    d. no known exeptions thrown
    */
    template <typename T>
    int LazyBST<T>::getHeight(TreeNode<T>*& node){
      if (node == nullptr) {
        return 0;
      }
      int leftHeight = getHeight(node->m_left);
      int rightHeight = getHeight(node->m_right);
      return 1 + std::max(leftHeight, rightHeight);
    }


// HELPER METHODS
    template <typename T>
    T LazyBST<T>::max(){
      getMaxHelper(m_root);
    }

    template <typename T>
    T LazyBST<T>::getMaxHelper(TreeNode<T>* n){
      // get to the right most node
      if (n -> m_right == NULL){
        // we found rightmost node
        return n -> m_data;
      } else {
        // keep looking at right children
        return getMaxHelper(n -> m_right);
      }
    }

    template <typename T>
    T LazyBST<T>::min(){
      getMinHelper(m_root);
    }

    template <typename T>
    T LazyBST<T>::getMinHelper(TreeNode<T>* n){
      if (n -> m_left == NULL){
        // we found leftmost node
        return n -> m_data;
      } else {
        // keep looking at left children
        return getMinHelper(n -> m_left);
      }
    }

    template <typename T>
    T LazyBST<T>::median(){
      // assume it's a non empty tree
      return m_root -> m_data;
    }

    template <typename T>
    int LazyBST<T>::size(){
      return m_size;
    }

    // ***************************************************************** //
    // ****************** LECTURE  19 ********************************** //
    // ***************************************************************** //

    template <typename T>
    void LazyBST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){
      while (target != NULL && target -> m_data != key){
        parent = target;
        if (key < target -> m_data){
          target = target -> m_left;
        } else {
          target = target -> m_right;
        }
      }
    }

    template <typename T>
    TreeNode<T>* LazyBST<T>::getSuccessor(TreeNode<T>* rightChild){
      while (rightChild -> m_left != NULL){
        rightChild = rightChild -> m_left;
        // successor is either the right of the target node OR
        // the target node's right child's leftmost child (leaf)
      }
      return rightChild;
    }

    template <typename T>
    void LazyBST<T>::remove(T d){
      // check if empty
      TreeNode<T>* target = NULL;
      TreeNode<T>* parent = NULL;
      target = m_root;

      // find target
      findTarget(d, target, parent); // no need to save, target is redefined within the method findTarget
      if (target == NULL){
        // the thing we tried to delete is not in the tree
        return;
      }
      // SCENARIO 1: check if target is a leaf (including root)
      if (target -> m_left == NULL && target -> m_right == NULL) { // no children, leaf
        if (target == m_root){
          m_root = NULL;
        } else { // it's a leaf but not the root
          // set parents left node to null, delete node
          if (target == parent -> m_left){
            parent -> m_left = NULL;
          } else { // right child
            parent -> m_right = NULL;
          }
        }
        delete target; // free up memory of target node, calls destructor of TreeNode
      // SCENARIO 3: target has 2 children
      } else if (target -> m_left != NULL && target -> m_right != NULL){ // both children not null
        TreeNode<T>* suc = getSuccessor(target -> m_right);
        T value = suc -> m_data;
        remove(value);
        target -> m_data = value; // change target (node being removed) to its successors data
      // SCENARIO 2: target has 1 child
      } else {
        TreeNode<T>* child;
        if (target -> m_left != NULL){ // child is left child
          child = target -> m_left;
        } else{ // child is right child
          child = target -> m_right;
        }
        if (target == m_root){
          m_root = child;
        } else {
          if (target == parent -> m_left){ // if target is left child
            parent -> m_left = child; // make the parent's new left child the target's child
          } else {
            parent -> m_right = child;
          }
        }
        delete target;
      }
      -- m_size;
    }

#endif

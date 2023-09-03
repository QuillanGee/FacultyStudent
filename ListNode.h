// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P5: Lazy Balanced Trees - ListNode template class

// ListNode template class

#ifndef LIST_NODE_H
#define LIST_NODE_H

template <typename T>
class ListNode{
  public:
    ListNode(T data);
    ~ListNode();
    T m_data; // actual value being held is
    // each ListNode is pointing to a ListNode front and ListNode back
    ListNode<T>* m_next; // recursive bc it points to instance of itself
    ListNode<T>* m_prev;

};

template <typename T>
ListNode<T>::ListNode(T data){
  m_data = data;
  m_next = NULL;
  m_prev = NULL;
}

template <typename T>
ListNode<T>::~ListNode(){
  m_next = NULL;
  m_prev = NULL;
}

#endif

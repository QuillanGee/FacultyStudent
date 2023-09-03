// Quillan Gee
// 2404244
// qgee@chapman.edu
// CPSC 350-02
// P4: Lazy Balanced Trees - DblList template class

// DblList template class

#ifndef DBL_LIST_H
#define DBL_LIST_H
#include "ListNode.h"

template <typename T>
class DblList{
  public:
    DblList();
    virtual ~DblList();
    int size();
    void addFront(T data);
    void addBack(T data);
    void add(int pos, T data);

    T removeFront();
    T removeBack();
    T remove(int pos);

    T get(int pos);

    bool isEmpty();

  protected:
    ListNode<T>* m_front;
    ListNode<T>* m_back;
    int m_size;
};

template <typename T>
DblList<T>::DblList(){
  m_front = NULL;
  m_back = NULL;
  m_size = 0;
}

template <typename T>
DblList<T>::~DblList(){
  ListNode<T>* current = m_front;
  while (current != NULL){
    delete current;
    current = current -> m_next;
    --m_size;
  }

  m_front = NULL;
  m_back = NULL;
  m_size = 0;
}

template <typename T>
int DblList<T>::size(){
  return m_size;
}

template <typename T>
bool DblList<T>::isEmpty(){
  return (m_size == 0);
}

template <typename T>
void DblList<T>::addFront(T data){
  ListNode<T>* newNode = new ListNode<T>(data);
  if (!isEmpty()){
    newNode -> m_next = m_front;
    m_front -> m_prev = newNode;
  } else {
    // if theres only 1 thing in list newNode is front and back
    m_back = newNode;
  }
  m_front = newNode;
  ++m_size;
}

template <typename T>
void DblList<T>::addBack(T data){
  ListNode<T>* newNode = new ListNode<T>(data);
  if (!isEmpty()){
    newNode -> m_prev = m_back; // set newNode's prev to old back
    m_back -> m_next = newNode; // set oldBack's next to newNode
  } else {
    // if theres only 1 thing in list newNode is front and back
    m_front = newNode;
  }
  m_back = newNode; // make newNode back regardless
  ++m_size;
}

template <typename T>
void DblList<T>::add(int pos, T data){
  if(isEmpty()){
    addFront(data);
  } else if (pos <= 0){
    addFront(data);
  } else if (pos >= m_size){
    addBack(data);
  } else {
    ListNode<T>* current = m_front;
    int cPos = 0;
    while (cPos != pos){
      current = current -> m_next;
      ++cPos;
    }
    ListNode<T>* newNode = new ListNode<T>(data);
    current -> m_prev -> m_next = newNode;
    newNode ->  m_prev = current -> m_prev;
    current -> m_prev = newNode;
    newNode ->  m_next = current;
    ++m_size;
  }
}

template <typename T>
T DblList<T>::removeFront(){
  if (!isEmpty()){
    T data = m_front -> m_data; // so we dont lose access to data later
    if (m_size == 1){
      delete m_front; // dont delete back bc its pointing to the same thing
      m_front = NULL;
      m_back = NULL;
    } else {
      ListNode<T>* currFront = m_front;
      m_front = m_front->m_next;
      m_front -> m_prev = NULL;
      delete currFront;
    }
    --m_size;
    return data;
  }
}

template <typename T>
T DblList<T>::removeBack(){
  if (!isEmpty()){
    T data = m_back -> m_data; // so we dont lose access to data later
    if (m_size == 1){
      delete m_back;
      m_front = NULL;
      m_back = NULL;
    } else {
      ListNode<T>* currBack = m_back;
      m_back = m_back -> m_prev;
      m_back -> m_next = NULL;
      delete currBack;
    }
    --m_size;
    return data;
  }  else {
    // empty
  }
}

template <typename T>
T DblList<T>::remove(int pos){
  if (!isEmpty()){
    T data;
    if(pos <= 0){
      data = removeFront();
    } else if (pos >= m_size){
      data = removeBack();
    } else {
      ListNode<T>* current = m_front;
      int cPos = 0;
      while (cPos != pos){
        current = current -> m_next;
        ++cPos;
      }
      data = current -> m_data;
      current -> m_prev -> m_next = current -> m_next;
      current -> m_next -> m_prev = current -> m_prev;
      delete current;
      --m_size;
    }
    return data;
  }  else {
    // empty
  }
}

template <typename T>
T DblList<T>::get(int pos){
  // check if in range
  if (pos < size()){
    ListNode<T>* current = m_front;
    int cPos = 0;
    while (cPos != pos){
      current = current -> m_next;
      ++cPos;
    }
    return current -> m_data;
  } else {
    // not in range
  }
}

#endif

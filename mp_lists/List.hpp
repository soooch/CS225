/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  tail_ = NULL;
  if (head_ == NULL) return;
  while (head_->next != NULL) {
    head_ = head_->next;
    delete head_->prev;
  }
  delete head_;
  head_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  head_ = newNode;
  

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode->next = NULL;
  newNode->prev = tail_;

  if (tail_ != NULL) {
    tail_->next = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
  }
  tail_ = newNode;

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  static const int rotateSize = 3;
  // @todo Graded in MP3.1
  if (this->length_ < rotateSize) return;
  ListNode * curr = head_;
  head_ = head_->next;
  for (int i = 0; i < length_ / rotateSize; i++) {
    ListNode * first = curr;
    curr = curr->next;
    ListNode * second = curr;
    for (int i = 0; i < rotateSize - 2; i++) { curr = curr->next;}
    ListNode * last = curr;
    curr = curr->next;

    second->prev = first->prev;
    first->next = curr;
    first->prev = last;
    last->next = first;
    if (second->prev != NULL) second->prev->next = second;
    if (curr != NULL) curr->prev = first;

  }
  while (tail_->next != NULL) {
    tail_ = tail_->next;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  std::swap(startPoint, endPoint);

  if (endPoint == head_) { 
    head_ = startPoint;
  }
  else if (startPoint != head_) {
    endPoint->prev->next = startPoint;
  }
  if (startPoint == tail_) { 
    tail_ = endPoint;
  }
  else if (endPoint != tail_) {
    startPoint->next->prev = endPoint;
  }

  ListNode * curr = startPoint;
  while (curr != endPoint) {
    std::swap(curr->prev, curr->next);
    curr = curr->next;
  }
  std::swap(endPoint->prev, endPoint->next);
  std::swap(startPoint->prev, endPoint->next);
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  ListNode * curr = head_;
  for (int i = 0; i < length_ / n; i++) {
    ListNode * start = curr;
    for (int i = 0; i < n - 1; i++) {
      curr = curr->next;
    }
    reverse(start, curr);
    curr = curr->next;
  }
  if (curr != NULL) reverse(curr, tail_);
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode * merged, * curr, * insertStart, * insertEnd;
  if (first->data < second->data) {
    curr = merged = first;
    insertStart = insertEnd = second;
  }
  else {
    curr = merged = second;
    insertStart = insertEnd = first;
  }
  
  while (curr->next != NULL) {
    while (curr->next != NULL) {
      if (curr->next->data < insertStart->data) {
        curr = curr->next;
      }
      else {
        break;
      }
    }
    if (curr->next == NULL) break;
  
    while (insertEnd->next != NULL) {
      if (insertEnd->next->data < curr->next->data) {
        insertEnd = insertEnd->next;
      }
      else {
        break;
      }
    }
    ListNode * insertNew = insertEnd->next;
    insertEnd->next = curr->next;
    curr->next->prev = insertEnd;
    if (insertNew == NULL) break;
    insertStart->prev = curr;
    curr->next = insertStart;
    curr = insertEnd->next;
    insertStart = insertEnd = insertNew;
  }
  insertStart->prev = curr;
  curr->next = insertStart;

  return merged;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength == 1) return start;
  return merge(mergesort(split(start, chainLength/2), chainLength - chainLength/2), mergesort(start, chainLength/2));
}

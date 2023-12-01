#include "chain.h"
#include <cmath>
#include <iostream>

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
  /* your code here */
  clear();
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::insertAfter(Node * p, const Block &ndata) {
  /* your code here */
  length_++;
  Node * startNode = new Node(ndata);
  if(p == NULL){
    
    if(head_ == NULL){
      head_ = startNode;
      return head_;
    }else{
      startNode->next = head_;
      head_->prev = startNode;
      head_ = startNode;
      return head_;
      
    }
    return head_;
    
  }else{
    startNode->next = p->next;
    if(p->next !=NULL){
      p->next->prev = startNode;
    }
    startNode->prev = p;
    p->next = startNode;
    return startNode;
  }
  
}

/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::swap(Node *p, Node *q) {
  /* your code here */
    /* your code here */
  if (p == NULL || q == NULL || p == q)
    return;

  if (p == head_)
    head_ = q;
  else if (q == head_)
    head_ = p;

  Node *temp;
  temp = p->next;
  p->next = q->next;
  q->next = temp;

  if (p->next != NULL)
    p->next->prev = p;
  if (q->next != NULL)
    q->next->prev = q;

  temp = p->prev;
  p->prev = q->prev;
  q->prev = temp;

  if (p->prev != NULL)
    p->prev->next = p;
  if (q->prev != NULL)
    q->prev->next = q;
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear() {
  /* your code here */
  Node * ptr = head_;

  while(ptr !=NULL){
    Node * temp = ptr;
    delete temp;
    ptr = ptr->next;
  }
  head_ = NULL;
  length_ = 0;
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other) {
  /* your code here */
  head_= new Node(other.head_->data);
  head_->next = other.head_->next;
  Node * ptr = head_;
  length_++;

  while(ptr->next !=NULL){
    Node * temp = new Node(ptr->next->data);
    temp->next = ptr->next->next;
    temp->prev = ptr;
    ptr=temp;
    length_++;
  }
}

/* Modifies the current chain:
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block
 *	is big for all other blocks.
 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::unscramble() {
  /* your code here */
  //finding the head
   /* your code here */
  //finding the head
  if(length_<=1)return;

  int len = length_;
  Node * right = head_;
  Node * left = head_;
  Node * section = head_->next;
  Node * change;
  double dist;
  bool rast = true;

  while(len>1){
    dist = pow(10,12);
      while(section != NULL){
        //merge from right
        if(right->data.distanceTo(section->data) < dist){
          dist = right->data.distanceTo(section->data);
          change = section;
          rast = true;
        }
        if(section->data.distanceTo(left->data) < dist){
          dist = section->data.distanceTo(left->data);
          change = section;
          rast = false;
        }

        if(section->next == left){
          section = right->next;
        }else{
          section = section->next;
        }
      }
  

    if(rast){
      if(right->next != NULL){
        swap(right->next,change);
        right = change;
      }else{
        swap(left->prev,change);
        for(int x =0;x<=(length_ - len);x++){
          swap(change,change->next);
        }
        right = change;
      }
    }else{
      if(left->prev!=NULL){
        swap(left->prev,change);
        left = change;
      }else{
        swap(right->next,change);
        for(int x = 0;x<=(length_ - len);x++){
          swap(change,change->prev);
        }
        left = change;
      }
    }
    section = right->next;
    len--;
  }
}

/* no-argument constructor */
Chain::Chain() {
  length_ = 0;
  head_ = NULL;
}

/* Most useful constructor. requires your
 * implementation of Block and insertAfter.
 * Builds a chain out of the blocks in the
 * given image. The blocks we create
 * have width equal to imIn.width()/k
 * (rounded down to an integer)
 * and height equal to imIn.height().
 *
 * @param imIn The image providing the blocks
 * @param k    The number of blocks to extract.
 */
Chain::Chain(PNG & imIn, int k) {
  int w = imIn.width()/k; // width of all blocks
  head_ = NULL;
  length_ = 0;
 

  Node *p = NULL;
  for( int i=0; i < k; i++ ) {
    Block b;
    b.build(imIn , i*w, w);
    p = insertAfter(p, b);
  }
}

/**
 * accessor for the length of the chain.
 */
int Chain::size() const {
   return length_;
}

/* copy constructor */
Chain::Chain(Chain const& other) {
   length_ = 0;
   head_ = NULL;
   copy(other);
}

/* assignment operator */
Chain & Chain::operator=(Chain const& rhs) {
   if (this != &rhs) {
      clear(); // you'll implement clear
      copy(rhs);
   }
   return *this;
}

/**
 * checks for empty list
 */
bool Chain::empty() const {
   return head_ == NULL;
}

/**
 * Takes the current chain and renders it into a
 * correctly sized PNG. The blocks in the chain
 * are placed in the image left to right in order
 * of their occurrence in the chain.
 */
PNG Chain::render() {
  //cout<<"rendering";
  if( head_ == NULL ) return PNG();
  int w = head_->data.width();
  int h = head_->data.height();
  PNG retVal(w * length_, h);
  Node *p = head_;
  for( int x=0; p != NULL; x += w ) {
    p->data.render(retVal, x);
    p=p->next;
  }
  return retVal;
}

/**
 * Public function to test the private function swap.
 * Swap the i-th and j-th nodes in the chain.
 * The 0-th node is the head_.
 */
void Chain::testSwap( int i, int j ) {
  Node *p = head_;
  Node *q = head_;
  for( int a=0; a < i; ++a )
    p = p->next;
  for( int b=0; b < j; ++b )
    q = q->next;
  swap(p,q);
}

/**
 * scramble : randomly permute the nodes in the chain.
 */
void Chain::scramble() {
  if( head_ == NULL ) return;
  
  Node *p = head_;
  for( int k=length_; k > 1; k-- ) {
    int j = rand() % k; // j = 0..k-1
    Node *q = p;
    for( int i=0; i<j; ++i )
      q = q->next;
    swap(p,q);
    // Node q is now in the position of Node p.  We need set p to q->next
    // to allow the for-loop to continue properly.
    p = q->next;
  }
}

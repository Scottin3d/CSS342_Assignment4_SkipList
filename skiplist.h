/**
 * SkipList https://en.wikipedia.org/wiki/Skip_list
 *
 * SkipList with a depth of 1 is similar to a doubly-linked list
 * Each item has a p percent chance of being at the next level up
 * For our implementation p = 50%
 * All elements are inserted at the lowest Depth (1)
 * 50% of the elements inserted in Depth = 2
 * 50% of 50%, or 25% of the elements inserted in Depth = 3
 * and so on
 *
 * If a Skip List has only 1 level, such as p = 0%
 * Insert O(n), Search O(n)
 * For Depth > 1
 * Insert O(log n), Search O(log n)
 * Modifying p allows us to trade off search speed and storage cost
 */

 // Modified and edited by Scott Shirley 0760484 Novemeber 2019


#ifndef ASS4_SKIP_LIST_SKIPLIST_H
#define ASS4_SKIP_LIST_SKIPLIST_H

#include <iostream>

using namespace std;

class SkipList {
  // display with level
  friend ostream &operator<<(ostream &Out, const SkipList &SkipL);

private:
  // private SNode
  // defined in .cpp as SkipList::SNode::SNode(int Data) ...
  struct SNode {
    explicit SNode(int Data);

    int Data = 0;
    // link to Next SNode
	SNode *Next = nullptr;
    // link to Prev SNode
    SNode *Prev = nullptr;
    // link to up one level
    SNode *UpLevel = nullptr;
    // link to down one level
    SNode *DownLevel = nullptr;
  };

  using Snode = struct Snode;

  // Depth of SkipList
  int MaxDepth = 0;

  // array of Depth SNode* objects as FrontGuards linking levels
  SNode **FrontGuards = nullptr;

  // array of Depth SNode* objects as RearGuards linking levels
  SNode **RearGuards;

  // given a SNode, place it before the given NextNode
  void addBefore(SNode *NewNode, SNode *NextNode);

  // return true 50% of time,
  // each node has a 50% chance of being at higher level
  bool alsoHigher() const;

public:
  // default SkipList has Depth of 1, just one doubly-linked list
  explicit SkipList(int Depth = 1);

  // destructor
  virtual ~SkipList();

  // return true if successfully added, no duplicates
  bool add(int Data);

  // return true if successfully removed
  bool remove(int Data);

  // return true if found in SkipList
  bool contains(int Data);

  // moves a node up a level in the skiplist
  SNode* moveNodeUp(SNode* RefNode) ;
};

#endif // ASS4_SKIP_LIST_SKIPLIST_H

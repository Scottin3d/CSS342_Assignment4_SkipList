//
// Created by Yusuf Pisan on 4/26/18.
// Modified and edited by Scott Shirley 0760484 Novemeber 2019
//

#include <climits>
#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "skiplist.h"

using namespace std;

//Outstream overload
std::ostream &operator<<(std::ostream &Out, const SkipList &SkipL) {

	int Level = SkipL.MaxDepth - 1;
  SkipList::SNode *Curr = SkipL.FrontGuards[Level];
  
  for(int I = Level; I >= 0 ; I--){
    Out << "Level: " << I << " -- ";


    while(Curr!= nullptr){
      Out << Curr->Data << ", ";
      Curr = Curr->Next;
	  //TabCount++;
    }
    Out << "\n";
    Curr = SkipL.FrontGuards[I-1];
  }

  return Out;
}

//Constructor for SNode: set the data, set all other pointers to nullptr
SkipList::SNode::SNode(int Data) {
  SNode::Data = Data;
  SNode::DownLevel = nullptr;
  SNode::UpLevel = nullptr;
  SNode::Next = nullptr;
  SNode::Prev = nullptr;
}

/*
SNode does not have any other functions. 
The data members of SNode are directly accessed from SkipList.
*/
SkipList::SkipList(int Depth) {
  MaxDepth = Depth;
  //set front and rear guard array nodes
  FrontGuards = new SNode*[MaxDepth];
  RearGuards = new SNode*[MaxDepth];
  
  //populate guards with SNodes
  for (int I = 0; I < MaxDepth; I++){
    //front/min value
    FrontGuards[I] = new SNode(INT_MIN);
    //rear/max value
    RearGuards[I] = new SNode(INT_MAX);
  }

  //set pointers of guards
  //possible combine with above
  for(int I = 0; I < MaxDepth; I++){
    //set down
    if(I == 0){
      FrontGuards[I]->DownLevel = nullptr;
      RearGuards[I]->DownLevel = nullptr;
    }else{
      FrontGuards[I]->DownLevel = FrontGuards[I-1];
      RearGuards[I]->DownLevel = RearGuards[I-1];
    }

    //set left/Prev
    FrontGuards[I]->Prev = nullptr;
    RearGuards[I]->Prev = FrontGuards[I];

    //set right/Next
    FrontGuards[I]->Next = RearGuards[I];
    RearGuards[I]->Next = nullptr;

    //set up
    if(I != MaxDepth-1){
      FrontGuards[I]->UpLevel = FrontGuards[I+1];
      RearGuards[I]->UpLevel = RearGuards[I+1];
    }else{
      FrontGuards[I]->UpLevel = nullptr;
      RearGuards[I]->UpLevel = nullptr;
    }
  }

  //set head
  //Head = nullptr;
}

//help function - coin flip 
bool SkipList::alsoHigher() const { 
	//clang tidy complained about randomness
	return std::rand()%2 == 1; 
}

//add to the skiplist
//note: while checking back, kept reaching a nullpt
bool SkipList::add(int Data) {
    //Create another node to be inserted at the higher level, newUpper
	//clang tidy is telling me to init with auto
    auto Add = new SNode(Data);
	SkipList::SNode* Curr = FrontGuards[0];

	while (Data >= Curr->Next->Data) {
		Curr = Curr->Next;

		if (Data == Curr->Data) {
			std::cout << Curr->Data << " already in Skiplist!" << "\n";
			delete Add;
			return false;
		}
	}

	//insert new node
	addBefore(Add, Curr->Next);
	//add node up on chance
	SNode* NodeToMoveUp = Curr->Next;

	int Level = 1;
	while (alsoHigher() && Level != MaxDepth) {
		NodeToMoveUp = moveNodeUp(NodeToMoveUp);
		Level++;
	}

	std::cout << NodeToMoveUp->Data << " added to list with " << Level << " Levels" << "\n";
	return true;
}

//help function - links node->UpLevel
SkipList::SNode* SkipList::moveNodeUp(SNode* RefNode) {
	//create new node with data value
	//clang tidy is telling me to init with auto
	auto NewNode = new SNode(RefNode->Data);
	//assign current up to new node up/down
	RefNode->UpLevel = NewNode;
	
	NewNode->DownLevel = RefNode;

	//join new node front/back
		//find next  back
	SNode* NextNode = RefNode->Next;
	//setback, look up, if not null, is value, else step back
	while (NextNode->UpLevel == nullptr) {
		//checks to see if at the back of the skiplist
		if (NextNode->Next == nullptr) {
			break;
		}
		NextNode = NextNode->Next;
	}
	SNode* NextUp = NextNode->UpLevel;
	//addBefore(RefNode->UpLevel, Back->Next)
	addBefore(NewNode, NextUp);
	
	return NewNode;
}

//insert node behind
void SkipList::addBefore(SNode *NewNode, SNode *NextNode) {
	/*
	PrevNode <==> NextNode
	PrevNode <==> NewNode <==> NextNode
	*/
	SNode* PrevNode = NextNode->Prev;

	NewNode->Prev = PrevNode;
	NewNode->Next = NextNode;
	PrevNode->Next = NewNode;
	NextNode->Prev = NewNode;

}

//destructor
SkipList::~SkipList() {
  // need to delete individual nodes
	int Level = MaxDepth - 1;
	for (int I = Level; I >= 0; I--) {
		std::wcout << "Deleting level " << I << "\n";
		SNode* CurrNode = FrontGuards[I];
		SNode* DeleteNode = CurrNode;
		SNode* NextNode = CurrNode->Next;

		//while the next is not null
		//set delete to current
		//set current to next
		//set next to next
		//delete delete
		while (NextNode != nullptr) {
			DeleteNode = CurrNode;
			CurrNode = NextNode;
			NextNode = CurrNode->Next;
			delete DeleteNode;
		}
		
	}
  //loop through list and set to nullptt
  //std:cout << "Deleting " << *this;
	//temp
	//curr = curr-> next
	//delete temp
}

//remove item from skiplist
bool SkipList::remove(int Data) { 
	std::cout << "Trying to remove " << Data << "from list.\n";

	int Level = MaxDepth - 1;
	SNode* CurrNode;

	for (int I = Level; I >= 0; I--) {
		CurrNode = FrontGuards[I];
		//is next data greater than next?
		while (Data >= CurrNode->Data) {
			if (Data == CurrNode->Data) {
				//for remaining levels unlink node
				//SNode* TempNode = CurrNode;
				SNode* NextNode = CurrNode->Next;
				SNode* PrevNode = CurrNode->Prev;

				for(int J = I; J >= 0; J--){
					SNode* TempNode = CurrNode;

					PrevNode->Next = NextNode;
					NextNode->Prev = PrevNode;

					//having trouble removing from bottom row
					if (CurrNode->DownLevel != nullptr) {
						CurrNode = CurrNode->DownLevel;
						PrevNode = CurrNode->Prev;
						NextNode = CurrNode->Next;
					}
					delete TempNode;
					
				}
				//found data, remove
				std::cout << Data << " found in list.  Deleting node!" << "\n";
				return true;
			}
			//down>next
			CurrNode = CurrNode->Next;
		}
		//is end?
		std::cout << Data << " not found on level " << I << "\n";
	}
	//not in list
	std::cout << Data << " not found in list!" << "\n";
	return false;
}

//checks skiplist for input data value
bool SkipList::contains(int Data) {
	//set to top left FrontGuard[MaxDepth-1]
	int Level = MaxDepth - 1;
	SNode* CurrNode;

	for (int I = Level; I >= 0; I--) {
		CurrNode = FrontGuards[I];
	    //is next data greater than next?
		while (Data >= CurrNode->Data) {
			if (Data == CurrNode->Data) {
				std::cout << Data << " found in list!" << "\n";
				return true;
			}
			//down>next
			CurrNode = CurrNode->Next;
		}
	   //is end?
		std::cout << Data <<  " not found on level " << I << "\n";
	}

	std::cout << Data << " not found in list!" << "\n";
	return false;
}

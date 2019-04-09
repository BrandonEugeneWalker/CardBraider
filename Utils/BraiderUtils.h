#ifndef BRAIDERUTILS_H
#define BRAIDERUTILS_H

#include "CardBraider.h"
using namespace model;

//Gets the next node from the given node and returns it.
//@precondition
//      none
//@return
//      the correct next node based on the type
//@para node
//      the node to get next from
//@para type
//      the type of next to get
static CardNode* getNextNode(CardNode* node, CardBraider::AddType type);

//Sets the next node in the given node.
//@precondition
//      none
//@postcondition
//      the next is set
//@para node
//      the node to use
//@para nodeToAdd
//      the node to set
//@para type
//      the type of set
static void setNextNode(CardNode* node, CardNode* nodeToAdd, CardBraider::AddType type);

//Gets the head of the braided list based on type.
//@precondition
//      none
//@return
//      the correct head node based on the type
//@para braider
//      the braider to get the head from
//@para type
//      the type of next to get
static CardNode* getBraidHead(CardBraider* braider, CardBraider::AddType type);

//Sets the head of the braided list based on type.
//@precondition
//      none
//@postcondition
//      the head is set based on type
//@para braider
//      the braider to set the head from
//@para nodeToSet
//      the node to set as the head
//@para type
//      the head type to set
static void setBraidHead(CardBraider* braider, CardNode* nodeToSet, CardBraider::AddType type);


#endif // BRAIDERUTILS_H

#include "CardBraider.h"

namespace model
{

CardBraider::CardBraider()
{
    this -> head = nullptr;
}

CardBraider::~CardBraider()
{
    if (this -> head == nullptr)
    {
        return;
    }
    deconstructNode(this -> head);
}

void CardBraider::deconstructNode(CardNode* currentNode)
{
    if (currentNode == nullptr)
    {
        return;
    }
    CardNode current = *currentNode;
    deconstructNode(current.getNextName());
    current.~CardNode();
}

//Starting with last name braid.
void CardBraider::addNode(CardNode* node)
{
    if (this -> head == nullptr)
    {
        this -> head = node;
    }
    else
    {
        addByNameBraid(this -> head, node);
    }
}

void CardBraider::addByNameBraid(CardNode* currentNode, CardNode* nodeToAdd)
{
    CardNode current = *currentNode;
    CardNode given = *nodeToAdd;
    string givenString = given.getLastName();
    string currentString = current.getLastName();
    if (givenString < currentString)
    {
        CardNode* newCurrent = current.getNextName();
        addByNameBraid(newCurrent, nodeToAdd);
    }
    else
    {
        CardNode* nextNode = current.getNextName();
        given.setNextName(nextNode);
        current.setNextName(nodeToAdd);
    }
}

void CardBraider::deleteNode(string name, CardNode* currentNode, CardNode* previousNode)
{
    if (currentNode == nullptr)
    {
        return;
    }
    CardNode prev = *previousNode;
    CardNode current = *currentNode;
    string currentName = current.getLastName();
    string currentNameToUpper = UTILS_H::toUpperCase(currentName);
    string givenToUpper = UTILS_H::toUpperCase(name);
    CardNode* nextNode = current.getNextName();
    deleteNode(name, nextNode, currentNode);
    if (currentNameToUpper == givenToUpper)
    {
        if (previousNode == nullptr)
        {
            this -> head = nextNode;
            current.~CardNode();
        }
        else
        {
            prev.setNextName(nextNode);
            current.~CardNode();
        }
    }
}

CardNode* CardBraider::getHead()
{
    return this -> head;
}




}

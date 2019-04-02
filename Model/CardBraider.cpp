#include "CardBraider.h"

#define DIAGNOSTIC_OUTPUT

#ifdef DIAGNOSTIC_OUTPUT
#include <iostream>
#endif

namespace model
{

CardBraider::CardBraider()
{
    this -> head = nullptr;
#ifdef DIAGNOSTIC_OUTPUT
    cout << "Constructed Braider: " << endl;
#endif
}

CardBraider::~CardBraider()
{
    if (this -> head == nullptr)
    {
        return;
    }
    deconstructNode(this -> head);
#ifdef DIAGNOSTIC_OUTPUT
    cout << "Destroyed Braider: " << endl;
#endif
}

void CardBraider::deconstructNode(CardNode* currentNode)
{
    if (currentNode == nullptr)
    {
        return;
    }
    deconstructNode(currentNode -> getNextName());
    delete currentNode;
}

//Starting with last name braid.
void CardBraider::addNode(CardNode* node)
{
    if (node == nullptr)
    {
        return;
    }
#ifdef DIAGNOSTIC_OUTPUT
    cout << "Added Node: " << node -> debugDescription() << endl;
#endif
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
    if (currentNode == nullptr)
    {
        nodeToAdd -> setNextName(this -> head);
        this -> head = nodeToAdd;
        return;
    }
    if (nodeToAdd == nullptr)
    {
        return;
    }

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Added Node By Name: " << nodeToAdd -> debugDescription() << endl;
#endif

    string givenString = nodeToAdd -> getLastName();
    string currentString = currentNode -> getLastName();

    if (givenString < currentString)
    {
        this -> addByNameBraid(currentNode -> getNextName(), nodeToAdd);
    }
    else
    {
        nodeToAdd -> setNextName(currentNode -> getNextName());
        currentNode -> setNextName(nodeToAdd);
    }
}

void CardBraider::deleteNode(string name, CardNode* currentNode, CardNode* previousNode)
{
    if (this -> head == nullptr)
    {
        return;
    }
    if (currentNode == nullptr)
    {
        currentNode = this -> head;
    }

    string currentName = currentNode -> getLastName();
    string currentNameToUpper = UTILS_H::toUpperCase(currentName);
    string givenToUpper = UTILS_H::toUpperCase(name);
    CardNode* nextNode = currentNode -> getNextName();
    deleteNode(name, nextNode, currentNode);
    if (currentNameToUpper == givenToUpper)
    {
        if (previousNode == nullptr)
        {
            this -> head = nextNode;
            delete currentNode;
        }
        else
        {
            previousNode -> setNextName(nextNode);
            delete currentNode;
        }
    }
}

CardNode* CardBraider::getHead()
{
    return this -> head;
}




}

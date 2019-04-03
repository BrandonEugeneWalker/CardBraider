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
        addByNameBraid(node);
    }
}

void CardBraider::addByNameBraid(CardNode* nodeToAdd)
{
    if (nodeToAdd == nullptr)
    {
        return;
    }
    CardNode* nextNode = this -> head;
    CardNode* previousNode = nullptr;
    //Candidate node possibly?
    while(nextNode != nullptr)
    {
        string givenString = nodeToAdd -> getLastName();
        string currentString = nextNode -> getLastName();
        if (givenString < currentString)
        {
            if (previousNode != nullptr)
            {
                previousNode -> setNextName(nodeToAdd);
                nodeToAdd -> setNextName(nextNode);
                return;
            }
            else
            {
                nodeToAdd -> setNextName(nextNode);
                this -> head = nodeToAdd;
                return;
            }
        }
        else
        {
            previousNode = nextNode;
            nextNode = nextNode -> getNextName();
        }
    }
    if (previousNode != nullptr)
    {
       previousNode -> setNextName(nodeToAdd);
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

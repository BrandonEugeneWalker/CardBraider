#include "CardBraider.h"

#define DIAGNOSTIC_OUTPUT

#ifdef DIAGNOSTIC_OUTPUT
#include <iostream>
#endif

namespace model
{

CardBraider::CardBraider()
{
    this -> nameHead = nullptr;
    this -> yearHead = nullptr;
    this -> conditionHead = nullptr;

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Constructed Braider: " << endl;
#endif
}

CardBraider::~CardBraider()
{
    if (this -> nameHead == nullptr)
    {
        return;
    }
    deconstructNode(this -> nameHead);
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

void CardBraider::addNode(CardNode* node)
{
    if (node == nullptr)
    {
        return;
    }
#ifdef DIAGNOSTIC_OUTPUT
    cout << "Added Node: " << node -> debugDescription() << endl;
#endif
    if (this -> nameHead == nullptr)
    {
        this -> nameHead = node;
    }
    else if(this -> yearHead == nullptr)
    {
        this -> yearHead = node;
    }
    else if(this -> conditionHead == nullptr)
    {
        this -> conditionHead = node;
    }
    else
    {
        addByNameBraid(node);
        addByYearBraid(node);
        addByConditionBraid(node);
    }
}

bool CardBraider::compareByLastName(CardNode* firstNode, CardNode* secondNode)
{
    string firstString = firstNode -> getLastName();
    string secondString = secondNode -> getLastName();
    return (firstString < secondString);
}

bool CardBraider::compareByYear(CardNode* firstNode, CardNode* secondNode)
{
    int firstYear = firstNode -> getYear();
    int secondYear = secondNode -> getYear();
    return (firstYear < secondYear);
}

bool CardBraider::compareByCondition(CardNode* firstNode, CardNode* secondNode)
{
    int firstCondition = firstNode -> getCondition();
    int secondCondition = secondNode -> getCondition();
    return (firstCondition < secondCondition);
}

void CardBraider::addByNameBraid(CardNode* nodeToAdd)
{
    if (nodeToAdd == nullptr)
    {
        return;
    }
    CardNode* nextNode = this -> nameHead;
    CardNode* previousNode = nullptr;

    while(nextNode != nullptr)
    {
        if (this -> compareByLastName(nodeToAdd, nextNode))
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
                this -> nameHead = nodeToAdd;
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

void CardBraider::addByYearBraid(CardNode* nodeToAdd)
{
    if (nodeToAdd == nullptr)
    {
        return;
    }
    CardNode* nextNode = this -> yearHead;
    CardNode* previousNode = nullptr;

    while(nextNode != nullptr)
    {
        int givenYear = nodeToAdd -> getYear();
        int currentYear = nextNode -> getYear();
        if (this -> compareByYear(nodeToAdd, nextNode))
        {
            if (previousNode != nullptr)
            {
                previousNode -> setNextYear(nodeToAdd);
                nodeToAdd -> setNextYear(nextNode);
                return;
            }
            else
            {
                nodeToAdd -> setNextYear(nextNode);
                this -> yearHead = nodeToAdd;
                return;
            }

        }
        else if (givenYear == currentYear)
        {
            if (this -> compareByLastName(nodeToAdd, nextNode))
            {
                if (previousNode != nullptr)
                {
                    previousNode -> setNextYear(nodeToAdd);
                    nodeToAdd -> setNextYear(nextNode);
                    return;
                }
                else
                {
                    nodeToAdd -> setNextYear(nextNode);
                    this -> yearHead = nodeToAdd;
                    return;
                }
            }
        }
        previousNode = nextNode;
        nextNode = nextNode -> getNextYear();
    }
    if (previousNode != nullptr)
    {
        previousNode -> setNextYear(nodeToAdd);
    }
}

void CardBraider::addByConditionBraid(CardNode* nodeToAdd)
{
    if (nodeToAdd == nullptr)
    {
        return;
    }
    CardNode* nextNode = this -> conditionHead;
    CardNode* previousNode = nullptr;

    while(nextNode != nullptr)
    {
        int givenCondition = nodeToAdd -> getCondition();
        int currentCondition = nextNode -> getCondition();
        if (this -> compareByCondition(nodeToAdd, nextNode))
        {
            if (previousNode != nullptr)
            {
                previousNode -> setNextCondition(nodeToAdd);
                nodeToAdd -> setNextCondition(nextNode);
                return;
            }
            else
            {
                nodeToAdd -> setNextCondition(nextNode);
                this -> conditionHead = nodeToAdd;
                return;
            }

        }
        else if (givenCondition == currentCondition)
        {
            if (this -> compareByLastName(nodeToAdd, nextNode))
            {
                if (previousNode != nullptr)
                {
                    previousNode -> setNextCondition(nodeToAdd);
                    nodeToAdd -> setNextCondition(nextNode);
                    return;
                }
                else
                {
                    nodeToAdd -> setNextCondition(nextNode);
                    this -> conditionHead = nodeToAdd;
                    return;
                }
            }

        }
        previousNode = nextNode;
        nextNode = nextNode -> getNextCondition();
    }
    if (previousNode != nullptr)
    {
        previousNode -> setNextCondition(nodeToAdd);
    }
}


void CardBraider::deleteNode(string name, CardNode* currentNode, CardNode* previousNode)
{
    if (this -> nameHead == nullptr)
    {
        return;
    }
    if (currentNode == nullptr)
    {
        currentNode = this -> nameHead;
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
            this -> nameHead = nextNode;
            delete currentNode;
        }
        else
        {
            previousNode -> setNextName(nextNode);
            delete currentNode;
        }
    }
}

CardNode* CardBraider::getNameHead()
{
    return this -> nameHead;
}

CardNode* CardBraider::getYearHead()
{
    return this -> yearHead;
}

CardNode* CardBraider::getConditionHead()
{
    return this -> conditionHead;
}

}

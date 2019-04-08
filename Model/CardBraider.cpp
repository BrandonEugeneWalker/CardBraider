#include "CardBraider.h"

#define DIAGNOSTIC_OUTPUT

#ifdef DIAGNOSTIC_OUTPUT
#include <iostream>
#endif

namespace model
{

CardBraider::CardBraider()
{
    this -> setHeadsToNullptr();

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
    this -> setHeadsToNullptr();
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
        this -> yearHead = node;
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
        //string nodeToAddName = UTILS_H::toUpperCase(nodeToAdd -> getLastName());
        //string nextNodeName = UTILS_H::toUpperCase(nodeToAdd -> getLastName());
        if (this -> compareByLastName(nodeToAdd, nextNode))
        {
            if (previousNode != nullptr)
            {
#ifdef DIAGNOSTIC_OUTPUT
                cout << "Added " << nodeToAdd -> getLastName() << " to " << previousNode -> getLastName() << endl;
#endif // DIAGNOSTIC_OUTPUT
                previousNode -> setNextName(nodeToAdd);
                nodeToAdd -> setNextName(nextNode);
                return;
            }
            else
            {
#ifdef DIAGNOSTIC_OUTPUT
                cout << "Set " << nodeToAdd -> getLastName() << " as the head node." << endl;
#endif // DIAGNOSTIC_OUTPUT
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
#ifdef DIAGNOSTIC_OUTPUT
        cout << "Added " << nodeToAdd -> getLastName() << " as braid end to" << previousNode -> getLastName() << endl;
#endif // DIAGNOSTIC_OUTPUT
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


void CardBraider::deleteNode(string name)
{
    if (this -> nameHead == nullptr)
    {
        return;
    }

    vector<CardNode*> nodesToDelete = this -> findNodesToRemoveByName(name);
#ifdef DIAGNOSTIC_OUTPUT
    cout << "Inside deleteNode size of vector of nodes to remove: " << nodesToDelete.size() << endl;
#endif // DIAGNOSTIC_OUTPUT

    while(nodesToDelete.size() != 0)
    {
        CardNode* currentNode = nodesToDelete.back();
        this -> removeNodeToDeleteFromNameBraid(currentNode);
        this -> removeNodeToDeleteFromYearBraid(currentNode);
        this -> removeNodeToDeleteFromConditionBraid(currentNode);
        nodesToDelete.pop_back();
        //delete currentNode;
    }
}

vector<CardNode*> CardBraider::findNodesToRemoveByName(string name)
{
    vector<CardNode*> returnVector;
    CardNode* currentNode = this -> nameHead;

    string nameToUpper = UTILS_H::toUpperCase(name);

    while(currentNode != nullptr)
    {
        string currentName = currentNode -> getLastName();
        string currentNameToUpper = UTILS_H::toUpperCase(currentName);
        if (currentNameToUpper == nameToUpper)
        {
#ifdef DIAGNOSTIC_OUTPUT
            cout << "Current: " << currentNameToUpper << " == " << nameToUpper << endl;
#endif
            returnVector.push_back(currentNode);
        }
        else
        {
#ifdef DIAGNOSTIC_OUTPUT
            cout << "Current: " << currentNameToUpper << " != " << nameToUpper << endl;
#endif
        }

        currentNode = currentNode -> getNextName();
    }
    return returnVector;

}

void CardBraider::removeNodeToDeleteFromNameBraid(CardNode* node)
{
    CardNode* previousNode = nullptr;
    CardNode* currentNode = this -> nameHead;
    while(currentNode != nullptr)
    {
        CardNode* nextNode = currentNode -> getNextName();
        if (node == currentNode)
        {
#ifdef DIAGNOSTIC_OUTPUT
            cout << "NameDelete: The currentNode matched the node." << endl;
#endif // DIAGNOSTIC_OUTPUT
            if (previousNode == nullptr)
            {
#ifdef DIAGNOSTIC_OUTPUT
                cout << "NameDelete: The previous node was nullptr." << endl;
#endif // DIAGNOSTIC_OUTPUT
                if (nextNode != nullptr)
                {
#ifdef DIAGNOSTIC_OUTPUT
                    cout << "NameDelete: The next node was not nullptr." << endl;
#endif // DIAGNOSTIC_OUTPUT
                    this -> nameHead = nextNode;
                }
                else
                {
#ifdef DIAGNOSTIC_OUTPUT
                    cout << "NameDelete: The next node was nullptr." << endl;
#endif // DIAGNOSTIC_OUTPUT
                    this -> nameHead = nullptr;
                }
            }
            else
            {
#ifdef DIAGNOSTIC_OUTPUT
                cout << "NameDelete: The previous node was not nullptr." << endl;
#endif // DIAGNOSTIC_OUTPUT
                if (nextNode != nullptr)
                {
                    previousNode -> setNextName(nextNode);
                }
                else
                {
                    previousNode -> setNextName(nullptr);
                }
            }
        }
#ifdef DIAGNOSTIC_OUTPUT
        cout << "NameDelete: The currentNode did not match the node." << endl;
#endif // DIAGNOSTIC_OUTPUT
        previousNode = currentNode;
        currentNode = nextNode;
    }
}

void CardBraider::removeNodeToDeleteFromYearBraid(CardNode* node)
{
    CardNode* previousNode = nullptr;
    CardNode* currentNode = this -> yearHead;
    while(currentNode != nullptr)
    {
        CardNode* nextNode = currentNode -> getNextYear();
        if (node == currentNode)
        {
#ifdef DIAGNOSTIC_OUTPUT
            cout << "YearDelete: The currentNode matched the node." << endl;
#endif // DIAGNOSTIC_OUTPUT
            if (previousNode == nullptr)
            {
#ifdef DIAGNOSTIC_OUTPUT
                cout << "YearDelete: The previous node was nullptr." << endl;
#endif // DIAGNOSTIC_OUTPUT
                if (nextNode != nullptr)
                {
#ifdef DIAGNOSTIC_OUTPUT
                    cout << "YearDelete: The next node was not nullptr." << endl;
#endif // DIAGNOSTIC_OUTPUT
                    this -> yearHead = nextNode;
                }
                else
                {
#ifdef DIAGNOSTIC_OUTPUT
                    cout << "YearDelete: The next node was nullptr." << endl;
#endif // DIAGNOSTIC_OUTPUT
                    this -> yearHead = nullptr;
                }
            }
            else
            {
#ifdef DIAGNOSTIC_OUTPUT
                cout << "YearDelete: The previous node was not nullptr." << endl;
#endif // DIAGNOSTIC_OUTPUT
                if (nextNode != nullptr)
                {
                    previousNode -> setNextYear(nextNode);
                }
                else
                {
                    previousNode -> setNextYear(nullptr);
                }
            }
        }
#ifdef DIAGNOSTIC_OUTPUT
        cout << "YearDelete: The currentNode did not match the node." << endl;
#endif // DIAGNOSTIC_OUTPUT
        previousNode = currentNode;
        currentNode = nextNode;
    }
}

void CardBraider::removeNodeToDeleteFromConditionBraid(CardNode* node)
{
    CardNode* previousNode = nullptr;
    CardNode* currentNode = this -> conditionHead;
    while(currentNode != nullptr)
    {
        CardNode* nextNode = currentNode -> getNextCondition();
        if (node == currentNode)
        {
#ifdef DIAGNOSTIC_OUTPUT
            cout << "ConditionDelete: The currentNode matched the node." << endl;
#endif // DIAGNOSTIC_OUTPUT
            if (previousNode == nullptr)
            {
#ifdef DIAGNOSTIC_OUTPUT
                cout << "ConditionDelete: The previous node was nullptr." << endl;
#endif // DIAGNOSTIC_OUTPUT
                if (nextNode != nullptr)
                {
#ifdef DIAGNOSTIC_OUTPUT
                    cout << "ConditionDelete: The next node was not nullptr." << endl;
#endif // DIAGNOSTIC_OUTPUT
                    this -> conditionHead = nextNode;
                }
                else
                {
#ifdef DIAGNOSTIC_OUTPUT
                    cout << "ConditionDelete: The next node was nullptr." << endl;
#endif // DIAGNOSTIC_OUTPUT
                    this -> conditionHead = nullptr;
                }
            }
            else
            {
#ifdef DIAGNOSTIC_OUTPUT
                cout << "ConditionDelete: The previous node was not nullptr." << endl;
#endif // DIAGNOSTIC_OUTPUT
                if (nextNode != nullptr)
                {
                    previousNode -> setNextCondition(nextNode);
                }
                else
                {
                    previousNode -> setNextCondition(nullptr);
                }
            }
        }
#ifdef DIAGNOSTIC_OUTPUT
        cout << "ConditionDelete: The currentNode did not match the node." << endl;
#endif // DIAGNOSTIC_OUTPUT
        previousNode = currentNode;
        currentNode = nextNode;
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

void CardBraider::setHeadsToNullptr()
{
    this -> nameHead = nullptr;
    this -> yearHead = nullptr;
    this -> conditionHead = nullptr;
}

}

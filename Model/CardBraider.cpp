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
        this -> insert(node, BraidType::NAME);
        this -> insert(node, BraidType::YEAR);
        this -> insert(node, BraidType::CONDITION);
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

bool CardBraider::yearEquals(CardNode* firstNode, CardNode* secondNode)
{
    int firstYear = firstNode -> getYear();
    int secondYear = secondNode -> getYear();
    return (firstYear == secondYear);
}

bool CardBraider::conditionEquals(CardNode* firstNode, CardNode* secondNode)
{
    int firstCondition = firstNode -> getCondition();
    int secondCondition = secondNode -> getCondition();
    return (firstCondition == secondCondition);
}

void CardBraider::insert(CardNode* nodeToAdd, BraidType type)
{
    if (nodeToAdd == nullptr)
    {
        return;
    }

    CardNode* nextNode = this -> getBraidHeadByType(type);
    CardNode* previousNode = nullptr;

    bool (CardBraider::*baseComparator)(CardNode*, CardNode*);
    bool (CardBraider::*equalsComparator)(CardNode*, CardNode*);

    if (type == CardBraider::BraidType::NAME)
    {
        baseComparator = &CardBraider::compareByLastName;
    }
    else if (type == CardBraider::BraidType::YEAR)
    {
        baseComparator = &CardBraider::compareByYear;
        equalsComparator = &CardBraider::yearEquals;
    }
    else if (type == CardBraider::BraidType::CONDITION)
    {
        baseComparator = &CardBraider::compareByCondition;
        equalsComparator = &CardBraider::conditionEquals;
    }

    while(nextNode != nullptr)
    {
        if ((this ->* baseComparator)(nodeToAdd, nextNode))
        {
            if (previousNode != nullptr)
            {
                this -> setNextNodeByType(previousNode, nodeToAdd, type);
                this -> setNextNodeByType(nodeToAdd, nextNode, type);
                return;
            }
            else
            {
                this -> setNextNodeByType(nodeToAdd, nextNode, type);
                this -> setBraidHeadByType(nodeToAdd, type);
                return;
            }
        }
        else if (type != BraidType::NAME)
        {
            if ((this ->* equalsComparator)(nodeToAdd, nextNode))
            {
                if (this -> compareByLastName(nodeToAdd, nextNode))
                {
                    if (previousNode != nullptr)
                    {
                        this -> setNextNodeByType(previousNode, nodeToAdd, type);
                        this -> setNextNodeByType(nodeToAdd, nextNode, type);
                        return;
                    }
                    else
                    {
                        this -> setNextNodeByType(nodeToAdd, nextNode, type);
                        this -> setBraidHeadByType(nodeToAdd, type);
                        return;
                    }
                }
            }
        }
        previousNode = nextNode;
        nextNode = this -> getNextNodeByType(nextNode, type);
    }
    if (previousNode != nullptr)
    {
        this -> setNextNodeByType(previousNode, nodeToAdd, type);
    }
}

bool CardBraider::deleteNode(string name)
{
    bool results = false;
    if (this -> nameHead == nullptr)
    {
        return false;
    }

    vector<CardNode*> nodesToDelete = this -> findNodesToRemoveByName(name);

    while(nodesToDelete.size() != 0)
    {
        CardNode* currentNode = nodesToDelete.back();
        //this -> removeNodeToDeleteFromNameBraid(currentNode);
        //this -> removeNodeToDeleteFromYearBraid(currentNode);
        //this -> removeNodeToDeleteFromConditionBraid(currentNode);
        this -> remove(currentNode, BraidType::NAME);
        this -> remove(currentNode, BraidType::YEAR);
        this -> remove(currentNode, BraidType::CONDITION);
        nodesToDelete.pop_back();
        delete currentNode;
        results = true;
    }
    return results;
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
            returnVector.push_back(currentNode);
        }

        currentNode = currentNode -> getNextName();
    }
    return returnVector;

}

void CardBraider::remove(CardNode* node, BraidType type)
{
    CardNode* previousNode = nullptr;
    CardNode* currentNode = this -> getBraidHeadByType(type);
    while(currentNode != nullptr)
    {
        CardNode* nextNode = this -> getNextNodeByType(currentNode, type);
        if (node == currentNode)
        {
            if (previousNode == nullptr)
            {
                if (nextNode != nullptr)
                {
                    this -> setNextNodeByType(this -> getBraidHeadByType(type), nextNode, type);
                }
                else
                {
                    this -> setBraidHeadByType(nullptr, type);
                }
            }
            else
            {
                if (nextNode != nullptr)
                {
                    this -> setNextNodeByType(previousNode, nextNode, type);
                }
                else
                {
                    this -> setNextNodeByType(previousNode, nullptr, type);
                }
            }
        }
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

void CardBraider::setNameHead(CardNode* node)
{
    this -> nameHead = node;
}

void CardBraider::setYearHead(CardNode* node)
{
    this -> yearHead = node;
}

void CardBraider::setConditionHead(CardNode* node)
{
    this -> conditionHead = node;
}

void CardBraider::setHeadsToNullptr()
{
    this -> nameHead = nullptr;
    this -> yearHead = nullptr;
    this -> conditionHead = nullptr;
}

CardNode* CardBraider::getNextNodeByType(CardNode* node, CardBraider::BraidType type)
{
    CardNode* returnNode = nullptr;
    if (type == BraidType::NAME)
    {
        returnNode = node -> getNextName();
    }
    else if (type == BraidType::YEAR)
    {
        returnNode = node -> getNextYear();
    }
    else if (type == BraidType::CONDITION)
    {
        returnNode = node -> getNextCondition();
    }
    return returnNode;
}

void CardBraider::setNextNodeByType(CardNode* node, CardNode* nodeToSet, CardBraider::BraidType type)
{
    if (type == BraidType::NAME)
    {
        node -> setNextName(nodeToSet);
    }
    else if (type == BraidType::YEAR)
    {
        node -> setNextYear(nodeToSet);
    }
    else if (type == BraidType::CONDITION)
    {
        node -> setNextCondition(nodeToSet);
    }
}

CardNode* CardBraider::getBraidHeadByType(CardBraider::BraidType type)
{
    CardNode* returnNode = nullptr;
    if (type == BraidType::NAME)
    {
        returnNode = this -> getNameHead();
    }
    else if (type == BraidType::YEAR)
    {
        returnNode = this -> getYearHead();
    }
    else if (type == BraidType::CONDITION)
    {
        returnNode = this -> getConditionHead();
    }
    return returnNode;
}

void CardBraider::setBraidHeadByType(CardNode* nodeToSet, CardBraider::BraidType type)
{
    if (type == BraidType::NAME)
    {
        this -> setNameHead(nodeToSet);
    }
    else if (type == BraidType::YEAR)
    {
        this -> setYearHead(nodeToSet);
    }
    else if (type == BraidType::CONDITION)
    {
        this -> setConditionHead(nodeToSet);
    }
}

}

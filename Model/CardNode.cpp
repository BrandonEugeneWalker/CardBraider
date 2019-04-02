#include "CardNode.h"

#define DIAGNOSTIC_OUTPUT

#ifdef DIAGNOSTIC_OUTPUT
#include <iostream>
#endif

namespace model
{

CardNode::CardNode(BaseballCard* nodeCard)
{
    this -> baseballCard = nodeCard;
    this -> firstName = nodeCard -> getFirstName();
    this -> lastName = nodeCard -> getLastName();
    this -> year = nodeCard -> getYear();
    this -> value = nodeCard -> getPrice();
    this -> nextName = nullptr;
    this -> nextYear = nullptr;
    this -> nextCondition = nullptr;
    #ifdef DIAGNOSTIC_OUTPUT
        cout << "Constructed Node: " << this -> debugDescription() << endl;
    #endif
}

CardNode::~CardNode()
{
    delete this -> baseballCard;
    this -> nextName = nullptr;
    this -> nextYear = nullptr;
    this -> nextCondition = nullptr;
    #ifdef DIAGNOSTIC_OUTPUT
        cout << "Destroyed Node: " << this -> debugDescription() << endl;
    #endif
}

string CardNode::getFirstName() const
{
    return this -> baseballCard -> getFirstName();
}

string CardNode::getLastName() const
{
    return this -> baseballCard -> getLastName();
}

BaseballCard::Condition CardNode::getCondition() const
{
    return this -> baseballCard -> getCondition();
}

int CardNode::getYear() const
{
    return this -> baseballCard -> getYear();
}

int CardNode::getValue() const
{
    return this -> baseballCard -> getPrice();
}

CardNode* CardNode::getNextName()
{
    return this -> nextName;
}

CardNode* CardNode::getNextYear()
{
    return this -> nextYear;
}

CardNode* CardNode::getNextCondition()
{
    return this -> nextCondition;
}

void CardNode::setNextName(CardNode* node)
{
    this -> nextName = node;
}

void CardNode::setNextYear(CardNode* node)
{
    this -> nextYear = node;
}

void CardNode::setNextCondition(CardNode* node)
{
    this -> nextCondition = node;
}

string CardNode::debugDescription()
{
    return this -> firstName + " " + this -> lastName;
}

BaseballCard* CardNode::getBaseballCard()
{
    return this -> baseballCard;
}

}

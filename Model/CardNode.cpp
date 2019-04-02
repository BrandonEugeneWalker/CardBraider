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
    BaseballCard dereferencedCard = *nodeCard;
    this -> firstName = dereferencedCard.getFirstName();
    this -> lastName = dereferencedCard.getLastName();
    this -> year = dereferencedCard.getYear();
    this -> value = dereferencedCard.getPrice();
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
    return this -> firstName;
}

string CardNode::getLastName() const
{
    return this -> lastName;
}

BaseballCard::Condition CardNode::getCondition() const
{
    return this -> condition;
}

int CardNode::getYear() const
{
    return this -> year;
}

int CardNode::getValue() const
{
    return this -> value;
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

}

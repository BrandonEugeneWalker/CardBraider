#include "BaseballCard.h"

#define DIAGNOSTIC_OUTPUT

#ifdef DIAGNOSTIC_OUTPUT
#include <iostream>
#endif

namespace model
{

BaseballCard::BaseballCard(const string& firstName, const string& lastName, int year, Condition condition, int price)
{
    this -> firstName = firstName;
    this -> lastName = lastName;
    this -> year = year;
    this -> condition = condition;
    this -> price = price;
    #ifdef DIAGNOSTIC_OUTPUT
        cout << "Constructed Card: " << this -> debugDescription() << endl;
    #endif
}

const string& BaseballCard::getFirstName() const
{
    return this -> firstName;
}

const string& BaseballCard::getLastName() const
{
    return this -> lastName;
}

BaseballCard::Condition BaseballCard::getCondition() const
{
    return this -> condition;
}

int BaseballCard::getYear() const
{
    return this -> year;
}

int BaseballCard::getPrice() const
{
    return this -> price;
}

BaseballCard::~BaseballCard()
{
    #ifdef DIAGNOSTIC_OUTPUT
        cout << "Destroyed Card: " << this -> debugDescription() << endl;
    #endif
}

string BaseballCard::debugDescription()
{
    string returnString = this -> firstName + " " + this -> lastName;
    return returnString;
}

}

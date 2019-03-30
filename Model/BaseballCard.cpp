#include "BaseballCard.h"

namespace model
{
//
// NOT documented as this class should be replaced by your own BaseballCard class
//
BaseballCard::BaseballCard(const string& firstName, const string& lastName, int year, Condition condition, int price)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->year = year;
    this->condition = condition;
    this->price = price;
}

const string& BaseballCard::getFirstName() const
{
    return this->firstName;
}

const string& BaseballCard::getLastName() const
{
    return this->lastName;
}

BaseballCard::Condition BaseballCard::getCondition() const
{
    return this->condition;
}

int BaseballCard::getYear() const
{
    return this->year;
}

int BaseballCard::getPrice() const
{
    return this->price;
}

BaseballCard::~BaseballCard()
{
    //dtor
}

}

#ifndef BASEBALLCARD_H
#define BASEBALLCARD_H

#include <string>
using namespace std;

namespace model
{

class BaseballCard
{
public:
    enum Condition {POOR, GOOD, EXCELLENT, MINT, PRISTINE, UNKNOWN};

private:
    string firstName;
    string lastName;
    int year;
    Condition condition;
    int price;

public:
    BaseballCard(const string& firstName, const string& lastName, int year, Condition condition, int price);
    virtual ~BaseballCard();

    const string& getFirstName() const;
    const string& getLastName() const;
    BaseballCard::Condition getCondition() const;
    int getYear() const;
    int getPrice() const;
};

}

#endif // BASEBALLCARD_H

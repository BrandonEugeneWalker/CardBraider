#ifndef BASEBALLCARD_H
#define BASEBALLCARD_H

#include <string>
using namespace std;

namespace model
{

class BaseballCard
{
public:
    //  The condition of the card.
    enum Condition {POOR, GOOD, EXCELLENT, MINT, PRISTINE, UNKNOWN};

private:
    string firstName;
    string lastName;
    int year;
    Condition condition;
    int price;

public:
    // Creates a new instance of a BaseballCard using the given parameters.
    // @precondition
    //      firstName cannot be none,
    //      lastName cannot be none,
    // @postcondition
    //      a new instance of the card is created
    // @para firstName
    //      the first name
    // @para lastName
    //      the last name
    // @para year
    //      the year the card was made
    // @para condition
    //      the condition of the card
    // @para price
    //      the price of the card
    BaseballCard(const string& firstName, const string& lastName, int year, Condition condition, int price);

    // Destroys a BaseballCard to free up memory.
    virtual ~BaseballCard();

    // Gets the first name on a card.
    //@precondition
    //      none
    // @return
    //      the first name
    const string& getFirstName() const;

    // Gets the last name on a card.
    //@precondition
    //      none
    // @return
    //      the last name
    const string& getLastName() const;

    // Gets the condition of a card.
    //@precondition
    //      none
    // @return
    //      the condition
    Condition getCondition() const;

    // Gets the year on a card.
    //@precondition
    //      none
    // @return
    //      the year
    int getYear() const;

    // Gets the price on a card.
    //@precondition
    //      none
    // @return
    //      the price
    int getPrice() const;

    //A method that returns a description of an object for debugging purposes.
    //@precondition
    //      none
    //@return
    //      a object description
    string debugDescription();
};

}

#endif // BASEBALLCARD_H

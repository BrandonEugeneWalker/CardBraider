#ifndef CARDNODE_H
#define CARDNODE_H

#include <string>
using namespace std;

#include "BaseballCard.h"

namespace model
{

class CardNode
{
private:
    BaseballCard* baseballCard;
    string firstName;
    string lastName;
    int year;
    BaseballCard::Condition condition;
    int value;
    CardNode* nextName;
    CardNode* nextYear;
    CardNode* nextCondition;


public:
    // Creates a new instance of a CardNode.
    // @precondition
    //      baseballCard cannot be a nullptr
    // @postcondition
    //      the CardNode is created.
    // @para baseballCard
    //      The card inside the node.
    CardNode(BaseballCard* nodeCard);

    //Destroys a CardNode to free up memory.
    virtual ~CardNode();

    // Gets the first name of the card inside of the node.
    // @precondition
    //      none
    // @return
    //      the first name
    string getFirstName() const;

    // Gets the last name of the card inside of the node.
    // @precondition
    //      none
    // @return
    //      the last name
    string getLastName() const;

    // Gets the condition of a card inside of the node.
    // @precondition
    //      none
    // @return
    //      the condition
    BaseballCard::Condition getCondition() const;

    // Gets the year on a card inside of the node.
    // @precondition
    //      none
    // @return
    //      the year
    int getYear() const;

    //Gets the value of a card inside of a node.
    // @precondition
    //      none
    // @return
    //      the year
    int getValue() const;

    // Gets the next name node.
    // @precondition
    //      none
    // @return
    //      the next name node
    CardNode* getNextName();

    // Gets the next year node.
    // @precondition
    //      none
    // @return
    //      the next year node
    CardNode* getNextYear();

    // Gets the next condition node.
    // @precondition
    //      none
    // @return
    //      the next condition node
    CardNode* getNextCondition();

    //Sets the next name node.
    //@precondition
    //      none
    //@postcondition
    //      the next node is set
    //@para node
    //      the node to set
    void setNextName(CardNode* node);

    //Sets the next year node.
    //@precondition
    //      none
    //@postcondition
    //      the next node is set
    //@para node
    //      the node to set
    void setNextYear(CardNode* node);

    //Sets the next condition node.
    //@precondition
    //      none
    //@postcondition
    //      the next node is set
    //@para node
    //      the node to set
    void setNextCondition(CardNode* node);

    //A method that returns a description of an object for debugging purposes.
    //@precondition
    //      none
    //@return
    //      a object description
    string debugDescription();


};

}

#endif // CARDNODE_H

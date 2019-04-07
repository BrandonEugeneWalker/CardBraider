#ifndef CARDBRAIDER_H
#define CARDBRAIDER_H

#include <string>
#include <iostream>
using namespace std;

#include "CardNode.h"
#include "Utils.h"

namespace model
{

class CardBraider
{
private:
    CardNode* nameHead;
    CardNode* yearHead;
    CardNode* conditionHead;

    void deconstructNode(CardNode* currentNode);

    bool compareByLastName(CardNode* firstNode, CardNode* secondNode);

    bool compareByYear(CardNode* firstNode, CardNode* secondNode);

    bool compareByCondition(CardNode* firstNode, CardNode* secondNode);

    void addByNameBraid(CardNode* nodeToAdd);

    void addByYearBraid(CardNode* nodeToAdd);

    void addByConditionBraid(CardNode* nodeToAdd);


public:
    // Creates a new instance of a CardBraider.
    // @precondition
    //      none
    // @postcondition
    //      the CardBraider is created.
    CardBraider();

    //Destroys a CardBraider to free up memory.
    virtual ~CardBraider();

    //Adds a node to each of the braids.
    //@precondition
    //      node cannot be nullptr
    //@postcondition
    //      the node is added
    //@para node
    //      the node to add
    void addNode(CardNode* node);

    //Removes all nodes matching the given last name.
    //@precondition
    //      name cannot be empty
    //@postcondition
    //      the node(s) are deleted
    //@para name
    //      the name to delete by
    void deleteNode(string name, CardNode* currentNode, CardNode* previousNode);

    //Gets and returns the pointer to the name head.
    //@precondition
    //      none
    //@return
    //      the pointer if it exists, nullptr otherwise
    CardNode* getNameHead();

    //Gets and returns the pointer to the year head.
    //@precondition
    //      none
    //@return
    //      the pointer if it exists, nullptr otherwise
    CardNode* getYearHead();

    //Gets and returns the pointer to the condition head.
    //@precondition
    //      none
    //@return
    //      the pointer if it exists, nullptr otherwise
    CardNode* getConditionHead();

};

}

#endif // CARDBRAIDER_H

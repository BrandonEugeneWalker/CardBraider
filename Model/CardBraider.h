#ifndef CARDBRAIDER_H
#define CARDBRAIDER_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include "CardNode.h"
#include "Utils.h"
namespace model
{

class CardBraider
{
public:
    enum BraidType {NAME, YEAR, CONDITION};

private:
    CardNode* nameHead;
    CardNode* yearHead;
    CardNode* conditionHead;

    void deconstructNode(CardNode* currentNode);
    bool compareByLastName(CardNode* firstNode, CardNode* secondNode);
    bool compareByYear(CardNode* firstNode, CardNode* secondNode);
    bool compareByCondition(CardNode* firstNode, CardNode* secondNode);
    void setHeadsToNullptr();
    vector<CardNode*> findNodesToRemoveByName(string name);
    void insert(CardNode* nodeToAdd, BraidType type);
    bool yearEquals(CardNode* firstNode, CardNode* secondNode);
    bool conditionEquals(CardNode* firstNode, CardNode* secondNode);
    void remove(CardNode* node, BraidType type);

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
    bool deleteNode(string name);

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

    //Sets the head of the name braid.
    //@precondition
    //      none
    //@postcondition
    //      the head is set
    //@para node
    //      the node to set as the head, can be nullptr
    void setNameHead(CardNode* node);

    //Sets the head of the year braid.
    //@precondition
    //      none
    //@postcondition
    //      the head is set
    //@para node
    //      the node to set as the head, can be nullptr
    void setYearHead(CardNode* node);

    //Sets the head of the condition braid.
    //@precondition
    //      none
    //@postcondition
    //      the head is set
    //@para node
    //      the node to set as the head, can be nullptr
    void setConditionHead(CardNode* node);

    //Gets the next node based on the given type.
    //@precondition
    //      none
    //@return
    //      the next node based on type
    //@para node
    //      the node to get the next node from
    //@para type
    //      the type of braid to get the next node from
    static CardNode* getNextNodeByType(CardNode* node, CardBraider::BraidType type);

    //Sets the next node depending on the given type.
    //@precondition
    //      none
    //@postcondition
    //      the next node is set
    //@para node
    //      the node whose next node is set
    //@para nodeToSet
    //      the node being set
    //@para type
    //      the braid type to set to
    void setNextNodeByType(CardNode* node, CardNode* nodeToSet, CardBraider::BraidType type);

    //Gets the head node of the given braid type.
    //@precondition
    //      none
    //@return
    //      the head node of the braid type
    //@para type
    //      the braid head to get
    CardNode* getBraidHeadByType(CardBraider::BraidType type);

    //Sets the head node depending on the given type.
    //@precondition
    //      none
    //@postcondition
    //      the head node is set
    //@para nodeToSet
    //      the node being set
    //@para type
    //      the braid type to set to
    void setBraidHeadByType(CardNode* nodeToSet, CardBraider::BraidType type);

};

}

#endif // CARDBRAIDER_H

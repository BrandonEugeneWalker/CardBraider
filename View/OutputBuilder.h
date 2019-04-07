#ifndef OUTPUTBUILDER_H
#define OUTPUTBUILDER_H

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

#include "CardBraider.h"
using namespace model;

namespace view
{

class OutputBuilder
{
public:
    //The sorting type to use when building the output.
    enum SortType {NAME, YEAR, CONDITION};

private:
    string outputString;
    void buildByLastName(bool isAscending, CardNode* node);
    void buildByYear(bool isAscending, CardNode* node);
    void buildByCondition(bool isAscending, CardNode* node);
    void buildCardDescription(CardNode* node);
    string determineCondition(BaseballCard::Condition condition);
    string buildMonetaryOutput(int value);

public:
    //Creates a new instance of a OutputBuilder.
    //@precondition
    //      none
    //@postcondition
    //      a new OutputBuilder is created.
    OutputBuilder();

    //Destroys a OutputBuilder to free up space.
    virtual ~OutputBuilder();

    //Recursively builds the output of a braided list from the given head.
    //@precondition
    //      none
    //@return
    //      output based on the list
    //@para isAscending
    //      true if ascending, false if descending
    //@para head
    //      the head node of the braided list
    string buildOutput(bool isAscending, SortType sortType, CardNode* head);


};

}

#endif // OUTPUTBUILDER_H

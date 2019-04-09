#ifndef OUTPUTBUILDER_H
#define OUTPUTBUILDER_H

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <locale>
using namespace std;

#include "CardBraider.h"
using namespace model;

namespace view
{

class OutputBuilder
{
private:
    string outputString;
    void buildCardDescription(CardNode* node);
    string buildMonetaryOutput(int value);
    void buildByType(bool isAscending, CardNode* node, CardBraider::BraidType type);

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
    //@para type
    //      the braid type to build using
    //@para head
    //      the head node of the braided list
    string buildOutput(bool isAscending, CardBraider::BraidType type, CardNode* head);


};

}

#endif // OUTPUTBUILDER_H

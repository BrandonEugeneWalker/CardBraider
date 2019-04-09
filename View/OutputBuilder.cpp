#include "OutputBuilder.h"

#define DIAGNOSTIC_OUTPUT


namespace view
{

OutputBuilder::OutputBuilder()
{
#ifdef DIAGNOSTIC_OUTPUT
    cout << "Constructed OutputBuilder: " << endl;
#endif
}

OutputBuilder::~OutputBuilder()
{
#ifdef DIAGNOSTIC_OUTPUT
    cout << "Destroyed OutputBuilder: " << endl;
#endif
}

string OutputBuilder::buildOutput(bool isAscending, CardBraider::BraidType type, CardNode* head)
{
    if (head == nullptr)
    {
        outputString = "The collection is empty.";
    }
    else
    {
        this -> buildByType(isAscending, head, type);
    }

    return this -> outputString;

}

void OutputBuilder::buildByType(bool isAscending, CardNode* node, CardBraider::BraidType type)
{
    if (node == nullptr)
    {
        return;
    }
    if (isAscending)
    {
        buildCardDescription(node);
        buildByType(isAscending, CardBraider::getNextNodeByType(node, type), type);
    }
    else
    {
        buildByType(isAscending, CardBraider::getNextNodeByType(node, type), type);
        buildCardDescription(node);
    }
}

void OutputBuilder::buildCardDescription(CardNode* node)
{
    if(node == nullptr)
    {
        return;
    }
    stringstream outputStream;

    string firstName = node -> getFirstName();
    string lastName = node -> getLastName();
    BaseballCard::Condition condition = node -> getCondition();
    float value = node -> getValue();
    int year = node -> getYear();
    string monetaryOutput = this -> buildMonetaryOutput(value);
    string fullName = firstName + " " + lastName;
    string conditionString = UTILS_H::enumToString(condition);

    outputStream << left << setw(20) << fullName;
    outputStream << left << setw(10) << year;
    outputStream << left << setw(10) << conditionString;
    outputStream << right << setw(18) << monetaryOutput;
    outputStream << endl;

    string currentOutput = this -> outputString;
    string results = outputStream.str();
    string newOutput = currentOutput + results;
    this -> outputString = newOutput;
}

string OutputBuilder::buildMonetaryOutput(int value)
{
    stringstream monetaryStream;
    locale mylocale("");
    monetaryStream.imbue(mylocale);
    monetaryStream << "$" << put_money(value * 100);
    return monetaryStream.str();
}

}

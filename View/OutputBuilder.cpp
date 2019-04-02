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

string OutputBuilder::buildOutput(bool isAscending, CardNode* head)
{
    if (head == nullptr)
    {
        return "The collection is empty.";
    }
    //changeOutputLocation();
    buildByLastName(isAscending, head);
    //returnOutputLocation();
    return this -> outputString;

}

void OutputBuilder::buildByLastName(bool isAscending, CardNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    if (isAscending)
    {
        buildCardDescription(node);
        buildByLastName(isAscending, node -> getNextName());
    }
    else
    {
        buildByLastName(isAscending, node -> getNextName());
        buildCardDescription(node);
    }
}

void OutputBuilder::buildCardDescription(CardNode* node)
{
    stringstream outputStream;

    string firstName = node -> getFirstName();
    string lastName = node -> getLastName();
    BaseballCard::Condition condition = node -> getCondition();
    float value = node -> getValue();
    int year = node -> getYear();
    string monetaryOutput = this -> buildMonetaryOutput(value);
    string fullName = firstName + " " + lastName;
    string conditionString = determineCondition(condition);

    outputStream << left << setw(20) << fullName;
    outputStream << left << setw(10) << year;
    outputStream << left << setw(10) << conditionString;
    outputStream << right << setw(20) << monetaryOutput;
    outputStream << endl;

    string currentOutput = this -> outputString;
    string results = outputStream.str();
    string newOutput = currentOutput + results;
    this -> outputString = newOutput;
}

string OutputBuilder::determineCondition(BaseballCard::Condition condition)
{
#ifdef DIAGNOSTIC_OUTPUT
    cout << "Output Builder Given Condition: " << condition << endl;
#endif

    string returnString = "Unknown";
    if (condition == 0)
    {
        returnString = "Poor";
    }
    else if (condition == 1)
    {
        returnString = "Good";
    }
    else if (condition == 2)
    {
        returnString = "Excellent";
    }
    else if (condition == 3)
    {
        returnString = "Mint";
    }
    else if (condition == 4)
    {
        returnString = "Pristine";
    }

    return returnString;
}

string OutputBuilder::buildMonetaryOutput(int value)
{
    string monetaryOutput = to_string(value);
    int insertPosition = monetaryOutput.length() - 3;
    while (insertPosition > 0)
    {
        monetaryOutput.insert(insertPosition, ",");
        insertPosition -= 3;
    }
    string returnString = "$" + monetaryOutput + ".00";
    return returnString;
}

}

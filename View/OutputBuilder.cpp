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

string OutputBuilder::buildOutput(bool isAscending, SortType sortType, CardNode* head)
{
    if (head == nullptr)
    {
            return "The collection is empty.";
        }
    if (sortType == SortType::NAME)
    {
        this -> buildByLastName(isAscending, head);
    }
    else if (sortType == SortType::YEAR)
    {
        this -> buildByYear(isAscending, head);
    }
    else if (sortType == SortType::CONDITION)
    {
        this -> buildByCondition(isAscending, head);
    }

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

void OutputBuilder::buildByYear(bool isAscending, CardNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    if (isAscending)
    {
        buildCardDescription(node);
        buildByYear(isAscending, node -> getNextYear());
    }
    else
    {
        buildByYear(isAscending, node -> getNextYear());
        buildCardDescription(node);
    }
}

void OutputBuilder::buildByCondition(bool isAscending, CardNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    if (isAscending)
    {
        buildCardDescription(node);
        buildByCondition(isAscending, node -> getNextCondition());
    }
    else
    {
        buildByCondition(isAscending, node -> getNextCondition());
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
    if (condition == BaseballCard::Condition::POOR)
    {
        returnString = "Poor";
    }
    else if (condition == BaseballCard::Condition::GOOD)
    {
        returnString = "Good";
    }
    else if (condition == BaseballCard::Condition::EXCELLENT)
    {
        returnString = "Excellent";
    }
    else if (condition == BaseballCard::Condition::MINT)
    {
        returnString = "Mint";
    }
    else if (condition == BaseballCard::Condition::PRISTINE)
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

#include "OutputBuilder.h"

#define DIAGNOSTIC_OUTPUT


namespace view
{

OutputBuilder::OutputBuilder()
{
    this -> coutBuff = nullptr;
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

void OutputBuilder::changeOutputLocation()
{
    streambuf *psbuf, *backup;
    ostringstream outputStream(this -> outputString, ios_base::out);

    backup = cout.rdbuf();

    psbuf = outputStream.rdbuf();
    cout.rdbuf(psbuf);

    this -> coutBuff = backup;
}

void OutputBuilder::returnOutputLocation()
{
    cout.rdbuf(this -> coutBuff);
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
    int value = node -> getValue();
    int year = node -> getYear();
    string fullName = firstName + " " + lastName;
    string conditionString = determineCondition(condition);

    outputStream << left << setw(20) << fullName;
    outputStream << left << setw(10) << year;
    outputStream << left << setw(10) << conditionString;
    outputStream << right << setw(10) << "$" << std::put_money(value);
    outputStream << endl;

    string currentOutput = this -> outputString;
    string results = outputStream.str();
    string newOutput = currentOutput + results;
    this -> outputString = newOutput;
}

string OutputBuilder::determineCondition(BaseballCard::Condition condition)
{
    string returnString;
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
    else
    {
        returnString = "Unknown";
    }
    return returnString;
}

}

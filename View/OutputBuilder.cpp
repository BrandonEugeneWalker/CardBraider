#include "OutputBuilder.h"

namespace view
{

OutputBuilder::OutputBuilder()
{
    this -> coutBuff = nullptr;
}

OutputBuilder::~OutputBuilder()
{
    //dtor
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
            return "";
    }
    changeOutputLocation();
    buildByLastName(isAscending, head);
    returnOutputLocation();
    return this -> outputString;

}

void OutputBuilder::buildByLastName(bool isAscending, CardNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    CardNode currentNode = *node;
    CardNode* nextNode = currentNode.getNextName();
    if (isAscending)
    {
        buildCardDescription(node);
        buildByLastName(isAscending, nextNode);
    }
    else
    {
        buildByLastName(isAscending, nextNode);
        buildCardDescription(node);
    }
}

void OutputBuilder::buildCardDescription(CardNode* node)
{
    CardNode currentNode = *node;
    string firstName = currentNode.getFirstName();
    string lastName = currentNode.getLastName();
    BaseballCard::Condition condition = currentNode.getCondition();
    int value = currentNode.getValue();
    int year = currentNode.getYear();
    string fullName = firstName + " " + lastName;
    string conditionString = determineCondition(condition);

    cout << left << setw(20) << fullName;
    cout << left << setw(20) << year;
    cout << left << setw(20) << conditionString;
    cout << right << setw(20) << std::put_money(value);
    cout << endl;
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

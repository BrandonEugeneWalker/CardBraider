#include "AddBaseballCardWindow.h"

#include "Utils.h"

#include <Fl/fl_ask.H>
#include <sstream>
using namespace std;

namespace view
{

//
// Constructs an add card window creating and initializing all the widgets that will be displayed
//
// @precondition none
// @postcondition none
//
AddBaseballCardWindow::AddBaseballCardWindow() : OKCancelWindow(330, 215, "Card to add")
{
    const int X_INPUT_LOCATION = 110;

    this->pCard = 0;

    begin();

    this->firstNameInput = new Fl_Input(X_INPUT_LOCATION, 15, 200, 25, "First name:");
    this->lastNameInput = new Fl_Input(X_INPUT_LOCATION, 45, 200, 25, "Last name:");
    this->yearInput = new Fl_Input(X_INPUT_LOCATION, 75, 60, 25, "Year:");
    this->conditionInput = new Fl_Input(X_INPUT_LOCATION, 105, 60, 25, "Condition:");
    this->priceInput = new Fl_Input(X_INPUT_LOCATION, 135, 60, 25, "Price:");

    this->setOKLocation(90, 170);
    this->setCancelLocation(170, 170);

    end();
}

//
// The instance handler when OK is invoked
//
// @precondition none
// @postcondition getCard() == baseball card object created from data user entered
//
void AddBaseballCardWindow::okHandler()
{
    string firstName = this->firstNameInput->value();
    string lastName = this->lastNameInput->value();

    BaseballCard::Condition cardCondition = this->determineAndSetConditionBasedOnUserInput();

    try
    {
        int year = this->determineAndSetYearBasedOnUserInput();
        int price = this->determineAndSetPriceBasedOnUserInput();
        this->pCard = new BaseballCard(firstName, lastName, year, cardCondition, price);
        this->hide();
    }
    catch (const char* message)
    {
        fl_message("%s", message);
    }


}

BaseballCard::Condition AddBaseballCardWindow::determineAndSetConditionBasedOnUserInput()
{
    string condition = this->conditionInput->value();
    condition = toUpperCase(condition);

    BaseballCard::Condition cardCondition = BaseballCard::Condition::UNKNOWN;

    if (condition == ENUM_TO_STR(POOR))
    {
        cardCondition = BaseballCard::Condition::POOR;
    }
    else if (condition == ENUM_TO_STR(GOOD))
    {
        cardCondition = BaseballCard::Condition::GOOD;
    }
    else if (condition == ENUM_TO_STR(EXCELLENT))
    {
        cardCondition = BaseballCard::Condition::EXCELLENT;
    }
    else if (condition == ENUM_TO_STR(MINT))
    {
        cardCondition = BaseballCard::Condition::MINT;
    }
    else if (condition == ENUM_TO_STR(PRISTINE))
    {
        cardCondition = BaseballCard::Condition::PRISTINE;
    }

    return cardCondition;
}

int AddBaseballCardWindow::determineAndSetYearBasedOnUserInput()
{
    string yearStr = this->yearInput->value();
    int year = toInt(yearStr, "Error converting year to an integer.");
    return year;
}


int AddBaseballCardWindow::determineAndSetPriceBasedOnUserInput()
{
    string priceStr = this->priceInput->value();
    int price = toInt(priceStr, "Error converting price to an integer.");
    return price;
}

//
// The instance handler when cancel is invoked
//
// @precondition none
// @postcondition getCard() == 0
//
void AddBaseballCardWindow::cancelHandler()
{
    if (this->pCard)
    {
        delete pCard;
    }

    this->pCard = 0;
    this->hide();
}

//
// Gets the new baseball card object based on what user entered
//
// @precondition none
// @postcondition none
//
// @return The baseball card object
//
BaseballCard* AddBaseballCardWindow::getCard() const
{
    return this->pCard;
}

//
// Destructor that cleans up all allocated resources for the window
//
AddBaseballCardWindow::~AddBaseballCardWindow()
{
    delete this->firstNameInput;
    delete this->lastNameInput;
    delete this->yearInput;
    delete this->conditionInput;
    delete this->priceInput;
}

}

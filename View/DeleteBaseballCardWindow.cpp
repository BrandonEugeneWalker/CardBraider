#include "DeleteBaseballCardWindow.h"

#include <iostream>
using namespace std;

namespace view {

//
// Constructs an delete card window creating and initializing all the widgets that will be displayed
//
// @precondition none
// @postcondition none
//
DeleteBaseballCardWindow::DeleteBaseballCardWindow() : OKCancelWindow(330, 90, "Card to delete")
{
    begin();

    this->lastNameInput = new Fl_Input(105, 15, 200, 25, "Last name:");
    this->setOKLocation(90, 50);
    this->setCancelLocation(170, 50);

    end();
}

//
// The instance handler when OK is invoked
//
// @precondition none
// @postcondition getLastName() == name user entered
//
void DeleteBaseballCardWindow::okHandler()
{
    this->lastName = this->lastNameInput->value();
    this->hide();
}

//
// The instance handler when Cancel is invoked
//
// @precondition none
// @postcondition getLastName() == ""
//
void DeleteBaseballCardWindow::cancelHandler()
{
    this->lastName = "";
    this->hide();
}

//
// Gets the last name entered
//
// @precondition none
// @postcondition none
//
// @return The last name entered
//
const string DeleteBaseballCardWindow::getLastName() const
{
    return this->lastName;
}

//
// Destructor that cleans up all allocated resources for the window
//
DeleteBaseballCardWindow::~DeleteBaseballCardWindow()
{
    delete this->lastNameInput;
}

}

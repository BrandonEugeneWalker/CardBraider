#ifndef DELETEBASEBALLCARDWINDOW_H
#define DELETEBASEBALLCARDWINDOW_H

#include "OKCancelWindow.h"

#include <Fl/Fl_Input.H>

#include <string>
using namespace std;

namespace view
{

//
// Defines the window where the user can enter the last name of a player card
//
class DeleteBaseballCardWindow : public OKCancelWindow
{
private:
    Fl_Input* lastNameInput;
    string lastName;

public:
    DeleteBaseballCardWindow();
    virtual ~DeleteBaseballCardWindow();

    void okHandler();
    void cancelHandler();

    const string getLastName() const;
};

}

#endif // DELETEBASEBALLCARDWINDOW_H

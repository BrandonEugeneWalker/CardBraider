#include "BaseballCardCollectionWindow.h"

#include "DeleteBaseballCardWindow.h"
#include "AddBaseballCardWindow.h"

#include <FL/fl_types.h>
#include <Fl/fl_draw.H>
#include <Fl/Fl_File_Chooser.H>

#define DIAGNOSTIC_OUTPUT

#ifdef DIAGNOSTIC_OUTPUT
#include <iostream>
#endif

namespace view
{

//
// Constructs a card collection window creating and initializing all the widgets that will be displayed
//
// @precondition width > 0 AND height > 0
// @postcondition none
//
// @param width The width of the window
// @param height The height of the window
// @param title The title to display for the window
//
BaseballCardCollectionWindow::BaseballCardCollectionWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    begin();

    this->sortingOutputLabel = new Fl_Output(100, 25, 0, 0, "Sort order:");
    createAndDisplaySortingRadioButtons();

    this->cardSummaryOutputLabel = new Fl_Output(270, 110, 0, 0, "Baseball card collection summary:");

    this->summaryOutputTextBuffer = new Fl_Text_Buffer();
    this->summaryOutputTextDisplay = new Fl_Text_Display(20, 120, 500, 200);
    this->summaryOutputTextDisplay->textfont(FL_COURIER);
    this->summaryOutputTextDisplay->buffer(summaryOutputTextBuffer);

    this->loadButton = new Fl_Button(120, 330, 70, 30, "Load");
    this->loadButton->callback(cbLoad, this);

    this->saveButton = new Fl_Button(200, 330, 70, 30, "Save");
    this->saveButton->callback(cbSave, this);

    this->addButton = new Fl_Button(280, 330, 70, 30, "Add");
    this->addButton->callback(cbAddCard, this);

    this->deleteButton = new Fl_Button(360, 330, 70, 30, "Delete");
    this->deleteButton->callback(cbDeleteCard, this);

    this->setSummaryText("Demo of how to set the summary text.");

    end();
}

//
// Overriding drawing of FL_Window so can draw a boxes around the sorting type radio buttons
// to make them appear in a group
//
void BaseballCardCollectionWindow::draw()
{
    Fl_Window::draw();
    fl_frame("AAAA", 20, 35, 500, 55);
}


void BaseballCardCollectionWindow::createAndDisplaySortingRadioButtons()
{
    const int X_RADIO_GROUP = 35;
    const int Y_RADIO_GROUP = 45;
    const int WIDTH_RADIO_GROUP = 400;
    const int HEIGHT_RADIO_GROUP = 100;

    this->sortingRadioGroup = new Fl_Group(X_RADIO_GROUP, Y_RADIO_GROUP, WIDTH_RADIO_GROUP, HEIGHT_RADIO_GROUP);

    this->sortingRadioGroup->begin();

    for (int i=0; i<SORTING_GROUPS; i++)
    {
        for (int j = 0; j<SORTING_TYPES_PER_GROUP; j++)
        {
            string label = this->sortingGroup[i] + " " + this->sortingTypes[j];
            int offset = (i*SORTING_TYPES_PER_GROUP) + j;
            this->radioSortingLabels[offset] = new string(label);
            this->sortingRadioGroupButton[offset] = new Fl_Round_Button(X_RADIO_GROUP + i*160, Y_RADIO_GROUP + j*25, 12, 12, radioSortingLabels[offset]->c_str());
            this->sortingRadioGroupButton[offset]->type(FL_RADIO_BUTTON);
            this->sortingRadioGroupButton[offset]->callback(cbSortingMethodChanged, this);
        }
    }

    this->sortingRadioGroup->end();

    this->sortingRadioGroupButton[0]->set();
    this->sortOrderSelection = NAME_ASCENDING;
}

//
// Callback when a radio button for the way to sort the cards has changed
//
// @precondition widget != 0 AND data != 0
// @postcondition CardCollectionWindow::getSortOrder() == value of new sort order selected
//
// @param widget The widget that initiatied the callback
// @param data Any data that was passed with the call back. In this instance, a pointer to the window.
//
void BaseballCardCollectionWindow::cbSortingMethodChanged(Fl_Widget* widget, void* data)
{
    BaseballCardCollectionWindow* window = (BaseballCardCollectionWindow*)data;
    window->sortingMethodChanged();

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Sorting method: " << window->getSortOrder() << endl;
#endif
}

//
// Callback that is an instance function of the window class to encapsulate function
//
// @precondition none
// @postcondition getSortOrder() == value of new sort order selected
//
void BaseballCardCollectionWindow::sortingMethodChanged()
{
    this->setSortOrderBasedOnSelection();
}

//
// Callback when the Load button is invoked
//
// @precondition widget != 0 AND data != 0
// @postcondition BaseballCardCollectionWindow::getFilename() == file selected by the user
//
// @param widget The widget that initiated the callback
// @param data Any data that was passed with the call back. In this instance, a pointer to the window.
//
void BaseballCardCollectionWindow::cbLoad(Fl_Widget* widget, void* data)
{
    BaseballCardCollectionWindow* window = (BaseballCardCollectionWindow*)data;
    window->promptUserForFilename(Fl_File_Chooser::SINGLE, "Card file to load");

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Filename selected: " << window->getFilename() << endl;
#endif

}

//
// Callback when the Load button is invoked
//
// @precondition type == Fl_File_Chooser type of SINGLE, MULTI, CREATE, or DIRECTORY
// @postcondition CardCollectionWindow::getFilename() == file selected by the user
//
// @param type Fl_File_Chooser type of SINGLE, MULTI, CREATE, or DIRECTORY
// @param title Title to display for the file chooser
//
// @return The filename the user selected
//
const string BaseballCardCollectionWindow::promptUserForFilename(int type, const string& title)
{
    Fl_File_Chooser chooser(".", "*", type, title.c_str());
    chooser.show();

    while(chooser.shown())
    {
        Fl::wait();
    }

    if (chooser.value() != 0)
    {
        this->selectedFilename = chooser.value();
    }
    else
    {
        this->selectedFilename = "";
    }

    return this->selectedFilename;
}

//
// Gets the filename the user selected when the file chooser was invoked
//
// @precondition none
// @postcondition none
//
// @return The filename the user had selected when the file chooser was invoked
//
const string BaseballCardCollectionWindow::getFilename() const
{
    return this->selectedFilename;
}

//
// Callback when the Save button is invoked
//
// @precondition widget != 0 AND data != 0
// @postcondition CardCollectionWindow::getFilename() == file selected by the user
//
// @param widget The widget that initiatied the callback
// @param data Any data that was passed with the call back. In this instance, a pointer to the window.
//
void BaseballCardCollectionWindow::cbSave(Fl_Widget* widget, void* data)
{
    BaseballCardCollectionWindow* window = (BaseballCardCollectionWindow*)data;
    window->promptUserForFilename(Fl_File_Chooser::CREATE, "Card file to save to");

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Filename selected: " << window->getFilename() << endl;
#endif

}

//
// Callback when the Add button is invoked
//
// @precondition widget != 0 AND data != 0
// @postcondition none
//
// @param widget The widget that initiatied the callback
// @param data Any data that was passed with the call back. In this instance, a pointer to the window.
//
void BaseballCardCollectionWindow::cbAddCard(Fl_Widget* widget, void* data)
{
    BaseballCardCollectionWindow* window = (BaseballCardCollectionWindow*)data; // TODO Currently, not used by may need to be used when adapt code

    AddBaseballCardWindow addCard;
    addCard.set_modal();
    addCard.show();

    while (addCard.shown())
    {
        Fl::wait();
    }

#ifdef DIAGNOSTIC_OUTPUT
    // TODO Remove or adapt code below, currently in for demo purposes
    if (addCard.getWindowResult() == OKCancelWindow::WindowResult::OK)
    {
        BaseballCard* pCard = addCard.getCard();
        cout << "OK" << endl;
        cout << "First name: " << pCard->getFirstName() << endl;
        cout << "Last name: " << pCard->getLastName() << endl;
        cout << "Year: " << pCard->getYear() << endl;
        cout << "Condition: " << pCard->getCondition() << endl;
        cout << "Price: " << pCard->getPrice() << endl;
    }
    else
    {
        cout << "Cancel or closed window." << endl;
    }
#endif

}

//
// Callback when the Delete button is invoked
//
// @precondition widget != 0 AND data != 0
// @postcondition none
//
// @param widget The widget that initiatied the callback
// @param data Any data that was passed with the call back. In this instance, a pointer to the window.
//
void BaseballCardCollectionWindow::cbDeleteCard(Fl_Widget* widget, void* data)
{
    BaseballCardCollectionWindow* window = (BaseballCardCollectionWindow*)data;

    DeleteBaseballCardWindow deleteCard;
    deleteCard.set_modal();
    deleteCard.show();

    while (deleteCard.shown())
    {
        Fl::wait();
    }

#ifdef DIAGNOSTIC_OUTPUT
    if (deleteCard.getWindowResult() == OKCancelWindow::WindowResult::OK)
    {
        cout << "OK - Player name: " << deleteCard.getLastName() << endl;
    }
    else
    {
        cout << "Cancel or closed window." << endl;
    }
#endif

}

//
// Determines and sets the sort order based on the radio button the user has selected.
//
// @preconditon none
// @postcondition getSortOrder() == sort order that user selected
//
void BaseballCardCollectionWindow::setSortOrderBasedOnSelection()
{
    for (int i=0; i<TOTAL_SORTING_METHODS; i++)
    {
        if (this->sortingRadioGroupButton[i]->value())
        {
            this->sortOrderSelection = (SortOrder)i;
        }
    }
}

//
// Sets the summary test to display in the card collection summary output
//
// @precondition none
// @postcondition none
//
// @param outputText The text to display
//
void BaseballCardCollectionWindow::setSummaryText(const string& outputText)
{
    this->summaryOutputTextBuffer->text(outputText.c_str());
}

//
// Gets the sort order the user has selected
//
// @precondition none
// @postcondition none
//
// @return The sort order the user has selected
//
BaseballCardCollectionWindow::SortOrder BaseballCardCollectionWindow::getSortOrder() const {
    return this->sortOrderSelection;
}

//
// Destructor that cleans up all allocated resources for the window
//
BaseballCardCollectionWindow::~BaseballCardCollectionWindow()
{
    for (int i=0; i<TOTAL_SORTING_METHODS; i++)
    {
        delete this->radioSortingLabels[i];
        delete this->sortingRadioGroupButton[i];
    }

    delete this->sortingOutputLabel;

    delete this->cardSummaryOutputLabel;
    this->summaryOutputTextDisplay->buffer(0);
    delete this->summaryOutputTextBuffer;
    delete this->summaryOutputTextDisplay;

    delete this->loadButton;
    delete this->saveButton;
    delete this->addButton;
    delete this->deleteButton;
}

}

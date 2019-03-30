
#include "BaseballCardCollectionWindow.h"
using namespace view;

int main (int argc, char ** argv)
{
    BaseballCardCollectionWindow mainWindow(540, 375, "A3: CardBraider by ...");
    mainWindow.show();

    int exitCode = Fl::run();
    return exitCode;
}

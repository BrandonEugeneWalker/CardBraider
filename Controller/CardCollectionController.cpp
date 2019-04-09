#include "CardCollectionController.h"

#define DIAGNOSTIC_OUTPUT

#ifdef DIAGNOSTIC_OUTPUT
#include <iostream>
#endif

namespace controller
{

CardCollectionController::CardCollectionController()
{
    this -> braidedCardList = new CardBraider();
}

CardCollectionController::~CardCollectionController()
{
    delete this -> braidedCardList;
}

CardBraider* CardCollectionController::getCardBraider()
{
    return this -> braidedCardList;
}

void CardCollectionController::addCard(BaseballCard* card)
{
#ifdef DIAGNOSTIC_OUTPUT
    cout << "Inside Controller addCard." << endl;
#endif // DIAGNOSTIC_OUTPUT
    if (card == nullptr)
    {
        throw invalid_argument("the card cannot be nullptr");
    }
    CardNode* newNode = new CardNode(card);
    this -> braidedCardList -> addNode(newNode);
}

bool CardCollectionController::deleteCard(string name)
{
#ifdef DIAGNOSTIC_OUTPUT
    cout << "Inside Controller deleteCard." << endl;
#endif // DIAGNOSTIC_OUTPUT
    return this -> braidedCardList -> deleteNode(name);
}

string CardCollectionController::buildOutput(int order)
{
#ifdef DIAGNOSTIC_OUTPUT
    cout << "Inside Controller buildOutput." << endl;
#endif // DIAGNOSTIC_OUTPUT
    OutputBuilder newBuilder;
    CardNode* headNode;
    string results;
    if (order == 0)
    {
        headNode = this -> braidedCardList -> getNameHead();
        results = newBuilder.buildOutput(true, CardBraider::BraidType::NAME, headNode);
    }
    else if(order == 1)
    {
        headNode = this -> braidedCardList -> getNameHead();
        results = newBuilder.buildOutput(false, CardBraider::BraidType::NAME, headNode);
    }
    else if(order == 2)
    {
        headNode = this -> braidedCardList -> getYearHead();
        results = newBuilder.buildOutput(true, CardBraider::BraidType::YEAR, headNode);
    }
    else if(order == 3)
    {
        headNode = this -> braidedCardList -> getYearHead();
        results = newBuilder.buildOutput(false, CardBraider::BraidType::YEAR, headNode);
    }
    else if(order == 4)
    {
        headNode = this -> braidedCardList -> getConditionHead();
        results = newBuilder.buildOutput(true, CardBraider::BraidType::CONDITION, headNode);
    }
    else if(order == 5)
    {
        headNode = this -> braidedCardList -> getConditionHead();
        results = newBuilder.buildOutput(false, CardBraider::BraidType::CONDITION, headNode);
    }
    return results;

}

void CardCollectionController::addCardsFromCollection(vector<BaseballCard*> cards)
{

#ifdef DIAGNOSTIC_OUTPUT
    cout << "Inside Controller Add All:" << endl;
#endif

    for (BaseballCard* currentCard : cards)
    {
        if (currentCard != nullptr)
        {
            this -> addCard(currentCard);
        }
    }
}

void CardCollectionController::resetBraidedList()
{
#ifdef DIAGNOSTIC_OUTPUT
    cout << "Inside Controller resetBraidedList." << endl;
#endif // DIAGNOSTIC_OUTPUT
    delete this -> braidedCardList;
    this -> braidedCardList = new CardBraider();
}

void CardCollectionController::saveBraidedList(string fileName)
{
    FileWriter fileWriter;
    fileWriter.writeNodesToFile(this -> braidedCardList -> getNameHead(), fileName);
}


}

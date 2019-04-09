#ifndef FUNCTIONPOINTERUTILS_H
#define FUNCTIONPOINTERUTILS_H

#include "CardNode.h"
#include "CardBraider.h"
using namespace model;

static CardNode* getNextNode(CardNode* node, CardBraider::AddType type);

static void setNextNode(CardNode* node, CardBraider::AddType type);

static void getBraidHead(CardBraider* braider, CardBraider::AddType type);

static void setBraidHead(CardBraider* braider, CardBraider::AddType type);


#endif // FUNCTIONPOINTERUTILS_H

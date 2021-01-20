#ifndef HELPERS_H
#define HELPERS_H
#include <iostream>
#include <vector>
#include <fstream>
#include "classes.h"

using namespace std;

void AddIdPrice(int* price_list, char id, int price);
void InitIdPriceList(int* price_list);
void InitPromotionRuleList(vector<PromotionRule>& promotion_rule_list);
void ReadCart(int* cart, char* cart_filename);
int CalculatePrice(vector<PromotionRule>& promotion_rule_list, const int* id_price_list, int* cart);

#endif

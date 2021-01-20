#include <iostream>
#include <vector>
#include "helpers.h"


using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2)
	{	cout << "Usage: " << argv[0] << " <input file>" << endl;
		exit(0);
	}

	int id_price_list[ID_COUNT] = {0}; // list of prices for each ID
	int cart[ID_COUNT] = {0}; // list of prices for each ID
	vector<PromotionRule> promotion_rule_list; // list of promotion rules

	InitIdPriceList(id_price_list);

	InitPromotionRuleList(promotion_rule_list);

	ReadCart(cart, argv[1]);

	int total_price = CalculatePrice(promotion_rule_list, id_price_list, cart);
	
	cout << "Total Price: " << total_price << endl;
	return 0;
}

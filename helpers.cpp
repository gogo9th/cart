#include "helpers.h"

using namespace std;

/* An internal helper function to add a price for a given id 
   We assume that all IDs are upper-case English characters */
void AddIdPrice(int* price_list, char id, int price)
{
   price_list[toupper(id) - 'A'] = price;
}

/* Create the list of prices for each ID */
void InitIdPriceList(int* price_list)
{
   AddIdPrice(price_list, 'A', 50);
   AddIdPrice(price_list, 'B', 30);
   AddIdPrice(price_list, 'C', 20);
   AddIdPrice(price_list, 'D', 15);
}


/* Create the list of active promotion rules */
void InitPromotionRuleList(vector<PromotionRule>& promotion_rule_list)
{
   PromotionRule promotion_rule;

   /* 3 of A's for 130 */
   promotion_rule.AddIdCount('A', 3);
   promotion_rule.SetValue(130);
   promotion_rule.SetType(PRICE);
   promotion_rule_list.push_back(promotion_rule);
	promotion_rule.Reset();

   /* 2 of B's for 45 */
   promotion_rule.AddIdCount('B', 2);
   promotion_rule.SetValue(45);
   promotion_rule.SetType(PRICE);
   promotion_rule_list.push_back(promotion_rule);
	promotion_rule.Reset();

   /* C & D for 30 */
   promotion_rule.AddIdCount('C', 1);
   promotion_rule.AddIdCount('D', 1);
   promotion_rule.SetValue(30);
   promotion_rule.SetType(PRICE);
   promotion_rule_list.push_back(promotion_rule);
	promotion_rule.Reset();

}

/* Save the cart's status in the cart array */
void ReadCart(int* cart, char* cart_filename)
{
   ifstream cart_file; // file reader that contains the cart

   cart_file.open(cart_filename);
   if (cart_file.fail())
   {
      cout << "Could not open file " << cart_filename << endl;
		cout << endl;
      exit(0);
   }

   string myText;
   getline(cart_file, myText);
   cart_file.close();

	/* count only alphabets and they are case-insensitive */
   for (int i = 0; i < myText.length(); i++)
   {  char nextChar = myText[i];
      if (nextChar < 'A' || (nextChar > 'Z' && nextChar < 'a') || nextChar > 'z')
         continue;
      cart[toupper(nextChar) - 'A']++;
   }
}

/* Calculate the final price of the cart after applying promotions */
int CalculatePrice(vector<PromotionRule>& promotion_rule_list, const int* id_price_list, int* cart)
{
   int total_price = 0;

/*for (int i = 0; i < promotion_rule_list.size(); i++)
{	PromotionRule promotion_rule = promotion_rule_list[i];
	for (int j = 0; j < ID_COUNT; j++)
		printf("%c: %d\n", j + 'A', promotion_rule.id_count_list[j]);
	cout << endl;
}
*/
	/* apply promotions */
   for (int i = 0; i < promotion_rule_list.size(); i++)
   {  PromotionRule* promotion_rule_ptr = &(promotion_rule_list[i]);
//printf("Test Rule\n");
      while (promotion_rule_ptr->ApplyRule(cart))
      {  
			int value = promotion_rule_ptr->GetValue();
         int type = promotion_rule_ptr->GetType();
printf("Rule %d: %d\n", i, value);
         switch (type)
         {  case PRICE:
               total_price += value;
					break;
            case PERCENT: // future implementation 
            case DISCOUNT: // future implementation
            default:
               cout << "Unknown Type: " << type << endl;
					exit(0);
         }
      }
   }

	/* remaining prices after promotions */
   for (int i = 0; i < ID_COUNT; i++)
   {	total_price += (id_price_list[i] * cart[i]);
if (cart[i]) printf("Add %d * %d = %d\n", id_price_list[i], cart[i], id_price_list[i] * cart[i]); 
	}
   return total_price;
}


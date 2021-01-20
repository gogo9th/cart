#include <iostream>

#ifndef CLASSES_H
#define CLASSES_H

#include <vector>

using namespace std;


enum PromotionType {
   PERCENT,    // % for the price
   PRICE,      // numeric final price
   DISCOUNT    // this much discount
};

#define ID_COUNT 'Z' - 'A' + 1 // offset for the ID array. The compiler will automatically


/* This represents the promotion rule slot */
class PromotionRule
{
public:
   int id_count_list[ID_COUNT] = {0}; // contains each ID's count in the rule
   int value; // the value in either price, % or discount 
   PromotionType type; // represents the type, either price, % or discount

	/* add one id & its count to the id_count_list array */
   void AddIdCount(char id, int count)
   {
      id_count_list[toupper(id) - 'A'] = count;
   }

	/* set the value */
   void SetValue(int v)
   {  value = v;
   }

	/* set the type */
   void SetType(PromotionType t)
   {
      type = t;
   }

	/* apply this rule to the cart and return true if the promotion is applicable */
   bool ApplyRule(int* id_price_list)
   {
      for (int i = 0; i < ID_COUNT; i++)
      {  
			if (id_price_list[i] < id_count_list[i])
            return false;
		}
      for (int i = 0; i < ID_COUNT; i++)
         id_price_list[i] -= id_count_list[i];
      return true;
   }

	/* get the value */
   int GetValue()
   {
      return value;
   }

	/* get the type */
   PromotionType GetType()
   {
      return type;
   }

	/* reset the id_count_list to zero */
	void Reset()
	{	
		fill(id_count_list, id_count_list + ID_COUNT * sizeof(int), 0);
		value = 0;
	}
};

#endif


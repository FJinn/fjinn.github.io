// product is concrete subject

#include "Product.h"

void Product::ChangePrice(float price)
{
	Notify(price);
}

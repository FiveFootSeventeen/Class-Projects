/*********************************************************************
** Author: Jacob Leno
** Date: 08/12/17
** Description: Assignment 10 - This is the class implementation file for the
** Product class, it contains the member functions for the class.
*********************************************************************/

#include "Product.hpp"


Product::Product(std::string idCodeIn, std::string titleIn, std::string descriptionIn, double priceIn, int quantityAvailableIn)
{											//Constructor for Product class
	idCode = idCodeIn;
	title = titleIn;
	description = descriptionIn;
	price = priceIn;
	quantityAvailable = quantityAvailableIn;
}

std::string Product::getIdCode()			//Return ID code for Product
{
	return idCode;
}

std::string Product::getTitle()				//Return title for Product
{
	return title;
}

std::string Product::getDescription()		//Return description for Product
{
	return description;
}

double Product::getPrice()					//Return price for Product
{
	return price;
}

int Product::getQuantityAvailable()			//Return quantity available for Product
{
	return quantityAvailable;
}

void Product::decreaseQuantity()			//Decrease quantity available in Product
{
	quantityAvailable -= 1;
}

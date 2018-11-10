/*********************************************************************
** Author: Jacob Leno
** Date: 08/12/17
** Description: Assignment 10 - This is the class implementation file for 
** the Customer class, it contains the member functions for the class.
*********************************************************************/

#include "Customer.hpp"
#include <string>
#include <vector>


Customer::Customer(std::string nameIn, std::string accountIDIn, bool premiumMemberIn) //Constructor for Customer class
{
	name = nameIn;
	accountID = accountIDIn;
	premiumMember = premiumMemberIn;
}

std::string Customer::getAccountID()					//Return account ID for Customer
{
	return accountID;
}

std::vector<std::string> Customer::getCart()			//Return cart for Customer
{
	return cart;
}

void Customer::addProductToCart(std::string idCode)		//Add product to customer's cart
{
	cart.push_back(idCode);
}

bool Customer::isPremiumMember()						//Returns true if customer is a premium member, false if otherwise
{
	if (premiumMember)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Customer::emptyCart()								//Clear the customer's cart
{
	cart.clear();
}
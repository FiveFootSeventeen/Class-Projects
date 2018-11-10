/*********************************************************************
** Author: Jacob Leno
** Date: 08/12/17
** Description: Assignment 10 - This is the class implementation file for 
** the Store class, it contains the member functions for the class.
*********************************************************************/

#include "Store.hpp"
#include <string>
#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;


void Store::addProduct(Product* prodAdd)		//Add a new Product to inventory vector
{
	inventory.push_back(prodAdd);
}

void Store::addMember(Customer* custAdd)		//Add a new Customer to member vector
{
	members.push_back(custAdd);
}


Product* Store::getProductFromID(string cartID)				//Return pointer to Product if it is in the inventory
{															//return NULL if not.
	for (unsigned int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i]->getIdCode() == cartID)
		{
			return inventory[i];
		}
	}
	return NULL;
}

Customer* Store::getMemberFromID(string memberID)			//Return pointer to Customer if it is in members
{															//return NULL if not
	for (unsigned int i = 0; i < members.size(); i++)
	{
		if (members[i]->getAccountID() == memberID)
		{
			return members[i];
		}
	}
	return NULL;
}

void Store::productSearch(string searchStr)			//Takes a single word as a string and searches the product's title and
{													//description for that word. If it is present it will print that product's
	string lowerSearch = "";						//title, ID code, price, and description.
	for (unsigned int i = 0; i < searchStr.length(); i++)
	{
		lowerSearch += tolower(searchStr[i]);
	}

	for (unsigned int i = 0; i < inventory.size(); i++)
	{
		string tempTitle = inventory[i]->getTitle();
		string tempDescription = inventory[i]->getDescription();
		string tempString = "";

		for (unsigned int j = 0; j < tempTitle.length(); j++)
		{
			tempString += tolower(tempTitle[j]);
		}
		for (unsigned int k = 0; k < tempDescription.length(); k++)
		{
			tempString += tolower(tempDescription[k]);
		}

		if (tempString.find(lowerSearch) != string::npos)
		{
			cout << tempTitle << endl;
			cout << "ID code : " << inventory[i]->getIdCode() << endl;
			cout << "price : $" << inventory[i]->getPrice() << endl;
			cout << tempDescription << endl << endl;
		}
	}
}

void Store::addProductToMemberCart(std::string productID, std::string memberID)		//Add a product to member's cart if found in inventory.
{																					//If product or member are not found display that on screen. 	
	bool addContinue = true;														//If product is not in stock display that on screen
	if (getMemberFromID(memberID) == NULL)
	{
		cout << "Member #" << memberID << " not found." << endl;
		addContinue = false;
	}
	if (getProductFromID(productID) == NULL)
	{
		cout << "Product #" << productID << " not found." << endl;
		addContinue = false;
	}
	if (addContinue == true && getProductFromID(productID)->getQuantityAvailable() <= 0)
	{
		cout << "Sorry product #" << productID << " is currently out of stock." << endl;
	}
	else
	{
		getMemberFromID(memberID)->addProductToCart(productID);
	}
}

void Store::checkOutMember(std::string memberID)		//Check out member if ID is found. If member is premium do not charge for shipping.
{														//If member is not premium add 7% for shipping. Print out the items in the cart,
	if (getMemberFromID(memberID) == NULL)				//the subtotal, shipping cost, and total.
	{
		cout << "Member #" << memberID << " not found." << endl;
	}
	else
	{
		double subTotal = 0.0;

		for (unsigned int i = 0; i < getMemberFromID(memberID)->getCart().size(); i++)
		{
			Product* prodPtr = getProductFromID(getMemberFromID(memberID)->getCart()[i]);	//Create a pointer to each product in cart for
																							//more streamlined and less confusing code.
				
			if (prodPtr->getQuantityAvailable() <= 0)
			{
				cout << "Sorry, product #" << prodPtr->getIdCode() << ", \"" 
					<< prodPtr->getTitle() << "\" is no longer available." << endl;
			}
			else
			{
				cout << prodPtr->getTitle() << " - $" << prodPtr->getPrice() << endl;
				subTotal += prodPtr->getPrice();
				prodPtr->decreaseQuantity();
			}
		}
		
		if (getMemberFromID(memberID)->getCart().size() <= 0)
		{
			cout << "There are no items in the cart" << endl;
		}
		else
		{
			cout << "Subtotal: $" << subTotal << endl;
			if (getMemberFromID(memberID)->isPremiumMember() == true)
			{
				cout << "Shipping Cost: $0" << endl;
				cout << "Total $" << subTotal << endl << endl;
			}
			else
			{
				cout << "Shipping Cost: $" << (subTotal * 0.07) << endl;
				cout << "Total $" << (subTotal + (subTotal * 0.07)) << endl << endl;
			}
		}
		getMemberFromID(memberID)->emptyCart();	//Clear contents of cart
	}
}
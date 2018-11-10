/*********************************************************************
** queueStack Functions
** Author: Jacob Leno
** Date: 11/25/17
** Description: Function implementations for the queueStack functions
*********************************************************************/

#include "queueStack.hpp"

/*********************************************************************
** queueMenue function: Called from main, begins the buffer simulation.
** First the user is asked for the number of rounds and two numbers
** that represent percentages. The function then sends these
** numbers to beginQueue
*********************************************************************/
void queueMenu()
{
	int percentPush, percentPop, rounds;
	int yorn;
	unsigned seed = int(time(0));
	srand(seed);
	std::queue<int> intQueue;

	do
	{
		if (!intQueue.empty()) { emptyQueue(intQueue); }		//If the queue has numbers in it, empty it
		rounds = intMenu("How many rounds should the simulation iterate for?", false, 100);
		percentPush = intMenu("Enter an integer 1-100\n"
			"This number represents the chance to put a random number"
			"\nat the end of the buffer: ", false, 100);
		percentPop = intMenu("Enter an integer 1-100\n"
			"This number represents the chance to remove a random number"
			"\nfrom the beginning of the buffer: ", false, 100);
		beginQueue(rounds, percentPush, percentPop, intQueue);
		displayText("Press enter to continue");
		std::cin.ignore(INT_MAX, '\n');					//Wait for the user to press enter
		yorn = intMenu("Would you like to run the program again?", true);
	} while (yorn != 2);

}

/*********************************************************************
** beginQueue function: Pushes a random number onto the queue if the 
** random number generated is lower or equal to the user number. Pops
** a number off the queue if the number generated is lower or equal to
** the user number. Round information is printed for each round.
*********************************************************************/

void beginQueue(int rounds, int percentPush, int percentPop, std::queue<int> &intQueue)
{
	int randomPop, randomPush, N;
	int buffLength;
	double averageLength;

	for (int i = 1; i <= rounds; i++)
	{
		randomPop = rand() % 100 + 1,
		randomPush = rand() % 100 + 1,
		N = rand() % 1000 + 1;

		cout << endl << "Round: " << i << endl;						//For TA testing purposes
		cout << "randomPush: " << randomPush << endl;
		cout << "randomPop: " << randomPop << endl;
		if (randomPush <= percentPush)
		{
			cout << "Number pushed: " << N << endl;					//For TA testing purposes
			intQueue.push(N);
		}
		if (randomPop <= percentPop && !intQueue.empty())
		{
			cout << "Number popped: " << intQueue.front() << endl;	//For TA testing purposes
			intQueue.pop();
		}

		displayValues(intQueue);			//Display values in the queue
		if (i == 1)
		{
			averageLength = intQueue.size();
			buffLength = intQueue.size();
			displayLengths(buffLength, averageLength);			//Its the first round, set the average length and buffLength
		}
		else
		{
			buffLength = intQueue.size();									//Update buffLength
			averageLength = (averageLength * (i - 1) + buffLength) / i;		//Get the average length using previous averageLength and current buffLength			
			displayLengths(buffLength, averageLength);
		}
	}

}

/*********************************************************************
** emptyQueue function: Empty the queue of its contents
*********************************************************************/

void emptyQueue(std::queue<int> &intQueue)
{
	while (!intQueue.empty())
	{
		intQueue.pop();
	}
}

/*********************************************************************
** displayLengths function:	Display the current length and the average
*********************************************************************/

void displayLengths(int current, double average)
{
	cout << "The current length of the buffer is " << current << endl;
	cout << "The average length of the buffer is " << fixed << showpoint << setprecision(2) << average << endl;
}

/*********************************************************************
** displayValues function:	Display the values in the buffer
*********************************************************************/

void displayValues(std::queue<int> tempQueue)
{
	int count = 0;
	cout << "Values in the buffer: " << endl;
	while (!tempQueue.empty())
	{
		cout << tempQueue.front();
		tempQueue.pop();
		count ++;
		if (count % 10 == 0) { cout << endl; }	//Create a newline every 10 values or else tab over
		else { cout << "\t"; }
	}
	cout << endl;
}

/*********************************************************************
** stackMenu function: Get the string from the user and send it to 
** beginStack to create the palindrome
*********************************************************************/

void stackMenu()
{
	int choice;
	std::string userString;

	do
	{
		userString = getString("Please enter text and I will create a palindrome: ");
		beginStack(userString);
		displayText("Press enter to continue");
		std::cin.ignore(INT_MAX, '\n');
		choice = intMenu("Would you like to run the program again?", true);
		userString.clear();
	} while (choice != 2);

}

/*********************************************************************
** beginStack function: Accepts a string that it iterates through pushing
** each character onto a stack. Then the values are pushed off the stack
** and appended to the string in reverse order.
*********************************************************************/

void beginStack(std::string userString)
{
	std::stack<char, std::list<char>> palindromeStack;

	for (unsigned i = 0; i < userString.length(); i++)
	{
		palindromeStack.push(userString[i]);		//Push each value in the string onto the stack
	}
	 int length = palindromeStack.size();
	for (int i = 0; i < length; i++)
	{
		cout << "Popping: " << palindromeStack.top() << endl;
		userString += palindromeStack.top();		//Append the values in reverse order onto the original string
		palindromeStack.pop();
	}
	displayPalindrome(userString);
}

/*********************************************************************
** displayPalindrome function: Display the palindrome
*********************************************************************/

void displayPalindrome(std::string palindrome)
{
	cout << "The new palindrome is:" << endl << palindrome << endl;
}
/*********************************************************************
** Class Name: University
** Author: Jacob Leno
** Date: 10/19/17
** Description: This is the implementation file for the University class
** this class defines the member variables for University objects. Within
** this class are the main functions for running the OSU Info System
** program. To start the program call the menu() on a University object
** from main.
*********************************************************************/

#include "University.hpp"


/*********************************************************************
** Default Constructor: Loads data from file when University object is
** created and stores the number of buildings and people in appropriate
** variables.
*********************************************************************/
University::University()
{
	loadData();
	buildings = buildingVector.size();
	people = personVector.size();
}

/*********************************************************************
**menu Function: Call this function on a University object from main
** to start the program. This function retrieves info from the user
** and calls the appropriate functions.
*********************************************************************/

void University::menu()
{
	int choice = 0;

	do {
		choice = intMenu("1. Print building information" \
					    "\n2. Print student and instructor information" \
						"\n3. Choose a person to do work" \
						"\n4. Add a Person to the database" \
						"\n5. Add a Building to the database" \
						"\n6. Quit", \
						false, 6, 1, true, \
						"Welcome to the " + name + " Information System \
						\nPlease make a selection");

		if (choice == 1) { printBuildings(); }
		if (choice == 2) { printPeople(); }
		if (choice == 3) { doWork(); }
		if (choice == 4) { addPeople(); }
		if (choice == 5) { addBuildings(); }
	} while (choice != 6);

	storeData(); //Save data when user quits
}

/*********************************************************************
**doWork Function: This function will call the do_work function in one
** of the student or instructor member functions depending on the number
** of the person chosen.
*********************************************************************/

void University::doWork()
{
	int choice;
	printPeople(true);// Print a list of the people available to do work w/ numbers
	choice = intMenu("Please enter the number of the person you would like to do work", false, people);
	personVector[(choice - 1)]->do_work();
	cout << "Please press enter to return to the main menu . . ." << endl;
	cin.ignore(INT_MAX, '\n');
}

/*********************************************************************
**storeData function: This function stores the data both the personVector
** and buildingVector by writing the information to a data file. All objects
** that contain pointers are serialized before stored.
*********************************************************************/

void University::storeData()
{
	outFile.open("OSU_Data.dat", std::ios::binary);

	if (!outFile)
	{
		cout << "Failed to store data!" << endl;
	}

	for (shared_ptr<Person> people : personVector)	//Loop through the entire vector
	{

		type = people->getType();					//Initialize the temp variables
		tempAge = people->getAge();
		if (people->getType() == 1)					//Check to see if the object is an Instructor
		{
			tempName = people->getName();
			length = tempName.length();
			tempRating = std::static_pointer_cast<Instructor>(people)->getRating();
			outFile.write(reinterpret_cast<char *>(&type), sizeof(type));
			outFile.write(reinterpret_cast<char *>(&tempRating), sizeof(tempRating));
			outFile.write(reinterpret_cast<char *>(&tempAge), sizeof(tempAge));
			outFile.write(reinterpret_cast<char *>(&length), sizeof(int));		   //Serialize the string object by storing its length first
			outFile.write(tempName.data(), length);								   //Now store the string as a char array
		}
		if (people->getType() == 2)					//Check to see if the object is a Student
		{
			tempGPA = std::static_pointer_cast<Student>(people)->getGPA();
			tempName = people->getName();
			length = tempName.length();
			outFile.write(reinterpret_cast<char *>(&type), sizeof(type));
			outFile.write(reinterpret_cast<char *>(&tempGPA), sizeof(tempGPA));
			outFile.write(reinterpret_cast<char *>(&tempAge), sizeof(tempAge));
			outFile.write(reinterpret_cast<char *>(&length), sizeof(int));			//Serialize the string object by storing its length first
			outFile.write(tempName.data(), length);									//Now store the string as a char array
		}
	}
	for (shared_ptr<Building> bldg : buildingVector)		//Loop through the entire vector
	{
		type = bldg->getType();
		tempSize = bldg->getSize();
		tempAddress = bldg->getAddress();
		tempName = bldg->getName();
		outFile.write(reinterpret_cast<char *>(&type), sizeof(type));
		outFile.write(reinterpret_cast<char *>(&tempSize), sizeof(tempSize));
		length = tempAddress.length();												//Get the length of the string
		outFile.write(reinterpret_cast<char *>(&length), sizeof(int));				//Store the length of the string object first
		outFile.write(tempAddress.data(), length);									//Now store the string as a char array
		length = tempName.length();													//repeat for name variable
		outFile.write(reinterpret_cast<char *>(&length), sizeof(int));
		outFile.write(tempName.data(), length);
	}

	outFile.close();
}

/*********************************************************************
**loadData function: This function loads the data for the program from a 
**binary file. It deserializes any previously serialized objects and stores
**them in the appropriate vector as DA object pointers.
*********************************************************************/

void University::loadData()
{
	static char buffer[256];

	inFile.open("OSU_Data.dat", std::ios::binary);

	if (!inFile)
	{
		cout << "Failed to load data!" << endl;
	}

	inFile.read(reinterpret_cast<char *>(&type), sizeof(type)); //Read the first type of object stored

	while (!inFile.eof())
	{
		if (type == 1)		//Instructor object
		{
			inFile.read(reinterpret_cast<char *>(&tempRating), sizeof(tempRating));
			inFile.read(reinterpret_cast<char *>(&tempAge), sizeof(tempAge));
			inFile.read(reinterpret_cast<char*>(&length), sizeof(int));			//First read the length
			inFile.read(buffer, length);										//Then read the c-string into a buffer
			buffer[length] = '\0';												//add the character
			tempName = buffer;													//convert back to string
			personVector.emplace_back(new Instructor(tempRating, tempName, tempAge));		//Create a new Instructor object in the person vector

		}
		if (type == 2)		//Student object
		{
			inFile.read(reinterpret_cast<char *>(&tempGPA), sizeof(tempGPA));
			inFile.read(reinterpret_cast<char *>(&tempAge), sizeof(tempAge));
			inFile.read(reinterpret_cast<char *>(&length), sizeof(int));		//First read the length
			inFile.read(buffer, length);										//Then read the c-string into a buffer
			buffer[length] = '\0';												//add the character
			tempName = buffer;													//convert back to string
			personVector.emplace_back(new Student(tempGPA, tempName, tempAge));				//Create a new Student object in the person vector
		}
		if (type == 3)		//Building object
		{
			inFile.read(reinterpret_cast<char *>(&tempSize), sizeof(tempSize));
			inFile.read(reinterpret_cast<char *>(&length), sizeof(int));		//First read the length
			inFile.read(buffer, length);										//Then read the c-string into a buffer
			buffer[length] = '\0';												//add the character
			tempAddress = buffer;												//convert back to string
			inFile.read(reinterpret_cast<char *>(&length), sizeof(int));		//repeat
			inFile.read(buffer, length);
			buffer[length] = '\0';
			tempName = buffer;
			buildingVector.emplace_back(new Building(tempSize, tempAddress, tempName));		//Create a new Building object in the building vector
		}
		inFile.read(reinterpret_cast<char *>(&type), sizeof(type));
	};
		inFile.close();
}

/*********************************************************************
**addBuildings: This function is used to add buildings to the building 
**vector
*********************************************************************/

void University::addBuildings()
{
	int size;
	std::string name, address;

	cout << "What is the name of the building?" << endl;;
	getline(cin, name);
	cout << "What is the building's address?" << endl;;
	getline(cin, address);
	size = intMenu("What is the size of the building in sqft?: ", false, 1000000);

	buildingVector.emplace_back(new Building(size, address, name));			//Create a new building object in the buildingVector
	buildings = buildingVector.size();			//Update the buildings variable
	cout << "Please press enter to return to the main menu . . ." << endl;
	cin.ignore(INT_MAX, '\n');
}

/*********************************************************************
**addPeople: This function is used to add Instructor or Student objects
**to the person vector
*********************************************************************/

void University::addPeople()
{
	int age, type;
	std::string name;
	double GPA, rating;

	type = intMenu("What type of person is this?\n1. Student\n2. Instructor", false, 2, 1);
	if (type == 1)
	{
		cout << "Please enter the name of the student:" << endl;
		getline(cin, name);
		age = intMenu("Please enter the age of the student:", false, 120, 16);
		GPA = decMenu("Please enter the student's GPA:", 4.0, 0.0, 1);
		personVector.emplace_back(new Student(GPA, name, age));					//Create a new Student object in the personVector
	}
	else
	{
		cout << "Please enter the name of the instructor:" << endl;
		getline(cin, name);
		age = intMenu("Please enter the age of the instructor:", false, 120, 20);
		rating = decMenu("Please enter the instructor's rating:", 5.0, 0.0, 1);
		personVector.emplace_back(new Instructor(rating, name, age));			//Create a new Instructor object in the personVector
	}
	cout << "Please press enter to return to the main menu . . ." << endl;
	cin.ignore(INT_MAX, '\n');
	people = personVector.size();		//Update the people variable
	
}

/*********************************************************************
**printBuildings: This function prints all the buildings in buildingVector
*********************************************************************/

void University::printBuildings()
{
	for (int i = 0; i < buildings; i++)
	{
		cout << endl << "Building name: " << buildingVector[i]->getName() << endl;
		cout << "Building address: " << buildingVector[i]->getAddress() << endl;
		cout << "Building size: " << buildingVector[i]->getSize() << "sqft" << endl;
	}
	cout << "Please press enter to return to the main menu . . ." << endl;
	cin.ignore(INT_MAX, '\n');
}

/*********************************************************************
** printPeople: This function prints all the Instructor and Student
** objects in the personVector. It has the option of print them with
** numbers if it is sent a value of true.
*********************************************************************/

void University::printPeople(bool withNumbers)
{

	for (int i = 0; i < people; i++)
	{

		if (personVector[i]->getType() == 1)
		{
			if (withNumbers) { cout << "Person: " << (i + 1) << endl; }
			cout << "Instructor name: " << personVector[i]->getName() << endl;
			cout << "Instructor age: " << personVector[i]->getAge() << endl;
			cout << "Rating: " << std::fixed << std::showpoint << std::setprecision(1) << \
				std::static_pointer_cast<Instructor>(personVector[i])->getRating() << endl << endl;
		}
		if (personVector[i]->getType() == 2)
		{
			if (withNumbers) { cout << "Person: " << (i + 1) << endl; }
			cout << "Student name: " << personVector[i]->getName() << endl;
			cout << "Student age: " << personVector[i]->getAge() << endl;
			cout << "GPA: " << std::fixed << std::showpoint << std::setprecision(1) << \
				std::static_pointer_cast<Student>(personVector[i])->getGPA() << endl << endl;
		}
	}

	if (withNumbers == false) //Let the user press enter before displaying the menu
	{ 
		cout << "Please press enter to return to the main menu . . ." << endl;
		cin.ignore(INT_MAX, '\n');
	} 

}

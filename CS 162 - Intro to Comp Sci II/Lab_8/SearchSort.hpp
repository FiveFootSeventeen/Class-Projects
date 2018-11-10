/*********************************************************************
** Class Name: SearchSort
** Author: Jacob Leno
** Date: 11/16/17
** Description: Header file for the SearchSort class
*********************************************************************/
#ifndef SEARCHSORT_HPP
#define SEARCHSORT_HPP

#include "menu.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using std::vector;
using std::fstream;
using std::string;
using std::cout;
using std::endl;

class SearchSort
{
protected:
	//Variables
	static const int SIZE = 4;
	const string PROGNAMES[SIZE] = { "no_zero.txt", "early.txt", "middle.txt", "end.txt" };
	string userNames[SIZE];
	vector<int> noZero, early, middle, end;
	vector<int>* listVector[SIZE] = { &noZero, &early, &middle, &end };
	fstream inOutFile;

	//Functions
	void vectorIn(vector<int>&, string, fstream&);
	void vectorOut(vector<int>&, string, fstream&);
	int linearSearch(vector<int>, int);
	int binarySearch(vector<int>, int);
	void quickSort(vector<int>&, int, int);
	void swap(int &, int &);
	int partition(vector<int>&, int, int);
	void printVector(vector<int>, int);

public:
	//Functions
	SearchSort() {}
	void sortFile();
	const string* getUnsorted() { return PROGNAMES; }
	string* getSorted() { return userNames; }
	void startBinary(const string[]);
	void startLinear(const string[]);
	void loadUnsortedData();
	bool loadSortedData();
};
#endif

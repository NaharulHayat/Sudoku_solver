/* Victoria Johnston ~ 5th March 2015
main.cpp
This program reads in a sudoku from the file entered by the user and prints the solved sudoku. */

#include <iostream>
#include <vector>
#include "sudoku.h"
using namespace std;

int main() 
{
	// Get name of sudoku file
	string sudoku_name;
	cout << "Enter sudoku file name: ";
	cin >> sudoku_name;

	// create sudoku class
	Puzzle sudoku(sudoku_name);
	
	//print finished sudoku 
	sudoku.solver();
}

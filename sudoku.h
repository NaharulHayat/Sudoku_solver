/* Victoria Johnston ~ 5th March 2015
sudoku.h
This program reads in a sudoku from the file entered by the user and prints the solved sudoku. */

#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

class Puzzle {
	public:
		Puzzle(string); //constructor
		void Print(); //prints sudoku board
		int isvalid(int,int,int); //checks whether user entry is valid
		int checkbox(int,int); //checks whether number is already in 3x3 box
		void solver();
	private:
		vector<vector <int> > puzzle; // 2d vector
				
};

#endif

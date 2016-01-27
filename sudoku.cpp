/* Victoria Johnston ~ 5th March 2015
sudoku.cpp
This program reads in a sudoku from the file entered by the user and prints the solved sudoku. */

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include "sudoku.h"
using namespace std;

/* The constructor is used to scan in numbers from an input file to create a sudoku. The sudoku board is stored in a 2D vector called puzzle. A temporary vector is used to push the numbers into puzzle. */
Puzzle::Puzzle(string file) {
        //intialize variables
        int value;
        // Open the file
        ifstream infile;
        infile.open(file.c_str());
        // Add elements from file to vector of vectors
        vector <int> tempVec;
	for (int s=0; s<=8; s++){
                for (int i=0; i<=8; i++){
                        infile >> value;
                        tempVec.push_back(value); //create a temp vector for each line
                }
                puzzle.push_back(tempVec); //create a vector of all the temp vectors
		tempVec.clear();	
	}
}

/* The solver function creates a 3D vector which contains the possibilty of numbers at each spot. If there is only one possibility left, that possibility is placed on the puzzle */
void Puzzle::solver(){
	// Declare vectors. three vec (3D vector) stores the vector of possibilities
	vector< vector< vector <int> > > threevec; //3d vector
	vector< vector <int> > twovec; //2d vector
	vector <int> vec; // linear vector

	// initialize 3d vector
	for (int i=0; i<=8; i++){
		threevec.push_back(twovec);
		for (int j=0; j<=8; j++){
			threevec[i].push_back(vec);
			for (int k=0; k<=8; k++){
				threevec[i][j].push_back(k+1);
			}
		}
	}
	int count=0;
	// compare to my puzzle - if there is already a number on the puzzle there is no need for possibilities for that spot.
	for (int a=0; a<=8; a++){
		for (int b=0; b<=8; b++){
			if (puzzle[a][b] != 0){ //there is a number if it is not zero
				for (int c=0; c<=8; c++){
			                threevec[a][b][c] = 0; //Make vector of possibilities for that spot all zero
        			}
			}
		}
	}
	
	// Declare variables
	int change;
	int pcount;
	int allzero;

	// Enter while loop for the solver. Keep looping through until there are no longer any changes.

	while (1){
		change = 0; //change starts off as 0. It will be one when a spot is filled in
	
		/* The vector of possibilites is updated everytime the board is updated.*/
		/* All numbers which are no longer possible are given a value of 0 on the possibility vector */
		for (int row=0; row<=8; row++){
			for (int col=0; col<=8; col++){
				// see if it is all zero
				allzero = 1;
				for (int z=0; z<=8; z++){
               				if (threevec[row][col][z] != 0){ 
                        			allzero = 0;
                			}
        			}
				if (allzero == 0) { //if it is all zero there is already a number on the board
                                	for (int num=0; num<=8; num++){ //if not remove the invalid spots
                                        	if ((*this).isvalid(num+1,row,col)==0){ 
                                                	threevec[row][col][num] = 0; //make invalid spot zero
						}	
					}
				}
			}
		}

	// SIMPLE SOLVER~ will place a number on a spot if that number is the only one left in the vector of 		possibilities			
	// if only one possibility in vector- change board
		for (int r=0; r<=8; r++){
			for (int c=0; c<=8; c++){
				// Check if the possibilities for a spot are all zero
				allzero = 1;
                                for (int zz=0; zz<=8; zz++){
                                        if (threevec[r][c][zz] != 0){
                                                allzero = 0;
                                        }
                                }
				// If the possibilities are not all zero-count how many possibilites are left
				if (allzero == 0){
					pcount = 0;
					for (int n=0; n<=8; n++){
						if (threevec[r][c][n] != 0)
							pcount++;
					}
					// If 1 possibility left set spot equal to the value			
					if (pcount == 1){ //true if one possibility left
						// Find the value of last possibility
						int x=0;
						while (threevec[r][c][x]==0){
							x++;
						}
						x++;
						//set that spot on board equal to that value
						puzzle[r][c] = x;
						// clear the possibilites
						for (int p=0; p<=8; p++){
		                                        threevec[r][c][p] = 0;
                		                }
						change=1; //show that there has been a change;
					}
				}
			}
		}
		
	
		// UPDATE vector of possibilities if theres been a change
                for (int row=0; row<=8; row++){
                        for (int col=0; col<=8; col++){
                                // see if it is all zero
                                allzero = 1;
                                for (int z=0; z<=8; z++){
                                        if (threevec[row][col][z] != 0){
                                                allzero = 0;
                                        }
                                }
                                if (allzero == 0) { //if it is all zero there is already a number on the board
                                        for (int num=0; num<=8; num++){ //if not remove the invalid spots
                                                if ((*this).isvalid(num+1,row,col)==0){
                                                        threevec[row][col][num] = 0; //make invalid spot zero
                                                }
                                        }
                                }
                        }
                }
		
		// SINGLETON SOLVER
/* For the singleton solver, a 1D vector count stores the amount of timesa number is a possibility in a row, column or 3x3 grid. It then check if a number only occurs once in a row,column or minigrid. If that is true, the spot which contains the number as a possibility is set equal to that number. */

		// Check 3x3 minigrid.
		
		for (int i=0; i<=2; i++){
			for (int j=0; j<=2; j++){
				// Initialize count vector
				vector <int> count(10);
				count.clear();
				for (int c=0; c<=8; c++){
					count.push_back(0);
				}
				int row,col;
				// Fill count vector with 3x3 grid possibilites
				for (int x=0; x<=2; x++){
					for (int y=0; y<=2; y++){
						row = (i*3)+x;
						col = (j*3)+y;
						if (puzzle[row][col]==0){ // Look at only empty spots on puzzle
							for (int p=0; p<=8; p++){
								if (threevec[row][col][p]!=0){
									count[p]++;
								}
							}
						}
					}
				}
				int single_num,final_row,final_col;
				// Evaluate count vector
				for (int e=0; e<=8; e++){
					if (count[e]==1){
						single_num=e+1;
						// Find where the row and column of that number
						for (int x=0; x<=2; x++){
							for (int y=0; y<=2; y++){
								row = (i*3)+x;
								col = (j*3)+y;
								for (int p=0; p<=8; p++){
									if (threevec[row][col][p]==single_num){
										final_row = row;
										final_col = col;
									}
								}
							}
						}
						puzzle[final_row][final_col]=single_num;
						change = 1;
						// Clear possibility vector for that spot
						for (int v=0; v<=8; v++){
							threevec[final_row][final_col][v]=0;
						}
					}
				}
			}
		}	

		// UPDATE vector of possibilities if theres been a change
                for (int row=0; row<=8; row++){
                        for (int col=0; col<=8; col++){
                                // see if it is all zero
                                allzero = 1;
                                for (int z=0; z<=8; z++){
                                        if (threevec[row][col][z] != 0){
                                                allzero = 0;
                                        }
                                }
                                if (allzero == 0) { //if it is all zero there is already a number on the board
                                        for (int num=0; num<=8; num++){ //if not remove the invalid spots
                                                if ((*this).isvalid(num+1,row,col)==0){
                                                        threevec[row][col][num] = 0; //make invalid spot zero
                                                }
                                        }
                                }
                        }
                }
		
		// Row
		for (int r=0; r<=8; r++){
			vector <int> rcount(10);
			// Initialize count vector
				rcount.clear();
				for (int l=0; l<=8; l++){
					rcount.push_back(0);
				}
				int row,col;
			for (int c=0; c<=8; c++){
				// Evaluate count vector using possibilities
				if (puzzle[r][c]==0){ // Look at only empty spots on puzzle
					for (int p=0; p<=8; p++){
						if (threevec[r][c][p]!=0){
							rcount[p]++;
						}
					}
				}
			}
			int single_num,final_row,final_col;
			// Evaluate the count vector
			for (int e=0; e<=8; e++){
				if (rcount[e]==1){
					single_num=e+1;
					// Find where the column of that number is 
					for (int c=0; c<=8; c++){
						for (int p=0; p<=8; p++){
							if (threevec[r][c][p]==single_num){
								final_row = r;
								final_col = c;
							}
						}
					}
					// Place spot on the board
					puzzle[final_row][final_col]=single_num;
					change = 1;
					// Clear possibility vector for that spot
					for (int v=0; v<=8; v++){
						threevec[final_row][final_col][v]=0;
					}
				}
			}
		}
	
		// UPDATE vector of possibilities if theres been a change
                for (int row=0; row<=8; row++){
                        for (int col=0; col<=8; col++){
                                // see if it is all zero
                                allzero = 1;
                                for (int z=0; z<=8; z++){
                                        if (threevec[row][col][z] != 0){
                                                allzero = 0;
                                        }
                                }
                                if (allzero == 0) { //if it is all zero there is already a number on the board
                                        for (int num=0; num<=8; num++){ //if not remove the invalid spots
                                                if ((*this).isvalid(num+1,row,col)==0){
                                                        threevec[row][col][num] = 0; //make invalid spot zero
                                                }
                                        }
                                }
                        }
                }
		
		// Column
		for (int r=0; r<=8; r++){
			vector <int> rcount(10);
			// Initialize count vector
				rcount.clear();
				for (int l=0; l<=8; l++){
					rcount.push_back(0);
				}
				int row,col;
			for (int c=0; c<=8; c++){
				// Evaluate count vector using possibilities
				if (puzzle[c][r]==0){ // Look at only empty spots on puzzle
					for (int p=0; p<=8; p++){
						if (threevec[c][r][p]!=0){
							rcount[p]++;
						}
					}
				}
			}
			int single_num,final_row,final_col;
			// Evaluate the count vector
			for (int e=0; e<=8; e++){
				if (rcount[e]==1){
					single_num=e+1;
					// Find where the row of that number is
					for (int c=0; c<=8; c++){
						for (int p=0; p<=8; p++){
							if (threevec[c][r][p]==single_num){
								final_row = c;
								final_col = r;
							}
						}
					}
					// Place spot on the board
					puzzle[final_row][final_col]=single_num;
					change = 1;
					// Clear possibility vector for that spot
					for (int v=0; v<=8; v++){
						threevec[final_row][final_col][v]=0;
					}
				}
			}
		}	
		
		if (change == 0)// if there are no more changes- break
			break;
	}
	Print();
}

int Puzzle::isvalid(int element,int row,int col) {
	// Check if element is anywhere else in row
	for (int c=0;c<=8;c++){
		if (puzzle[row][c]==element){ //if the element is already in the row
			return 0; // return false
		}
	}
	// Check if element is anywhere else in column
	for (int r=0;r<=8;r++){
		if (puzzle[r][col]==element){ //if the element is already in the column
			return 0; // return false
		}
	}
	// check if element is anywhere else in 3X3 box
	int box =0;
	for (int i=0;i<=8;i+=3){
		for (int j=0;j<=8;j+=3){
			box ++;
			if ((i<=row) && (row<=(i+2)) && (j<=col) && (col<=(j+2))){
				if (checkbox(element,box)==0){ //function to check the mini grid
					return 0;
				}
			}
		}
	}	
	return 1;
}

int Puzzle::checkbox(int element,int box) {
	int r,c; //row and column of each box
	switch (box) {
		case 1:
			r=0; c=0; // top left box. starts with puzzle[0][0]
			break;
		case 2: 
			r=0; c=3; // top center box. starts with puzzle[0][3]
			break;
		case 3: 
			r=0; c=6; // top right box. starts with puzzle[0][6]
			break;
		case 4: 
			r=3; c=0; // center left box. starts with puzzle[3][0]
			break;
		case 5: 
			r=3; c=3; // center center box. starts with puzzle[3][3]
			break;
		case 6:
			r=3; c=6; // center  right box. starts with puzzle[3][6]
			break;
		case 7: 
			r=6; c=0; // bottom left box. starts with puzzle[6][0]
			break;
		case 8:
			r=6; c=3; // bottom center box. starts with puzzle[6][3]
			break;
		case 9:
			r=6; c=6; // bottom right box. starts with puzzle[6][6]
			break;
	}
	for (int it_r=r;it_r<=r+2;it_r++){ //check three cells in each box
		for (int it_c=c;it_c<=c+2;it_c++){
			if (puzzle[it_r][it_c]==element) //if any of the cells is the same as the element
				return 0; //not a valid move
		}
	}
	return 1; //if element is not already in cell- valid move
}

void Puzzle::Print() {
        for (int i=0;i<=8;i++) {
                for (int j=0;j<=8;j++) {
                        if (puzzle[i][j]==0 || puzzle[i][j]=='0') { //check if the board has 0 (int or char)
                                cout << "  "; //if 0 the board should print an empty spot
                        } else {
                                cout << puzzle[i][j] << " "; //if not 0, print the puzzle piece
                        }
                        if ((j+1)%3==0) {
                                cout << "|"; //print a vertical line every 3 cells to make minigrid
                        }
                        // print row numbers
                        if (j==8)
                                cout << "  " << (i+1);
                }
                cout << endl;
                if ((i+1)%3==0) {
                        for (int s=0;s<=20;s++)
                                cout << "-"; //print horizontal line every 3 cells to make minigrid
                cout << endl;
                }
        }
        //print column numbers
        for (int n=0;n<=8;n++) {
                cout  << (n+1) << " " ;
                if ((n+1)%3==0)
                        cout << " ";
        }
        cout << endl;
}

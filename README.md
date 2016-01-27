# Sudoku_solver

Victoria Johnston
5th March 2015
Fundamentals of Computing 2 ~ Lab 6 Report ~ Sudoku Solver

How the user uses the program:

The user is asked to enter a file name. The file entered by the user shoudl contains the numbers needed to scan into a sudoku puzzle. Once the user presses enter, the solved sudoku from the file is displayed to the user. All the numbers in the file before are the same except the now all the zeros are replaced with numbers. All the rows, columns and mini 3x3 grids will all have the numbers 1-9.

How the program works internally:

The sudoku uses a Puzzle class. It stores the sudoku board in the 2D vector of integers, puzzle. This is done in the constructor because when the constructor is run, the ifstream is used to create an input file called infile. Infile is then used to open a file with the file name (the input into the constructor). A temporary vector called tempVec is created. The numbers on each row of the file are scanned into tempVec. A 2D vector puzzle is created by adding the tempVec vectors to it to create a vector of vectors.
Once the sudoku is stored in puzzle the solver function is run. A 3D vector (threevec) is created which stores all the possible numbers a spot can be. This vector is initialized using a 1D and a 2D vector. It pushes back the numbers 1-9 as a possibility for each spot. This was done on the assumption that an empty board (all 0s) has the possibility 1-9 on every spot. Now the 3D vector is cpompared to the global 2D vector puzzle. Whenever puzzle has a non zero spot, every number on the vector of possibilities for that spot is made to 0. In other words, the 1-9 are all replaced with 0s.
After this, a while loop is entered. This is where the sudoku is solved. The simple solver is implemented first and then the singleton. The simple solver looks at the possibility vector of every position. If there is only one possibility left in the vector (i.e. only 1 number form 1-9 is not 0) then that number is placed into the puzzle. The singleton solver uses a 1D vector called count which stores the amount of times the numbers 1-9 are a possibility in a row, column or 3x3 grid. It then checks if a number only occurs once in a row,column or minigrid. If there is only one possibility for a number, the spot which contains the number is set equal to that number. (that last possibility is put into puzzle). The singleton solver consists of three parts, one to check rows, columns and minigrids. All of these are done in the while loop and between each solver, the vector of possibilities is updated like it was before. At the top of the while loop an int variable, change is made equal to 0. Whenever a new number is placed in puzzle, change is made equal to 1. The while loop will break only when change remains as 0. This indicates that there are no more solutions.
The sudoku is then printed using the print function from lab 5.

How the program was verified:

The three provided sudokus were used to test the program. I started with the simple solver to see that it placed numbers down on the board correctly. Once I was happy with this I moved onto the singleton solvers starting with the minigrid solver before making the singleton solver for the row and column. Once all these solvers were finised, I tested the program on other sudokus to see if it placed number correctly everytime. This was repeated until I was happy with the result.

What worked well, what did not work, "how" the solver was implemented:

The 3D vector was at first hard to conceptionalize. I also had a hard time trying to initialize it.
At first I took on another method when trying to write the singleton solver. My version was a lot longer and less efficient as I tried to make count a 3D vector which also stored the row and the column of the spot.
Once I got past this, I think my program as a whole went well. using a 1D for count was a lot more efficient and my code also looked easier to read and understand.

// Project 4a written by Darin Hunt & Ojasvi DSilva
// This is the CPP file for Project 4. 
// It calls the functions of the board class
#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include "board.h"
#include <list>
#include <fstream>
#include <vector>

int main()
{
    ifstream fin;
    int choice;
    string fileName;
	bool solve;
	cout << "What puzzle would you like 1, 2 or 3?" << endl;
	cin >> choice;
	
    switch(choice)
    {
    	case(1):
    		{
    		fileName = 	"Sudoku 1.txt";
			}
			
		case(2):
			{
				fileName = "Sudoku 2.txt";
			}
		case(3):
			{
				fileName = "Sudoku 3.txt";	
			}	
	}
    // Read the sample grid from the file.
    fin.open(fileName.c_str());
    if (!fin)
    {
        cerr << "Cannot open " << fileName << endl;
        exit(1);
    }
  
    try
    {
    	
        board b1(SquareSize);
        int countto81;
        while (fin && fin.peek() != 'Z')
        {
            b1.initialize(fin);
            b1.print();
        }
        //while (b1.Solved()!=1)
        
        b1.printConflicts();
        b1.setCell(3, 3, 7); //sets cell, for this purpose we only need to do it once
        b1.print();
        b1.printConflicts();
       	b1.clearCell(3,3,7); //clears a cell for this purpose we only need to do it once
       	b1.print();
       	
       	b1.printConflicts();
        
        //when calling the find first blank cell fucntion do:
        //column = /*what is return from firstblankcell*/ /9 +1
        //row = /*what is returned from first blankcell*/ %9 or if it is a x%9=0 number just make it equal to 9;
        
        solve=b1.Solved();
        if (solve==true) //if solved is true it is solved
        {
        	cout << "Sodoku Solved" << endl;
		}
		else
			cout << "Sodoku Not Solved" << endl;
        
        
    }
    catch  (indexRangeError &ex)
    {
        cout << ex.what() << endl;
        exit(1);
    }

}

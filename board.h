// Project 4a written by Darin Hunt & Ojasvi DSilva
// This is a Header file for Project 4. 
// It builds the board class and defines it's functions. 

#ifndef board_h
#define board_h
#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>
#include <vector>
using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank

const int SquareSize = 3;  //  The number of cells in a small square
//  (usually 3).  The board has
//  SquareSize^2 rows and SquareSize^2
//  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

int numSolutions = 0;

class board
// Stores the entire Sudoku board
{
public:
    board(int);
    void clear();
    void initialize(ifstream &fin);
    void print();
    bool isBlank(int, int);
    void setCell(int x, int y, int z);
    void findConflict(int i, int j, int k, bool ba);
    void printConflicts();
    ValueType getCell(int, int);
    int squareNumber(int i, int j);
    bool Solved();
    void clearCell(int x, int y, int z);
    vector <int> findBlankCell();
    bool isLegal(int i, int j, int k);
    void solveBoard();
    int recursive; // keep track of recursive calls.
    
    
private:
    
    // The following matrices go from 1 to BoardSize in each
    // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)
    
    matrix<int> value;
    matrix <bool> c_columns;
    matrix <bool> c_rows;
    matrix <bool> c_square;
    
    
};

board::board(int sqSize)
: value(BoardSize+1,BoardSize+1)
// Board constructor
{
    clear();
}

void board::clear() //clears board
// Mark all possible values as legal for each board entry
{
    for (int i = 1; i <= BoardSize; i++)
        for (int j = 1; j <= BoardSize; j++)
        {
            value[i][j] = Blank;
        }
}



void board::initialize(ifstream &fin) //initializer
// Read a Sudoku board from the input file.
{
	
    char ch;
    c_columns.resize(10,10);
    c_rows.resize(10,10);
    c_square.resize(10,10); //sets size of conflict vectors
    clear();
    
    for (int i = 1; i <= BoardSize; i++)
        for (int j = 1; j <= BoardSize; j++)
        {
            fin >> ch;
            
            // If the read char is not Blank
            if (ch != '.')
                setCell(i,j,ch-'0');   // Convert char to int casted
            findConflict(i, j, value[i][j],false); //sends false since it is before initial initialization
        }
}

int board::squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
    // Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
    // coordinates of the square that i,j is in.
    
    return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}
ostream &operator<<(ostream &ostr, vector<int> &v)
// Overloaded output operator for vector class.
{
    for (int i = 0; i < v.size(); i++)
        ostr << v[i] << " ";
    cout << endl;
    return ostr;
}
ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
    if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
        return value[i][j];
    else
        throw rangeError("bad value in getCell");
}
void board::setCell(int x, int y, int z) //will assign a cell a value

{
    
    cout << "adding " << z << " to cell " << x << "," << y << endl; //adds values
    value[x][y] = z; //sets a new cell to a value z
    findConflict(x,y,z,true);
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
    if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
        throw rangeError("bad value in setCell");
    
    return (getCell(i,j) == Blank);
} 
void board::findConflict(int i, int j, int k, bool ba) //i and j are touples, k is the value and ba is before/after initilization
{
    ofstream fout("stuff.txt");
    int square;
    
            //int tempi=0, tempj=0;
                    
                    if (value[i][j]==-1&& ba==false) //before it is initilized, all values are checked at the samre time
                    {
            		 //does nothing
                    }
                
                	else if(value[i][j]==-1 && ba==true) //after it is inialized its done individually
                	{
                		c_columns[i][k] = false; 
                    	c_rows[j][k] = false;
                        square = squareNumber(i,j); //finds what square to update
                        c_square[square][k] = false;
					}
                
                    else //same for all
                    {
                    	
                        c_columns[i][value[i][j]] = true;
                        c_rows[j][value[i][j]] = true;
                        square = squareNumber(i,j); //finds what square to update
                        c_square[square][value[i][j]] = true;
                    }
}
void board::printConflicts()
{
	cout << "1  2  3  4  5  6  7  8  9" << endl << endl; //just for reference
    //each matrix needs a individual nester for loop
    cout << "ROWS" << endl; //will print the rows
    for (int i=MinValue; i<=MaxValue; i++) //this one will do columns
    {
        for (int j=MinValue; j<=MaxValue; j++)
        {
            cout << c_columns[i][j] << "  " ; //will print 0 oe 1
        }
        cout << endl;
    }
    
    
    cout << endl<< "COLUMNS" << endl;
    for (int k=MinValue; k<=MaxValue; k++) //this one will do columns conflicts
    {
        for (int l=MinValue; l<=MaxValue; l++)
        {
            cout << c_rows[k][l] << "  "  ; //wiull print a 0 or 1
        }
        cout << endl;
    }
    
    cout << endl<< "SQUARES" << endl;
    for (int m=MinValue; m<=MaxValue; m++) //this one will do squares
    {
        for (int n=MinValue; n<=MaxValue; n++)
        {
            cout << c_square[m][n] << "  " ; //will print a 0 or 1
        }
        cout << endl;
    }
}

bool board::isLegal(int i, int j, int k)
{
    int square = squareNumber(i,j);
    
    if (c_columns[i][k]==true)
    {
        return false;
    }
    else if (c_rows[j][k]==true)
    {
        return false;
    }
    else if (c_square[square][k]==true)
    {
        return false;
    }
    else
    {
        return true; //means that the number is valid;
    }
}

void board::clearCell(int x, int y, int z) //will clear a value

{
	cout << "removing " << z << " to cell " << x << "," << y << endl; //removes
    value[x][y] = - 1; //sets it to -1, which means empty
    findConflict(x,y,z,true); //sends 'true' so that it knows to save the value back to -1
}


vector<int> board::findBlankCell()
{
    vector <int> nextCell;
	int count = 0;
	int check = 9;
	nextCell.resize(2);

	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
				
		if (isBlank(i,j)==1)
		
		{
			for(int k = 1; k <= check; k++)
			{
				
				if(isLegal(i,j,k)==1)
				{
					count ++;
				}
			}
			
		if (count < check) 
		{
			nextCell[0] = i;
			nextCell[1] = j;
			check = count;
			
		}			
		}
			
			
			
			
		}
		
		
		
		
	}
	return nextCell;
} 

bool board::Solved() //checks all aspects of the board, if no spacs are blank it is solved
{
    for (int i = MinValue; i<=MaxValue; i++)
    {
        for (int j = MinValue; i<=MaxValue; j++)
        {
            if (isBlank(i,j)==1)
            {
                return false; //a blank space was found
            }
        }
    }
    return true; //no spaces are blank
} 

void board::solveBoard()
{
 //call this when initilize has already been called as well as an intiial conflict
 vector <int> nextCell;
 nextCell = findBlankCell();
   if (Solved()==1)// if board is fully solved
   {
   	
   	print() ;
   }
   else
   {
   	int i=nextCell[0];
	int j=nextCell[1];
	for (int k = MinValue; k<=MaxValue; k++)
	{
		if(isLegal(i,j,k)==1)
			
			{
				setCell(i,j,k); 
				solveBoard();
			
			}
			
	}
   	
   }
}

void board::print()
// Prints the current board.
{
    for (int i = 1; i <= BoardSize; i++)
    {
        if ((i-1) % SquareSize == 0)
        {
            cout << " -";
            for (int j = 1; j <= BoardSize; j++)
                cout << "---";
            cout << "-";
            cout << endl;
        }
        for (int j = 1; j <= BoardSize; j++)
        {
            if ((j-1) % SquareSize == 0)
                cout << "|";
            if (!isBlank(i,j))
                cout << " " << getCell(i,j) << " ";
            else
                cout << "   ";
        }
        cout << "|";
        cout << endl;
    }
    
    cout << " -";
    for (int j = 1; j <= BoardSize; j++)
        cout << "---";
    cout << "-";
    cout << endl;
    
}
#endif /* header_h */

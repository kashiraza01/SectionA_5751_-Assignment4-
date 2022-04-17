#include <iostream>
#include <fstream>
#include<string>

using namespace std;

//Helper Funtions
int StringLenght(char* str)   //function to calculate stringlenght
{
	int strLength = 0;
	int i = 0;

	while (str[i] != '\0')
	{
		strLength++;
		i++;
	}

	return strLength;
}
//Function Declarations
int* SAD(char**, int, int, int, int, char*);  
char** INPWords(int, int);    
int* GS(char**, int, int, char*); 
void OUTCordinates(char**, int, char**, int, int);
char** RWSG(int, int, int);  

int main()
{

	ifstream fin("InputQ2.txt");
	if (fin)
	{
		//r= rows, c= columns, tc= testingvalues
		int r, c, tc;

		//inputting values
		fin >> r >> c >> tc;
		cout << " \t \t \t WORD SEARCHER" << endl;

		//variable to tell line from where compiler needs to read the values
		int Line;
		char** grid = 0;
		Line = 2;  //first line has rows and col second has testcases
		grid = RWSG(r,c,Line);     //reads the grid


		char** list = 0;
		Line = 2 + r;  //list of words start after grid 
		list = INPWords(tc,Line);         //reads the list

		OUTCordinates(list, tc, grid, r, c);
		cout << endl << "All Words Have Been Searched!\nCheck Your File:)\n";
	}
	system("pause");
}
//Function Definitions:

//Function to show starting and ending cordinates of the given word in output.txt
void OUTCordinates(char** list, int numberOfWords, char** grid, int r, int c)
{
	ofstream file("Output.txt");
	if (file)
	{
		for (int i = 0; i < numberOfWords; i++)
		{

			int* resultArr = new int[4];

			resultArr = GS(grid, r, c, list[i]);  //this function returns the cordinates

			if (resultArr[0] == -1)
			{
				file << "NOT FOUND";
			}
			else
			{
				file << "{" << resultArr[0] << "," << resultArr[1] << "}" << "{" << resultArr[2] << "," << resultArr[3] << "}";
			}
			file << endl;
			delete[]resultArr;
		}
	}
	file.close();
}

//Function to read the list of search words from file
char** INPWords(int tc, int Line)
{
	ifstream file("InputQ2.txt");
	if (file)
	{
		string dummy;
		for (int i = 0; i < Line; i++)      //this skips all the data before words 
		{
			getline(file, dummy);
		}


		char** wordList = new char* [tc];
		int i = 0;
		while (i < tc)
		{
			char ab[80];

			file.getline(ab, 80);

			int cols = 0;
			cols = StringLenght(ab);

			wordList[i] = new char[cols + 1];

			int j = 0;
			for (j = 0; j < cols; j++) //deep copying
			{
				wordList[i][j] = ab[j];
			}
			wordList[i][j] = '\0';
			i++;
		}

		return wordList;
	}

}
//Function to read the grid from file
char** RWSG(int r, int c, int Line)
{
	ifstream file("InputQ2.txt");
	if (file)
	{

		string dummyLine;
		for (int i = 0; i < Line; i++) //this skips all the data before grid
		{
			getline(file, dummyLine);
		}

		int i = 0;
		char** Grid = new char* [r];
		while (i < r)
		{
			char x[80];

			file.getline(x, 80);
			Grid[i] = new char[c + 1];

			int j = 0;
			int k = 0;
			for (j = 0; j < c && k < (c + c - 1); j++) //deep copying
			{

				Grid[i][j] = x[k];
				k += 2;

			}
			Grid[i][j] = '\0';
			i++;
		}

		return Grid;
	}
}
//This function inputs all words  of the list turn by turn and searches them.
int* GS(char** grid, int GR, int GC, char* word)
{
	//Array used to return value
	int* returnArray = new int[4];
	//Array used to assign end coordinates
	int* arr = new int[3];

	for (int i = 0; i < GR; i++)
	{
		for (int col = 0; col < GC; col++)
		{
			arr = SAD(grid, GR, GC, i, col, word);
			if (arr[0] == 1)
			{
				returnArray[0] = i;  //start cordinates of word
				returnArray[1] = col;

				returnArray[2] = arr[1];  //end codinates of the word
				returnArray[3] = arr[2];
				return returnArray;
			}

		}

	}
	delete[]arr;
	returnArray[0] = -1;
	returnArray[1] = 0;
	returnArray[2] = 0;
	returnArray[3] = 0;
	return returnArray;

}
//Funtion to search the word in all 8 directions
int* SAD(char** grid, int gridRow, int gridCol, int row, int col, char* word)
{
	int rowD[] = { 0, 0, 1,-1, 1, 1, -1, -1 };     // 8 directions  in the order (right to left),(left to right),(top to bottom),(bottom to top),(top left to bottom right),(top right to bottom left),(bottom left to top right),(bottom right to top left)
	int colD[] = { -1, 1, 0, 0, 1, -1, 1, -1 };

	int* arr = new int[3];    //this array will keep have 1 at 0 position if word is found and record of the end cordinates of the word
							 //if word not found then the array wil will have -1 at 0 position

	if (grid[row][col] != word[0])   //checks if the cordinate have the first letter of word 
	{
		arr[0] = -1;
		arr[1] = 0;
		arr[2] = 0;
		return  arr;
	}


	int length = StringLenght(word);


	for (int i = 0; i < 8; i++)  //for 8 directions
	{
		int j;
		int moveRow = row + rowD[i];
		int moveCol = col + colD[i];

		// First character is already checked, match remaining 
		// characters 
		for (j = 1; j < length; j++)  //as first letter is found so starting form 1
		{


			// Out of bound check 
			if (moveRow >= gridRow || moveRow < 0 || moveCol >= gridCol || moveCol < 0)
			{
				break;
			}
			// If value does not match then break from loop. 
			if (grid[moveRow][moveCol] != word[j])
			{
				break;
			}
			moveRow = moveRow + rowD[i];   //moves in a specific direction 
			moveCol = moveCol + colD[i];
		}


		if (j == length) //if the word is found then j will be equal to length
		{
			moveRow = moveRow - rowD[i];
			moveCol = moveCol - colD[i];

			arr[0] = 1;
			arr[1] = moveRow;   //end cordinates of the word
			arr[2] = moveCol;

			return arr;
		}

	}
	arr[0] = -1;
	arr[1] = 0;
	arr[2] = 0;
	return  arr;
}
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstring>
using namespace std;

//function definitions
void filerfun(string A[]);
int longstr(string A[]);

void wordsearch(int len, string arr[])
{
	//grid array
	char **A;
	A=new char*[len];
	
	for(int i=0;i<len;i++)
	{
		A[i]=new char[len];
	}
	
	int rno;		//random number
	char rch;	//random character
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			rno = rand() % 26;//generates random number between 0 and 26
			rch = 'a' + rno;//add the random number generated above 'r' into the ASCII value of 'a'
			A[i][j] = rch;//grid initializer
		}
	}
	//variables to modify rows and cols while assignment.
	int n=0;
	int m=0;
	
	for (int idx = 0; idx < 7; idx++)
	{

		if (arr[idx].length() == len||(n==0))
		{
			
			// put word diagonally
			int row = 0;
			int col = 0;
			for (int i = 0; arr[idx][i] != '\0'; i++, row++, col++) {
				A[row][col] = arr[idx][i];
			}
			n++;
			
		} 
		else if (arr[idx].length() % 2 == 0)
		{
			// put word horizontally
			int row = (rand() % len)+1;
			int col = (rand() % 3)+4;
			if(n==1)
				row--;
			else if(n==2)
				row++;
			for (int i = 0; arr[idx][i] != '\0'; i++, col++) {
				A[row][col] = arr[idx][i];
			}
			n++;
		} 
		else 
		{
			int row=(rand()%4)+1;
			int col=rand()%5;
			if(m==0)
				col++;
			if(m==2)
			{
				int row = 0;
				int col = len-1;
				for (int i = 0; arr[idx][i] != '\0'; i++, row++, col--)
				{
					A[row][col] = arr[idx][i];
				}
			}
			if(m==1)
				col--;
			if(m==3)
			{
			col+=2;
			row++;
			}
			if(m==4)
			{
			row++;	
			}	
			for (int i = 0,j=idx; arr[idx][i] != '\0'; i++, row++) {
				A[row][col] = arr[idx][i];
			}
			m++;
		}
	}
	ofstream fout("output.txt");//putting the grid in an output.txt file
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			fout << A[i][j] << " ";
		}
		fout << endl;
	}
	fout.close();
}

int main() {
	int length = 0;
	string arr[7];
	filerfun(arr);
	length = longstr(arr);
	if (length < 10)
	{
		length = 10;
	}
	wordsearch(length, arr);
	cout<<"The words are stored in file output.txt"<<endl;
	system("pause");
	return 0;
}

//Filing
void filerfun(string A[])
 { 
	ifstream fin;
	fin.open("inputQ1.txt");
	string line;
	int i = 0;
	while (!fin.eof()) 
	{
		getline(fin, line,'\n');
		A[i] = line;
		fin >> A[i];
		i++;
	}
	fin.close();
	cout<<"Words given are:"<<endl;
	for(int j=0; j<i; j++)
	{
		cout<<A[j]<<endl;
	}
}
//function to find longest string in file
int longstr(string A[])
 {
	int o,max;
	for (int i = 0; i < 6; i++)
	{
		o= A[0].length();
		if (A[i].length() < A[i + 1].length()) 
		{
			max = A[i + 1].length();
		}
		if (max > o)
		{
			o = max;
		}
	}
	return o;
}
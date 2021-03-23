#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

//prototypes
bool fileCheck();
bool isPrime();
int Pathway();
int strToInt();
vector<vector<int>> copyMatrix();
int Pathway();

bool fileCheck(ifstream & file, int & numrow, int & numcol) //function that checks whether the file contains only integers
{
	char ch;
	bool valid = true;
	int currentcol = 1, max = 0;

	while(file.get(ch)) // read file char by char 
	{

		if( ch == ' ' && ch != '\n')
		{
			currentcol++; //to count number of columns in the current row
		}


		if(ch == '\n')
		{
			numrow++;
			if(currentcol > max) //here we try to find the highest number of cols that we will need to form the matrix
			{
				max = currentcol;
				currentcol = 1;
			}
		}

		if( ch != '1' && ch != '2' && ch != '3'&& ch != '4' && ch != '5' && ch != '6' && ch != '7' && ch != '8' && ch != '9' && ch != '0' &&
			//ch != '-1' && ch != '-2' && ch != '-3'&& ch != '-4' && ch != '-5' && ch != '-6' && ch != '-7' && ch != '-8' && ch != '-9' &&
			ch != ' ' && ch != '\n' && ch != '\t') // if the char is not integer or whitespace 
		{
			valid = false;
		}

		//int x = ch - '0';

		//if( x != -1 && x != -2 && x != -3 && x != -4 && x != -5 && x != -6 && x != -7 && 
		//	x != -8 && x != -9) // if the char is not integer or whitespace 
		//{
		//	valid = false;
		//}

		
	}

	if(currentcol > max) //here we try to find the highest number of cols that we will need to form a square matrix
	{
		max = currentcol;
		currentcol = 1;
		numcol = max;
	}

	file.clear(); 
	file.seekg(0); // go back to the beginning of the file 
	return valid; // returns that there are valid char 
}

bool isPrime(int n)
{
	int i, m=0;
	m=n/2; 

	if(n == 1)
		return false;

	for(i = 2; i <= m; i++)  
	{  
      if(n % i == 0)  
      {  
          //"Number is not Prime."  
          return false;
      }  
	}  
    // "Number is Prime."
	return true;
}

int strToInt(string s) //function to convert string to integer 
{
	return stoi(s);
}

vector<vector<int>> copyMatrix(vector<vector<string>> str_matrix, int row, int cols) //function that converts the string matrix to an int matrix
{
	string s;
	int t;
	vector<vector<int>> mat(row, vector<int>(cols,0));

	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < row; j++)
		{
			s = str_matrix[i][j];
			t = strToInt(s); //convert string to integer 
			mat[i][j] = t; //store integer in new matrix
		}
	}

	return mat;
}

int Pathway(vector<vector<int>> mat)
{
	vector<int> nums;

	int sum = mat[0][0];

	if(isPrime(sum))
		return INT_MAX;

	nums.push_back(sum);
 
	unsigned int i = 0, j = 0;
	
		while (i < mat.size()-1)//for (j = 0; j < mat[0].size(); j++)
		{
			int current;
			//**************Part 1 ********************//if not first column and not last column and not first row and not last row
			if (j != 0 && j != mat[0].size()-1 && i != 0 && i != mat.size()-1) 
			{
				vector<int> vec;
				vector<string> str_vec;

				int down = mat[i+1][j];
				int left_diag = mat[i+1][j-1];
				int right_diag = mat[i+1][j+1];
				
				if (!isPrime(down))
				{
					vec.push_back(down);
					str_vec.push_back("D");
				}

				if (!isPrime(left_diag))
				{
					vec.push_back(left_diag);
					str_vec.push_back("L");
				}

				if (!isPrime(right_diag))
				{
					vec.push_back(right_diag);
					str_vec.push_back("R");
				}

				if (isPrime(right_diag) && isPrime(down) && isPrime(left_diag))
				{
					break;
				}

				//int max = *max_element(vec.begin(), vec.end());
				int pos = 0;
				int max = 0;
				string direction;

				for (unsigned int k = 0; k < vec.size(); k++)
				{
					if(vec[k] > max)
					{
						max = vec[k];
						pos = k;
					}
					 
					/*if (vec[k] == max)
						pos = k;*/
				}

				nums.push_back(max);

				if (str_vec.size() != 0)
					direction = str_vec[pos];
				
				if (direction == "D")
				{
					current = mat[i+1][j];
					i++;
					sum += current;
				}

				else if (direction == "R")
				{
					current = mat[i+1][j+1];
					i++;
					j++;
					sum += current;
				}

				else 
				{
					current = mat[i+1][j-1];
					i++;
					j--;
					sum += current;
				}
			}

			//**************Part 2 ********************//if first column //
			else if ( j == 0 && i != mat.size()-1)
			{
				vector<int> vec;
				vector<string> str_vec;

				int down = mat[i+1][j];
				int right_diag = mat[i+1][j+1];

				if (!isPrime(down))
				{
					vec.push_back(down);
					str_vec.push_back("D");
				}

				if (!isPrime(right_diag))
				{
					vec.push_back(right_diag);
					str_vec.push_back("R");
				}

				if (isPrime(right_diag) && isPrime(down))
				{
					break;
				}

				//int max = *max_element(vec.begin(), vec.end());
				int pos = 0;
				int max = 0;

				for (unsigned int k = 0; k < vec.size(); k++)
				{
					if(vec[k] > max)
					{
						max = vec[k];
						pos = k;
					}
					 
					/*if (vec[k] == max)
						pos = k;*/
				}

				nums.push_back(max);
				string direction;

				if (str_vec.size() != 0)
					direction = str_vec[pos];
				
				if (direction == "D")
				{
					current = mat[i+1][j];
					i++;
					sum += current;
				}

				else if (direction == "R")
				{
					current = mat[i+1][j+1];
					i++;
					j++;
					sum += current;
				}

			}
		}

	cout << "Pathway: " ;

	if(nums.size() == 1)
		cout << nums[0] << endl ;

	else 
	{
		for (unsigned int h = 0; h < nums.size()-1; h++)
			cout << nums[h] << ">" ;

		cout <<nums[nums.size()-1];
		cout << endl;
	}

	return sum;
}

vector<vector<string>> StoreMatrix(int row, int cols, ifstream & file)
{
	char ch;
	vector<vector<string>> mat (row, vector<string>(cols,"0")); //matrix intialized to 0
	vector<char> storage;
	vector<string> ss;
	string line1;
	int R = 0, C =0;
	string s = "", temp;

	while(file.get(ch))
	{
		storage.push_back(ch); //storing all chars including whitespaces to a vector 
	}

	for (unsigned int i = 0; i < storage.size(); i++) //removing spaces between chars and converting chars to string 
	{
		if (storage[i] != ' ' && storage[i] != '\n')
		{
			s += storage[i]; //keep adding chars to one string until space is reached signifying that one integer is complete 
			//e.g '2''3''1' '4''4''4' -> 231 and 444
			if (i != storage.size()-1 && storage[i + 1] == '\n')
				ss.push_back(s); //if its the last integer of the row, add it to the vector 
		}
		else if (storage[i] == ' ') //once space is reached, add the resulting string to the vector 
		{
			ss.push_back(s);
			s = "";
		}
		else // if end line character is reached, add to the vector 
		{
			s = "";
			s += storage[i];
			ss.push_back(s);
			s = "";
		}

		if ( i == storage.size()-1 && storage[i] != '\n') //if only one integer exists in file, simply add the resulting string to vector 
		{
			ss.push_back(s);
			s = "";
		}

	}

	for (unsigned int i = 0; i < ss.size(); i++)
	{
		if (ss[i] != "\n")
		{
			mat[R][C] = ss[i]; //adding string to the matrix 
			C++;
		}

		else 
		{
			R++;
			C = 0;
		}
	}
	return mat;
}

int main()
{
	string fname, s, f;
	ifstream input1;
	vector<vector<string>> str_matrix;
	vector<vector<int>> int_matrix;
	vector<int> path;
	int numrow = 1, numcol = 1;

	do
	{
		cout << "Please enter file name: " ;
		cin >> fname; // entering file name 

		input1.open(fname.c_str()); // opening file 

		if (input1.fail()) // if file fails to open
			cout << endl << "Cannot find a file named " << fname << endl << endl;
	} while (input1.fail()); // keep asking until file successfully opens

	bool check = fileCheck(input1,numrow,numcol);

	if(!check) // if the file includes invalid char
		cout << endl << fname << " includes invalid char(s)" << endl;

	else 
	{
		str_matrix = StoreMatrix(numrow,numcol,input1);
		int_matrix = copyMatrix(str_matrix, numrow, numcol);

		int answer = Pathway(int_matrix);
		if(answer == INT_MAX)
			cout << "No path exists." << endl << "Sum: 0"  << endl;
		else
		cout << "Sum: " << answer << endl;
	}
	return 0;
}
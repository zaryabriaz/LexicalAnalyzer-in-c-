/*Lexical analysis or Scanner CC Project Phase 1*/
#include <iostream>
#include <fstream>
#include<list>
#include <string>
using namespace std;
char *keywords[] = { "asm", "else", "new", "this", "auto", "enum", "operator", "throw", "bool", "explicit", "private", "true", "break", "export", "protected", "try",
"case","extern","public","typedef","catch","false","register typeid","char","float","typename","class","for","return","union","const","friend",
"short","unsigned","goto","signed","using","continue","if","sizeof","virtual","default","inline","static","void","delete","int","volatile","do",
"long","struct","double","mutable","switch","while","namespace","template","input->","output<-"};


const int MAX = 500;


class Node {

	string identifier, scope, type;
	int lineNo;
	Node* next;

public:
	Node()
	{
		next = NULL;
	}

	Node(string key, string value, string type, int lineNo)
	{
		this->identifier = key;
		this->scope = value;
		this->type = type;
		this->lineNo = lineNo;
		next = NULL;
	}

	void print()
	{
		cout << "Identifier's Name:" << identifier
			<< "\nType:" << type
			<< "\nScope: " << scope
			<< "\nLine Number: " << lineNo << endl;
	}
	friend class SymbolTable;
};

class SymbolTable {
	Node* head[MAX];

public:
	SymbolTable()
	{
		for (int i = 0; i < MAX; i++)
			head[i] = NULL;
	}

	int hashf(string id); // hash function 
	bool insert(string id, string scope,
		string Type, int lineno);

	int find(string id);
	int index(string id)
	{
		int index = hashf(id);
		Node* start = head[index];

		if (start == NULL)
			return -1;

		while (start != NULL) {

			if (start->identifier == id) {
				//		start->print();
				return index;
			}

			start = start->next;
		}

		return index; // not found
	}
	bool deleteRecord(string id);

	bool modify(string id, string scope,
		string Type, int lineno);
	void printall()
	{
		int i = 0;
		Node* start = head[i];

		if (start == NULL)
			cout << "No data in symbol table";

		while (start != NULL) {
			
			cout <<"Scope = "<< start->scope << endl;

			cout << "Type = " << start->type << endl;

			cout << "Lineno = " << start->lineNo << endl;
			
			
			start = start->next;
		}
	
	}
};

// Function to modify an identifier 
bool SymbolTable::modify(string id, string s,
	string t, int l)
{
	int index = hashf(id);
	Node* start = head[index];
	
	if (start == NULL)
		return -1;

	while (start != NULL) {
		if (start->identifier == id) {
			start->scope = s;
			start->type = t;
			start->lineNo = l;
			return true;
		}
		start = start->next;
	}

	return false; // id not found 
}

// Function to delete an identifier 
bool SymbolTable::deleteRecord(string id)
{
	int index = hashf(id);
	Node* tmp = head[index];
	Node* par = head[index];

	// no identifier is present at that index 
	if (tmp == NULL) {
		return false;
	}
	// only one identifier is present 
	if (tmp->identifier == id && tmp->next == NULL) {
		tmp->next = NULL;
		delete tmp;
		return true;
	}

	while (tmp->identifier != id && tmp->next != NULL) {
		par = tmp;
		tmp = tmp->next;
	}
	if (tmp->identifier == id && tmp->next != NULL) {
		par->next = tmp->next;
		tmp->next = NULL;
		delete tmp;
		return true;
	}

	// delete at the end 
	else {
		par->next = NULL;
		tmp->next = NULL;
		delete tmp;
		return true;
	}
	return false;
}

// Function to find an identifier 
int SymbolTable::find(string id)
{
	int index = hashf(id);
	Node* start = head[index];
	
	if (start == NULL)
		return -1;

	while (start != NULL) {

		if (start->identifier == id) {
	//		start->print();
			return index;
		}

		start = start->next;
	}

	return -1; // not found 
}




// Function to insert an identifier 
bool SymbolTable::insert(string id, string scope,
	string Type, int lineno)
{
	int index = hashf(id);
	Node* p = new Node(id, scope, Type, lineno);

	if (head[index] == NULL) {
		head[index] = p;
		/*cout << "\n"
			<< id << " inserted";
			*/
		return true;
	}

	else {
		Node* start = head[index];
		while (start->next != NULL)
			start = start->next;

		start->next = p;
		cout << "\n"
			<< id << " inserted";

		return true;
	}

	return false;
}

int SymbolTable::hashf(string id)
{
	int asciiSum = 0;

	for (int i = 0; i < id.length(); i++) {
		asciiSum = asciiSum + id[i];
	}

	return (asciiSum % 100);
}




int len(char arr[])
{
	int i = 0;
	for (i; i < arr[i] != NULL; i++)
	{
	}
	return i;
}
void strcopy(char temp[], char arr[], int j, int result)
{
	int size = result-j ; int i = 0;
	for (; i < size; i++)
	{
		temp[i] = arr[j];
		j++;
	}
	temp[i] = NULL;
}


bool search(char temp[], char arr[])
{
	if (len(temp) != len(arr))return false;
	for (int i = 0; arr[i]!= NULL; i++)
	{
		if (temp[i] != arr[i])
		{
			return false;
		}
	}
	return true;
}
bool check_in_keywords(char temp[])
{

	for (int i = 0; i < 59; i++)
	{
		if (search(temp, keywords[i]) == true)
		{
	       return true;
		}
	}
	return false;
}
int identifier(char arr[],int loop)
{
	char lexeme[100]; int a = 0;
	int tr[4][5] = { 2, 2, -1, -1, -1,3,2,3,-1,-1,3,2,2,4,-1,-1,-1,-1,-1,1};
	int state = 1;
	while (tr[state - 1][4] != 1)
	{
		if (state == -1)return 0;
		if (arr[loop] == '_'&& tr[state - 1][0] != -1)
		{
			
			state = tr[state - 1][0];
				loop++;
     	}		
		else if ((arr[loop] <= 'z' && arr[loop] >= 'a') || (arr[loop] <= 'Z' && arr[loop] >= 'A') && tr[state - 1][1] != -1)
		{
			
			state = tr[state - 1][1];
			loop++;

		}
		else if ((arr[loop] <= '9' && arr[loop] >= '0') && tr[state - 1][2] != -1)
		{
			state = tr[state - 1][2];
			loop++;

		}
		else if (tr[state-1][3]!=-1)
		{
			state = tr[state - 1][3];
		
		}
		else
		{
			return 0;
		}
		}
	
	return loop;
}

int operation(char arr[], int loop){
	char lexeme[200];
	int tr[15][16] = {  14, 2, 3, 4, 5, 6, 7, 8, 9,-1, 10, 11, 12, 13, -1,-1,//1 
	                   -1, 15, 15, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15, -1,//2 
	                   -1, -1, 15, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15, -1,//3 
	                   -1, -1, -1, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,//4
					   -1, -1, -1, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,//5
					   -1, -1, -1, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,//6
					   -1, -1, -1, 15, -1, -1, 15, -1, -1, -1, -1, -1, -1, -1, 15, -1,//7
					   -1, -1, -1, -1, -1, -1, -1, 15, -1, -1, -1, -1, -1, -1, -1, -1,//8
					   -1, -1, -1, -1, -1, -1, -1, -1, 15, -1, -1, -1, -1, -1, -1, -1,//9
					   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15, -1,//10
					   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15, -1, -1, -1, -1,//11
					   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15, -1,//12
					   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15, -1,//13
					   15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,//14
					   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1,//15
					   
	};
	int state = 1;
	while (tr[state - 1][15] != 1)
	{
		if (arr[loop] == '*'&& tr[state - 1][0] != -1)
		{

			state = tr[state - 1][0];
			loop++;
		}
		else if (arr[loop] == '<' && tr[state - 1][1] != -1)
		{

			state = tr[state - 1][1];
			loop++;

		}
		else if ((arr[loop] == '>') && tr[state - 1][2] != -1)
		{
			state = tr[state - 1][2];
			loop++;

		}
		else if ((arr[loop] == '=') && tr[state - 1][3] != -1)
		{
			state = tr[state - 1][3];
			loop++;

		}
		else if ((arr[loop] == ':') && tr[state - 1][4] != -1)
		{
			state = tr[state - 1][4];
			loop++;

		}
		else if ((arr[loop] == '!') && tr[state - 1][5] != -1)
		{
			state = tr[state - 1][5];
			loop++;

		}
		else if ((arr[loop] == '+') && tr[state - 1][6] != -1)
		{
			state = tr[state - 1][6];
			loop++;

		}
		else if ((arr[loop] == '|') && tr[state - 1][7] != -1)
		{
			state = tr[state - 1][7];
			loop++;

		}
		else if ((arr[loop] == '"') && tr[state - 1][8] != -1)
		{
			state = tr[state - 1][8];
			loop++;

		}
		else if ((arr[loop] == '"') && tr[state - 1][9] != -1)
		{
			state = tr[state - 1][9];
			loop++;

		}
		else if ((arr[loop] == '%') && tr[state - 1][10] != -1)
		{
			state = tr[state - 1][10];
			loop++;

		}
		else if ((arr[loop] == '&') && tr[state - 1][11] != -1)
		{
			state = tr[state - 1][11];
			loop++;

		}
		else if ((arr[loop] == '/') && tr[state - 1][12] != -1)
		{
			state = tr[state - 1][12];
			loop++;

		}
		else if ((arr[loop] == '-') && tr[state - 1][13] != -1)
		{
			state = tr[state - 1][13];
			loop++;

		}

		else if (tr[state - 1][14] != -1)
		{
			state = tr[state - 1][14];

		}

		else
		{
			return 0;
		}
	}
	return loop;
	
}
int Keyword(char arr[],int loop)
{
	char lexeme[100]; int a = 0;
	int tr[8][6] = {2,-1,-1,-1,-1,-1,
					3,-1,-1,-1,-1,-1,
	                4,-1,-1,-1, 8,-1,
	                4,5,-1,-1,-1,-1,
	                -1,-1,6,7,-1,-1,
	                -1,-1,-1,-1,8,-1,
	                 -1,8,-1,-1,-1,-1,
	                 -1,-1,-1,-1,-1,1};

	int state = 1;
	while (tr[state - 1][5] != 1)
	{
		if ((arr[loop] <= 'z' && arr[loop] >= 'a') || (arr[loop] <= 'Z' && arr[loop] >= 'A') && tr[state - 1][0] != -1)
		{

			state = tr[state - 1][0];
			a++;
			loop++;
		}
		else if (arr[loop] == '-' && tr[state - 1][1] != -1)
		{

			state = tr[state - 1][1];
			loop++;
			a++;
		}
		else if ((arr[loop] == '>') && tr[state - 1][2] != -1)
		{
			state = tr[state - 1][2];
			loop++;
			a++;
		}
		else if ((arr[loop] == '<') && tr[state - 1][3] != -1)
		{
			state = tr[state - 1][3];
			loop++;
			a++;
		}
		else if (tr[state - 1][3] != -1)
		{
			state = tr[state - 1][4];

		}
		else
		{
			if (a >= 2)return loop;
			else 
				return 0;
		}
	}
	return loop;
}
int punctuation(char arr[], int loop)
{

	char lexeme[100]; int a = 0;
	int tr[8][8] = {2 ,  3,  4 ,  5,  6,  7, -1, -1,
	               -1 ,  3, -1, -1, -1, -1,  8, -1,
	               -1 , -1,  4, -1, -1, -1,  8, -1,
				   -1 , -1, -1,  5, -1, -1,  8, -1,
				   -1,  -1, -1, -1,  6, -1,  8, -1,
				   -1,  -1, -1, -1, -1,  7,  8, -1,
				   -1,  -1, -1, -1, -1, -1,  8, -1,
				   -1,  -1, -1, -1, -1, -1, -1,  1,
	};
	int state = 1;
	while (tr[state - 1][7] != 1)
	{
		if (arr[loop] == '[' && tr[state - 1][0] != -1)
		{

			state = tr[state - 1][0];
			loop++;
		}
		else if (arr[loop] == '{' && tr[state - 1][1] != -1)
		{

			state = tr[state - 1][1];
			loop++;

		}
		else if ((arr[loop] == '(') && tr[state - 1][2] != -1)
		{
			state = tr[state - 1][2];
			loop++;

		}
		else if ((arr[loop] == ')') && tr[state - 1][3] != -1)
		{
			state = tr[state - 1][3];
			loop++;

		}
		else if ((arr[loop] == '}') && tr[state - 1][4] != -1)
		{
			state = tr[state - 1][4];
			loop++;

		}
		else if ((arr[loop] == ']') && tr[state - 1][5] != -1)
		{
			state = tr[state - 1][5];
			loop++;

		}
		else if (tr[state - 1][6] != -1)
		{
			state = tr[state - 1][6];

		}
		else
		{
			return 0;
		}
	}
	return loop;
	
}

int numbers(char arr[], int loop)
{
	

		char lexeme[100]; int a = 0;
		int tr[8][7] = {2, 2, 2, -1, -1, -1, -1,
			           -1,-1, 2,  8, -1,  3, -1,
					   -1,-1, 4, -1, -1, -1, -1,
					   -1,-1, 4,  8, -1, -1, 5,
					    6, 6,-1, -1, -1, -1,  -1,
					   -1,-1, 7, -1, -1, -1, -1,
					   -1,-1, 7,  8, -1, -1, -1,
					   -1,-1,-1, -1,  1, -1, -1
                      };
		
		int state = 1;
		while (tr[state - 1][4] != 1)
		{
			if (arr[loop] == '+' && tr[state - 1][0]!=-1)
			{

				state = tr[state - 1][0];
				loop++;
			}
			else if (arr[loop] == '-' && tr[state - 1][1] != -1)
			{

				state = tr[state - 1][1];
				loop++;

			}
			else if ((arr[loop] >= '0' && arr[loop] <= '9') && tr[state - 1][2] != -1)
			{
				state = tr[state - 1][2];
				loop++;

			}
			else if ((arr[loop] == '.') && tr[state - 1][5] != -1)
			{
				state = tr[state - 1][5];
				loop++;

			}
			else if (((arr[loop] == 'E' || arr[loop] == 'e')) && tr[state - 1][6] != -1)
			{
				state = tr[state-1][6];
				loop++;

			}
		
			else if (tr[state - 1][3] != -1)
			{
				state = tr[state - 1][3];

			}
			else
			{
				return 0;
			}
		}
		return loop;

	
}
void lexical(char arr[], SymbolTable st,int line)
{
	ofstream file,token;
	file.open("error.txt", ios::app);
	token.open("token.txt", ios::app);
	int size=len(arr);
	int result;
	int index=-1;
	int check;
	char temp[100];

	for (int j = 0; j < size;)
	{
		if (arr[j] == ' ')j++;
		result = 0;
		result=identifier(arr, j);
		if (result!=0)
		{ 
			cout << "Identifier :>" << endl;
			for (int k = j; k < result; k++)
			{
				cout << arr[k];
			}
			cout << endl;
			
			strcopy(temp, arr, j, result);

			check = st.find(temp);
			j = result;

			if (check != -1)
				cout << "Identifier Is already presentin symbol table\n";
			else{
				st.insert(temp, "local", "identifier", line);
				check = st.find(temp);
			}
			token << "<" << temp << "," << check<< ">  " << endl;

		}
		else if (result = Keyword(arr, j))
		{
			
			strcopy(temp, arr, j, result);
			bool response=check_in_keywords(temp);
			if (response == true)
			{
				cout << "keyword :>" << endl;
				for (int k = j; k < result; k++)
				{
					cout << arr[k];
				}
				cout << endl;
				strcopy(temp, arr, j, result);
				j = result;

				check = st.find(temp);
				if (check != -1)
					cout << "Keyword Is already present in symbol table\n";
				else
				{
					st.insert(temp, "local", "Keyword", line);

					check = st.find(temp);
				}

				token << "<" << temp << "," << check << ">  " << endl;

			}
			else{
					cout << endl << "errors :>" << endl;
					//	j--;
					cout << temp;
					file << temp << endl;
					cout << endl;
			}
			j = result;

		}
		else if (result = numbers(arr, j))
		{

			cout << "Numbers :>" << endl;
			for (int k = j; k < result; k++)
			{
				cout << arr[k];
			}
			cout << endl;
			
			strcopy(temp, arr, j, result);
			j = result;
			check = st.find(temp);
			if (check != -1)
				cout << "Number Is already present in symbol table\n";
			else{
				st.insert(temp, "local", "Number", line);
				check = st.find(temp);
			}
			token << "<" << temp << "," << check << ">  " << endl;

		}
		else if (result = operation(arr, j))
		{

			cout << "operators :>" << endl;
			for (int k = j; k < result; k++)
			{
				cout << arr[k];
			}
			cout << endl;
			strcopy(temp, arr, j, result);
			j = result;

			check = st.find(temp);

			if (check != -1)
				cout << "operator Is already present in symbol table\n";
			else{
				st.insert(temp, "local", "operator", line);
				check = st.find(temp);

			}
			token << "<" << temp << "," << check << ">  " << endl;
		}
		else if (result = punctuation(arr, j))
		{

			cout << "punctuation :>" << endl;
			for (int k = j; k < result; k++)
			{
				cout << arr[k];
			}
			cout << endl;
			strcopy(temp, arr, j, result);
			j = result;

			check = st.find(temp);
			if (check != -1)
				cout << "Punctuation Is already present in symbol table\n";
			else{
				st.insert(temp, "local", "punctuation", line);
				check = st.find(temp);

			}
			token << "<" << temp << "," << check << ">  " << endl;

		}
		
		else
		{
			if (arr[j] != ' ')
			{
				cout << endl << "errors :>" << endl;
				//	j--;
				cout << arr[j];
				file << arr[j];
				j++;
				cout << endl;
				file << endl;
			}
		}


	}
	file.close();
	token.close();
}
int main(){
	ifstream fin;
	SymbolTable st;

	fin.open("text.txt");
	char buffer[4096];
	//SymbolTable st;
	int line = 1;

	while (!fin.eof()){
		fin.getline(buffer, 4096);
		//cout << buffer << endl;
		lexical(buffer,st,line);
		line++;
		//cout << "Second line" << endl;
	}

}


/*NOTE: In token.txt i am generating every token not unique only because of that if int comes in symbol table then its position will be 
same so in short only for showing the symbol table working.Thanks*/









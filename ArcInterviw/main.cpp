#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iterator>

using namespace std;

//struct node
//{
//	char substr[4];
//	int occurs;
//	node *next;
//};

int GetLength(string fileName);
void GetSubstr(string data, int end);
//void StoreSubstr(node** head, char(&combo)[4]);
//void PrintCombos(node** head);
void PrintCombos(map<string, int> mapName);
//int CompareSubs(char (&arr1)[4], char (&arr2)[4]);

//const char fileName[] = "fasta1.fasta";

void main()
{
	int ind = 0;															//index counter
	int length, lastInd;

	string fileName, line, data;
	ifstream myfile;
	cout << "Please enter the name of the file: ";
	getline(cin, fileName);
	myfile.open(fileName.data(), ios::in);

	if (myfile.is_open()) {
		length = GetLength(fileName);
		lastInd = length - 4;

		getline(myfile, line);												//ignore first line

		while (getline(myfile, line)) {										//store data into string
			data.append(line);
		}

		myfile.close();

		GetSubstr(data, lastInd);											//get substrings, store them, then print them
	}
	else {
		cout << "Error\n";
	}

	system("pause");
	system("exit");
}

//get the length of data in the file not counting the first line
int GetLength(string fileName)
{
	ifstream file(fileName.c_str());
	string line;
	int length = 0;

	file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');			//skip first line of file
	while (getline(file, line)) {
		length += line.length();											// count characters
	}

	return length;
}

//Get the substring from the data string passed in
//then pass off to StoreSubstr funct to put in one of 4 linked lists
//void GetSubstr(string data, int end)
//{
//	int idx = 0;
//	string sub;
//	char arr[4];															//char array to hold substring for storing
//
//	node *headA = NULL;
//	node *headC = NULL;
//	node *headG = NULL;
//	node *headT = NULL;
//
//	while (idx <= end) {
//		sub = data.substr(idx, 4);
//		for (int i = 0; i < 4; i++) {
//			arr[i] = sub.at(i);
//		}
//
//		switch (arr[0])	
//		{
//		case 'A':
//			StoreSubstr(&headA, arr); 
//			break;
//		case 'C':
//			StoreSubstr(&headC, arr);
//			break;
//		case 'G' :
//			StoreSubstr(&headG, arr);
//			break;
//		case 'T':
//			StoreSubstr(&headT, arr);
//			break;
//		}
//		idx++;
//	}
//
//	PrintCombos(&headA);
//	PrintCombos(&headC);
//	PrintCombos(&headG);
//	PrintCombos(&headT);
//}

void GetSubstr(string data, int end)
{
	int idx = 0;
	string sub;

	map<string, int> mapA;
	map<string, int> mapC;
	map<string, int> mapG;
	map<string, int> mapT;

	while (idx <= end) {
		sub = data.substr(idx, 4);

		switch (sub.at(0)) {
		case 'A':
			++mapA[sub];
			break;
		case 'C':
			++mapC[sub];
			break;
		case'G':
			++mapG[sub];
			break;
		case 'T':
			++mapT[sub];
			break;
		}

		//++map[sub];
		idx++;
	}

	PrintCombos(mapA);
	PrintCombos(mapC);
	PrintCombos(mapG);
	PrintCombos(mapT);
}

//Sort substring into appropriate linked list
//if substring is already in the list, increment occurs
//void StoreSubstr(node** head, char (&combo)[4])
//{
//	node* curr = *head;
//	node* newsub = new node;
//
//	if (*head == NULL) {
//		for (int i = 0; i < 4; i++) {
//			newsub->substr[i] = combo[i];
//		}
//		newsub->occurs = 1;
//		newsub->next = NULL;
//		*head = newsub;
//	}
//	else {
//		while (curr != NULL) {
//			if (CompareSubs(combo, curr->substr)) {
//				curr->occurs++;
//				break;
//			}
//			else if (curr->next == NULL) {
//				for (int i = 0; i < 4; i++) {
//					newsub->substr[i] = combo[i];
//				}
//				newsub->occurs = 1;
//				newsub->next = NULL;
//				curr->next = newsub;
//				break;
//			}
//			else {
//				curr = curr->next;
//			}
//		}
//	}
//}

//print the linked list of 4mers and number of occurances
//void PrintCombos(node** head)
//{
//	node* curr = *head;
//
//	while (curr != NULL) {
//		cout << "4mers: " << curr->substr[0] << curr->substr[1] << curr->substr[2] << curr->substr[3] << " # of occurrences: " << curr->occurs << endl;
//		curr = curr->next;
//	}
//}

void PrintCombos(map<string, int> mapName)
{
	for (map<string, int>::iterator it = mapName.begin(); it != mapName.end(); ++it) {
		cout << "4-mers: " << it->first << " # of occurrences: " << it->second << endl;
	}
}

//int CompareSubs(char(&arr1)[4], char(&arr2)[4])
//{
//	for (int k = 0; k < 4; k++) {
//		if (arr1[k] != arr2[k]) {
//			return 0;
//		}
//	}
//	return 1;
//}
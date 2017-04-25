// INFO450Music.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int READERROR = 100;
const int WRITEERROR = 200;
const int ARRAYSIZE = 100;


//music class
class music
{
	string songName;
	string songArtist;
	music* next;

public:
	music();
	music(string song, string art);
	void showSong();
	friend class linkedList;
};

//class linked list
class linkedList
{
	int numrecords;
	music* head;
	music* tail;
public:
	linkedList();
	~linkedList();
	void showList(); //Transverse a list
	int readList(string filename);
	void addNodeToEnd(music* newnode);
	void skipMusic(); //Skip a node
	int removeMusic(int i); //Delete a node
};

//default constructor - initalized empty
music::music()
{
	songName = "";
	songArtist = "";
	next = NULL;
}

//overload constructor initlized w/values
music::music(string song, string art)
{
	songName = song;
	songArtist = art;
	next = NULL;
}

//Linked List constructor 
linkedList::linkedList()
{
	numrecords = 0;
	head = NULL;
	tail = NULL;
}


//deconstructor - free allocated memory
linkedList::~linkedList()
{
	music* ptr = head;
	while (ptr != NULL)
	{
		head = ptr->next;
		delete ptr;
		ptr = head;
	}
}


//Show song to console that is playing
void music::showSong()
{
	cout << songName << endl;
}


//Traverse/Show/PlaySong to console
void linkedList::showList()
{
	music* ptr = head;
	music* prev = NULL;
	
	string choice;
	
	int amount;


	cout << "**** My Music List **** " << endl;
	if (head == NULL)
	{
		return;
	}
	while (ptr != NULL)
	{
		cout << "The song is " << ptr->songName << " by " << ptr->songArtist << "[P]lay, [S]kip,[D]elete, or [Q]uit?" << endl;
		getline(cin, choice);
		//play song
		if (choice == "p" || choice == "P")
		{
			cout << "Playing: ";
			ptr->showSong();
			ptr = ptr->next;
		}
		//skip song
		if (choice == "s" || choice == "S")
		{
			cout << "How many?" << endl;
			cin >> amount;

			for (int i = 1; ptr && i <= amount; i++)
			{
				cout << "Skipping: ";
				ptr->showSong();
				prev = ptr;
				ptr = ptr->next;
			}
		}
		//deletes song
		if (choice == "D" || choice == "d")
		{


		}
		
	}
}

void linkedList::addNodeToEnd(music* newnode)
{
	if (head == NULL)
	{
		head = newnode;
		tail = newnode;
	}
	else
	{
		tail->next = newnode;
		tail = newnode;
	}
}


int linkedList::readList(string filename)
{
	string isong, iname;
	ifstream infile(filename, ios::in);
	if (!infile)
	{
		cout << "File could not be opened for reading" << endl;
		return READERROR;
	}


	while (!infile.eof())
	{
		getline(infile, iname, '|');
		if (!iname.empty())
		{
			getline(infile, isong);

			music* newnode = new music(isong, iname);
			addNodeToEnd(newnode);

			numrecords++;
		}
	}

	infile.close();
	return 0;
}

int main()
{
	linkedList my;

	int error;
	string answer;
	string filename;

	cout << "Welcome to  Music Player!" << endl;
	cout << "To access the list text file. Use the file path where the text file" << endl;
	cout << "is stored on your machine. Ex. C:\\Projects\\MyMusic.txt" << endl;

	cout << "Enter the full path of the file: " << endl;
	getline(cin, filename);
	ifstream file(filename);
	error = my.readList(filename);
	if (error)
	{
		cout << "Cannot read list" << endl;
		cout << "Possible issues:" << endl;
		cout << "1. Incorrect file name" << endl;
		cout << "2. File does not exist " << endl;
		cout << "3. Incorrect file path" << endl;

		return 0;
	}
	my.showList();


	return 0;
}

// INFO450Music.cpp : Defines the entry point for the console application.
//

//Author: James Nicholson
//Spring 2017
//Purpose: Creating an application that reads a music play list from a file.
//Once read, the program will present each song in order.
//As each song is presented, the user has the option to Play, Skip or Delete from the play list.
//The program should require the user to enter a full path filename of an existing playlist text file.
//All the entries  in the file should be read.
//The program should continue to present the next song until the user decides to Quit.
//If the end of the music list is reached, the program should 
//start over from the beginning of the list and again, present each song in turn to Play, Skip, Delete or Quit.


#include "stdafx.h"
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int READERROR = 100;
const int WRITEERROR = 200;
const int ARRAYSIZE = 100;


//Music class
class music
{
	string songName;
	string songArtist;
	int p;
	music* next;

public:
	music();
	music(string song, string art);
	void showSong();
	friend class linkedList;
};

//Class linked list
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
};

//Default constructor - initalized empty
music::music()
{
	songName = "";
	songArtist = "";
	next = NULL;
}

//Overload constructor initlized w/values
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

//Deconstructor - free allocated memory
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

//Show song name to console
void music::showSong()
{
	cout << songName << endl;
}

//Traverse, Skip, Delete, Node from list
void linkedList::showList()
{
	music* ptr = head;
	music* prev = NULL;
	string choice;
	int amount;

	cout << "**** My Music List **** " << endl;
	if (head == NULL) //Empty List
	{
		cout << "List is empty!" << endl;
		return;
	}

	//If only 1 node in the list
	if (head == tail)
	{
		head = NULL;
		tail = NULL;
	}
	else
		head = head->next;

	while (ptr != NULL)
	{
		cout << "The song is " << ptr->songName << " by " << ptr->songArtist << " [P]lay, [S]kip,[D]elete, or [Q]uit? ";
		getline(cin, choice);

		if (choice == "p" || choice == "P")
		{
			cout << "---------\n";
			cout << "Playing: ";
			ptr->showSong();
			cout << "---------\n";
			if (ptr == tail)
			{
				ptr = head;
			}
			else
			{
				ptr = ptr->next;
			}
		}
		//Skip song on list
		if (choice == "s" || choice == "S")
		{
			cout << "How many?" << endl;
			cin >> amount;
			cin.clear();
			cin.ignore();
			cout << "---------\n";
			for (int i = 1; ptr && i <= amount; i++)
			{
				cout << "Skipping: ";
				ptr->showSong();

				prev = ptr;
				if (ptr == tail)
				{
					ptr = head;
				}
				else
				{
					ptr = ptr->next;
				}
			}
			cout << "---------\n";
		}

		//Delete song from list
		if (choice == "D" || choice == "d")
		{
			if (ptr->next && (ptr->next)->songName == ptr->songName)
			{
				if (tail == ptr->next)
					tail = ptr;

				music* tbd = ptr->next;
				ptr->next = (ptr->next)->next;
				delete tbd;
			}
			cout << "---------\n";
			cout << "Deleting: ";
			ptr->showSong();
			cout << "---------\n";

			if (ptr == tail)
			{
				ptr = head;
			}
			else
			{
				ptr = ptr->next;
			}
		}

		//Quit List
		if (choice == "Q" || choice == "q")
		{
			cout << "Thanks for listening! " << endl;
			break;
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
	linkedList musicplay;

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
	musicplay.showList();


	return 0;
}

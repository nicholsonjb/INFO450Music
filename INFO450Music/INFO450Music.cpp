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

class music 
{
	string songName;
	string songArtist;
	music *next;

public:
	music();
	music(string song, string art);
	void showSong();
	friend class linkedList;
};
music::music() 
{
	songName = "";
	songArtist = "";
	next = NULL;
}

music::music(string song, string art)
{
	songName = song;
	songArtist = art;
	next = NULL;
}

class linkedList
{
	int numrecords;
	music *head;
	music *tail;
public:
	linkedList();
	void showList(); //Transverse a list
	int readList(string filename);
	void addNodeToEnd(music* newnode);
	void skipMusicNode(); //Skip a node
	void removeMusicNode(); //Delete a node
	

};

linkedList::linkedList()
{
	numrecords = 0;
	head = NULL;
	tail = NULL;
}

void music::showSong()
{
	cout << "Playing:"  << songName << endl;
}


void linkedList::showList()
{
	music* ptr = head;
		 cout << "**** My Music List **** " << endl;
		 if (head == NULL)
		 { 
		return;
		 }
	while (ptr != NULL)
	{
		ptr->showSong();
		ptr = ptr->next;
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

			music *newnode = new music (isong, iname);
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


    return 0;
}


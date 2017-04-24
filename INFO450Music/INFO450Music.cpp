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
	music(string song, string art);
	friend class linkedList;
};

music::music(string song, string art)
{
	songName = song;
	songArtist = art;
	next = NULL;
}

class linkedList
{
	music *head;
	music *tail;
public:
	linkedList();
	void showList(); //Transverse a list
	int readList(string filename);
	void skipMusicNode(); //Skip a node
	void removeMusicNode(); //Delete a node
	

};

linkedList::linkedList()
{
	head = NULL;
	tail = NULL;
}


void linkedList::showList()
{
		music *ptr;
		 ptr = head;
		 cout << "**** My Music List **** " << endl;
		 if (ptr == NULL)
		 { 
			 cout << "list is empty" << endl;
		return;
		 }

		 cout << "The song is " << head->songName << " by " << tail->songArtist << endl;
	while (ptr != NULL)
	{
		cout << "Playing: " << ptr->songName << endl;
		ptr = ptr->next;
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

		getline(infile, iname, ',');
		if (!iname.empty())
		{
			getline(infile, isong);

			music *newnode = new music (isong, iname);
			/*AddNodeToEnd(newnode);*/

			/*numrecords++;*/
		}
	}

	infile.close();
	return 0;
}

int main()
{
    return 0;
}


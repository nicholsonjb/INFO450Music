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
	string artistName;
	string songName;
	music *next;

public:
	music(string artist, string song);
	friend class musickLinkedList;
};


class musicLinkedList
{
	music *head;
	music *tail;
public:
	musicLinkedList();
	void skipMusicNode(); //Skip a node
	void removeMusicNode(); //Delete a node
	void showMusicList(); //Transverse a list

};

int main()
{
    return 0;
}


#pragma once

#include <Windows.h>
#include <iostream>
#include <string>

#include "Manager.h"
#include <time.h>
#include <conio.h>

using namespace std;

class UserInterface
{
private:
	HANDLE _hndl;
	Manager* manager;
	bool end = false;
	void TuneCmd();
	void TextColor(int color);
	void Pause();
	int Choicer(int min, int max);
	void PrintStats();
	int OptionsMenu();
	bool AddInputFile();
	bool AddOutputFile();
public:
	int MainMenu();
	UserInterface();
	~UserInterface();
};

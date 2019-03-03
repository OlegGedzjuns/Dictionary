#include "UserInterface.h"

void UserInterface::TuneCmd()
{
	SetConsoleTitle("Dictionary");
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;	// Width of each character in the font
	cfi.dwFontSize.Y = 24;	// Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");	// Choose your font
	SetCurrentConsoleFontEx(_hndl, FALSE, &cfi);
}

void UserInterface::TextColor(int color)
{
	SetConsoleTextAttribute(_hndl, color);
}

void UserInterface::Pause()
{
	cout << "Press any key to continue..";
	_getch();
}

int UserInterface::Choicer(int min, int max)
{
	int choice = 0;
	do
	{
		TextColor(7);
		cout << "Your choice : ";
		cin >> choice;
	} while (choice < min || choice > max);
	return choice;
}

void UserInterface::PrintStats()
{
	TextColor(7); //White
	cout << "Current stats : " << endl;
	TextColor(8); //Gray
	cout << "\tWord count : " << manager->wordCnt << endl;
	cout << "\tInput file status : ";
	if (manager->haveInputFile)
	{
		TextColor(2);
		cout << "Opened" << endl;
		TextColor(8);
	}
	else
	{
		TextColor(4);
		cout << "Not found" << endl;
		TextColor(8);
	}
	cout << "\tEaten RAM : " << sizeof(*manager) << " bytes" << endl;
}

int UserInterface::OptionsMenu()
{
	TextColor(7);	//White
	cout << "What to do next?" << endl;
	TextColor(8);	//Gray
	cout << "\t1.Add data from file" << endl;
	cout << "\t2.Print data to file" << endl;
	cout << "\t3.Add input file" << endl;
	cout << "\t4.Add output file" << endl;
	cout << "\t5.Delete data from programm" << endl;
	cout << "\t6.Exit" << endl;
	return Choicer(1, 6);
}

bool UserInterface::AddInputFile()
{
	system("cls");
	TextColor(7);
	if (!manager->haveInputFile)
	{
		cout << "You have no input file, add it" << endl;
	}
	else
	{
		cout << "Which file do you want to use" << endl;
	}
	string name = "input.txt";
	TextColor(8);
	cout << "\t1.Use standart (input.txt)" << endl;
	cout << "\t2.Use custom" << endl;
	switch (Choicer(1, 2))
	{
		case 1:
		{
			return manager->AddInputFile(name);
		}
		case 2:
		{
			bool added = false;
			do
			{
				cout << "Enter name : ";
				cin >> name;
				added = manager->AddInputFile(name);
				if (!added)
				{
					TextColor(4);
					cout << "Wrong" << endl;
					TextColor(7);
				}
			} while (!added);
			return added;
		}
		default:
			return false;
	}
}

bool UserInterface::AddOutputFile()
{
	system("cls");
	TextColor(7);
	if (!manager->haveOutputFile)
	{
		cout << "You have no output file, add it" << endl;
	}
	else
	{
		cout << "Which file do you want to use" << endl;
	}
	string name = "result.txt";
	TextColor(8);
	cout << "\t1.Use standart (result.txt)" << endl;
	cout << "\t2.Use custom" << endl;
	switch (Choicer(1, 2))
	{
	case 1:
	{
		return manager->AddOutputFile(name);
	}
	case 2:
	{
		bool added = false;
		do
		{
			cout << "Enter name : ";
			cin >> name;
			added = manager->AddOutputFile(name);
			if (!added)
			{
				TextColor(4);
				cout << "Wrong" << endl;
				TextColor(7);
			}
		} while (!added);
		return added;
	}
	default:
		return false;
	}
}

int UserInterface::MainMenu()
{
	while (!end)
	{
		system("cls");
		PrintStats();
		switch (OptionsMenu())
		{
			case 1:
			{
				if (!manager->haveInputFile)
				{
					while (!AddInputFile());
				}
				system("cls");
				cout << "Loading.." << endl;
				clock_t start = clock();
				int cnt = manager->GetData();
				clock_t end = clock();
				cout << "File readen in " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
				cout << "Added " << cnt << " words" << endl;
				Pause();
				break;
			}
			case 2:
			{
				if (!manager->haveOutputFile)
				{
					while (!AddOutputFile());
				}
				system("cls");
				cout << "Printing.." << endl;
				clock_t start = clock();
				manager->PrinToFile();
				clock_t end = clock();
				cout << "File printed in " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
				Pause();
				break;
			}
			case 3:
			{
				while (!AddInputFile());
				break;
			}
			case 4:
			{
				while (!AddOutputFile());
				break;
			}
			case 5:
			{
				system("cls");
				TextColor(4);
				cout << "TODO" << endl;
				Pause();
				break;
			}
			case 6:
			{
				end = true;
				break;
			}
			default:
				break;
		}
	}
	return 0;
}

UserInterface::UserInterface()
{
	manager = new Manager;
	TuneCmd();
	_hndl = GetStdHandle(STD_OUTPUT_HANDLE);
}

UserInterface::~UserInterface()
{
	delete manager;
}

#include "UserInterface.h"

void UserInterface::TuneCmd()
{
	SetConsoleTitle("Dictionary");
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;	// Width of each character in the font
	cfi.dwFontSize.Y = 16;	// Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Lucida Console");	// Choose your font
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
	cout << "\t5.Find word" << endl;
	cout << "\t6.Find simmilar word" << endl;
	cout << "\t7.Delete data from programm" << endl;
	cout << "\t8.Exit" << endl;
	return Choicer(1, 8);
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
			return manager->AddInputFile("input.txt");
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
				sw.StartTimeMeasure();
				int cnt = manager->GetData();
				sw.EndTimeMeasure();
				TextColor(2);
				cout << "File has been read in " << sw.GetTimeMeasure() << " seconds" << endl;
				cout << "Added " << cnt << " words" << endl;
				TextColor(7);
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
				sw.StartTimeMeasure();
				manager->PrinToFile();
				sw.EndTimeMeasure();
				TextColor(2);
				cout << "File printed in " << sw.GetTimeMeasure() << " seconds" << endl;
				TextColor(7);
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
				bool stop = false;
				while (!stop)
				{
					TextColor(7);
					cout << "Enter word to search (X to stop) : ";
					string word;
					cin >> word;
					if (word == "X")
					{
						stop = true;
						break;
					}
					if (manager->CheckWord(word))
					{
						if (manager->FindWord(word))
						{
							TextColor(8);
							cout << "Word (" << word << ") exist in dictionary" << endl;
						}
						else
						{
							TextColor(8);
							cout << "This word is not in the dictionary" << endl;
							cout << "Do you want to add it? Y/N" << endl;
							TextColor(7);
							cout << "Your choice : ";
							char c = 'N';
							cin >> c;
							if (c == 'Y')
							{
								manager->AddToDict(word);
							}
						}
					}
					else
					{
						TextColor(8);
						cout << "Not a word" << endl;
					}
				}
				break;
			}
			case 6:
			{
				system("cls");
				TextColor(7);
				cout << "Enter word to correct : ";
				string word;
				cin >> word;
				TextColor(8);
				if (!manager->CheckWord(word))
				{
					cout << "Not a word" << endl;
					Pause();
					break;
				}
#if _DEBUG
				sw.StartTimeMeasure();
				cout << "Methode A : " << manager->FindCorrect(word, 1) << endl;
				sw.EndTimeMeasure();
				cout << "Found in " << sw.GetTimeMeasure() << endl << endl;
				sw.StartTimeMeasure();
				cout << "Methode B : " << manager->FindCorrect(word, 2) << endl;
				sw.EndTimeMeasure();
				cout << "Found in " << sw.GetTimeMeasure() << endl << endl;
				sw.StartTimeMeasure();
				cout << "Methode C : " << manager->FindCorrect(word, 3) << endl;
				sw.EndTimeMeasure();
				cout << "Found in " << sw.GetTimeMeasure() << endl << endl;
				sw.StartTimeMeasure();
				cout << "Methode D : " << manager->FindCorrect(word, 4) << endl;
				sw.EndTimeMeasure();
				cout << "Found in " << sw.GetTimeMeasure() << endl << endl;
				sw.StartTimeMeasure();
				cout << "Methode E : " << manager->FindCorrect(word, 5) << endl;
				sw.EndTimeMeasure();
				cout << "Found in " << sw.GetTimeMeasure() << endl << endl;
#else
				sw.StartTimeMeasure();
				cout << "Correct : " << manager->FindCorrect(word, 5) << endl;
				sw.EndTimeMeasure();
				cout << "Found in " << sw.GetTimeMeasure() << " seconds" << endl;

#endif
				TextColor(7);
				Pause();
				break;
			}
			case 7:
			{
				system("cls");
				TextColor(4);
				cout << "TODO" << endl;
				Pause();
				break;
				
			}
			case 8:
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
	_hndl = GetStdHandle(STD_OUTPUT_HANDLE);
	TuneCmd();
}

UserInterface::~UserInterface()
{
	delete manager;
}

#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <vector>
#include <cctype>


using namespace std;

string header(
" _   _    \n"                                     
"| | | |                                        \n"
"| |_| | __ _ _ __   __ _ _ __ ___   __ _ _ __\n"
"|  _  |/ _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\ \n"
"| | | | (_| | | | | (_| | | | | | | (_| | | | |\n"
"\\_| |_/\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|\n"
"                    __/ |                      \n"
"                   |___/                       \n"
);

void Art(int fehler);

int main()
{
	bool repeat = true, rightguess = false, firsttimerunning = true;
	string word, guess, winword = word;
	int numberoflines = 0;
	ifstream file("Woerter.txt");
	srand(time(NULL));
	int randNumber;
	vector<string> woerter;
	
	for (string line; getline(file, line);) {
		woerter.push_back(line);
		++numberoflines;
	}
	
	randNumber = rand() % numberoflines;

	word = woerter.at(randNumber);
	winword = word;
	

	string hiddenword(word.length(), '_');
	int pos = 0, glength = 0, wlength = word.length();
	int fehler = 0;
	

	while (hiddenword.find("_") != string::npos && fehler <= 5) {
		system("cls");
		cout << header;
		if (!firsttimerunning)
		cout << "Your guess was " << (rightguess == true ? "right" : "wrong") << "\t" << 5-fehler << " tries left\n";
		firsttimerunning = false;
		Art(fehler);
		cout << endl << "\t\t\t\t\t\t" << hiddenword << endl /*<< word*/ << endl;
		cout << "Your guess: ";
		getline(cin, guess);
		string uppercaseGuess(1, toupper(guess[0]));
		string lowercaseGuess(1, tolower(guess[0]));
		glength = guess.length();
		string replace(glength, '_');
		if (word.find(uppercaseGuess) != string::npos || word.find(lowercaseGuess) != string::npos && guess != winword) {
			while (word.find(uppercaseGuess) != string::npos || word.find(lowercaseGuess) != string::npos) {
				if (word.find(uppercaseGuess)!=string::npos)
				{
					pos = word.find(uppercaseGuess);
					guess[0] = uppercaseGuess[0];
					hiddenword.replace(pos, glength, guess);
				}
				else
				{
					pos = word.find(lowercaseGuess);
					guess[0] = lowercaseGuess[0];
					hiddenword.replace(pos, glength, guess);
				}
				word.replace(pos, guess.size(), replace);
				rightguess = true;
			}
		}
		else if (guess == winword) {
			break;
		}
		else {
			fehler++;
			rightguess = false;
		}
	}

	if (hiddenword.find("_") == string::npos || guess == winword) {
		system("cls");
		Art(fehler);
		cout << "\nSie haben gewonnen!!! Das zu suchende wort war: " << winword << endl;

	}
	else {
		system("cls");
		Art(5);
		cout << "\nSie haben verloren:( Das zu suchende wort war: " << winword << endl;
	}

	
}


void Art(int fehler) {
	switch (fehler)
	{

	case 0:{
		cout << 
			""
			"\n   "
			"\n   "
			"\n   "
			"\n    "
			"\n   "
			"\n"
			"\n____  "
			;
		break;
		}
	case 1:
	{
		cout << 
			""
			"\n|"
			"\n|"
			"\n|"
			"\n|"
			"\n|"
			"\n|"
			"\n|___  "
			;
		break;
	}
	case 2:
	{
		cout << 
			"_______"
			"\n|/"
			"\n|"
			"\n|"
			"\n|"
			"\n|"
			"\n|"
			"\n|___  "
			;
		break;
	}
	case 3: {
		cout << 
			"_______"
			"\n|/   |"
			"\n|"
			"\n|"
			"\n|"
			"\n|"
			"\n|"
			"\n|___";
		break;
	}
	case 4: {
		cout << 
			"_______"
			"\n|/   |"
			"\n|   (_)"
			"\n|"
			"\n|"
			"\n|"
			"\n|"
			"\n|___";
		break;
	}
	case 5: {
		cout << 
			"_______"
			"\n|/   |"
			"\n|   (_)"
			"\n|   \\|/ "
			"\n|    |"
			"\n|   / \\ "
			"\n|"
			"\n|___  "; break;
	}

	}

}

void WinScreen() {

}

void ClearScreen()
{
	COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
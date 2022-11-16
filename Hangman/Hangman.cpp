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
	
	for (string line; getline(file, line);) {	//Checks the .txt File
		woerter.push_back(line);				//counts how many lines it has
		++numberoflines;						//and creates a Vector with all the words
	}
	
	randNumber = rand() % numberoflines;

	word = woerter.at(randNumber); //Assigns a random word to the word that has to be guesses
	winword = word;
	

	string hiddenword(word.length(), '_'); //This string will be shown on the console and it shows the correct inputs
	int pos = 0, glength = 0, wlength = word.length();
	int fehler = 0;
	

	while (hiddenword.find("_") != string::npos && fehler <= 5) { //stops if either the word has been guesses or not
		system("cls");
		cout << header;
		if (!firsttimerunning) //that it doesn't show if wrong or right input at start
		cout << "Your guess was " << (rightguess == true ? "right" : "wrong") << "\t" << 5-fehler << " tries left\n"; //shows the user if he guessed right or not
		firsttimerunning = false; //from now on it will be shown if input is right or wrong
		Art(fehler); //Shows the Hangman
		cout << endl << "\t\t\t\t\t\t" << hiddenword << endl << word << endl; //shows the hidden word
		cout << "Your guess: ";
		getline(cin, guess); //Input for the guess

		string uppercaseGuess(1, toupper(guess[0]));	//makes an Uppercase string of the guess
		string lowercaseGuess(1, tolower(guess[0]));	//makes a  Lowercase string of the guess
		
		glength = guess.length(); //length of guess
		string replace(glength, '_'); //string which has as many '_' as the length of the string
		if (word.find(uppercaseGuess) != string::npos || word.find(lowercaseGuess) != string::npos && guess != winword) {
			while (word.find(uppercaseGuess) != string::npos || word.find(lowercaseGuess) != string::npos) { //changes the underscore to the guesses letter as many times as needed
				if (word.find(uppercaseGuess)!=string::npos) //checks if the word in uppercase is same as in lowercase
				{
					pos = word.find(uppercaseGuess); //gets the position where the guess matched with the word
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

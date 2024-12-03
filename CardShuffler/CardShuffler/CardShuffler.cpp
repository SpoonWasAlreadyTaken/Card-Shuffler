#include <iostream>
#include <vector>
#include <string>

using namespace std;


// variables
vector<vector<string>> Decks = { {"King Hearts", "Queen Clubs", "8 of Spade", "Jack of Aces", "10 of Aces", "Jack of Spades"}, {"Queen Hearts", "King Clubs", "9 of Spade", "Jack of Hearts", "2 of Aces", "Jack of Clubs"} };
vector<string> deckNames;

string helpText = "Info:\n  This is a card deck shuffler and puller, must input a deck of cards as a text file. In the format of ''Card1 Count, Card2 Count''.\n  Write Clear to clear the screen.\n  Write Shuffle to Shuffle current Deck.\n  Write Select and Deck Name to Select another Deck Name.\n  Write ADD DECK to add another Deck.\n  Write Help to see this help menu again.\n";




// function declerations

string ParseInput(string input);



// main function
int main()
{
	cout << "\u001b[2m" << helpText << "\u001b[0m";

	while (true)
	{
		string unparsedInput;

		getline(cin, unparsedInput);

		cout << ParseInput(unparsedInput);
	}
}


string ParseInput(string input)
{
	vector<string> parsedInput;
	string stored;

	input += " ";

	for (int i = 0; i < input.size(); i++)
	{
		if (input.at(i) == ' ')
		{
			parsedInput.push_back(stored);
			stored = "";
		}
		else
		{
			stored += input.at(i);
		}
	}

	if (parsedInput.at(0) == "Clear" || parsedInput.at(0) == "clear")
	{
		system("CLS");
		return "";
	}
	else if (parsedInput.at(0) == "Help" || parsedInput.at(0) == "help")
	{
		return "\u001b[2m" + helpText + "\u001b[0m";
	}
	else
	{
		string error;
		error = "\u001b[31m";
		error += "ERROR: ";
		error += "\u001b[37m";
		error += "''" + input + "\b'' " + "\u001b[31m" + "Is not a command" + "\u001b[37m";
		return error;
	}

}
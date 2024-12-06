#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


// variables
vector<vector<string>> decks = { {"King of Hearts", "Queen of Clubs", "Eight of Spade", "Jack of Aces", "Ten of Aces", "Jack of Spades"}, {"Queen of Hearts", "King of Clubs", "Nine of Spade", "Jack of Hearts", "Two of Aces", "Jack of Clubs"} };
vector<string> deckNames = {"standart", "second"};
int currentDeck = 0;

string helpText = "Info:\n  This is a card deck shuffler and puller, must input a deck of cards as a text file. In the format of ''Card1 Count, Card2 Count''.\n  Write Clear to clear the screen.\n  Write Shuffle to Shuffle current Deck or Shuffle Cut to shuffle cut the current Deck.\n  Write Select and Deck Name to Select another Deck Name.\n  Write ADD DECK to add another Deck.\n  Write Pull to Pull a card or write pull and a number to pull a number of cards.\n  Write Peak to look at a card or write Peak and a number to look at a number of cards.\n  Write Print to print out the entire Deck of cards.\n  Write Swtich and a Deck name to switch to that deck.\n  Write Help to see this help menu again.\n";




// function declerations

string ParseInput(string input);
vector<string> Shuffle(vector<string> deck, string shuffleType);




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

	if (parsedInput.at(0) == "clear")
	{
		system("CLS");
		return "";
	}
	else if (parsedInput.at(0) == "help")
	{
		return "\u001b[2m" + helpText + "\u001b[0m";
	}
	else if (parsedInput.at(0) == "pull")
	{
		string cards;
		int toPull = 1;
		if (parsedInput.size() > 1)
		{
			bool hasNumber = false;
			for (int i = 0; i < parsedInput.at(1).size(); i++)
			{
				if (isdigit(parsedInput.at(1).at(i)))
				{
					hasNumber = true;
					break;
				}
			}
			if (hasNumber)
			{
				if (stoi(parsedInput.at(1)) > decks.at(currentDeck).size() - 1)
				{
					string errorMSG;
					errorMSG += "\u001b[31m";
					errorMSG += "Error: Not a valid ammount!";
					errorMSG += "\u001b[37m";
					errorMSG += "\n";
					return errorMSG;
				}
				else
				{
					toPull = stoi(parsedInput.at(1));
				}

			}
			else
			{
				string errorMSG;
				errorMSG += "\u001b[31m";
				errorMSG += "Error: Not a valid ammount!";
				errorMSG += "\u001b[37m";
				errorMSG += "\n";
				return errorMSG;
			}
		}	

		for (int i = 0; i < toPull; i++)
		{
			cards += decks.at(currentDeck).at(0);
			decks.at(currentDeck).push_back(decks.at(currentDeck).at(0));
			decks.at(currentDeck).erase(decks.at(currentDeck).begin());
			if (i < toPull - 1)
			{
				cards += ", ";
			}
		}

		string pulledCard;
		pulledCard += "Card: " + cards + "\n";
		return pulledCard;
	}
	else if (parsedInput.at(0) == "switch" && parsedInput.size() > 1)
	{
		for (int i = 0; i < deckNames.size(); i++)
		{
			if (deckNames.at(i) == parsedInput.at(1))
			{
				currentDeck = i;
				return "Current Deck: " + parsedInput.at(1) + "\n";
			}
		}

		return "No Deck of matching name found\n";
	}
	else if (parsedInput.at(0) == "print")
	{
		string cards;
		for (int i = 0; i < decks.at(currentDeck).size(); i++)
		{
			cards += decks.at(currentDeck).at(i);
			if (i < decks.at(currentDeck).size() - 1)
			{
				cards += ", ";
			}
		}

		string fullDeck;
		fullDeck += "Deck: " + cards + "\n";
		return fullDeck;
	}
	else if (parsedInput.at(0) == "peak")
	{
		string cards;
		int toPull = 1;
		if (parsedInput.size() > 1)
		{
			bool hasNumber = false;
			for (int i = 0; i < parsedInput.at(1).size(); i++)
			{
				if (isdigit(parsedInput.at(1).at(i)))
				{
					hasNumber = true;
					break;
				}
			}
			if (hasNumber)
			{
				if (stoi(parsedInput.at(1)) > decks.at(currentDeck).size() - 1)
				{
					string errorMSG;
					errorMSG += "\u001b[31m";
					errorMSG += "Error: Not a valid ammount!";
					errorMSG += "\u001b[37m";
					errorMSG += "\n";
					return errorMSG;
				}
				else
				{
					toPull = stoi(parsedInput.at(1));
				}

			}
			else
			{
				string errorMSG;
				errorMSG += "\u001b[31m";
				errorMSG += "Error: Not a valid ammount!";
				errorMSG += "\u001b[37m";
				errorMSG += "\n";
				return errorMSG;
			}
		}

		for (int i = 0; i < toPull; i++)
		{
			cards += decks.at(currentDeck).at(i);

			if (i < toPull - 1)
			{
				cards += ", ";
			}
		}

		string pulledCard;
		pulledCard += "Peak Cards: " + cards + "\n";
		return pulledCard;
	}
	else if (parsedInput.at(0) == "shuffle")
	{
		if (parsedInput.size() > 1)
		{
			if (parsedInput.at(1) == "cut")
			{
				decks.at(currentDeck) = Shuffle(decks.at(currentDeck), "cut");

				string shuffled;
				shuffled += "\u001b[32m";
				shuffled += "Cut!";
				shuffled += "\u001b[37m";
				shuffled += "\n";
				return shuffled;
			}
		}
		else
		{
			decks.at(currentDeck) = Shuffle(decks.at(currentDeck), "normal");

			string shuffled;
			shuffled += "\u001b[32m";
			shuffled += "Shuffled!";
			shuffled += "\u001b[37m";
			shuffled += "\n";
			return shuffled;
		}
	}
	else
	{
		string error;
		error = "\u001b[31m";
		error += "ERROR: ";
		error += "\u001b[37m";
		error += "''" + input + "\b'' " + "\u001b[31m" + "Is not a command" + "\u001b[37m";
		error += "\n";
		return error;
	}
}


vector<string> Shuffle(vector<string> deck, string shuffleType)
{
	if (shuffleType == "normal")
	{
		random_shuffle(deck.begin(), deck.end());

		return deck;
	}
	else if (shuffleType == "cut")
	{
		int halfDeck = deck.size() / 2;

		for (int i = 0; i < halfDeck; i += 2)
		{
			swap(deck.at(i), deck.at(halfDeck + i));
		}

		return deck;
	}
	else
	{
		string error;
		error = "\u001b[31m";
		error += "ERROR: ";
		error += "Not a shuffle method";
		error += "\u001b[37m";
		error += "\n";
		cout << error;
		return deck;
	}
}
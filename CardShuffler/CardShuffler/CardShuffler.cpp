#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


// variables
vector<vector<string>> decks = { 
{
		"Fleshy Overgrowth", "Fleshy Overgrowth",
		"Hemotology",
		"Faultlines",
		"Power Overwhealming", "Power Overwhealming",
		"Sunfall",
		"Scent Of Blood",
		"Unkillable", "Unkillable", "Unkillable",
		"Hirearchy",
		"Abyssal Strain", "Abyssal Strain", "Abyssal Strain",
		"Harvesters", "Harvesters",
		"Harrow",
		"Exhumed Cards",
		"Shadows",
		"Twilight",
		"Crosswired",
		"Heartless Man", "Heartless Man",
		"Rot Flower", "Rot Flower",
		"Brutality Cross",
		"Dozers", "Dozers", "Dozers",
		"Unity",
		"Restless",
		"Paleknight", "Paleknight",
		"Weakened",
		"Convergent", "Convergent",
		"Divergent", "Divergent",
		"Seams", "Seams", "Seams",
		"Penance", "Penance" "Penance",
		"The Sick", "The Sick", "The Sick",
		"Stuffed Toy", 
		"Twisted Mirror",
		"Help From Down Below",
		"Watchful Eye",
		"Dark Gods Rejoice"

}, 

{"Queen of Hearts", 
"King of Clubs", 
"Nine of Spade", 
"Jack of Hearts", 
"Two of Aces", 
"Jack of Clubs"} };

vector<string> deckNames = {"Eclipse", "Soulless"};
int currentDeck = 0;

string helpText = "Info:\n  This is a card deck shuffler and drawer, must input a deck of cards as a text file. In the format of ''Card1 Count, Card2 Count''.\n  Write Clear to clear the screen.\n  Write Shuffle to Shuffle current Deck or Shuffle Cut to shuffle cut the current Deck.\n  Write Select and Deck Name to Select another Deck Name.\n  Write ADD DECK to add another Deck.\n  Write Draw to Draw a card or write draw and a number to draw a number of cards.\n  Write Peak to look at a card or write Peak and a number to look at a number of cards.\n  Write Print to print out the entire Deck of cards.\n  Write Swtich and a Deck name to switch to that deck.\n  Write Help to see this help menu again.\n";




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

	if (parsedInput.at(0) == "clear" || parsedInput.at(0) == "Clear")
	{
		system("CLS");
		return "";
	}
	else if (parsedInput.at(0) == "help" || parsedInput.at(0) == "Help")
	{
		return "\u001b[2m" + helpText + "\u001b[0m";
	}
	else if (parsedInput.at(0) == "draw" || parsedInput.at(0) == "Draw")
	{
		string cards;
		int toDraw = 1;
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
					toDraw = stoi(parsedInput.at(1));
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

		for (int i = 0; i < toDraw; i++)
		{
			cards += decks.at(currentDeck).at(0);
			decks.at(currentDeck).push_back(decks.at(currentDeck).at(0));
			decks.at(currentDeck).erase(decks.at(currentDeck).begin());
			if (i < toDraw - 1)
			{
				cards += ", ";
			}
		}

		string drawnCard;
		drawnCard += "Card: " + cards + "\n";
		return drawnCard;
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
	else if (parsedInput.at(0) == "print" || parsedInput.at(0) == "Print")
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
	else if (parsedInput.at(0) == "peak" || parsedInput.at(0) == "Peak")
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
	else if (parsedInput.at(0) == "shuffle" || parsedInput.at(0) == "Shuffle")
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
	else if (parsedInput.at(0) == "count" || parsedInput.at(0) == "Count")
	{
		string shuffled;
		shuffled += "\u001b[32m";
		shuffled += "Count: " + std::to_string(decks[currentDeck].size());
		shuffled += "\u001b[37m";
		shuffled += "\n";
		return shuffled;
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
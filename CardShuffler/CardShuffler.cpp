#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>



// variables
std::random_device rd;
std::mt19937 g(rd());
std::vector<std::vector<std::string>> decks = { 
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
		"Penance", "Penance", "Penance",
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

std::vector<std::string> deckNames = {"Eclipse", "Soulless"};
int currentDeck = 0;

std::string helpText = "Info:\n  This is a card deck shuffler and drawer, must input a deck of cards as a text file. In the format of ''Card1 Count, Card2 Count''.\n  Write Clear to clear the screen.\n  Write Shuffle to Shuffle current Deck or Shuffle Cut to shuffle cut the current Deck.\n  Write Select and Deck Name to Select another Deck Name.\n  Write ADD DECK to add another Deck.\n  Write Draw to Draw a card or write draw and a number to draw a number of cards.\n  Write Peak to look at a card or write Peak and a number to look at a number of cards.\n  Write Print to print out the entire Deck of cards.\n  Write Swtich and a Deck name to switch to that deck.\n  Write Help to see this help menu again.\n";




// function declerations

std::string ParseInput(std::string input);
std::vector<std::string> Shuffle(std::vector<std::string> deck, std::string shuffleType);




// main function
int main()
{
    std::cout << "\u001b[2m" << helpText << "\u001b[0m";

	while (true)
	{
        std::string unparsedInput;

        std::getline(std::cin, unparsedInput);

        std::cout << ParseInput(unparsedInput);
	}
}


std::string ParseInput(std::string input)
{
    std::vector<std::string> parsedInput;
    std::string stored;

	input += " ";

	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == ' ') 
		{
			if (stored != "") parsedInput.push_back(stored);
			stored = "";
		}
		else
		{
			stored += input[i];
		}
	}

	if (parsedInput[0] == "clear" || parsedInput[0] == "Clear")
	{
        std::cout << "\033[2J\033[H";
		return "";
	}
	else if (parsedInput[0] == "help" || parsedInput[0] == "Help")
	{
		return "\u001b[2m" + helpText + "\u001b[0m";
	}
	else if (parsedInput[0] == "draw" || parsedInput[0] == "Draw")
	{
        std::string cards;
		int toDraw = 1;
		if (parsedInput.size() > 1)
		{
			bool hasNumber = false;
			for (int i = 0; i < parsedInput[1].size(); i++)
			{
				if (isdigit(parsedInput[1][i]))
				{
					hasNumber = true;
					break;
				}
			}
			if (hasNumber)
			{
				if (std::stoi(parsedInput[1]) > decks[currentDeck].size() - 1)
				{
                    std::string errorMSG;
					errorMSG += "\u001b[31m";
					errorMSG += "Error: Not a valid ammount!";
					errorMSG += "\u001b[37m";
					errorMSG += "\n";
					return errorMSG;
				}
				else
				{
					toDraw = stoi(parsedInput[1]);
				}

			}
			else
			{
                std::string errorMSG;
				errorMSG += "\u001b[31m";
				errorMSG += "Error: Not a valid ammount!";
				errorMSG += "\u001b[37m";
				errorMSG += "\n";
				return errorMSG;
			}
		}	

		for (int i = 0; i < toDraw; i++)
		{
			cards += decks[currentDeck][0];
			decks[currentDeck].push_back(decks[currentDeck][0]);
			decks[currentDeck].erase(decks[currentDeck].begin());
			if (i < toDraw - 1)
			{
				cards += ", ";
			}
		}

        std::string drawnCard;
		drawnCard += "Card: " + cards + "\n";
        return drawnCard;
	}
	else if (parsedInput[0] == "switch" && parsedInput.size() > 1)
	{
		for (int i = 0; i < deckNames.size(); i++)
		{
			if (deckNames[i] == parsedInput[1])
			{
				currentDeck = i;
				return "Current Deck: " + parsedInput[1] + "\n";
			}
		}

		return "No Deck of matching name found\n";
	}
	else if (parsedInput[0] == "print" || parsedInput[0] == "Print")
	{
        std::string cards;
		for (int i = 0; i < decks[currentDeck].size(); i++)
		{
			cards += decks[currentDeck][i];
			if (i < decks[currentDeck].size() - 1)
			{
				cards += ", ";
			}
		}

        std::string fullDeck;
		fullDeck += "Deck: " + cards + "\n";
		return fullDeck;
	}
	else if (parsedInput[0] == "peak" || parsedInput[0] == "Peak")
	{
        std::string cards;
		int toPull = 1;
		if (parsedInput.size() > 1)
		{
			bool hasNumber = false;
			for (int i = 0; i < parsedInput[1].size(); i++)
			{
				if (std::isdigit(parsedInput[1][i]))
				{
					hasNumber = true;
					break;
				}
			}
			if (hasNumber)
			{
				if (std::stoi(parsedInput[1]) > decks[currentDeck].size() - 1)
				{
                    std::string errorMSG;
					errorMSG += "\u001b[31m";
					errorMSG += "Error: Not a valid ammount!";
					errorMSG += "\u001b[37m";
					errorMSG += "\n";
					return errorMSG;
				}
				else
				{
					toPull = std::stoi(parsedInput[1]);
				}

			}
			else
			{
                std::string errorMSG;
				errorMSG += "\u001b[31m";
				errorMSG += "Error: Not a valid ammount!";
				errorMSG += "\u001b[37m";
				errorMSG += "\n";
				return errorMSG;
			}
		}

		for (int i = 0; i < toPull; i++)
		{
			cards += decks[currentDeck][i];

			if (i < toPull - 1)
			{
				cards += ", ";
			}
		}

        std::string pulledCard;
		pulledCard += "Peak Cards: " + cards + "\n";
		return pulledCard;
	}
	else if (parsedInput[0] == "shuffle" || parsedInput[0] == "Shuffle")
	{
		if (parsedInput.size() > 1)
		{
			if (parsedInput[1] == "cut")
			{
				decks[currentDeck] = Shuffle(decks[currentDeck], "cut");

                std::string shuffled;
				shuffled += "\u001b[32m";
				shuffled += "Cut!";
				shuffled += "\u001b[37m";
				shuffled += "\n";
				return shuffled;
			}
		}
		else
		{
			decks[currentDeck] = Shuffle(decks[currentDeck], "normal");

            std::string shuffled;
			shuffled += "\u001b[32m";
			shuffled += "Shuffled!";
			shuffled += "\u001b[37m";
			shuffled += "\n";
			return shuffled;
		}
	}
	else if (parsedInput[0] == "count" || parsedInput[0] == "Count")
	{
        std::string shuffled;
		shuffled += "\u001b[32m";
		shuffled += "Count: " + std::to_string(decks[currentDeck].size());
		shuffled += "\u001b[37m";
		shuffled += "\n";
		return shuffled;
	}
	else
	{
        std::string error;
		error = "\u001b[31m";
		error += "ERROR: ";
		error += "\u001b[37m";
		error += "''" + input + "\b'' " + "\u001b[31m" + "Is not a command" + "\u001b[37m";
		error += "\n";
		return error;
	}
    std::string error;
	error = "\u001b[31m";
	error += "ERROR: ";
	error += "\u001b[37m";
	error += "''" + input + "\b'' " + "\u001b[31m" + "Is not a command" + "\u001b[37m";
	error += "\n";
	return error;
}


std::vector<std::string> Shuffle(std::vector<std::string> deck, std::string shuffleType)
{
	if (shuffleType == "normal")
	{
        std::shuffle(deck.begin(), deck.end(), g);

		return deck;
	}
	else if (shuffleType == "cut")
	{
		int halfDeck = deck.size() / 2;

		for (int i = 0; i < halfDeck; i += 2)
		{
			swap(deck[i], deck[halfDeck + i]);
		}

		return deck;
	}
	else
	{
        std::string error;
		error = "\u001b[31m";
		error += "ERROR: ";
		error += "Not a shuffle method";
		error += "\u001b[37m";
		error += "\n";
        std::cout << error;
		return deck;
	}
}

#include <iostream>
#include <ctime>

using namespace std;

void PrintIntroduction(int difficulty)
{
	cout << "\n\nYou are a secret agent breaking into a level "<< difficulty;
	cout << " secure server room...\nEnter the correct code to continue...\n\n";
}

bool PlayGame (int difficulty)
{
	PrintIntroduction(difficulty);

	//Generate Code
	const int codeA = rand() % difficulty + difficulty;
	const int codeB = rand() % difficulty + difficulty;
	const int codeC = rand() % difficulty + difficulty;

	const int codeSum = codeA + codeB + codeC;
	const int codeProduct = codeA * codeB * codeC;

	//Print codeSum and codeProduct to the terminal
	cout << "+ There are 3 numbers in the code";
	cout << "\n+ The code adds up to: " << codeSum;
	cout << "\n+ The code multiplies to give: " << codeProduct << endl;

	//Store player guess
	int guessA, guessB, guessC;

	cin >> guessA >> guessB >> guessC;

	int guessSum = guessA + guessB + guessC;
	int guessProduct = guessA * guessB * guessC;

	//check if players guess is correct
	if (guessSum == codeSum && guessProduct == codeProduct)
	{
		cout << "\n*** Well done agent! you have extracted a file! Keep going! ***";
		return true;
	}
	else
	{
		cout << "\n*** You entered the wrong code! Careful agent! Try again! ***";
		return false;
	}
}

int main()
{
	srand(time(NULL)); //create new random sequence based on time of day

	int levelDifficulty = 1;
	int const maxDifficulty = 5;
	
	while(levelDifficulty <= maxDifficulty) // Loop game until all levels are completed
	{
		bool bLevelComplete = PlayGame(levelDifficulty);
		cin.clear(); //clear any errors
		cin.ignore(); //discard the buffer

		if(bLevelComplete)
		{
			++levelDifficulty;
		}
	}
	cout << "\n*** Great work agent! You got all the files! Now get out of there! ***\n";
	return 0;
}

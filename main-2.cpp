#include <iostream> // used to input and output in the console
#include <string> // used to declare strings of text as a variable
#include <cstdlib> // used to generate the random number
#include <ctime> // used to seed the random number generator
#include <windows.h>
#include <vector>

using namespace std;

void playerGridOut(int lower, int higher, int playerGuess, int enemy)
{
    const int arrSize = 8; // sets the size of the array
	int arrNum = 0; // the value of each element in the array
	int my2DArr[arrSize][arrSize]; //2D array
    vector <int> pastGuesses;
    pastGuesses.push_back(playerGuess);

	for (size_t row = 0; row < arrSize; row++)
	{
		for (size_t coloumn = 0; coloumn < arrSize; coloumn++) //nested for loop to set the value of each element in the array
		{
			arrNum++; // increases the value of the element
			my2DArr[row][coloumn] = arrNum ; // sets the value of each element
		}
	}

	for (size_t row = 0; row < arrSize; row++)
	{
		for (size_t coloumn = 0; coloumn < arrSize; coloumn++) //nested for loop to display the grid to the player
		{
			if (my2DArr[row][coloumn] <= lower || my2DArr[row][coloumn] >= higher) // marks out the upper and lower range to give the plyaer a visula
            {
                cout << " [X] ";
			}
			else cout << " [ ] ";
		}

            cout << "\n";//Your past guesses are ";
//		for (int element = pastGuesses.begin(); element != pastGuesses.end(); element++)
//        {
//            cout << *element << " ";
//        }

	}

}

void instructions() // Function that houses the instructions to easily find and modify it
{
    cout << "Welcome to the SkyNet HK-Aerial: War-games. You will be "
         << "playing against two AI drones to find and eliminate the "
         << "target. The two AIs will be using different search methods, "
         << "one will use a linear search method, the second AI will use "
         << "a random search method that modifies its range each guess. "
         << "After all you and both the drones have found the target, "
         << "the program will output the results. You are looking for "
         << "the enemy in an 8x8 grid, numbered 1 - 64. \n";
}
void gridOut(int enemy) //outputs the grid after player makes a guess
{
    const int arrSize = 8; // sets the size of the array
	int arrNum = 0; // the value of each element in the array
	int my2DArr[arrSize][arrSize]; //2D array



	for (size_t row = 0; row < arrSize; row++)
	{
		for (size_t coloumn = 0; coloumn < arrSize; coloumn++) //nested for loop to set the value of each element in the array
		{
			arrNum++; // increases the value of the element
			my2DArr[row][coloumn] = arrNum ; // sets the value of each element
		}
	}

	for (size_t row = 0; row < arrSize; row++)
	{
		for (size_t coloumn = 0; coloumn < arrSize; coloumn++) //nested for loop to display the grid to the player
		{
			if (my2DArr[row][coloumn] == enemy) // marks the grid with where the enemy is so the player knows during the AI turn
			{
			    cout << " [X] ";
			}
			else cout << " [ ] ";
		}

		cout << "\n";
	}
    cout << "\n";
}
int randomAISeach (int enemy) // the function that houses the random AI
{
    int randomGuess = 0; // what the AI is guessing
    int numberOfAIGuesses = 1; // How many guesses the AI has made
    int maximum = 64; // the maximum number the AI can guess
    int minimum = 1; // the minimum number the AI can guess

    string divider = "----------------------------------------\n\n"; // put in to minimize the amount of lines of code

    cout << "\nGenerating random enemy position on the 8x8 grid....."
         << "Enemy located at #" << enemy << ". The grid looks like this: \n\n";

    gridOut(enemy);

    while (randomGuess != enemy) // runs the following code as long as the AI hasn't guessed the answer.
    {
        int range = maximum - minimum + 1; // the range of numbers the AI can guess
        randomGuess = rand() % range + minimum; // generates the random guess
        cout << "The SkyNet AI controlled Drone is sending out ping #" << numberOfAIGuesses << "\n";
        if (randomGuess < enemy) // checks to see if the guess is lower then the location of the target
        {
            minimum = randomGuess + 1; // changes the minimum value to one higher then the last guess
            cout << "The AI pinged location " << randomGuess << " and it was lower than the actual location. \n"
                 << "The new lower limit of the range is: " << minimum << "\n" << divider;
            numberOfAIGuesses++; // increases the number of guesses

        }
        else if (randomGuess > enemy) // checks to see if the guess is higher then the location of the target
        {
            maximum = randomGuess - 1; // changes the maximum value to one lower then the last guess
            cout << "The AI pinged location " << randomGuess << " and it was higher than the actual location. \n"
                 << "The new higher limit of the range is: " << maximum << "\n" << divider;
            numberOfAIGuesses++; // increases the number of guesses

        }
        else
        {
            cout << "The AI pinged location " << randomGuess << " and it was the actual location. \n\n\n";
        }
        Sleep(2000);
    }

    return numberOfAIGuesses; // returns how many guesses the AI took.
}
int main()
{
	instructions(); // calls the function that houses the instructions
	char playAgain = 'y'; // used to check if the player wants to play again
	while (playAgain == 'y') // runs the program as long as the player wants to play
	{
	    srand(time(NULL)); // seed the random number generator
        int lowerLimit = 0;
        int upperLimit = 65;
	    int playerGuess; // what the player guesses
	    int numberOfGuesses = 0; // how many guesses the player has made
    	int enemyPosition = rand() % 64 + 1; // randomly assigns the enemy's position in the grid
	    while (playerGuess != enemyPosition) // runs the main bit of code as long as the player hasn't guessed correctly
	    {
	        cout << "\nPlease make a guess at where you think the target is located. \n";
	        cin >> playerGuess;
	        if (playerGuess >= 1 && playerGuess <= 64) // used to make sure the guess the player made was valid
	        {
    	        numberOfGuesses++; // increases the number of guesses
                if (playerGuess <= lowerLimit || playerGuess >= upperLimit)
                {
                    cout << "\nYou have already ruled out that option. Please try again. \n";
                    playerGridOut(lowerLimit, upperLimit, playerGuess, enemyPosition);
                }
                else if (playerGuess < enemyPosition)
                {
                    cout << "\nYour guess was too low. \n";
                    lowerLimit = playerGuess;
                    playerGridOut(lowerLimit, upperLimit, playerGuess, enemyPosition);
                }
                else if (playerGuess > enemyPosition)
                {
                    cout << "\nYour guess was too high. \n";
                    upperLimit = playerGuess;
                    playerGridOut(lowerLimit, upperLimit, playerGuess, enemyPosition);
                }
                else
                {
                    cout << "\nYou correctly guessed the targets location. \n\n";
                    playerGridOut(lowerLimit, upperLimit, playerGuess, enemyPosition);
                }
	        }
	        else
	        {
    	        cout << "\nSorry, that guess is not valid. Please choose between 1 and 64. \n" ;
	        }
	    }
	    int numberOfAIGuesses = randomAISeach(enemyPosition); // runs the random search AI function
	    cout << "The target was successfully located by both drones and the player. \n"
             << "The target was located at node # " << enemyPosition << ". \n"
	         << "It took the you, the player, " << numberOfGuesses << " attempts. \n"
	         << "It took the AI using linear search " << enemyPosition << " attempts. \n"
	         << "It took the AI using random search " << numberOfAIGuesses << " attempts. \n";


	    cout << "Would you like to try the simulation again? (y/n)";
	    cin >> playAgain;
	}
	system("pause"); // pauses the screen till user hits a key to continue
	return 0;
}

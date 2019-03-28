#include <iostream> // used to input and output in the console
#include <string> // used to declare strings of text as a variable
#include <cstdlib> // used to generate the random number
#include <ctime> // used to seed the random number generator
#include <windows.h> // used to call the Sleep function to simulate the AI thinking about its next move. Not necessary to have the program work but adds a nice touch
#include <vector> // used to assign vectors as a variable

using namespace std;

void playerGridOut(int lower, int higher, int playerGuess, int enemy, vector <int> pastGuesses) // function the outputs a grid when the player makes a guess
{
    const int amountOfRows = 8; // sets the amount of rows in the 2D array
	const int amountOfColumns = 8; // sets the amount of columns  in the 2D array
	int arrayValue = 0; // the value of each element in the array
	int my2DArr[amountOfRows][amountOfColumns]; //2D array
    //nested for loop to set the value of each element in the array
	for (size_t row = 0; row < amountOfRows; row++) // used to get the row in the 2d Array
	{
		for (size_t column = 0; column < amountOfColumns; column++) // used to get the column in the 2d Array
		{
		    arrayValue++; // increases the value of the element
			my2DArr[row][column] = arrayValue ; // sets the value of each element
		}
	}
    //nested for loop to display the grid to the player
	for (size_t row = 0; row < amountOfRows; row++)// used to get the row in the 2d Array
	{
		for (size_t column = 0; column < amountOfColumns; column++) // used to get the row in the 2d Array
		{
		    if (my2DArr[row][column] <= lower || my2DArr[row][column] >= higher) // marks out the upper and lower range to give the player a visual of the scope
            {
                cout << " [X] ";
			}
			else cout << " [ ] ";
		}
        cout << "\n";
    }
    cout << "Your past guesses are: ";
    for (int guess = 0; guess != pastGuesses.size(); guess++)//for loop to run through the vector to display the players past guess
    {
        cout << pastGuesses.at(guess) << " ";
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

void gridOut(int enemy) //outputs the grid showing where the enemy is located for the AI
{
    const int amountOfRows = 8; // sets the amount of rows in the 2D array
	const int amountOfColumns = 8; // sets the amount of columns  in the 2D array
	int arrayValue = 0; // the value of each element in the array
	int my2DArr[amountOfRows][amountOfColumns]; //2D array
    //nested for loop to set the value of each element in the array
	for (size_t row = 0; row < amountOfRows; row++) // used to get the row in the 2d Array
	{
		for (size_t column = 0; column < amountOfColumns; column++) // used to get the column in the 2d Array
		{
		    arrayValue++; // increases the value of the element
			my2DArr[row][column] = arrayValue ; // sets the value of each element
		}
	}
    //nested for loop to display the grid to the player
	for (size_t row = 0; row < amountOfRows; row++)// used to get the row in the 2d Array
	{
		for (size_t column = 0; column < amountOfColumns; column++) // used to get the row in the 2d Array
		{
			if (my2DArr[row][column] == enemy) // marks the grid with where the enemy is so the player knows during the AI turn
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

    gridOut(enemy); // Call the function to output the grid

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
        Sleep(2000); // pauses the output of the program for (x) milliseconds
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
        int lowerLimit = 0; // sets the lower limit of what can be guessed
        int upperLimit = 65; // sets the upper limit of what can be guessed.
	    int playerGuess; // what the player guesses
	    int numberOfGuesses = 0; // how many guesses the player has made
    	int enemyPosition = rand() % 64 + 1; // randomly assigns the enemy's position in the grid
	    vector <int> pastGuesses; // used to store the players past guesses dynamically.
	    while (playerGuess != enemyPosition) // runs the main bit of code as long as the player hasn't guessed correctly
	    {
	        //cout << "the enemy is located at " << enemyPosition << "."; left in for debugging the AI quickly
	        cout << "\n\nPlease make a guess at where you think the target is located. \n";
	        cin >> playerGuess;
	        if (playerGuess >= 1 && playerGuess <= 64) // used to make sure the guess the player made was valid
	        {
    	        numberOfGuesses++; // increases the number of guesses
                if (playerGuess <= lowerLimit || playerGuess >= upperLimit) // checks to see if the players guess is
                {
                    cout << "\nYou have already ruled out that option. Please try again. \n";
                    playerGridOut(lowerLimit, upperLimit, playerGuess, enemyPosition, pastGuesses); //calls the function passing the needed information
                }
                else if (playerGuess < enemyPosition) //
                {
                     pastGuesses.push_back(playerGuess); // add the players current guess to the end of the vector
                    cout << "\nYour guess was too low. \n";
                    lowerLimit = playerGuess;//
                    playerGridOut(lowerLimit, upperLimit, playerGuess, enemyPosition, pastGuesses);//calls the function passing the needed information
                }
                else if (playerGuess > enemyPosition)//
                {
                    pastGuesses.push_back(playerGuess); // add the players current guess to the end of the vector
                    cout << "\nYour guess was too high. \n";
                    upperLimit = playerGuess;
                    playerGridOut(lowerLimit, upperLimit, playerGuess, enemyPosition, pastGuesses);//calls the function passing the needed information
                }
                else// checks to see if the player made the right guess
                {
                    pastGuesses.push_back(playerGuess); // add the players current guess to the end of the vector
                    cout << "\nYou correctly guessed the targets location. \n\n";
                    playerGridOut(lowerLimit, upperLimit, playerGuess, enemyPosition, pastGuesses);//calls the function passing the needed information
                }
	        }
	        else // outputs the following if the player makes an invalid guess outside the range of the grid
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
	return 0; // ends the program
}

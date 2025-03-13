#include <iostream> //allows input and output
#include <ctime> // time-related functions
#include <cstdlib> // used for rand() and number generation
#include <iomanip> // setw, setprecision (formatting)
#include <limits> // matters with input validation (clearing invalid input, i used this for my bool playagain code)

using namespace std;

// functionarations
void playGame(bool &, string &);
bool isTimeUp(time_t startTime, int difficulty);
bool playAgain();
void displayGameOver();
void displayScoreboard(int guesses, time_t startTime);

int main() 
{
    srand(time(0)); // Seed the random number generator

    bool impossibleMode = false; // Tracks activation
    string name;

    // Get Name
    cout << endl << "What's your name? : ";
    getline(cin, name);

    // Capitalize the first letter of name
    name[0] = toupper(name[0]);
    for (int i = 1; i < name.length(); i++) 
    {
        if (name[i - 1] == ' ') 
        {
            name[i] = toupper(name[i]);
        }
    }
    // calls playagain if they choose yes and playgame loop 
    while (true) 
    {
        playGame(impossibleMode, name); 
        if (!playAgain()) {
            break; // Exit loop if player doesnt want to play again
        }
        cout << "Starting a new round..." << endl; // Print for debugging (i ran into an issue where my code would crash, so i put this here to ensure)
    }
    // ending message
    cout << "Thanks for playing " << name << "!" << endl;
    return 0;
}

// Game logic
void playGame(bool &impossibleMode, string &name)
{
    int number, guess;
    int maxGuesses = impossibleMode ? 1 : 5; // 1 guess allowance in impossible mode, if not it stays 5
    int difficulty; 
    bool guessedCorrectly = false;
    time_t startTime = time(0); // Reset the start time every round

    // Ask for difficulty level
    do {
        cout << "Choose difficulty level, " << name << ", (1: Easy, 2: Medium, 3: Hard): ";
        cin >> difficulty;
    } while (difficulty < 1 || difficulty > 3); // Ensure valid input

    // use different responses
    int insultChoice = rand() % 3; // Random number between 0 and 2 for different responses
    switch (insultChoice) {
    case 0:
        cout << "Easy mode... are you really that sensitive?" << endl;
        break;
    case 1:
        cout << "Challenge yourself, it causes growth!" << endl;
        break;
    case 2:
        cout << "If you fail, you need to go back to kindergarten." << endl;
        break;
    default:
        cout << "You've got this!" << endl;
        break;
    }

    if (difficulty == 2)
    {
        cout << "Okay, the heat's coming...";
    }
    if (difficulty == 3)
    { 
        cout << "Let's see these skills, genius.";
    }

    // Set the max range for the random number bsaed on difficulty
    int maxRange = (difficulty == 1) ? 10 : (difficulty == 2) ? 35 : 100;
    number = rand() % maxRange + 1; // Generate random number per round

    cout << "I'm thinking of a number between 1 and " << maxRange << "." << endl;

    // Loops through until player runs out of guesse or guesses correctly, or time runs out
    for (int attempts = 1; attempts <= maxGuesses; attempts++)
    {
        if (isTimeUp(startTime, difficulty)) return; // Exit when time is out

        //aalow valid input
        while (true) {
            cout << "Attempt " << attempts << ": ";
            cin >> guess;

            if (cin.fail() || guess < 1 || guess > maxRange) {
                cin.clear(); // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                cout << "Invalid input. Please enter a number between 1 and " << maxRange << ": ";
            } else {
                break; // valid input
            }
        }

        // Check if guess is correct
        if (guess == number)
        {
            cout << "Great job, " << name << "! You guessed it in " << attempts << " tries!\n";
        
            // Level up autmoatically if guessed on the first try
            if (attempts == 1)
            {
                cout << "You leveled up automatically! Moving to a harder difficulty!\n";
                difficulty = (difficulty == 1) ? 2 : (difficulty == 2) ? 3 : 3; // Upgrade difficulty
                maxGuesses = difficulty == 3 ? 3 : (difficulty == 2 ? 4 : 5); // Update guesses per difficulty
            }

            // Easter Egg: Unlock Impossible Mode if guessed on the first try
            if (attempts == 1 && !impossibleMode)
            {
                cout << "Unlocking impossible mode... You're either a genius or a cheater. We'll see what the truth is now.\n";
                impossibleMode = true;
                maxGuesses = 1; // Set only 1 guess for impossible mode
            }

            displayScoreboard(attempts, startTime); // Show the scoreboard
            return; // Exit function after a correct guess
        }
        else 
        {
            // Give feedback if guess is incorrect
            cout << (guess < number ? "Too low." : "Too high.") << endl;
        }
    }

    // Reveal the correct number
    cout << "Your guess count is out! The answer was: " << number << "." << endl << endl;
    displayScoreboard(maxGuesses, startTime); // Show the scoreboard
}

// Check if time limit (20 seconds) is over
bool isTimeUp(time_t startTime, int difficulty)
{
    // Adjust time limit based on difficulty
    int timeLimit = (difficulty == 1) ? 30 : (difficulty == 2) ? 20 : 10;
    
    if (time(0) - startTime > timeLimit)
    {
        displayGameOver(); // Game over message
        return true; // Time has run out
    }
    return false; // Time is still in
}

// Display message when time runs out
void displayGameOver() 
{
    cout << "THE END HAS COME, time is out, loser!" << endl;
}

// Display player's stats at end of the round
void displayScoreboard(int guesses, time_t startTime) 
{
    time_t endTime = time(0);
    double timeTaken = difftime(endTime, startTime);

    int byemsg = rand() % 4; // Random number between 0 and 3
    string farewellMessage; 

    switch (byemsg) {
        case 0:
            farewellMessage = "Thank you for playing!";
            break;
        case 1:
            farewellMessage = "Try again!";
            break;
        case 2:
            farewellMessage = "Play one more time!";
            break;
        case 3:
            farewellMessage = "All-star! Let's go again!";
            break;
        default:
            farewellMessage = "Til next time!";
            break;
    }

    cout << "********** GAME RECEIPT **********" << endl;
    cout << "----------------------------------" << endl;
    cout << left << setw(25) << "Time taken:" << right << setw(5) << fixed << setprecision(2) << timeTaken << " seconds" << endl;
    cout << left << setw(25) << "Total guesses:" << right << setw(5) << guesses << endl;
    cout << "----------------------------------" << endl;
    cout << left << setw(25) << farewellMessage << endl;
    cout << "**********************************" << endl;
}

// Ask the player if they want to play again
bool playAgain() 
{
    string response;
    
    cout << "Do you want to play again? (yes/no): ";
    
    // Ensure any leftover characters in the input buffer are cleared
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input 
    getline(cin, response);  // Use getline to capture the full input string

    // Return true if response is "yes" or "y"
    return (response == "yes" || response == "y"); 
}

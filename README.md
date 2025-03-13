# Guessing Game

## Overview
The **Guessing Game** is a simple command-line program written in C++ that challenges the player to guess a randomly generated number within a specified range. The program provides hints based on the player's input, helping them to determine the correct number.

## Features
- Random number generation
- User input for guessing
- Hint system (higher/lower feedback)
- Loop until correct guess is made
- Configurable number range (if applicable)

## How to Run
1. Ensure you have a C++ compiler installed (e.g., g++ for GCC).
2. Compile the program using the following command:
   ```sh
   g++ -o GuessingGame GuessingGame.cpp
   ```
3. Run the executable:
   ```sh
   ./GuessingGame
   ```

## How to Play
1. The program will generate a random number within a specified range.
2. The user is prompted to guess the number.
3. After each guess, the program provides feedback:
   - "Too high! Try again."
   - "Too low! Try again."
4. The game continues until the correct number is guessed.
5. Upon guessing correctly, the program displays a congratulatory message and may offer to restart.

## Dependencies
- Standard C++ libraries (iostream, cstdlib, ctime)

## Possible Enhancements
- Implement a scoring system based on the number of attempts.
- Add difficulty levels (easy, medium, hard).
- Allow the user to set a custom number range.
- Add a graphical interface for better user experience.

## License
This project is open-source and free to use. Modify and distribute as needed.

## Author
Haily Watkins


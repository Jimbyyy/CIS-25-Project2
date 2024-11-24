#ifndef P02_1_GAME_H
#define P02_1_GAME_H

#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include <conio.h>
using namespace std;

enum class Difficulty { Easy, Medium, Hard };

struct Pipe {
	int xCoord;
	int topHeight;
	int bottomHeight;
};

struct Player {
	string name;
	int score;
};

class DynamicArray {
public:
	// attributes
	Player* arrPtr;
	int size;

	// constructors
	DynamicArray(int size);
	DynamicArray() = default;
	
	// destructor
	~DynamicArray();

	// resizes the array
	void resize(int newSize);
};

// ANSI clear terminal command
void clear();

// Displays the gamefield
void updateDisplay(const int HEIGHT, const int WIDTH, int& birdYCoord, int& numPipes, Pipe pipes[], int& score, int& highScore, int& difficultySpeed);

// Calculates bird physics
void birdLogic(const int HEIGHT, const int WIDTH, int& birdYCoord, int& birdVelocity);

// Handles Pipe generation and deletion
void pipeLogic(const int HEIGHT, const int WIDTH, int& birdYCoord, int& birdVelocity, int& numPipes, Pipe pipes[], bool& gameOver, int& score);

// Grabs user input and jump bird
void input(int& birdVelocity);

// Read high score from the file
void readHighScore(int& highScore);

// Write high score to the file
void writeHighScore(int& score, int& highScore);

// Display welcome message and difficulty settings
void displayWelcome(int& difficultyChoice);

// Set the difficulty enum based on user's difficulty choice
void setGameDifficulty(int& difficultyChoice, Difficulty& gameDifficulty);

// Set the difficulty speed based on difficulty speed enum
void setDifficultySpeed(Difficulty gameDifficulty, int& difficultySpeed);

// Function to display the scoreboard
void displayScoreboard(Player players[], int count);

// Function to manually sort the players by score (bubble sort)
void sortScoreboard(Player players[], int count);

// Function to load the scoreboard from the file
int loadScoreboard(Player players[]);

// Function to save the scoreboard to the file
void saveScoreboard(Player players[], int count);


#endif
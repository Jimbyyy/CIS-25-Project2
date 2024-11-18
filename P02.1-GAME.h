#pragma once
#include <iostream>
#include <ctime>
#include <fstream>
#include <windows.h>
#include <conio.h>
using namespace std;

enum class Difficulty { Easy, Medium, Hard };

struct Pipe {
	int xCoord;
	int topHeight;
	int bottomHeight;
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

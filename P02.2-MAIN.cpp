/*******************************************
Project 2: Flappy Bird
----------------------
This program runs flappy bird in the terminal!
Note that this runs in WINDOWS OS ONLY!!
********************************************/

#include "P02.1-GAME.h"

// Game constants
const int HEIGHT = 20;
const int WIDTH = 40;

int main() {

    // Initializing scoreboard variables
    int maxPlayers = 100; 
    DynamicArray players(maxPlayers);  // Array to store players
    int count = loadScoreboard(players.arrPtr);

	// Initializing game variables
	int birdYCoord = HEIGHT / 2;
	int birdVelocity = 0;
	int score = 0;
	int highScore = 0;
	bool gameOver = false;
	Difficulty gameDifficulty = Difficulty::Medium;
	int difficultyChoice = 0;
	int difficultySpeed = 100;
	Pipe pipes[10];
	int numPipes = 0;
	srand(time(nullptr));

    // Get current player name
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;

	displayWelcome(difficultyChoice);
	setGameDifficulty(difficultyChoice, gameDifficulty);
	setDifficultySpeed(gameDifficulty, difficultySpeed);

	readHighScore(highScore);

	// flappy bird game loop
	while (!gameOver) {
		updateDisplay(HEIGHT, WIDTH, birdYCoord, numPipes, pipes, score, highScore, difficultySpeed);
		input(birdVelocity);
		birdLogic(HEIGHT, WIDTH, birdYCoord, birdVelocity);
		pipeLogic(HEIGHT, WIDTH, birdYCoord, birdVelocity, numPipes, pipes, gameOver, score);
	}

	writeHighScore(score, highScore);

	clear();
	cout << "Game Over! Your final score is: " << score << endl << endl;

    // Store the new player's score
    if (count < maxPlayers) {
        players.arrPtr[count].name = playerName;
        players.arrPtr[count].score = score;
        ++count;
    }
    else {
        cout << "Sorry, the scoreboard is full!" << endl;
    }

    // Sort the players by score
    sortScoreboard(players.arrPtr, count);

    // Display the updated scoreboard
    displayScoreboard(players.arrPtr, count);

    // Save the updated scoreboard back to the file
    saveScoreboard(players.arrPtr, count);

	return 0;
}
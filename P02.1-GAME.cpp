#include "P02.1-GAME.h"

// ANSI clear terminal command
void clear() {
	// CSI[2J clears screen, CSI[H moves the cursor to top-left corner
	cout << "\x1B[2J\x1B[H";
}

// Displays the gamefield
void updateDisplay(const int HEIGHT, const int WIDTH, int& birdYCoord, int& numPipes, Pipe pipes[], int& score, int& highScore, int& difficultySpeed) {
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (y == 0) {
				cout << "#"; // TOP BORDER
			}
			else if (x == 0) {
				cout << "#"; // LEFT BORDER
			}
			else if (x == WIDTH - 1) {
				cout << "#"; // RIGHT BORDER
			}
			else if (y == HEIGHT - 1) {
				cout << "#"; // BOTTOM BORDER
			}
			else if (y == birdYCoord && x == 5) {
				cout << "0"; // BIRD CHARACTER
			}
			else {
				bool drawn = false;
				for (int i = 0; i < numPipes; i++) {
					// TOP PIPE
					if (x == pipes[i].xCoord && y < pipes[i].topHeight) {
						cout << "|";
						drawn = true;
						break;
					}
					// BOTTOM PIPE
					if (x == pipes[i].xCoord && y >= pipes[i].bottomHeight) {
						cout << "|";
						drawn = true;
						break;
					}
				}
				if (!drawn) {
					cout << " "; // SPACE BETWEEN PIPES
				}
			}
		}
		cout << endl;
	}
	cout << "Score: " << score << "   High Score: " << highScore << endl;;

	// Lets the frame hang for a moment before being updated
	Sleep(difficultySpeed);
	clear();
}

// Calculates bird physics
void birdLogic(const int HEIGHT, const int WIDTH, int& birdYCoord, int& birdVelocity) {
	// applying gravity to the bird
	birdVelocity += 1;
	birdYCoord += birdVelocity;

	// prevents bird from falling through floor
	if (birdYCoord >= HEIGHT) {
		birdYCoord = HEIGHT - 2;
	}
	// prevents bird from going through ceiling
	else if (birdYCoord <= 0) {
		birdYCoord = 1;
	}
}

// Handles Pipe generation and deletion
void pipeLogic(const int HEIGHT, const int WIDTH, int& birdYCoord, int& birdVelocity, int& numPipes, Pipe pipes[], bool& gameOver, int& score) {
	// generates new pipes if there are no pipes or a pipe has moved a certain distance
	if (numPipes == 0 || pipes[numPipes - 1].xCoord <= WIDTH - 10) {
		Pipe newPipe;
		newPipe.xCoord = WIDTH;
		newPipe.topHeight = rand() % (HEIGHT / 2); // endpoint of top pipe
		newPipe.bottomHeight = newPipe.topHeight + (rand() % 5) + 5; // starting point of bottom pipe
		pipes[numPipes++] = newPipe;  // Add the new pipe to the pipes array
	}

	// moves pipes across the screen
	for (int i = 0; i < numPipes; i++) {
		pipes[i].xCoord--;
	}

	// Remove pipes that are off the screen
	if (pipes[0].xCoord < 0) {
		for (int i = 0; i < numPipes - 1; i++) {
			pipes[i] = pipes[i + 1]; // shift pipes left in array
		}
		numPipes--; // decrement counter to the newly avaliable pipe array space
	}

	// Check collision with pipes
	for (int i = 0; i < numPipes; i++) {
		if (pipes[i].xCoord == 5) {
			if (birdYCoord < pipes[i].topHeight || birdYCoord >= pipes[i].bottomHeight) {
				gameOver = true;
			}
			else {
				score++;
			}
		}
	}
}

// Grabs user input
void input(int& birdVelocity) {
	if (_kbhit()) {
		char current = _getch();
		if (current == ' ') {
			birdVelocity = -3; // Jump
		}
	}
}

// Read high score from the file
void readHighScore(int& highScore) {
	ifstream inputFile("highScore.txt");  // Open the file for reading
	if (inputFile.is_open()) {
		inputFile >> highScore;  // Read the high score
		inputFile.close();
	}
	else {
		// If the file doesn't exist, set the high score to 0
		highScore = 0;
	}
}

// Write high score to the file
void writeHighScore(int& score, int& highScore) {
	// Update the high score if the current score is higher
	if (score > highScore) {
		highScore = score;
		ofstream outputFile("highScore.txt");  // Open the file for writing
		if (outputFile.is_open()) {
			outputFile << highScore;  // Write the high score to the file
			outputFile.close();
		}
	}
}

// Display welcome message and difficulty settings
void displayWelcome(int& difficultyChoice) {
	cout << "Welcome to Flappy Bird!" << endl;
	cout << "Choose difficulty level: " << endl;
	cout << "1. Easy" << endl;
	cout << "2. Medium" << endl;
	cout << "3. Hard" << endl;
	cin >> difficultyChoice;
}

// Set the difficulty based on user input
void setGameDifficulty(int& difficultyChoice, Difficulty& gameDifficulty) {
	switch (difficultyChoice) {
	case 1:
		gameDifficulty = Difficulty::Easy;
		break;
	case 2:
		gameDifficulty = Difficulty::Medium;
		break;
	case 3:
		gameDifficulty = Difficulty::Hard;
		break;
	default:
		cout << "Invalid choice, defaulting to Medium difficulty." << endl;
		gameDifficulty = Difficulty::Medium;
		break;
	}
}

// Set the difficulty speed based on chosen game difficulty
void setDifficultySpeed(Difficulty gameDifficulty, int& difficultySpeed) {
	switch (gameDifficulty) {
	case (Difficulty::Easy):
		difficultySpeed = 150;
		break;
	case (Difficulty::Medium):
		difficultySpeed = 100;
		break;
	case (Difficulty::Hard):
		difficultySpeed = 50;
		break;
	}
}
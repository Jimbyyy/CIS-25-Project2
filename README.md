# CIS25-Project-2

Author: Jimmy Hsu

Project: Flappy Bird in Terminal

Recording: [Video Overview Here](https://youtu.be/zZiiCWDBftI)

## Project Objective

The original objective of this project was to simulate the popular mobile game, "Flappy Bird", in the terminal. The plan was to expand beyond the scope of the last project, "Stock Simulator", by implementing adjustable difficulty settings, a highscore tracker, and a permanant score board. Unfortunately, this program will **only run on Windows** as it relies on a few key Windows specific functions. Further commit notes can be found on my [main repo](https://github.com/Jimbyyy/CiS25)

## Explanation of the Code

1. **Game Setup**: The game initializes with the bird in the center of the screen, and a score of 0. The pipe positions are randomly generated and added to the screen as the game progresses.

2. **Drawing the Screen**: The screen is "cleared" each time using ANSI escape codes. Then, the borders(#), bird (O) and the pipes (|) are drawn on the screen from right to left, top to bottom. The pipes move from right to left across the screen.

3. **Bird Physics**: Every frame, the bird will fall and accelerate due to gravity, and the bird’s Y position is updated accordingly. The player can press the space bar to make the bird jump (move up).

4. **Pipe Logic**: Pipes are generated randomly and move left across the screen. The game tracks whether the bird has passed a pipe, and increases the score if the bird successfully flies between pipes. If the bird collides with a pipe, the game ends

5. **Game Over**: The game ends if the bird collides with a pipe or goes out of bounds (top or bottom of the screen).

6. **Input Handling**: The input() function uses the _kbhit() function to detect key presses and responds to the space bar for jumping.

7. **Score Tracking**: The game records the player's highest score to a text file so that it is saved between different playthroughs.

8. **Dynamic Scoreboard**: The game records the name and score of the player to a text file and sorts it for display at the end of each game so that multiple player's scores can be seen from highest to lowest.

## Project Takeaways

- The largest hurdle by far was trying to research a way to clear the terminal screen in order to sequentially display frames to mimic motion. Much time was devoted to searching webforums for non-OS specific methods of clearing the terminal, and I eventually was able to stumble upon ANSI escape codes, which was more preferable to using Window's system commands.
    - Unfortunately, I still had to use OS specific libraries like `Sleep()` from `windows.h` and `_kbhit()` and `_getch()` from `conio.h` due to the frame-by-frame nature of my program. Initially I planned on using `cin.getline()` to take the spacebar as an input, however, I was quickly stumped by the fact that `cin` and `getline` pause the program execution, which unfortunately also prevented the drawing of new frames and the entire game execution at large. Some research yieled multi-threading as a potential solution, however that was far beyond my technical expertise to implement.
    - This does unfortunately mean that this project is a **Windows exclusive program**.
    - This was one of the first times I had to properly sit down and write out detailed notes for the logic of my game on paper in psuedo-code in order to figure out how to program a "refresh rate" into the terminal. It was a fun excercise.

- The next largest hurdle was actually creating the game. Rendering a "viewing frame" and the "flappy bird" with ascii characters was easy enough, as well as simulating implementing simple physics like gravity and collision for said "flappy bird". Pipe dynamic generation, deletion, and rendering however, was far more difficult to plan and create, and required extensive time to debug and plan

- Over the course of the project, a large chunk of time amount of time was spent figuring out how to refactor the code. As this was my first time programming a real-time video game, my program initally made use of a slew of global variables located in the header file, which made implenting additional infastructure like score-board tracking extremely difficult. A class seemed like a potenially answer, but I encountered difficulties implenting a class due to all my functions requiring direct access to global variables. As such, I ultimitely compromised by making all my function parameters pass-by-reference, and initializing and storing my variables in my main function.

- Creating a simple difficulty adjustment using enumerations was needlesly difficult as well. Just figuring out how to adjust the difficulty of the game via my programs game logic took a little bit of effort. Initally I had planned on changing the speed at which pipes would approach the player by multiplying their x-coordinate translation rate, however, the collision detection logic for the pipes relied directly on reading the coordinate location of the pipes, so having them "jump" forwards faster was out of the question. I ultimitely ended up manipulating the frame-rate of the program via the `Sleep()` function, as the speed of the game is directly proportional to it.

- Score keeping was a simple enough thing to keep track of, and exporting the user's highest score to an external text file for reading and writing was relatively simple as well. When it came to figuring out how to make a dynamic scoreboard, however, I had a real headache; trying to figure out how to create my own dynamic array class to store as many users as I wanted with custom operator overloading and inputs parameters turned out to be quite a difficult task. I unfortunately ran out of time on this front due to project deadlines, so it had to be cut. Some remnant code is still inside the program for it though in the form of a few null pointers.
    + UPDATE: I added a custom scoreboard. It was a bit difficult trying to figure out how to read multiple things at once from a file. Ultimitely I ended up using spaces and newlines to leverage the fact that `getline()` stops reading at spaces and newlines.
    + How I ended up solving my previous dilemna was by breaking up my problem into smaller chunks. I knew I wanted parallized arrays initially, but that ended up posing a huge logistical overhead for implementing ways to read and sort data. So instead of using paralleized arrays, I ended up grouping player score and name data into a struct called `Player`, and making an array of structs! Then it was jsut a matter of figuring out how to format my external text file and reading off of it onto my custom Player array for display!
        - For rapid prototyping's sake, I ended up not making use of my `DynamicArray`'s `resize()` methong. As of writing, I still have not implented it into my program. It is unlikely I will have time to finish that in the near future ahh...

- Coming out of this project, I have a newfound respect for all the groundwork laid down the professional game devlopers of this world. It was a very fun (but stressful) experience learning how to simulate basic physics and motion in the terminal. It was great falling into the same pitfalls as old games too, such as having game logic tied directly to the computers framerate.
    - I think the biggest take-away I have is the importance of planning ahead and the downfalls of technical debt. It was extremely demoralizing to have to refactor my code in the middle of my project, and I hope to minimize the amount of times I need to do that in the future.

## Program Screenshots: 

<img width="858" alt="image" src="https://github.com/user-attachments/assets/a72657ee-7674-4661-9f3c-2a95c1527f77">

<img width="857" alt="image" src="https://github.com/user-attachments/assets/919489a7-c015-49c0-bae5-089222390813">

<img width="854" alt="image" src="https://github.com/user-attachments/assets/0afd02bb-d154-48e2-a1f9-3bc0c94292dc">


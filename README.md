<h1 align="center">Paciência Data Structure 🃏</h1>

## Developed by 💻:

- [Gabriel Reis](https://github.com/GabrielBReis).
- [Vinícius de Araújo e Souza]( ).

## Special Thanks:

- [Márcio Soussa](https://www.linkedin.com/in/marcio-soussa/?originalSubdomain=br), our teacher, your experience and knowledge have been invaluable to our progress.

## About 🤔:

This repository contains the source code for the console-based Paciência game, developed for the "Algorithms and Data Structures I" course at SENAI CIMATEC in 2022. The game makes use of various data structures and algorithms, including:

- Stack: Used to manage the order of gameplay actions and track the move history.

- Singly Linked List: Responsible for storing and managing the Paciência cards for each player, allowing efficient manipulation of player hands.

- Doubly Linked List: Represents the game board, offering flexibility to add and remove cards during gameplay.

- Array: Employed to store and manage the game board state, player scores, and other relevant information in a structured manner.

- Sorting Algorithms: Incorporated to organize the Paciência cards in a specific order, facilitating efficient search and selection during gameplay.

This project demonstrates the practical application of algorithmic thinking and data structure implementation to create a functional Paciência game in a console environment.

## Features 🧑‍🔬:

- Single-player gameplay modes: The game offers a mode for a single player, providing an individual gaming experience.

- Victory condition based on foundation completion: The game checks if all 52 cards have been moved to the foundations, declaring the player as the winner in that case.

- Termination condition: The game ends when all foundations are filled with the correct cards in ascending order for each suit, indicating the player's victory.

- Card visualization: The game displays the available cards for movement and allows the player to plan strategies based on the visible cards.

- Feedback and move validation: The game provides feedback for each move made by the player, ensuring that only valid moves are executed, avoiding invalid actions during the game.

## Dependencies 🚚:

Paciência game dependencies include the standard C and C++ libraries and:

- ```<conio.h>```.
- ```<Windows.h>```.

Ensure you have all dependencies before running this Paciência game.

## How to Run 🏃:

First, clone this repository. Then, compile the ```pacience_game.c``` file with the command:

    gcc ./src/pacience_game.c -o pacience_game

Next, execute the newly generated executable with:

    ./pacience_game

## Development Process ⚙️:

The development of the Paciência game in C was informally done, without any specific methodology. Developers would gather in calls and code together, helping each other out.

### Tools Used 🛠️: 

- [VSCode](https://code.visualstudio.com/).

## How to Contribute 🫂:

Feel free to create a new branch, fork the project, or get in touch with us to contribute to this Paciência game.

## License 📜:

[Apache V2](https://choosealicense.com/licenses/apache-2.0/)

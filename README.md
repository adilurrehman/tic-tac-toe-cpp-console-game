# Tic-Tac-Toe C++ Console Game

A feature-rich C++ console Tic-Tac-Toe game with user authentication, smart AI opponent, lives system, score tracking, and persistent high scores. Supports PvP and PvC modes.

## Features

### Core Features
- **User Authentication System**: Secure registration and login with username/password
- **Smart AI Opponent**: Minimax algorithm for challenging gameplay
- **Lives System**: Each player has 3 lives; lose all lives and you're out!
- **Score Tracking**: Track wins, losses, and draws for each player
- **Persistent High Scores**: Top 10 high scores saved to disk
- **Two Game Modes**:
  - **PvP (Player vs Player)**: Challenge another human player
  - **PvC (Player vs Computer)**: Battle against the AI

### Game Mechanics
- Classic 3x3 Tic-Tac-Toe grid
- Turn-based gameplay with clear visual board
- Input validation and error handling
- Player statistics tracking
- File-based data persistence

## Requirements

- C++ compiler with C++11 support (g++, clang++, etc.)
- Make (optional, for using Makefile)
- Unix-like system (Linux, macOS) or Windows with appropriate terminal

## Building the Game

### Using Make
```bash
make
```

### Manual Compilation
```bash
g++ -std=c++11 -Wall -Wextra -o tictactoe main.cpp
```

## Running the Game

```bash
./tictactoe
```

Or with Make:
```bash
make run
```

## How to Play

### First Time Setup
1. **Register**: Create a new account with username and password
2. **Login**: Use your credentials to log in

### Main Menu Options
- **Register**: Create a new user account
- **Login**: Access your account
- **View High Scores**: See top 10 players
- **Exit**: Quit the game

### After Login
- **Play vs Computer (PvC)**: Challenge the AI opponent
- **Play vs Player (PvP)**: Play against another registered player
- **View My Stats**: Check your wins, losses, draws, and remaining lives
- **View High Scores**: See leaderboard
- **Logout**: Return to main menu

### During Gameplay
- The board is numbered from 1-3 for rows and columns
- Enter row number (1-3) and column number (1-3) when prompted
- First player uses 'X', second player (or computer) uses 'O'
- Three in a row wins the game!
- Lives are deducted when you lose a game
- Score is calculated based on wins and remaining lives

### Lives System
- Each player starts with 3 lives
- Losing a game costs 1 life
- When lives reach 0, that account can no longer play
- Lives are persistent across sessions

### Scoring System
- Score = (Wins × 10) + (Remaining Lives × 5)
- Higher scores appear on the leaderboard
- Only top 10 scores are kept

## File Structure

```
tic-tac-toe-cpp-console-game/
├── main.cpp           # Main game source code
├── Makefile          # Build configuration
├── README.md         # This file
├── .gitignore        # Git ignore rules
├── users.dat         # User data (auto-generated)
└── highscores.dat    # High scores (auto-generated)
```

## Data Persistence

The game creates two data files:
- **users.dat**: Stores user credentials and statistics
- **highscores.dat**: Stores top 10 high scores

These files are automatically created when needed and updated after each game.

## AI Algorithm

The computer opponent uses the **Minimax algorithm**, which:
- Evaluates all possible game outcomes
- Chooses the optimal move
- Provides a challenging experience
- Never makes mistakes (perfect play)

## Cleaning Up

To remove compiled files and data:
```bash
make clean
```

This removes:
- The executable (`tictactoe`)
- User data (`users.dat`)
- High scores (`highscores.dat`)

## Example Gameplay

```
========================================
   TIC-TAC-TOE - Feature-Rich Edition
========================================

Logged in as: Player1
Lives: 3

1. Play vs Computer (PvC)
2. Play vs Player (PvP)
3. View My Stats
4. View High Scores
5. Logout

Choose an option: 1

     1   2   3
   +---+---+---+
 1 |   |   |   |
   +---+---+---+
 2 |   |   |   |
   +---+---+---+
 3 |   |   |   |
   +---+---+---+

Player1 (X) vs Computer (O)
Player1 Lives: 3 | Computer Lives: Unlimited

Player1's turn (X)
Enter row (1-3): 2
Enter column (1-3): 2
```

## Technical Details

- **Language**: C++11
- **Architecture**: Object-oriented design with classes for:
  - Board: Game board management
  - User: Player data structure
  - UserAuth: Authentication system
  - HighScoreSystem: Score management
  - AIPlayer: Computer opponent with Minimax
  - Game: Game engine and logic
- **Data Storage**: Simple file-based persistence
- **Input Handling**: Robust error checking and validation

## Future Enhancements (Ideas)

- Different difficulty levels for AI
- Tournament mode with brackets
- Network multiplayer
- Graphical user interface
- Sound effects
- Customizable board sizes
- Time limits per move
- Undo/redo functionality
- Game replay feature

## Security Notes

**Important:** This is a demonstration project for educational purposes. Please note:

- Passwords are stored in plain text in the `users.dat` file
- For production use, passwords should be properly hashed (e.g., using bcrypt or SHA-256)
- Usernames and passwords must not contain spaces (validated during registration)
- Data files should be protected with appropriate file permissions

This implementation prioritizes code clarity and educational value over production-grade security.

## License

This project is open source and available for educational purposes.

## Author

Created as a comprehensive C++ console game demonstration.

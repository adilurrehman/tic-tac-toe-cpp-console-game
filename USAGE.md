# Tic-Tac-Toe Game Usage Guide

## Quick Start

1. Build the game:
   ```bash
   make
   ```

2. Run the game:
   ```bash
   ./tictactoe
   ```

## Walkthrough

### Step 1: Register a User
When you first run the game, you'll see the main menu:
```
========================================
   TIC-TAC-TOE - Feature-Rich Edition
========================================

1. Register
2. Login
3. View High Scores
4. Exit

Choose an option:
```

Choose option `1` to register:
- Enter a username (e.g., "alice")
- Enter a password (e.g., "pass123")

### Step 2: Login
After registration, choose option `2` to login:
- Enter your username
- Enter your password

Once logged in, you'll see:
```
Logged in as: alice
Lives: 3

1. Play vs Computer (PvC)
2. Play vs Player (PvP)
3. View My Stats
4. View High Scores
5. Logout
```

### Step 3: Play Against Computer
Choose option `1` to play against the AI:
- The game board will be displayed
- Enter row number (1-3) when prompted
- Enter column number (1-3) when prompted
- Try to get three X's in a row before the computer does!

Example moves:
```
     1   2   3
   +---+---+---+
 1 |   |   |   |
   +---+---+---+
 2 |   |   |   |
   +---+---+---+
 3 |   |   |   |
   +---+---+---+

Player1's turn (X)
Enter row (1-3): 2
Enter column (1-3): 2
```

### Step 4: Play Against Another Player
Choose option `2` to play PvP:
- The opponent must also be registered
- Enter opponent's username and password
- Take turns making moves

### Step 5: View Statistics
Choose option `3` to see your stats:
```
=== alice's Stats ===
Wins: 5
Losses: 2
Draws: 1
Lives Remaining: 1
Total Games: 8
```

### Step 6: View High Scores
Choose option `4` to see the leaderboard:
```
=== HIGH SCORES ===
1. alice - 65 points
2. bob - 45 points
3. charlie - 30 points
```

## Tips

- **Lives Management**: You start with 3 lives. Each loss costs 1 life. When you reach 0 lives, create a new account!
- **Strategy**: Against the AI, try to block its moves and create multiple winning threats
- **Scoring**: Wins give more points, but keeping your lives helps too!
- **Practice**: The AI uses perfect strategy (minimax), so it's quite challenging

## Common Issues

### Invalid Move
- Make sure the cell is empty (not already X or O)
- Enter numbers between 1-3 only

### Login Failed
- Check that you registered first
- Verify your username and password are correct
- Usernames and passwords are case-sensitive

### No Lives Left
- Create a new account to continue playing
- Your stats are saved and contribute to high scores

## Example Game Session

```bash
./tictactoe

# At main menu, choose 1 to register
1
alice
secretpass

# Choose 2 to login
2
alice
secretpass

# Choose 1 to play vs computer
1

# Make your moves:
2
2
# Computer will respond...

1
1
# Computer will respond...

3
3
# Continue until someone wins or it's a draw

# After the game, choose 3 to see your stats
3

# Choose 5 to logout, then 4 to exit
5
4
```

Enjoy the game!

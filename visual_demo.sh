#!/bin/bash

# Script to show visual game interface examples

cat << 'EOF'

================================================================================
                    TIC-TAC-TOE GAME - VISUAL DEMO
================================================================================

SCREEN 1: Main Menu (Not Logged In)
--------------------------------------------------------------------------------
========================================
   TIC-TAC-TOE - Feature-Rich Edition
========================================

1. Register
2. Login
3. View High Scores
4. Exit

Choose an option: _
--------------------------------------------------------------------------------


SCREEN 2: Registration Process
--------------------------------------------------------------------------------
========================================
   TIC-TAC-TOE - Feature-Rich Edition
========================================

1. Register
2. Login
3. View High Scores
4. Exit

Choose an option: 1

Enter username: alice
Enter password: ********

Registration successful!
Press Enter to continue...
--------------------------------------------------------------------------------


SCREEN 3: Login Process
--------------------------------------------------------------------------------
========================================
   TIC-TAC-TOE - Feature-Rich Edition
========================================

1. Register
2. Login
3. View High Scores
4. Exit

Choose an option: 2

Enter username: alice
Enter password: ********

Login successful! Welcome, alice!
Press Enter to continue...
--------------------------------------------------------------------------------


SCREEN 4: Main Menu (Logged In)
--------------------------------------------------------------------------------
========================================
   TIC-TAC-TOE - Feature-Rich Edition
========================================

Logged in as: alice
Lives: 3

1. Play vs Computer (PvC)
2. Play vs Player (PvP)
3. View My Stats
4. View High Scores
5. Logout

Choose an option: _
--------------------------------------------------------------------------------


SCREEN 5: Game Board - Start of PvC Game
--------------------------------------------------------------------------------

     1   2   3
   +---+---+---+
 1 |   |   |   |
   +---+---+---+
 2 |   |   |   |
   +---+---+---+
 3 |   |   |   |
   +---+---+---+

alice (X) vs Computer (O)
alice Lives: 3 | Computer Lives: Unlimited

alice's turn (X)
Enter row (1-3): _
--------------------------------------------------------------------------------


SCREEN 6: Game Board - Mid Game
--------------------------------------------------------------------------------

     1   2   3
   +---+---+---+
 1 | X |   |   |
   +---+---+---+
 2 |   | X | O |
   +---+---+---+
 3 |   |   |   |
   +---+---+---+

alice (X) vs Computer (O)
alice Lives: 3 | Computer Lives: Unlimited

alice's turn (X)
Enter row (1-3): 3
Enter column (1-3): 3
--------------------------------------------------------------------------------


SCREEN 7: Game Board - Player Wins!
--------------------------------------------------------------------------------

     1   2   3
   +---+---+---+
 1 | X |   | O |
   +---+---+---+
 2 |   | X | O |
   +---+---+---+
 3 |   |   | X |
   +---+---+---+

alice wins!

Press Enter to continue...
--------------------------------------------------------------------------------


SCREEN 8: Player Statistics
--------------------------------------------------------------------------------
========================================
   TIC-TAC-TOE - Feature-Rich Edition
========================================

Logged in as: alice
Lives: 3

1. Play vs Computer (PvC)
2. Play vs Player (PvP)
3. View My Stats
4. View High Scores
5. Logout

Choose an option: 3

=== alice's Stats ===
Wins: 5
Losses: 2
Draws: 1
Lives Remaining: 1
Total Games: 8

Press Enter to continue...
--------------------------------------------------------------------------------


SCREEN 9: High Scores Leaderboard
--------------------------------------------------------------------------------
========================================
   TIC-TAC-TOE - Feature-Rich Edition
========================================

Logged in as: alice
Lives: 3

1. Play vs Computer (PvC)
2. Play vs Player (PvP)
3. View My Stats
4. View High Scores
5. Logout

Choose an option: 4

=== HIGH SCORES ===
1. alice - 65 points
2. bob - 45 points
3. charlie - 30 points
4. david - 25 points
5. eve - 20 points

Press Enter to continue...
--------------------------------------------------------------------------------


SCREEN 10: PvP Game Setup
--------------------------------------------------------------------------------
========================================
   TIC-TAC-TOE - Feature-Rich Edition
========================================

Logged in as: alice
Lives: 3

1. Play vs Computer (PvC)
2. Play vs Player (PvP)
3. View My Stats
4. View High Scores
5. Logout

Choose an option: 2

Enter opponent's username: bob
Enter opponent's password: ********

     1   2   3
   +---+---+---+
 1 |   |   |   |
   +---+---+---+
 2 |   |   |   |
   +---+---+---+
 3 |   |   |   |
   +---+---+---+

alice (X) vs bob (O)
alice Lives: 3 | bob Lives: 2

alice's turn (X)
Enter row (1-3): _
--------------------------------------------------------------------------------


SCREEN 11: Computer's Turn
--------------------------------------------------------------------------------

     1   2   3
   +---+---+---+
 1 |   |   |   |
   +---+---+---+
 2 |   | X |   |
   +---+---+---+
 3 |   |   |   |
   +---+---+---+

alice (X) vs Computer (O)
alice Lives: 3 | Computer Lives: Unlimited

Computer is thinking...
Computer played: Row 1, Column 1
Press Enter to continue...
--------------------------------------------------------------------------------


SCREEN 12: Draw Game
--------------------------------------------------------------------------------

     1   2   3
   +---+---+---+
 1 | X | O | X |
   +---+---+---+
 2 | O | X | O |
   +---+---+---+
 3 | O | X | O |
   +---+---+---+

It's a draw!

Press Enter to continue...
--------------------------------------------------------------------------------


SCREEN 13: Out of Lives Warning
--------------------------------------------------------------------------------
========================================
   TIC-TAC-TOE - Feature-Rich Edition
========================================

Logged in as: alice
Lives: 0

You have no lives left! Please register a new account.
Press Enter to continue...
--------------------------------------------------------------------------------

================================================================================
                    END OF VISUAL DEMONSTRATION
================================================================================

All features demonstrated:
  ✅ User registration and authentication
  ✅ PvC mode with smart AI
  ✅ PvP mode with two players
  ✅ Lives system tracking
  ✅ Statistics tracking (wins/losses/draws)
  ✅ High score leaderboard
  ✅ Persistent data storage
  ✅ Input validation
  ✅ Win/loss/draw detection
  ✅ Clear visual board display

EOF

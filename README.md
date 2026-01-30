# 🎮 Tic-Tac-Toe Game (C++)

A feature-rich C++ console game that transforms the classic Tic-Tac-Toe into a competitive, strategic, and visually engaging experience with professional UI design.

---

## 🎯 Overview

**Tic-Tac-Toe Game** is a Windows-based console application supporting **single-player (vs AI)** and **two-player modes**.  
Players compete in multiple rounds with a lives system, score tracking, and persistent high scores.

The project features **professional console UI engineering** with animated loading screens, colored boxes, password masking, **smart AI logic**, and **file-based data persistence**.

---

## ✨ Key Features

| Feature | Description |
|---------|-------------|
| 🔐 **User Authentication** | Registration & login system with hidden password input |
| 🎬 **Animated Loading** | Stylish loading bar animation on startup |
| 📺 **Fullscreen Mode** | Game launches in maximized fullscreen window |
| 🤖 **Smart AI Opponent** | Strategic computer AI with win/block logic |
| 🎭 **Dual Game Modes** | Player vs Computer & Player vs Player |
| ❤️ **Lives System** | 3 lives per player displayed with heart icons |
| 🏆 **Score Tracking** | +10 points for wins, +5 for draws |
| 💾 **Persistent High Scores** | High scores saved per user in login.txt |
| 🎨 **Colored Visual UI** | Styled boxes, color-coded X (Cyan) and O (Red) |
| 📊 **Progress Bar** | Real-time progress tracking displayed at top |
| 💡 **Smart Hint System** | Strategic hints for winning moves and blocks |
| 🔊 **Sound Effects** | Beeps for moves, placement, victories, and draws |
| 📋 **Game Instructions** | Welcome screen with gameplay instructions |
| ⌨️ **Arrow Key Navigation** | Smooth cursor movement with visual selection |

---

## 🛠️ Tech Stack

- **Language:** C++
- **Platform:** Windows API (Console Control)
- **Libraries:** 
  - `windows.h` - Console manipulation, fullscreen mode, cursor positioning, colors & sound (Beep)
  - `conio.h` - Real-time keyboard input with password masking
  - `fstream` - File handling for user data
- **Features:** 
  - File-based authentication with hidden password input
  - AI strategy pattern implementation
  - Console color manipulation with SetConsoleTextAttribute
  - Windows Beep API for sound effects
  - Animated loading bar with progress visualization
  - Styled box drawing for professional UI

---

## 🎮 Game Mechanics

### Visual Enhancements:
- **Colored Markers:** X appears in Cyan, O appears in Red
- **Cursor Highlight:** Selected cell highlighted in Yellow
- **Progress Bars:** Visual bars showing score progression for both players
- **Victory Effects:** Color-coded win messages with victory tunes

### Smart Hint System:
The game provides intelligent hints during gameplay:
1. **Win Detection:** Alerts when you can win
2. **Block Alert:** Warns about opponent's winning moves
3. **Strategic Advice:** Suggests center and corner positions
4. **Real-time Updates:** Hints update based on current board state

### Sound Effects:
- **Movement Sound:** Low beep (400Hz) when moving cursor
- **Placement Sound:** Medium beep (600Hz) when placing mark
- **Victory Tune:** Three ascending beeps for wins
- **Draw Sound:** Two neutral beeps for ties

### AI Strategy (Priority Order):
1. **Win** - Complete a winning line if possible
2. **Block** - Prevent opponent from winning
3. **Center** - Take the center position
4. **Corners** - Occupy corner positions
5. **Edges** - Fill remaining edge positions

### Scoring System:
- **Win:** +10 points
- **Draw:** +5 points each
- **Lives:** 3 per player (lose one when opponent wins)
- **Champion:** Player with lives remaining when opponent reaches 0

---

## 🚀 How to Run

### Option 1: Using the Executable
1. Navigate to the project folder
2. Run `setup.exe`
3. Register a new account or login
4. Start playing!

### Option 2: Compile from Source
1. Open `main.cpp` in any C++ IDE (Visual Studio, Code::Blocks, Dev-C++)
2. Build the project
3. Run the compiled executable

### Option 3: Command Line
```bash
g++ main.cpp -o TicTacToe.exe
./TicTacToe.exe
```

---

## 🎛️ Controls

| Key | Action |
|-----|--------|
| ↑ ↓ ← → | Move cursor on grid / Navigate menus |
| Enter | Place mark / Select option |
| ESC | Exit game from menu |
| M | Return to main menu (after game over) |

---

## 📁 Project Structure

```
Tick-Tac-Toe Game/
├── main.cpp          # Main source code (1500+ lines)
├── login.txt         # User credentials & high scores
├── main.exe          # Compiled executable
└── README.md         # Project documentation
```

---

## 📸 Screenshots

### Loading Screen
```
+------------------------------------------------+
|                TIC-TAC-TOE GAME                |
|   Developed by: Adil ur Rehman                 |
|   Roll No: 24-CS-760                           |
+------------------------------------------------+

                  Game Loading
[========================================]
```

### Login Screen
```
+------------------------------------------------+
|                TIC-TAC-TOE GAME                |
+------------------------------------------------+
Developed by: Adil ur Rehman | Roll: 24-CS-760

+---------------------------------------------+
|          Welcome To Login Page              |
|       Enter Username and Password           |
+---------------------------------------------+

=== LOGIN ===
Enter Username: adil
Enter Password: ****
```

### Game Menu
```
+------------------------------------------------+
|                TIC-TAC-TOE GAME                |
+------------------------------------------------+          Score: 30
Developed by: Adil ur Rehman | Roll: 24-CS-760   High Score: 50
                                                  Lives X: ♥ ♥ ♥
           === GAME MENU ===                      Lives O: ♥ ♥
+---------------------------------+
| > Player VS. Computer       <   |
|   Player VS. Player             |
|   View High Score               |
|   Exit Game                     |
+---------------------------------+

[UP/DOWN: Navigate | ENTER: Select | ESC: Exit]
```

### Gameplay
```
Progress: [==========                ] 3/9        Score: 30
+------------------------------------------------+  High Score: 50
|                TIC-TAC-TOE GAME                |  Lives X: ♥ ♥ ♥
+------------------------------------------------+  Lives O: ♥ ♥

          Games won - X: 2  |  O: 1
          
            >>> X's Turn! <<<

           [.]| X |   
           -----------
              | O |   
           -----------
            X |   | O 

[UP/DOWN/LEFT/RIGHT: Move | ENTER: Place Mark]

Hint: BLOCK opponent at position 3!
```

---

## ⚠️ Requirements

- **OS:** Windows only (uses WinAPI)
- **Compiler:** Any C++ compiler supporting Windows headers
- **Console:** Windows Command Prompt or PowerShell

---

## 📚 Learning Outcomes

- ✅ Console UI/UX design with styled boxes and centering
- ✅ Animated loading bar implementation
- ✅ Password masking for secure input
- ✅ Fullscreen console mode configuration
- ✅ File-based authentication system
- ✅ Game state management (lives, scores, rounds)
- ✅ AI decision-making algorithms
- ✅ Arrow key input handling with visual feedback
- ✅ Console color manipulation and visual enhancements
- ✅ Sound effect integration with Windows Beep API
- ✅ Real-time hint system implementation
- ✅ Progress tracking with visual progress bars
- ✅ Data persistence with file I/O
- ✅ Modular function design

---

## 👨‍💻 Author

**Adil ur Rehman**  
Computer Science Undergraduate  
Roll No: 24-CS-760

---

## 📄 License

This project is created for educational purposes as part of the **Programming Fundamentals** course final semester project.

---

*Made with ❤️ and C++*

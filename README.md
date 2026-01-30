# 🎮 Tic-Tac-Toe Game (C++)

A feature-rich C++ console game that transforms the classic Tic-Tac-Toe into a competitive, strategic, and visually engaging experience.

---

## 🎯 Overview

**Tic-Tac-Toe Game** is a Windows-based console application supporting **single-player (vs AI)** and **two-player modes**.  
Players compete in multiple rounds with a lives system, score tracking, and persistent high scores.

The project focuses on **console UI engineering**, **smart AI logic**, and **file-based data persistence**.

---

## ✨ Key Features

| Feature | Description |
|---------|-------------|
| 🔐 **User Authentication** | Registration & login system (file-based) |
| 🤖 **Smart AI Opponent** | Strategic computer AI with win/block logic |
| 🎭 **Dual Game Modes** | Player vs Computer & Player vs Player |
| ❤️ **Lives System** | 3 lives per player, last one standing wins |
| 🏆 **Score Tracking** | +10 points for wins, +5 for draws |
| 💾 **Persistent High Scores** | High scores saved per user account |
| 🎨 **Centered Console UI** | Dynamic centering adapts to console size |
| ⌨️ **Arrow Key Navigation** | Smooth cursor movement on the grid |
| 🔄 **Symbol Selection** | Choose X or O in single-player mode |

---

## 🛠️ Tech Stack

- **Language:** C++
- **Platform:** Windows API (Console Control)
- **Libraries:** 
  - `windows.h` - Console manipulation & cursor positioning
  - `conio.h` - Real-time keyboard input
  - `fstream` - File handling for user data
- **Features:** 
  - File-based authentication & data persistence
  - AI strategy pattern implementation

---

## 🎮 Game Mechanics

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
| M | Return to main menu (after game over) |

---

## 📁 Project Structure

```
Huzaifa Tick-Tac-Toe Game/
├── main.cpp          # Main source code (850+ lines)
├── login.txt         # User credentials & high scores
├── setup.exe         # Compiled executable
└── README.md         # Project documentation
```

---

## 📸 Screenshots

```
**********************************************
*              TICK-TAC-TOE GAME             *
*            Developed by: Adil ur Rehman    *
*              Roll No: 24-CS-760            *
**********************************************

    X's Turn!
    
   [.]| X |   
   -----------
      | O |   
   -----------
    X |   | O 

   CONTROLS:
   Arrow Keys = Move | Enter = Place Mark
```

---

## ⚠️ Requirements

- **OS:** Windows only (uses WinAPI)
- **Compiler:** Any C++ compiler supporting Windows headers
- **Console:** Windows Command Prompt or PowerShell

---

## 📚 Learning Outcomes

- ✅ Console UI/UX design with dynamic centering
- ✅ File-based authentication system
- ✅ Game state management (lives, scores, rounds)
- ✅ AI decision-making algorithms
- ✅ Arrow key input handling
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

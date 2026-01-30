#include<iostream>
#include<conio.h>
#include<cstdlib>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// Arrow key codes
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

// All function declarations
void pvp(void);
void pvc(void);
void printheadermenu();
void printloginmenu();
void loginn();
void registerr();
void gotoxy(int x, int y);
void displayGrid(int[], int);
void displayControls(void);
void displayTurn(int);
int isGridFull(int[]);
int getGameWinner(int[]);
void displayResultScreen(int[], int&, int&);
void computerTurn(int[], int[], int);
void endScreen(int, int);
void getConsoleSize(int &width, int &height);
void centerText(string text);
void saveHighScore(string username, int score);
int getHighScore(string username);
int selectGameMode();

// Win counters
int recordx=0;
int recordo=0;

// Lives and scores
int livesX = 3;
int livesO = 3;
int scoreX = 0;
int scoreO = 0;

// Player symbol choice in PvC mode (0 = not chosen yet, 1 = X, 2 = O)
int playerSymbolChoice = 0;

// Current logged in username
string currentUser = "";

// Get current console window size
void getConsoleSize(int &width, int &height){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// Print text in center of screen
void centerText(string text){
    int w, h;
    getConsoleSize(w, h);
    int pad = (w - text.length()) / 2;
    if(pad < 0) pad = 0;
    for(int i = 0; i < pad; i++) cout << " ";
    cout << text;
}

// Get center X position for text
int getCenterX(int textLen){
    int w, h;
    getConsoleSize(w, h);
    return (w - textLen) / 2;
}

// Get center Y position
int getCenterY(){
    int w, h;
    getConsoleSize(w, h);
    return h / 2;
}

int main()
{
    printheadermenu();
    system("CLS");
    
    int w, h;
    getConsoleSize(w, h);
    gotoxy(getCenterX(18), h/2);
    cout << "Login Starting...";
    Sleep(1000);
    
    system("CLS");
    printloginmenu();
    loginn();
    system("CLS");
    
    // Reset lives and scores for new session
    livesX = 3;
    livesO = 3;
    scoreX = 0;
    scoreO = 0;
    playerSymbolChoice = 0;  // Reset player symbol choice
    
    int option = selectGameMode();
    
    if (option == 0)
        pvc();
    else
        pvp();
    return 0;
}

void gotoxy(int x, int y) 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printheadermenu() 
{
    system("CLS");
    int w, h;
    getConsoleSize(w, h);
    int startY = h / 2 - 4;
    int startX = getCenterX(46);
    
    gotoxy(startX, startY);     cout << "**********************************************";
    gotoxy(startX, startY + 1); cout << "*              TICK-TAC-TOE GAME             *";
    gotoxy(startX, startY + 2); cout << "*            Developed by: Adil ur Rehman    *";
    gotoxy(startX, startY + 3); cout << "*              Roll No: 24-CS-760            *";
    gotoxy(startX, startY + 4); cout << "**********************************************";
    gotoxy(getCenterX(30), startY + 6);
    cout << "Game Loading in 3 Seconds......";
    Sleep(2000);
}

void printloginmenu()
{
    system("CLS");
    int w, h;
    getConsoleSize(w, h);
    int startY = h / 2 - 4;
    int startX = getCenterX(46);
    
    gotoxy(startX, startY);     cout << "**********************************************";
    gotoxy(startX, startY + 1); cout << "*             TICK-TAC-TOE GAME              *";
    gotoxy(startX, startY + 2); cout << "*           Welcome To Login Page            *";
    gotoxy(startX, startY + 3); cout << "**********************************************";
    gotoxy(getCenterX(30), startY + 5); cout << "Enter Username and Password";
    Sleep(500);
}

void loginn()
{
    int count = 0;
    string username;
    string passward;
    string id;
    string pass;
    int score;
    int w, h;
    getConsoleSize(w, h);
    int startY = h / 2 + 2;
    int startX = getCenterX(30);
    
    gotoxy(startX, startY); cout << "Login";
    gotoxy(startX, startY + 1); cout << "Enter username: ";
    cin >> username;
    gotoxy(startX, startY + 2); cout << "Enter password: ";
    cin >> passward;
    
    fstream login;
    login.open("login.txt", ios::in);
    while(login >> id >> pass >> score)
    {
        if(id == username && pass == passward)
            count++;
    }
    login.close();
    
    if(count > 0)
    {
        currentUser = username;
        gotoxy(startX, startY + 4); cout << "Welcome to Your Account " << username << endl;
        gotoxy(startX, startY + 5); cout << "Your High Score: " << getHighScore(username) << endl;
        Sleep(1500);
    }
    else
    {
        gotoxy(startX, startY + 4); cout << "Login Error: Invalid username or password" << endl;
        gotoxy(startX, startY + 5); cout << "Please Register Yourself";
        registerr();
        Sleep(700);
    }
}

void registerr()
{
    string username, passward, id, pass;
    int score;
    bool usernameExists = false;
    int w, h;
    getConsoleSize(w, h);
    int startY = h / 2 + 8;
    int startX = getCenterX(30);

    gotoxy(startX, startY); cout << "Register";

    do {
        usernameExists = false;
        gotoxy(startX, startY + 2); cout << "Enter username: ";
        cin >> username;

        fstream login;
        login.open("login.txt", ios::in);
        while (login >> id >> pass >> score) {
            if (id == username) 
            {
                usernameExists = true;
                gotoxy(startX, startY + 3); cout << "Username already taken!";
                Sleep(1000);
                gotoxy(startX, startY + 3); cout << "                       ";
                break;
            }
        }
        login.close();
    } 
    while (usernameExists);

    gotoxy(startX, startY + 3); cout << "Enter password: ";
    cin >> passward;

    fstream login;
    login.open("login.txt", ios::app);
    login << username << ' ' << passward << ' ' << 0 << endl;
    login.close();

    gotoxy(startX, startY + 5); cout << "Registration Successful!";
    Sleep(500);
    gotoxy(startX, startY + 6); cout << "Redirecting to Login...";
    Sleep(500);
    system("CLS");
    printloginmenu();
    loginn();
}

// Player vs Computer mode
void pvc(){
    int grid[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int possibleMoves[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int turn = 0;
    int cursor = 0;
    int key;
    int w, h;
    int playerSymbol;
    
    // Only ask for symbol choice if not already chosen this session
    if(playerSymbolChoice == 0){
        int selected = 0;  // 0 = X, 1 = O
        int selKey;
        
        while(true){
            system("cls");
            getConsoleSize(w, h);
            int startY = h/2 - 3;
            
            gotoxy(getCenterX(25), startY);
            cout << "Choose Your Symbol:";
            
            // Option X
            gotoxy(getCenterX(10), startY + 3);
            if(selected == 0)
                cout << ">>  X  <<";
            else
                cout << "    X    ";
            
            // Option O
            gotoxy(getCenterX(10), startY + 5);
            if(selected == 1)
                cout << ">>  O  <<";
            else
                cout << "    O    ";
            
            selKey = getch();
            if(selKey == 0 || selKey == 224){
                selKey = getch();
            }
            
            if(selKey == KEY_UP || selKey == KEY_DOWN){
                selected = (selected == 0) ? 1 : 0;
            }
            else if(selKey == KEY_ENTER){
                playerSymbolChoice = (selected == 0) ? 1 : 2;
                break;
            }
        }
    }
    
    // Set turn and playerSymbol based on saved choice
    turn = playerSymbolChoice;
    playerSymbol = playerSymbolChoice;
    
    // main game loop
    do{
        system("cls");
        getConsoleSize(w, h);
        int startY = h/2 - 7;
        
        gotoxy(getCenterX(40), startY);
        cout << "Games won X=" << recordx << "  O=" << recordo;
        gotoxy(getCenterX(50), startY + 1);
        cout << "Lives: X=" << livesX << "  O=" << livesO << "  |  Score: X=" << scoreX << "  O=" << scoreO;
        displayTurn(turn);
        displayGrid(grid, cursor);
        displayControls();
        
        // get arrow key or enter
        key = getch();
        if(key == 0 || key == 224){
            key = getch();
        }
        
        // move cursor based on arrow keys
        if(key == KEY_UP && cursor >= 3)
            cursor -= 3;
        else if(key == KEY_DOWN && cursor <= 5)
            cursor += 3;
        else if(key == KEY_LEFT && cursor % 3 != 0)
            cursor -= 1;
        else if(key == KEY_RIGHT && cursor % 3 != 2)
            cursor += 1;
        else if(key == KEY_ENTER){
            // place mark if cell is empty
            if(grid[cursor] == 0){
                if(turn % 2 == 1)
                    grid[cursor] = 1;
                else
                    grid[cursor] = 2;
                
                // computer plays after player
                if(getGameWinner(grid) == 0 && !isGridFull(grid))
                    computerTurn(grid, possibleMoves, turn);
            }
        }
    } while(!isGridFull(grid) && getGameWinner(grid) == 0);
    
    displayResultScreen(grid, livesX, livesO);
    endScreen(playerSymbol, 1);
}

// Player vs Player mode
void pvp(){
    int grid[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int turn = rand() % 2;
    int cursor = 0;
    int key;
    int w, h;
    
    // main game loop
    do{
        system("cls");
        getConsoleSize(w, h);
        int startY = h/2 - 7;
        
        gotoxy(getCenterX(40), startY);
        cout << "Games won X=" << recordx << "  O=" << recordo;
        gotoxy(getCenterX(50), startY + 1);
        cout << "Lives: X=" << livesX << "  O=" << livesO << "  |  Score: X=" << scoreX << "  O=" << scoreO;
        displayTurn(turn);
        displayGrid(grid, cursor);
        displayControls();
        
        // get arrow key or enter
        key = getch();
        if(key == 0 || key == 224){
            key = getch();
        }
        
        // move cursor based on arrow keys
        if(key == KEY_UP && cursor >= 3)
            cursor -= 3;
        else if(key == KEY_DOWN && cursor <= 5)
            cursor += 3;
        else if(key == KEY_LEFT && cursor % 3 != 0)
            cursor -= 1;
        else if(key == KEY_RIGHT && cursor % 3 != 2)
            cursor += 1;
        else if(key == KEY_ENTER){
            // place mark if cell is empty
            if(grid[cursor] == 0){
                if(turn % 2 == 1)
                    grid[cursor] = 1;
                else
                    grid[cursor] = 2;
                turn++;
            }
        }
    } while(!isGridFull(grid) && getGameWinner(grid) == 0);
    
    displayResultScreen(grid, livesX, livesO);
    endScreen(0, 0);
}

// Draw the 3x3 grid with cursor highlight (centered)
void displayGrid(int grid[], int cursor){
    int w, h;
    getConsoleSize(w, h);
    int startX = getCenterX(11);
    int startY = h/2 - 2;
    
    for(int i=0; i<9; i+=3){
        gotoxy(startX, startY + (i/3)*2);
        for(int j=0; j<3; j++){
            int cell = i + j;
            
            // show cursor with brackets [ ]
            if(cell == cursor){
                if(grid[cell] == 0)
                    cout<<"[.]";
                else if(grid[cell] == 1)
                    cout<<"[X]";
                else
                    cout<<"[O]";
            }
            else{
                if(grid[cell] == 0)
                    cout<<"   ";
                else if(grid[cell] == 1)
                    cout<<" X ";
                else
                    cout<<" O ";
            }
            
            if(j < 2)
                cout<<"|";
        }
        if(i < 6){
            gotoxy(startX, startY + (i/3)*2 + 1);
            cout<<"-----------";
        }
    }
    cout << endl;
}

// Show controls help (centered)
void displayControls(){
    int w, h;
    getConsoleSize(w, h);
    gotoxy(getCenterX(10), h/2 + 5);
    cout << "CONTROLS:";
    gotoxy(getCenterX(38), h/2 + 6);
    cout << "Arrow Keys = Move | Enter = Place Mark";
}

// Show whose turn it is (centered)
void displayTurn(int turn){
    int w, h;
    getConsoleSize(w, h);
    gotoxy(getCenterX(10), h/2 - 4);
    if(turn%2==1)
        cout<<"X's Turn!";
    else
        cout<<"O's Turn!";
}

// Check if all cells are filled
int isGridFull(int grid[]){
    for(int i=0;i<9;i++){
        if(grid[i]==0)
            return 0;
    }
    return 1;
}

// Check who won the game
int getGameWinner(int grid[]){
    int i;
    // Check rows
    for(i=0;i<9;i+=3){
        if(grid[i]==grid[i+1]&&grid[i]==grid[i+2]){
            if (grid[i+1]==1)
                return 1;
            else if (grid[i+2]==2)
                return 2;
        }
    }
    // Check columns
    for(i=0;i<3;i++){
        if(grid[i]==grid[i+3]&&grid[i]==grid[i+6]){
            if (grid[i]==1)
                return 1;
            else if(grid[i]==2)
                return 2;
        }
    }
    // Check diagonals
    if ((grid[0]==grid[4]&&grid[0]==grid[8])||(grid[2]==grid[4]&&grid[2]==grid[6])){
        if (grid[4]==1)
            return 1;
        else if (grid[4]==2)
            return 2;
    }
    return 0;
}

// Show final result (centered)
void displayResultScreen(int grid[], int &livesX, int &livesO){
    system("cls");
    displayGrid(grid, -1);
    int w, h;
    getConsoleSize(w, h);
    
    gotoxy(getCenterX(15), h/2 + 4);
    if (getGameWinner(grid)==1){
        cout << "X Wins! +10 points";
        recordx++;
        scoreX += 10;
        livesO--;
    }
    else if (getGameWinner(grid)==2){
        cout << "O Wins! +10 points";
        recordo++;
        scoreO += 10;
        livesX--;
    }
    else{
        cout << "Draw! +5 points each";
        scoreX += 5;
        scoreO += 5;
    }
    
    gotoxy(getCenterX(30), h/2 + 5);
    cout << "Lives remaining: X=" << livesX << "  O=" << livesO;
    gotoxy(getCenterX(30), h/2 + 6);
    cout << "Scores: X=" << scoreX << "  O=" << scoreO;
}

// Check if a move can win for a given player (returns cell index or -1)
int findWinningMove(int grid[], int player){
    // All winning combinations
    int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},  // rows
        {0,3,6}, {1,4,7}, {2,5,8},  // columns
        {0,4,8}, {2,4,6}            // diagonals
    };
    
    for(int i = 0; i < 8; i++){
        int a = wins[i][0], b = wins[i][1], c = wins[i][2];
        
        // Check if two cells have player's mark and one is empty
        if(grid[a] == player && grid[b] == player && grid[c] == 0) return c;
        if(grid[a] == player && grid[c] == player && grid[b] == 0) return b;
        if(grid[b] == player && grid[c] == player && grid[a] == 0) return a;
    }
    return -1;
}

// Smart Computer AI
void computerTurn(int grid[], int possibleMoves[], int turn){
    int computerMark = turn % 2 + 1;  // Computer's symbol
    int playerMark = (computerMark == 1) ? 2 : 1;  // Player's symbol
    int move = -1;
    
    // 1. Try to win
    move = findWinningMove(grid, computerMark);
    if(move != -1){
        grid[move] = computerMark;
        return;
    }
    
    // 2. Block player from winning
    move = findWinningMove(grid, playerMark);
    if(move != -1){
        grid[move] = computerMark;
        return;
    }
    
    // 3. Take center if available
    if(grid[4] == 0){
        grid[4] = computerMark;
        return;
    }
    
    // 4. Take a corner if available
    int corners[4] = {0, 2, 6, 8};
    for(int i = 0; i < 4; i++){
        if(grid[corners[i]] == 0){
            grid[corners[i]] = computerMark;
            return;
        }
    }
    
    // 5. Take any edge
    int edges[4] = {1, 3, 5, 7};
    for(int i = 0; i < 4; i++){
        if(grid[edges[i]] == 0){
            grid[edges[i]] = computerMark;
            return;
        }
    }
}

// Ask player what to do after game ends (centered)
void endScreen(int playerSymbol, int isPvC){
    int input;
    int w, h;
    getConsoleSize(w, h);
    
    gotoxy(getCenterX(25), h/2 + 8);
    cout << "Press anything to continue.";
    getch();
    system("cls");
    
    getConsoleSize(w, h);
    
    // Check if game is over (someone ran out of lives)
    if(livesX <= 0 || livesO <= 0){
        gotoxy(getCenterX(30), h/2 - 2);
        cout << "========= GAME OVER =========";
        gotoxy(getCenterX(30), h/2);
        if(livesX <= 0){
            cout << "O is the CHAMPION!";
            gotoxy(getCenterX(30), h/2 + 1);
            cout << "Final Score - X: " << scoreX << "  O: " << scoreO;
        } else {
            cout << "X is the CHAMPION!";
            gotoxy(getCenterX(30), h/2 + 1);
            cout << "Final Score - X: " << scoreX << "  O: " << scoreO;
        }
        
        // Save high score for logged in player
        int playerScore = (isPvC && playerSymbol == 1) ? scoreX : ((isPvC && playerSymbol == 2) ? scoreO : (scoreX > scoreO ? scoreX : scoreO));
        if(!currentUser.empty()){
            int oldHighScore = getHighScore(currentUser);
            if(playerScore > oldHighScore){
                saveHighScore(currentUser, playerScore);
                gotoxy(getCenterX(30), h/2 + 3);
                cout << "NEW HIGH SCORE: " << playerScore << "!";
            } else {
                gotoxy(getCenterX(30), h/2 + 3);
                cout << "Your High Score: " << oldHighScore;
            }
        }
        
        gotoxy(getCenterX(32), h/2 + 5);
        cout << "Press [M] to return to Main Menu.";
        input = getch();
        if(input=='m'||input=='M'){
            livesX = 3;
            livesO = 3;
            scoreX = 0;
            scoreO = 0;
            playerSymbolChoice = 0;
            main();
        }
    } else {
        // Continue playing - still have lives
        int selected = 0;  // 0 = Continue, 1 = Main Menu
        int selKey;
        
        while(true){
            system("cls");
            getConsoleSize(w, h);
            
            gotoxy(getCenterX(25), h/2 - 4);
            cout << "===== ROUND COMPLETE =====";
            
            gotoxy(getCenterX(30), h/2 - 2);
            cout << "Lives: X=" << livesX << "  O=" << livesO;
            gotoxy(getCenterX(30), h/2 - 1);
            cout << "Score: X=" << scoreX << "  O=" << scoreO;
            
            gotoxy(getCenterX(20), h/2 + 2);
            cout << "What would you like to do?";
            
            // Option Continue
            gotoxy(getCenterX(15), h/2 + 4);
            if(selected == 0)
                cout << ">> Continue <<";
            else
                cout << "   Continue   ";
            
            // Option Main Menu
            gotoxy(getCenterX(15), h/2 + 6);
            if(selected == 1)
                cout << ">> Main Menu <<";
            else
                cout << "   Main Menu   ";
            
            selKey = getch();
            if(selKey == 0 || selKey == 224){
                selKey = getch();
            }
            
            if(selKey == KEY_UP || selKey == KEY_DOWN){
                selected = (selected == 0) ? 1 : 0;
            }
            else if(selKey == KEY_ENTER){
                break;
            }
        }
        
        if(selected == 1){
            // Save current score as high score if better
            int playerScore = (isPvC && playerSymbol == 1) ? scoreX : ((isPvC && playerSymbol == 2) ? scoreO : (scoreX > scoreO ? scoreX : scoreO));
            if(!currentUser.empty()){
                int oldHighScore = getHighScore(currentUser);
                if(playerScore > oldHighScore){
                    saveHighScore(currentUser, playerScore);
                }
            }
            livesX = 3;
            livesO = 3;
            scoreX = 0;
            scoreO = 0;
            playerSymbolChoice = 0;
            main();
        } else {
            // Continue with another round
            if(isPvC)
                pvc();
            else
                pvp();
        }
    }
}

// Get high score for a user from login.txt
int getHighScore(string username){
    fstream file;
    string id, pass;
    int score;
    file.open("login.txt", ios::in);
    while(file >> id >> pass >> score){
        if(id == username){
            file.close();
            return score;
        }
    }
    // Try reading without score (old format)
    file.close();
    file.open("login.txt", ios::in);
    while(file >> id >> pass){
        if(id == username){
            file.close();
            return 0;
        }
    }
    file.close();
    return 0;
}

// Save high score for a user in login.txt
void saveHighScore(string username, int score){
    fstream file;
    string id, pass;
    int oldScore;
    string fileContent = "";
    bool found = false;
    
    // Read all data
    file.open("login.txt", ios::in);
    string line;
    while(getline(file, line)){
        // Parse the line
        size_t pos1 = line.find(' ');
        if(pos1 != string::npos){
            string uname = line.substr(0, pos1);
            string rest = line.substr(pos1 + 1);
            size_t pos2 = rest.find(' ');
            string pwd;
            int existingScore = 0;
            
            if(pos2 != string::npos){
                pwd = rest.substr(0, pos2);
                existingScore = stoi(rest.substr(pos2 + 1));
            } else {
                pwd = rest;
            }
            
            if(uname == username){
                fileContent += uname + " " + pwd + " " + to_string(score) + "\n";
                found = true;
            } else {
                fileContent += uname + " " + pwd + " " + to_string(existingScore) + "\n";
            }
        }
    }
    file.close();
    
    // Write back
    file.open("login.txt", ios::out | ios::trunc);
    file << fileContent;
    file.close();
}

// Select game mode with navigation keys
int selectGameMode(){
    int selected = 0;
    int key;
    int w, h;
    
    while(true){
        system("cls");
        getConsoleSize(w, h);
        int startY = h/2 - 4;
        
        gotoxy(getCenterX(42), startY);
        cout << "Welcome to Tic-Tac-Toe! (by Adil ur Rehman)";
        gotoxy(getCenterX(42), startY + 1);
        cout << "------------------------------------------";
        gotoxy(getCenterX(28), startY + 3);
        cout << "Select Game Mode (Arrow Keys):";
        
        // Option 1
        gotoxy(getCenterX(25), startY + 5);
        if(selected == 0)
            cout << ">> Player VS. Computer <<";
        else
            cout << "   Player VS. Computer   ";
        
        // Option 2
        gotoxy(getCenterX(22), startY + 7);
        if(selected == 1)
            cout << ">> Player VS. Player <<";
        else
            cout << "   Player VS. Player   ";
        
        key = getch();
        if(key == 0 || key == 224){
            key = getch();
        }
        
        if(key == KEY_UP || key == KEY_DOWN){
            selected = (selected == 0) ? 1 : 0;
        }
        else if(key == KEY_ENTER){
            return selected;
        }
    }
}

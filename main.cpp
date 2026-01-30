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

// Sound types
#define SOUND_MOVE 1
#define SOUND_PLACE 2
#define SOUND_WIN 3
#define SOUND_LOSE 4
#define SOUND_DRAW 5

// Console colors
#define COLOR_GREEN 10
#define COLOR_RED 12
#define COLOR_YELLOW 14
#define COLOR_CYAN 11
#define COLOR_WHITE 15
#define COLOR_BLUE 9
#define COLOR_DARK_CYAN 3
#define KEY_ESC 27

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
void displayProgressBar(int scoreX, int scoreO, int livesX, int livesO);
void displayHint(int grid[], int turn);
void playSound(int type);
void setColor(int color);
void resetColor();
void setFullScreen();
void drawLoadingBar();
void drawBox(int x, int y, int width, int height, int color);
void displayGameInstructions();
void displayHeader();
void displayScorePanel();
void displayEvidenceBar();
string getHiddenPassword();

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
    setFullScreen();
    printheadermenu();
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
    int boxWidth = 50;
    int boxHeight = 6;
    int startY = h / 2 - 6;
    int startX = getCenterX(boxWidth);
    
    // Draw decorative border box
    drawBox(startX, startY, boxWidth, boxHeight, COLOR_CYAN);
    
    // Title inside box
    gotoxy(startX + (boxWidth - 16) / 2, startY + 2);
    setColor(COLOR_GREEN);
    cout << "TIC-TAC-TOE GAME";
    
    // Developer info
    gotoxy(startX + 5, startY + 3);
    setColor(COLOR_YELLOW);
    cout << "Developed by: ";
    setColor(COLOR_CYAN);
    cout << "Adil ur Rehman";
    
    gotoxy(startX + 5, startY + 4);
    setColor(COLOR_YELLOW);
    cout << "Roll No: ";
    setColor(COLOR_CYAN);
    cout << "24-CS-760";
    resetColor();
    
    // Loading text
    gotoxy(getCenterX(12), startY + boxHeight + 3);
    setColor(COLOR_GREEN);
    cout << "Game Loading";
    resetColor();
    
    // Draw loading bar
    drawLoadingBar();
}

void printloginmenu()
{
    system("CLS");
    int w, h;
    getConsoleSize(w, h);
    
    // Draw header
    displayHeader();
    
    // Login box
    int boxWidth = 45;
    int boxHeight = 4;
    int startY = h / 2 - 2;
    int startX = getCenterX(boxWidth);
    
    drawBox(startX, startY, boxWidth, boxHeight, COLOR_CYAN);
    
    gotoxy(startX + (boxWidth - 21) / 2, startY + 1);
    setColor(COLOR_WHITE);
    cout << "Welcome To Login Page";
    
    gotoxy(startX + (boxWidth - 29) / 2, startY + 2);
    setColor(COLOR_GREEN);
    cout << "Enter Username and Password";
    resetColor();
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
    int startY = h / 2 + 4;
    int startX = getCenterX(30) - 5;
    
    setColor(COLOR_YELLOW);
    gotoxy(startX, startY);
    cout << "=== LOGIN ===";
    resetColor();
    
    gotoxy(startX, startY + 2);
    setColor(COLOR_GREEN);
    cout << "Enter Username: ";
    setColor(COLOR_CYAN);
    cin >> username;
    
    gotoxy(startX, startY + 3);
    setColor(COLOR_GREEN);
    cout << "Enter Password: ";
    setColor(COLOR_CYAN);
    passward = getHiddenPassword();
    resetColor();
    
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
        gotoxy(startX, startY + 5);
        setColor(COLOR_GREEN);
        cout << "Login Successful! Welcome, " << username << "!";
        gotoxy(startX, startY + 6);
        setColor(COLOR_YELLOW);
        cout << "Your High Score: ";
        setColor(COLOR_CYAN);
        cout << getHighScore(username);
        resetColor();
        playSound(SOUND_WIN);
        Sleep(2000);
    }
    else
    {
        gotoxy(startX, startY + 5);
        setColor(COLOR_RED);
        cout << "Login Error: Invalid username or password";
        gotoxy(startX, startY + 6);
        setColor(COLOR_YELLOW);
        cout << "Redirecting to Registration...";
        resetColor();
        playSound(SOUND_LOSE);
        Sleep(1500);
        registerr();
    }
}

void registerr()
{
    system("CLS");
    displayHeader();
    
    string username, passward, id, pass;
    int score;
    bool usernameExists = false;
    int w, h;
    getConsoleSize(w, h);
    int startY = h / 2;
    int startX = getCenterX(30) - 5;

    setColor(COLOR_YELLOW);
    gotoxy(startX, startY);
    cout << "=== REGISTER ===";
    resetColor();

    do {
        usernameExists = false;
        gotoxy(startX, startY + 2);
        setColor(COLOR_GREEN);
        cout << "Enter Username: ";
        setColor(COLOR_CYAN);
        cin >> username;

        fstream login;
        login.open("login.txt", ios::in);
        while (login >> id >> pass >> score) {
            if (id == username) 
            {
                usernameExists = true;
                gotoxy(startX, startY + 3);
                setColor(COLOR_RED);
                cout << "Username already taken!         ";
                resetColor();
                playSound(SOUND_LOSE);
                Sleep(1000);
                gotoxy(startX, startY + 2);
                cout << "                                          ";
                gotoxy(startX, startY + 3);
                cout << "                                          ";
                break;
            }
        }
        login.close();
    } 
    while (usernameExists);

    gotoxy(startX, startY + 3);
    setColor(COLOR_GREEN);
    cout << "Enter Password: ";
    setColor(COLOR_CYAN);
    passward = getHiddenPassword();
    resetColor();

    fstream login;
    login.open("login.txt", ios::app);
    login << username << ' ' << passward << ' ' << 0 << endl;
    login.close();

    gotoxy(startX, startY + 5);
    setColor(COLOR_GREEN);
    cout << "Registration Successful!";
    playSound(SOUND_WIN);
    Sleep(1000);
    gotoxy(startX, startY + 6);
    setColor(COLOR_YELLOW);
    cout << "Redirecting to Login...";
    resetColor();
    Sleep(1000);
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
            
            displayHeader();
            
            int startY = h/2 - 3;
            
            gotoxy(getCenterX(22), startY);
            setColor(COLOR_YELLOW);
            cout << "=== Choose Your Symbol ===";
            resetColor();
            
            // Draw options box
            int boxWidth = 25;
            int boxX = getCenterX(boxWidth);
            drawBox(boxX, startY + 2, boxWidth, 5, COLOR_CYAN);
            
            // Option X
            gotoxy(boxX + 5, startY + 3);
            if(selected == 0){
                setColor(COLOR_GREEN);
                cout << "> ";
                setColor(COLOR_CYAN);
                cout << "Play as X";
                setColor(COLOR_GREEN);
                cout << " <";
            }
            else{
                setColor(COLOR_WHITE);
                cout << "  Play as X  ";
            }
            
            // Option O
            gotoxy(boxX + 5, startY + 5);
            if(selected == 1){
                setColor(COLOR_GREEN);
                cout << "> ";
                setColor(COLOR_RED);
                cout << "Play as O";
                setColor(COLOR_GREEN);
                cout << " <";
            }
            else{
                setColor(COLOR_WHITE);
                cout << "  Play as O  ";
            }
            resetColor();
            
            selKey = getch();
            if(selKey == 0 || selKey == 224){
                selKey = getch();
            }
            
            if(selKey == KEY_UP || selKey == KEY_DOWN){
                selected = (selected == 0) ? 1 : 0;
                playSound(SOUND_MOVE);
            }
            else if(selKey == KEY_ENTER){
                playSound(SOUND_PLACE);
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
        
        // Display header and score panel
        displayHeader();
        displayScorePanel();
        displayEvidenceBar();
        
        int startY = h/2 - 6;
        
        gotoxy(getCenterX(40), startY);
        setColor(COLOR_YELLOW);
        cout << "Games won - ";
        setColor(COLOR_CYAN);
        cout << "X: " << recordx;
        setColor(COLOR_WHITE);
        cout << "  |  ";
        setColor(COLOR_RED);
        cout << "O: " << recordo;
        resetColor();
        
        displayTurn(turn);
        displayGrid(grid, cursor);
        displayControls();
        
        // Display hint for current player
        displayHint(grid, turn);
        
        // get arrow key or enter
        key = getch();
        if(key == 0 || key == 224){
            key = getch();
        }
        
        // move cursor based on arrow keys (PvC)
        if(key == KEY_UP && cursor >= 3){
            cursor -= 3;
            playSound(SOUND_MOVE);
        }
        else if(key == KEY_DOWN && cursor <= 5){
            cursor += 3;
            playSound(SOUND_MOVE);
        }
        else if(key == KEY_LEFT && cursor % 3 != 0){
            cursor -= 1;
            playSound(SOUND_MOVE);
        }
        else if(key == KEY_RIGHT && cursor % 3 != 2){
            cursor += 1;
            playSound(SOUND_MOVE);
        }
        else if(key == KEY_ENTER){
            // place mark if cell is empty
            if(grid[cursor] == 0){
                if(turn % 2 == 1)
                    grid[cursor] = 1;
                else
                    grid[cursor] = 2;
                playSound(SOUND_PLACE);
                
                // computer plays after player
                if(getGameWinner(grid) == 0 && !isGridFull(grid)){
                    Sleep(300);
                    computerTurn(grid, possibleMoves, turn);
                    playSound(SOUND_PLACE);
                }
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
        
        // Display header and score panel
        displayHeader();
        displayScorePanel();
        displayEvidenceBar();
        
        int startY = h/2 - 6;
        
        gotoxy(getCenterX(40), startY);
        setColor(COLOR_YELLOW);
        cout << "Games won - ";
        setColor(COLOR_CYAN);
        cout << "X: " << recordx;
        setColor(COLOR_WHITE);
        cout << "  |  ";
        setColor(COLOR_RED);
        cout << "O: " << recordo;
        resetColor();
        
        displayTurn(turn);
        displayGrid(grid, cursor);
        displayControls();
        
        // Display hint for current player
        displayHint(grid, turn);
        
        // get arrow key or enter
        key = getch();
        if(key == 0 || key == 224){
            key = getch();
        }
        
        // move cursor based on arrow keys (PvP)
        if(key == KEY_UP && cursor >= 3){
            cursor -= 3;
            playSound(SOUND_MOVE);
        }
        else if(key == KEY_DOWN && cursor <= 5){
            cursor += 3;
            playSound(SOUND_MOVE);
        }
        else if(key == KEY_LEFT && cursor % 3 != 0){
            cursor -= 1;
            playSound(SOUND_MOVE);
        }
        else if(key == KEY_RIGHT && cursor % 3 != 2){
            cursor += 1;
            playSound(SOUND_MOVE);
        }
        else if(key == KEY_ENTER){
            // place mark if cell is empty
            if(grid[cursor] == 0){
                if(turn % 2 == 1)
                    grid[cursor] = 1;
                else
                    grid[cursor] = 2;
                playSound(SOUND_PLACE);
                turn++;
            }
        }
    } while(!isGridFull(grid) && getGameWinner(grid) == 0);
    
    displayResultScreen(grid, livesX, livesO);
    endScreen(0, 0);
}

// Draw the 3x3 grid with cursor highlight (centered) and colored UI
void displayGrid(int grid[], int cursor){
    int w, h;
    getConsoleSize(w, h);
    int startX = getCenterX(11);
    int startY = h/2 - 2;
    
    for(int i=0; i<9; i+=3){
        gotoxy(startX, startY + (i/3)*2);
        for(int j=0; j<3; j++){
            int cell = i + j;
            
            // show cursor with brackets [ ] and colors
            if(cell == cursor){
                setColor(COLOR_YELLOW);  // Highlight cursor
                if(grid[cell] == 0)
                    cout<<"[.]";
                else if(grid[cell] == 1){
                    setColor(COLOR_CYAN);
                    cout<<"[X]";
                }
                else{
                    setColor(COLOR_RED);
                    cout<<"[O]";
                }
                resetColor();
            }
            else{
                if(grid[cell] == 0)
                    cout<<"   ";
                else if(grid[cell] == 1){
                    setColor(COLOR_CYAN);
                    cout<<" X ";
                    resetColor();
                }
                else{
                    setColor(COLOR_RED);
                    cout<<" O ";
                    resetColor();
                }
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
    gotoxy(getCenterX(48), h/2 + 6);
    setColor(COLOR_DARK_CYAN);
    cout << "[UP/DOWN/LEFT/RIGHT: Move | ENTER: Place Mark]";
    resetColor();
}

// Show whose turn it is (centered)
void displayTurn(int turn){
    int w, h;
    getConsoleSize(w, h);
    gotoxy(getCenterX(12), h/2 - 4);
    if(turn%2==1){
        setColor(COLOR_CYAN);
        cout << ">>> X's Turn! <<<";
    }
    else{
        setColor(COLOR_RED);
        cout << ">>> O's Turn! <<<";
    }
    resetColor();
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
        setColor(COLOR_GREEN);
        cout << "X Wins! +10 points";
        resetColor();
        playSound(SOUND_WIN);
        recordx++;
        scoreX += 10;
        livesO--;
    }
    else if (getGameWinner(grid)==2){
        setColor(COLOR_GREEN);
        cout << "O Wins! +10 points";
        resetColor();
        playSound(SOUND_WIN);
        recordo++;
        scoreO += 10;
        livesX--;
    }
    else{
        setColor(COLOR_YELLOW);
        cout << "Draw! +5 points each";
        resetColor();
        playSound(SOUND_DRAW);
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
    
    gotoxy(getCenterX(30), h/2 + 8);
    setColor(COLOR_DARK_CYAN);
    cout << "Press any key to continue...";
    resetColor();
    getch();
    system("cls");
    
    getConsoleSize(w, h);
    displayHeader();
    
    // Check if game is over (someone ran out of lives)
    if(livesX <= 0 || livesO <= 0){
        int boxWidth = 40;
        int boxX = getCenterX(boxWidth);
        int boxY = h/2 - 4;
        
        drawBox(boxX, boxY, boxWidth, 10, COLOR_CYAN);
        
        gotoxy(boxX + (boxWidth - 16) / 2, boxY + 1);
        setColor(COLOR_YELLOW);
        cout << "=== GAME OVER ===";
        
        gotoxy(boxX + 5, boxY + 3);
        if(livesX <= 0){
            setColor(COLOR_RED);
            cout << "O is the CHAMPION!";
        } else {
            setColor(COLOR_CYAN);
            cout << "X is the CHAMPION!";
        }
        
        gotoxy(boxX + 5, boxY + 5);
        setColor(COLOR_WHITE);
        cout << "Final Score - ";
        setColor(COLOR_CYAN);
        cout << "X: " << scoreX;
        setColor(COLOR_WHITE);
        cout << "  ";
        setColor(COLOR_RED);
        cout << "O: " << scoreO;
        
        // Save high score for logged in player
        int playerScore = (isPvC && playerSymbol == 1) ? scoreX : ((isPvC && playerSymbol == 2) ? scoreO : (scoreX > scoreO ? scoreX : scoreO));
        if(!currentUser.empty()){
            int oldHighScore = getHighScore(currentUser);
            if(playerScore > oldHighScore){
                saveHighScore(currentUser, playerScore);
                gotoxy(boxX + 5, boxY + 7);
                setColor(COLOR_GREEN);
                cout << "NEW HIGH SCORE: " << playerScore << "!";
                playSound(SOUND_WIN);
            } else {
                gotoxy(boxX + 5, boxY + 7);
                setColor(COLOR_YELLOW);
                cout << "Your High Score: " << oldHighScore;
            }
        }
        resetColor();
        
        gotoxy(getCenterX(35), boxY + 12);
        setColor(COLOR_DARK_CYAN);
        cout << "[Press M to return to Main Menu]";
        resetColor();
        
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
        string options[] = {"Continue Playing", "Return to Main Menu"};
        int numOptions = 2;
        
        while(true){
            system("cls");
            getConsoleSize(w, h);
            
            displayHeader();
            displayScorePanel();
            
            int boxWidth = 40;
            int boxX = getCenterX(boxWidth);
            int boxY = h/2 - 4;
            
            drawBox(boxX, boxY, boxWidth, 10, COLOR_CYAN);
            
            gotoxy(boxX + (boxWidth - 18) / 2, boxY + 1);
            setColor(COLOR_YELLOW);
            cout << "=== ROUND COMPLETE ===";
            
            gotoxy(boxX + 5, boxY + 3);
            setColor(COLOR_WHITE);
            cout << "Lives - ";
            setColor(COLOR_CYAN);
            cout << "X: " << livesX;
            setColor(COLOR_WHITE);
            cout << "  |  ";
            setColor(COLOR_RED);
            cout << "O: " << livesO;
            
            gotoxy(boxX + 5, boxY + 4);
            setColor(COLOR_WHITE);
            cout << "Score - ";
            setColor(COLOR_CYAN);
            cout << "X: " << scoreX;
            setColor(COLOR_WHITE);
            cout << "  |  ";
            setColor(COLOR_RED);
            cout << "O: " << scoreO;
            resetColor();
            
            gotoxy(boxX + 5, boxY + 6);
            setColor(COLOR_WHITE);
            cout << "What would you like to do?";
            
            // Draw options
            for(int i = 0; i < numOptions; i++){
                gotoxy(boxX + 5, boxY + 7 + i);
                if(i == selected){
                    setColor(COLOR_GREEN);
                    cout << "> ";
                    setColor(COLOR_YELLOW);
                    cout << options[i];
                    setColor(COLOR_GREEN);
                    cout << " <";
                } else {
                    setColor(COLOR_WHITE);
                    cout << "  " << options[i];
                }
                resetColor();
            }
            
            selKey = getch();
            if(selKey == 0 || selKey == 224){
                selKey = getch();
            }
            
            if(selKey == KEY_UP || selKey == KEY_DOWN){
                selected = (selected == 0) ? 1 : 0;
                playSound(SOUND_MOVE);
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

// Set console text color
void setColor(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Reset console color to white
void resetColor(){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_WHITE);
}

// Play sound effects using Windows Beep function
void playSound(int type){
    switch(type){
        case SOUND_MOVE:
            Beep(400, 100);  // Low frequency, short beep for cursor movement
            break;
        case SOUND_PLACE:
            Beep(600, 150);  // Medium frequency for placing mark
            break;
        case SOUND_WIN:
            Beep(800, 200);  // High frequency
            Sleep(50);
            Beep(1000, 200);
            Sleep(50);
            Beep(1200, 300); // Victory tune
            break;
        case SOUND_LOSE:
            Beep(400, 200);
            Sleep(50);
            Beep(300, 300);  // Sad tune
            break;
        case SOUND_DRAW:
            Beep(500, 200);
            Sleep(50);
            Beep(500, 200);  // Neutral beeps
            break;
    }
}

// Display visual progress bar showing game progress
void displayProgressBar(int scoreX, int scoreO, int livesX, int livesO){
    int w, h;
    getConsoleSize(w, h);
    int startY = h/2 - 8;
    int barWidth = 40;
    
    // Calculate progress percentages
    int maxScore = 100; // Target score for visual representation
    int progressX = (scoreX * barWidth) / maxScore;
    int progressO = (scoreO * barWidth) / maxScore;
    if(progressX > barWidth) progressX = barWidth;
    if(progressO > barWidth) progressO = barWidth;
    
    // Draw X's progress bar
    gotoxy(getCenterX(45), startY);
    setColor(COLOR_CYAN);
    cout << "X Progress: ";
    resetColor();
    cout << "[";
    setColor(COLOR_GREEN);
    for(int i = 0; i < progressX; i++) cout << "=";
    resetColor();
    for(int i = progressX; i < barWidth; i++) cout << " ";
    cout << "] " << scoreX;
    
    // Draw O's progress bar
    gotoxy(getCenterX(45), startY + 1);
    setColor(COLOR_YELLOW);
    cout << "O Progress: ";
    resetColor();
    cout << "[";
    setColor(COLOR_RED);
    for(int i = 0; i < progressO; i++) cout << "=";
    resetColor();
    for(int i = progressO; i < barWidth; i++) cout << " ";
    cout << "] " << scoreO;
}

// Display hint for best move (using AI logic)
void displayHint(int grid[], int turn){
    int w, h;
    getConsoleSize(w, h);
    int currentMark = turn % 2 + 1;
    int opponentMark = (currentMark == 1) ? 2 : 1;
    
    // Try to find winning move
    int move = findWinningMove(grid, currentMark);
    if(move != -1){
        gotoxy(getCenterX(35), h/2 + 8);
        setColor(COLOR_GREEN);
        cout << "Hint: You can WIN at position " << move + 1 << "!";
        resetColor();
        return;
    }
    
    // Try to find blocking move
    move = findWinningMove(grid, opponentMark);
    if(move != -1){
        gotoxy(getCenterX(38), h/2 + 8);
        setColor(COLOR_YELLOW);
        cout << "Hint: BLOCK opponent at position " << move + 1 << "!";
        resetColor();
        return;
    }
    
    // Suggest center if available
    if(grid[4] == 0){
        gotoxy(getCenterX(35), h/2 + 8);
        setColor(COLOR_CYAN);
        cout << "Hint: Center (position 5) is strategic!";
        resetColor();
        return;
    }
    
    // Suggest corners
    int corners[4] = {0, 2, 6, 8};
    for(int i = 0; i < 4; i++){
        if(grid[corners[i]] == 0){
            gotoxy(getCenterX(40), h/2 + 8);
            setColor(COLOR_CYAN);
            cout << "Hint: Corner (position " << corners[i] + 1 << ") is a good move!";
            resetColor();
            return;
        }
    }
    
    // Default hint
    gotoxy(getCenterX(30), h/2 + 8);
    setColor(COLOR_WHITE);
    cout << "Hint: Choose any available position";
    resetColor();
}

// Set console to fullscreen mode
void setFullScreen(){
    // Maximize the console window
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);
    
    // Set console buffer size
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hOut, &csbi);
    
    // Hide cursor for cleaner look
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

// Draw animated loading bar like Mystery Murder Game
void drawLoadingBar(){
    int w, h;
    getConsoleSize(w, h);
    int barWidth = 40;
    int startX = getCenterX(barWidth + 4);
    int startY = h / 2 + 2;
    
    // Draw bar frame
    gotoxy(startX, startY);
    setColor(COLOR_CYAN);
    cout << "[ ";
    for(int i = 0; i < barWidth; i++) cout << " ";
    cout << " ]";
    
    // Animate the bar filling
    for(int i = 0; i < barWidth; i++){
        gotoxy(startX + 2 + i, startY);
        setColor(COLOR_GREEN);
        cout << "=";
        Beep(300 + (i * 10), 30);
        Sleep(50);
    }
    resetColor();
    Sleep(500);
}

// Draw a styled box with border
void drawBox(int x, int y, int width, int height, int color){
    setColor(color);
    
    // Top border
    gotoxy(x, y);
    cout << "+";
    for(int i = 0; i < width - 2; i++) cout << "-";
    cout << "+";
    
    // Side borders
    for(int i = 1; i < height - 1; i++){
        gotoxy(x, y + i);
        cout << "|";
        gotoxy(x + width - 1, y + i);
        cout << "|";
    }
    
    // Bottom border
    gotoxy(x, y + height - 1);
    cout << "+";
    for(int i = 0; i < width - 2; i++) cout << "-";
    cout << "+";
    
    resetColor();
}

// Display the game header (like Mystery Murder Game)
void displayHeader(){
    int w, h;
    getConsoleSize(w, h);
    int boxWidth = 50;
    int startX = getCenterX(boxWidth);
    int startY = 2;
    
    drawBox(startX, startY, boxWidth, 3, COLOR_CYAN);
    
    gotoxy(startX + (boxWidth - 16) / 2, startY + 1);
    setColor(COLOR_GREEN);
    cout << "TIC-TAC-TOE GAME";
    resetColor();
    
    // Developer info below header
    gotoxy(startX + 3, startY + 3);
    setColor(COLOR_YELLOW);
    cout << "Developed by: ";
    setColor(COLOR_CYAN);
    cout << "Adil ur Rehman";
    setColor(COLOR_WHITE);
    cout << " | ";
    setColor(COLOR_YELLOW);
    cout << "Roll: ";
    setColor(COLOR_CYAN);
    cout << "24-CS-760";
    resetColor();
}

// Display score panel in top corner
void displayScorePanel(){
    int w, h;
    getConsoleSize(w, h);
    int startX = w - 25;
    int startY = 2;
    
    setColor(COLOR_WHITE);
    gotoxy(startX, startY);
    cout << "Score: ";
    setColor(COLOR_GREEN);
    cout << scoreX + scoreO;
    
    gotoxy(startX, startY + 1);
    setColor(COLOR_WHITE);
    cout << "High Score: ";
    setColor(COLOR_YELLOW);
    cout << getHighScore(currentUser);
    
    gotoxy(startX, startY + 2);
    setColor(COLOR_WHITE);
    cout << "Lives X: ";
    setColor(COLOR_RED);
    for(int i = 0; i < livesX; i++) cout << "♥ ";
    
    gotoxy(startX, startY + 3);
    setColor(COLOR_WHITE);
    cout << "Lives O: ";
    setColor(COLOR_RED);
    for(int i = 0; i < livesO; i++) cout << "♥ ";
    resetColor();
}

// Display progress bar in top left corner (like Evidence bar in Murder Game)
void displayEvidenceBar(){
    int startX = 2;
    int startY = 1;
    int barWidth = 30;
    int totalMoves = 9;
    int movesMade = scoreX + scoreO > 0 ? min((scoreX + scoreO) / 5, 9) : 0;
    int progress = (movesMade * barWidth) / totalMoves;
    
    gotoxy(startX, startY);
    setColor(COLOR_WHITE);
    cout << "Progress: [ ";
    setColor(COLOR_GREEN);
    for(int i = 0; i < progress; i++) cout << "=";
    resetColor();
    for(int i = progress; i < barWidth; i++) cout << " ";
    cout << " ] " << movesMade << "/" << totalMoves;
}

// Display game instructions screen (like Mystery Murder Game)
void displayGameInstructions(){
    system("cls");
    int w, h;
    getConsoleSize(w, h);
    
    // Display header
    displayHeader();
    
    // Instructions box
    int boxWidth = 60;
    int boxHeight = 14;
    int startX = getCenterX(boxWidth);
    int startY = 7;
    
    drawBox(startX, startY, boxWidth, boxHeight, COLOR_CYAN);
    
    // Title
    gotoxy(startX + (boxWidth - 38) / 2, startY + 1);
    setColor(COLOR_YELLOW);
    cout << "=== WELCOME TO TIC-TAC-TOE GAME ===";
    
    gotoxy(startX + 5, startY + 2);
    setColor(COLOR_GREEN);
    cout << "Welcome to the ultimate Tic-Tac-Toe challenge!";
    
    // Game description
    gotoxy(startX + 5, startY + 4);
    setColor(COLOR_WHITE);
    cout << "Battle your friends or the AI in this classic game.";
    gotoxy(startX + 5, startY + 5);
    cout << "Each player has 3 lives. Win rounds to survive!";
    
    // Instructions list
    gotoxy(startX + 8, startY + 7);
    setColor(COLOR_CYAN);
    cout << "As a player, you must:";
    gotoxy(startX + 10, startY + 8);
    setColor(COLOR_GREEN);
    cout << "> Use Arrow Keys to move cursor";
    gotoxy(startX + 10, startY + 9);
    cout << "> Press ENTER to place your mark";
    gotoxy(startX + 10, startY + 10);
    cout << "> Get 3 in a row to win";
    gotoxy(startX + 10, startY + 11);
    cout << "> Outlast your opponent!";
    
    resetColor();
    
    // Navigation hint
    gotoxy(getCenterX(45), startY + boxHeight + 2);
    setColor(COLOR_YELLOW);
    cout << "Use ARROW KEYS to navigate, ENTER to select";
    
    gotoxy(getCenterX(40), startY + boxHeight + 4);
    setColor(COLOR_GREEN);
    cout << "Press any key to begin your game...";
    resetColor();
    
    playSound(SOUND_PLACE);
    getch();
}

// Get password with asterisks (hidden input)
string getHiddenPassword(){
    string password = "";
    char ch;
    
    while(true){
        ch = getch();
        if(ch == 13){ // Enter key
            break;
        }
        else if(ch == 8){ // Backspace
            if(password.length() > 0){
                password.pop_back();
                cout << "\b \b";
            }
        }
        else if(ch >= 32 && ch <= 126){ // Printable characters
            password += ch;
            setColor(COLOR_YELLOW);
            cout << "*";
            resetColor();
        }
    }
    cout << endl;
    return password;
}

// Select game mode with navigation keys
int selectGameMode(){
    // First show game instructions
    displayGameInstructions();
    
    int selected = 0;
    int key;
    int w, h;
    string options[] = {"Player VS. Computer", "Player VS. Player", "View High Score", "Exit Game"};
    int numOptions = 4;
    
    while(true){
        system("cls");
        getConsoleSize(w, h);
        
        // Display header
        displayHeader();
        
        // Display score panel on top right
        displayScorePanel();
        
        // Menu title
        int startY = h/2 - 2;
        gotoxy(getCenterX(20), startY);
        setColor(COLOR_YELLOW);
        cout << "=== GAME MENU ===";
        resetColor();
        
        // Draw menu box
        int boxWidth = 35;
        int boxHeight = numOptions + 2;
        int boxX = getCenterX(boxWidth);
        int boxY = startY + 2;
        drawBox(boxX, boxY, boxWidth, boxHeight, COLOR_CYAN);
        
        // Draw options
        for(int i = 0; i < numOptions; i++){
            gotoxy(boxX + 3, boxY + 1 + i);
            if(i == selected){
                setColor(COLOR_GREEN);
                cout << "> ";
                setColor(COLOR_YELLOW);
                cout << options[i];
                setColor(COLOR_GREEN);
                int padding = boxWidth - 7 - options[i].length();
                for(int p = 0; p < padding; p++) cout << " ";
                cout << " <";
            } else {
                setColor(COLOR_WHITE);
                cout << "  " << options[i];
            }
            resetColor();
        }
        
        // Controls hint
        gotoxy(getCenterX(45), boxY + boxHeight + 2);
        setColor(COLOR_DARK_CYAN);
        cout << "[UP/DOWN: Navigate | ENTER: Select | ESC: Exit]";
        resetColor();
        
        key = getch();
        if(key == 0 || key == 224){
            key = getch();
        }
        
        if(key == KEY_UP){
            selected = (selected == 0) ? numOptions - 1 : selected - 1;
            playSound(SOUND_MOVE);
        }
        else if(key == KEY_DOWN){
            selected = (selected == numOptions - 1) ? 0 : selected + 1;
            playSound(SOUND_MOVE);
        }
        else if(key == KEY_ENTER){
            playSound(SOUND_PLACE);
            if(selected == 2){
                // View high score
                system("cls");
                displayHeader();
                getConsoleSize(w, h);
                gotoxy(getCenterX(30), h/2);
                setColor(COLOR_YELLOW);
                cout << "Your High Score: ";
                setColor(COLOR_GREEN);
                cout << getHighScore(currentUser);
                resetColor();
                gotoxy(getCenterX(25), h/2 + 2);
                cout << "Press any key to continue...";
                getch();
            }
            else if(selected == 3){
                exit(0);
            }
            else{
                return selected;
            }
        }
        else if(key == KEY_ESC){
            exit(0);
        }
    }
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <ctime>
#include <cstdlib>

using namespace std;

// Constants
const string USERS_FILE = "users.dat";
const string SCORES_FILE = "highscores.dat";

// Structure to store user data
struct User {
    string username;
    string password;
    int wins;
    int losses;
    int draws;
    int lives;
    
    User() : username(""), password(""), wins(0), losses(0), draws(0), lives(3) {}
    User(string u, string p) : username(u), password(p), wins(0), losses(0), draws(0), lives(3) {}
};

// Structure for high scores
struct HighScore {
    string username;
    int score;
    
    HighScore() : username(""), score(0) {}
    HighScore(string u, int s) : username(u), score(s) {}
    
    bool operator>(const HighScore& other) const {
        return score > other.score;
    }
};

// Game Board class
class Board {
private:
    char cells[3][3];
    
public:
    Board() {
        reset();
    }
    
    void reset() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cells[i][j] = ' ';
            }
        }
    }
    
    void display() const {
        cout << "\n";
        cout << "     1   2   3\n";
        cout << "   +---+---+---+\n";
        for (int i = 0; i < 3; i++) {
            cout << " " << (i + 1) << " | " << cells[i][0] << " | " << cells[i][1] << " | " << cells[i][2] << " |\n";
            cout << "   +---+---+---+\n";
        }
        cout << "\n";
    }
    
    bool makeMove(int row, int col, char player) {
        if (row < 0 || row > 2 || col < 0 || col > 2 || cells[row][col] != ' ') {
            return false;
        }
        cells[row][col] = player;
        return true;
    }
    
    char getCell(int row, int col) const {
        if (row < 0 || row > 2 || col < 0 || col > 2) {
            return ' ';
        }
        return cells[row][col];
    }
    
    bool isFull() const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (cells[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }
    
    char checkWinner() const {
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (cells[i][0] != ' ' && cells[i][0] == cells[i][1] && cells[i][1] == cells[i][2]) {
                return cells[i][0];
            }
        }
        
        // Check columns
        for (int j = 0; j < 3; j++) {
            if (cells[0][j] != ' ' && cells[0][j] == cells[1][j] && cells[1][j] == cells[2][j]) {
                return cells[0][j];
            }
        }
        
        // Check diagonals
        if (cells[0][0] != ' ' && cells[0][0] == cells[1][1] && cells[1][1] == cells[2][2]) {
            return cells[0][0];
        }
        if (cells[0][2] != ' ' && cells[0][2] == cells[1][1] && cells[1][1] == cells[2][0]) {
            return cells[0][2];
        }
        
        return ' ';
    }
    
    vector<pair<int, int>> getAvailableMoves() const {
        vector<pair<int, int>> moves;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (cells[i][j] == ' ') {
                    moves.push_back({i, j});
                }
            }
        }
        return moves;
    }
};

// User Authentication System
class UserAuth {
private:
    map<string, User> users;
    
public:
    UserAuth() {
        loadUsers();
    }
    
    void loadUsers() {
        ifstream file(USERS_FILE);
        if (file.is_open()) {
            string username, password;
            int wins, losses, draws, lives;
            while (file >> username >> password >> wins >> losses >> draws >> lives) {
                User user(username, password);
                user.wins = wins;
                user.losses = losses;
                user.draws = draws;
                user.lives = lives;
                users[username] = user;
            }
            file.close();
        }
    }
    
    void saveUsers() {
        ofstream file(USERS_FILE);
        if (file.is_open()) {
            for (const auto& pair : users) {
                const User& user = pair.second;
                file << user.username << " " << user.password << " " 
                     << user.wins << " " << user.losses << " " 
                     << user.draws << " " << user.lives << "\n";
            }
            file.close();
        }
    }
    
    bool registerUser(const string& username, const string& password) {
        if (users.find(username) != users.end()) {
            return false;
        }
        users[username] = User(username, password);
        saveUsers();
        return true;
    }
    
    User* login(const string& username, const string& password) {
        if (users.find(username) != users.end() && users[username].password == password) {
            return &users[username];
        }
        return nullptr;
    }
    
    void updateUser(const User& user) {
        users[user.username] = user;
        saveUsers();
    }
};

// High Score System
class HighScoreSystem {
private:
    vector<HighScore> scores;
    
public:
    HighScoreSystem() {
        loadScores();
    }
    
    void loadScores() {
        ifstream file(SCORES_FILE);
        if (file.is_open()) {
            string username;
            int score;
            while (file >> username >> score) {
                scores.push_back(HighScore(username, score));
            }
            file.close();
        }
        sort(scores.begin(), scores.end(), greater<HighScore>());
    }
    
    void saveScores() {
        ofstream file(SCORES_FILE);
        if (file.is_open()) {
            for (const auto& score : scores) {
                file << score.username << " " << score.score << "\n";
            }
            file.close();
        }
    }
    
    void addScore(const string& username, int score) {
        scores.push_back(HighScore(username, score));
        sort(scores.begin(), scores.end(), greater<HighScore>());
        
        // Keep only top 10 scores
        if (scores.size() > 10) {
            scores.resize(10);
        }
        
        saveScores();
    }
    
    void displayHighScores() {
        cout << "\n=== HIGH SCORES ===\n";
        if (scores.empty()) {
            cout << "No high scores yet!\n";
        } else {
            for (size_t i = 0; i < scores.size(); i++) {
                cout << (i + 1) << ". " << scores[i].username << " - " << scores[i].score << " points\n";
            }
        }
        cout << "\n";
    }
};

// AI Player with smart moves
class AIPlayer {
private:
    char aiSymbol;
    char humanSymbol;
    
    int minimax(Board& board, bool isMaximizing, int depth) {
        char winner = board.checkWinner();
        
        if (winner == aiSymbol) {
            return 10 - depth;
        } else if (winner == humanSymbol) {
            return depth - 10;
        } else if (board.isFull()) {
            return 0;
        }
        
        if (isMaximizing) {
            int bestScore = -1000;
            vector<pair<int, int>> moves = board.getAvailableMoves();
            for (const auto& move : moves) {
                board.makeMove(move.first, move.second, aiSymbol);
                int score = minimax(board, false, depth + 1);
                board.makeMove(move.first, move.second, ' ');
                bestScore = max(score, bestScore);
            }
            return bestScore;
        } else {
            int bestScore = 1000;
            vector<pair<int, int>> moves = board.getAvailableMoves();
            for (const auto& move : moves) {
                board.makeMove(move.first, move.second, humanSymbol);
                int score = minimax(board, true, depth + 1);
                board.makeMove(move.first, move.second, ' ');
                bestScore = min(score, bestScore);
            }
            return bestScore;
        }
    }
    
public:
    AIPlayer(char ai, char human) : aiSymbol(ai), humanSymbol(human) {}
    
    pair<int, int> getBestMove(Board& board) {
        int bestScore = -1000;
        pair<int, int> bestMove = {-1, -1};
        
        vector<pair<int, int>> moves = board.getAvailableMoves();
        for (const auto& move : moves) {
            board.makeMove(move.first, move.second, aiSymbol);
            int score = minimax(board, false, 0);
            board.makeMove(move.first, move.second, ' ');
            
            if (score > bestScore) {
                bestScore = score;
                bestMove = move;
            }
        }
        
        return bestMove;
    }
};

// Game Engine
class Game {
private:
    Board board;
    User* player1;
    User* player2;
    UserAuth& auth;
    HighScoreSystem& scoreSystem;
    bool isPvC;
    AIPlayer* ai;
    
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    bool getPlayerMove(char symbol, const string& playerName) {
        int row, col;
        cout << playerName << "'s turn (" << symbol << ")\n";
        cout << "Enter row (1-3): ";
        
        if (!(cin >> row)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            return false;
        }
        
        cout << "Enter column (1-3): ";
        if (!(cin >> col)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            return false;
        }
        
        row--;
        col--;
        
        if (!board.makeMove(row, col, symbol)) {
            cout << "Invalid move! Try again.\n";
            return false;
        }
        
        return true;
    }
    
public:
    Game(User* p1, User* p2, UserAuth& a, HighScoreSystem& hs, bool pvC) 
        : player1(p1), player2(p2), auth(a), scoreSystem(hs), isPvC(pvC), ai(nullptr) {
        if (isPvC) {
            ai = new AIPlayer('O', 'X');
        }
    }
    
    ~Game() {
        if (ai) {
            delete ai;
        }
    }
    
    void play() {
        board.reset();
        char currentPlayer = 'X';
        User* currentUser = player1;
        
        while (true) {
            clearScreen();
            board.display();
            
            cout << "\n" << player1->username << " (X) vs " 
                 << (isPvC ? "Computer (O)" : player2->username + " (O)") << "\n";
            cout << player1->username << " Lives: " << player1->lives << " | ";
            if (!isPvC) {
                cout << player2->username << " Lives: " << player2->lives;
            } else {
                cout << "Computer Lives: Unlimited";
            }
            cout << "\n\n";
            
            bool validMove = false;
            
            if (currentPlayer == 'X') {
                validMove = getPlayerMove('X', player1->username);
            } else {
                if (isPvC) {
                    cout << "Computer is thinking...\n";
                    pair<int, int> move = ai->getBestMove(board);
                    board.makeMove(move.first, move.second, 'O');
                    validMove = true;
                    cout << "Computer played: Row " << (move.first + 1) 
                         << ", Column " << (move.second + 1) << "\n";
                    cin.ignore();
                    cout << "Press Enter to continue...";
                    cin.get();
                } else {
                    validMove = getPlayerMove('O', player2->username);
                }
            }
            
            if (!validMove) {
                continue;
            }
            
            char winner = board.checkWinner();
            
            if (winner != ' ') {
                clearScreen();
                board.display();
                
                if (winner == 'X') {
                    cout << "\n" << player1->username << " wins!\n";
                    player1->wins++;
                    if (!isPvC) {
                        player2->losses++;
                        player2->lives--;
                    }
                    int score = player1->wins * 10 + player1->lives * 5;
                    scoreSystem.addScore(player1->username, score);
                } else {
                    if (isPvC) {
                        cout << "\nComputer wins!\n";
                        player1->losses++;
                        player1->lives--;
                    } else {
                        cout << "\n" << player2->username << " wins!\n";
                        player2->wins++;
                        player1->losses++;
                        player1->lives--;
                        int score = player2->wins * 10 + player2->lives * 5;
                        scoreSystem.addScore(player2->username, score);
                    }
                }
                
                auth.updateUser(*player1);
                if (!isPvC && player2) {
                    auth.updateUser(*player2);
                }
                
                break;
            }
            
            if (board.isFull()) {
                clearScreen();
                board.display();
                cout << "\nIt's a draw!\n";
                player1->draws++;
                if (!isPvC) {
                    player2->draws++;
                    auth.updateUser(*player2);
                }
                auth.updateUser(*player1);
                break;
            }
            
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            currentUser = (currentUser == player1) ? player2 : player1;
        }
        
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
};

// Display user stats
void displayUserStats(const User& user) {
    cout << "\n=== " << user.username << "'s Stats ===\n";
    cout << "Wins: " << user.wins << "\n";
    cout << "Losses: " << user.losses << "\n";
    cout << "Draws: " << user.draws << "\n";
    cout << "Lives Remaining: " << user.lives << "\n";
    cout << "Total Games: " << (user.wins + user.losses + user.draws) << "\n";
    cout << "\n";
}

// Main menu
void mainMenu() {
    UserAuth auth;
    HighScoreSystem scoreSystem;
    User* currentUser = nullptr;
    
    srand(time(0));
    
    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        cout << "========================================\n";
        cout << "   TIC-TAC-TOE - Feature-Rich Edition\n";
        cout << "========================================\n\n";
        
        if (currentUser == nullptr) {
            cout << "1. Register\n";
            cout << "2. Login\n";
            cout << "3. View High Scores\n";
            cout << "4. Exit\n";
            cout << "\nChoose an option: ";
            
            int choice;
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore();
            
            if (choice == 1) {
                string username, password;
                cout << "\nEnter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                
                if (auth.registerUser(username, password)) {
                    cout << "\nRegistration successful!\n";
                } else {
                    cout << "\nUsername already exists!\n";
                }
                
                cout << "Press Enter to continue...";
                cin.get();
                
            } else if (choice == 2) {
                string username, password;
                cout << "\nEnter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                
                currentUser = auth.login(username, password);
                if (currentUser) {
                    cout << "\nLogin successful! Welcome, " << currentUser->username << "!\n";
                    cout << "Press Enter to continue...";
                    cin.get();
                } else {
                    cout << "\nInvalid username or password!\n";
                    cout << "Press Enter to continue...";
                    cin.get();
                }
                
            } else if (choice == 3) {
                scoreSystem.displayHighScores();
                cout << "Press Enter to continue...";
                cin.get();
                
            } else if (choice == 4) {
                cout << "\nThank you for playing!\n";
                break;
            }
            
        } else {
            cout << "Logged in as: " << currentUser->username << "\n";
            cout << "Lives: " << currentUser->lives << "\n\n";
            
            if (currentUser->lives <= 0) {
                cout << "You have no lives left! Please register a new account.\n";
                currentUser = nullptr;
                cout << "Press Enter to continue...";
                cin.get();
                continue;
            }
            
            cout << "1. Play vs Computer (PvC)\n";
            cout << "2. Play vs Player (PvP)\n";
            cout << "3. View My Stats\n";
            cout << "4. View High Scores\n";
            cout << "5. Logout\n";
            cout << "\nChoose an option: ";
            
            int choice;
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore();
            
            if (choice == 1) {
                Game game(currentUser, nullptr, auth, scoreSystem, true);
                game.play();
                
            } else if (choice == 2) {
                string opponent;
                cout << "\nEnter opponent's username: ";
                getline(cin, opponent);
                
                string password;
                cout << "Enter opponent's password: ";
                getline(cin, password);
                
                User* player2 = auth.login(opponent, password);
                if (player2) {
                    if (player2->lives <= 0) {
                        cout << "\n" << opponent << " has no lives left!\n";
                        cout << "Press Enter to continue...";
                        cin.get();
                    } else {
                        Game game(currentUser, player2, auth, scoreSystem, false);
                        game.play();
                    }
                } else {
                    cout << "\nInvalid opponent credentials!\n";
                    cout << "Press Enter to continue...";
                    cin.get();
                }
                
            } else if (choice == 3) {
                displayUserStats(*currentUser);
                cout << "Press Enter to continue...";
                cin.get();
                
            } else if (choice == 4) {
                scoreSystem.displayHighScores();
                cout << "Press Enter to continue...";
                cin.get();
                
            } else if (choice == 5) {
                currentUser = nullptr;
                cout << "\nLogged out successfully!\n";
                cout << "Press Enter to continue...";
                cin.get();
            }
        }
    }
}

int main() {
    mainMenu();
    return 0;
}

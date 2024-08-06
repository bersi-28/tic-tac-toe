#include <iostream>
#include <cstdlib> // system("cls")
#include <cstring> // strlen()
#include <windows.h> // Coloring
#include <fstream> // Read File

using namespace std;

string readFile(string fileName, string fallback) {
    string totalFile = "";
    string line;
    ifstream MyFile(fileName);

    if (MyFile.fail()) {
        return fallback;
    }

    // getLine returns the number of characters in the line that is read
    // so when it reaches past the final line, it will read no character, therefore it should stop
    while (getline(MyFile, line)) {
        totalFile += line + "\n";
    }

    MyFile.close();
    return totalFile;

}

void displayBoard(char board[3][3]) {
    HANDLE col = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(col, 7); // Set To Default
    system("cls");

    SetConsoleTextAttribute(col, 14);
    cout << "_____________\n";
    for(int i = 0; i < 3; i++) {
        SetConsoleTextAttribute(col, 14);
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            char current = board[i][j];
            if (current == ' ') {
                SetConsoleTextAttribute(col, 8);
                cout << j + 3*i + 1;
            } else {
                if (current == 'O') {
                    SetConsoleTextAttribute(col, 1);
                } else if (current == 'X') {
                    SetConsoleTextAttribute(col, 4);
                }
                cout << current;
            }
            SetConsoleTextAttribute(col, 14);
            cout << " | ";
        }
        SetConsoleTextAttribute(col, 14);
        cout << "\n-------------\n";
        SetConsoleTextAttribute(col, 7); // Set To Default
    }
}

string validateInput(char board[3][3], int number) {
    if (number > 9 || number < 1) {
        return "Number must be between 1-9.";
    }
    int rowIndex = (number - 1) / 3;
    int colIndex = (number - 1) % 3;
    char current = board[rowIndex][colIndex];
    if (current == ' ') {
        return "";
    } else {
        return "Cell is already filled.";
    }
}

bool isStringValidNumber(string numb) {
    int len = numb.size();
    if (len == 0) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        char current = numb[i];
        if (current < '0' || current > '9') {
            return false;
        }
    }
    return true;
}

int getGameState(char board[3][3]) {
    /**
    * if O wins, return 1,
    * if X wins, return 2,
    * if tie and over, return 3,
    * if game not over, return 0
    */

    for (int i =0; i < 3; i++) {
        // Check Horizontals
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            char turn = board[i][0];
            if (turn == 'O') {
                return 1; // O Wins
            } else if (turn == 'X') {
                return 2; // X Wins
            }
        }
        // Check Verticals
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            char turn = board[0][i];
            if (turn == 'O') {
                return 1; // O Wins
            } else if (turn == 'X') {
                return 2; // X Wins
            }
        }
    }
    // Check Diagonals
    if (
        (board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        ) {
        char turn = board[1][1];
        if (turn == 'O') {
            return 1; // O Wins
        } else if (turn == 'X') {
            return 2; // X Wins
        }
    }
    // Is Completely Filled?
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            char current = board[i][j];
            if (current == ' ') {
                return 0; // Game not over yet!
            }
        }
    }
    return 3; // Tie, Board is completely filled.
}


void playGame() {
    HANDLE col = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(col, 7); // Set To Default
    char matrix[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    displayBoard(matrix);

    char turn = 'O';
    int input;
    string line;
    int state = 0;
    while (state == 0) {
        cout << turn << "'s Turn: ";
        getline(cin, line);
        if (!isStringValidNumber(line)) {
                SetConsoleTextAttribute(col, 4);
            cout << "Please, enter a valid number." << endl;
                    SetConsoleTextAttribute(col, 7);

            continue;
        }
        input = stoi(line);
        string validation = validateInput(matrix, input);
        if (validation != "") {
            SetConsoleTextAttribute(col, 4); // Error, 4/12
            cout << validation << endl;
            SetConsoleTextAttribute(col, 7);
            continue;
        }
        int rowIndex = (input - 1) / 3;
        int colIndex = (input - 1) % 3;
        matrix[rowIndex][colIndex] = turn;
        turn = turn == 'O' ? 'X' : 'O';

        state = getGameState(matrix);
        displayBoard(matrix);
    }

    // displayBoard(matrix);
    string gameOver = readFile("gameover.txt", "Game Over!");
    SetConsoleTextAttribute(col, 5);
    cout << gameOver << endl;
    SetConsoleTextAttribute(col, 7);
    if (state == 1) {
        cout << "O Wins!" << endl;
    } else if (state == 2) {
        cout << "X Wins!" << endl;
    } else if (state == 3) {
        cout << "Tie!";
    }
}

void displayCredit() {
    system("cls");
    HANDLE col = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(col, 11);
    string logo = readFile("logo.txt", "Tic-Tac-Toe O/X");
    cout << logo << endl;
    SetConsoleTextAttribute(col, 7); // Default

    cout << "Credits" << endl;
    string names[][2]= {
        {"Abel Tadesse", "\tUGR/1059/15"},
        {"Abenezer Alebachew", "UGR/4429/15"},
        {"Addis Alemayehu", "UGR/4143/15"},
        {"Bersabeh Degefu","UGR/2049/15"},
        {"Dejen Achenef","UGR/7100/15"},
        {"Desalegn Derbe","UGR/3992/15"},
        {"Eden Awoke","\tUGR/2222/15"},
        {"Hana Hilekiros","UGR/5655/15"},
        {"Hanan Abdulshikur","UGR/6257/15"},
        {"Hanan Fatih","\tUGR/6009/15"},
    };

    for (int i = 0; i < 10; i++) {
       cout << i+1 << ". " << names[i][0] << "\t" << names[i][1] << endl;
    }
}

// Tic-Tac-Toe
int main() {
    HANDLE col = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(col, 11);
    string logo = readFile("logo.txt", "Tic-Tac-Toe O/X");
    cout << logo << endl;
    SetConsoleTextAttribute(col, 7); // Default

    string response;
    cout << "Press any key to start the game...";
    getline(cin, response);


    do {
        playGame();
        cout << "\nDo you want to play again? (Y/N): ";
        getline(cin, response);
    } while (response == "Y" || response == "y");

    displayCredit();

    cout << "\nPress any key to close the game...";
    getline(cin, response);

    return 0;
}

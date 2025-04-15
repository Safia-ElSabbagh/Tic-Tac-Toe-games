#ifndef BOARD_GAMES_FOURINROW_H
#define BOARD_GAMES_FOURINROW_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;
static bool isRandom2 = false;

template <typename T>
class Connect_Four_Board:public Board<T> {
public:
    Connect_Four_Board (){
        this->columns = 7;
        this->rows = 6;
        // Allocate memory for the rows (6 rows)
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            // Allocate memory for the columns in each row (7 columns)
            this->board[i] = new char[this->columns];
            // Initialize each cell to 0 (representing an empty state)
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
        // Initialize the number of moves to 0
        this->n_moves = 0;

    }

    bool update_board(int x, int y, T symbol) override {
        // Check if the column is valid
        if (y < 0 || y >= this->columns) {
            if(!isRandom2){
                cerr << "Invalid column! \n";
            }
            return false;
        }

        // Search from the bottom of the column (row 5) to the top (row 0)
        for (int row = 5; row >= 0; row--) {
            if (symbol == 0){
                this->n_moves--;
                this->board[x][y] = 0;
            }
            else if (this->board[row][y] == 0) {
                this->board[row][y] = toupper(symbol);
                this->n_moves++;
                return true;
            }
        }

        // If no empty spot is found
        if(!isRandom2){
            cerr << "Column is full! \n";
        }
        return false;
    }


    void display_board() override {
        // Print the column indices
        cout << "   ";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(3) << j << "  "; // Column numbers at the top
        }
        cout << "\n";

        // Print each row with its content
        for (int i = 0; i < this->rows; i++) {
            cout << i << " |"; // Row index at the start
            for (int j = 0; j < this->columns; j++) {
                char display_char = this->board[i][j] == 0 ? ' ' : this->board[i][j]; // Empty space for 0
                cout << setw(3) << display_char << " |";
            }
            cout << "\n    " << "____________________________________" << "\n"; // Separator line
        }
        cout << endl;
    }


    bool is_win() override{
        // Check rows and columns
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns - 3; j++) {
                // Check row
                if (this->board[i][j] == this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2] &&
                    this->board[i][j+2] == this->board[i][j+3] && this->board[i][j] != 0) {
                    return true;
                }
            }
        }

        for (int j = 0; j < this->columns; j++) {
            for (int i = 0; i < this->rows - 3; i++) {
                // Check column
                if (this->board[i][j] == this->board[i+1][j] && this->board[i+1][j] == this->board[i+2][j] &&
                    this->board[i+2][j] == this->board[i+3][j] && this->board[i][j] != 0) {
                    return true;
                }
            }
        }

        // Check diagonals
        for (int i = 0; i < this->rows - 3; i++) {
            for (int j = 0; j < this->columns - 3; j++) {
                // Principal diagonal
                if (this->board[i][j] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j+2] &&
                    this->board[i+2][j+2] == this->board[i+3][j+3] && this->board[i][j] != 0) {
                    return true;
                }
                // Bottom-left to top-right
                if (this->board[i+3][j] == this->board[i+2][j+1] && this->board[i+2][j+1] == this->board[i+1][j+2] &&
                    this->board[i+1][j+2] == this->board[i][j+3] && this->board[i+3][j] != 0) {
                    return true;
                }
            }
        }

        return false;
    }
    bool is_draw() override{
        return (this->n_moves == 42 && !is_win());
    }
    bool game_is_over() override{
        return is_win() || is_draw();
    }

};

template <typename T>
class Connect_Four_Player : public Player<T> {
public:
    Connect_Four_Player (string name, T symbol);
    void getmove(int& , int& y) {
        cout << "\nPlease enter your move by specifying the column (0-6): \n";
        cin >> y;

    }

};

template <typename T>
class Connect_Four_Random_Player : public RandomPlayer<T>{
public:
    Connect_Four_Random_Player (T symbol);
    void getmove(int &x, int &y) override{
        x = rand() % this->dimension;
        y = rand() % this->dimension;
    }
};

template <typename T>
Connect_Four_Player<T>::Connect_Four_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
Connect_Four_Random_Player<T>::Connect_Four_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 6;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

#endif

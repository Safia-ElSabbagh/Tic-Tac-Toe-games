#ifndef BOARD_GAMES_NUMERICALTICTACTOE_H
#define BOARD_GAMES_NUMERICALTICTACTOE_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
static bool isRandom5 = false;


template <typename T>
class Numerical_TicTacToe_Board: public Board<T> {
private:
    vector<int> player1_values = {1, 3, 5, 7, 9};
    vector<int> player2_values = {2, 4, 6, 8};

public:
    Numerical_TicTacToe_Board() {
        this->columns = 3;
        this->rows = 3;
        this->board = new int*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new int[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
    }
    bool update_board(int x, int y, T symbol) override {
        // Validate position
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
            if(!isRandom5 ){
                cerr << "Invalid move! Position out of bounds.\n";
            }
            return false;
        }
        if (this->board[x][y] != 0) {
            if(!isRandom5){
                cerr << "Invalid move! Cell already occupied.\n";
            }
            return false;
        }
        // Player 1's turn
        if (this->n_moves % 2 == 0) {
            if (find(player1_values.begin(), player1_values.end(), symbol) != player1_values.end()) {
                this->board[x][y] = symbol;
                player1_values.erase(remove(player1_values.begin(), player1_values.end(), symbol), player1_values.end());
                this->n_moves++;
                return true;
            } else {
                if(!isRandom5 ){
                    cerr<< "Invalid move! Number not allowed or already used by Player 1.\n";
                }
                return false;
            }
        }
        // Player 2's turn
        else {
            if (find(player2_values.begin(), player2_values.end(), symbol) != player2_values.end()) {
                this->board[x][y] = symbol;
                player2_values.erase(remove(player2_values.begin(), player2_values.end(), symbol), player2_values.end());
                this->n_moves++;
                return true;
            } else {
                if(!isRandom5){
                    cerr<< "Invalid move! Number not allowed or already used by Player 2.\n";
                }
                return false;
            }
        }
    }

    void display_board() override {
        cout << "   ";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(3) << j << "  ";
        }
        cout << "\n";

        for (int i = 0; i < this->rows; i++) {
            cout << i << " |";
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] == 0) {
                    cout << setw(3) << " " << " |";
                } else {
                    cout << setw(3) << this->board[i][j] << " |";
                }
            }
            cout << "\n    " << "-----------------" << "\n";
        }
        cout << endl;
    }

    bool is_win() override {
        // Check rows and columns
        for (int i = 0; i < this->rows; i++) {
            if (this->board[i][0] + this->board[i][1] + this->board[i][2] == 15
                &&(this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0)) {
                return true;
            }
        }
        for (int j = 0; j < this->columns; j++) {
            if (this->board[0][j] + this->board[1][j] + this->board[2][j] == 15 &&
                this->board[0][j] != 0 &&  this->board[1][j] != 0 &&  this->board[2][j] != 0) {
                return true;
            }
        }

        // Check diagonals
        if ((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15 &&
             (this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0 )) ||
            (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15 &&
             (this->board[0][2] != 0 && this->board[1][1] != 0) &&this->board[2][0] != 0)) {
            return true;
        }

        return false;
    }

    bool is_draw() override {
        return (this->n_moves == 9 && !is_win());
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

template <typename T>
class Numerical_TicTacToe_Player : public Player<T> {
public:
    Numerical_TicTacToe_Player(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y)override{
        cout << "\nPlease enter your index (row and column, space-separated):\n ";
        cin >> x >> y;
        int number ;
        cout << "\nPlease enter the number you want to add:\n ";
        cin >> number;
        this ->symbol = number;
    }

};

template <typename T>
class Numerical_TicTacToe_Random_Player : public RandomPlayer<T> {
public:
    Numerical_TicTacToe_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
Numerical_TicTacToe_Random_Player<T>::Numerical_TicTacToe_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Numerical_TicTacToe_Random_Player<T>::getmove(int& x, int& y){
    isRandom5 = true;
    vector<int> numbers = {1,2,3, 4,5, 6,7, 8,9};
    int randomNumber;

    randomNumber = numbers[rand() % numbers.size()];

    x = rand() % this->dimension;
    y = rand() % this->dimension;

    // Store the number as used
    this->symbol = randomNumber;

}

#endif // BOARD_GAMES_NUMERICALTICTACTOE_H
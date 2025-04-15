#ifndef BOARD_GAMES_PYRAMID_TICTACTOE_H
#define BOARD_GAMES_PYRAMID_TICTACTOE_H
#include <iostream>
#include <iomanip>
#include "BoardGame_Classes.h"

using namespace std;
static bool isRandom1 = false;

template <typename T>
class PyramidTicTacToe : public Board<T> {
public:
    PyramidTicTacToe() {
        this->rows = 3;
        this->columns = 5;
        int count = 1;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; ++j) {
                this->board[i][j] = ' ';
                if((i == 0 && j == 2) || (i == 1 && j >= 1 && j <= 3) || i == 2){
                    this->board[i][j] = '0' + count;
                    count++;
                }
                this->n_moves = 0;
            }
        }
    }
    void display_board() override{
        /// Row 1
        cout << setw(14) << "| " << this->board[0][2] << " |\n";
        /// Row 2
        cout << setw(8) << "| " << this->board[1][1] << " | | "
             << this->board[1][2] << " | | " << this->board[1][3] << " |\n";
        /// Row 3
        cout << "| " << this->board[2][0] << " | | " << this->board[2][1] << " | | " << this->board[2][2] << " | | "
             << this->board[2][3] << " | | " << this->board[2][4] << " |\n";
    }
    bool update_board(int x, int y, T symbol) override{
        /// Check if the index the user will enter within the boundary and doesn't contain X, O already or not
        if(((x == 0 && y == 2) ||
            (x == 1 && y >= 1 && y <= 3) ||
            (x == 2 && y >= 0 && y <= 4)) &&
           (this->board[x][y] != 'X' && this->board[x][y] != 'O' || symbol == 0)){
            if (symbol == 0){
                this->n_moves--;
                this->board[x][y] = ' ';
            }
            else {
                this->n_moves++;
                this->board[x][y] = toupper(symbol);
            }
            return true;
        }
//        if(!isRandom1){
//            cerr << "Invalid move";
//        }
        return false;
    }
    /// Returns true if there is any winner
    bool is_win(){
        /// Check diagonals
        if((this->board[0][2] == this->board[1][1] && this->board[0][2] == this->board[2][0] && this->board[0][2] != ' ') ||
        (this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4] && this->board[0][2] != ' ')){
            return true;
        }
        /// Check the middle column and middle row
        if((this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2] && this->board[0][2] != ' ')
        || (this->board[1][1] == this->board[1][2] && this->board[1][2] == this->board[1][3] && this->board[1][1] != ' ')){
            return true;
        }
        /// check last row
        for (int i = 0; i < this->columns - 2; ++i) {
            if (this->board[2][i] == this->board[2][i + 1] &&
                this->board[2][i] == this->board[2][i + 2] &&
                this->board[2][i] != ' ') {
                return true;
            }
        }
        return false;
    }

    /// Return true if all moves are done and no winner
    bool is_draw(){
        return (this->n_moves == 9 && !is_win());
    }

    /// Return true if the game is over
    bool game_is_over(){
        return (is_win() || is_draw());
    }
};

template <typename T>
class Pyramid_player : public Player<T>{
public:
    Pyramid_player(string name, T symbol) : Player<T>(name, symbol){}
    void getmove(int& x, int& y) override{
        int index;
        cout << "Enter the index of box you want to add in:";
        cin >> index;
        /// Assign each number in the pyramid to its corresponding index
        if(index == 1){
            x = 0;
        }else if(index == 2 || index == 3 || index == 4){
            x = 1;
        }else if(index == 5 || index == 6 || index == 7 || index == 8 || index == 9){
            x = 2;
        }
        if(index == 5){
            y = 0;
        }else if(index == 1 || index == 3 || index == 7){
            y = 2;
        }else if(index == 6 || index == 2){
            y = 1;
        }else if(index == 8 || index == 4){
            y = 3;
        }else if(index == 9){
            y = 4;
        }
    }
};
template <typename T>
class Pyramid_randomPlayer : public RandomPlayer<T> {
public:
    Pyramid_randomPlayer(T symbol) : RandomPlayer<T>(symbol) {
        this->dimension = 3;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    }
    void getmove(int& x, int& y) override{
        x = rand() % this->dimension;  // Random number between 0 and 2
        y = rand() % 5;
        isRandom1 = true;
    }
};

#endif //BOARD_GAMES_PYRAMID_TICTACTOE_H

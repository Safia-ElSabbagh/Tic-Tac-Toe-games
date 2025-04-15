#ifndef BOARD_GAMES_SUS_H
#define BOARD_GAMES_SUS_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

static bool isRandom9 = false;
Player<char>* globalPlayers_SUS[2];

template <typename T>
class SUS_Board:public Board<T> {
private:
    bool countedRows[3] = {false, false, false};
    bool countedCols[3] = {false, false, false};
    bool countedDiagonals[2] = {false, false};
    int player1Points = 0;
    int player2Points = 0;

public:
    SUS_Board (){
        this->rows = this->columns = 3;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
        this->n_moves = 0;
    }

    // Destructor to free dynamically allocated memory
    ~SUS_Board() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
        // Reset counted flags as they are of type static for multi games
        for (int i = 0; i < 3; i++) {
            countedRows[i] = false;
            countedCols[i] = false;
        }
        countedDiagonals[0] = countedDiagonals[1] = false;

        globalPlayers_SUS[0] = nullptr;
        globalPlayers_SUS[1] = nullptr;

    }

    bool update_board (int x , int y , T symbol) override{
        if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| symbol == 0)) {
            if (symbol == 0){
                this->n_moves--;
                this->board[x][y] = 0;
            }
            else {
                this->n_moves++;
                this->board[x][y] = toupper(symbol);
            }

            return true;
        }else{
            if(!isRandom9){
                cerr << "Invalid move! \n";
            }
        }
        return false;
    }
    void display_board () override{
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
            cout << "\n    " << "________________" << "\n"; // Separator line
        }
        cout << endl;
    }

    void SUS_count() {

        for (int i = 0; i < this->rows; i++) {
            // Check row
            if (!countedRows[i] && this->board[i][0] == 'S' && this->board[i][1] == 'U' && this->board[i][2] == 'S') {
                if (this->n_moves % 2 == 0) {
                    player2Points++;
                } else {
                    player1Points++;
                }
                countedRows[i] = true; // Mark row as counted
            }

            // Check column
            if (!countedCols[i] && this->board[0][i] == 'S' && this->board[1][i] == 'U' && this->board[2][i] == 'S') {
                if (this->n_moves % 2 == 0) {
                    player2Points++;
                } else {
                    player1Points++;
                }
                countedCols[i] = true; // Mark column as counted
            }
        }

        // Check diagonals
        if (!countedDiagonals[0] && this->board[0][0] == 'S' && this->board[1][1] == 'U' && this->board[2][2] == 'S') {
            if (this->n_moves % 2 == 0) {
                player2Points++;
            } else {
                player1Points++;
            }
            countedDiagonals[0] = true; // Mark diagonal as counted
        }
        if (!countedDiagonals[1] && this->board[0][2] == 'S' && this->board[1][1] == 'U' && this->board[2][0] == 'S') {
            if (this->n_moves % 2 == 0) {
                player2Points++;
            } else {
                player1Points++;
            }
            countedDiagonals[1] = true; // Mark diagonal as counted
        }

    }


    bool is_win() override{
        SUS_count();

        // Determine game end condition
        if (this->n_moves == 9) {
            if (player1Points > player2Points) {
                *globalPlayers_SUS[1] = *globalPlayers_SUS[0];
                return true;
            }
            else if(player1Points < player2Points){
                *globalPlayers_SUS[0] = *globalPlayers_SUS[1];
                return true;
            }

        }
        return false;
    }


    bool is_draw() override {
        // A draw happens when the board is full and no player has won
        return (this->n_moves == 9 && !is_win());
    }

    bool game_is_over() override {
        // The game ends if there's a win or a draw
        return is_win() || is_draw();
    }

};

template <typename T>
class SUS_Player : public Player<T> {
public:
    SUS_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T>{
public:
    SUS_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

template <typename T>
SUS_Player<T>::SUS_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void SUS_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void SUS_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    isRandom9 = true;
}

#endif //BOARD_GAMES_SUS_H

#ifndef BOARD_GAMES_MISERE_TIC_TAC_TOE_H
#define BOARD_GAMES_MISERE_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

Player<char>* globalPlayers2[2];


template <typename T>
class Misere_Tic_Tac_Toe:public Board<char> {
public:
    Misere_Tic_Tac_Toe(){
        rows = 3;
        columns = 3;

        // Dynamically allocate the 2D board
        board = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new char[columns];
            // Initialize board with empty spaces
            for (int j = 0; j < columns; ++j) {
                board[i][j] = ' ';
            }
        }
    }

    // Destructor to free dynamically allocated memory
    ~Misere_Tic_Tac_Toe() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;

        globalPlayers2[0] = nullptr;
        globalPlayers2[1] = nullptr;
    }

    bool update_board (int x , int y , char symbol) override{
        if(x < 0 || x>= rows || y < 0 || y >= columns)
            return false;

        //Check if the cell is empty to allow move
        if(board[x][y] != ' ')
            return false;

        board[x][y] = symbol;   //If valid move place the player symbol in cell
        n_moves++;

        return true;
    }

    void display_board () override{
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                cout<< board[i][j];
                if (j < columns - 1) cout << " | ";
            }
            cout<< endl;
            if (i < rows - 1) cout << "-----------" << endl;
        }
    }



    bool is_win() override{
        // Check rows
        for (int i = 0; i < rows; i++) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
                if(board[i][0] == 'X')
                    *globalPlayers2[0] = *globalPlayers2[1];  // This copies the entire player object
                else
                    *globalPlayers2[1] = *globalPlayers2[0];  // This copies the entire player object
                return true;
            }
        }

        // Check columns
        for (int i = 0; i < columns; i++) {
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
                if(board[0][i] == 'X')
                    *globalPlayers2[0] = *globalPlayers2[1];  // This copies the entire player object
                else
                    *globalPlayers2[1] = *globalPlayers2[0];  // This copies the entire player object
                return true;
            }
        }

        // Check diagonals
        if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == 'X') ||
            (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == 'X')) {
            *globalPlayers2[0] = *globalPlayers2[1];  // This copies the entire player object
            return true;
        }
        else if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == 'O') ||
                 (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == 'O')) {
            *globalPlayers2[1] = *globalPlayers2[0];  // This copies the entire player object
            return true;
        }

        return false;
    }


    bool is_draw() override{
        return (n_moves == 9 && !is_win());
    }

    bool game_is_over() override{
        return is_win() || is_draw();
    }

};


template <typename T>
class Misere_Player : public Player<T> {
public:
    Misere_Player(string name, T symbol) : Player<T>(name, symbol){}

    void getmove(int& x, int& y){
        cout << this->name << ", enter your move (row [0-2] col [0-2]): ";
        cin >> x >> y;
    }

};


template <typename T>
class Misere_Random_Player : public RandomPlayer<T>{
public:
    Misere_Random_Player(T symbol) : RandomPlayer<T>(symbol){
        this->dimension = 3;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    }

    void getmove(int &x, int &y){
        x = rand() % this->dimension;  // Random number between 0 and 2
        y = rand() % this->dimension;
    }
};



#endif //BOARD_GAMES_MISERE_TIC_TAC_TOE_H
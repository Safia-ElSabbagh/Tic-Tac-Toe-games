#ifndef BOARD_GAMES_TIC_TAC_TOE_H
#define BOARD_GAMES_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
#include <random>
#include <ctime>

Player<char>* globalPlayers_ttt[2];

template <typename T>
class Tic_Tac_Toe_Board  : public Board<char>{
public:

    Tic_Tac_Toe_Board(){
        rows = 5;
        columns = 5;

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
    ~Tic_Tac_Toe_Board() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;

        globalPlayers_ttt[0] = nullptr;
        globalPlayers_ttt[1] = nullptr;

    }



    // update_board implementation
    bool update_board(int x, int y, char symbol) override {

        //Check if move within boundaries
        if(x < 0 || x>= rows || y < 0 || y >= columns) {
            cerr<< "Invalid move!" << endl;
            return false;
        }

        //Check if the cell is empty to allow move
        if(board[x][y] != ' ')
            return false;

        board[x][y] = symbol;   //If valid move place the player symbol in cell
        n_moves++;
        return true;

    }

    //display_board implementation
    void display_board() override{
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                cout<< board[i][j];
                if (j < columns - 1) cout << " | ";
            }
            cout<< endl;
            if (i < rows - 1) cout << "---------------" << endl;
        }
        cout<< endl;

    }

    int playerCount(char symbol){
        int player_count = 0;

        // Horizontal Sequence Counting
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col <= columns - 3; ++col) {
                if (board[row][col] == symbol && board[row][col+1] == symbol && board[row][col+2] == symbol) {
                    player_count++;
                }
            }
        }

        // Vertical Sequence Counting
        for (int col = 0; col < columns; ++col) {
            for (int row = 0; row <= rows - 3; ++row) {
                if (board[row][col] == symbol && board[row+1][col] == symbol && board[row+2][col] == symbol) {
                    player_count++;
                }
            }
        }

        // Diagonal (Top-Left to Bottom-Right) Sequences
        for (int row = 0; row <= rows - 3; ++row) {
            for (int col = 0; col <= columns - 3; ++col) {
                // Check diagonal from top-left to bottom-right
                if (board[row][col] == symbol && board[row+1][col+1] == symbol && board[row+2][col+2] == symbol) {
                    player_count++;
                }
            }
        }

        // Diagonal (Top-Right to Bottom-Left) Sequences
        for (int row = 0; row <= rows - 3; ++row) {
            for (int col = 2; col < columns; ++col) {
                // Check diagonal from top-right to bottom-left
                if (board[row][col] == symbol && board[row+1][col-1] == symbol && board[row+2][col-2] == symbol) {
                    player_count++;
                }
            }
        }

        return player_count;

    }

    //is_win implementation
    bool is_win() override {

        if(n_moves == 24) {
            int count_p1 = playerCount('X');
            int count_p2 = playerCount('O');

            if (count_p1 > count_p2 ) {
                // Access and update player names
                *globalPlayers_ttt[1] = *globalPlayers_ttt[0];  // This copies the entire player object
                return true;
            }
            else if(count_p1 < count_p2){
                return true;
            }

        }

        return false;
    }


    bool is_draw() override{
        return (n_moves == 24 && !is_win());
    }

    bool game_is_over() override{
        return is_win() || is_draw();

    }

};



template <typename T>
class TTT_Player : public Player<T> {
public:
    // Constructor using parent class constructors
    TTT_Player(string name, T symbol) : Player<T>(name, symbol) {}

    // Implement getmove method to get user input
    void getmove(int& x, int& y) override {
        cout << this->name << ", enter your move (row [0-4] col [0-4]): ";
        cin >> x >> y;

    }

};

// Random Computer Player Template
template <typename T>
class RandomComputerPlayer : public RandomPlayer<T> {
public:
    // Constructor
    RandomComputerPlayer(T symbol) : RandomPlayer<T>(symbol) {
        this->dimension = 5;
        this->name = "Random Computer Player";
        srand(static_cast<unsigned int>(time(0)));   // Seed the random number generator
    }

    // Generate random move
    void getmove(int& x, int& y) override {
        x = rand() % this->dimension;
        y = rand() % this->dimension;
    }

};


#endif //BOARD_GAMES_TIC_TAC_TOE_H

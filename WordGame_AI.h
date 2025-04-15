#ifndef BOARD_GAMES_WORDGAME_AI_H
#define BOARD_GAMES_WORDGAME_AI_H

#include "BoardGame_Classes.h"
#include "Word_TicTacTtoe.h"
#include <limits>
#include <algorithm>
#include <fstream>
#include <unordered_set>
#include <string>

using namespace std;

template <typename T>
class Word_MinMax_Player : public Player<T> {
public:
    Word_MinMax_Player(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    std::pair<int, int> getBestMove();
    char selectCharacter(int x, int y, T symbol);
    unordered_set<string> loadDictionary();

    unordered_set<string> dictionary; // Store valid words from the dictionary
};

//--------------------------------------- IMPLEMENTATION

// Constructor for the templated class
template <typename T>
Word_MinMax_Player<T>::Word_MinMax_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Word Player";
    dictionary = loadDictionary(); // Load the dictionary
}

// Load dictionary words into a set
template <typename T>
unordered_set<string> Word_MinMax_Player<T>::loadDictionary() {
    unordered_set<string> dataSet;
    ifstream inputFile("dic.txt");

    if (!inputFile) {
        cerr << "Error opening dictionary file!" << endl;
        return dataSet;
    }

    string line;
    while (getline(inputFile, line)) {
        if (!line.empty()) {
            dataSet.insert(line);
        }
    }
    inputFile.close();
    return dataSet;
}

// Method to get the best move for the player
template <typename T>
void Word_MinMax_Player<T>::getmove(int& x, int& y) {
    std::pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
    this->symbol = selectCharacter(x, y, this->symbol); // Choose a valid character
}

// Minimax algorithm to evaluate the board
template <typename T>
int Word_MinMax_Player<T>::calculateMinMax(T s, bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    } else if (this->boardPtr->is_draw()) {
        return 0;
    }

    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    T nextSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (char c = 'A'; c <= 'Z'; ++c) { // Test all characters
                if (this->boardPtr->update_board(i, j, c)) {
                    int value = calculateMinMax(nextSymbol, !isMaximizing);
                    this->boardPtr->update_board(i, j, 0); // Undo move

                    if (isMaximizing) {
                        bestValue = std::max(bestValue, value);
                    } else {
                        bestValue = std::min(bestValue, value);
                    }
                }
            }
        }
    }

    return bestValue;
}

// Select a character for the given move without directly accessing board
template <typename T>
char Word_MinMax_Player<T>::selectCharacter(int x, int y, T symbol) {
    // Temporary variables to hold row/column/diagonal content
    string row, column, diagonal1, diagonal2;

    // Use update_board to simulate and analyze the board
    for (int i = 0; i < 3; ++i) {
        // Simulate updates to build rows and columns
        this->boardPtr->update_board(x, i, 0);  // Try to clear for row
        row += this->symbol;  // Replace with current symbol
        this->boardPtr->update_board(i, y, 0);  // Try to clear for column
        column += this->symbol;  // Replace with current symbol
    }

    for (int i = 0; i < 3; ++i) {
        this->boardPtr->update_board(i, i, 0);  // Main diagonal
        diagonal1 += this->symbol;
        this->boardPtr->update_board(i, 2 - i, 0);  // Anti-diagonal
        diagonal2 += this->symbol;
    }

    // Test each character
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (dictionary.count(row + c) || dictionary.count(column + c) ||
            dictionary.count(diagonal1 + c) || dictionary.count(diagonal2 + c)) {
            return c;
        }
    }

    return 'A'; // Default to 'A' if no valid word is found
}

// Find the best move using the minimax algorithm
template <typename T>
std::pair<int, int> Word_MinMax_Player<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};

    // Iterate over all board positions
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (char c = 'A'; c <= 'Z'; ++c) { // Test all characters
                if (this->boardPtr->update_board(i, j, c)) {
                    int moveValue = calculateMinMax(this->symbol, false);
                    this->boardPtr->update_board(i, j, 0); // Undo move

                    if (moveValue > bestValue) {
                        bestMove = {i, j};
                        bestValue = moveValue;
                    }
                }
            }
        }
    }

    return bestMove;
}

#endif //BOARD_GAMES_WORDGAME_AI_H

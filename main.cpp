#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Pyramid_TicTacToe.h"
#include "FourInRow.h"
#include "NumericalTicTacToe.h"
#include "BoardGame_Classes.h"
#include "Word_TicTacTtoe.h"
#include "4x4TicTacToe.h"
#include "Misere_Tic_Tac_Toe.h"
#include "Ultimate_TTT.h"
#include "Tic_Tac_Toe_Board.h"
#include "SUS.h"

using namespace std;

// Define a generic structure to hold the board and players
template <typename T>
struct GameSetup {
    Board<T>* board;
    Player<T>* players[2];
};

template <typename T>
GameSetup<T> choosePlayer(Board<T>* board, T symbol1, T symbol2, int gameType) {
    // Choose Player 1 type
    cout << "Choose the type of Player 1:\n1. Human Player\n2. Random Player\n3. AI Player\n";
    int player1Type;
    cin >> player1Type;

    Player<T>* player1;

    if (player1Type == 1) {
        string player1_name;
        cout << "Enter Player 1 name:\n";
        cin >> player1_name;
        /// Player 1 creation
        switch (gameType) {
            case 1:{
                player1 = new Pyramid_player<T>(player1_name, symbol1);
                break;
            }
            case 2:{
                player1 = new Connect_Four_Player<T>(player1_name, symbol1);
                break;
            }
            case 3:{
                player1 = new  TTT_Player<T>(player1_name, symbol1);
                break;
            }
            case 4:{
                player1 = new Word_player<T>(player1_name,symbol1);
                break;
            }
            case 5:{
                player1 = new Numerical_TicTacToe_Player<T>(player1_name, symbol1);
                break;
            }
            case 6:{
                player1 = new Misere_Player<T>(player1_name,symbol1);
                break;
            }
            case 7:{
                player1 = new TicTacToe4x4_Player<T>(player1_name,symbol1);
                break;
            }
            case 8:{
                player1 = new Ultimate_player<T>(player1_name,symbol1);
                break;
            }
            case 9:{
                player1 = new SUS_Player<T>(player1_name,symbol1);
                break;
            }
        }
    } else if (player1Type == 2) {
        switch (gameType) {
            case 1:{
                player1 = new Pyramid_randomPlayer<T>(symbol1);
                break;
            }
            case 2:{
                player1 = new Connect_Four_Random_Player<T>('X');
                break;
            }
            case 3:{
                player1 =  new RandomComputerPlayer<T>('X');
                break;
            }
            case 4:{
                player1 = new Word_randomPlayer(symbol1);
                break;
            }
            case 5:{
                player1 = new Numerical_TicTacToe_Random_Player<T>(symbol1);
                break;
            }
            case 6:{
                player1 = new Misere_Random_Player<T>(symbol1);
                break;
            }
            case 7:{
                player1 = new TicTacToe4x4_Random_Player<T>('X');
                player1Random = true;
                break;
            }
            case 8:{
                p1_israndom = true;
                player1 = new RandomComputerPlayer_Ultimate<T>('X');
                break;
            }
            case 9:{
                player1 = new SUS_Random_Player<T>('S');
            }
        }
    }
    // Choose Player 2 type
    cout << "Choose the type of Player 2:\n1. Human Player\n2. Random Player\n3. AI Player\n";
    int player2Type;
    cin >> player2Type;

    Player<T>* player2;

    if (player2Type == 1) {
        string player2_name;
        cout << "Enter Player 2 name:\n";
        cin >> player2_name;
        /// Player 2 creation
        switch (gameType) {
            case 1:{
                player2 = new Pyramid_player<T>(player2_name, symbol2);
                break;
            }
            case 2:{
                player2 = new Connect_Four_Player<T>(player2_name, symbol2);
                break;
            }
            case 3:{
                player2 = new TTT_Player<T>(player2_name, symbol2);
                break;
            }
            case 4:{
                player2 = new Word_player<T>(player2_name,symbol2);
                break;
            }
            case 5:{
                player2 = new Numerical_TicTacToe_Player<T>(player2_name, symbol2);
                break;
            }
            case 6:{
                player2 = new Misere_Player<T>(player2_name,symbol2);
                break;
            }
            case 7:{
                player2 = new TicTacToe4x4_Player<T>(player2_name,symbol2);
                break;
            }
            case 8:{
                player2 = new Ultimate_player<T>(player2_name,symbol2);
                break;
            }
            case 9:{
                player2 = new SUS_Player<T>(player2_name,symbol2);
                break;
            }
        }
    } else if (player2Type == 2) {
        switch (gameType) {
            case 1:{
                player2 = new Pyramid_randomPlayer<T>(symbol2);
                break;
            }
            case 2:{
                player2 = new Connect_Four_Random_Player<T>('O');
                break;
            }
            case 3:{
                player2 =  new RandomComputerPlayer<T>('O');
                break;
            }
            case 4:{
                player2 = new Word_randomPlayer(symbol2);
                break;
            }
            case 5:{
                player2 = new Numerical_TicTacToe_Random_Player<T>(symbol2);
                break;
            }
            case 6:{
                player2 = new Misere_Random_Player<T>(symbol2);
                break;
            }
            case 7:{
                player2 = new TicTacToe4x4_Random_Player<T>('O');
                player2Random = true;
                break;
            }
            case 8:{
                p2_israndom = true;
                player2 = new RandomComputerPlayer_Ultimate<T>('O');
                break;
            }
            case 9:{
                player2 = new SUS_Random_Player<T>('U');
                break;
            }
        }
    }
    else {
        throw invalid_argument("Invalid player type!");
    }

    return {board, {player1, player2}};
}

template <typename T>
void deletePlayers(GameSetup<T>& setup) {
    for (auto player : setup.players) {
        delete player;
    }
    delete setup.board;
}


int main() {
    srand(static_cast<unsigned>(time(0))); // Seed random number generator
    cout << "__________ Welcome to \"World Of Games!\" __________\n";


    while(true){

        int choice;
        cout << "\nChoose a game:\n1. Pyramid Tic Tac Toe\n2. Connect Four\n3. 5*5 Tic Tac Toe\n4. Word Tic Tac Toe"
                "\n5. Numerical Tic Tac Toe \n6. Misere Tic Tac Toe\n"
                "7. 4*4 Tic Tac Toe\n8. Ultimate Tic Tac Toe\n9. SUS\n0. Exit\n";
        cin >> choice;

        switch (choice) {
            case 0:
                cout << "\nThanks for playing!\n";
                return 0;

            case 1:{
                auto* board = new PyramidTicTacToe<char>();
                GameSetup<char> setup = choosePlayer<char>(board, 'X', 'O', 1);

                GameManager<char> game(setup.board, setup.players);
                game.run();

                deletePlayers(setup);
                cout << "_______________________________________________________";
                break;
            }
            case 2: {
                auto* board = new Connect_Four_Board<char>();
                GameSetup<char> setup = choosePlayer<char>(board, 'X', 'O', 2);

                GameManager<char> game(setup.board, setup.players);
                game.run();

                deletePlayers(setup);
                cout << "_______________________________________________________";
                break;
            }
            case 3:{
                auto* board = new Tic_Tac_Toe_Board<char>();
                GameSetup<char> setup = choosePlayer<char>(board, 'X', 'O', 3);
                GameManager<char> game(setup.board, setup.players);
                globalPlayers_ttt[0] = setup.players[0];
                globalPlayers_ttt[1] = setup.players[1];
                game.run();

                deletePlayers(setup);
                cout << "_______________________________________________________";

                break;
            }
            case 4:{
                auto* board = new WordTicTacToe<char>();
                GameSetup<char> setup = choosePlayer<char>(board, 'X', 'O', 4);

                GameManager<char> game(setup.board, setup.players);
                game.run();

                deletePlayers(setup);
                cout << "_______________________________________________________";
                break;
            }
            case 5: {
                auto* board = new Numerical_TicTacToe_Board<int>();

                GameSetup<int> setup = choosePlayer<int>(board, 1, 2, 5);

                GameManager<int> game(setup.board, setup.players);
                game.run();

                deletePlayers(setup);
                cout << "_______________________________________________________";
                break;
            }
            case 6:{
                auto* board = new Misere_Tic_Tac_Toe<char>();
                GameSetup<char> setup = choosePlayer<char>(board, 'X', 'O', 6);

                GameManager<char> game(setup.board, setup.players);
                globalPlayers2[0] = setup.players[0];

                globalPlayers2[1] = setup.players[1];
                game.run();

                deletePlayers(setup);
                cout << "_______________________________________________________";
                break;
            }
            case 7:{
                auto* board = new TicTacToe4x4_Board<char>();

                GameSetup<char> setup = choosePlayer<char>(board, 'X', 'O', 7);

                GameManager<char> game(setup.board, setup.players);
                game.run();

                deletePlayers(setup);
                cout << "_______________________________________________________";
                break;
            }
            case 8:{
                auto* board = new Ultimate_TTT<char>();

                GameSetup<char> setup = choosePlayer<char>(board, 'X', 'O', 8);

                GameManager<char> game(setup.board, setup.players);
                game.run();

                deletePlayers(setup);
                cout << "_______________________________________________________";
                break;
            }
            case 9:{
              auto* board = new SUS_Board<char>();

                GameSetup<char> setup = choosePlayer<char>(board, 'S', 'U', 9);

                GameManager<char> game(setup.board, setup.players);
                globalPlayers_SUS[0] = setup.players[0];
                globalPlayers_SUS[1] = setup.players[1];
                game.run();

                deletePlayers(setup);
                cout << "_______________________________________________________";

                break;
            }
            default:
                cerr << "Invalid choice! Please select a valid option.\n";
                break;
        }

    }
}
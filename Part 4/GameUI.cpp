//
// GameUI.cpp
//
// The simplest UI implementation
//

#include <iostream>
#include <iomanip>

#include "GameUI.h"
#include "GameData.h"

#define CELL_CLOSED '#'
#define CELL_HOLE   'H'


namespace GameUI {

    void showMessage(const char* msg) {
        std::cout << msg;
    }

    void Welcome() {
        showMessage("Welcome to Proxx game \n");
    }

    // Function: gameMenu
    // 
    // Description: displays game menu and the main thread(menu, play, settings)
    // 
    // Parameters: void
    // 
    // Returns: actions
    //          GameMenu::Play - start new game
    //          GameMenu::Settting - modify game settings
    //          GameMenu::Quit - quit
    //
    //
    GameMenu gameMenu() {
        while (true)
        {
            std::cout << std::endl;
            std::cout << "N: Start new game (board size is "
                << GameSettings::getSettings().get_board_size()
                << ", count of black holes is " << GameSettings::getSettings().get_black_holes()
                << ")\n";
            std::cout << "S: Set game settings\n";
            std::cout << "Q: Quit\n";

            std::cin.clear();
            char choice = 0;
            std::cin >> choice;
            switch (choice) {
            case 'N': case 'n':
                return GameMenu::Play;
            case 'S': case 's':
                return GameMenu::Settting;
            case 'Q': case 'q':
                return GameMenu::Quit;
            default:
                std::cout << "Incorrect choise, try again...\n";
                break;
            }
        }
        return GameMenu::Undefined;
    }

    void getBoardSize(int& sz, int min_val, int max_val) {
        sz = 0;
        std::cout << "Input board size (an integer value in the range[" << min_val << "," << max_val << "]), or a value out of range to cancel:";
        std::cin >> sz;
    }

    void getBlackHoles(int& black_holes, int min_val, int max_val) {
        black_holes = 0;
        std::cout << "Input number of black holes (an integer value in the range[" << min_val << "," << max_val << "]):";
        std::cin >> black_holes;
    }

    // Like a click anywhere, not necessarily on the board
    bool getMoveInTheGame(int& row, int& col) {
        row = col = 0; // clear it
        std::cout << "Enter your move (row column) or zero to cancel:";
        std::cin >> row >> col;
        return (row && col); // > 0
    }


    void ShowGameBoard(const GameBoard* board, bool debug_mode) {
        std::cout << "Game state " << (debug_mode ? "(debug mode)" : "") << ":\n";

        int cnt = debug_mode ? 2 : 1;
        // header
        for (auto i = 0; i < cnt; i++) {
            std::cout << "   ";
            for (auto col = 1; col <= board->board_size(); ++col) {
                std::cout << std::setw(2) << col << " ";
            }
            std::cout << " ";
        }
        std::cout << std::endl;

        for (auto i = 0; i < cnt; i++) {
            std::cout << "    ";
            for (auto col = 1; col <= board->board_size(); ++col) {
                std::cout << "---";
            }
        }
        std::cout << std::endl;


        for (auto row = 0; row < board->board_size(); ++row) {
            for (auto i = 0; i < cnt; i++) {
                std::cout << std::setw(2) << row + 1 << "|";
                for (auto col = 0; col < board->board_size(); ++col) {
                    char cell = CELL_CLOSED;
                    auto nearBy = [](const GameBoard * board, int r, int c) { return '0' + board->black_holes_nearby(r, c); };
                    if (i) { // debug mode, we display all the cells on the debug board
                        cell = board->is_black_hole_cell(row, col) ? CELL_HOLE : ('0' + board->black_holes_nearby(row, col));
                    }
                    else {
                        cell = board->is_opened_cell(row, col)
                             ? (board->is_black_hole_cell(row, col)
                             ? CELL_HOLE : nearBy(board, row, col))
                             : CELL_CLOSED;
                    }

                    std::cout << " " << cell << " ";
                }
                std::cout << "|";
            }
            std::cout << std::endl;
        }

        // footer
        for (auto i = 0; i < cnt; i++) {
            std::cout << "    ";
            for (auto col = 1; col <= board->board_size(); ++col) {
                std::cout << "---";
            }
        }
        std::cout << std::endl;

    }// void ShowGameBoard(const GameBoard* board, bool debug_mode)

}; // namespace GameUI

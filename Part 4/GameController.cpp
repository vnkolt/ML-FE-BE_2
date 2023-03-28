//
// GameController.cpp
//
#include "GameController.h"
#include "GameData.h"
#include "GameUI.h"

#include "Helpers.h"

#include <string>

/*
    Function: DoSettings
    Parameters: void

    Description: modifies game settings

    Returns: void

*/
void DoSettings() {
    int board_size(0),
        black_holes(0);

    GameUI::getBoardSize(board_size, MIN_BOARD_SIZE, MAX_BOARD_SIZE);
    if (board_size < MIN_BOARD_SIZE || board_size > MAX_BOARD_SIZE) { // Invalid value, return without applying new settings
        return;
    }

    GameUI::getBlackHoles(black_holes, MIN_BLACK_HOLES, MAX_BLACK_HOLES(board_size));
    if (black_holes < MIN_BLACK_HOLES || black_holes > MAX_BLACK_HOLES(board_size)) { // Invalid value, return without applying new settings
        return;
    }
    // Applying new settings
    GameSettings::getSettings().set_board_size(board_size);
    GameSettings::getSettings().set_black_holes(black_holes);
}

/*
    Function: DoPlay
    Parameters:
        debug_mode  - allows to display secondary "debug" game board
        filename - file with specified game conditions, e.g.

0 1 0 1 0 0
0 0 0 0 0 0
0 1 1 0 0 0
1 0 0 0 0 0
0 0 0 0 1 0
0 0 0 0 0 1

        where 1 means a black hole cell, 0 means a normal cell

    Description: initializes and starts a new game

    Returns boolean:
        false if specified file does not exist or has invalid content
        Always returns true if filename==nullptr

*/
bool DoPlay(bool debug_mode, const char* filename) {
    GameBoard game_board;
    // Initialize new game
    std::vector<int> black_holes;

    if (filename) { // Get black holes from the specefied file
        unsigned int n(0);
        black_holes = black_holes_from_file(filename, n);
        if (n >= MIN_BOARD_SIZE && black_holes.size())
        {
            GameSettings::getSettings().set_board_size(n);
            GameSettings::getSettings().set_black_holes((int)black_holes.size());
        }
        else {
            return false;
        }
    }
    else {
        // Get random black hole indexes on the board NxN
        black_holes = randoms(GameSettings::getSettings().get_black_holes(), // the number of black holes on the board we need
            0, // the first possible index in the board array where black holes can be placed
            GameSettings::getSettings().get_board_cells() - 1 // the latest possible index in the board array where black holes can be placed
        );
    }

    game_board.setup(GameSettings::getSettings().get_board_size(), black_holes);

    while (true) {
        GameUI::ShowGameBoard(&game_board, debug_mode);

        if (game_board.IsGameover()) {
            GameUI::showMessage(game_board.IsWin() ? "You won!" : "You lost!");
            break;
        }

        int click_row(0), click_col(0);
        if (!GameUI::getMoveInTheGame(click_row, click_col)) {
            GameUI::showMessage("The game has been cancelled...");
            break;
        }
        click_row--; click_col--; // Because we use zero-based indexes, and for a player they start from 1
        if (!game_board.is_valid_cell(click_row, click_col)) { // Is that click outside the board?
            GameUI::showMessage("Invalid move entered, try again, e.g. 1 1\n");
        }
        else if (game_board.is_opened_cell(click_row, click_col)) { // Was that cell already opened?
            GameUI::showMessage("This cell is alredy opened, please select another one...\n");
        }
        else if (game_board.is_black_hole_cell(click_row, click_col)) { // If it is a hole, it's game over
            game_board.open_black_holes();
            game_board.Lost();
        }
        else {
            game_board.do_open(click_row, click_col);
            if (game_board.hidden_cells() == 0) { // If there are no opened cells, the game is over
                game_board.Win();
            }
        }
    }
    return true;
}

/*
    Function: Run
    Parameters:
        debug_mode  - allows to display secondary "debug" game board
        filename - file with specified game conditions, e.g.

    Description: the main thread (menu, play, settings)

    Returns integer:
        0 - success
        1 - failure

*/
int Run(bool debug, const char* filename) {
    GameUI::Welcome();

    if (filename) {
        // Play using settings from file
        if (!DoPlay(debug, filename)) {
            return 1;
        }
    }

    try {
        while (true) {
            switch (GameUI::gameMenu()) {
            case GameUI::GameMenu::Play:
                DoPlay(debug);
                break;
            case GameUI::GameMenu::Settting:
                DoSettings();
                break;
            case GameUI::GameMenu::Quit:
                return 0;
            default:
                break;
            }
        }
    }
    catch (...) {
        GameUI::showMessage("Something wrong...\n");
    }
    return 1;
}
#ifndef GameUI_H
#define GameUI_H

class GameBoard;

namespace GameUI {

    enum class GameMenu {
        Undefined,
        Play,
        Settting,
        Quit
    };

    GameMenu gameMenu();

    void showMessage(const char* msg);
    void Welcome();
    void getBoardSize(int& sz, int min_val, int max_val);
    void getBlackHoles(int& black_holes, int min_val, int max_val);
    bool getMoveInTheGame(int& row, int& col);
    void ShowGameBoard(const GameBoard* board, bool debug_mode);
};

#endif

#ifndef GameData_h
#define GameData_h

#include <cassert>
#include <vector>

#define BOARD_SIZE   8 // Default board size is 8x8
#define BLACK_HOLES 10 // Default black holes count

#define MIN_BOARD_SIZE  5
#define MAX_BOARD_SIZE  16

#define MIN_BLACK_HOLES 1
#define MAX_BLACK_HOLES(board_size) (board_size*board_size - 9)

class GameSettings {
private:
    int bord_size = BOARD_SIZE;		// NxN board
    int black_holes = BLACK_HOLES;
public:
    static GameSettings& getSettings() {
        static GameSettings settings;
        return settings;
    }
    void set_board_size(int size) {
        bord_size = size;
    }
    void set_black_holes(int holes) {
        black_holes = holes;
    }

    int get_board_size() const {
        return bord_size;
    }
    int get_board_cells() const {
        return bord_size * bord_size;
    }
    int get_black_holes() const {
        return black_holes;
    }

};

struct GameCell {
    bool  opened;     // if the cell is opened
    bool  black_hole; // if the cell is a black hole
    int   nearby;     // Counts of # of adjacent black holes
};

class GameBoard {
private:
    int                   n;
    std::vector<GameCell> board;

/*
              NW  N  NE
                \ | /
             W -- H -- E
                / | \
              SW  S  SE
 
*/
//                                  NW        N       NE
        int compass_rose[8][2] = { {-1,-1},{0,-1}, {1, -1},
//                                   W        H       E
                                   {-1, 0},        {1, 0},
//                                  SW        S       SE
                                   {-1, 1},{0, 1}, {1,  1}
                                 };

public:
    GameBoard(int size = BOARD_SIZE) {
        reset(size);
    }

    void reset(int size) {
        n = size;
        board.resize(n * n); // Allocate game board
        for (auto& i : board) {
            i.opened = false;
            i.black_hole = false;
            i.nearby = 0;
        }
    }

    // compute adjacent black holes for specefied cell
    void compute_adjacent_black_holes(int row, int col) {
        board[row * n + col].nearby = 0;
        // Move clockwise from NW to W and check black holes
        for (auto i = 0u; i < sizeof(compass_rose) / sizeof(compass_rose[0]); ++i) {
            if (is_valid_cell(row + compass_rose[i][1], col + compass_rose[i][0]) &&
                is_black_hole_cell(row + compass_rose[i][1], col + compass_rose[i][0])) {
                board[row * n + col].nearby++;
            }
        }
    }

    // compute adjacent black holes for all cells
    void compute_adjacent_black_holes() {
        for (auto row(0); row < board_rows(); row++) {
            for (auto col(0); col < board_cols(); col++) {
                compute_adjacent_black_holes(row, col);
            }
        }
    }

    void set_black_holes(const std::vector<int>& holes) {
        for (auto i : holes) {
            assert(0 <= i && i < n* n);
            board[i].black_hole = true;
        }
    }

    int board_size() const {
        return n;
    }

    int board_rows() const {
        return board_size();
    }

    int board_cols() const {
        return board_size();
    }

    int board_cells() const {
        return n * n;
    }

    bool is_valid_cell(int row, int col) const {
        return (row >= 0 && col >= 0 && row < n&& col < n);
    }

    bool is_opened_cell(int row, int col) const {
        assert(is_valid_cell(row, col));
        return board[row * n + col].opened;
    }

    bool is_black_hole_cell(int row, int col) const {
        assert(is_valid_cell(row, col));
        return board[row * n + col].black_hole;
    }

    int black_holes_nearby(int row, int col) const {
        assert(is_valid_cell(row, col));
        return board[row * n + col].nearby;
    }
};


#endif

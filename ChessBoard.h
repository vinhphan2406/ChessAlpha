#include <cmath>

#ifndef _POSITION_STRUCT
#define _POSITION_STRUCT
struct Position {
    int col; 
    int row;
    Position();
    Position(int _col, int _row);
    bool operator== (const Position& pos);
    void operator= (const Position& pos);
};
#endif

class ChessBoard {
    private:
        bool** chessBoard;
        
        int numOfCol;
        int numOfRow;
        int numOfSquares;
    public:
        ChessBoard(int _numOfCol, int _numOfRow);
        virtual ~ChessBoard();
        // De-select or re-select a square on the board 
        bool bannedSquares(const Position& pos, bool option);
        // De-select or re-select an area of squares on the board
        bool bannedSquares(const Position& topLeftSquare, const Position& bottomRightSquare, bool option);
        // 
};
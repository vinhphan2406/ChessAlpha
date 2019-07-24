#include "ChessBoard.h"

// 

// Initialize the base board
ChessBoard::ChessBoard(int _numOfCol, int _numOfRow){
    this->numOfCol = _numOfCol;
    this->numOfRow = _numOfRow;
    this->numOfSquares = _numOfCol * _numOfRow;
    // Allocate memory for the board
    this->chessBoard = new bool*[_numOfRow];
    for (int i = 0; i < _numOfRow; i++){
        this->chessBoard[i] = new bool[_numOfCol];
        for (int j = 0; j < _numOfCol; j++){
            this->chessBoard[i][j] = true;
        }
    }
}
// De-select or re-select a square on the board
bool ChessBoard::bannedSquares(const Position& pos, bool option){
    if (this->chessBoard[pos.col][pos.row] == option){
        this->chessBoard[pos.col][pos.row] = !option;
        if (option){
            this->numOfSquares++;
        }
        else {
            this->numOfSquares--;
        }
        return true;
    }
    return false;
}

// De-select or re-select an area of squares on the board
bool ChessBoard::bannedSquares(const Position& topLeftSquare, const Position& bottomRightSquare, bool option){
    if (topLeftSquare.row > bottomRightSquare.row && topLeftSquare.col < bottomRightSquare.col){
        int _numOfCol = abs(topLeftSquare.col - bottomRightSquare.col) + 1;
        int _numOfRow = abs(topLeftSquare.row - bottomRightSquare.row) + 1;
        for (int i = 0; i < numOfCol; i++){
            for (int j = 0; j < numOfRow; j++){
                if (this->chessBoard[topLeftSquare.col + i][bottomRightSquare.row + j] == option){
                    this->chessBoard[topLeftSquare.col + i][bottomRightSquare.row + j] = !option;
                }
                if (option){
                    this->numOfSquares++;
                }
                else {
                    this->numOfSquares--;
                }
            }
        }
        return true;
    }
    return false;
}
// Deallocate memory of the board
ChessBoard::~ChessBoard(){
    for (int i = 0; i < this->numOfRow; i++){
        delete[] this->chessBoard[i];
    }
    delete[] this->chessBoard;
}
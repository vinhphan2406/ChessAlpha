#include "Chess.h"

// Temporary constant for chess board dimension
#define BOARD_SIZE 8
#define NUM_OF_PIECES 32

void GameManager::Initialization(){
}

void GameManager::Finalization(){
}

void GameManager::setupBoard(){
    this->chessBoard = new ChessBoard(BOARD_SIZE, BOARD_SIZE);
}

void GameManager::setupPieces(){
    this->piecesManager = ChessPiecesManager();
}

void GameManager::processRequest(std::string pos, sideColor _side, std::string req){
    ChessPieces obj = this->PGNParser(pos, _side);
    for (int i = 0; i < this->piecesManager.getNumOfPieces(); i++){
        if (*(this->piecesManager.getChessPiece(i)) == obj){
            // 
        }
    }
}

ChessPieces GameManager::PGNParser(std::string _pgn, sideColor _side){
    ChessPieces obj;
    // Set side of chess piece
    obj.setSideOfChessPiece(_side);
    int counter = 0;
    // Set type of piece
    if (isalpha(_pgn[counter])){
        if (_pgn[counter] == 'K'){
            obj.setTypeOfChessPiece(king);
        }
        else if (_pgn[counter] == 'Q') {
            obj.setTypeOfChessPiece(queen);
        }
        else if (_pgn[counter] == 'R') {
            obj.setTypeOfChessPiece(rook);
        }
        else if (_pgn[counter] == 'B') {
            obj.setTypeOfChessPiece(bishop);
        }
        else if (_pgn[counter] == 'N') {
            obj.setTypeOfChessPiece(knight);
        }
        counter++;
    }
    else {
        obj.setTypeOfChessPiece(pawn);
    }
    // Set position of chess piece
    std::string _pos = _pgn.substr(counter);
    
    int col = (int)_pos[0] - 'a';
    int row = (int)_pos[1] - '0';
    Position pos(col, row);
    obj.setPositionOfChessPiece(pos);
    return obj;
}

bool GameManager::makeMove(ChessPieces& _obj, int option){
    std::vector<Position> listOfPossibleMoves = _obj.possibleMoves;
    for (int i = 0; i < ){
        
    }
}

GameManager::~GameManager(){
    delete[] this->chessBoard;
}




#include "ChessPieces.h"

Position::Position(){

}

Position::Position (int _col, int _row){
    this->col = _col;
    this->row = _row;
};

bool Position::operator==(const Position& pos){
    if (this->col == pos.col && this->row == pos.row){
        return true;
    }
    return false;
}

void Position::operator=(const Position& pos){
    this->col = pos.col;
    this->row = pos.row;
}

ChessPieces::ChessPieces(){
    this->side = white;
}

ChessPieces::ChessPieces(const Position& _startingPos, sideColor _side, pieceType _typeOfPiece){
    this->currentPos = _startingPos;
    this->side = _side;
    this->typeOfPiece = _typeOfPiece;
}
// Copy constructor
ChessPieces::ChessPieces(const ChessPieces& _obj){
    this->currentPos = _obj.currentPos;
    this->side = _obj.side;
    this->typeOfPiece = _obj.typeOfPiece;
}
// Deep copy
void ChessPieces::operator=(const ChessPieces& _obj){
    this->currentPos = _obj.currentPos;
    this->side = _obj.side;
    this->typeOfPiece = _obj.typeOfPiece;
}
// Operator ==
bool ChessPieces::operator==(const ChessPieces& _obj){
    if (this->currentPos == _obj.currentPos &&
    this->typeOfPiece == _obj.typeOfPiece &&
    this->side == _obj.side){
        return true;
    }
    return false;
}
// Setting position of each chess piece
void ChessPieces::setPositionOfChessPiece(const Position& _pos){
    this->currentPos = _pos;
}
// Getting position of each chess piece
Position ChessPieces::getPositionOfChessPiece() const {
    return this->currentPos;
}
// Setting position of each chess piece 
void ChessPieces::setPositionOfChessPiece(int _row, int _col){
    this->currentPos.row = _row;
    this->currentPos.col = _col;
}
// Setting side of each chess piece
void ChessPieces::setSideOfChessPiece(sideColor _side){
    this->side = _side;
}

int ChessPieces::getSideOfChessPiece() const {
    return this->side;
}

void ChessPieces::setTypeOfChessPiece(pieceType _typeOfPiece){
    this->typeOfPiece = _typeOfPiece;
}

int ChessPieces::getTypeOfChessPiece() const {
    return this->typeOfPiece;
}


bool ChessPieces::checkLegalPosition(const Position& _originalPos){
    if (_originalPos.col >= 0 && _originalPos.col < numOfCol && _originalPos.row >= 0 && _originalPos.row < numOfRow) return true;
    return false;
}

Position ChessPieces::fromOriginalPos(const Position& _originalPos, int _right, int _up){
    Position result = _originalPos;
    // Move from original position x squares to the right and y squares to the top
    result.row += _right;
    result.col += _up;
    return result;
}

Position ChessPieces::turn90Degrees(const Position& _originalPos, const Position& _fixedSquare, bool isRight){
    Position resultPos;
    int coef;
    if (isRight){
        coef = 1;
    }
    else {
        coef = -1;
    }
    // Turn 90 degrees to the right (or left)
    resultPos.row = coef * -(_originalPos.col - _fixedSquare.col) + _fixedSquare.row;
    resultPos.col = coef * (_originalPos.row - _fixedSquare.row) + _fixedSquare.col;
    return resultPos;
}

Position ChessPieces::mirrorSquare(const Position& _originalPos, const Position& _fixedSquare, bool colAxis){
    Position resultPos;
    if (colAxis){
        // Reflection through the vertical axis
        resultPos.row = 2 * _originalPos.row - _fixedSquare.row;
    }
    else {
        // Reflection through the horizontal axis
        resultPos.col = 2 * _originalPos.col - _fixedSquare.col;
    }
    return resultPos;
}

std::vector<Position> ChessPieces::possibleMoves(bool** &chessBoard, int numOfRow, int numOfCol){
    std::vector<Position> legalMoves;
    int reverse;
    if (this->side == white){
        reverse = 1;
    }
    else {
        reverse = -1;
    }
    Position solPos = this->currentPos;
    switch(this->typeOfPiece){
        case pawn:
            // White Pawn: nextPos is 1 square in front of currentPos
            // or Black Pawn: nextPos is 1 square behind currentPos
            
            solPos.col += 1 * reverse;
            if (chessBoard[solPos.col][solPos.row] && 
            checkLegalPosition(solPos, numOfRow, numOfCol)){
                legalMoves.push_back(solPos);
            }

            // Move diagonally right if there's a piece
            solPos = this->currentPos;
            solPos.col += 1 * reverse;
            solPos.row += 1 * reverse;
            if (!chessBoard[solPos.col][solPos.row] && 
            checkLegalPosition(solPos, numOfRow, numOfCol)){
                legalMoves.push_back(solPos);
            }

            // Move diagonally left if there's a piece
            solPos = this->currentPos;
            solPos.col += 1 * reverse;
            solPos.row -= 1 * reverse;
            if (!chessBoard[solPos.col][solPos.row] && 
            checkLegalPosition(solPos, numOfRow, numOfCol)){
                legalMoves.push_back(solPos);
            }
            break;
        case knight:
            solPos.col += 1;
            solPos.row += 2;
            for (int i = 0; i < 4; i++){
                if (checkLegalPosition(solPos, numOfRow, numOfCol)){
                    legalMoves.push_back(solPos);
                }
                // Reflective symmetry with respect to the vertical axis (y-axis: '|')
                if (checkLegalPosition(mirrorSquare(solPos, this->currentPos, true), numOfRow, numOfCol)){
                    legalMoves.push_back(mirrorSquare(solPos, this->currentPos, true));
                }
                // Rotate 90 degrees
                solPos = turn90Degrees(solPos, this->currentPos, true);
            }
            break;
        case bishop:
            for (int i = 0; i < 4; i++){
                for (int j = 1; checkLegalPosition(solPos, numOfRow, numOfCol); j++){
                    solPos = this->currentPos;
                    // 1 sqaure up in the diagonal line
                    solPos.col += j;
                    solPos.row += j;
                    // Number of rotations 
                    for (int k = 0; k < i; k++){
                        solPos = turn90Degrees(solPos, this->currentPos, true);
                    }
                    // Push back to the vector of possible moves
                    legalMoves.push_back(mirrorSquare(solPos, this->currentPos, true));
                    // Escape loop behind pushing back in vector to also include 
                    if (!chessBoard[solPos.col][solPos.row]){
                        break;
                    }
                    // Escape loop after finding a position which contains another piece
                    if (){

                    }
                }
            }
            break;
        case rook:
            for (int i = 0; i < 4; i++){
                for (int j = 1; checkLegalPosition(solPos, numOfRow, numOfCol); j++){
                    solPos = this->currentPos;
                    // 1 sqaure up in the vertical line
                    solPos.col += j;
                    // Number of rotations 
                    for (int k = 0; k < i; k++){
                        solPos = turn90Degrees(solPos, this->currentPos, true);
                    }
                    // Push back to the vector of possible moves
                    legalMoves.push_back(mirrorSquare(solPos, this->currentPos, true));
                    // Escape loop behind pushing back in vector to also include 
                    if (!chessBoard[solPos.col][solPos.row]){
                        break;
                    }
                }
            }
            break;
        case queen:
            // Bishop-like movement
            for (int i = 0; i < 4; i++){
                for (int j = 1; checkLegalPosition(solPos, numOfRow, numOfCol); j++){
                    solPos = this->currentPos;
                    // 1 sqaure up in the diagonal line
                    solPos.col += j;
                    solPos.row += j;
                    // Number of rotations 
                    for (int k = 0; k < i; k++){
                        solPos = turn90Degrees(solPos, this->currentPos, true);
                    }
                    // Push back to the vector of possible moves
                    legalMoves.push_back(mirrorSquare(solPos, this->currentPos, true));
                    // Escape loop behind pushing back in vector to also include 
                    if (!chessBoard[solPos.col][solPos.row]){
                        break;
                    }
                }
            }
            // Rook-like movement
            for (int i = 0; i < 4; i++){
                for (int j = 1; checkLegalPosition(solPos, numOfRow, numOfCol); j++){
                    solPos = this->currentPos;
                    // 1 sqaure up in the vertical line
                    solPos.col += j;
                    // Number of rotations 
                    for (int k = 0; k < i; k++){
                        solPos = turn90Degrees(solPos, this->currentPos, true);
                    }
                    // Push back to the vector of possible moves
                    legalMoves.push_back(mirrorSquare(solPos, this->currentPos, true));
                    // Escape loop behind pushing back in vector to also include 
                    if (!chessBoard[solPos.col][solPos.row]){
                        break;
                    }
                }
            }
            break;
        case king:
            for (int i = 0; i < 4; i++){
                solPos = this->currentPos;
                // Go up 1 square
                solPos.col += 1;
                for (int j = 0; j < i; j++){
                    if (checkLegalPosition(solPos, numOfRow, numOfCol)){
                        solPos = turn90Degrees(solPos, this->currentPos, true);
                    }
                }
                solPos = this->currentPos;
                // Move right 1 square after go up 1 square
                solPos.col += 1;
                solPos.row += 1;
                for (int j = 0; j < i; j++){
                    if (checkLegalPosition(solPos, numOfRow, numOfCol)){
                        solPos = turn90Degrees(solPos, this->currentPos, true);
                    }
                }
            }
            break;
    }
}

ChessPiecesManager::ChessPiecesManager(){
    this->currentNumOfPieces = 0;
};

int ChessPiecesManager::getNumOfPieces() const{
    return this->currentNumOfPieces;
}
// Construct a new instance of ChessPieces from other ChessPieces
void ChessPiecesManager::allocate(const ChessPieces& _obj){
    ChessPieces* newPiece = new ChessPieces;
    *newPiece = _obj;
    this->chessPieces.push_back(newPiece);
    this->currentNumOfPieces++;
}
// Allocate new memory to the ChessPieces vector from position, side and type of piece
void ChessPiecesManager::allocate(const Position& _startingPos, sideColor _side,  pieceType _type){
    ChessPieces* newPiece = new ChessPieces;
    newPiece->setPositionOfChessPiece(_startingPos);
    newPiece->setSideOfChessPiece(_side);
    newPiece->setTypeOfChessPiece(_type);
    this->chessPieces.push_back(newPiece);
    this->currentNumOfPieces++;
}
// Destroy an instance of ChessPieces
void ChessPiecesManager::deallocate(const ChessPieces& _obj){ 
    for (int i = 0; i < currentNumOfPieces; i++){
        if (*(this->chessPieces[i]) == _obj){
            delete[] this->chessPieces[i];
            this->chessPieces.erase(chessPieces.begin() + i);
            this->currentNumOfPieces--;
            return;
        }
    }
    
}
// Deallocate memory to the ChessPieces vector from position, side and type of piece
void ChessPiecesManager::deallocate(const Position& _startingPos){
    ChessPieces newPiece;
    newPiece.setPositionOfChessPiece(_startingPos);
    for (int i = 0; i < currentNumOfPieces; i++){
        if (this->chessPieces[i]->getPositionOfChessPiece() == _startingPos){
            delete[] this->chessPieces[i];
            this->chessPieces.erase(chessPieces.begin() + i);
            this->currentNumOfPieces--;
            return;
        }
    }
    
}

ChessPieces* ChessPiecesManager::getChessPiece(int _index) const {
    return chessPieces[_index];
}

bool ChessPiecesManager::isOccupied(const Position& _pos){
    for (int i = 0; i < this->getNumOfPieces(); i++){
        if (this->chessPieces[i]->getPositionOfChessPiece() == _pos; i++){
            return true;
        }
    }
    return false;
}

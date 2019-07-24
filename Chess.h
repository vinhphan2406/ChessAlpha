#include "ChessBoard.h"
#include "ChessPieces.h"

#include <string>
#include <cctype>

class GameManager {
    private:
        bool whiteTurn = true;
        static int numOfTurns;
        ChessBoard* chessBoard;
        ChessPiecesManager piecesManager;
    public:
        GameManager();
        ~GameManager();
        // Intialize any needed dynamic memory
        void Initialization();
        // Finalize any memory allocated
        void Finalization();
        // Set up the board and chess pieces
        void setupBoard();
        void setupPieces();
        // 
        ChessPieces PGNParser(std::string _pgn, sideColor _side);
        bool makeMove(ChessPieces& _obj, int option);
        void processRequest(std::string req, sideColor _side, std::string move);
        //
        void displayChessBoard();
        void displayMoveOptions(ChessPieces& _obj);
        void display();
};
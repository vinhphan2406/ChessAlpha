
#include <vector>

#ifndef _SIDE_TYPE
#define _SIDE_TYPE
enum sideColor {
    white,
    black,
    all_colors
};

enum pieceType {
    pawn,
    knight,
    bishop,
    rook,
    queen,
    king,
    all_types
};
#endif

#ifndef _POSITION_STRUCT
#define _POSITION_STRUCT
struct Position {
    int col; 
    int row;
    Position();
    Position(int _col, int _row);
    bool operator==(const Position& pos);
    void operator=(const Position& pos);
};
#endif

class ChessPieces {
    private:
        ChessPiecesManager* id;
        Position currentPos;
        sideColor side;
        pieceType typeOfPiece;
    public:
        ChessPieces();
        ChessPieces(const Position& _startingPos, sideColor _side, pieceType _typeOfPiece);
        // ~ChessPieces();
        // Copy constructor
        ChessPieces(const ChessPieces& _obj);
        void Initialization();
        void Finalization();
        // Copy an instance of a class
        void operator=(const ChessPieces& _obj);
        // Operator == 
        bool operator==(const ChessPieces& _obj);
        // Set the specification of each piece
        void setPositionOfChessPiece(const Position& _pos);
        void setPositionOfChessPiece(int _row, int _col);
        void setSideOfChessPiece(sideColor _side);
        void setTypeOfChessPiece(pieceType _typeOfPiece);
        // Get the specification of each piece
        Position getPositionOfChessPiece() const;
        int getSideOfChessPiece() const;
        int getTypeOfChessPiece() const;
        // Check if a move is legal
        bool checkLegalPosition(const Position& _originalPos);
        // Utility function 
        Position fromOriginalPos(const Position& _originalPos, int _right, int _up);
        Position turn90Degrees(const Position& _originalPos, const Position& _fixedSquare, bool isRight);
        Position mirrorSquare(const Position& _originalPos, const Position& _fixedSquare, bool colAxis);
        // Make a list of possible moves
        std::vector<Position> possibleMoves(bool** &chessBoard, int numOfRow, int numOfCol);
};


class ChessPiecesManager{
    private:
        int currentNumOfPieces;
        std::vector<ChessPieces*> chessPieces;
    public:
        ChessPiecesManager();
        int getNumOfPieces() const;
        // Construct an new instance of ChessPieces
        void allocate(const ChessPieces& _obj);
        void allocate(const Position& _startingPos,  sideColor _size, pieceType _type);
        // Destroy an instance of ChessPieces
        void deallocate(const ChessPieces& _obj);
        void deallocate(const Position& _startingPos);
        // Access the list of chess pieces on a board
        ChessPieces* getChessPiece(int _index) const;
        // Check if a position is occupied
        bool isOccupied(const Position& _pos);
        friend std::vector<Position> ChessPieces::possibleMoves(bool** &chessBoard, int numOfRow, int numOfCol);
};

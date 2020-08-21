#pragma once

#include "raylib.h"
#include <stdio.h>


#define WKING           0x2654
#define WQUEEN          0x2655
#define WROOK           0x2656
#define WBISHOP         0x2657
#define WKNIGHT         0x2658
#define WPAWN           0x2659
#define BKING           0x265A
#define BQUEEN          0x265B
#define BROOK           0x265C
#define BBISHOP         0x265D
#define BKNIGHT         0x265E
#define BPAWN           0x265F

struct Piece {
    int* piece;
    Vector2 pos;
    Vector2 move;   //  1 pawns, 2 knight, 3 bishop, 4 rook, 5 Queen, 6 king
    Color team;
    bool taken;
    bool selected;
    bool moved;
    bool checked; // for the king only
};
typedef struct Piece Piece;


//Square on the board a 8 by 8 grid (0,0) at top left
struct Square {
    bool black_att;
    bool white_att;
    Piece* piece;
};
typedef struct Square Square;

struct Move{
    Vector2 new_pos;
    Vector2 init_pos;
    Piece* piece;
    char move[4];
};
typedef struct Move Move;

struct MoveNode {
    Move move;
    struct MoveNode* past_move;
    struct MoveNode* next_move;
};
typedef struct MoveNode MoveNode;


void InitBoard(Square board[8][8], Piece piece[32], int font_code[12]);

void DoMove(Square board[8][8], Move next_move);

void AddMove(MoveNode* move_list, Move* move);

Move RemoveMove(MoveNode* move_list);

void Undo(Square board[8][8], MoveNode* move_list);


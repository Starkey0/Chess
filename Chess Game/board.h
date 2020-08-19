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
    Color team;
    bool taken;
    bool selected;
};
typedef struct Piece Piece;

//Board is a 8 by 8 grid (0,0) at top left


void InitBoard(Piece piece[32], int font_code[12]);

Vector2 GetMouseGridPosition();

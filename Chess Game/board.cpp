#include "board.h"

void InitBoard(Piece piece[32], int font_code[12])
{
	//Load codepoint font table
	for (int i = 0; i < 6; ++i)
	{
		font_code[i] = WKING + i;
		font_code[i + 6] = BKING + i;
	}

	//Pawns
	for (int i = 0; i < 8; ++i)
	{
		piece[i].pos = (Vector2) { i, 1 };
		piece[i].piece = &font_code[5];
		piece[i].team = WHITE;

		piece[i+8].pos = (Vector2) { i, 6 };
		piece[i+8].piece = &font_code[11];
		piece[i+8].team = BLACK;
	}

	//Rook, bishop, knight, queen, king, ...

	piece[16].pos = (Vector2){ 0, 0 };
	piece[16].piece = &font_code[2];
	piece[16].team = WHITE;

	piece[17].pos = (Vector2){ 1, 0 };
	piece[17].piece = &font_code[3];
	piece[17].team = WHITE;

	piece[18].pos = (Vector2){ 2, 0 };
	piece[18].piece = &font_code[4];
	piece[18].team = WHITE;

	piece[19].pos = (Vector2){ 3, 0 };
	piece[19].piece = &font_code[1];
	piece[19].team = WHITE;

	piece[20].pos = (Vector2){ 4, 0 };
	piece[20].piece = &font_code[0];
	piece[20].team = WHITE;

	piece[21].pos = (Vector2){ 5, 0 };
	piece[21].piece = &font_code[4];
	piece[21].team = WHITE;

	piece[22].pos = (Vector2){ 6, 0 };
	piece[22].piece = &font_code[3];
	piece[22].team = WHITE;

	piece[23].pos = (Vector2){ 7, 0 };
	piece[23].piece = &font_code[2];
	piece[23].team = WHITE;


	piece[24].pos = (Vector2){ 0, 7 };
	piece[24].piece = &font_code[8];
	piece[24].team = BLACK;

	piece[25].pos = (Vector2){ 1, 7 };
	piece[25].piece = &font_code[9];
	piece[25].team = BLACK;

	piece[26].pos = (Vector2){ 2, 7 };
	piece[26].piece = &font_code[10];
	piece[26].team = BLACK;

	piece[27].pos = (Vector2){ 3, 7 };
	piece[27].piece = &font_code[7];
	piece[27].team = BLACK;

	piece[28].pos = (Vector2){ 4, 7 };
	piece[28].piece = &font_code[6];
	piece[28].team = BLACK;

	piece[29].pos = (Vector2){ 5, 7 };
	piece[29].piece = &font_code[10];
	piece[29].team = BLACK;

	piece[30].pos = (Vector2){ 6, 7 };
	piece[30].piece = &font_code[9];
	piece[30].team = BLACK;

	piece[31].pos = (Vector2){ 7, 7 };
	piece[31].piece = &font_code[8];
	piece[31].team = BLACK;

}

Vector2 GetMouseGridPosition()
{



	return (Vector2) { 0,0 };
}
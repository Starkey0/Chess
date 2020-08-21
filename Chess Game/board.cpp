#include "board.h"

void InitBoard(Square board[8][8], Piece piece[32], int font_code[12])
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

		board[i][1].piece = &piece[i];
		board[i][6].piece = &piece[i+8];
	}

	//Rook, bishop, knight, queen, king, ...

	piece[16].pos = (Vector2){ 0, 0 };
	piece[16].piece = &font_code[2];
	piece[16].team = WHITE;
	board[0][0].piece = &piece[16];

	piece[17].pos = (Vector2){ 1, 0 };
	piece[17].piece = &font_code[3];
	piece[17].team = WHITE;
	board[1][0].piece = &piece[17];

	piece[18].pos = (Vector2){ 2, 0 };
	piece[18].piece = &font_code[4];
	piece[18].team = WHITE;
	board[2][0].piece = &piece[18];

	piece[19].pos = (Vector2){ 3, 0 };
	piece[19].piece = &font_code[1];
	piece[19].team = WHITE;
	board[3][0].piece = &piece[19];

	piece[20].pos = (Vector2){ 4, 0 };
	piece[20].piece = &font_code[0];
	piece[20].team = WHITE;
	board[4][0].piece = &piece[20];

	piece[21].pos = (Vector2){ 5, 0 };
	piece[21].piece = &font_code[4];
	piece[21].team = WHITE;
	board[5][0].piece = &piece[21];

	piece[22].pos = (Vector2){ 6, 0 };
	piece[22].piece = &font_code[3];
	piece[22].team = WHITE;
	board[6][0].piece = &piece[22];

	piece[23].pos = (Vector2){ 7, 0 };
	piece[23].piece = &font_code[2];
	piece[23].team = WHITE;
	board[7][0].piece = &piece[23];


	piece[24].pos = (Vector2){ 0, 7 };
	piece[24].piece = &font_code[8];
	piece[24].team = BLACK;
	board[0][7].piece = &piece[24];

	piece[25].pos = (Vector2){ 1, 7 };
	piece[25].piece = &font_code[9];
	piece[25].team = BLACK;
	board[1][7].piece = &piece[25];

	piece[26].pos = (Vector2){ 2, 7 };
	piece[26].piece = &font_code[10];
	piece[26].team = BLACK;
	board[2][7].piece = &piece[26];

	piece[27].pos = (Vector2){ 3, 7 };
	piece[27].piece = &font_code[7];
	piece[27].team = BLACK;
	board[3][7].piece = &piece[27];

	piece[28].pos = (Vector2){ 4, 7 };
	piece[28].piece = &font_code[6];
	piece[28].team = BLACK;
	board[4][7].piece = &piece[28];

	piece[29].pos = (Vector2){ 5, 7 };
	piece[29].piece = &font_code[10];
	piece[29].team = BLACK;
	board[5][7].piece = &piece[29];

	piece[30].pos = (Vector2){ 6, 7 };
	piece[30].piece = &font_code[9];
	piece[30].team = BLACK;
	board[6][7].piece = &piece[30];

	piece[31].pos = (Vector2){ 7, 7 };
	piece[31].piece = &font_code[8];
	piece[31].team = BLACK;
	board[7][7].piece = &piece[31];
}

void AddMove(MoveNode* move_list, Move* move)
{
	MoveNode* new_move = move_list;

	while (new_move->next_move)
	{
		new_move = new_move->next_move;
	}

	new_move->next_move = (MoveNode*) calloc(1, sizeof(MoveNode));
	new_move->next_move->past_move = new_move;
	new_move->next_move->move= *move;
	new_move->next_move->next_move = NULL;
}

Move RemoveMove(MoveNode* move_list)
{
	MoveNode* last_move = move_list;
	Move move = {0};

	if (last_move->next_move == NULL) return move;

	while (last_move->next_move)
	{
		last_move = last_move->next_move;
	}

	move = last_move->move;
	last_move->past_move->next_move = NULL;
	free(last_move);
	return move;
}

void Undo(Square board[8][8], MoveNode* move_list)
{
	Move move = RemoveMove(move_list);

	if (move.piece != NULL)
	{
		Vector2 pos = move.new_pos;
		move.new_pos = move.init_pos;
		move.init_pos = pos;

		DoMove(board, move);
	}
	

}

void DoMove(Square board[8][8], Move next_move)
{
	int mouse_x = next_move.new_pos.x;
	int mouse_y = next_move.new_pos.y;

	int x = next_move.piece->pos.x;
	int y = next_move.piece->pos.y;

	board[mouse_x][mouse_y].piece = next_move.piece;
	board[mouse_x][mouse_y].piece->pos.x = mouse_x;
	board[mouse_x][mouse_y].piece->pos.y = mouse_y;

	board[x][y].piece = NULL;
}
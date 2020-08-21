

/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples in Notepad++, provided with default raylib installer package,
*   just press F6 and run [raylib_compile_execute] script, it will compile and execute.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on [C:\raylib\raylib\examples] directory and
*   raylib official webpage: [www.raylib.com]
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2020 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <assert.h>
#include "board.h"

#define SCREENWIDTH     1000
#define SCREENHEIGHT    1000
#define GRIDWIDTH       100
#define GRIDHEIGHT      100
#define CHECKEDWIDTH    800
#define CHECKEDHEIGHT   800


int GetMouseGridPositionX()
{    
    int mouse_x = GetMouseX();
    if (mouse_x > SCREENWIDTH / 2 - CHECKEDWIDTH / 2 &&
        mouse_x < SCREENWIDTH / 2 - CHECKEDWIDTH / 2 + CHECKEDWIDTH)
        return (int)(mouse_x - (SCREENWIDTH / 2 - CHECKEDWIDTH / 2)) / GRIDWIDTH;
    return -1;
}

int GetMouseGridPositionY()
{
    int mouse_y = GetMouseY();

    if (mouse_y > SCREENHEIGHT / 2 - CHECKEDHEIGHT / 2 &&
        mouse_y < SCREENHEIGHT / 2 - CHECKEDHEIGHT / 2 + CHECKEDHEIGHT)
        return (int)(mouse_y - (SCREENHEIGHT / 2 - CHECKEDHEIGHT / 2)) / GRIDHEIGHT;
    return -1;
}

void DrawBoard(Piece pieces[32], Font *fontEmoji, Texture2D *checked, Piece *selected)
{
    Vector2 pos_init = { SCREENWIDTH / 2 - checked->width / 2,
                         SCREENHEIGHT / 2 - checked->height / 2};
    Vector2 pos_x = { GRIDWIDTH,0 };
    Vector2 pos_y = { 0, GRIDHEIGHT };
    Vector2 pos;

    char c_mouse_pos[12];
    char c_select_pos[12];

    //Board
    DrawTexture(*checked, SCREENWIDTH / 2 - checked->width / 2,
                          SCREENHEIGHT / 2 - checked->height / 2, 
                          Fade(WHITE, 0.5f));

    //Left text
    for (int i = 1; i <= 8; ++i)
    {
        char n[2];
        n[0] = (char)('0' + i);
        n[1] = '\0';
        DrawText(n, pos_init.x - GRIDWIDTH / 3 + 6, i * GRIDHEIGHT + 4, 20.0, BLACK);
    }

    //Bottom text
    for (int i = 1; i <= 8; ++i)
    {
        char n[2];
        n[0] = (char)('@' + i);
        n[1] = '\0';
        DrawText(n, i * GRIDWIDTH + 6, pos_init.y + GRIDHEIGHT * 8 + 4, 20.0, BLACK);
    }

    //Board Pieces
    for (int i = 0; i < 32; ++i)
    {
        pos = (Vector2){ pos_init.x + pieces[i].pos.x * pos_x.x + pos_x.x / 2 / 3 ,
                         pos_init.y + pieces[i].pos.y * pos_y.y + pos_y.y / 2 / 3 };
        DrawTextCodepoint(*fontEmoji, *pieces[i].piece, pos, 1.0, pieces[i].team);
    }

    sprintf_s(c_mouse_pos,12, "%d , %d", GetMouseGridPositionX(), GetMouseGridPositionY());
    
    if (selected != NULL)
        sprintf_s(c_select_pos,12, "%d , %d", (int) selected->pos.x, 
                                                   (int) selected->pos.y
                                                   );
    
    DrawText(c_mouse_pos, 0, 0, 20.0, BLACK);
    DrawText(c_select_pos, CHECKEDWIDTH, 0, 20.0, BLACK);
}

void GetInput(Square board[8][8],Piece **selected, Move* move, MoveNode* move_list)
{
    move->new_pos = (Vector2){ 0,0 };
    move->piece = NULL;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        int mouse_x = GetMouseGridPositionX();
        int mouse_y = GetMouseGridPositionY();

        if (*selected == NULL)
        {
            if (mouse_x != -1 && mouse_y != -1)
            {
                *selected = board[mouse_x][mouse_y].piece;
            }
            else
            {
                *selected = NULL;
            }
            return;
        }

        if (*selected != NULL)
        {
            if (mouse_x != -1 && mouse_y != -1)
            {
                if (board[mouse_x][mouse_y].piece == NULL)
                {

                    move->new_pos.x = mouse_x;
                    move->new_pos.y = mouse_y;
                    move->piece = *selected;
                    move->init_pos = (*selected)->pos;
                }
                    
            }
            *selected = NULL;
            return;
        }
        
    }   

    if (IsKeyPressed(KEY_Z)) Undo(board,move_list);


}


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = SCREENWIDTH;
    const int screenHeight = SCREENHEIGHT;

    // Generate a checked texture by code
    int width = CHECKEDWIDTH;
    int height = CHECKEDHEIGHT;

    Square board[8][8] = { 0 };
    Piece pieces[32] = { 0 };
    int font_code[12];
    Piece *selected = NULL;
    Move next_move = {0};
    MoveNode *move_list, *undo_buffer;

    move_list = (MoveNode*)calloc(1, sizeof(MoveNode));
    undo_buffer = (MoveNode*)calloc(1, sizeof(MoveNode));

    InitBoard(board, pieces, font_code);
    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Chess");

    Font fontEmoji = LoadFontEx("resources/Symbola.ttf", GRIDWIDTH*2/3, font_code, 12);

    // Dynamic memory allocation to store pixels data (Color type)
    Color* pixels = (Color*)calloc(width * height, sizeof(Color));

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (((x / GRIDWIDTH + y / GRIDHEIGHT) / 1) % 2 == 0) pixels[y * width + x] = BROWN;
            else pixels[y * width + x] = BEIGE;
        }
    }

    // Load pixels data into an image structure and create texture
    Image checkedIm = {
        .data = pixels,             // We can assign pixels directly to data
        .width = width,
        .height = height,
        .mipmaps = 1,
        .format = UNCOMPRESSED_R8G8B8A8
    };

    Texture2D checked = LoadTextureFromImage(checkedIm);
    //UnloadImage(checkedIm);         // Unload CPU (RAM) image data (pixels)
    //SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            DrawBoard(pieces, &fontEmoji, &checked, selected);
            GetInput(board, &selected, &next_move, move_list);
            if (next_move.piece != NULL)
            {
                DoMove(board, next_move);
                AddMove(move_list, &next_move);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(checked);     // Texture unloading
    UnloadFont(fontEmoji);      // Unload font resource
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


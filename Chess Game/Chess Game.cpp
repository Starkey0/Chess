

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


#include "board.h"

#define SCREENWIDTH     900
#define SCREENHEIGHT    900
#define GRIDWIDTH       100
#define GRIDHEIGHT      100


void DrawBoard(Piece pieces[32], Font *fontEmoji, Texture2D *checked)
{
    Vector2 pos_init = { SCREENWIDTH / 2 - checked->width / 2,
                         SCREENHEIGHT / 2 - checked->height / 2};
    Vector2 pos_x = { GRIDWIDTH,0 };
    Vector2 pos_y = { 0, GRIDHEIGHT };
    Vector2 pos;

    int mouse_x, mouse_y;
    char c_mouse_pos[12];

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

    //Mouse position
    mouse_x = GetMouseX();
    mouse_y = GetMouseY();

    sprintf_s(c_mouse_pos,12, "%d , %d", mouse_x, mouse_y);

    DrawText(c_mouse_pos, 0,0, 20.0, BLACK);
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = SCREENWIDTH;
    const int screenHeight = SCREENHEIGHT;

    // Generate a checked texture by code
    int width = 800;
    int height = 800;

    Piece pieces[32] = { 0 };

    int font_code[12];

    InitBoard(pieces, font_code);

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
            DrawBoard(pieces, &fontEmoji, &checked);

            

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


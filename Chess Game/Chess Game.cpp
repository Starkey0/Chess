

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


#include "raylib.h"

#define SCREENWIDTH     800
#define SCREENHEIGHT    800
#define GRIDWIDTH       100
#define GRIDHEIGHT      100

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

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = SCREENWIDTH;
    const int screenHeight = SCREENHEIGHT;

    int font_chars[12] = { 0x2654, 0x2655 , 0x2656, 0x2657 , 0x2658 , 0x2659 , 0x265A 
        , 0x265B , 0x265C , 0x265D , 0x265E , 0x265F };

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Chess");

    //Font fontEmoji = LoadFont("resources/Symbola.ttf");
    Font fontEmoji = LoadFontEx("resources/Symbola.ttf", GRIDWIDTH, font_chars, 12);

    // Generate a checked texture by code
    int width = screenWidth;
    int height = screenHeight;

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
        .format = UNCOMPRESSED_R8G8B8A8,
        .mipmaps = 1
    };

    Texture2D checked = LoadTextureFromImage(checkedIm);
    //UnloadImage(checkedIm);         // Unload CPU (RAM) image data (pixels)

    Vector2 pos = { 2.0f, 2.0f };
    

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
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

            //const char* txt = "\xA60";

            ClearBackground(RAYWHITE);
            DrawTexture(checked, screenWidth / 2 - checked.width / 2, screenHeight / 2 - checked.height / 2, Fade(WHITE, 0.5f));
            //DrawTextEx(fontEmoji, txt, pos, fontEmoji.baseSize, 1.0, Fade(LIGHTGRAY, 0.4f));
            DrawTextCodepoint(fontEmoji, 0x2654, pos, 1.0, WHITE);

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


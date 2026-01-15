#include "include\raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "student.h"
#include "elements.hpp"

// Screens
typedef enum
{
    SCREEN_LOGIN
} GameScreen;

// Main Program
int main()
{

    // Draw the Main Window
    InitWindow(1280, 720, "Student Registration System");
    SetTargetFPS(60);

    // Initialize Fonts
        // Sekuya
        char sekuyaPath[] = "assets\\fonts\\Sekuya-Regular.ttf";
        Font sekuya40 = LoadFontEx(sekuyaPath, 50, 0, 0);
        SetTextureFilter(sekuya40.texture, TEXTURE_FILTER_BILINEAR);
        // Orbitron
        char orbitronPath[] = "assets\\fonts\\Orbitron-SemiBold.ttf";
        Font orbitron30 = LoadFontEx(orbitronPath, 30, 0, 0);

    // Initialize Textures
        //"NEXT" Button Textures
        char nextButtonPath[] = "assets\\textures\\next_button.png";
        char nextButtonHoverPath[] = "assets\\textures\\next_hover.png";
        char nextButtonClickedPath[] = "assets\\textures\\next_pressed.png";

        //"CONFIRM" Button Textures
        char confirmButtonPath[] = "assets\\textures\\confirm_button.png";
        char confirmButtonHoverPath[] = "assets\\textures\\confirm_hover.png";
        char confirmButtonClickedPath[] = "assets\\textures\\confirm_pressed.png";
        //App Icon
        char logoPath[] = "assets\\textures\\student_registration_logo.png";
        Image logo = LoadImage(logoPath);
        ImageResizeNN(&logo, 256, 256);

    //Initialize Classes, Buttons, Text input Boxes and Game Screen
    Student student;
    GameScreen currentScreen = SCREEN_LOGIN;
    
        //"NEXT" Button
        Button next(
            nextButtonPath,
            nextButtonHoverPath,
            nextButtonClickedPath
        );
        //"CONFIRM" button
        Button confirm(
            confirmButtonPath,
            confirmButtonHoverPath,
            confirmButtonClickedPath
        );
        //Initialize TextBox Buffers
        char nameBuffer[128] = "";
        char IDBuffer[128] = "";
        bool nameBoxToggle = false;
        bool IDBoxToggle = false;


        

    SetWindowIcon(logo);
    //Text, Position, and Scale Variables so that we don't gouge our eyes out when reading the code cuz whAT THE FUCK
    float spacing = 3.0f;
    float titleScale = 50.0f;
    float subtitleScale = 30.0f;
        //"STUDENT LOGIN" text position
        char studentLoginText[] = "STUDENT LOGIN";
        Vector2 getStudentLoginTextScale = MeasureTextEx(sekuya40, studentLoginText, titleScale, spacing);
        Vector2 studentLoginTextPos = {
            (GetScreenWidth()/2) - (getStudentLoginTextScale.x/2),
            (GetScreenHeight()/3.8f) - (getStudentLoginTextScale.y/2)
        };

        //"Name:" text position
        char nameText[] = "Name:";
        Vector2 getNameTextScale = MeasureTextEx(orbitron30, nameText, subtitleScale, spacing);
        Vector2 nameTextPos = {
            (GetScreenWidth() / 3.3f) - (getNameTextScale.x/2),
            (GetScreenHeight() / 2.6f) - (getNameTextScale.y/2)
        };
        //"ID:" text position
        char IDText[] = "ID:";
        Vector2 getIDTextScale = MeasureTextEx(orbitron30, IDText, subtitleScale, spacing);
        Vector2 IDTextPos = {
            (GetScreenWidth() / 2.88f) - (getNameTextScale.x/2),
            (GetScreenHeight() / 1.9f) - (getNameTextScale.y/2)
        };
        Rectangle nameInputBox = {
            GetScreenWidth()/2.8f,
            GetScreenHeight()/1.885f - (getNameTextScale.y/2),
            370,
            30
        };
        Rectangle IDInputBox = {
            GetScreenWidth()/2.8f,
            GetScreenHeight()/2.585f - (getIDTextScale.y/2),
            370,
            30
        };
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
        //====LOGIN-SCREEN====
        if (currentScreen == SCREEN_LOGIN)
        {
            DrawTextEx(sekuya40, studentLoginText,{studentLoginTextPos.x, studentLoginTextPos.y}, titleScale, spacing, BLACK);
            DrawTextEx(orbitron30, nameText, {nameTextPos.x, nameTextPos.y}, subtitleScale, spacing, DARKGRAY);
            if(GuiTextBox(nameInputBox, nameBuffer, 100, nameBoxToggle)) nameBoxToggle = !nameBoxToggle;
            string name = nameBuffer;
            DrawTextEx(orbitron30, IDText, {IDTextPos.x, IDTextPos.y}, subtitleScale, spacing, DARKGRAY);
            if(GuiTextBox(IDInputBox, IDBuffer, 100, IDBoxToggle)) IDBoxToggle = !IDBoxToggle;
            string ID = IDBuffer;
            next.Draw({(float)GetScreenWidth()/2, (float)GetScreenHeight()/1.4f}, 2, 0);
            if(next.isPressed()){
                if(name.empty()){
                    DrawText("Name is Empty!", GetScreenWidth()/2, GetScreenHeight()/2, 30, DARKGREEN);
                } else if (ID.length() != 9){
                    DrawText("ID must be 9 digits!", GetScreenWidth()/2, GetScreenHeight()/2, 30, DARKGREEN);
                }else if (ID.substr(0, 4) != "7000"){
                    DrawText("ID should follow the format 7000XXXXX", GetScreenWidth()/2, GetScreenHeight()/2, 30, DARKGREEN);
                }   
            }
        }
        EndDrawing();
    }
}

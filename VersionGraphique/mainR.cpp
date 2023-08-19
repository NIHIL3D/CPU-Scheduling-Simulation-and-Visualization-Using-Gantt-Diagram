#include <cstring>
#include <string>
#include <vector>
#include "SchedulingAlgoR.hpp"
using namespace std;

typedef enum GameScreen { SCREEN1, SCREEN2, SCREEN3, SCREEN4, QUANTUM } GameScreen;


int main(void)
{
    
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "CPU Scheduling Simulation");

    GameScreen currentScreen = SCREEN1;

    Image logo = LoadImage("logo2.png");    
    Texture2D texture = LoadTextureFromImage(logo);         
    UnloadImage(logo);   
    string name, quantum;      
    int letterCount = 0;
    bool openfile = false;
    int choice;
    
    Process process;
    vector<Process> processuses;
    vector<Process> processes;
    string myline;
    ifstream myfile;
    string fichier ;


    Rectangle textBox = { 50, 180, screenWidth - 100 , 50 };
    Rectangle ButtonFCFS = { screenWidth/2.0f - 100, 130, 225, 50 };
    Rectangle ButtonSJF = { screenWidth/2.0f - 100, 190, 225, 50 };
    Rectangle ButtonRR = { screenWidth/2.0f - 100, 250, 225, 50 };
    Rectangle ButtonPS = { screenWidth/2.0f - 100, 310, 225, 50 };
    Rectangle ButtonClose = { screenWidth/2.0f - 100, 370, 225, 50 };
    Rectangle textboxQUANTUM = {screenWidth/2.0f - 100, 180, 225, 50 };
    bool mouseOnText = false;
    bool mouseOnButton = false;
    Rectangle Button;
    bool close = false;

    int framesCounter = 0;          

    SetTargetFPS(10);              
    while (!WindowShouldClose() && !close)    
    {
        // Update
        //----------------------------------------------------------------------------------
        switch(currentScreen)
        {
            case SCREEN1:
            {
               

                framesCounter++;    

                
                if (framesCounter > 50)
                {
                    currentScreen = SCREEN2;
                }
            } break;
            case SCREEN2:
            {
                
                choice = 0;
                if (CheckCollisionPointRec(GetMousePosition(), textBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnText = true;
                else if (!CheckCollisionPointRec(GetMousePosition(), textBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnText = false;

                if (mouseOnText)
                {
                    
                    SetMouseCursor(MOUSE_CURSOR_IBEAM);

                    
                    int key = GetCharPressed();

                    
                    while (key > 0)
                    {
                        
                        name.push_back((char)key);
                        
                        letterCount++;

                        key = GetCharPressed();  
                    }

                    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyDown(KEY_BACKSPACE))
                    {
                        name.pop_back();
                        letterCount--;
                        if (letterCount < 0) {
                            name = "";
                            letterCount = 0;
                        }
                        
                    }
                    if (IsKeyPressed(KEY_ENTER))
                        {
                            mouseOnText = false;
                            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                            openfile = true;
                            currentScreen = SCREEN3;
                        }
                }
                else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

                if (mouseOnText) framesCounter++;
                else framesCounter = 0;
            } break;
            case SCREEN3:
            {
                if (openfile)
                {
                    myfile.open(name);

                    if (myfile.is_open())
                    {
                        getline(myfile, myline);
                        int c = 1, k;
                        while (getline(myfile, myline))
                        {
                            if (!(myline == "" || myline[0] == '#'))
                            {
                                vector<string> line = split(myline);
                                
                                process.pid = line[0];
                                process.arrivalTime = stoi(line[1]);
                                process.burstTime = stoi(line[2]);
                                
                                process.color = { GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
                               
                                if (line.size()==4)
                                {
                                    process.priority = stoi(line[3]);
                                };
                                processuses.push_back(process);
                            }
                        }
                        openfile = false;
                    }
                }
                

                if (CheckCollisionPointRec(GetMousePosition(), ButtonFCFS)) 
                {
                    
                    mouseOnButton = true;
                    Button = ButtonFCFS;
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) choice = 1;

                }
                else if (CheckCollisionPointRec(GetMousePosition(), ButtonSJF)) 
                {
                    mouseOnButton = true;
                    Button = ButtonSJF;
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) choice = 2;

                }
                else if (CheckCollisionPointRec(GetMousePosition(), ButtonRR)) 
                {
                    mouseOnButton = true;
                    Button = ButtonRR;
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) choice = 3;

                }
                else if (CheckCollisionPointRec(GetMousePosition(), ButtonPS)) 
                {
                    mouseOnButton = true;
                    Button = ButtonPS;
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) choice = 4;

                }
                 
                else mouseOnButton = false;
                
                
                
                switch (choice) {
                    case 1:
                        // FCFS
                        processes = FCFS(processuses);
                        currentScreen = SCREEN4;
                        break;
                    case 2:
                        // SJF
                        processes = SJF(processuses);
                        currentScreen = SCREEN4;
                        break;
                    case 3:
                        // Round Robin
                        currentScreen = QUANTUM;
                        break;
                        case 4:
                        // PS
                        processes = PS(processuses);
                        currentScreen = SCREEN4;
                        break;
                    default:
                        
                        break;
                }
                
            } break;
            case SCREEN4:
            {
                
                if (CheckCollisionPointRec(GetMousePosition(), ButtonClose)) 
                {
                    
                    mouseOnButton = true;
                    Button = ButtonClose;
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) close = true;

                }
                else mouseOnButton = false;
            } break;
            case QUANTUM:
            {
                
                if (CheckCollisionPointRec(GetMousePosition(), textboxQUANTUM) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnText = true;
                else if (!CheckCollisionPointRec(GetMousePosition(), textboxQUANTUM) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) mouseOnText = false;

                if (mouseOnText)
                {
                    
                    SetMouseCursor(MOUSE_CURSOR_IBEAM);

                    
                    int key = GetCharPressed();

                    
                    while (key > 0)
                    {
                        
                        quantum.push_back((char)key);
                        
                        
                        letterCount++;

                        key = GetCharPressed();  
                    }

                    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyDown(KEY_BACKSPACE))
                    {
                        quantum.pop_back();
                        letterCount--;
                        if (letterCount < 0) {
                            quantum = "";
                            letterCount = 0;
                        }
                        
                    }
                    if (IsKeyPressed(KEY_ENTER))
                        {
                            cout << quantum << endl;
                            processes = RoundRobin(processuses, stoi(quantum));
                            
                            mouseOnText = false;
                            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                            currentScreen = SCREEN4;
                        }
                }

            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);


            DrawText("Made by Mohammed EL KHATTABI && Abdessamad LAMGHARI IDRISSI", 130, 432, 16, GRAY);
            switch(currentScreen)
            {
                case SCREEN1:
                {
                    
                    DrawTexture(texture, 280, 0, LIGHTGRAY);
                    
                    DrawText("CPU Scheduling Simulation", 80, 200, 50, GRAY);

                } break;
                case SCREEN2:
                {
                    DrawText("Insert your text file", 280, 140, 20, GRAY);

                    DrawRectangleRec(textBox, LIGHTGRAY);
                    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
                    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

                    DrawText(name.c_str(), (int)textBox.x + 5, (int)textBox.y + 14, 20, MAROON);

                    

                    if (mouseOnText)
                    {
                        
                        if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name.c_str(), 20), (int)textBox.y + 18, 20, MAROON);
                        DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
                    }
                } break;
                case SCREEN3:
                {
                    
                    DrawText("Chose your Scheduling Algorithm!", 150, 40, 30, GRAY);
                    DrawRectangleRec(ButtonFCFS, LIGHTGRAY);
                    DrawRectangleRec(ButtonSJF, LIGHTGRAY);
                    DrawRectangleRec(ButtonRR, LIGHTGRAY);
                    DrawRectangleRec(ButtonPS, LIGHTGRAY);
                    if (mouseOnButton) 
                    {
                        DrawRectangleRec(Button, GRAY);
                        DrawRectangleLines((int)Button.x, (int)Button.y, (int)Button.width, (int)Button.height, RED);
                    }
                    DrawText("FCFS", screenWidth/2.0f - 10, 145, 20, MAROON);
                    DrawText("SJF", screenWidth/2.0f - 5, 205, 20, MAROON);
                    DrawText("RR", screenWidth/2.0f, 265, 20, MAROON);
                    DrawText("PS", screenWidth/2.0f, 325, 20, MAROON);
                    
                    

                } break;
                case SCREEN4:
                {
                    int space = 0;
                    int spaceP = 0;
                    int responseTime;
                    int burstTime;
                    
                    
                    DrawLine(100, 80, 100, 340, BLACK);
                    DrawLine(100, 340, 700, 340, BLACK);

                    
                    switch (choice) {
                    case 1:
                        DrawText("FCFS", 100, 20, 40, GRAY);
                        break;
                    case 2:
                        DrawText("SJF", 100, 20, 40, GRAY);
                        break;
                    case 3:
                        DrawText("RR", 100, 20, 40, GRAY);
                        break;
                        case 4:
                        DrawText("PS", 100, 20, 40, GRAY);
                        break;
                    default: break;
                }



                    for(int i = 0; i<processuses.size(); i++)
                        {
                            DrawText("P", 65, 90 + spaceP, 25, DARKGRAY);
                            DrawText(processes[i].pid.c_str(), 80, 103 + spaceP, 18, DARKGRAY);
                            spaceP += 40;
                        }
                    

                    if (choice == 3)
                    {
                        
                        for(int i = 0; i < processuses.size(); i++)
                        { 
                            
                            for(int j = 0; j < processes[i].responseTimes.size(); j++)
                            {
                                
                                responseTime = processuses[i].responseTimes[j][0]*20;
                                burstTime = processuses[i].responseTimes[j][1]*20;
                                
                                DrawRectangle(105 + responseTime, 90 + space, burstTime, 30, processuses[i].color);
                            }
                            space += 40;
                        }
                        
                    }
                    else 
                    {
                        for(int i = 0; i<processuses.size(); i++)
                        {
                            
                            
                            responseTime = processuses[i].responseTime*20;
                            DrawRectangle(105 + responseTime, 90 + space, 20*processuses[i].burstTime, 30, processuses[i].color);
                            space += 40;
                        }
                        
                    }
                    
                     
                    DrawRectangleRec(ButtonClose, LIGHTGRAY);
                    if (mouseOnButton) 
                    {
                        DrawRectangleRec(Button, GRAY);
                        DrawRectangleLines((int)Button.x, (int)Button.y, (int)Button.width, (int)Button.height, RED);
                    }

                    DrawText("Close", screenWidth/2.0f - 40, 375, 40, MAROON);
                } break;
                case QUANTUM:
                {
                    
                    DrawText("QUANTUM:", 350, 140, 25, GRAY);
                    DrawRectangleRec(textboxQUANTUM, LIGHTGRAY);
                    if (mouseOnText) DrawRectangleLines((int)textboxQUANTUM.x, (int)textboxQUANTUM.y, (int)textboxQUANTUM.width, (int)textboxQUANTUM.height, RED);
                    else DrawRectangleLines((int)textboxQUANTUM.x, (int)textboxQUANTUM.y, (int)textboxQUANTUM.width, (int)textboxQUANTUM.height, DARKGRAY);

                    DrawText(quantum.c_str(), (int)textboxQUANTUM.x + 5, (int)textboxQUANTUM.y + 14, 20, MAROON);

                    

                    if (mouseOnText)
                    {
                        
                        if (((framesCounter/20)%2) == 0) DrawText("_", (int)textboxQUANTUM.x + 8 + MeasureText(quantum.c_str(), 20), (int)textboxQUANTUM.y + 18, 20, MAROON);
                        DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
                    }
                } break;
                default: break;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    

    CloseWindow();       
    //--------------------------------------------------------------------------------------

    return 0;
}


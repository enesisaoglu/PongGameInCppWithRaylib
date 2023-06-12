#include <iostream>
#include "raylib.h"

using namespace std;

//Global Variables...
Color green = Color{38,185,154,255};
Color darkGreen = Color{ 20,160,133,255 };
Color lightGreen = Color{ 129,204,184,255 };
Color yellow = Color{ 243,213,91,255 };

int playerScore = 0;
int cpuScore = 0;

class Ball {
public:
    float x, y;
    int speedX, speedY;
    int radius;

    void DrawBall() {
        DrawCircle(x, y, radius, yellow);//Function to draw circle which is here ball...
    }

    void uptade() {
        x += speedX;
        y += speedY;

        if (y < 0 || y > GetScreenHeight()) {
            speedY *= -1;
        }
       

        if (x<=0)//Player Wins
        {
            playerScore++;
            ResetBall();
        }

        if(x>=GetScreenWidth())//Cpu Wins
        {
            cpuScore++;
            ResetBall();
        }

   
    }

    void ResetBall()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speedChoices[2] = { -1,1 };
        speedX *= speedChoices[GetRandomValue(0, 1)];
        speedY *= speedChoices[GetRandomValue(0, 1)];
    }

};

class Paddle {
protected:
    void LimitMovement()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }

    }
public:
    float x, y;
    float width, height;
    int speed;

    void DrawPaddle() {
        DrawRectangleRounded(Rectangle{ x,y,width,height }, 0.8, 0, WHITE);
    }

    void update() {
        if (IsKeyDown(KEY_UP))
        {

            y = y - speed;

        }
        if(IsKeyDown(KEY_DOWN))
        {
        
            y = y + speed;

        }
        
        LimitMovement();
  
    }
};

class CpuPaddle: public Paddle {

public:
    void Update(int ball_y) 
    {
        if(y+height/2>ball_y)
        {
            y = y - speed;
        }
        if(y+height/2<=ball_y)
        {
            y = y + speed;
        }

        LimitMovement();
    }



};



//Declaration of class objects...
Ball ball;
Paddle player;
CpuPaddle cpu;


int main(void)
{
    cout << "starting the game" << endl;

    const int screenWidth = 1280;
    const int screenHeight = 800;

    InitWindow(screenWidth,screenHeight,"Pong Game!"); //Set weight and height of the screen will be displayed...
                                                        //And string message in screen...
    
    
    SetTargetFPS(60);//How fast the game should run...
                     //Frame rate for our game...
                    
    

    //Initialize member data of ball class...
    ball.radius = 20;
    ball.x = screenWidth / 2;
    ball.y = screenHeight / 2;
    ball.speedX = 7;
    ball.speedY = 7;
    //Initialize member data of paddle class...
    player.width = 25;
    player.height = 120;
    player.x = screenWidth - player.width - 10;
    player.y = screenHeight / 2 - player.height / 2;
    player.speed = 6;
    //Initialize inherited data of CpuPaddle class...
    cpu.height = 120;
    cpu.width = 25;
    cpu.x = 10;
    cpu.y = screenHeight / 2 - cpu.height / 2;
    cpu.speed = 6;

    

    while (!WindowShouldClose())//if the close icon of the window is not pressed,
    {                           // execute the body of control structure...
       
        BeginDrawing(); // Function to creates a blank canvas...
        
     
        //Updating...
        ball.uptade();
        player.update();
        cpu.Update(ball.y);

     
        //Checking for collisions...
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{player.x,player.y,player.width,player.height}))
        {
        
            ball.speedX *= -1;

        }
        if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ cpu.x,cpu.y,cpu.width,cpu.height }))
        {

            ball.speedX *= -1;

        }

        ClearBackground(darkGreen);// Function to fill the window we are drawing on with black color...

        //Drawing the material in the game to be displayed in the screen...
        DrawRectangle(screenWidth/2,0,screenWidth/2,screenHeight,green);
        DrawCircle(screenWidth / 2, screenHeight / 2, 150, lightGreen);
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
        ball.DrawBall();
        cpu.DrawPaddle();
        player.DrawPaddle();
        DrawText(TextFormat("%i",cpuScore), screenWidth / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", playerScore), 3 * screenWidth / 4 - 20, 20, 80, WHITE);

        EndDrawing();// Function to end the canvas drawing...

    }

    CloseWindow();

    return 0;
}
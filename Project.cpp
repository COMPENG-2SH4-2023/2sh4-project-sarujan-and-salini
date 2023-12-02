#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include <random>
#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

//create references to GameMechanics and Player class to use throughout the main program
GameMechs* myGM;
Player* myPlayer;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    //game should only run while exitflag status is set to false
    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    //initialize the object references that were created globally
    myGM = new GameMechs(26, 13);
    myPlayer = new Player(myGM);

    //seed the random number generation
    srand(time(NULL));

    //intialize a starting position for food
    myGM->generateFood(myPlayer->getPlayerPos());
}

void GetInput(void)
{
    char temp_input;
    temp_input = myGM->getInput();


    //check if the input entered by user corresponds to the exit flag key
    //if not assign input into gameMechanics object
    if( temp_input == ' ')
    {
        myGM->setExitTrue();
    }
   
    else
    {
        myGM->setInput(temp_input);
    }
   
}

void RunLogic(void)
{
    //steps for main logic
    //process input and update the player direction, move the player based on the processed input, then clear input
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 
    bool drawn;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;

    objPos foodPos;
    myGM->getFoodPos(foodPos);

    int i, j, k, row, col;

    
    //nested for loops that draw the screen
    for(i = 0; i < myGM->getBoardSizeY(); i++)
    {   
        if(i == 0 || i == myGM->getBoardSizeY() - 1 )
        {
            //for loop that draws the border
           for(j = 0; j < myGM->getBoardSizeX(); j++)
           {
                MacUILib_printf("#");
           }
        }
        else
        {
            for(j = 0; j < myGM->getBoardSizeX(); j++)
            {
                drawn = false;
                //draw the player body
                //iterate through every element in the player body list 
                for(k = 0; k < playerBody->getSize(); k++)
                {
                    //for each iteration we get a copy of that element in the body and compare it to the current
                    //element being printed on the screen
                    playerBody->getElement(tempBody, k);
                    if(tempBody.x == j && tempBody.y == i)
                    {
                        MacUILib_printf("%c", tempBody.symbol);
                        drawn = true;
                        break;
                    }

                }
                //if player body was drawn dont draw anything
                if(drawn) continue;

                //second check for the border coords
                if(j == 0 || j == myGM->getBoardSizeX() - 1)
                {   
                    MacUILib_printf("#");
                }
                
                //If nothing is printed then a blank space is printed
                else if (j > 0 && j < myGM->getBoardSizeX() - 1)
                {
                    
                    if(j == foodPos.x && i == foodPos.y)
                    {
                        MacUILib_printf("%c", foodPos.symbol);
                    }
                    else
                    {
                        MacUILib_printf(" ");
                    }
                
                }
            }
        }
        MacUILib_printf("\n");
    }

    //output the score, current food position, and player body positions
    MacUILib_printf("Score: %d", myGM->getScore());
    MacUILib_printf("\nFood Pos: <%d, %d>", foodPos.x, foodPos.y);
    MacUILib_printf("\nPlayer positions:\n");
    for(int l = 0; l < playerBody->getSize();l++)
    {
        playerBody->getElement(tempBody, l);
        MacUILib_printf("<%d,%d> ", tempBody.x, tempBody.y );
    }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();  

    if(myGM->getLoseFlagStatus())
    {
        MacUILib_printf("\n----------- GAME OVER -----------");
        MacUILib_printf("\n            .--.");
        MacUILib_printf("\n        >--'--') )");
        MacUILib_printf("\n              / / ");
        MacUILib_printf("\n             / / ");
        MacUILib_printf("\n            ( ( _ . __ __ _,");
        MacUILib_printf("\n             '.__ __ .- - '   ");
 
        
        
    }
    else
    {
        MacUILib_printf("\n----------- You successfully exited the game! -----------");
    }

    MacUILib_printf("\n\nYour score was: %d", myGM->getScore());

    delete myGM;
    delete myPlayer;  

    
  
    MacUILib_uninit();
}

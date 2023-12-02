#include "GameMechs.h"
#include "MacUILib.h"


GameMechs::GameMechs()
{
    input = '\0';
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 20; // default board size
    boardSizeY = 10;

    foodPos.setObjPos(-1,-1, 'o'); //initialize food pos outside of the game board

}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = '\0';
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX; // default board size
    boardSizeY = boardY;

    foodPos.setObjPos(-1,-1, 'o'); //initialize food pos outside of the game board


}

// do you need a destructor?
GameMechs::~GameMechs()
{
   
}


bool GameMechs::getExitFlagStatus()
{
    //return the exitflag 
    return exitFlag;

}
void GameMechs::setExitTrue()
{
    //set exit flag to true
    exitFlag = true;
}

bool GameMechs::getLoseFlagStatus()
{
    //return the current loseflag status
    return loseFlag;
}

void GameMechs::setLoseFlag()
{
    //set lose flag to true
    loseFlag = true;

}

char GameMechs::getInput()
{
    //if a key is pressed we store it in input
    if(MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
    
    return input;

}

void GameMechs::setInput(char this_input)
{
    //set input to the input that stored in this_input
    input = this_input;

}

void GameMechs::clearInput()
{
    input = '\0';
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;

}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;

}



int GameMechs::getScore()
{
    return score;

}

void GameMechs::incrementScore()
{
    //increment score by 1 when food is collected
    score += 1;

}

void GameMechs::generateFood(objPosArrayList* blockOff)
{
    int i, j, rand_x, rand_y;
    bool valid = false;

    objPos tempPos;

    objPosArrayList* playerBody = blockOff;

    objPos tempBody;
    const objPos* tempBodyRef;
    tempBodyRef = &tempBody;

    //while loop runs until a valid set of x/y coords are generated
    //ensure x and y dont interfere with snake position
    while(valid != true)
    {
        //generate random x and y coords and make sure they are not border or block off position
        rand_x = rand() % (boardSizeX - 2) + 1;
        rand_y = rand() % (boardSizeY - 2) + 1;

        //assign the x and y values to tempPos before testing
        tempPos.x = rand_x;
        tempPos.y = rand_y;
    
        //run through each snake body element and ensure the random coords dont match the player coords
        for(int k = 0; k < blockOff->getSize();k++)
        {
            playerBody->getElement(tempBody, k);
            {
                if(tempPos.isPosEqual(tempBodyRef) == true)
                {   
                    valid = false;
                    break;
                }
                else
                {
                    valid = true;
                }
                
            }
            
        }
        


    }
    //assign the x and y values to foodpos after comparing to player pos
    foodPos.x = tempPos.x;
    foodPos.y = tempPos.y;
    foodPos.symbol = 'o';

}

void GameMechs::getFoodPos(objPos &returnPos)
{
    //write the current foodPos into returnPos
    returnPos.x = foodPos.x;
    returnPos.y = foodPos.y;
    returnPos.symbol = 'o';

}



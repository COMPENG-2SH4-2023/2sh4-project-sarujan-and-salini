#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    
    objPos tempPos;
    //set player position to the center of the board
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    
    //create place to hold all the player body positions
    playerPosList = new objPosArrayList();
    //add head a the preset center of the board
    playerPosList->insertHead(tempPos);


}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
   // returns the reference to the playerPos array list
   return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic       
    //get player input from GameMechs class
    char input = mainGameMechsRef->getInput();


    if (myDir == LEFT)  //if left, only directions allowed are up and down, NOT right or left again
    {
        if (input == 'a' || input == 'd')    // if its left or right, just maintain direction as left by changing input to 'a' (left)
        {
            input = 'a';
        }
        else      
        {
            //pass through input without any changes
        }
    }
    else if (myDir == RIGHT) 
    {
        if (input == 'a' || input == 'd')
        {
            input = 'd';
        }
        else    
        {
            
        }
    }
    else if (myDir == UP) 
    {
        if (input == 'w' || input == 's')
        {
            input = 'w';
        }
        else    
        {
                
        }
    }
    else if (myDir == DOWN) 
    {
        if (input == 'w' || input == 's')
        {
            input = 's';  
        }
        else    
        {

        }
    }
    else
    {
        //do nothing 
    }

    switch(input)
    {                      
        case ' ':  // exit if space bar is pressed
            mainGameMechsRef->setExitTrue();
            break;

        case 'a':
            myDir = LEFT;
            break;         //if this is the character pressed, set myDir and break out of switch case

        case 'd':
            myDir = RIGHT;
            break;

        case 'w':
            myDir = UP;
            break;

        case 's':
            myDir = DOWN;
            break;  
                
        default:
            break;
    }

    //clear the input buffer via gameMechanics reference
    mainGameMechsRef->clearInput();
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    objPos currHead; 
    playerPosList->getHeadElement(currHead);  //the posiiton info of the current head gets passed into currHead

    objPos foodPos;
    mainGameMechsRef->getFoodPos(foodPos);  //food positions info gets passed into foodPos

    objPos tempBody;

    //created in order to use func isPosEqual, as it only accepts type const objPos*
    const objPos* tempBodyRef;
    tempBodyRef = &tempBody;
    
    switch (myDir)
    {
        case LEFT:
            currHead.x--;  //decrement the x value to go left
            if(currHead.x <= 0)  // if position goes out of bounds, apply wraparound logic
            {
                currHead.x = mainGameMechsRef->getBoardSizeX() - 2; //subtract by two so that it doesn't go into border
            }
            break;

        case RIGHT:
            currHead.x++;
            if(currHead.x >= mainGameMechsRef->getBoardSizeX() - 1)
            {
                currHead.x = 1; //set to one so it doesn't go into border which is position 0
            }
            break;

        case UP:

            currHead.y--;
            if(currHead.y <= 0)
            {
                currHead.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;

        case DOWN:
            currHead.y++;
            if(currHead.y >= mainGameMechsRef->getBoardSizeY() - 1)
            {
                currHead.y = 1;
            }
            break;

        case STOP:    //no actions needed when game is stopped

            break;
    }

    //new current head should be inserted to the head of the list
    playerPosList->insertHead(currHead);

    if(myDir != STOP)
    {
        int i;
        // for every item in the list check if current head position is the same as any of the others
        //counter starts at one so that it doesn't allow for suicide when there is only one body segment
        for(i = 1; i < playerPosList->getSize(); i++)
        {
            playerPosList->getElement(tempBody, i);
            if(currHead.isPosEqual(tempBodyRef) == true)
            {
                //set both lose flag and exit flag to true if self suicide
                mainGameMechsRef->setLoseFlag();
                mainGameMechsRef->setExitTrue();
            }
        }
    }

    //checking for food collision
    if(currHead.x == foodPos.x && currHead.y == foodPos.y)
    {
        //if food position and current position are the same, increment score and generate new food
        mainGameMechsRef->incrementScore();
        mainGameMechsRef->generateFood(playerPosList);
    }
    else
    {
        //remove tail if food food isn't eaten, so player is still moving, just not increasing length
        playerPosList->removeTail();

    }
    
}




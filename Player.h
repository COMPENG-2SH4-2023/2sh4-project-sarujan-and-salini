#ifndef PLAYER_H
#define PLAYER_H

#define ROW 18
#define COL 36

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList* getPlayerPos(); // Upgrade this in iteration 3.
        void updatePlayerDir();
        void movePlayer();
        //need more action in here
        // -after inserting the head but before removing the tail 
            //-check if new head position collides with food
                //if yes increment the score in gm
                //generate new food
                //do not remove tail

                //otherwise remove tail and move on

                //lastly self collision check
                //if self collided set lose flag to true and exit flag to true through GM

                //if ending you need to differentiate the end game state
                //lost - display lost message
                //otherwise display end game message

    private:
        objPosArrayList *playerPosList;   // Upgrade this in iteration 3.       
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif
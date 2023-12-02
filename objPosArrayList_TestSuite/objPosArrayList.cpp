#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; //creates elements on the heap based on board size
    arrayCapacity = ARRAY_MAX_CAP; //starts at the highest possible capacity
    listSize = 0; //when starting, nothing valid would be in the list

}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; //delete the elements on the heap 
}

int objPosArrayList::getSize()
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    //add error check for when listSize is at capacity
    //if listSize == arrayCapacity; if at capacity don't insert
    int i;
    if(listSize == arrayCapacity)
    {
        //do not insert head if at capacity
    }
    else
    {
        for(i = listSize; i > 0; i--)
        {
            aList[i].setObjPos(aList[i - 1]); //shifts everything to the right by one to insert head
        }

        aList[0].setObjPos(thisPos); //override the first element with what we are trying to add in the head

        listSize++; //increment listSize once an element is added
    }

}

void objPosArrayList::insertTail(objPos thisPos)
{

    if(listSize == arrayCapacity)
    {
        //do not insert tail if at capacity
    }
    else
    {
        aList[listSize++].setObjPos(thisPos); //override the last element with the one being passed into the function
    }
}



void objPosArrayList::removeHead()
{
    int i;
    if(listSize == 0)
    {
        //do nothing if there is nothing in the list
    }
    else
    {
        for(i = 0; i < listSize; i++)
        {
            aList[i].setObjPos(aList[i + 1]); //move everything to the left which automatically removes head
        }
        listSize--; //decrement because of the lost head
    }
}

void objPosArrayList::removeTail()
{
    if(listSize == 0)
    {
        // do nothing if there is nothing in the list
    }
    else
    {
        listSize--; //remove the last element in the list
    }
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[listSize - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);
}
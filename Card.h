#include "MImage.h"


typedef struct Card{
    MImage* mImage;
    int clear;
    int status;
    int resetTime;
    int id;
} Card;

Card * createCard(const char* path,int x,int y,int w,int h,int id){
    Card* card = (struct Card*)malloc( sizeof(struct Card));

    card->mImage = createMImage(path,x,y,w,h);
    card->clear = 0;
    card->status = 0;
    card->resetTime = 0;
    card->id = id;

    return card;
}

#include <string.h>
#include "MImage.h"
#include "Card.h"

Card*** cards;
const int rows = 4;
const int cols = 4;

int timeClock = 60;
float countTime = 0;
int gameOver = 0;

MImage * frontImg;
MImage * playBtn;
MImage * exitBtn;

int clickCount = 0;
int countCardClear = 0;
float resetTime = 0;

float startShowTime = 0;
int gameStatus = 0;

Card*  checkMatchCard(Card * checkCard);


char* getImage(int i){
    char* assets[8] = {
            "assets/1.jpg",
            "assets/2.jpg",
            "assets/3.jpg",
            "assets/4.jpg",
            "assets/5.jpg",
            "assets/6.jpg",
            "assets/7.jpg",
            "assets/8.jpg"
    };
    return assets[i];
}

void gameStart(){
    cards = (Card***)malloc(rows * sizeof(Card**));
    int imgI = 0;
    int x = 5;
    int y = 5;
    int offset = 4;
    for (int row = 0; row < rows; row++) {
        cards[row] = (int**) malloc(cols * sizeof(Card*));
        for(int col = 0; col < cols;col++){
            cards[row][col] = createCard(getImage(imgI),x,y,140,200,imgI);
            x += 140 + offset;
            imgI++;
            if(imgI == 8){
                imgI = 0;
            }
        }
        x = 5;
        y += 200 + offset;
    }
    frontImg = createMImage("assets/front.png",0,0,140,200);
    playBtn  = createMImage("assets/playBtn.jpg",200,200,300,75);;
    exitBtn  = createMImage("assets/exitBtn.jpg",200,300,300,75);;

    // random cards
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int t = rand() % rows * cols;
            int rrow    = t / cols;
            int rcol = t % cols;

            int tmpX = cards[row][col]->mImage->dest.x;
            int tmpY = cards[row][col]->mImage->dest.y;

            cards[row][col]->mImage->dest.x = cards[rrow][rcol]->mImage->dest.x;;
            cards[row][col]->mImage->dest.y = cards[rrow][rcol]->mImage->dest.y;;
            cards[rrow][rcol]->mImage->dest.x = tmpX;
            cards[rrow][rcol]->mImage->dest.y = tmpY;
        }
    }
}

void gameUpdate(){
    if(gameStatus == 0 || gameStatus == 2 || gameStatus == 3){
        return;
    }

    if(countCardClear >= rows * cols){
        gameStatus = 3;
    }

    if(gameStatus == 1){
        countTime += deltaTime;
        if(countTime >= 1000 && countCardClear < rows * cols){
            countTime = 0;
            timeClock--;
            if(timeClock < 0){
                gameOver = 1;
                gameStatus = 2;
            }
        }
        resetTime += deltaTime;
        if(clickCount == 2 && resetTime >= 1000){ // reset card
            clickCount = 0;
            resetTime = 0;
            for (int row = 0; row < rows; row++) {
                for(int col = 0; col < cols;col++){
                    if(cards[row][col]->status == 1){
                        cards[row][col]->status = 0;
                    }
                }
            }
        }

        for (int row = 0; row < rows; row++) {
            for(int col = 0; col < cols;col++){
                Card *card = cards[row][col];
                if(card->status == 2){
                    card->resetTime += deltaTime;
                    if(card->resetTime >= 0){
                        card->resetTime = 0;
                        card->mImage->dest.w -= 5;
                        card->mImage->dest.h -= 5;
                    }
                }

            }
        }
    }

    if(gameStatus == 10){
        startShowTime += deltaTime;
        if(startShowTime >= 10 * 1000){
            startShowTime = 0;
            gameStatus = 1;
        }
    }

}

void onClick(int x,int y){
    if(gameStatus == 1){
        for (int row = 0; row < rows; row++) {
            for(int col = 0; col < cols;col++){
                Card *card = cards[row][col];
                if(x >= card->mImage->dest.x && x <= card->mImage->dest.x + card->mImage->dest.w
                   && y >= card->mImage->dest.y && y <= card->mImage->dest.y + card->mImage->dest.h){
                    if(card->status == 0 && clickCount < 2){
                        card->status = 1;
                        clickCount++;
                        resetTime = 0;

                        Card* otherCard = checkMatchCard(card);
                        if(otherCard != NULL){
                            card->status = 2;
                            otherCard->status = 2;
                            clickCount = 0;
                            countCardClear += 2;
                        }
                    }
                }

            }
        }
    }

    if(gameStatus == 0 || gameStatus == 2 || gameStatus == 3){
        if(x >= playBtn->dest.x && x <= playBtn->dest.x + playBtn->dest.w
           && y >= playBtn->dest.y && y <= playBtn->dest.y + playBtn->dest.h){
            gameStatus = 10;
        }
        if(x >= exitBtn->dest.x && x <= exitBtn->dest.x + playBtn->dest.w
           && y >= exitBtn->dest.y && y <= exitBtn->dest.y + playBtn->dest.h){
            exit(1);
        }
    }

}


void gameDraw(){
    if(gameStatus == 0){
        drawMImage(playBtn);
        drawMImage(exitBtn);
        return;
    }
    if(gameStatus == 2){
        showText(200,100,"GameOver!",233,233,233);
        //drawMImage(playBtn);
        drawMImage(exitBtn);
        return;
    }
    if(gameStatus == 3){
        showText(200,100,"You_Win!",233,233,233);
        //drawMImage(playBtn);
        drawMImage(exitBtn);
        return;
    }

    for (int row = 0; row < rows; row++) {
        for(int col = 0; col < cols;col++){
            if(cards[row][col]->status == 0){
                frontImg->dest.x  = cards[row][col]->mImage->dest.x;
                frontImg->dest.y  = cards[row][col]->mImage->dest.y;
                drawMImage(frontImg);
            }else if(cards[row][col]->status == 1 || cards[row][col]->status == 2){
                drawMImage(cards[row][col]->mImage);
            }
            if(gameStatus == 10){
                drawMImage(cards[row][col]->mImage);
            }
        }
    }

    if(gameStatus == 10){
        char strTime[200] = "Start in:";
        char timeClockStr[100];
        sprintf(timeClockStr, " %.1f", 10 - startShowTime / 1000);
        strcat(strTime,timeClockStr);
        showText(600,500,strTime,233,233,233);
    }

    char strTime[200] = "Time: ";
    char timeClockStr[100];
    sprintf(timeClockStr, " %d", timeClock);
    strcat(strTime,timeClockStr);
    showText(600,200,strTime,233,233,233);
}


Card* checkMatchCard(Card * checkCard){
    for (int row = 0; row < rows; row++) {
        for(int col = 0; col < cols;col++){
            Card *card = cards[row][col];
            if(card->status == 1 && card != checkCard && card->id == checkCard->id ){
                return card;
            }
        }
    }
    return NULL;
}


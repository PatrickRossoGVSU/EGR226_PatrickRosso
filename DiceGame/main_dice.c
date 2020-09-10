#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int isNumber(char CHARcredits[]){// checks if the given string is a positive integer
    int rtn =1;
    int length = strlen(CHARcredits);
    for (int i=0;i<length;i++){
        if (!isdigit(CHARcredits[i])){
            rtn = 0;
            break;
        }
    }
    if(atoi(CHARcredits)<0){
        rtn = 0;
    }
    return rtn;
}


int main()
{
    char CHARcredits[50] = "";
    int credits;
    int check = 0;
    int bet;
    int compRoll;
    int playerRoll;
    time_t t;
    int replay=0;
    srand((unsigned) time(&t));//starts timer for random rolls
    printf("How many credits would you like to start with? ");


    scanf("%s", &CHARcredits);
    credits = atoi(CHARcredits);//sets the int credits equal to the string CHARcredits
    check = isNumber(CHARcredits);

while(replay == 0){//loop for replay-ability
    while(check == 0){//checks initial input
        printf("Please enter a positive number ");
        scanf("%s", &CHARcredits);
        check = isNumber(CHARcredits);
    }
    credits = atoi(CHARcredits);

    printf("How many credits would you like to bet? ");

    scanf("%s", &CHARcredits);
    bet = atoi(CHARcredits);
    check = 0;


    while(check == 0){//checks betting input
        check = isNumber(CHARcredits);
        if(bet>credits || check == 0){
            printf("Please enter a positive number within your balance ");
            scanf("%s", &CHARcredits);
            bet = atoi(CHARcredits);
            check = 0;
        }else{
        check = 1;
    }
    }
    bet = atoi(CHARcredits);

    compRoll = rand()%101;//computer and player roll
    playerRoll = rand()%101;
    printf("The house rolled: %d\nYou rolled:%d\n", compRoll, playerRoll);

    if(playerRoll > compRoll){//win
        credits+=bet;
        printf("You Win! You're current balance is: %d\n", credits);
    }else{
    if(compRoll > playerRoll){//lose
        credits-=bet;
        printf("You Lose... You're current balance is: %d\n", credits);
    }else{//tie
        printf("Tie Game! You're current balance is: %d\n", credits);
    }
    }

    printf("Play again?\nEnter 0 to play again \nEnter 1 to quit\n");
    scanf("%d", &replay);
    itoa(credits, CHARcredits,10);//converts an int into a string
}

printf("You ended with %d credits!", credits);
return 0;
}

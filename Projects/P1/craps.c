/* Fig. 5.10: fig05_10.c
 * Game of Craps from Deitel & Associates,
 * Craps */
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 	/* contains prototype for function time */
#include "wagers.h"

/* enumeration constants represent game status */
enum Status { CONTINUE, WON, LOST };

int rollDice( void ); /* function prototype */

/* Runs a game of craps. Takes no parameters and
 * returns an enum that represents the status of the game.
 * Pre conditions: Game rules printed out and balance initialized
 * Post conditions: A game of craps has been completed and an enum is returned.
*/
enum Status playGame()
{
   int sum;        /* sum of rolled dice */
   int myPoint;    /* point earned */

   enum Status gameStatus; /* can contain CONTINUE, WON, or LOST */

   /* randomize random number generator using current time */
   srand( time( NULL ) );

   sum = rollDice(); /* first roll of the dice */

   /* determine game status based on sum of dice */
   switch( sum ) {

      /* win on first roll */
      case 7:
      case 11:
      gameStatus = WON;
      break;

      /* lose on first roll */
      case 2:
      case 3:
      case 12:
      gameStatus = LOST;
      break;

      /* remember point */
      default:
      gameStatus = CONTINUE;
      myPoint = sum;
      printf( "Point is %d\n", myPoint );
      break; /* optional */
   } /* end switch */

   /* while game not complete */
   while ( gameStatus == CONTINUE ) {
      sum = rollDice(); /* roll dice again */

      /* determine game status */
      if ( sum == myPoint ) { /* win by making point */
         gameStatus = WON; /* game over, player won */
      } /* end if */
      else {

         if ( sum == 7 ) { /* lose by rolling 7 */
            gameStatus = LOST; /* game over, player lost */
         } /* end if */

      } /* end else */

   } /* end while */

   return gameStatus; /* returns game status */

} /* end playGame */

/* roll dice, calculate sum and display results */
int rollDice( void )
{
   int die1;    /* first die */
   int die2;    /* second die */
   int workSum; /* sum of dice */

   die1 = 1 + ( rand() % 6 ); /* pick random die1 value */
   die2 = 1 + ( rand() % 6 ); /* pick random die2 value */
   workSum = die1 + die2;     /* sum die1 and die2 */

   /* display results of this roll */
   printf( "Player rolled %d + %d = %d\n", die1, die2, workSum );

   return workSum; /* return sum of dice */

} /* end function rollRice */
/*
 * function main that starts program
 */
int main( void )
{
    //Initialize and declare balance
    double balance;
    double initBalance;
    printGameRules();
    balance = getBankBalance();
    initBalance = balance;
    //Initialize and declare wager using loop
    while (1)
    {
        double wager;
        while (1) //Loop until a valid wager is entered
        {
            wager = getWager();
            if (checkWager(wager, balance) == 1)
            {
                break;
            }
            printf("Your wager must not exceed your current balance.\n");
        }

        //Create chatter based on the wager
        if (wager <= (0.25 * balance)) //Chatter if wager is less than quarter of balance
        {
            printf("Aw c'mon, take a chance!\n");
        }
        if (wager >= (0.60 * balance)) //Chatter if wager is more than 60% of balance
        {
            printf("Oh, you're going for broke, huh?\n");
        } else {
            printf("Playing it safe, huh?\n"); //Chatter if in between
        }
        //Run playgame and check the returned game status to see if player won or lost
        if (playGame() == WON)
        {
            printf("Player wins\n");
            //Add wager to balance if player won
            balance = adjustBalance( balance, wager, 1);
        }
        else {
            printf("Player loses\n");
            //Subtract wager from balance if player lost
            balance = adjustBalance( balance, wager, 0);
        }
        //Print current balance
        printf("\nBalance = $%1f\n", balance);
        //Chatter if balance is 50% larger than initial balance
        if (balance >= (1.5 * initBalance))
        {
            printf("You're up big, now's the time to cashin your chips!\n");
        } else {
            printf("Keep going! You could earn a lot more!");
        }
        //End game if balance is less than 0 or if player replies no
        if (balance == 0 || getYESorNO() == 0) {
            if (balance == 0)
            {
                printf("\nSorry, you busted!\n");//Chatter if balance is 0
            }

            printf("\nYour final balance is $%1f\n", balance);//Print final balance

            break;
        }
    }

    return 0; /* Indicates successful termination */
}


/**************************************************************************
 * (C) Copyright 1992-2004 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/

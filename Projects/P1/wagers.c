#include <stdio.h>

/*
 * Prints the rules for craps.
 * Takes no paramenters and returns nothing.
 * Pre conditions: None
 * Post conditions: Game rules have been printed to output
 */
void printGameRules( void )
{
    //Print game rules
    printf("Welcome to Craps!.\n"
           "Each die has six faces.\n"
           "These faces contain 1, 2, 3, 4, 5, and 6 spots."
           "After the dice have come to rest, the sum of the spots on the two upward faces is calculated.\n"
           "If the sum is 7 or 11 on the first throw, the player wins.\n"
           "If the sum is 2, 3, or 12 on the first throw (called \"craps\"), the player loses (i.e., the \"house\" wins).\n"
           "If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes the player's \"point.\"\n"
           "To win, you must continue rolling the dice until you \"make your point.\"\n"
           "The player loses by rolling a 7 before making the point.\n"
        );
}

/*
 * Prompts player for initial bank balance.
 * Returns a double which represents the entered balance.
 * Takes no parameters.
 * Pre conditions: None
 * Post conditions: A double which represents the entered balance
 * has been returned.
 */
double getBankBalance( void )
{
    double balance;

    //Prompt player for balance
    printf("Balance = $");
    while(1)// Loop until valid balance has been enetered
    {
        while(scanf("%lf", &balance) != 1)//Prompt until double has been entered
        {
            while (getchar() != '\n');//Clear input buffer
            printf("Please enter a valid balance.\n");
            printf("Balance: $");
        }
        if (balance > 0.0)
        {
            break;
        }
        printf("Please enter a balance greater than 0.\n");
        printf("Balance: $");
    }
    while (getchar() != '\n'); //Clear input buffer

    return balance;
}

/*
 * Checks if the provided wager is less than or equal to the provided balance.
 * Takes wager and balance as parameters.
 * Returns an 0 if wager > balance and 1 other wise.
 * Pre conditions: Two doubles are provided as parameters
 * Post conditions: Either a 0 or 1 is returned
 */
int checkWager( double wager, double balance )
{
    if (wager > balance)//Compare wager to balance
    {
        return 0;
    }
    return 1;
}

/*
 * Prompts the user for a wager before a game.
 * Takes no parameters.
 * returns a double which represents player entered wager
 * Pre conditions: none
 * Post conditions: a double equal to player entered wager has been returned
 */
double getWager( void )
{
    double wager;

    //Prompt for wager
    printf("Enter wager: ");
    while(1)// Loop until valid wager is entered
    {
        while(scanf("%lf", &wager) != 1)//Prompt until a double has been entered
        {
            while(getchar() != '\n'); // Clear input buffer
            printf("Enter a valid wager.\n");
            printf("Enter a new wager: ");
        }
        if (wager >= 0.0)
        {
            break;
        }
        printf("Enter a valid wager.\n");
        printf("Enter a new wager: ");
    }
    while(getchar() != '\n');// Clear input buffer

    return wager;
}

/*
 * Adjusts the balance based on the wager and whether player won or lost the game.
 * The wager is added to the balance if the player won and subtracted if the player lost.
 * Function takes 2 doubles and an int as parameters: bankbalance, wageamount,
 * and addOrSubtractToBalance. If the third parameter is a 0, the wager is subtracted.
 * Otherwise, the wager is added.
 * Returns the adjusted balance
 * Pre conditions: Two doubles are entered as the first two parameters and a 1 or a 0 is entered
 * as the third.
 * Post conditions: A double representing the adjusted balacne is returned.
 */
double adjustBalance( double bankbalance, double wageamount, int addOrSubtractToBalance )
{
    //Check if the third parameter is 0
    if (addOrSubtractToBalance == 0)
    {
        return bankbalance - wageamount;
    }
    return bankbalance + wageamount;
}

/*
 * Asks the player if they want to play another game of craps.
 * The function takes no parameters.
 * Returns an int where 1 represents yes and 0 represents no.
 * Pre conditions: None
 * Post conditions: An int (0 or 1) representing the players response is returned
 */
int getYESorNO( void )
{
    char c;
    while (1)//Prompt user until a valid response is entered
    {
        printf("Do you want to play another game? (y or n): ");
        c = getchar();//Clear input buffer
        while(getchar() != '\n');
        if (c != 'y' && c != 'n')//Check if input is valid.
        {
            printf("You must answer y or n.\n");
        } else {
            break;
        }
    }
    //Check if input is 'y'
    if (c == 'y')
    {
        return 1;
    }

    //Return 0 if input is 'n'
    return 0;
}

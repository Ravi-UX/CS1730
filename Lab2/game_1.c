#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define ROCK 			0
#define PAPER 			1
#define SCISSORS 		2
#define DONE 			3

#define NUMBER_GAME_OBJECTS 	3
#define rock_s 			"rock"
#define paper_s 		"paper"
#define scissors_s 		"scissors"

char *  game_object[3];		// replace with game object


// allocate a string denoting a game object then
// let the array pointer point to that string
void intialize_game_objects()
{
	game_object[ROCK] 	= strdup( rock_s );
	game_object[PAPER] 	= strdup( paper_s );
	game_object[SCISSORS] 	= strdup( scissors_s );
}


// welcomes the user
void greeting()
{
	printf( "\n\nHello, Welcome to rock-paper-scissors\n" ) ;
	printf( "                  rock-paper-scissors\n" ) ;
	printf( "                  rock-paper-scissors\n" ) ;
}


// print out a menu to user.
void printMenu()
{
	printf( "\n\nPlease type:\n"
		"               0 for Rock \n"
		"               1 for Paper\n"
		"               2 for Scissors\n"
		"               3 for Quit\n"
		"---> "
                );
}


// ask user for input, and returns the input of the user
int askUser()
{
	char 	line[255];
	int	return_user_int=-1;

	printMenu();

        fgets( line, sizeof( line ), stdin );

	// get the 'integer' from line of input
	// put it in the variable container 'user'
	while( sscanf( line, "%d", &return_user_int ) != 1 )
	{
		printf( "\n*** You have not entered an integer ***\n" );
		printMenu();
		fgets( line, sizeof( line ), stdin );
	}
	return return_user_int;
}


// promts the user ot hit any key. to continue on.
int promptUser( char *toseewhat )
{
	char 	line[255];

    	printf( "\n\nHit <return>\n   %s  --> ", toseewhat) ;
   	fgets( line, sizeof( line ), stdin );
   	printf("\n");

	return 0;
}


// --- LAB -- begins ----

// Question 1: CheckRange:
int checkRange( int user_pick )
{
	// write code that checks the RANGE of the user input
    if (user_pick < 0 || user_pick > 3) {
        printf("Your number is not in the proper range.\n");
        printf("The proper range is between 0 and 3");
        return -1;
    }


	// tell the user via a printf() statement the proper range.


 	return 0;  //  what should return?
}


// Question 2: ComputerPick
int computerPick()
{
	int computer_pick = ROCK;

	// QUESTION 2: relace the below statement so that computer
	// picks 0, 1 or 2 randomly. you will neet do use:
	// 1) rand() and
	// 2) the  modulus operator '%'
	//
	// man rand to see how to use rand (use the man pages)


	// computer always picks rock here.
    srand(time(NULL));
	computer_pick = rand() % 3;


	return computer_pick;
}


// Question 3: computeOutcome
void computeOutcome( 	int computer_pick,
			int user_pick,
                        char *users_pick_string,
			char *computers_pick_string
		)
{

	// you never lose here because of a logical error!
	// do you know why?
	//
	// well you need to fix the bug - so hopefully you do.

	// logic:
	// the computer wins if it is one ahead of user in a 'circular' list
	// rock paper scissors
		// rock paper scissors
			// rock paper scissors

	// replace the below "0" with conditional statement where the
	// computer wins.
	//
	// HINT:
	// to check whether the computer pick is clockwise
	// one unit 'ahead; of user pick, imagine
	// that the list is circular

	if( computer_pick - user_pick == 1 || computer_pick - user_pick == -2 )
	// computer wins, because it is clockwise one unit away
	// from what user selected.
	{
		printf( " %s (you)  <  %s (puter)  You Lost \n" ,
				users_pick_string, computers_pick_string );
	}
	else if( computer_pick == user_pick )
	{
		printf( " %s (you)  =  %s (puter)  It's a TIE \n" ,
				users_pick_string, computers_pick_string );
	}
	else
	{
		printf( " %s (you)  >  %s (puter)  You Won \n" ,
			users_pick_string, computers_pick_string );
	}
}
// --- LAB -- ends  ----


int rungame( int argc, const char *argv[] )
{
	char 	users_pick_string[10], computers_pick_string[10];
	int 	user_pick, computer_pick;

	// greet the user
	greeting();

	// initializers
	srand( time( NULL ) ); 		// seed the randomizer

	intialize_game_objects();	// set the game objec array

	// enter an infinite loop // so we can play forever
	while( 1 )
	{
		user_pick = askUser();

		// ------------------------------------------------------------
		//  checkRange() is below
		// ------------------------------------------------------------
		if( checkRange( user_pick ) ) // check the range
		{
				// go back to beginning of the while loop
				// if input is NOT In range go back to
				// beginning of the while loop.
			continue;
		}

		// check wether the user is done with game
		if( user_pick == DONE )
		{
			printf("Sad to see you leave. Good bye...\n" );
			return 0;
		}

		// decode the user input to a character string
		strcpy( users_pick_string, game_object[ user_pick ] );


		// ------------------------------------------------------------
		//  computerPick() is below
		// ------------------------------------------------------------
		computer_pick = computerPick();

		// decode the computer input to a character string
		strcpy( computers_pick_string, game_object[ computer_pick ] );

		printf( "YOU picked      ------>  %s\n", users_pick_string );

		promptUser( "Computer pick" );

		printf( "\nComputer picked ------>  %s\n\n\n", computers_pick_string );

		// ------------------------------------------------------------
		//  computeOutcome() is below
		// ------------------------------------------------------------
		computeOutcome(
			computer_pick, user_pick,
			users_pick_string, computers_pick_string
			);

	} // while loop
}


int main( int argc, const char *argv[] )
{
 rungame( argc, argv );
}

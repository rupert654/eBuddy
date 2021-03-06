/**
 * @file guess.h
 * @author Andrew Pickin
 *
 * The guess module is run when the user enters guess mode to play the  
 * guessing game
 */

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "emotion.h"
#include "input.h"
#include "gesture_interface.h"
#include "main.h"
#include "queue.h"

// number user needs to guess in sequence to win
#define GUESS_NUMBERTOGUESS 5 

// number needs to guess in first round
#define GUESS_STARTINGNUMTOGUESS 3 

// number of different gestures ebuddy makes in game
#define GUESS_NUMGESTURES 3 

// number of fun points added if game is won
#define GUESS_FUNPOINTS 30 

/**
 * Allows the user to play the eBuddy's guessing game
 * Returns from the function when the user wins or loses the game
 */
int guess_main(em_State *emotions, qu_Queue *notifications, ph_handle *phandle);

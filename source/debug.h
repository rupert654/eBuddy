#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include "utility.h"
#include "input.h"
#include "emotion.h"
#include "gesture_interface.h"
#include "mode.h"
#include "notify.h"
#include "queue.h"

//size between steps when setting or updating emotions
#define DEBUG_EM_STEP 10

//size of the buffer used to store generated text
#define DEBUG_BUFF_SIZE 32

//menu item number used to exit debug
#define DEBUG_EXIT -1

//debug mode entry point
int debug_main(em_State *emotions, qu_queue *notifications, ph_handle *phhandle);

//emotion menu allows user to get and set emotion levels
int debug_emotions(em_State *emotions, qu_queue *notifications, ph_handle *phhandle);

//print event stream to lcd screen
int debug_events(em_State *emotions, qu_queue *notifications, ph_handle *phhandle);

//manually change modes
int debug_modes(em_State *emotions, qu_queue *notifications, ph_handle *phhandle);

//display a menu on the lcd screen allowing the user to choose between
//item's. the function returns the item number or debug_none if the operation
//is canceled
int debug_menu(const char **items, int num_items, ph_handle *phhandle);

//get a number from the user between min and max with
//steps of the given size
int debug_input(int min, int max, int step, ph_handle *phhandle);


#endif

/** 
 * @file main.h
 * @author Rowan Saundry
 *
 * The main module contains the main function and configuration shared
 * between other modules such as emotion definitions and mode numbers.
 * It also contains the mn_run function which accepts a value of type mn_mode
 * and maps it to a function call using a switch case statement. This
 * allows modes used by other modules to be represented by an enum so that
 * they can be stored in configuration arrays.
 */

#ifndef MAIN_H
#define MAIN_H

#include "emotion.h"
#include "phidget.h"
#include "queue.h"


/**
 * @define MN_NUM_EMOTIONS
 *
 * The number of emotions the eBuddy has
 */
#define MN_NUM_EMOTIONS 5

/**
 * @define MN_CONFIG_PATH
 *
 * The path to the configuration directory
 */
#define MN_CONFIG_PATH "conf/"

/**
 * @define MN_NT_CONFIG
 *
 * The path to the notification configuration file
 */
#define MN_NT_CONFIG MN_CONFIG_PATH "notify.json"

/**
 * @define MN_EM_STATE_PATH
 *
 * The path to the emotion state file
 */
#define MN_EM_STATE_PATH MN_CONFIG_PATH "em_state"

/**
 * @define MN_STARTUP_MODE
 *
 * The mode to run on startup
 */
#define MN_STARTUP_MODE MN_REACT

/**
 * @enum emotion_type
 *
 * Contains one entry for each emotion
 */
typedef enum emotion_type {
  MN_EM_NONE = -1,
  MN_EM_HUNGER = 0,
  MN_EM_ENERGY = 1,
  MN_EM_CLEAN = 2,
  MN_EM_SOCIAL = 3,
  MN_EM_FUN = 4
} emotion_type;

/**
 * @enum mn_mode
 *
 * Contains an entry for each run mode
 * (values are used by debug module).
 */
typedef enum mn_mode {
  MN_END = -1,
  MN_NONE = 0,
  MN_REACT = 1,
  MN_SLEEP = 2,
  MN_DEMO = 3,
  MN_DEBUG = 4,
  MN_GUESS = 5,
} mn_mode;

/**
 * @define MN_EMOTIONS
 *
 * Contains the emotion definition array which will be passed
 * to the emotion module.
 */
const em_Emotion MN_EMOTIONS[MN_NUM_EMOTIONS];

/**
 * Initialisises all modules and switches to the mode defined in
 * MN_STARTUP_MODE. After mn_run returns, finalises all modules
 * and exits. 
 *
 * @return A POSIX error code
 */
int main(void);

/**
 * Takes an mn_mode and calls the appropriate entry function.
 *
 * @arg emotions The eBuddys emotion state
 * @arg notifications The notification queue
 * @arg phhandle The handle used to access the phidgets
 * @return A ut_error_code. Passes back errors from child modes.
 */ 
ut_ErrorCode mn_run(mn_mode mode, em_State *emotions, qu_Queue *notifications, ph_handle *phhandle);
#endif

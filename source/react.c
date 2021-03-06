/**
 * @file react.c
 * @author Rowan Saundry
 */

#include <assert.h>

#include "utility.h"
#include "main.h"
#include "emotion.h"
#include "gesture_interface.h"
#include "input.h"
#include "notify.h"
#include "phidget.h"

#include "react.h"

 /*
 * Each emotion action has the following fields: 
 *  
 * Full gesture
 * Low gesture
 * Critical gesture
 * Critical mode
 */
const rc_EmotionAction RC_EM_ACTION[MN_NUM_EMOTIONS] = {
  
  //Hunger
  {{gsi_eyeflash,   "*burp*"},
   {gsi_eyeflash,   "hungry"},
   {gsi_raise_arms, "feed me"},
   MN_NONE},
   
  //Energy
  {{gsi_eyeflash,   "aaauuuoowhh"},
   {gsi_raise_arms, "*yaawn*"},
   {gsi_raise_arms, "*yaaaaaawn*"},
   MN_SLEEP},
   
  //Cleanliness
  {{NULL,           ""},
   {gsi_eyeflash,   "euhg"},
   {gsi_shake_head, "eeeewwwwww"},
   MN_NONE},
   
  //Social
  {{NULL,           ":)"},
   {gsi_raise_arms, "hey"},
   {gsi_fun_level1, "helloooo"},
   MN_NONE},
   
  //Fun
  {{gsi_fun_level1, "wooooo"},
   {gsi_eyeflash,   ":("},
   {gsi_shake_head, "booooring"},
   MN_NONE}
};


 /*
 * Each input action has the following fields: 
 *  
 * Primary emotion update
 * Secondary emotion update
 * Full gesture
 * Normal gesture
 * Low gesture
 * Mode
 */
const rc_InputAction RC_IN_ACTION[IN_NUM_INPUTS] = {

  //Nuts and bolts
  {{EM_ACTION_UPDATE,   MN_EM_HUNGER, 50},
   {EM_ACTION_NONE,    MN_EM_NONE,    0},
   
   {gsi_shake_head,  "*burp*",          "",     0},
   {gsi_eyeflash,    "munch munch",     "",     0},
   {gsi_shake_head,  "yummm!!!",        "",     0},
   
   MN_NONE}, 

  //Oil can
  {{EM_ACTION_UPDATE,   MN_EM_ENERGY, -25},
   {EM_ACTION_UPDATE,   MN_EM_FUN,    15},
   
   {gsi_fun_level1,  "*glug* *glug*",   "",     0},
   {gsi_eyeflash,    "glug",            "",     0},
   {gsi_shake_head,  "yuck",            "",     0},
   
   MN_NONE}, 

  //Battery
  {{EM_ACTION_UPDATE,   MN_EM_FUN,   -25},
   {EM_ACTION_UPDATE,   MN_EM_ENERGY, 15},
   
   {gsi_raise_arms,   "buzz buzz buzz", "",     0},
   {gsi_eyeflash,     "buzz...",        "",     0},
   {gsi_shake_head,   "...",            "",     0},
   
   MN_NONE},  
  
  //Force sensor
  {{EM_ACTION_UPDATE,   MN_EM_SOCIAL, 20},
   {EM_ACTION_UPDATE,   MN_EM_FUN,    5},
   
   {gsi_eyeflash,      "meh",           "",     0},
   {gsi_move_arms,     "tee he he",     "",     0},
   {gsi_happy_level1,  "yeaaaa",        "",     0},
   
   MN_NONE},

  //Dark sensor
  {{EM_ACTION_NONE,    MN_EM_ENERGY,  0},
   {EM_ACTION_NONE,    MN_EM_NONE,    0},

   {gsi_shake_head,   ":(",             "",     0},
   {gsi_move_arms,    "yawn",           "",     0},
   {gsi_raise_arms,   "yaaawn",         "",     0},
   
   MN_SLEEP},
  
  //Left hand
  {{EM_ACTION_NONE,     MN_EM_FUN,    0},
   {EM_ACTION_NONE,     MN_EM_NONE,   0},
   
   {gsi_shake_head,   "",               "",     0},
   {gsi_raise_left,   ":D",             "",     0},
   {gsi_raise_left,   ":)",             "",     0},
   
   MN_GUESS},

  //Right hand 
  {{EM_ACTION_NONE,     MN_EM_FUN,    0},
   {EM_ACTION_NONE,     MN_EM_NONE,   0},
  
   {gsi_shake_head,   "",               "",     0},
   {gsi_raise_right,  ":D",             "",     0},
   {gsi_raise_right,  ":)",             "",     0},
   
   MN_NONE},
   
  //Power on
  {{EM_ACTION_NONE,     MN_EM_NONE,   0},
   {EM_ACTION_NONE,     MN_EM_NONE,   0},

   {NULL,            "",                "",     0},
   {NULL,            "",                "",     0},
   {gsi_eyeflash,    "i am a robot",    "",     0},
   
   MN_NONE},

  //Power off
  {{EM_ACTION_NONE,     MN_EM_NONE,   0},
   {EM_ACTION_NONE,     MN_EM_NONE,   0},

   {NULL,           "",                 "",     0},
   {NULL,           "",                 "",     0},
   {gsi_wave_right, "bye bye",          "",     0},

   MN_END},
    
  //Demo key
  {{EM_ACTION_NONE,     MN_EM_NONE,   0},
   {EM_ACTION_NONE,     MN_EM_NONE,   0},

   {NULL,            "",                "",     0},
   {NULL,            "",                "",     0},
   {gsi_eyeflash,    "demo",            "",     0},
   
   MN_DEMO},

  //Debug key
  {{EM_ACTION_NONE,     MN_EM_NONE,   0},
   {EM_ACTION_NONE,     MN_EM_NONE,   0},

   {NULL,             "",             "",       0},
   {NULL,             "",             "",       0},
   {gsi_eyeflash,     "debug",        "",       0},
   
   MN_DEBUG}
};

const gsi_Reaction RC_MSG_ACTION = {gsi_shake_head,   "beep beep",  "",   0};

const rc_InputAction rc_sleep_action =

  {{EM_ACTION_UPDATE,   MN_EM_ENERGY,   1},
  {EM_ACTION_NONE,      MN_EM_NONE,     0},
  
  {gsi_shake_head,  "..."},
  {gsi_eyeflash,    "zzzzz"},
  {gsi_eyeflash,    "zzZZZzZz"},

  MN_END};


const int RC_MAIN_PAUSE  = 1;
const int RC_SLEEP_PAUSE = 5;


ut_ErrorCode rc_main(em_State *emotions, qu_Queue *notifications, ph_handle *phhandle) {
  const rc_EmotionAction *em_action;
  const rc_InputAction *in_action;
  nt_Message *message;
  em_Event emotion_event; 
  em_condition condition;
  in_input_type input_event;
  int running, rc;

  //keep looping until shutdown signal
  running = 1;
  
  while(running) {

    //look for input events
    input_event = in_get_input();
  
    //react to events
    if(input_event) {
    
      //get action from table
      in_action = &RC_IN_ACTION[input_event - 1];
    
      //get condition of primary emotion before update
      if(in_action->primary_emotion.emotion != MN_EM_NONE) {
        condition = em_get_condition(emotions, in_action->primary_emotion.emotion);
      }
    
      //if emotion is none use critical gesture
      else {
        condition = EM_COND_CRITICAL;
      }
    
      //update primary emotion
      rc = em_react(emotions, &in_action->primary_emotion);
    
      //check for errors in reaction table
      assert(rc ==0);
    
      //update secondary emotion
      rc = em_react(emotions, &in_action->secondary_emotion);
    
      //check for errors in reaction table
      assert(rc ==0);
    
      //if emotion was full do full gesture
      if(condition == EM_COND_FULL) {
        gsi_react(&in_action->full_gesture, phhandle);
      }
    
      //if it was normal do normal gesture
      else if(condition == EM_COND_NORMAL) {
        gsi_react(&in_action->normal_gesture, phhandle);
      }
    
      //otherwise do low gesture
      else {
        gsi_react(&in_action->low_gesture, phhandle);
      }
      
      //check for shutdown signal
      if(in_action->mode == MN_END) {
        running = 0;
      }
    
      //if the input triggers a mode change and emotion level isnt full switch mode
      else if(in_action->mode && condition != EM_COND_FULL) {
        rc = mn_run(in_action->mode, emotions, notifications, phhandle);
      
        //return errors to parent mode
        if(rc) {
          return rc;
        }
      }
    }
 
    //look for emotion events
    rc = em_check(emotions, &emotion_event);
  
    //react to events if there was one
    if(!rc) {
     
      //get the correct set of reations
      em_action = &RC_EM_ACTION[emotion_event.emotion];
     
      //do full gesture if condition is full
      if(emotion_event.type == EM_COND_FULL) {
        gsi_react(&em_action->full_gesture, phhandle);
      }
    
    //do low gesture if condition is low
      else if(emotion_event.type == EM_COND_LOW) {
        gsi_react(&em_action->low_gesture, phhandle);
      }
    
      //do critical gesture if condition is critical
      else {
        gsi_react(&em_action->critical_gesture, phhandle);
        
        //if critical mode is kill end main loop
        if(em_action->critical_mode == MN_END) {
          running = 0;
        }
        
        //check for other mode changes
        else if(em_action->critical_mode) {
          mn_run(em_action->critical_mode, emotions, notifications, phhandle);
        }
      }
    }
    
    //Check if the queue is has notifications
    if(qu_size(notifications) > 0) {
      //get notification events
      message = qu_pop(notifications);
  
      //do a gesture and print the text on the screen
      if(message) {
        //return errors to parent mode 
        if(message->error) {
          return message->error;
        }
        gsi_sound("computing", 1);
        gsi_react(&RC_MSG_ACTION, phhandle);
        gsi_printLCD(message->text, phhandle);
      }
    }
  
    sleep(RC_MAIN_PAUSE);
  }
  
  return UT_ERR_CLOSE;
}

ut_ErrorCode rc_sleep(em_State *emotions, qu_Queue *notifications, ph_handle *phhandle) {
  nt_Message *message;
  em_Event emotion_event; 
  em_condition condition;
  in_input_type input_event;
  int asleep, rc;

  //keep looping until woken up
  asleep = 1;
  
  while(asleep) {

    //look for input events
    input_event = in_get_input();
  
    //wake up on button press or force sensor
    if(input_event == INPT_LEFT_HAND || input_event == INPT_RIGHT_HAND || input_event == INPT_FORCE) {
      asleep = 0;
    }
    
    //shutdown on power button
    if(input_event == INPT_POWER_OFF) {
      return UT_ERR_CLOSE;
    }
 
    //look for emotion events but don't respond to them
    rc = em_check(emotions, &emotion_event);
  
    //Check if the queue is has notifications
    if(qu_size(notifications) > 0) {
      //get notification events
      message = qu_pop(notifications);
  
      //do a gesture and print the text on the screen
      if(message) {
        //return errors to parent mode 
        if(message->error) {
          return message->error;
        }
        gsi_printLCD(message->text, phhandle);
      }
    }
    
    //get condition of primary sleep emotion
    if(rc_sleep_action.primary_emotion.emotion != MN_EM_NONE) {
      condition = em_get_condition(emotions, rc_sleep_action.primary_emotion.emotion);
    }
    
    //if emotion is none use full gesture
    else {
      condition = EM_COND_FULL;
    }
    
    //update primary emotion
    rc = em_react(emotions, &rc_sleep_action.primary_emotion);
    
    //check for errors in reaction table
    assert(rc ==0);
    
    //update secondary emotion
    rc = em_react(emotions, &rc_sleep_action.secondary_emotion);
    
    //check for errors in reaction table
    assert(rc ==0);
    
    //if emotion was full do full gesture
    if(condition == EM_COND_FULL) {
      gsi_react(&rc_sleep_action.full_gesture, phhandle);
      
      //check for wake up signal
      if(rc_sleep_action.mode == MN_END) {
        asleep = 0;
      }
    
      //if the input triggers a mode change switch to that mode
      else if(rc_sleep_action.mode) {
        rc = mn_run(rc_sleep_action.mode, emotions, notifications, phhandle);
      
        //return errors to parent mode
        if(rc) {
          return rc;
        }
      }
    }
    
    //if it was normal do normal gesture
    else if(condition == EM_COND_NORMAL) {
      gsi_react(&rc_sleep_action.normal_gesture, phhandle);
    }
    
    //otherwise do low gesture
    else {
      gsi_react(&rc_sleep_action.low_gesture, phhandle);
    }
  
    sleep(RC_SLEEP_PAUSE);
  }
  
  //wake up animation
  gsi_raise_arms(phhandle);
  
  return UT_ERR_NONE;
}

#include <stdio.h>
#include <assert.h>
#include "simulation_input.h"
#include "utility.h"
#include "gesture_interface.h"


//Need to use a global variable here to emulate the input module
smi_Reader *sm_input_reader;


int ph_init(const char *config_path, ph_handle *phhandle) {
  return UT_ERR_NONE;
}

int gsi_gesture_init(ph_handle *handle) {
  return UT_ERR_NONE;
}

int gsi_gesture_close(ph_handle *handle) {
  return UT_ERR_NONE;
}

int in_input_init(ph_handle *handle) {

  //create an input reader
  sm_input_reader = smi_init();	
  return UT_ERR_NONE;
}

int ph_destruct(ph_handle *phhandle) {
  smi_destroy(sm_input_reader);
  return 0;
}

int in_get_input(void) {
  in_input_type last_input;
  
  assert(sm_input_reader);
  
  //get input from the reader
  smi_read(sm_input_reader, &last_input);
  
  //return the input
  return last_input;
}

int gsi_react(const gsi_Reaction *resp, ph_handle *phhandle) {
	
  //check message is not null or null string
  if(resp->message && *(resp->message)) {
  	
  	//print message to the lcd screen
    gsi_printLCD(resp->message, phhandle);
  }
  
  //if a gesture is given run it
  if(resp->gesture) {
    resp->gesture(phhandle);
  }
  
  return 0;
}

int gsi_printLCD(const char* str, ph_handle *phhandle) {
  printf("-- %s --\n", str);
  
  return 0;
}

int gsi_happy_level1(ph_handle *phhandle) {
  printf("*smiles*\n");
  return 0;
}

int gsi_fun_level1(ph_handle *phhandle) {
  printf("*fun*\n");
  return 0;
}

int gsi_sound(const char *sound, int repeat) {
  printf("*sound*\n");
  return 0;
}

int gsi_test(ph_handle *phhandle) {
  printf("*test*\n");
  return 0;
}

int gsi_shake_head(ph_handle *phhandle) {
  printf("*shakes head*\n");
  return 0;
}

int gsi_move_arms(ph_handle *phhandle) {
  printf("*moves arms*\n");
  return 0;
}

int gsi_raise_arms(ph_handle *phhandle)  {
  printf("*raises arms*\n");
  return 0;
}

int gsi_eyeflash(ph_handle *phhandle) {
  printf("*flashes eyes*\n");
  return 0;
}

int gsi_wave_right(ph_handle *phhandle) {
  printf("*waves with right hand*\n");
  return 0;
}

int gsi_wave_left(ph_handle *phhandle) {
  printf("*waves with left hand*\n");
  return 0;
}

int gsi_raise_right(ph_handle *phhandle) {
  printf("*raises right hand*\n");
  return 0;
}
int gsi_raise_left(ph_handle *phhandle) {
  printf("*raises left hand*\n");
  return 0;
}

#include <phidget21.h>

extern int ph_init(PhidgetHandle *phidgets, const char *config);

extern int ph_destruct(void);

/*Servo Header*/
extern CPhidgetAdvancedServoHandle ph_get_servo_handle(void);
CPhidgetAdvancedServoHandle ph_servo_initialise(void);
int ph_servo_DetachHandler(CPhidgetHandle phidget_servo, void *p);
int ph_servo_AttachHandler(CPhidgetHandle phidget_servo, void *p);
int ph_servo_ErrorHandler(CPhidgetHandle phidget_servo, void *p, int ErrorCode, const char *Description);
int ph_servo_close(CPhidgetHandle);

/*RFID Header*/

int ph_RFID_AttachHandler(CPhidgetHandle RFID, void *userptr);
int ph_RFID_DetachHandler(CPhidgetHandle RFID, void *userptr);
int ph_RFID_ErrorHandler(CPhidgetHandle RFID, void *userptr, int ErrorCode, const char *unknown);
CPhidgetRFIDHandle ph_RFID_openrfid(void);
CPhidgetRFIDHandle ph_get_RFID_handle (void);
void ph_RFID_closerfid(void);

/*Interface Kit Header*/
CPhidgetInterfaceKitHandle ph_kit_openkit(void);
void ph_kit_closekit(void);
int ph_kit_AttachHandler(CPhidgetHandle IFK, void *userptr);
int ph_kit_DetachHandler(CPhidgetHandle IFK, void *userptr);
int ph_kit_ErrorHandler(CPhidgetHandle IFK, void *userptr, int ErrorCode, const char *unknown);

CPhidgetInterfaceKitHandle ph_get_kit_handle (void);

int ph_lcd_ErrorHandler(CPhidgetHandle TXT, void *userptr, int ErrorCode, const char *Description);
int ph_lcd_DetachHandler(CPhidgetHandle TXT, void *userptr);
int ph_lcd_AttachHandler(CPhidgetHandle TXT, void *userptr);
CPhidgetTextLCDHandle ph_lcd_initialise(void);
CPhidgetTextLCDHandle ph_get_lcd_handle(void);

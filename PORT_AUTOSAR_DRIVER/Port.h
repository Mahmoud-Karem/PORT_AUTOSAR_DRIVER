 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mahmoud Karem Zamel
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR */
#define PORT_VENDOR_ID    (1112U)

/* Port Module Id */
#define PORT_MODULE_ID    (222U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Dio Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

#include "Std_Types.h"

/* AUTOSAR version checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION) != (PORT_AR_RELEASE_MAJOR_VERSION))\
 || ((STD_TYPES_AR_RELEASE_MINOR_VERSION) != (PORT_AR_RELEASE_MINOR_VERSION))\
 || ((STD_TYPES_AR_RELEASE_PATCH_VERSION) != (PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */ 
#include "Port_Cfg.h"
   
/* AUTOSAR version checking between Port Pre-Compile Configurations and Port Modules */   
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION) != (PORT_AR_RELEASE_MAJOR_VERSION))\
 || ((PORT_CFG_AR_RELEASE_MINOR_VERSION) != (PORT_AR_RELEASE_MINOR_VERSION))\
 || ((PORT_CFG_AR_RELEASE_PATCH_VERSION) != (PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Cfg.h does not match the expected version"
#endif
   
/* Software version checking between Port Pre-Compile Configurations and Port Modules */ 
#if ((PORT_CFG_SW_MAJOR_VERSION) != (PORT_SW_MAJOR_VERSION))\
 || ((PORT_CFG_SW_MINOR_VERSION) != (PORT_SW_MINOR_VERSION))\
 || ((PORT_CFG_SW_PATCH_VERSION) != (PORT_SW_PATCH_VERSION))
#error "The Software version of Port_Cfg.h does not match the expected version"
#endif   
   
/* Non AUTOSAR files */
#include "Common_Macros.h"
   
/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for PORT Initialization */
#define PORT_INIT_SID                                      (uint8)0x00
   
/* Service ID for setting PORT pin Direction */ 
#define PORT_SET_PIN_DIRECTION_SID                         (uint8)0x01
   
/* Service ID for refreshing PORT Direction */    
#define PORT_REFRESH_PORT_DIRECTION_SID                    (uint8)0x02
   
/* Service ID for getting PORT version */    
#define PORT_GET_VERSION_INFO_SID                          (uint8)0x03
   
/* Service ID for setting PORT pin mode */    
#define PORT_SET_PIN_MODE_SID                              (uint8)0x04
   

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code to report Incorrect Port Pin ID passed */
#define PORT_E_PARAM_PIN                                   (uint8)0x0A
 
/* DET code to report that Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE                      (uint8)0x0B

/* DET code to report API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG                                (uint8)0x0C
   
/* DET code to report API Port_SetPinMode service called when mode is invalid */
#define PORT_E_PARAM_INVALID_MODE                          (uint8)0x0D  
   
/* DET code to report API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE                           (uint8)0x0E
   
/* DET coed to report API service called without module initialization */
#define PORT_E_UNINIT                                      (uint8)0x0F
   
/* DET coed to report APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER                               (uint8)0x10
 
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/
   
/* Type definition for the symbolic name of a port pin */
typedef uint8 Port_PinType;

/* Type definition for Possible directions of a port pin */
typedef enum { 
        PORT_PIN_IN,PORT_PIN_OUT
    }Port_PinDirectionType;

/* Type definition for pin internal resistor */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* Type definition for Different port pin modes */
typedef uint8 Port_PinModeType;

typedef enum 
{
  DIRECTION_OFF,DIRECTION_ON
}PORT_PinDirectionChangeable;

typedef enum
{
  MODE_CHANGE_OFF,MODE_CHANGE_ON
}Port_PinModeChangeable;
                         
/* Description: Structure to configure each individual PIN:
 *      1. the number of pin in the Port
 *		2. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *		3. the direction of pin --> INPUT or OUTPUT
 *      4. the mode of pin (GPIO,ADC,UART,etc.)
 *      5. the internal resistor --> Disable, Pull up or Pull down
 */
typedef struct{
 uint8 port_num;
 uint8 pin_num;
 Port_PinDirectionType direction;
 Port_InternalResistor resistor;
 PORT_PinDirectionChangeable direction_changeable;
 uint8 initial_value;
 Port_PinModeType Mode;
 Port_PinModeChangeable mode_changeable ;
}Port_ConfigChannel;

/* Data Structure to Initialize the Port Driver */
typedef struct{
  Port_ConfigChannel Channels[PORT_CONFIGURED_CHANNELS];
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function for Initialization of the Port Driver module */
void Port_Init(const Port_ConfigType* ConfigPtr);
   
/* Function for Setting the port pin direction */
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction);
#endif

/* Function for Refreshing port direction */
void Port_RefreshPortDirection( void );

/* Function for Returning the version information of this module */
#if (PORT_VERSION_INFO_API  == STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );
#endif

/* Function for Setting the port pin mode */
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode); 
  
/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const  Port_ConfigType Port_Configuration;

#endif /* PORT_H */

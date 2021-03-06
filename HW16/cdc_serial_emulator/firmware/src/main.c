/*******************************************************************************
  MPLAB Harmony Project Main Source File

  Company:
    Microchip Technology Inc.
  
  File Name:
    main.c

  Summary:
    This file contains the "main" function for an MPLAB Harmony project.

  Description:
    This file contains the "main" function for an MPLAB Harmony project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state 
    machines of all MPLAB Harmony modules in the system and it calls the 
    "SYS_Tasks" function from within a system-wide "super" loop to maintain 
    their correct operation. These two functions are implemented in 
    configuration-specific files (usually "system_init.c" and "system_tasks.c")
    in a configuration-specific folder under the "src/system_config" folder 
    within this project's top-level folder.  An MPLAB Harmony project may have
    more than one configuration, each contained within it's own folder under
    the "system_config" folder.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

//Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "system/common/sys_module.h"   // SYS function prototypes
#include <stdio.h>
#include <xc.h>          // processor SFR definitions
#include <sys/attribs.h> // __ISR macro

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all MPLAB Harmony modules, including application(s). */
    SYS_Initialize ( NULL );
    // set B5 as OC1
    RPB5Rbits.RPB5R = 0b0101;       // set B5 to OC2
    OC2CONbits.OCTSEL = 1;          // Select Timer3 for comparison
    T3CONbits.TCKPS = 0;            // Timer3 prescaler 1:1
    PR3 = 3999;                     // period = (PR2+1) * N * 12.5 ns = 20 kHz
    TMR3 = 0;                       // initial TMR3 count is 0

    OC2CONbits.OCM = 0b110;         // PWM mode with no fault pin; other OC2CON bits are defaults

    OC2RS = 2500;                   // duty cycle = OC2RS/(PR3+1) = 50%
    OC2R = 2500;

    T3CONbits.ON = 1;               // turn on Timer3
    OC2CONbits.ON = 1;              // turn on OC2


    // set B15 as OC1
    RPB15Rbits.RPB15R = 0b0101;     // set B15 to OC1

    OC1CONbits.OCTSEL = 0;          // Select Timer2 for comparison
    T2CONbits.TCKPS = 0;            // Timer2 prescaler 1:1
    PR2 = 3999;                     // period = (PR2+1) * N * 12.5 ns = 20 kHz
    TMR2 = 0;                       // initial TMR2 count is 0

    OC1CONbits.OCM = 0b110;         // PWM mode with no fault pin; other OC1CON bits are defaults

    OC1RS = 2500;                   // duty cycle = OC1RS/(PR2+1) = 50%
    OC1R = 25000;

    T2CONbits.ON = 1;               // turn on Timer2
    OC1CONbits.ON = 1;              // turn on OC1

    //A Phase: B7 - Digital Output
    TRISBbits.TRISB7 = 0;      // 0 is output, 1 is input

    //B Phase: B14 - Digital Output
    ANSELBbits.ANSB14 = 0;      // 0 for digital, 1 for analog
    TRISBbits.TRISB14 = 0;      // 0 is output, 1 is input

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );

    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/


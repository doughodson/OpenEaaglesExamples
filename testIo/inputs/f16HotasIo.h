//------------------------------------------------------------------------------
// Example F-16 Stick/Throttle I/O definitions -- 
//
// Notes:
//    1) Numbering of both analog and bit channels start at one(1).
//    2) This file defines channels for both the C++ code and the Eaagles
//       input files, so use only C pre-processor directives only.
//------------------------------------------------------------------------------
#ifndef __F16_HOTAS_IO_DEF_H__
#define __F16_HOTAS_IO_DEF_H__

// analog input channels
#define ROLL_AI            1
#define PITCH_AI           2
#define THROTTLE_AI        3
#define RUDDER_AI          4
#define ANT_ELEV_AI        5
#define RANGE_AI           6
#define CURSOR_X_AI        7
#define CURSOR_Y_AI        8

// input bit channels
#define TRIGGER_SW1         1
#define TRIGGER_SW2         2
#define PICKLE_SW           3

#define PINKY_SW            4
#define PADDLE_SW           5
#define NWS_SW              6

#define TMS_UP_SW           7
#define TMS_DOWN_SW         8
#define TMS_LEFT_SW         9
#define TMS_RIGHT_SW       10
#define TMS_PUSH_SW        11

#define DMS_UP_SW          12
#define DMS_RIGHT_SW       13
#define DMS_DOWN_SW        14
#define DMS_LEFT_SW        15
#define DMS_PUSH_SW        16

#define CMS_UP_SW          17
#define CMS_RIGHT_SW       18
#define CMS_DOWN_SW        19
#define CMS_LEFT_SW        20
#define CMS_PUSH_SW        21

#define TRIM_PITCH_DOWN_SW 22
#define TRIM_PITCH_UP_SW   23
#define TRIM_ROLL_RIGHT_SW 24
#define TRIM_ROLL_LEFT_SW  25
#define TRIM_PUSH_SW       26

#define RDR_CUR_ENB_SW     27
#define RNG_UNCAGE_SW      28
#define MSL_MODE_SW        29
#define DOG_MODE_SW        30
#define SB_EXT_SW          31
#define SB_RET_SW          32
#define IFF_IN_SW          33
#define IFF_OUT_SW         34
#define VHF_SW             35
#define UHF_SW             36

#endif

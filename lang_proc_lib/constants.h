#ifndef CONSTANTS_H
#define CONSTANTS_H

//=====================//
//  Numeric constants  //
//=====================//

const int IO_BUFFER_SIZE        = 32;
const int OUTPUT_NUMBER_SYSTEM  = 10;
const int INPUT_NUMBER_SYSTEM   = 10;
const int STACK_FRAME_OFFSET    = 0x10;
const int ELEMENT_SIZE          = 8;

//=====================//
//   Label constants   //
//=====================//
char ATOI[]                     = "atoi";
char ATOI_LOOP[]                = "atoi_loop";
char ATOI_LOOP_END[]            = "atoi_loop_end";

char ITOA[]                     = "itoa";
char RENOMINATION_LOOP[]        = ".renomLoop";
char RENOMINATION_LOOP_END[]    = ".renomLoopEnd";

char START_LABEL[]              = "_start";

#endif
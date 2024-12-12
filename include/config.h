#ifndef _CONFIG_H_
#define _CONFIG_H_

// Enables #warning and compile time extra messages (can also fail compilation
// in some cases)
#ifndef DEBUG_COMPILE
#define DEBUG_COMPILE 1
#endif

// Enables runtime print messages
#ifndef DEBUG_MESSAGES
#define DEBUG_MESSAGES 1
#endif

// Strips extra code
#ifndef OPTIMIZE
#define OPTIMIZE 0
#endif

#endif //_CONFIG_H_

#ifndef _CONFIG_H_
#define _CONFIG_H_

// Enables #warning and compile time extra messages (can also fail compilation
// in some cases)
#ifndef DEBUG_COMPILE
#define DEBUG_COMPILE 1
#endif

// Enables runtime print messages
// If set to 0 functions will completely be stripped
// If set to 1 debug messages still can be turned off runtime by setting DEBUG
// to 0
#ifndef DEBUG_MESSAGES
#define DEBUG_MESSAGES 1
#endif

// Strips extra code
#ifndef OPTIMIZE
#define OPTIMIZE 0
#endif

// Enables function tracing (very verbose)
#ifndef TRACE
#define TRACE 1
#endif

#endif //_CONFIG_H_

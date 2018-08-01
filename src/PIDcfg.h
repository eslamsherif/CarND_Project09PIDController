#ifndef PID_CFG_H
#define PID_CFG_H

#define DEBUG_GENERAL

#ifdef DEBUG_GENERAL
// #define DEBUG_INITIALIZATION
// #define DEBUG_UPDATEERROR
#define DEBUG_TOTALERROR
#endif

#define PROPORTIONAL_GAIN (0.6)
#define DIFFERENTIAL_GAIN (0.001)
#define INTEGRAL_GAIN     (15.0)

#endif /* PID_CFG_H */
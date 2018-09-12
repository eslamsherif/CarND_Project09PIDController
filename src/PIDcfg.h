#ifndef PID_CFG_H
#define PID_CFG_H

#define DEBUG_GENERAL

#ifdef DEBUG_GENERAL
// #define DEBUG_INITIALIZATION
// #define DEBUG_UPDATEERROR
// #define DEBUG_TOTALERROR
#endif

#define PROPORTIONAL_GAIN (0.18)
#define DIFFERENTIAL_GAIN (0.005)
#define INTEGRAL_GAIN     (1.06)

#endif /* PID_CFG_H */
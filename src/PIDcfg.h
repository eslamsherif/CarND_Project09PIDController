#ifndef PID_CFG_H
#define PID_CFG_H

#define DEBUG_GENERAL

#ifdef DEBUG_GENERAL
#define DEBUG_INITIALIZATION
#endif

#define PROPORTIONAL_GAIN (1U)
#define DIFFERENTIAL_GAIN (1U)
#define INTEGRAL_GAIN     (1U)

#endif /* PID_CFG_H */
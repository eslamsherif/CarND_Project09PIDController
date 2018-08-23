#ifndef PID_H
#define PID_H

#include "PIDcfg.h"

class PID {
private:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  double previous_cte;

  double max_out;
  double min_out;

public:
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double __Kp = PROPORTIONAL_GAIN,
            double __Ki = DIFFERENTIAL_GAIN,
            double __Kd = INTEGRAL_GAIN,
            double __min_out = -1.0,
            double __max_out = 1.0);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte, double __dt);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /* Get Mean Output */
  double Get_Mean_Output();
};

#endif /* PID_H */

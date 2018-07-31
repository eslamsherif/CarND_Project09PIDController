#include "PID.h"

#ifdef DEBUG_GENERAL
#include <iostream>
using namespace std;
#endif


/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double __Kp, double __Ki, double __Kd)
{
  Kp = __Kp;
  Ki = __Ki;
  Kd = __Kd;

  p_error = 0UL;
  i_error = 0UL;
  d_error = 0UL;

  previous_cte   = 0UL;

  #ifdef DEBUG_INITIALIZATION
  cout << "PID Init complete." << endl;
  cout << "Used Proportional gain = " << Kp << endl;
  cout << "Used Integral gain = " << Ki << endl;
  cout << "Used Differential gain = " << Kd << endl;
  #endif
}

void PID::UpdateError(double cte)
{
  double dt = 1UL;

  if(0U == previous_cte)
  {
    previous_cte = cte;
  }

  p_error  = cte;
  i_error += cte;
  d_error  = ( (cte - previous_cte) / dt );

  previous_cte = cte;

  #ifdef DEBUG_UPDATEERROR
  cout << "CTE           " << cte << endl;
  cout << "p_error     = " << p_error << endl;
  cout << "i_error     = " << i_error << endl;
  cout << "d_error     = " << d_error << endl;
  #endif
}

double PID::TotalError()
{
  double PTerm = Kp * p_error;
  double ITerm = Ki * i_error;
  double DTerm = Kd * d_error;

  double toterr = -1 * (PTerm + ITerm + DTerm);

  #ifdef DEBUG_TOTALERROR
  cout << "PTerm       = " << PTerm << endl;
  cout << "ITerm       = " << ITerm << endl;
  cout << "DTerm       = " << DTerm << endl;
  cout << "Total error = " << toterr << endl;
  #endif

  return toterr;
}


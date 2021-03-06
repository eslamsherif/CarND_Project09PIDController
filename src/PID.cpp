#include "PID.h"
#include <math.h>

#ifdef DEBUG_GENERAL
#include <iostream>
using namespace std;
#endif

PID::PID() {}

PID::~PID() {}

void PID::Init(double __Kp, double __Ki, double __Kd, double __min_out, double __max_out)
{
  Kp = __Kp;
  Ki = __Ki;
  Kd = __Kd;

  max_out = __max_out;
  min_out = __min_out;

  p_error = 0UL;
  i_error = 0UL;
  d_error = 0UL;

  previous_cte   = 0UL;

  #ifdef DEBUG_INITIALIZATION
  cout << "Module PID > Init complete." << endl;
  cout << "Used Proportional gain = " << Kp << endl;
  cout << "Used Integral gain = " << Ki << endl;
  cout << "Used Differential gain = " << Kd << endl;
  #endif
}

void PID::UpdateError(double __cte, double __dt)
{
  if(0U == previous_cte)
  {
    previous_cte = __cte;
  }

  p_error  = __cte;
  i_error += __cte;
  d_error  = ( (__cte - previous_cte) / __dt );

  previous_cte = __cte;

  #ifdef DEBUG_UPDATEERROR
  cout << "CTE           " << __cte << endl;
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

  #define SATURATE

  #ifdef SATURATE
  if(toterr > max_out)
  {
    toterr = max_out;
  }
  else if(toterr < min_out)
  {
    toterr = min_out;
  }
  #endif

  #ifndef SATURATE
  /* testing using tanh to see if it produce better result than the saturation solution */
  toterr = tanh(toterr);
  #endif

  #ifdef DEBUG_TOTALERROR
  cout << "PTerm       = " << PTerm << endl;
  cout << "ITerm       = " << ITerm << endl;
  cout << "DTerm       = " << DTerm << endl;
  cout << "Total error = " << toterr << endl;
  #endif

  return toterr;
}

double PID::Get_Mean_Output()
{
    double max_mod = fabs(max_out);
    double min_mod = fabs(min_out);

    if( max_mod != min_mod )
    {
        cout << "Mean Calculation for ASymitrical Output range is not supported." << endl;
        return 0.0;
    }
    else
    {
        return ( max_mod + min_mod ) / (4.0);
    }
}
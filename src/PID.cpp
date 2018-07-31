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
  
  #ifdef DEBUG_INITIALIZATION
  cout << "PID Init complete." << endl;
  cout << "Used Proportional gain = " << Kp << endl;
  cout << "Used Integral gain = " << Ki << endl;
  cout << "Used Differential gain = " << Kd << endl;
  #endif
}

void PID::UpdateError(double cte)
{
}

double PID::TotalError()
{
}


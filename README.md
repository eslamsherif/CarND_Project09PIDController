# CarND_Project09PIDController

Solution for Udacity Self driving car Nano degree eigthth project: PID controller Project.

---

Abbreviations:

PID: Proportional, Integratl and Derivative controller

CTE: Cross track error

---

## Objective

Implement a PID controller controlling a car around the udacity simulator track. The pass criteria is to complete one revolution around the track.

---

### Reflection

This project aims to control a car movement, i.e. steering angle and throttle/brakes, by implementing a PID controller. Udacity simulated track is the testing ground for the controller.

The simulator provide a CTE value and a speed measuerments of the car as an input, the CTE is used as an input to the PID controller responsible for the steering angle.

The speed is provided as input to the control code responsible for the throttle value.

---

### Theory

PID controller consist of three main parts:
  * Proportional:
    - Represent the response to the current error allowing for fast response but can lead to osciallations because it doesn't take previous or future measuerments in consideration.
  * Integral:
    - Represent the resposne for all past errors allowing for addressing residual errors building up in our system state without being detected.
  * Derivative:
    - Represent the response for the rate of change of error, i.e. how fast are we approching zero error state.

each part needs a tuning parameter to accomodate for different system parameters, several methods are available to tune those parameters as:
  * Ziegler–Nichols tuning: tune the parameters using a set of experiments and theortical calculations, usually produce a theortically acceptable but not optimum state.
  * Manual tuning: tune the parameters manually till an acceptable state is reached, usually a method as Ziegler–Nichols is used to reach a set of initial parameters and then further optimized manually allowing to reach a more optimal state.
  * Twiddle: an automatic process using a simulated model to exhaustively search all the possible parameter space till it reach the optimal parameters, it is very time consuming and very dependent on the simulated model accuracy however due to the low number of parameters, only 3, it can be used on this project with no issues.

---

### Implementation

Udacity have provided most of the control code as:
  * Communication between PID and Udacity simulator.
  * Parsing of the simulator input.
  
I have made some modifications to this control code to support both twiddle and actual PID runs and the input parameters can be changed manually from command line to speed up tuning process. 
  
I had to implement the following parts:
  * PID: Complete implementation of the PID controller consisting of:
    - PID state initialization
    - PID error update handling
    - PID output control.
    
I have added some pre-processor switch as well to:
  * Different handling of the output control.
  * Enable various level of debugging of the code.

- Output Control:
The simulator accepts values within a certain range as inputs so the output of the PID controller must be adjusted for this.

I tried first with a simple saturation model so whenever the maximum value is exceeded any excess values are ignored and only the max is outputted and same for min values.

I then thought about using the same normalization method as in the NN in first term using the tanh function since it maps the input within the [-1,1] range autmatically.

I have tested with both models exensivelly and finalized that the saturation model is sufficient and the tanh approch decrease the requested steering angle causing us to some time overshoot the desired output, however in can be considered as an optimization approch as it eliminate a branch operation and the decrease in accuracy can be handled using the different tuning parameters of the PID.

- The Tuning process:
I tried to use twiddle at first but the simulator kept crashing in the middle, it works fine with the normal PID so I expect i provide some wrong input causing the crash but I couldn't manage to find the error within the remaining time frame so I reverted to manual tuning.

- The Throttle control:
Udacity suggested using a different PID for the throttle/brake control, however I prefered to use a much more simpler approch mimicing the way humans drive below is the psudeo code:
  1) If in a critical situation (steering angle very large) --> Apply brakes with intensity depending on the actual situation.
  2) if turning but no critical situation --> reduce speed without applying brakes.
  3) if moving in straight line --> apply full throttle.
  4) if stopped --> apply full throttle.

---

### Results

The car is able to traverse the whole track as requested, I have made a video with two laps shown to show that the PID can handle the complete track at different speeds.

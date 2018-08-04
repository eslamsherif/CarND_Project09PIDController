#include <uWS/uWS.h>
#include <iostream>
#include "json.hpp"
#include "PID.h"
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <chrono>

using namespace std;

static double Thrttle_u;
static clock_t prevtime;

/* Tuning Specific variables */
static double tol;
static unsigned long iterThreshold;

const uint64_t nanos()
{
  /* Code obtained from here https://stackoverflow.com/questions/21856025/getting-an-accurate-execution-time-in-c-micro-seconds */
  uint64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::
                  now().time_since_epoch()).count();
  return ns; 
}

// for convenience
using json = nlohmann::json;

enum GainIdx
{
  PGain = 1,
  IGain,
  DGain,
  Throttle
};

enum TuneStage
{
  INCREMENT_TERM,
  DECREMENT_TERM,
  DEFINE_NEXT_MARGIN
};

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
std::string hasData(std::string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != std::string::npos) {
    return "";
  }
  else if (b1 != std::string::npos && b2 != std::string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

void tune_PID(void)
{
  uWS::Hub h;
  PID StrAngPid;

  // static double param[3]  = {0, 0, 0};
  // static double dparam[3] = {1, 1, 1};

  // static double best_Error;
  static double accu_Error = 0U;
  // static bool isFirstTime = true;
  // static unsigned int index = 0U;
  // static unsigned int stage = 0U;

  static unsigned long itrCnt = 0U;

  Thrttle_u = 0.3;
  // prevtime = nanos();

  // StrAngPid.Init(param[0], param[1], param[2], -1.0, 1.0);
  StrAngPid.Init();

  h.onMessage([&StrAngPid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event

    if (length && length > 2 && data[0] == '4' && data[1] == '2')
    {
      auto s = hasData(std::string(data).substr(0, length));
      if (s != "")
      {
        auto j = json::parse(s);
        std::string event = j[0].get<std::string>();
        if (event == "telemetry")
        {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<std::string>());
          // double speed = std::stod(j[1]["speed"].get<std::string>());
          // double angle = std::stod(j[1]["steering_angle"].get<std::string>());

          StrAngPid.UpdateError(cte, (nanos() - prevtime) / 1000000000.0);

          double steer_value    = StrAngPid.TotalError();
          // double steer_value    = 0.0;
          double throttle_value = Thrttle_u - (Thrttle_u * fabs(steer_value));
          // double throttle_value = 5.0;

          // accu_Error += fabs(steer_value);
          itrCnt = (itrCnt + 1U) % iterThreshold;
          cout << "Iter: " << itrCnt << " ,error: " << accu_Error << endl;

          // if(0U == itrCnt)
          // {
            // if(true == isFirstTime)
            // {
              // best_Error = accu_Error;
              // cout << "best error = " << best_Error << endl;

              // isFirstTime = false;
            // }

            // if( (dparam[0] + dparam[1] + dparam[2]) < tol )
            // {
              // cout << "PID tuning finished." << endl;
              // cout << "PTerm = " << param[0];
              // cout << "ITerm = " << param[1];
              // cout << "DTerm = " << param[2];

              // exit(0);
            // }
            // else
            // {
              // switch(stage)
              // {
                // case DEFINE_NEXT_MARGIN:
                  // cout << "decrement stage error = " << accu_Error << endl;
                  // if(accu_Error < best_Error)
                  // {
                    // /* decreasing decreased the error, continue in this direction */
                    // best_Error = accu_Error;
                    // cout << "New Best Error" << best_Error << endl;
                    // dparam[index] *= 1.1;
                    // cout << "decrement stage succ, dparam[" << index << "] = " << dparam[index] << endl;
                  // }
                  // else
                  // {
                    // /* neither increasing or decreasing it is good, lower search margin */
                    // param[index] += dparam[index];
                    // dparam[index] *= 0.9;
                    // cout << "both stage fail, dparam[" << index << "] = " << dparam[index] << endl;
                  // }

                  // index = (index + 1) % 3;
                  // /* No break, fall through intentional */
                // case INCREMENT_TERM:
                  // /* Try to Increment one param and calculate new error */
                  // param[index] += dparam[index];
                  // cout << "increment stage param[" << index << "] = " << param[index] << endl;
                  // StrAngPid.Init(param[0], param[1], param[2], -1.0, 1.0);

                  // stage = DECREMENT_TERM;
                // break;
                // case DECREMENT_TERM:
                  // cout << "increment stage error = " << accu_Error << endl;
                  // if(accu_Error < best_Error)
                  // {
                    // /* incrementing decreased the error continue in this direction */
                    // best_Error = accu_Error;
                    // cout << "New Best Error" << best_Error << endl;
                    // dparam[index] *= 1.1;
                    // cout << "increment stage succ, dparam[" << index << "] = " << dparam[index] << endl;

                    // index = (index + 1) % 3;
                    // /* not best coding pactice as i am basically duplicating the increment term stage code */
                    // param[index] += dparam[index];
                    // cout << "increment stage param[" << index << "] = " << param[index] << endl;
                    // StrAngPid.Init(param[0], param[1], param[2], -1.0, 1.0);
                  // }
                  // else
                  // {
                    // /* incrementing increased the error, try decreasing it */
                    // param[index] -= (2.* dparam[index]);
                    // cout << "decrement stage param[" << index << "] = " << param[index] << endl;
                    // StrAngPid.Init(param[0], param[1], param[2], -1.0, 1.0);

                    // stage = DEFINE_NEXT_MARGIN;
                  // }
                // break;
              // }
            // }

            // /* Reset SIM */
            // accu_Error = 0U;
            // auto msg = "42[\"reset\",{}]";
            // ws.send(msg, strlen(msg), uWS::OpCode::TEXT);
          // }

          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = throttle_value;
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          // std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
          prevtime = nanos();
        }
      }
    }
  });

  // We don't need this since we're not using HTTP but if it's removed the program
  // doesn't compile :-(
  h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
    const std::string s = "<h1>Hello world!</h1>";
    if (req.getUrl().valueLength == 1)
    {
      res->end(s.data(), s.length());
    }
    else
    {
      // i guess this should be done more gracefully?
      res->end(nullptr, 0);
    }
  });

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port))
  {
    std::cout << "Listening to port " << port << std::endl;
  }
  else
  {
    std::cerr << "Failed to listen to port" << std::endl;
  }

  h.run();
}

void run_PID(const bool init, char *argv[])
{
  uWS::Hub h;
  PID StrAngPid;

  if(true == init)
  {
    double Gp = atof(argv[PGain]);
    double Gi = atof(argv[IGain]);
    double Gd = atof(argv[DGain]);

    StrAngPid.Init( Gp , Gi, Gd, -1.0, 1.0);
    Thrttle_u = atof(argv[Throttle]);
  }
  else
  {
    StrAngPid.Init();
    Thrttle_u = 0.3;
  }

  prevtime = nanos();

  h.onMessage([&StrAngPid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
    /* "42" at the start of the message means there's a websocket message event. *
     * The 4 signifies a websocket message                                       *
     * The 2 signifies a websocket event                                         */

    if (length && length > 2 && data[0] == '4' && data[1] == '2')
    {
      auto s = hasData(std::string(data).substr(0, length));
      if (s != "") {
        auto j = json::parse(s);
        std::string event = j[0].get<std::string>();
        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<std::string>());
          // double speed = std::stod(j[1]["speed"].get<std::string>());
          // double angle = std::stod(j[1]["steering_angle"].get<std::string>());

          cout << "CTE         = " << cte << endl;

          StrAngPid.UpdateError(cte, (nanos() - prevtime) / 1000000000.0);

          double steer_value    = StrAngPid.TotalError();
          double throttle_value = Thrttle_u - (Thrttle_u * fabs(steer_value));

          if(throttle_value == 0.0)
          {
            throttle_value = 0.1;
          }
 
          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = throttle_value;
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
          prevtime = nanos();
        }
      } else {
        // Manual driving
        std::string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }
  });

  h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
    const std::string s = "<h1>Hello world!</h1>";
    if (req.getUrl().valueLength == 1)
    {
      res->end(s.data(), s.length());
    }
    else
    {
      // i guess this should be done more gracefully?
      res->end(nullptr, 0);
    }
  });

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port))
  {
    std::cout << "Listening to port " << port << std::endl;
  }
  else
  {
    std::cerr << "Failed to listen to port" << std::endl;
  }

  h.run();
}

int main(int argc, char *argv[])
{
  switch(argc)
  {
    case 1U: /* Normal Mode No Init */
      run_PID(false, NULL);
    break;
    case ( Throttle + 1U ):
      run_PID(true, argv);
    break;
    case 4U:
      if('T' == argv[1][0])
      {
        tol           = atof(argv[2]);
        iterThreshold = atol(argv[3]);
        tune_PID();
      }
      break;
    default:
    break;
  }

  exit(1);
}

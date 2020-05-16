#include "project/Agent.hpp"
#include "project/Environment.hpp"

#include <iostream>

int main()
{
  Reinforcement::Agent circleAgent{CIRCLE_SIDE};
  Reinforcement::Agent crossAgent{CROSS_SIDE};
  circleAgent.Initialize();
  crossAgent.Initialize();

  Reinforcement::Environment environment;
  environment.Initialize();

  return 0;
}

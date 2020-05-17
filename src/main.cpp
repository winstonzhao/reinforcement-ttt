#include "project/Agent.hpp"
#include "project/Environment.hpp"
#include "project/Util.hpp"

#include <iostream>

int main()
{
  try
  {
    Reinforcement::Agent circleAgent{CIRCLE_SIDE};
    Reinforcement::Agent crossAgent{CROSS_SIDE};
    circleAgent.Initialize();
    crossAgent.Initialize();

    Reinforcement::Environment environment;
    while (true)
    {
      environment.Initialize();

      const Board *initialState = environment.GetState();
      const auto circleInitialMove = circleAgent.GetEpsilonGreedyAction(initialState);
      auto circleObservation = environment.Update(circleInitialMove->first);
      const auto crossInitialMove = crossAgent.GetEpsilonGreedyAction(circleObservation.first);
      auto crossObservation = environment.Update(crossInitialMove->first);

      int circleMove;
      int crossMove;

      while (!environment.IsGameOver())
      {
        circleMove = circleAgent.Observe(crossObservation.first, crossObservation.second);
        circleObservation = environment.Update(circleMove);
        if (environment.IsGameOver())
          break;
        crossMove = crossAgent.Observe(circleObservation.first, circleObservation.second);
        crossObservation = environment.Update(crossMove);
      }

      circleAgent.GameOver(GetGameState(*(environment.GetState())) == CIRCLE_WIN);
      crossAgent.GameOver(GetGameState(*(environment.GetState())) == CROSS_WIN);
    }
  }
  catch (const char *e)
  {
    std::cout << e << std::endl;
  }

  return 0;
}

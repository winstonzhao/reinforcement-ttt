#pragma once
#include <iostream>
#include "project/Constants.hpp"
#include "project/Types.hpp"

namespace Reinforcement
{
  class Agent
  {
  public:
    Agent(bool side);
    void Initialize();
    bool GetSide();
    std::pair<int, double> *GetEpsilonGreedyAction(const Board *board);
    int Observe(const Board *board, int reward);
    void GameOver(bool win);

  private:
    void RecursePossibleBoardStates(Board board, int numO, int numX);
    std::pair<int, double> &GetAction(const Board *board, int action);

  private:
    bool mSide;
    StateActionPairs mStateActionPairs;
    std::vector<std::pair<std::pair<Board, int>, double>> mEligibility;
    Policy mPolicy;
    double mEpsilon = 0.50; // % chance of random exploration
    double mEpsilonDecayRate = 0.90;
    double mGamma = 1;     // discount factor of previous estimations
    double mAlpha = 0.001; // learning rate
    double mLambda = 1;    // discount factor of previous eligibility
    double mSumError = 0;
    std::pair<int, double> *mPrevMove;
    int mSteps = 0;
  };
}; // namespace Reinforcement
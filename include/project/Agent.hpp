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

  private:
    inline char NumToPiece(int num)
    {
      if (num == BLANK)
        return ' ';
      else if (num == CIRCLE)
        return 'O';
      else if (num == CROSS)
        return 'X';
      throw "Invalid number to attempt to convert to a piece";
    }

    void RecursePossibleBoardStates(Board board, int numO, int numX);
    void PrintBoard(Board &board);
    int GetAction(Board *board);

  private:
    bool mSide;
    StateActionPairs mStateActionPairs;
    QMap<int> mEligibility;
    Policy mPolicy;
    double mEpsilon = 0.75;
  };
}; // namespace Reinforcement
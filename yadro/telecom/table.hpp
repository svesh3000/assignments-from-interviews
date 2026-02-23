#ifndef TABLE_HPP
#define TABLE_HPP
#include "time.hpp"

namespace telecom
{
  class Table
  {
  public:
    explicit Table(int num);

    int getNum() const;
    int getRevenue() const;
    const Time & getSumTime() const;

    void startSession(const Time & start);
    void endSession(const Time & end, int cost);

    bool isBusy() const;

  private:
    int num_;
    bool busy_flag_;
    int revenue_;
    Time start_;
    Time sum_time_;
  };
}

#endif

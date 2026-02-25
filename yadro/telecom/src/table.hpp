#ifndef TABLE_HPP
#define TABLE_HPP
#include "time.hpp"

namespace telecom
{
  class Table
  {
  public:
    explicit Table(int num);

    int getNum() const noexcept;
    int getRevenue() const noexcept;
    const Time & getSumTime() const noexcept;

    void startSession(const Time & start);
    void endSession(const Time & end, int cost) noexcept;

    bool isFree() const noexcept;

  private:
    int num_;
    bool free_flag_;
    int revenue_;
    Time start_;
    Time sum_time_;
  };
}

#endif

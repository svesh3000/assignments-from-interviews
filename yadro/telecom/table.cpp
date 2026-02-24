#include "table.hpp"

#include <stdexcept>

#include "time.hpp"

telecom::Table::Table(int num):
  num_(num),
  free_flag_(true),
  revenue_(0),
  start_{0, 0},
  sum_time_{0, 0}
{}

int telecom::Table::getNum() const noexcept
{
  return num_;
}

int telecom::Table::getRevenue() const noexcept
{
  return revenue_;
}

const telecom::Time & telecom::Table::getSumTime() const noexcept
{
  return sum_time_;
}

void telecom::Table::startSession(const Time & start)
{
  if (!free_flag_)
  {
    throw std::logic_error("Attempt to start session on a busy table in Table::startSession");
  }

  free_flag_ = false;
  start_ = start;
}

void telecom::Table::endSession(const Time & end, int cost) noexcept
{
  free_flag_ = true;
  Time dur = countDuration(start_, end);
  sum_time_ = sum_time_ + dur;
  revenue_ += dur.hours_ * cost;
  revenue_ += (dur.minutes_ > 0) ? cost : 0;
}

bool telecom::Table::isFree() const noexcept
{
  return free_flag_;
}

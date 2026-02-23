#include "table.hpp"

#include "time.hpp"

telecom::Table::Table(int num):
  num_(num),
  busy_flag_(false),
  revenue_(0),
  start_(),
  sum_time_()
{}

int telecom::Table::getNum() const
{
  return num_;
}

int telecom::Table::getRevenue() const
{
  return revenue_;
}

const telecom::Time & telecom::Table::getSumTime() const
{
  return sum_time_;
}

void telecom::Table::startSession(const Time & start)
{
  busy_flag_ = true;
  start_ = start;
}

void telecom::Table::endSession(const Time & end, int cost)
{
  busy_flag_ = false;
  Time dur = countDuration(end, start_);
  sum_time_ = sum_time_ + dur;
  revenue_ += dur.hours_ * cost;
  revenue_ += (dur.minutes_ > 0) ? cost : 0;
}

bool telecom::Table::isBusy() const
{
  return busy_flag_;
}

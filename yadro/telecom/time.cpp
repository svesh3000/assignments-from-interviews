#include "time.hpp"

#include <cctype>

#include "stream-guard.hpp"

namespace
{

  struct TwoDigits
  {
    int value;
  };

  std::istream & operator>>(std::istream & in, TwoDigits & td);

  std::istream & operator>>(std::istream & in, TwoDigits & td)
  {
    std::istream::sentry s(in);
    if (!s)
    {
      return in;
    }

    char d1, d2;
    if (in >> d1 >> d2)
    {
      if (std::isdigit(d1) && std::isdigit(d2))
      {
        td.value = (d1 - '0') * 10 + (d2 - '0');
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    return in;
  }
}

std::istream & telecom::operator>>(std::istream & in, Time & t)
{
  std::istream::sentry s(in);
  if (!s)
  {
    return in;
  }

  TwoDigits hours, minutes;
  char del;

  in >> hours >> del >> minutes;

  if (in && del == ':' && hours.value <= 23 && minutes.value <= 59)
  {
    t.hours_ = hours.value;
    t.minutes_ = minutes.value;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::ostream & telecom::operator<<(std::ostream & out, const Time & t)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  StreamGuard streamguard(out);

  if (t.hours_ < 10)
  {
    out << '0';
  }
  out << t.hours_ << ':';
  if (t.minutes_ < 10)
  {
    out << '0';
  }
  out << t.minutes_;

  return out;
}

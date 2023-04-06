#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool placement(const AvailabilityMatrix &avail, int &x, int &y, DailySchedule &sched);
bool confirmFree(size_t dailyNeed, size_t x, size_t maxShifts, size_t section, DailySchedule &sched, const AvailabilityMatrix &availd);
bool help(int size, const AvailabilityMatrix &avail, int maxShifts, DailySchedule &sched);
bool recursiveSchedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, long int check);

// Add your implementation of schedule() and other helper functions here

bool schedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    long int check = 0;
    return recursiveSchedule(avail, dailyNeed, maxShifts, sched, check);
    // long int check = 0;
    // vector<Worker_T> schedule;
    // while (check < avail.size())
    // {
    //   sched.push_back(schedule);
    //   long int count = 0;
    //   while (count < dailyNeed)
    //   {
    //     sched[check].push_back(-1);
    //     ++count;
    //   }
    //   ++check;
    // }

    // while (true)
    // {
    //   int x = 5;
    //   for (long i = 0; i < 5; i++)
    //   {
    //     check--;
    //   }
    //   break;
    // }

    // return help(check, avail, maxShifts, sched);
}

bool recursiveSchedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, long int check)
{
    if(check >= avail.size())
    {
        return help(check, avail, maxShifts, sched);
    }
    else
    {
        vector<Worker_T> schedule;
        sched.push_back(schedule);
        long int count = 0;
        while (count < dailyNeed)
        {
            sched[check].push_back(-1);
            ++count;
        }
        ++check;
        return recursiveSchedule(avail, dailyNeed, maxShifts, sched, check);
    }
}

bool help(int size, const AvailabilityMatrix &avail, int maxShifts, DailySchedule &sched)
{
  int rows, columns = 0;
  bool available;
  bool checking = placement(avail, rows, columns, sched);
  
  switch (checking)
  {
    case true:
      break;
    case false:
      return true;
  }

  long int confirm = 0;
  do
    {
      size_t dailyNeed;
      available = confirmFree(dailyNeed, rows, confirm, maxShifts, sched, avail);
      switch (available)
      {
      case true:
          sched[rows][columns] = confirm;
          if (help(confirm, avail, maxShifts, sched))
          {
            return true;
          }

          sched[rows][columns] = INVALID_ID;
        }

        ++confirm;
    }
    while (confirm <= avail[0].size() - 1);
    return false;
 }

bool placement(const AvailabilityMatrix &avail, int &x, int &y, DailySchedule &sched)
{
  x = 0;
  do
  {
    y = 0;
    int size = (int)sched[x].size();
    while (y < size)
    {
      bool flag;
      int n = sched[x][y];

      if (n != -1)
      {
        flag = false;
      }

      switch (n)
      {
        case -1:
        flag = true;
        break;
      }

      if (flag == true)
      {
        return true;
      }
      ++y;
    }
    
    ++x;
  }
  while (x <= (int)sched.size() - 1);
  return false;
 }

bool confirmFree(size_t dailyNeed, size_t x, size_t section, size_t maxShifts, DailySchedule &sched, const AvailabilityMatrix &avail)
{
  bool banner;
  int temp = 0;
  if (avail[x][section])
  {
    long int check = 0;
    do
    {
      long int second = 0;
      int one = 1;
      while (second <= sched[0].size() * one - 1)
      {
        int confirm = sched[check][second];
        if (confirm != section)
        {}
        else
        {
          ++temp;
        }
        ++second;
      }
      ++check;
    } 

    while (check <= sched.size() - 1);
    bool checks = (temp >= maxShifts);
    if (checks)
    {
      banner = false;
    }
    else
    {
      banner = true;
    }
  }
  return banner;
}



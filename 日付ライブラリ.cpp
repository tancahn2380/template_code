#include "bits/stdc++.h"
using namespace std;

// 閏年かどうか調べる
bool is_leap(int y) {
  if ((y % 400) == 0) {
    return true;
  } else if ((y % 100) == 0) {
    return false;
  } else if ((y % 4) == 0) {
    return true;
  }
  return false;
}
 
int get_days_in_month(int y, int m) {
  assert(m >= 1 && m <= 12);
  int days[] = {31, 28, 31, 30, 31, 30,
                31, 31, 30, 31, 30, 31};
  if (m == 2 && is_leap(y)) {
    return days[1] + 1;
  }
  return days[m - 1];
}
 
// 日付処理
class MyDate{
 public:
  int day;
  int month;
  int year;
 
  MyDate(int y, int m, int d) {
    year = y;
    month = m;
    day = d;
  }
 
  MyDate tomorrow() {
    int td = day, tm = month, ty = year;
 
    td++;
    if (td > get_days_in_month(year, month)) {
      td = 1;
      tm++;
      if (tm > 12) {
        ty++;
        tm = 1;
      }
    }
    return MyDate(ty, tm, td);
  }
};
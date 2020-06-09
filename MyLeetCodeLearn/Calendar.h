#ifndef Calendar_H_
#define Calendar_H_

#include <stdlib.h>
#include <string>
using namespace std;

class Calendar
{
public:
	Calendar();
	~Calendar();

	//获取某月天数方法
	int GetDaysInMonth(int month);
	//使用年月日判断当前星期几方法
	int CaculateWeekDay(int y, int m, int d);

	//传入年月, 在控制台中绘制月历
	void DrawCalendar(int y, int m);

};

#endif

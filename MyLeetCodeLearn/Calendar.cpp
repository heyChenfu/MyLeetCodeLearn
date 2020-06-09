#include "stdafx.h"
#include "Calendar.h"

//每个月对应的天数
int day[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

Calendar::Calendar()
{
}

Calendar::~Calendar()
{
}

int Calendar::GetDaysInMonth(int month){
	if (month > sizeof(day) / sizeof(day[0]) || month <= 0){
		return -1;
	}
	return day[month - 1];
}

//把一月和二月看成是上一年的十三月和十四月，例：如果是2004-1-10则换算成：2003-13-10来代入公式计算
int Calendar::CaculateWeekDay(int y, int m, int d){
	if (m == 1 || m == 2) {
		m += 12;
		y--;
	}
	int iWeek = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7; //0为星期一
	return iWeek;
}

//日历绘制
void Calendar::DrawCalendar(int y, int m){
	//获取该月有多少天
	int totalDay = GetDaysInMonth(m);

	//绘制星期一~星期日
	for (int i = 0; i < 7; i++){
		string sType = "";
		if (i == 0) sType = "星期日\0";
		else if (i == 1) sType = "星期一\0";
		else if (i == 2) sType = "星期二\0";
		else if (i == 3) sType = "星期三\0";
		else if (i == 4) sType = "星期四\0";
		else if (i == 5) sType = "星期五\0";
		else if (i == 6) sType = "星期六\0";
		printf("%s\t", sType.c_str());
	}
	printf("\n");

	//计算当月第一天星期几
	int firstDay = CaculateWeekDay(y, m, 1);
	//计算该月第一天前需要空出多少天
	int emptyCount = firstDay >= 6 ? 0 : firstDay + 1;
	int index = 0;
	int dayNum = 1;
	while (true){
		if (dayNum > totalDay)
			break;
		//根据第一天星期几计算需要空出的日子
		if (emptyCount <= index){
			printf("%02d", dayNum);

			//判断是否需要换行
			if ((emptyCount + dayNum) % 7 == 0){
				printf("\n");
			}
			else{
				printf("\t");
			}

			dayNum++;
		}
		else{
			printf("      \t");
		}
		
		index++;
	}

	printf("\n");
}
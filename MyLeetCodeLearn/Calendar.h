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

	//��ȡĳ����������
	int GetDaysInMonth(int month);
	//ʹ���������жϵ�ǰ���ڼ�����
	int CaculateWeekDay(int y, int m, int d);

	//��������, �ڿ���̨�л�������
	void DrawCalendar(int y, int m);

};

#endif

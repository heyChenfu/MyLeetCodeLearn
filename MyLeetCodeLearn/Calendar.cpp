#include "stdafx.h"
#include "Calendar.h"

//ÿ���¶�Ӧ������
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

//��һ�ºͶ��¿�������һ���ʮ���º�ʮ���£����������2004-1-10����ɣ�2003-13-10�����빫ʽ����
int Calendar::CaculateWeekDay(int y, int m, int d){
	if (m == 1 || m == 2) {
		m += 12;
		y--;
	}
	int iWeek = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7; //0Ϊ����һ
	return iWeek;
}

//��������
void Calendar::DrawCalendar(int y, int m){
	//��ȡ�����ж�����
	int totalDay = GetDaysInMonth(m);

	//��������һ~������
	for (int i = 0; i < 7; i++){
		string sType = "";
		if (i == 0) sType = "������\0";
		else if (i == 1) sType = "����һ\0";
		else if (i == 2) sType = "���ڶ�\0";
		else if (i == 3) sType = "������\0";
		else if (i == 4) sType = "������\0";
		else if (i == 5) sType = "������\0";
		else if (i == 6) sType = "������\0";
		printf("%s\t", sType.c_str());
	}
	printf("\n");

	//���㵱�µ�һ�����ڼ�
	int firstDay = CaculateWeekDay(y, m, 1);
	//������µ�һ��ǰ��Ҫ�ճ�������
	int emptyCount = firstDay >= 6 ? 0 : firstDay + 1;
	int index = 0;
	int dayNum = 1;
	while (true){
		if (dayNum > totalDay)
			break;
		//���ݵ�һ�����ڼ�������Ҫ�ճ�������
		if (emptyCount <= index){
			printf("%02d", dayNum);

			//�ж��Ƿ���Ҫ����
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
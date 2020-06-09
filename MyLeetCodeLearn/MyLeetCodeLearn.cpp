// MyLeetCodeLearn.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <unordered_map>
#include <algorithm> 
#include "Calendar.h"

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

/*
* ����list����
*/
ListNode* CreateList(vector<int> data){
	ListNode* head = new ListNode(0);
	ListNode* ptr = head;

	for (int i = 0; i < data.size(); i++){
		auto newNode = new ListNode(data[i]);
		ptr->next = newNode;
		ptr = ptr->next;
	}

	return head->next;
}

/*
ֱ�Ӳ�������
*/
void InsertSort(int * a, int n) {
	if (n <= 1)
		return;
	//�ӵڶ���Ԫ�ؿ�ʼ, Ĭ��ǰ��Ԫ������, С����һ��Ԫ������ǰ�������λ��
	for (int i = 1; i < n; i++) {
		if (a[i] < a[i - 1] ) {
			//��Ҫ����
			int tmp = a[i];
			int j = i - 1;
			//����ƶ�Ԫ��
			while (tmp < a[j] && j >= 0) {
				//��Ŀ��Ԫ�ش��Ԫ�������
				a[j + 1] = a[j];
				j--;
			}
			//���ʵ�λ�ò���
			a[j + 1] = tmp;
		}
	}
}

/*******������********/
void CreateHeap(int * a, int i, int len){
	for (; i >= 0; i--){
		//���������ӽڵ�
		int leftChild = i * 2 + 1;
		int rightChild = i * 2 + 2;
		if (leftChild >= len) continue;
		if (rightChild >= len) continue;
		//�жϸ��ڵ�������ӽڵ��С
		int max = i;
		if (a[max] < a[leftChild]){
			max = leftChild;
		}
		if (a[max] < a[rightChild]){
			max = rightChild;
		}
		//����
		if (max != i){
			int tmp = a[i];
			a[i] = a[max];
			a[max] = tmp;
		}
	}

}

/*
�ۼ��㷨 1 + ... + n
*/
int accumulation(int n){
	int sum = 0;
	for (int i = 1; i <= n; i++){
		sum += i;
	}
	return sum;
}

/*
�򵥵��ۼ��㷨 1 + ... + n ��˹��ʽ
*/
int accumulationEx(int n){
	int sum = 0;
	sum = (1 + n) * n / 2;
	return sum;
}


/*
* ����һ������ɾ������ĵ����� n ���ڵ㣬���ҷ��������ͷ���
*/
ListNode* removeNthFromEnd(ListNode* head, int n) {
	ListNode * newHead = head;
	ListNode * pNode = head;
	int length = 1;
	//���ȼ���������
	while (pNode->next != NULL){
		pNode = pNode->next;
		length++;
	}
	//���ݲ�һ���Ͳ��ñ�����
	if (length <= 1){
		return NULL;
	}

	ListNode * pPre = head;
	pNode = head;
	//�ڶ��α������ݳ��Ⱥ�n��ֵɾ��������n���ڵ�
	for (int i = 0; i < length; i++){
		if (i == length - n){
			//���жϸýڵ��Ƿ�Ϊͷ�ڵ�
			if (pNode == head){
				newHead = pNode->next;
			}
			//ɾ���ýڵ�
			pPre->next = pNode->next;
			pNode = NULL;
			break;
		}
		pPre = pNode;
		pNode = pNode->next;
	}

	return newHead;
}

ListNode* removeNthFromEndEx(ListNode* head, int n) {
	if (head->next == NULL)
		return NULL;

	//˫ָ�뷨, ��������ָ��֮����Ϊn
	ListNode * p1 = head;
	ListNode * p2 = head;
	for (int i = 0; i < n; i++){
		if (p2->next == NULL){ //���Ȳ��� ˵��ɾ������ͷ�ڵ�
			auto tmp = head->next;
			delete head;
			return tmp;
		}
		else
			p2 = p2->next;
	}

	//����ֱ��p2->nextΪ��, ��p1->nextΪ����ɾ���ڵ�
	while (p2 && p2->next){
		p1 = p1->next;
		p2 = p2->next;
	}
	//ɾ��
	auto tmp = p1->next;
	p1->next = tmp->next;
	delete tmp;

	return head;
}

/*
* ����һ��ֻ���� '('��')'��'{'��'}'��'['��']' ���ַ������ж��ַ����Ƿ���Ч
*/
bool isValid(string s) {
	//�ֱ𱣴�����ź��ҷ���
	vector<char> left = { '(', '[', '{' };
	vector<char> right = { ')', ']', '}' };
	stack<char> myStack;
	//�����ַ���, �ж��ַ�������Ż����ҷ���
	//Ӧ�����Ƚ�����Ĺ���, ����ʹ�ö�ջ
	for (auto character : s){
		//�ж���ջ���ǳ�ջ
		auto leftIt = find(left.begin(), left.end(), character);
		auto rightIt = find(right.begin(), right.end(), character);
		if (leftIt != left.end()){
			myStack.push(character);
		}
		else if (rightIt != right.end()){
			//�����ʱ��û��Ԫ����ջ?!
			if (myStack.size() == 0){
				return false;
			}
			else{
				//ȥ�����һ��Ԫ��
				char tmp = myStack.top();
				auto tmpIt = find(left.begin(), left.end(), tmp);
				if ((tmpIt - left.end()) != (rightIt - right.end())){
					//��ǰ��Ҫ��ջ���ַ������һ����ջ���ַ����ǶԳ��ַ�
					return false;
				}
				else{
					//�����һ��Ԫ�س�ջ
					myStack.pop();
				}
			}
		}
	}

	//����ж��Ƿ���Ԫ��δ��ջ�����������
	if (myStack.size() > 0){
		return false;
	}
	return true;
}

vector<string> gpResult;
void generateParenthesisLoop(string s, int n, int lNum, int rNum){
	//�����ϣ��������ŷֱ�Ϊn��
	//�����ŵ�������Ҫ���ڵ��������ŵ�����
	if (lNum > n || rNum > n)
		return;
	if (rNum > lNum)
		return;
	//������������б�
	if (rNum == lNum && rNum == n){
		gpResult.push_back(s);
		return;
	}

	//�������ŷֱ��1
	generateParenthesisLoop(s + "(", n, lNum + 1, rNum);
	generateParenthesisLoop(s + ")", n, lNum, rNum + 1);
}

/*
* ���� n �����������ŵĶ���������д��һ��������ʹ���ܹ��������п��ܵĲ�����Ч���������
*/
vector<string> generateParenthesis(int n) {

	generateParenthesisLoop("", n, 0, 0);

	return gpResult;
}

ListNode * mergeKListsLoop(ListNode * ptr1, ListNode * ptr2){
	ListNode * head = new ListNode(0);
	ListNode * ptr = head;
	//�ϲ���������
	while (ptr1 != NULL && ptr2 != NULL){
		if (ptr2->val < ptr1->val){
			ptr->next = ptr2;
			ptr2 = ptr2->next;
		}
		else{
			ptr->next = ptr1;
			ptr1 = ptr1->next;
		}
		if (ptr->next != NULL) ptr = ptr->next;
	}
	//ʣ�����ݴ���
	while (ptr1 != NULL){
		ptr->next = ptr1;
		ptr1 = ptr1->next;
		if (ptr->next != NULL) ptr = ptr->next;
	}
	while (ptr2 != NULL){
		ptr->next = ptr2;
		ptr2 = ptr2->next;
		if (ptr->next != NULL) ptr = ptr->next;
	}
	return head->next;
}

/*
* �ϲ� k �������������غϲ������������������������㷨�ĸ��Ӷ�
*/
ListNode* mergeKLists(vector<ListNode*>& lists) {
	if (lists.size() == 0)
		return NULL;

	vector<ListNode*> newList = lists;

	//ʹ�÷��η�
	while (newList.size() != 1){
		vector<ListNode*> tmpList;
		int len = newList.size() >> 1;
		for (int i = 0; i < len; i++){
			int j = len + i;
			auto mergeHead = mergeKListsLoop(newList[i], newList[j]);
			tmpList.push_back(mergeHead);
		}
		//����©һ��
		if (newList.size() != 1 && newList.size() % 2 != 0)
			tmpList.push_back(newList[newList.size() - 1]);
		newList = tmpList;
	}

	return newList[0];
}

void swapPairsLoop(ListNode * ptrBef, ListNode * ptrCurr){
	//�����������ڽڵ�
	auto ptrNext = ptrCurr->next;
	if (ptrNext == NULL){
		return;
	}
	//����
	auto tmp = ptrNext->next;
	ptrNext->next = ptrCurr;
	ptrCurr->next = tmp;
	ptrBef->next = ptrNext;

	if (tmp == NULL) return;

	swapPairsLoop(ptrCurr, tmp);
}

/*
* ����һ���������������������ڵĽڵ㣬�����ؽ����������
*/
ListNode* swapPairs(ListNode* head) {
	if (head == NULL) return NULL;
	if (head->next == NULL) return head;

	ListNode * newHead = new ListNode(0);
	newHead->next = head;
	ListNode * ptr = newHead;

	swapPairsLoop(newHead, head);

	return newHead->next;
}


/*
���ֲ��ҷ�
*/
int binarySearch(vector<int>& nums, int target) {
	int result = -1;
	int low = 0, hight = nums.size() - 1;
	while (low <= hight){
		//����middle
		int middle = low + hight >> 1;
		if (target < nums[middle]){
			hight = middle - 1;
		}
		else if (target > nums[middle]){
			low = middle + 1;
		}
		else{
			result = middle;
			break;
		}
	}
	return result;
}

/*
����һ�����������һ��Ŀ��ֵ�����������ҵ�Ŀ��ֵ�������������������Ŀ��ֵ�������������У����������ᱻ��˳������λ�á�
*/
int searchInsert(vector<int>& nums, int target) {
	for (vector<int>::iterator it = nums.begin(); it != nums.end(); it++) {
		//���ҵ�Ŀ��ֵ
		if ((*it) >= target) {
			return it - nums.begin();
		}
	}
	//������������Ԫ��
	return nums.size();
}


/*
�ж�һ�� 9x9 �������Ƿ���Ч��ֻ��Ҫ�������¹�����֤�Ѿ�����������Ƿ���Ч���ɡ�
	���� 1-9 ��ÿһ��ֻ�ܳ���һ�Ρ�
	���� 1-9 ��ÿһ��ֻ�ܳ���һ�Ρ�
	���� 1-9 ��ÿһ���Դ�ʵ�߷ָ��� 3x3 ����ֻ�ܳ���һ��
*/
bool isValidSudoku(vector<vector<char>>& board) {
	int lineSize = board.size();
	int columeSize = board[0].size();
	//����ÿ��
	for (int i = 0; i < lineSize; i++) {
		bool bShow[10] = { false };
		for (int j = 0; j < columeSize; j++) {
			if (board[i][j] != '.') { //�ǿ�
				if (bShow[board[i][j] - '0'] == false) {
					bShow[board[i][j] - '0'] = true;
				}
				else {
					return false;
				}
			}
		}
	}
	//����ÿ��
	for (int i = 0; i < columeSize; i++) {
		bool bShow[10] = { false };
		for (int j = 0; j < lineSize; j++) {
			if (board[j][i] != '.') { //�ǿ�
				if (bShow[board[j][i] - '0'] == false) {
					bShow[board[j][i] - '0'] = true;
				}
				else {
					return false;
				}
			}
		}
	}
	//����ÿ��3x3
	int lineIndex = 0;
	int columeIndex = 0;
	while (lineIndex < 3 && columeIndex < 3) {
		bool bShow[10] = { false };
		for (int i = lineIndex * 3; i < lineIndex * 3 + 3; i++) {
			for (int j = columeIndex * 3; j < columeIndex * 3 + 3; j++) {
				if (board[i][j] != '.') { //�ǿ�
					if (bShow[board[i][j] - '0'] == false) {
						bShow[board[i][j] - '0'] = true;
					}
					else {
						return false;
					}
				}
			}
		}
		if (lineIndex < 2) {
			lineIndex++;
		}
		else {
			lineIndex = 0;
			columeIndex++;
		}
	}

	return true;
}

/*
����������һ���������У��������е�������˳����б������õ���һ��������ǰ�������£�
1.     1
2.     11
3.     21
4.     1211
5.     111221
1 ������  "one 1"  ("һ��һ") , �� 11��
11 ������ "two 1s" ("����һ"��, �� 21��
21 ������ "one 2",  "one 1" ��"һ����" ,  "һ��һ") , �� 1211��
*/
string countAndSay(int n) {
	if (n == 0)
		return "";

	string result = "1";
	map<string, string> contrastMap = {
		pair<string, string>("1", "11"),
		pair<string, string>("11", "21"),
		pair<string, string>("12", "1112"),
		pair<string, string>("21", "1211"),
	};

	while (n > 1) {
		string newResult = "";
		string tmp = "";
		for (int i = 0; i < result.size(); i++) {
			tmp += result[i];
			if (tmp.size() >= 2) {
				newResult += contrastMap[tmp];
				tmp = "";
			}
		}
		if(tmp != ""){
			newResult += contrastMap[tmp];
		}

		result = newResult;
		n--;
	}

	return result;
}


/*
����ѭ������ ��һ������Ϊn������A��Ԫ��ѭ������kλ
*/
void RightMoveVector(vector<int> & vec, int k) {
	k %= vec.size(); //���k�ܱ����鳤��len��������ô����˳�򲻱�
	while (k > 0) {
		int lastNum = vec[vec.size() - 1];
		for (int i = vec.size() - 1; i > 0 ; i--) {
			vec[i] = vec[i - 1];
		}
		vec[0] = lastNum;

		k--;
	}
}

/*
����һ���������� nums ���ҵ�һ���������͵����������飨���������ٰ���һ��Ԫ�أ�������������
*/
int maxSubArray(vector<int>& nums) {
	if (nums.size() == 1)
		return nums[0];
	//̰���㷨, �����ұ�������, �����������������ֵ
	int contiueNum = 0, maxNum = INT_MIN;
	for (int i = 0; i < nums.size(); i++) {
		if (nums[i] > nums[i] + contiueNum) {
			//���´Ӹ�λ�ÿ�ʼ����
			contiueNum = nums[i];
		}
		else {
			//�ۼ�
			contiueNum += nums[i];
		}
		if (contiueNum > maxNum)
			maxNum = contiueNum;
	}

	return maxNum;
}

int climbStairsRecursion(int * arr, int i, int n) {
	//i�ۼӵ�n��Ϊһ�ֽ��
	if (i > n) {
		return 0;
	}
	if (i == n) {
		return 1;
	}
	//ǰ����һ�������ֿ���
	if (arr[i] == 0) {
		arr[i] = climbStairsRecursion(arr, i + 1, n) + climbStairsRecursion(arr, i + 2, n);
	}
	return arr[i];
}

/*
������������¥�ݡ���Ҫ n ������ܵ���¥����
ÿ��������� 1 �� 2 ��̨�ס����ж����ֲ�ͬ�ķ�����������¥���أ�
*/
int climbStairs(int n) {
	int* arr = new int[n];
	memset(arr, 0, n * sizeof(int));
	//��0��n�ݹ�
	int result = climbStairsRecursion(arr, 0, n);
	delete[] arr;
	return result;
}

int myatoi(string input) {
	int result = 0;
	bool symbol = 1;
	if (input[0] == '-') {
		symbol = -1;
		input = input.substr(1, input.size() - 1);
	}

	//ȡ��ÿλ����
	int tmp = 1;
	for (int i = input.size() - 1; i >= 0; i--) {
		int num = (input[i] - '0')* tmp;
		if (result + num > INT_MAX) {
			result = INT_MAX;
			break;
		}
		result += num;
		tmp *= 10;
	}
	return result * symbol;
}

/*
�����������ַ�����ʽ��ʾ�ķǸ����� num1 �� num2������ num1 �� num2 �ĳ˻������ǵĳ˻�Ҳ��ʾΪ�ַ�����ʽ
*/
string multiply(string num1, string num2) {
	int a = myatoi(num1);
	int b = myatoi(num2);
	return to_string(a * b);
}

void combinationSumRecursion(vector<int>& candidates, vector<vector<int>> & result, vector<int> & singleResult, int currIndex, int target) {
	if (target == 0) {
		result.push_back(singleResult);
		return;
	}
	if (target < 0) {
		return;
	}

	for (int i = currIndex; i < candidates.size(); i++) {
		singleResult.push_back(candidates[i]);
		combinationSumRecursion(candidates, result, singleResult, i, target - candidates[i]);
		singleResult.pop_back();
	}
}

/*
����һ�����ظ�Ԫ�ص����� candidates ��һ��Ŀ���� target ���ҳ� candidates �����п���ʹ���ֺ�Ϊ target ����ϡ�
candidates �е����ֿ����������ظ���ѡȡ
*/
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	vector<vector<int>> result;
	vector<int> singleResult;
	combinationSumRecursion(candidates, result, singleResult, 0, target);
	return result;
}

int uniquePathsRecursion(vector<vector<int>> & arr, const int & m, const int & n, int currM, int currN) {
	if (currM == m - 1 && currN == n - 1) {
		//�ҵ��յ�
		return 1;
	}
	if (currM >= m || currN >= n) {
		//Խ��
		return 0;
	}
	//������ֻ�����һ�������
	if (arr[currM][currN] != 0) {
		return arr[currM][currN];
	}
	arr[currM][currN] = uniquePathsRecursion(arr, m, n, currM + 1, currN) + uniquePathsRecursion(arr, m, n, currM, currN + 1);
	return arr[currM][currN];
}

/*
һ��������λ��һ�� m x n ��������Ͻ� ����ʼ������ͼ�б��Ϊ��Start�� ����
������ÿ��ֻ�����»��������ƶ�һ������������ͼ�ﵽ��������½ǣ�����ͼ�б��Ϊ��Finish������
���ܹ��ж�������ͬ��·����
*/
int uniquePaths(int m, int n) {
	//�����Ӧ���ӵĽ������������ظ��ݹ�
	vector<vector<int>> arr(m, vector<int>(n));
	int result = 0;
	result = uniquePathsRecursion(arr, m, n, 0, 0);
	return result;
}

int uniquePathsEx(int m, int n) {
	vector<vector<int>> dp(m, vector<int>(n, 0));
	for (int i = 0; i < n; i++)  
		dp[0][i] = 1;
	for (int i = 0; i < m; i++)  
		dp[i][0] = 1;
	for (int i = 1; i < m; i++)
		for (int j = 1; j < n; j++) 
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
	return dp[m - 1][n - 1];
}

/*
����һ���ǿ��������飬����ĳ��Ԫ��ֻ����һ�����⣬����ÿ��Ԫ�ؾ��������Ρ��ҳ��Ǹ�ֻ������һ�ε�Ԫ�ء�
����㷨Ӧ�þ�������ʱ�临�Ӷȡ� ����Բ�ʹ�ö���ռ���ʵ����
*/
int singleNumber(vector<int>& nums) {
	unordered_map<int, int> myMap;
	for (int i = 0; i < nums.size(); i++) {
		if (myMap.find(nums[i]) != myMap.end()) {
			myMap.erase(nums[i]);
		}
		else {
			myMap.insert(pair<int, int>(nums[i], 1));
		}
	}

	return myMap.begin()->first;
}

/*
һ�����飬��ô����ѭ��������һ��ֵ�������������
*/
void PrintArrayRecursion(int* arr, int index) {
	if (index <= 0)
		return;
	index--;
	printf("��%d = %d", index, arr[index]);
	PrintArrayRecursion(arr, index);
}

void PrintArray(int * arr, int len) {
	PrintArrayRecursion(arr, len);
}

/*
�õݹ������У�1��1��2��3��5��8��13��������n ��n��ֵ
*/
int GetArrFibonacciRecursion(int index) {
	if (index <= 2)
		return 1;
	return GetArrFibonacciRecursion(index - 1) + GetArrFibonacciRecursion(index - 2);
}

int GetArrFibonacci(int index) {
	return GetArrFibonacciRecursion(index);
}

/*
ð��
*/
void MaoPaoSort(vector<int> & vec) {
	for (int i = 0; i < vec.size(); i++) {
		for (int j = vec.size() - 1; j > i; j--) {
			if (vec[j] < vec[j - 1]) {
				int tmp = vec[j];
				vec[j] = vec[j - 1];
				vec[j - 1] = tmp;
			}
		}
	}
}

/*********************/

int _tmain(int argc, _TCHAR* argv[])
{
	/*int a[10] = { 1, 3, 2, 9, 6, 8, 7, 5, 0, 4 };
	InsertSort(a, sizeof(a) / sizeof(a[0]));*/

	/*int a[10] = { 1, 3, 2, 9, 6, 8, 7, 5, 0, 4 };
	CreateHeap(a, 10 >> 1, 10);*/

	//�ۼӲ���
	//int sum1 = accumulation(7);
	//int sum2 = accumulationEx(7);

	//��Ŀ19
	//ListNode * head = new ListNode(1);
	//auto realHead = head;
	//for (int i = 2; i <= 2; i++){
	//	auto tmp = new ListNode(i);
	//	head->next = tmp;
	//	head = tmp;
	//}
	//removeNthFromEndEx(realHead, 2);

	//��Ŀ20
	//bool val = isValid("]");

	//��Ŀ22
	//generateParenthesis(3);

	//��Ŀ23
	//vector<ListNode*> test = { CreateList({ 1, 4, 5 }), 
	//	CreateList({1, 3, 4}), 
	//	CreateList({ 2, 6 }) };
	//mergeKLists(test);

	//��Ŀ24
	//auto test = CreateList({1, 2, 3, 4});
	//swapPairs(test);

	//���������������о�
	/*float a = 0.1f;
	float b = 0.09f;
	float c = a - b;
	float comp = pow(10, -6);
	float comp2 = 1e-6;
	if (fabs(c - 0.01f) <= comp){
		printf("���!");
	}
	else{
		printf("����!");
	}*/

	/************�ӿ���̨��ȡ����*************/
	//printf("���������£�");
	//int year = 0, month = 0;
	//scanf_s("%d%d", &year, &month);
	////����̨��ʾ����
	//Calendar * calender = new Calendar();
	//calender->DrawCalendar(year, month);

	//��Ŀ35
	//vector<int> vec = { 1,3,5,6 };
	//int index = searchInsert(vec, 0);

	//��Ŀ36
	//vector<vector<char>> vec = {
	//	{'5','3','.','.','7','.','.','.','.'},
	//	{'6','.','.','1','9','5','.','.','.'},
	//	{'.','9','8','.','.','.','.','6','.'},
	//	{'8','.','.','.','6','.','.','.','3'},
	//	{'4','.','.','8','.','3','.','.','1'},
	//	{'7','.','.','.','2','.','.','.','6'},
	//	{'.','6','.','.','.','.','2','8','.'},
	//	{'.','.','.','4','1','9','.','.','5'},
	//	{'.','.','.','.','8','.','.','7','9'}
	//};
	//bool bValid = isValidSudoku(vec);

	//��Ŀ38
	//string tmp = countAndSay(5);

	//vector<int> vec = {1, 2, 3, 4, 5};
	//RightMoveVector(vec, 3);

	//��Ŀ53
	//vector<int> vec = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	//int num = maxSubArray(vec);

	//��Ŀ70
	//int num = climbStairs(3);

	//��Ŀ43
	//string tmp = multiply("123", "456");

	//��Ŀ39
	//vector<int> tmp = {2, 3, 6, 7};
	//vector<vector<int>> result = combinationSum(tmp, 7);

	//��Ŀ62
	//int tmp = uniquePaths(3, 2);

	//��Ŀ136
	//vector<int> tmp = {4, 1, 2, 1, 2};
	//int result = singleNumber(tmp);

	//int arr[] = {3, 5, 6, 4, 2, 9};
	//PrintArray(arr, sizeof(arr) / sizeof(int));

//int tmp = GetArrFibonacci(7);

//MaoPaoSort(arr);
//STL�ṩ�������㷨
int a[20] = { 2,4,1,23,5,76,0,43,24,65 };
sort(a, a + 20);
vector<int> arr = { 2, 1, 5, 4 };
sort(arr.begin(), arr.end());

	system("pause");
	return 0;
}


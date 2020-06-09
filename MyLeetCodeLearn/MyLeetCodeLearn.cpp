// MyLeetCodeLearn.cpp : 定义控制台应用程序的入口点。
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
* 创建list方法
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
直接插入排序
*/
void InsertSort(int * a, int n) {
	if (n <= 1)
		return;
	//从第二个元素开始, 默认前面元素有序, 小于上一个元素则向前插入合适位置
	for (int i = 1; i < n; i++) {
		if (a[i] < a[i - 1] ) {
			//需要插入
			int tmp = a[i];
			int j = i - 1;
			//向后移动元素
			while (tmp < a[j] && j >= 0) {
				//比目标元素大的元素向后移
				a[j + 1] = a[j];
				j--;
			}
			//合适的位置插入
			a[j + 1] = tmp;
		}
	}
}

/*******堆排序********/
void CreateHeap(int * a, int i, int len){
	for (; i >= 0; i--){
		//计算左右子节点
		int leftChild = i * 2 + 1;
		int rightChild = i * 2 + 2;
		if (leftChild >= len) continue;
		if (rightChild >= len) continue;
		//判断父节点和左右子节点大小
		int max = i;
		if (a[max] < a[leftChild]){
			max = leftChild;
		}
		if (a[max] < a[rightChild]){
			max = rightChild;
		}
		//交换
		if (max != i){
			int tmp = a[i];
			a[i] = a[max];
			a[max] = tmp;
		}
	}

}

/*
累加算法 1 + ... + n
*/
int accumulation(int n){
	int sum = 0;
	for (int i = 1; i <= n; i++){
		sum += i;
	}
	return sum;
}

/*
简单的累加算法 1 + ... + n 高斯公式
*/
int accumulationEx(int n){
	int sum = 0;
	sum = (1 + n) * n / 2;
	return sum;
}


/*
* 给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点
*/
ListNode* removeNthFromEnd(ListNode* head, int n) {
	ListNode * newHead = head;
	ListNode * pNode = head;
	int length = 1;
	//首先计算链表长度
	while (pNode->next != NULL){
		pNode = pNode->next;
		length++;
	}
	//数据才一个就不用遍历了
	if (length <= 1){
		return NULL;
	}

	ListNode * pPre = head;
	pNode = head;
	//第二次遍历根据长度和n的值删除倒数第n个节点
	for (int i = 0; i < length; i++){
		if (i == length - n){
			//且判断该节点是否为头节点
			if (pNode == head){
				newHead = pNode->next;
			}
			//删除该节点
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

	//双指针法, 先让两个指针之间间隔为n
	ListNode * p1 = head;
	ListNode * p2 = head;
	for (int i = 0; i < n; i++){
		if (p2->next == NULL){ //长度不够 说明删除的是头节点
			auto tmp = head->next;
			delete head;
			return tmp;
		}
		else
			p2 = p2->next;
	}

	//遍历直到p2->next为空, 则p1->next为所需删除节点
	while (p2 && p2->next){
		p1 = p1->next;
		p2 = p2->next;
	}
	//删除
	auto tmp = p1->next;
	p1->next = tmp->next;
	delete tmp;

	return head;
}

/*
* 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效
*/
bool isValid(string s) {
	//分别保存左符号和右符号
	vector<char> left = { '(', '[', '{' };
	vector<char> right = { ')', ']', '}' };
	stack<char> myStack;
	//遍历字符串, 判断字符是左符号还是右符号
	//应符合先进后出的规律, 所以使用堆栈
	for (auto character : s){
		//判断入栈还是出栈
		auto leftIt = find(left.begin(), left.end(), character);
		auto rightIt = find(right.begin(), right.end(), character);
		if (leftIt != left.end()){
			myStack.push(character);
		}
		else if (rightIt != right.end()){
			//如果这时候还没有元素入栈?!
			if (myStack.size() == 0){
				return false;
			}
			else{
				//去除最后一个元素
				char tmp = myStack.top();
				auto tmpIt = find(left.begin(), left.end(), tmp);
				if ((tmpIt - left.end()) != (rightIt - right.end())){
					//当前需要出栈的字符和最后一个入栈的字符并非对称字符
					return false;
				}
				else{
					//将最后一个元素出栈
					myStack.pop();
				}
			}
		}
	}

	//最后判断是否还有元素未出栈。。是则错误
	if (myStack.size() > 0){
		return false;
	}
	return true;
}

vector<string> gpResult;
void generateParenthesisLoop(string s, int n, int lNum, int rNum){
	//数量上，左右括号分别都为n个
	//左括号的数量需要大于等于右括号的数量
	if (lNum > n || rNum > n)
		return;
	if (rNum > lNum)
		return;
	//合理则加入结果列表
	if (rNum == lNum && rNum == n){
		gpResult.push_back(s);
		return;
	}

	//左右括号分别加1
	generateParenthesisLoop(s + "(", n, lNum + 1, rNum);
	generateParenthesisLoop(s + ")", n, lNum, rNum + 1);
}

/*
* 给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合
*/
vector<string> generateParenthesis(int n) {

	generateParenthesisLoop("", n, 0, 0);

	return gpResult;
}

ListNode * mergeKListsLoop(ListNode * ptr1, ListNode * ptr2){
	ListNode * head = new ListNode(0);
	ListNode * ptr = head;
	//合并两个链表
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
	//剩余数据处理
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
* 合并 k 个排序链表，返回合并后的排序链表。请分析和描述算法的复杂度
*/
ListNode* mergeKLists(vector<ListNode*>& lists) {
	if (lists.size() == 0)
		return NULL;

	vector<ListNode*> newList = lists;

	//使用分治法
	while (newList.size() != 1){
		vector<ListNode*> tmpList;
		int len = newList.size() >> 1;
		for (int i = 0; i < len; i++){
			int j = len + i;
			auto mergeHead = mergeKListsLoop(newList[i], newList[j]);
			tmpList.push_back(mergeHead);
		}
		//奇数漏一个
		if (newList.size() != 1 && newList.size() % 2 != 0)
			tmpList.push_back(newList[newList.size() - 1]);
		newList = tmpList;
	}

	return newList[0];
}

void swapPairsLoop(ListNode * ptrBef, ListNode * ptrCurr){
	//交换两个相邻节点
	auto ptrNext = ptrCurr->next;
	if (ptrNext == NULL){
		return;
	}
	//交换
	auto tmp = ptrNext->next;
	ptrNext->next = ptrCurr;
	ptrCurr->next = tmp;
	ptrBef->next = ptrNext;

	if (tmp == NULL) return;

	swapPairsLoop(ptrCurr, tmp);
}

/*
* 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表
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
二分查找法
*/
int binarySearch(vector<int>& nums, int target) {
	int result = -1;
	int low = 0, hight = nums.size() - 1;
	while (low <= hight){
		//计算middle
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
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
*/
int searchInsert(vector<int>& nums, int target) {
	for (vector<int>::iterator it = nums.begin(); it != nums.end(); it++) {
		//查找到目标值
		if ((*it) >= target) {
			return it - nums.begin();
		}
	}
	//均大于数组内元素
	return nums.size();
}


/*
判断一个 9x9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可。
	数字 1-9 在每一行只能出现一次。
	数字 1-9 在每一列只能出现一次。
	数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次
*/
bool isValidSudoku(vector<vector<char>>& board) {
	int lineSize = board.size();
	int columeSize = board[0].size();
	//遍历每行
	for (int i = 0; i < lineSize; i++) {
		bool bShow[10] = { false };
		for (int j = 0; j < columeSize; j++) {
			if (board[i][j] != '.') { //非空
				if (bShow[board[i][j] - '0'] == false) {
					bShow[board[i][j] - '0'] = true;
				}
				else {
					return false;
				}
			}
		}
	}
	//遍历每列
	for (int i = 0; i < columeSize; i++) {
		bool bShow[10] = { false };
		for (int j = 0; j < lineSize; j++) {
			if (board[j][i] != '.') { //非空
				if (bShow[board[j][i] - '0'] == false) {
					bShow[board[j][i] - '0'] = true;
				}
				else {
					return false;
				}
			}
		}
	}
	//遍历每个3x3
	int lineIndex = 0;
	int columeIndex = 0;
	while (lineIndex < 3 && columeIndex < 3) {
		bool bShow[10] = { false };
		for (int i = lineIndex * 3; i < lineIndex * 3 + 3; i++) {
			for (int j = columeIndex * 3; j < columeIndex * 3 + 3; j++) {
				if (board[i][j] != '.') { //非空
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
报数序列是一个整数序列，按照其中的整数的顺序进行报数，得到下一个数。其前五项如下：
1.     1
2.     11
3.     21
4.     1211
5.     111221
1 被读作  "one 1"  ("一个一") , 即 11。
11 被读作 "two 1s" ("两个一"）, 即 21。
21 被读作 "one 2",  "one 1" （"一个二" ,  "一个一") , 即 1211。
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
数组循环右移 将一个长度为n的数组A的元素循环右移k位
*/
void RightMoveVector(vector<int> & vec, int k) {
	k %= vec.size(); //如果k能被数组长度len整除，那么数组顺序不变
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
给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和
*/
int maxSubArray(vector<int>& nums) {
	if (nums.size() == 1)
		return nums[0];
	//贪心算法, 从左到右遍历数组, 保存连续子数组最大值
	int contiueNum = 0, maxNum = INT_MIN;
	for (int i = 0; i < nums.size(); i++) {
		if (nums[i] > nums[i] + contiueNum) {
			//重新从该位置开始计算
			contiueNum = nums[i];
		}
		else {
			//累加
			contiueNum += nums[i];
		}
		if (contiueNum > maxNum)
			maxNum = contiueNum;
	}

	return maxNum;
}

int climbStairsRecursion(int * arr, int i, int n) {
	//i累加到n则为一种结果
	if (i > n) {
		return 0;
	}
	if (i == n) {
		return 1;
	}
	//前往下一步有两种可能
	if (arr[i] == 0) {
		arr[i] = climbStairsRecursion(arr, i + 1, n) + climbStairsRecursion(arr, i + 2, n);
	}
	return arr[i];
}

/*
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
*/
int climbStairs(int n) {
	int* arr = new int[n];
	memset(arr, 0, n * sizeof(int));
	//从0到n递归
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

	//取出每位数字
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
给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式
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
给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的数字可以无限制重复被选取
*/
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	vector<vector<int>> result;
	vector<int> singleResult;
	combinationSumRecursion(candidates, result, singleResult, 0, target);
	return result;
}

int uniquePathsRecursion(vector<vector<int>> & arr, const int & m, const int & n, int currM, int currN) {
	if (currM == m - 1 && currN == n - 1) {
		//找到终点
		return 1;
	}
	if (currM >= m || currN >= n) {
		//越界
		return 0;
	}
	//机器人只能向右或向下走
	if (arr[currM][currN] != 0) {
		return arr[currM][currN];
	}
	arr[currM][currN] = uniquePathsRecursion(arr, m, n, currM + 1, currN) + uniquePathsRecursion(arr, m, n, currM, currN + 1);
	return arr[currM][currN];
}

/*
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
问总共有多少条不同的路径？
*/
int uniquePaths(int m, int n) {
	//保存对应格子的结果避免大量的重复递归
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
给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？
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
一个数组，怎么不用循环，不逐一赋值，把它逆序输出
*/
void PrintArrayRecursion(int* arr, int index) {
	if (index <= 0)
		return;
	index--;
	printf("第%d = %d", index, arr[index]);
	PrintArrayRecursion(arr, index);
}

void PrintArray(int * arr, int len) {
	PrintArrayRecursion(arr, len);
}

/*
用递归求数列：1，1，2，3，5，8，13，……，n 第n个值
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
冒泡
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

	//累加测试
	//int sum1 = accumulation(7);
	//int sum2 = accumulationEx(7);

	//题目19
	//ListNode * head = new ListNode(1);
	//auto realHead = head;
	//for (int i = 2; i <= 2; i++){
	//	auto tmp = new ListNode(i);
	//	head->next = tmp;
	//	head = tmp;
	//}
	//removeNthFromEndEx(realHead, 2);

	//题目20
	//bool val = isValid("]");

	//题目22
	//generateParenthesis(3);

	//题目23
	//vector<ListNode*> test = { CreateList({ 1, 4, 5 }), 
	//	CreateList({1, 3, 4}), 
	//	CreateList({ 2, 6 }) };
	//mergeKLists(test);

	//题目24
	//auto test = CreateList({1, 2, 3, 4});
	//swapPairs(test);

	//浮点数精度问题研究
	/*float a = 0.1f;
	float b = 0.09f;
	float c = a - b;
	float comp = pow(10, -6);
	float comp2 = 1e-6;
	if (fabs(c - 0.01f) <= comp){
		printf("相等!");
	}
	else{
		printf("不等!");
	}*/

	/************从控制台获取输入*************/
	//printf("请输入年月：");
	//int year = 0, month = 0;
	//scanf_s("%d%d", &year, &month);
	////控制台显示月历
	//Calendar * calender = new Calendar();
	//calender->DrawCalendar(year, month);

	//题目35
	//vector<int> vec = { 1,3,5,6 };
	//int index = searchInsert(vec, 0);

	//题目36
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

	//题目38
	//string tmp = countAndSay(5);

	//vector<int> vec = {1, 2, 3, 4, 5};
	//RightMoveVector(vec, 3);

	//题目53
	//vector<int> vec = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	//int num = maxSubArray(vec);

	//题目70
	//int num = climbStairs(3);

	//题目43
	//string tmp = multiply("123", "456");

	//题目39
	//vector<int> tmp = {2, 3, 6, 7};
	//vector<vector<int>> result = combinationSum(tmp, 7);

	//题目62
	//int tmp = uniquePaths(3, 2);

	//题目136
	//vector<int> tmp = {4, 1, 2, 1, 2};
	//int result = singleNumber(tmp);

	//int arr[] = {3, 5, 6, 4, 2, 9};
	//PrintArray(arr, sizeof(arr) / sizeof(int));

//int tmp = GetArrFibonacci(7);

//MaoPaoSort(arr);
//STL提供的排序算法
int a[20] = { 2,4,1,23,5,76,0,43,24,65 };
sort(a, a + 20);
vector<int> arr = { 2, 1, 5, 4 };
sort(arr.begin(), arr.end());

	system("pause");
	return 0;
}


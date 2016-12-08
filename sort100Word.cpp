#include <iostream>      
#include <fstream>
#include <map>
#include <malloc.h>
#include <string>
#include <algorithm>
#include <regex>
using namespace std;

struct treeNode {
	string word;
	int count;
	treeNode * nextNode;
};


template <class T>
void mySwap(T & s1, T & s2) {
	T temp;
	temp = s1;
	s1 = s2;
	s2 = temp;
}

#define left(x) 2*x+1;//获得左节点在数组中的下标
#define right(x) 2 * (x + 1);//获得右节点在数组中的下标
const int heapSize = 100;

void displayList(treeNode *list) {
	treeNode * temp = (list)->nextNode;
	while (temp->nextNode != NULL) {
		cout << "word" << " " << temp->word << " " << "count" << " " << temp->count << endl;
		temp = temp->nextNode;
	}
	cout << "word" << " " << temp->word << " " << "count" << " " << temp->count << endl;
}


treeNode * findItemById(treeNode *list, int id) {
	treeNode * temp = (list)->nextNode;
	while (id--)
		temp = temp->nextNode;
	//int count =  temp->count;
	return temp;
}

void changeItemById(treeNode *list, int id, int count) {
	list = (list)->nextNode;
	while (id--)
		list = list->nextNode;
	list->count = count;
}

void swapTreeNodeById(treeNode *list, int firstId, int secondId){

	treeNode * temp = list->nextNode;
	treeNode * firstNodePoint;
	while (firstId--)
		temp = temp->nextNode;
	firstNodePoint = temp;

	temp = list->nextNode;
	treeNode * secondNodePoint;
	while (secondId--)
		temp = temp->nextNode;
	secondNodePoint = temp;

	mySwap(firstNodePoint->word, secondNodePoint->word);
	mySwap(firstNodePoint->count, secondNodePoint->count);
}

//假定对某一个节点i其左，右子树都是都是最大堆，但是对于节点i和它的左右子节点则可能破坏最大堆的性质，我们来写一个函数对这
//情况下的堆来进行维护使整体的堆满足最大堆性质

void MaxHeapify(treeNode * a, int i, int low, int high)//输入为要被排序的数组和根节点，数组a当中被维护的那一部分的下标low，high
{
	int l = left(i);//计算下标为i的节点的左子节点
	int r = right(i);//计算下标为i的节点的右子节点
	int largest;//保存i,l,r(即i和它的左右子节点)之间的最大数的下标

	int smallest;

	int temp;//交互数组中的数所使用的临时变量
			 //找到三个数当中最大的那个数，将最大的那个数和i进行互换
	if (l <= high && findItemById(a,l)->count < findItemById(a, i)->count)            
	{

		smallest = l;
	}
	else {
		smallest = i;
	}

	if (r <= high && findItemById(a, r)->count < findItemById(a, smallest)->count)
	{
		smallest = r;
	}
	if (smallest != i)
	{
		swapTreeNodeById(a, i, smallest);

		MaxHeapify(a, smallest, low, high);//交换有可能破坏子树的最大堆性质，所以对所交换的那个子节点进行一次维护，而未交换的那个子节点，根据我们的假设，是保持着最大堆性质的。
	}
}

//将数组建立为一个最大堆
//调整数组当中数的位置将其处理为一个最大堆
void BuildMaxHeap(treeNode * a, int length)
{
	for (int i = length / 2 - 1; i >= 0; i--)    //从最后一个非叶子节点开始往顶走。 即是堆顶在变化
	{
		MaxHeapify(a, i, 0, length - 1);
	}
}

//堆排序函数
void HeapSort(treeNode * a, int length)
{
	int temp;
	BuildMaxHeap(a, heapSize);
	//for (int i = 0; i < length; i++)
		//cout << findItemById(a, i) << endl;
	//cout << endl;

	for (int i = heapSize; i < length; i++) {
		if (findItemById(a, i)->count > a->nextNode->count) {
			swapTreeNodeById(a, 0, i);
			MaxHeapify(a, 0, 0, heapSize-1);
		}
	}

	for (int i = 0; i < heapSize; i++)
		cout << "Count" << " " << findItemById(a, i)->count << " " << "Word" << " " << findItemById(a,i)->word << endl;
	cout << endl;
	//for (int i = length - 1; i >= 1; i--)
	//{
	//	//交换根节点和数组的最后一个节点
	//	temp = a[i];
	//	a[i] = a[0];
	//	a[0] = temp;
	//	MaxHeapify(a, 0, 0, i - 1);//维护从下标为i-1到0的子数组          //0是堆顶 越后面的数越大。
	//}
}



int main() {
	char content[200];
	string tempStr;
	map<string, int> word_count;
	map<string, int>::iterator iter;
	fstream fs;
	treeNode * head = new treeNode [sizeof(treeNode)];
	treeNode * rear;
	rear = head;
	int textLength = 0;
	

	fs.open("test.txt", fstream::in | fstream::out | fstream::app);
	while (!fs.eof()) {
		fs.getline(content, 200);
		tempStr = content;
		if (word_count.find(tempStr) != word_count.end()) {
			word_count[tempStr]++;
		}
		else
			word_count[tempStr] = 1;
	}
	fs.close();
	
	
	for (iter = word_count.begin(); iter != word_count.end(); iter++) {
		textLength++;
		tempStr = iter->first;
		//cout << "textLength" << " " << textLength << " ";
		//cout << iter->first << " " << iter->second << endl;
		treeNode * tempPoint;
		tempPoint = new treeNode[sizeof(treeNode)];
		tempPoint->word = iter->first;
		tempPoint->count = iter->second;
		rear->nextNode = tempPoint;
		rear = tempPoint;
	}
	rear->nextNode = NULL;
	HeapSort(head, textLength);
	//displayList(head);

	return 0;
}

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

#define left(x) 2*x+1;//�����ڵ��������е��±�
#define right(x) 2 * (x + 1);//����ҽڵ��������е��±�
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

//�ٶ���ĳһ���ڵ�i�������������Ƕ������ѣ����Ƕ��ڽڵ�i�����������ӽڵ�������ƻ����ѵ����ʣ�������дһ����������
//����µĶ�������ά��ʹ����Ķ�������������

void MaxHeapify(treeNode * a, int i, int low, int high)//����ΪҪ�����������͸��ڵ㣬����a���б�ά������һ���ֵ��±�low��high
{
	int l = left(i);//�����±�Ϊi�Ľڵ�����ӽڵ�
	int r = right(i);//�����±�Ϊi�Ľڵ�����ӽڵ�
	int largest;//����i,l,r(��i�����������ӽڵ�)֮�����������±�

	int smallest;

	int temp;//���������е�����ʹ�õ���ʱ����
			 //�ҵ����������������Ǹ������������Ǹ�����i���л���
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

		MaxHeapify(a, smallest, low, high);//�����п����ƻ��������������ʣ����Զ����������Ǹ��ӽڵ����һ��ά������δ�������Ǹ��ӽڵ㣬�������ǵļ��裬�Ǳ������������ʵġ�
	}
}

//�����齨��Ϊһ������
//�������鵱������λ�ý��䴦��Ϊһ������
void BuildMaxHeap(treeNode * a, int length)
{
	for (int i = length / 2 - 1; i >= 0; i--)    //�����һ����Ҷ�ӽڵ㿪ʼ�����ߡ� ���ǶѶ��ڱ仯
	{
		MaxHeapify(a, i, 0, length - 1);
	}
}

//��������
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
	//	//�������ڵ����������һ���ڵ�
	//	temp = a[i];
	//	a[i] = a[0];
	//	a[0] = temp;
	//	MaxHeapify(a, 0, 0, i - 1);//ά�����±�Ϊi-1��0��������          //0�ǶѶ� Խ�������Խ��
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

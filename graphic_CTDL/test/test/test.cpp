#include "graphics.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma comment(lib, "graphics.lib")
using namespace std;

struct RecXY
{
	int x, y, z, t;
	int key;
	void initRec(int a, int b) {
		this->x = a;
		this->y = b;
		this->z = a + 70;
		this->t = b + 70;
 	}	
	void CreateRec()
	{
		this->printKey(x, y, z, t);
		rectangle(x, y , z, t);
	}
	void printKey(int a, int b, int c, int d)
	{
		char strKey[100];
		sprintf_s(strKey, "%d", key);
		outtextxy(a + (c - a) / 2 - 5, b + (d - b) / 2 - 5, strKey);
	}
	void movTop(int step) {
		this->printKey(x, y - step, z, t - step);
		rectangle(x, y - step, z, t - step);
		
		y -= step; 
		t -= step;
	}
	void movBottom(int step) {

		this->printKey(x, y + step, z, t + step);
		
		rectangle(x, y + step, z, t + step);
		y += step;
		t += step;
	}
	void movRight(int step) {

		this->printKey(x + step, y, z + step, t);
		
		rectangle(x + step, y, z + step, t);
		x += step;
		z += step;
	}
	void movLeft(int step) {

		this->printKey(x - step, y, z - step, t);
		
		rectangle(x - step, y, z - step, t);
		x -= step;
		z -= step;
	}
};
struct STACK
{
	int top = -1;
	RecXY stack[10];
	bool IsEmpTy()
	{
		return top < 0;
	}
	void Push(int val) {
		stack[++top].key = val;
	}
	int Pop()
	{
		if (this->IsEmpTy() == true)
		{
			return 0;
		}
		int x = stack[top--].key;
		return x;
	}
};
void nhapKey(RecXY rec[], int& n);

void swapRec(RecXY &a, RecXY &b, RecXY arr[], int n);
void swapRec_ShellSort(RecXY& a, RecXY& b, RecXY arr[], int n, RecXY gap[], int i_gap);
void swapRec_Merge(RecXY& a, RecXY& b, RecXY arr[], int n, int s, int e, int mid);
void swapRec_QuickSort(RecXY& a, RecXY& b, RecXY arr[], int n, RecXY gap[], int i_gap, RecXY pivot);

void showRec(RecXY arr[], int n);
void showRec_None(RecXY arr[], int s, int e);
void showRec_None1(RecXY arr[], int s, int e);
void showRec_NoColor(RecXY arr[], int n);
void showRec_QuickSort(RecXY arr[], int s, int e);


void bubbleSort(RecXY rec[], int n);
void selectionSort(RecXY rec[], int n);
void comparisionCounting(RecXY rec[], int n);
void insertionSort(RecXY rec[], int n);
void shellSort(RecXY rec[], int n);
int nextGap(int gap);
void inPlaceMerge(RecXY nums[], int start, int end, int n);
void mergeSort(RecXY nums[], int s, int e, int n);

int partition(RecXY rec[], int l, int h, int n, RecXY st[]);
void quickSort_1(RecXY rec[], int l, int h, int n);



int main() {
	int gd = DETECT, gm;
	initgraph(&gd, &gm, NULL);
	initwindow(1400, 600);
	
	RecXY rec[100];
	int n;
	nhapKey(rec, n);
	
	cout << "\n1.Selection Sort \n2.Bubble Sort \n3.Comparision Counting \n4.Insertion Sort \n5.Shell Sort \n6.Merge Sort \n7.Quick Sort\nNhap lua chon cua ban: ";

	int choice; cin >> choice;
	switch (choice)
	{
	case 1: 
		delay(1500);
		selectionSort(rec, n);
		break;
	case 2:
		delay(1500);
		bubbleSort(rec, n);
		break;

	case 3:
		delay(1500);
		comparisionCounting(rec, n);
		break;
	case 4:
		delay(1500);
		insertionSort(rec, n);
		break;
	case 5:
		delay(1500);
		shellSort(rec, n);
		break;
	case 6:
		delay(1500);
		mergeSort(rec, 0, n - 1, n);
		break;
	case 7:
		delay(1500);
		quickSort_1(rec, 0, n - 1, n);
		break;
	default:
		break;
	}
	getch();
	closegraph();
	return 0;
}

void nhapKey(RecXY rec[], int &n)
{
	cout << "Nhap so phan tu: "; cin >> n;
	cout << "Nhap key: ";
	rec[0].initRec(70, 150);
	for (int i = 0; i < n; i++)
	{
		cin >> rec[i].key;
	}
	for (int i = 1; i < n; i++)
	{
		rec[i].initRec(rec[i - 1].x + 100, rec[i - 1].y);
	}
}

void showRec(RecXY arr[], int n)
{
	
	for (int i = 0; i < n; i++)
	{
		arr[i].CreateRec();
		setfillstyle(EMPTY_FILL, WHITE);
		floodfill(arr[i].x + 30, arr[i].y + 30, WHITE);
	}
}
void showRec_NoColor(RecXY arr[], int n)
{

	for (int i = 0; i < n; i++)
	{
		arr[i].CreateRec();
	}
}
void showRec_None(RecXY arr[], int s, int e)
{
	
	for (int i = s; i <= e; i++)
	{
		arr[i].CreateRec();
		setfillstyle(SOLID_FILL, LIGHTBLUE);
		floodfill(arr[i].x + 30, arr[i].y + 30, WHITE);
	}
}
void showRec_None1(RecXY arr[], int s, int e)
{

	for (int i = s; i <= e; i++)
	{
		arr[i].CreateRec();
		setfillstyle(SOLID_FILL, RED);
		floodfill(arr[i].x + 30, arr[i].y + 30, WHITE);
	}
}
void showRec_QuickSort(RecXY arr[], int s, int e)
{
	for (int i = s; i <= e; i++)
	{
		arr[i].CreateRec();
		setfillstyle(SOLID_FILL, LIGHTBLUE);
		floodfill(arr[i].x + 30, arr[i].y + 30, WHITE);
	}
}
void swapRec(RecXY &a, RecXY &b, RecXY arr[], int n) {
	char mang[10] = "ARR";
	int desOfCharArr = arr[0].y + 20;
	//Cho Rec a xuong 80px, Rec b len 80px
	for (int i = 0; i < 80; i++)
	{
		showRec(arr, n);
		outtextxy(0, desOfCharArr, mang);
		a.movBottom(1);
		b.movTop(1);	
		setfillstyle(SOLID_FILL, GREEN);
		floodfill(a.x + 10, a.y + 10, WHITE);
		setfillstyle(SOLID_FILL, GREEN);
		floodfill(b.x + 10, b.y + 10, WHITE);
		delay(10);
		swapbuffers();
		cleardevice();
	}
	//Tinh khoang cach giua Rec b va Rec a
	int distance = b.x - a.x;
	for (int i = 0; i < distance; i+=3)
	{
		showRec(arr, n);
		outtextxy(0, desOfCharArr, mang);
		a.movRight(3); 
		b.movLeft(3);
		setfillstyle(SOLID_FILL, GREEN);
		floodfill(a.x + 10, a.y + 10, WHITE);
		setfillstyle(SOLID_FILL, GREEN);
		floodfill(b.x + 10, b.y + 10, WHITE);
		Sleep(10);
		swapbuffers();
		cleardevice();

	}
	//Cho Rec a len 80px, b xuong 80px
	for (int i = 0; i < 80; i++)
	{
		showRec(arr, n);
		outtextxy(0, desOfCharArr, mang);
		a.movTop(1);
		b.movBottom(1);
		setfillstyle(SOLID_FILL, GREEN);
		floodfill(a.x + 10, a.y + 10, WHITE);
		setfillstyle(SOLID_FILL, GREEN);
		floodfill(b.x + 10, b.y + 10, WHITE);

		swapbuffers();
		delay(10);
		cleardevice();
	}
		
	outtextxy(0, desOfCharArr, mang);
	showRec(arr, n);
	swapbuffers();

}
void swapRec_Merge(RecXY& a, RecXY& b, RecXY arr[], int n, int s, int e, int mid) 
{
	char mang[10] = "ARR";
	int desOfCharArr = arr[0].y + 20;
	for (int i = 0; i < 80; i++)
	{
		showRec_NoColor(arr, n);
		outtextxy(0, desOfCharArr, mang);
		
		a.movBottom(1);
		b.movTop(1);
		showRec_None(arr, s, mid + 1);
		showRec_None1(arr, mid + 1, e);
		/*setfillstyle(SOLID_FILL, GREEN);
		floodfill(a.x + 10, a.y + 10, WHITE);
		setfillstyle(SOLID_FILL, GREEN);
		floodfill(b.x + 10, b.y + 10, WHITE);*/
		delay(10);
		swapbuffers();
		cleardevice();
	}

	int distance = b.x - a.x;
	for (int i = 0; i < distance; i += 3)
	{
		showRec_NoColor(arr, n);
		outtextxy(0, desOfCharArr, mang);
		
		a.movRight(3);
		b.movLeft(3);
		showRec_None(arr, s, mid + 1);
		showRec_None1(arr, mid + 1, e);
		/*setfillstyle(SOLID_FILL, GREEN);
		floodfill(a.x + 10, a.y + 10, WHITE);
		setfillstyle(SOLID_FILL, GREEN);
		floodfill(b.x + 10, b.y + 10, WHITE);*/
		Sleep(10);
		swapbuffers();
		cleardevice();

	}
	for (int i = 0; i < 80; i++)
	{
		showRec_NoColor(arr, n);
		outtextxy(0, desOfCharArr, mang);
		
		a.movTop(1);
		b.movBottom(1);
		showRec_None(arr, s, mid + 1);
		showRec_None1(arr, mid + 1, e);
		/*setfillstyle(SOLID_FILL, GREEN);
		floodfill(a.x + 10, a.y + 10, WHITE);
		setfillstyle(SOLID_FILL, GREEN);
		floodfill(b.x + 10, b.y + 10, WHITE);*/

		swapbuffers();
		delay(10);
		cleardevice();
	}

	outtextxy(0, desOfCharArr, mang);
	showRec_NoColor(arr, n);
	swapbuffers();

}

void swapRec_ShellSort(RecXY& a, RecXY& b, RecXY arr[], int n, RecXY gap[], int i_gap) {
	char g[10] = "GAP";
	char mang[10] = "ARR";
	int desOfCharArr = arr[0].y + 20;
	for (int i = 0; i < 80; i++)
	{
		showRec(arr, n);
		showRec(gap, i_gap);
		outtextxy(0, desOfCharArr, mang);
		outtextxy(0, gap[0].y + 20, g);
		a.movBottom(1);
		b.movTop(1);
		setfillstyle(SOLID_FILL, GREEN);
		floodfill(a.x + 10, a.y + 10, WHITE);
		setfillstyle(SOLID_FILL, GREEN);
		floodfill(b.x + 10, b.y + 10, WHITE);
		setfillstyle(SOLID_FILL, LIGHTBLUE);
		floodfill(gap[i_gap - 1].x + 10, gap[i_gap - 1].y + 10, WHITE);
		swapbuffers();

		Sleep(5);
		cleardevice();
	}
	int distance = b.x - a.x;
	for (int i = 0; i < distance; i += 2)
	{
		showRec(arr, n);
		showRec(gap, i_gap);

		outtextxy(0, gap[0].y + 20, g);
		outtextxy(0, desOfCharArr, mang);

		a.movRight(2);
		b.movLeft(2);
		setfillstyle(SOLID_FILL, GREEN);
		floodfill(a.x + 10, a.y + 10, WHITE);
		setfillstyle(SOLID_FILL, GREEN);
		floodfill(b.x + 10, b.y + 10, WHITE);
		setfillstyle(SOLID_FILL, LIGHTBLUE);
		floodfill(gap[i_gap - 1].x + 10, gap[i_gap - 1].y + 10, WHITE);
		swapbuffers();
		Sleep(10);
		cleardevice();
	}
	for (int i = 0; i < 80; i++)
	{
		showRec(arr, n);
		showRec(gap, i_gap);

		outtextxy(0, gap[0].y + 20, g);
		outtextxy(0, desOfCharArr, mang);

		a.movTop(1);
		b.movBottom(1);
		setfillstyle(SOLID_FILL, GREEN);
		floodfill(a.x + 10, a.y + 10, WHITE);
		setfillstyle(SOLID_FILL, GREEN);
		floodfill(b.x + 10, b.y + 10, WHITE);
		setfillstyle(SOLID_FILL, LIGHTBLUE);
		floodfill(gap[i_gap - 1].x + 10, gap[i_gap - 1].y + 10, WHITE);
		swapbuffers();

		Sleep(5);
		cleardevice();
	}
	outtextxy(0, desOfCharArr, mang);
	showRec(arr, n);
	swapbuffers();
}
void swapRec_QuickSort(RecXY& a, RecXY& b, RecXY arr[], int n, RecXY gap[], int i_gap, RecXY pivot) 
{
	char g[10] = "STACK";
	char mang[10] = "ARR";
	int desOfCharArr = arr[0].y + 20;
	for (int i = 0; i < 80; i++)
	{
		showRec(arr, n);
		showRec(gap, i_gap);

		outtextxy(0, desOfCharArr, mang);
		outtextxy(0, gap[0].y + 20, g);
		a.movBottom(1);
		b.movTop(1);
		
		showRec_QuickSort(arr, gap[0].key, gap[1].key);

		swapbuffers();

		Sleep(5);
		cleardevice();
	}
	int distance = b.x - a.x;
	for (int i = 0; i < distance; i += 2)
	{
		showRec(arr, n);
		showRec(gap, i_gap);
		outtextxy(0, gap[0].y + 20, g);
		outtextxy(0, desOfCharArr, mang);
		a.movRight(2);
		b.movLeft(2);
		
		showRec_QuickSort(arr, gap[0].key, gap[1].key);

		swapbuffers();
		Sleep(10);
		cleardevice();
	}
	for (int i = 0; i < 80; i++)
	{
		showRec(arr, n);
		showRec(gap, i_gap);
		outtextxy(0, gap[0].y + 20, g);
		outtextxy(0, desOfCharArr, mang);
		a.movTop(1);
		b.movBottom(1);
		showRec_QuickSort(arr, gap[0].key, gap[1].key);
		swapbuffers();

		Sleep(5);
		cleardevice();
	}
	outtextxy(0, desOfCharArr, mang);
	showRec(arr, n);
	swapbuffers();
}
void bubbleSort(RecXY rec[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (rec[i].key > rec[j].key)
			{
				swapRec(rec[i], rec[j], rec, n);
				swap(rec[i], rec[j]);
			}
		}
	}
	while (1)
	{
		showRec(rec, n);
		Sleep(5000);
		break;
	}
}
void selectionSort(RecXY rec[], int n)
{
	int minKeyIndex;
	for (int i = 0; i < n - 1; i++)
	{
		minKeyIndex = i;
		for (int j = i + 1; j < n; j++)
		{
			if (rec[j].key < rec[minKeyIndex].key)
			{
				minKeyIndex = j;
			}
		}
		swapRec(rec[i], rec[minKeyIndex], rec, n);
		swap(rec[minKeyIndex], rec[i]);
	}
	for (int i = 0; i < n; i++)
	{	
		cout << rec[i].key << " ";
	}
	while (1)
	{
		showRec(rec, n);
		Sleep(5000);
		break;
	}
}
void comparisionCounting(RecXY rec[], int n) 
{
	//Tao mang count
	RecXY COUNT[100];
	char strCount[100] = "COUNT";
	char strArr[100] = "ARR";
	int y_strArr = rec[0].y + 25;
	outtextxy(0, y_strArr, strArr);
	
	COUNT[0].initRec(70, 250);
	int y_strCount = COUNT[0].y + 25;
	outtextxy(0, y_strCount, strCount);
	//Gan mang COUNT[i] = 0
	for (int i = 0; i < n; i++)
	{
		COUNT[i].key = 0;
		outtextxy(0, y_strCount, strCount);
		outtextxy(0, y_strArr, strArr);
		
	}
	for (int i = 1; i < n; i++)
	{
		COUNT[i].initRec(COUNT[i - 1].x + 100, COUNT[i - 1].y);
		outtextxy(0, y_strCount, strCount);
		outtextxy(0, y_strArr, strArr);
		
	}
	

	for (int i = n - 1; i >= 1; i--)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if (rec[i].key <= rec[j].key)
			{
				COUNT[j].key++;
				showRec(rec, n);

				showRec(COUNT, n);
				outtextxy(0, y_strCount, strCount);
				outtextxy(0, y_strArr, strArr);
				setfillstyle(SOLID_FILL, LIGHTRED);
				floodfill(COUNT[j].x + 10, COUNT[j].y + 10, WHITE);
				delay(500);
			}
			else
			{
				COUNT[i].key++;
				showRec(rec, n);

				showRec(COUNT, n);
				outtextxy(0, y_strCount, strCount);
				outtextxy(0, y_strArr, strArr);
				setfillstyle(SOLID_FILL, LIGHTBLUE);
				floodfill(COUNT[i].x + 10, COUNT[i].y + 10, WHITE);
				delay(500);

			}
		}
	}

	int P[100];
	for (int j = 0; j < n; j++)
	{
		showRec(COUNT, n);
		outtextxy(0, y_strCount, strCount);
		outtextxy(0, y_strArr, strArr);
		P[COUNT[j].key] = j;
	}
	for (int i = 0; i < n; i++)
	{
		COUNT[i].key = P[i];
		showRec(rec, n);
		showRec(COUNT, n);

		outtextxy(0, y_strCount, strCount);
		outtextxy(0, y_strArr, strArr);
		setfillstyle(SOLID_FILL, GREEN);
		floodfill(COUNT[i].x + 10, COUNT[i].y + 10, WHITE);
		setfillstyle(SOLID_FILL, GREEN);
		floodfill(COUNT[P[i]].x + 10, COUNT[P[i]].y + 10, WHITE);
		delay(700);
	}
	for (int i = 0; i < n; i++)
	{
		if (COUNT[i].key >= i)
		{
			//Di xuong 200px
			for (int j = 0; j < 200; j+=2)
			{
				showRec(rec, n);
				showRec(COUNT, n);
				outtextxy(0, y_strCount, strCount);
				outtextxy(0, y_strArr, strArr);
				rec[COUNT[i].key].movBottom(2);
				setfillstyle(SOLID_FILL, GREEN);
				floodfill(rec[COUNT[i].key].x + 10, rec[COUNT[i].key].y + 10, WHITE);
				setfillstyle(SOLID_FILL, GREEN);
				floodfill(COUNT[i].x + 10, COUNT[i].y + 10, WHITE);
				swapbuffers();
				delay(10);
				cleardevice();
			}

			outtextxy(0, y_strCount, strCount);
			outtextxy(0, y_strArr, strArr);
			//Qua trai dung vi tri
			int distance = rec[COUNT[i].key].x - COUNT[i].x;
			for (int j = 0; j < distance; j+=4)
			{
				showRec(rec, n);
				showRec(COUNT, n);
				outtextxy(0, y_strCount, strCount);
				outtextxy(0, y_strArr, strArr);

				rec[COUNT[i].key].movLeft(4);
				setfillstyle(SOLID_FILL, GREEN);
				floodfill(rec[COUNT[i].key].x + 10, rec[COUNT[i].key].y + 10, WHITE);
				setfillstyle(SOLID_FILL, GREEN);
				floodfill(COUNT[i].x + 10, COUNT[i].y + 10, WHITE);
				swapbuffers();
				delay(10);
				cleardevice();
			}

		}
		else
		{
			showRec(rec, n);
			showRec(COUNT, n);
			//Qua phai dung vi tri
			int distance = COUNT[i].x - rec[COUNT[i].key].x;
			for (int j = 0; j < distance; j+=4)
			{
				showRec(rec, n);
				outtextxy(0, y_strCount, strCount);
				outtextxy(0, y_strArr, strArr);

				showRec(COUNT, n);
				rec[COUNT[i].key].movRight(4);
				setfillstyle(SOLID_FILL, GREEN);
				floodfill(rec[COUNT[i].key].x + 10, rec[COUNT[i].key].y + 10, WHITE);
				setfillstyle(SOLID_FILL, GREEN);
				floodfill(COUNT[i].x + 10, COUNT[i].y + 10, WHITE);
				swapbuffers();
				delay(10);
				cleardevice();
				
			}
			//Di xuong 200px
			for (int j = 0; j < 200; j+=2)
			{

				showRec(rec, n);
				showRec(COUNT, n);
				outtextxy(0, y_strCount, strCount);
				outtextxy(0, y_strArr, strArr);

				rec[COUNT[i].key].movBottom(2);
				setfillstyle(SOLID_FILL, GREEN);
				floodfill(rec[COUNT[i].key].x + 10, rec[COUNT[i].key].y + 10, WHITE);
				setfillstyle(SOLID_FILL, GREEN);
				floodfill(COUNT[i].x + 10, COUNT[i].y + 10, WHITE);
				swapbuffers();
				delay(10);
				cleardevice();
				
			}
		}
		showRec(rec, n);
		showRec(COUNT, n);
		outtextxy(0, y_strCount, strCount);
		outtextxy(0, y_strArr + 200, strArr);
		swapbuffers();

	}
	for (int i = 0; i < n; i++)
	{
		cout << rec[COUNT[i].key].key << " ";
	}
}
void insertionSort(RecXY rec[], int n)
{
	char strArr[100] = "ARR";
	int y_strArr = rec[0].y + 25;
	for (int i = 1; i < n; i++)
	{

		//Di chuyen rec[i] xuong 100px
		for (int j = 0; j <= 100; j += 1)
		{
			showRec(rec, n);
			outtextxy(0, y_strArr, strArr);
			rec[i].movBottom(1);
			setfillstyle(SOLID_FILL, GREEN);
			floodfill(rec[i].x + 10, rec[i].y + 10, WHITE);
			delay(10);
			swapbuffers();
			cleardevice();
		}
		int j = i;
		RecXY temp = rec[i];
		RecXY temp1 = rec[j];
		while (j > 0 && rec[j - 1].key > temp.key)
		{
			//Di chuyen recs sang phai
			temp1 = rec[j - 1];
			for (int k = 0; k < 100; k+=2)
			{
				showRec(rec, n);
				temp.CreateRec();
				setfillstyle(SOLID_FILL, GREEN);
				floodfill(temp.x + 10, temp.y + 10, WHITE);
				outtextxy(0, y_strArr, strArr);
				rec[j - 1].movRight(2);
				setfillstyle(SOLID_FILL, LIGHTBLUE);
				floodfill(rec[j - 1].x + 10, rec[j - 1].y + 10, WHITE);
				delay(10);
				swapbuffers();
				cleardevice();
			}
			rec[j] = rec[j - 1];
			j--;
		}
		
		//Di chuyen recs sang trai
		int distance = temp.x - temp1.x; 
		for (int k = 0; k < distance; k+=2)
		{
			showRec(rec, n);
			outtextxy(0, y_strArr, strArr);
			temp.movLeft(2);
			setfillstyle(SOLID_FILL, GREEN);
			floodfill(temp.x + 10, temp.y + 10, WHITE);
			delay(10);
			swapbuffers();
			cleardevice();
		}
		
		rec[j] = temp;
		//Di chuyen len 100px
		for (int k = 0; k < 100; k += 1)
		{

			showRec(rec, n);
			outtextxy(0, y_strArr, strArr);
			rec[j].movTop(1);
			setfillstyle(SOLID_FILL, GREEN);
			floodfill(rec[j].x + 10, rec[j].y + 10, WHITE);
			delay(10);
			swapbuffers();
			cleardevice();
		}
	}

	showRec(rec, n);
	outtextxy(0, y_strArr, strArr);
	swapbuffers();
	for (int i = 0; i < n; i++)
	{
		cout << rec[i].key << " ";
	}
}
void shellSort(RecXY rec[], int n)
{
	int i, j, k, h;
	RecXY H[5];
	cout << "Nhap mang H (4 phan tu): ";
	H[0].initRec(70, 350);
	for (int i = 0; i < 4; i++)
	{
		cin >> H[i].key;
	}
	for (int i = 1; i < 4; i++)
	{
		H[i].initRec(H[i - 1].x + 100, H[i - 1].y);
	}
	for (int s = 3; s >= 0; s--)
	{
		h = H[s].key;
		for (j = h; j < n; j++)
		{
			for (k = j - h; k >= 0; k-=h)
			{
				if (rec[k + h].key >= rec[k].key)
					break;
				else
				{
					swapRec_ShellSort(rec[k], rec[k + h], rec, n, H, s + 1);
					swap(rec[k], rec[k + h]);
				}
			}
		}
	}
	showRec(rec, n);
		
}
int nextGap(int gap)
{
	if (gap <= 1)
		return 0;

	return (int)ceil(gap / 2.0);
}
void inPlaceMerge(RecXY rec[], int s, int e, int n)
{
	int gap = e - s + 1;
	int mid = (s + e) / 2;

	for (int i = 0; i < 100; i += 3)
	{
		for (int j = s; j <= mid; j++)
		{
			showRec_NoColor(rec, n);
			rec[j].movBottom(3);
			showRec_None(rec, s, mid);
			showRec_None1(rec, mid + 1, e);

			delay(10);
			swapbuffers();
			cleardevice();
		}
	}
	delay(300);

	for (int i = 0; i < 100; i += 3)
	{
		for (int j = mid + 1; j <= e; j++)
		{
			showRec_NoColor(rec, n);

			rec[j].movBottom(3);
			showRec_None(rec, s, mid);
			showRec_None1(rec, mid + 1, e);
			delay(10);

			swapbuffers();
			cleardevice();
		}

	}
	for (gap = nextGap(gap);
		gap > 0; gap = nextGap(gap))
	{
		for (int i = s; i + gap <= e; i++)
		{
			int j = i + gap;
			if (rec[i].key > rec[j].key)
			{
				swapRec_Merge(rec[i], rec[j], rec, n, s, e, (s + e) /2);
				
				swap(rec[i], rec[j]);
				showRec_None(rec, s, mid);
				showRec_None1(rec, mid + 1, e);
				delay(200);

			}
		}
	}
	for (int i = 0; i < 100; i += 4)
	{
		for (int j = s; j <= e; j++)
		{
			showRec_NoColor(rec, n);
			rec[j].movTop(4);
			showRec_None(rec, s, mid);
			showRec_None1(rec, mid + 1, e);

			delay(10);

			swapbuffers();
			cleardevice();
		}
	}

}
void mergeSort(RecXY rec[], int s, int e, int n)
{
	if (s == e)
		return;

	int mid = (s + e) / 2;

	showRec_None(rec, s, mid);
	delay(300);
	showRec_None1(rec, mid + 1, e);
	delay(300);
	mergeSort(rec, s, mid, n);


	showRec_None(rec, s, mid);
	delay(300);
	showRec_None1(rec, mid + 1, e);
	delay(300);
	mergeSort(rec, mid + 1, e, n);


	inPlaceMerge(rec, s, e, n);
	showRec(rec, n);
	
}
int partition(RecXY rec[], int l, int h, int n, RecXY st[])
{
	int x = rec[h].key;
	int i = (l - 1);
	RecXY pivot = rec[h];
	for (int j = l; j <= h - 1; j++)
	{
		if (rec[j].key <= x)
		{
			i++;
			swapRec_QuickSort(rec[i], rec[j], rec, n, st, 2, pivot);
			swap(rec[i], rec[j]);
		}
	}
	swapRec_QuickSort(rec[i + 1], rec[h], rec, n, st, 2, pivot);
	swap(rec[i + 1], rec[h]);
	return (i + 1);
}
void quickSort_1(RecXY rec[], int l, int h, int n)
{
	// Tao stack
	STACK st;

	// push index l va h vao stack
	st.Push(l);
	st.Push(h);
	st.stack[0].initRec(200, 350);
	st.stack[1].initRec(st.stack[0].x + 100, st.stack[0].y);

	for (int i = 0; i < 130; i++)
	{
		showRec(rec, n);
		st.stack[0].movLeft(1);
		st.stack[1].movLeft(1);
		swapbuffers();
		cleardevice();
		delay(10);
	}
	
	// Lap va pop cho den khi stack rong
	while (!st.IsEmpTy())
	{
		// Pop h va l
		h = st.Pop();
		l = st.Pop();
		
		// Tim vi tri pivot
		int p = partition(rec, l, h, n, st.stack);

		// Neu ma phan tu nam ben trai vi tri pivot thi xu li cac phan tu  ben trai vao stack
		if (p - 1 > l)
		{
			for (int i = 0; i < 80; i++)
			{
				showRec(rec, n);
				st.stack[0].movBottom(1);
				st.stack[1].movBottom(1);
				setfillstyle(SOLID_FILL, RED);
				floodfill(st.stack[0].x + 10, st.stack[0].y + 10, WHITE);
				setfillstyle(SOLID_FILL, RED);
				floodfill(st.stack[1].x + 10, st.stack[1].y + 10, WHITE);
				swapbuffers();
				cleardevice();
				delay(10);
			}
			delay(1000);

			
			st.stack[0].initRec(200, 350);
			st.stack[1].initRec(st.stack[0].x + 100, st.stack[0].y);
			for (int i = 0; i < 130; i++)
			{
				showRec(rec, n);
				st.stack[0].movLeft(1);
				st.stack[1].movLeft(1);
				swapbuffers();
				cleardevice();
				delay(10);
			}
			st.Push(l);
			st.Push(p - 1);
			
		}

		// Neu ma phan tu nam ben phai vi tri pivot thi xu li cac phan tu ben phai vao stack

		if (p + 1 < h)
		{
			for (int i = 0; i < 80; i++)
			{
				showRec(rec, n);
				st.stack[0].movBottom(1);
				st.stack[1].movBottom(1);
				setfillstyle(SOLID_FILL, RED);
				floodfill(st.stack[0].x + 10, st.stack[0].y + 10, WHITE);
				setfillstyle(SOLID_FILL, RED);
				floodfill(st.stack[1].x + 10, st.stack[1].y + 10, WHITE);
				swapbuffers();
				cleardevice();
				delay(10);
			}
			
			delay(1000);
			st.stack[0].initRec(200, 350);
			st.stack[1].initRec(st.stack[0].x + 100, st.stack[0].y);
			for (int i = 0; i < 130; i++)
			{
				showRec(rec, n);
				st.stack[0].movLeft(1);
				st.stack[1].movLeft(1);
				swapbuffers();
				cleardevice();
				delay(10);
			}
			st.Push(p + 1);
			st.Push(h);
		}
	}
}

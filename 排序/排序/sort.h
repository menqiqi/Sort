#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void PrintArray(int array[], int size)
{
	int i = 0;
	for(i=0; i<size; i++)
	{
		printf("%d ",array[i]);
	}
	printf("\n");
}


//直接插入排序（从后往前顺序找）
//可以做到稳定
//时间复杂度：最坏(O(n^2)),平均(O(n^2)),最好（O(n)）
void InsertSort(int array[], int size)
{
	int i,j,key;
	//第一个数默认有序，所以从第二个数开始向前排序，保证要排序的数的前面是有序的
	for(i=1; i<size; i++)
	{
		key = array[i];
		for(j=i-1; i>=0; j--)
		{
			if(key < array[j])
			{
				//如果不满足升序，找到要插入的位置，把原来位置上的数顺序后移
				array[j+1] = array[j];
			}
			else{
				break;
			}
		}
		//要排序的数插入到正确位置上
		array[j+1] = key;
	}
}

//直接插入排序（二分查找）
//可以做到稳定
//时间复杂度：最优情况:O(n)  平均情况:O(n^2)  最差情况:O(n^2)
void InsertSortBinary(int array[], int size)
{
	int i,j,key,left,right,mid;
	for(i=1; i<size; i++)
	{
		left = 0;
		right = i-1;
		key = array[i];
		while(left <= right)
		{
			mid = left+(right-left)/2;
			if(key < array[mid])
			{
				right = mid - 1;
			}
			else{
				left = mid + 1;
			}
		}
		for(j=i; j>left; j--)
		{
			array[j] = array[j-1];
		}
		array[left] = key;
	}
}


//希尔排序
//不稳定
//时间复杂度 O（n^1,2~1.3）
void ShellSort(int array[], int size)
{
	int g,i,j;
	int gap = size;
	int key;

	//当gap不为1时，是预排序，当gap==1时，进行插入排序
	while(1)
	{
		gap = gap/3+1; //这种分组的方法只是一个经验值，并没有什么特别的含义

		//一共排gap组
		for(g=0; g<gap; g++)
		{
			//分别按组进行插排
			for(i=g+gap; i<size; i+=gap)
			{
				key = array[i];
				for(j=i-gap; j>=0; j-=gap)
				{
					if(key < array[j])
					{
						array[j+gap] = array[j];
					}
					else{
						break;
					}
				}
				array[j+gap] = key;
			}
		}
		if(gap == 1)
		{
			break;
		}
	}
}

void Swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

//堆排序(升序，建大堆)
//向下调整
void AdjustDown(int array[], int size, int root)
{
	int left;
	int right,maxChild;
	while(1){
		left = root*2+1;
		right = root*2+2;
	if(left >= size)
	{
		return;
	}
	maxChild = left;
	if(right<size && array[right]>array[left])
	{
		maxChild = right;
	}
	if(array[maxChild] <= array[root])
	{
		return;
	}
		Swap(array+maxChild, array+root);
		root = maxChild;
	}
}

void HeapSort(int array[], int size)
{
	int i = 0;
	int j = 0;
	//建堆
	//从最后一个叶子节点的双亲节点开始向下调整
	for(i=(size-2)/2; i>=0; i--)
	{
		AdjustDown(array, size, i);
	}

	//排序
	for(j=size-1; j>=0; j--)
	{
		Swap(array+j, array);
		AdjustDown(array, j, 0);
	}
}

//选择排序（每次排最大的和最小的）
//时间复杂度:O(n^2)
//不稳定
void SelectSort(int array[], int size)
{
	int i;
	int maxPos,minPos;//下标
	int minSpace = 0;
	int maxSpace = size-1;
	while(minSpace < maxSpace)
	{
	minPos = minSpace;
	maxPos = minSpace;
	for(i=minSpace+1; i<=maxSpace; i++)
	{
		if(array[i] < array[minPos])
		{
			minPos = i;
		}
		if(array[i] > array[maxPos])
		{
			maxPos = i;
		}
	}
	Swap(array+minSpace, array+minPos);
	if(minSpace == maxPos)
	{
		maxPos = minPos;
	}//不要漏掉这一点
	Swap(array+maxSpace, array+maxPos);
	minSpace++;
	maxSpace--;
	}
}

//冒泡排序
//时间复杂度：最好的情况:O(n) 最差的情况:O(n^2)
//稳定
void BubbleSort(int array[], int size)
{
	int i = 0;
	int j = 0;
	int flag ;
	for(i=0; i<size; i++)
	{
		flag = 1;//假设已经有序了
		for(j=0; j<size-1-i; j++)
		{
			if(array[j] > array[j+1])
			{
				Swap(array+j, array+j+1);
				flag = 0;
			}
		}
		if(flag == 1)
			break;
	}
}

//将区间按照基准值划分为左右两半部分有三种方法：
//1.Hoare版本（左右指针法）
//2.挖坑法
//3.前后指针法
//选的基准值放右边，所以要先动begin
int Partion_1(int array[], int left, int right)
{
	int pivot = array[right];
	int begin = left;
	int end = right;
	while(begin < end)
	{
		//需要在条件里判断begin和end的关系
		while(begin<end && array[begin]<=pivot)
		{
			begin++;
		}
		if(begin == end)
		{
			break;
		}
		while(begin<end && array[end]>=pivot)
		{
			end--;
		}
		if(begin == end)
		{
			break;
		}
		Swap(array+begin, array+end);
	}
	Swap(array+begin, array+right);

	return begin;
}

//先记下pivot
//从begin开始遍历，小的数放在左边，遇到小的数继续往前走，遇到大的数时，把该数填在刚才挖好的坑里（end）
//从end开始遍历，遇到大的数继续走，遇到小的数填在刚才的坑里（begin）
int Partion_2(int array[], int left, int right)
{
	int pivot = array[right];
	int begin = left;
	int end = right;
	while(begin < end)
	{
		while(begin<end && array[begin]<=pivot)
		{
			begin++;
		}
		if(begin == end)
		{
			break;
		}
		array[end] = array[begin];
		
		while(begin<end && array[end]>=pivot)
		{
			end--;
		}
		if(begin == end)
		{
			break;
		}
		array[begin] = array[end];
	}
	array[begin] = pivot;
	return begin;
}

//div之前是比pivot小的数
//div和cur之间是比pivot大的数
//最后一个是基准值
//交换好之后把最后一个数和div交换
int Partion_3(int array[], int left, int right)
{
	int pivot = array[right];
	int div = left;
	int cur = left;
	for(cur = left; cur <= right; cur++)
	{
		if(array[cur] < pivot)
		{
			Swap(array+cur, array+div);
			div++;
		}
	}
	Swap(array+right, array+div);
	return div;
}

void __QuickSort(int array[], int left, int right)
{
	//选取基准值：选最右边的为基准值
	int pivot = array[right];
	int div;
	if(left == right)
	{
		//区间只剩一个数，不需要再排序
		return;
	}
	if(left > right)
	{
		//区间没有数了，不需要排序
		return;
	}
	div = Partion_3(array, left, right);
	//[div]放基准值
	__QuickSort(array, left, div-1);
	__QuickSort(array, div+1, right);
}

//快速排序
void QuickSort(int array[], int size)
{
	__QuickSort(array, 0, size-1);
}

//合并
void Merge(int array[], int left, int mid, int right, int extra[])
{
	int left_i = left;//左边的区间的下标
	int right_i = mid;//右边区间的下标
	int extra_i = left;//新区间的下标
	while(left_i<mid && right_i<right){
	if(array[left_i] <= array[right_i])
	{
		extra[extra_i] = array[left_i];
		extra_i++;
		left_i++;
	}
	else{
		extra[extra_i] = array[right_i];
		extra_i++;
		right_i++;
	}
	}
	while(left_i < mid)
	{
		extra[extra_i++] = array[left_i++];
	}
	while(right_i < right)
	{
		extra[extra_i++] = array[right_i++];
	}
	memcpy(array+left, extra+left, sizeof(int)*(right-left));
}

//划分
void __MergeSort(int array[], int left, int right, int extra[])
{
	int mid;
	if(left == right-1)
	{
		//区间内只剩一个数
		return;
	}
	if(left >= right)
	{
		//区间内没有数
		return;
	}
	mid = left+(right-left)/2;
	//把mid放在右边的区间内
	//左边的区间：[left,mid)
	//右边的区间：[mid,right)
	__MergeSort(array, left, mid, extra);
	__MergeSort(array, mid, right, extra);
	Merge(array, left, mid, right, extra);
}



//归并排序
void MergeSort(int array[], int size)
{
	int *extra = (int *)malloc(sizeof(int)*size);
	__MergeSort(array, 0, size, extra);
	free(extra);
}

void Test()
{
	int array[] = {9,7,8,4,1,0,5,6,3,2};
	int size = sizeof(array)/sizeof(array[0]);

	/*printf("直接插入排序（从后往前顺序找）：\n");
	InsertSort(array, size);
	PrintArray(array, size);

	printf("直接插入排序（二分查找）：\n");
	InsertSortBinary(array, size);
	PrintArray(array, size);*/

	/*printf("希尔排序：\n");
	ShellSort(array, size);
	PrintArray(array, size);*/

	printf("堆排序:\n");
	HeapSort(array, size);
	PrintArray(array, size);

	/*printf("选择排序:\n");
	SelectSort(array, size);
	PrintArray(array, size);*/

	/*printf("冒泡排序:\n");
	BubbleSort(array, size);
	PrintArray(array, size);*/

	/*printf("快速排序:\n");
	QuickSort(array, size);
	PrintArray(array, size);*/

	/*printf("归并排序:\n");
	MergeSort(array, size);
	PrintArray(array, size);*/
}
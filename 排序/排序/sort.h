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


//ֱ�Ӳ������򣨴Ӻ���ǰ˳���ң�
//���������ȶ�
//ʱ�临�Ӷȣ��(O(n^2)),ƽ��(O(n^2)),��ã�O(n)��
void InsertSort(int array[], int size)
{
	int i,j,key;
	//��һ����Ĭ���������Դӵڶ�������ʼ��ǰ���򣬱�֤Ҫ���������ǰ���������
	for(i=1; i<size; i++)
	{
		key = array[i];
		for(j=i-1; i>=0; j--)
		{
			if(key < array[j])
			{
				//��������������ҵ�Ҫ�����λ�ã���ԭ��λ���ϵ���˳�����
				array[j+1] = array[j];
			}
			else{
				break;
			}
		}
		//Ҫ����������뵽��ȷλ����
		array[j+1] = key;
	}
}

//ֱ�Ӳ������򣨶��ֲ��ң�
//���������ȶ�
//ʱ�临�Ӷȣ��������:O(n)  ƽ�����:O(n^2)  ������:O(n^2)
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


//ϣ������
//���ȶ�
//ʱ�临�Ӷ� O��n^1,2~1.3��
void ShellSort(int array[], int size)
{
	int g,i,j;
	int gap = size;
	int key;

	//��gap��Ϊ1ʱ����Ԥ���򣬵�gap==1ʱ�����в�������
	while(1)
	{
		gap = gap/3+1; //���ַ���ķ���ֻ��һ������ֵ����û��ʲô�ر�ĺ���

		//һ����gap��
		for(g=0; g<gap; g++)
		{
			//�ֱ�����в���
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

//������(���򣬽����)
//���µ���
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
	//����
	//�����һ��Ҷ�ӽڵ��˫�׽ڵ㿪ʼ���µ���
	for(i=(size-2)/2; i>=0; i--)
	{
		AdjustDown(array, size, i);
	}

	//����
	for(j=size-1; j>=0; j--)
	{
		Swap(array+j, array);
		AdjustDown(array, j, 0);
	}
}

//ѡ������ÿ�������ĺ���С�ģ�
//ʱ�临�Ӷ�:O(n^2)
//���ȶ�
void SelectSort(int array[], int size)
{
	int i;
	int maxPos,minPos;//�±�
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
	}//��Ҫ©����һ��
	Swap(array+maxSpace, array+maxPos);
	minSpace++;
	maxSpace--;
	}
}

//ð������
//ʱ�临�Ӷȣ���õ����:O(n) �������:O(n^2)
//�ȶ�
void BubbleSort(int array[], int size)
{
	int i = 0;
	int j = 0;
	int flag ;
	for(i=0; i<size; i++)
	{
		flag = 1;//�����Ѿ�������
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

//�����䰴�ջ�׼ֵ����Ϊ�������벿�������ַ�����
//1.Hoare�汾������ָ�뷨��
//2.�ڿӷ�
//3.ǰ��ָ�뷨
//ѡ�Ļ�׼ֵ���ұߣ�����Ҫ�ȶ�begin
int Partion_1(int array[], int left, int right)
{
	int pivot = array[right];
	int begin = left;
	int end = right;
	while(begin < end)
	{
		//��Ҫ���������ж�begin��end�Ĺ�ϵ
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

//�ȼ���pivot
//��begin��ʼ������С����������ߣ�����С����������ǰ�ߣ����������ʱ���Ѹ������ڸղ��ںõĿ��end��
//��end��ʼ��������������������ߣ�����С�������ڸղŵĿ��begin��
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

//div֮ǰ�Ǳ�pivotС����
//div��cur֮���Ǳ�pivot�����
//���һ���ǻ�׼ֵ
//������֮������һ������div����
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
	//ѡȡ��׼ֵ��ѡ���ұߵ�Ϊ��׼ֵ
	int pivot = array[right];
	int div;
	if(left == right)
	{
		//����ֻʣһ����������Ҫ������
		return;
	}
	if(left > right)
	{
		//����û�����ˣ�����Ҫ����
		return;
	}
	div = Partion_3(array, left, right);
	//[div]�Ż�׼ֵ
	__QuickSort(array, left, div-1);
	__QuickSort(array, div+1, right);
}

//��������
void QuickSort(int array[], int size)
{
	__QuickSort(array, 0, size-1);
}

//�ϲ�
void Merge(int array[], int left, int mid, int right, int extra[])
{
	int left_i = left;//��ߵ�������±�
	int right_i = mid;//�ұ�������±�
	int extra_i = left;//��������±�
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

//����
void __MergeSort(int array[], int left, int right, int extra[])
{
	int mid;
	if(left == right-1)
	{
		//������ֻʣһ����
		return;
	}
	if(left >= right)
	{
		//������û����
		return;
	}
	mid = left+(right-left)/2;
	//��mid�����ұߵ�������
	//��ߵ����䣺[left,mid)
	//�ұߵ����䣺[mid,right)
	__MergeSort(array, left, mid, extra);
	__MergeSort(array, mid, right, extra);
	Merge(array, left, mid, right, extra);
}



//�鲢����
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

	/*printf("ֱ�Ӳ������򣨴Ӻ���ǰ˳���ң���\n");
	InsertSort(array, size);
	PrintArray(array, size);

	printf("ֱ�Ӳ������򣨶��ֲ��ң���\n");
	InsertSortBinary(array, size);
	PrintArray(array, size);*/

	/*printf("ϣ������\n");
	ShellSort(array, size);
	PrintArray(array, size);*/

	printf("������:\n");
	HeapSort(array, size);
	PrintArray(array, size);

	/*printf("ѡ������:\n");
	SelectSort(array, size);
	PrintArray(array, size);*/

	/*printf("ð������:\n");
	BubbleSort(array, size);
	PrintArray(array, size);*/

	/*printf("��������:\n");
	QuickSort(array, size);
	PrintArray(array, size);*/

	/*printf("�鲢����:\n");
	MergeSort(array, size);
	PrintArray(array, size);*/
}
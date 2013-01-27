// ManRevier.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}


/*颜海镜 模拟商人过河，任意商人任意仆人
要求n个商人，m个仆人，在河的一案摆渡到另一按，每次只能载2个人
若仆人数大于商人数失败
代码已完成，释放所有节点没有内存泄漏
程序全部用结构体存储
代码尚未优化
2011.12.18	颜海镜 于保定
*/
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>
#include<time.h>
#include"MyListControlApi.h"

int iNum=0;//存储结果数量
int iNumBerBack=0;//回溯的次数

int ResultOutPrint(struct sresult *pSubHead)
{
	struct sresult *sSubTempPointer;//只是变量
	iNum++;//每次结果加1技术
	sSubTempPointer=pSubHead;
	printf("第%d种答案\n",iNum);
	printf("此岸	彼岸	船上人数	方向\n");
	while(sSubTempPointer!=NULL)
	{
		printf("(%d,%d)	(%d,%d)	 (%d,%d)		%c\n",sSubTempPointer->iThisMan,sSubTempPointer->iThisRetainer,sSubTempPointer->iThatMan,sSubTempPointer->iThatRetainer,sSubTempPointer->sStructShip.iMan,sSubTempPointer->sStructShip.iRetainer,sSubTempPointer->sStructShip.cFlag);
		sSubTempPointer=sSubTempPointer->pNext;
	}
	
	return 0;
}

int BackTrack(int iSubThisMan,int iSubThisRetainer,int iSubThatMan,int iSubThatRetainer,struct sresult *pSubHead,struct sresult *pSubTail,struct sship sSubShip)
{
	//定义局部变量避免回复
	int iSubTempThisMan;
	int iSubTempThisRetainer;
	int iSubTempThatMan;
	int iSubTempThatRetainer;
	int i;//计数器'
	struct sresult *sSubTempPointer;//申请新节点用，即为本层节点释放用
	struct sresult *sSubPointCurrent;//指针变量，指示当前节点，避免死循环用
	struct sresult *sSubPointPrevious;//当前节点的前一个节点

	if(iSubThisMan==0&&iSubThisRetainer==0)//结束
	{
		//打印输出结果，并且释放本曾节点
		ResultOutPrint(pSubHead);
		iNumBerBack++;
		return 1;
	}
	//申请空间
	sSubTempPointer=(struct sresult *)malloc(sizeof(struct sresult));
	if(!sSubTempPointer) exit(0);
	sSubTempPointer->pNext=NULL;
	pSubTail->pNext=sSubTempPointer;//新申请空间连接到链上
	sSubPointPrevious=pSubTail;//保存当前节点的前一个节点
	pSubTail=pSubTail->pNext;//尾节点后移

	//船在this bank
	if(sSubShip.cFlag=='S')
	{
		for(i=0;i<5;i++)
		{
			int iFlag=0;//为0就没有走过
			//每次初始化临时变量为上次的变量
			iSubTempThisMan=iSubThisMan;
			iSubTempThisRetainer=iSubThisRetainer;
			iSubTempThatMan=iSubThatMan;
			iSubTempThatRetainer=iSubThatRetainer;

			//五种情况
			if(i==0) {iSubTempThisMan-=2;iSubTempThatMan+=2;}
			if(i==1) {iSubTempThisMan-=1;iSubTempThatMan+=1;}
			if(i==2) {iSubTempThisRetainer-=2;iSubTempThatRetainer+=2;}
			if(i==3) {iSubTempThisRetainer-=1;iSubTempThatRetainer+=1;}
			if(i==4) {iSubTempThisMan-=1;iSubTempThisRetainer-=1;iSubTempThatMan+=1;iSubTempThatRetainer+=1;}

			if ((iSubTempThisMan>pSubHead->iThisMan||iSubTempThatMan>pSubHead->iThisMan)||(iSubTempThisRetainer>pSubHead->iThisRetainer||iSubTempThatRetainer>pSubHead->iThisRetainer)) iFlag=1;//运完后人数不能增多即，此岸有1个商人不能向对岸运2个
			if ((iSubTempThisMan!=0)&&iSubTempThisMan<iSubTempThisRetainer||(iSubTempThatMan!=0&&iSubTempThatMan<iSubTempThatRetainer)) iFlag=1;//运完后不能造成商铺人数大于商人数若商人数不为0

			//避免死循环，检查链表直到当前项的前一项
			if(!iFlag)
			{
				sSubPointCurrent=pSubHead;//当前节点指向头结点
				while(sSubPointCurrent!=sSubTempPointer)
				{
					//判断是否已经有过
					if(sSubPointCurrent->sStructShip.cFlag=='T'&&(sSubPointCurrent->iThisMan==iSubTempThisMan&&sSubPointCurrent->iThisRetainer==iSubTempThisRetainer))
					{
						iFlag=1;
						break;
					}
					sSubPointCurrent=sSubPointCurrent->pNext;//当前指针只想下一个元素
				}
			}

			//判断标志位从而判断是否走过
			if(iFlag!=1) 
			{
				struct sship sSubTempShip;
				//给船赋值//初始化下层船值
				sSubTempShip.iMan=abs(iSubThisMan-iSubTempThisMan);
				sSubTempShip.iRetainer=abs(iSubThisRetainer-iSubTempThisRetainer);
				sSubTempShip.cFlag='T';
				//可以运修改当前层值
				sSubTempPointer->iThisMan=iSubTempThisMan;
				sSubTempPointer->iThisRetainer=iSubTempThisRetainer;
				sSubTempPointer->iThatMan=iSubTempThatMan;
				sSubTempPointer->iThatRetainer=iSubTempThatRetainer;
				sSubTempPointer->sStructShip=sSubTempShip;

				//能运递归调用自己
				BackTrack(iSubTempThisMan,iSubTempThisRetainer,iSubTempThatMan,iSubTempThatRetainer,pSubHead,pSubTail,sSubTempShip);
			}
		}
		//本层结束要释放本曾的值
		MyFree(sSubPointPrevious,sSubTempPointer);
		iNumBerBack++;
		return 2;
	}
	
	//船在that bank
	for(i=0;i<5;i++)
	{
		int iFlag=0;//为0就没有走过
		//每次初始化临时变量为上次的变量
		iSubTempThisMan=iSubThisMan;
		iSubTempThisRetainer=iSubThisRetainer;
		iSubTempThatMan=iSubThatMan;
		iSubTempThatRetainer=iSubThatRetainer;
		//五种情况
		if(i==0) {iSubTempThisMan+=2;iSubTempThatMan-=2;}
		if(i==1) {iSubTempThisMan+=1;iSubTempThatMan-=1;}
		if(i==2) {iSubTempThisRetainer+=2;iSubTempThatRetainer-=2;}
		if(i==3) {iSubTempThisRetainer+=1;iSubTempThatRetainer-=1;}
		if(i==4) {iSubTempThisMan+=1;iSubTempThisRetainer+=1;iSubTempThatMan-=1;iSubTempThatRetainer-=1;}

		//判断是否可行,运后仆人数不能大于商人数
		if ((iSubTempThisMan>pSubHead->iThisMan||iSubTempThatMan>pSubHead->iThisMan)||(iSubTempThisRetainer>pSubHead->iThisRetainer||iSubTempThatRetainer>pSubHead->iThisRetainer)) iFlag=1;//运完后人数不能增多即，此岸有1个商人不能向对岸运2个
		if ((iSubTempThisMan!=0)&&iSubTempThisMan<iSubTempThisRetainer||(iSubTempThatMan!=0&&iSubTempThatMan<iSubTempThatRetainer)) iFlag=1;

		//避免死循环，检查链表直到当前项的前一项
		if(!iFlag)
		{
			sSubPointCurrent=pSubHead;//当前节点指向头结点
			while(sSubPointCurrent!=sSubTempPointer)
			{
				//判断是否已经有过
				if(sSubPointCurrent->sStructShip.cFlag=='S'&&(sSubPointCurrent->iThisMan== iSubTempThisMan&&sSubPointCurrent->iThisRetainer==iSubTempThisRetainer))
				{
					iFlag=1;
					break;
				}
				sSubPointCurrent=sSubPointCurrent->pNext;//当前指针只想下一个元素
			}
		}

		//判断标志位从而判断是否走过
		if(iFlag!=1) 
		{
			struct sship sSubTempShip;
			//给船赋值//初始化下层船值
			sSubTempShip.iMan=abs(iSubThisMan-iSubTempThisMan);
			sSubTempShip.iRetainer=abs(iSubThisRetainer-iSubTempThisRetainer);
			sSubTempShip.cFlag='S';
			//可以运修改当前层值
			sSubTempPointer->iThisMan=iSubTempThisMan;
			sSubTempPointer->iThisRetainer=iSubTempThisRetainer;
			sSubTempPointer->iThatMan=iSubTempThatMan;
			sSubTempPointer->iThatRetainer=iSubTempThatRetainer;
			sSubTempPointer->sStructShip=sSubTempShip;

			//能运递归调用自己
			BackTrack(iSubTempThisMan,iSubTempThisRetainer,iSubTempThatMan,iSubTempThatRetainer,pSubHead,pSubTail,sSubTempShip);
		}
	}
	//本层结束要释放本曾的值
	MyFree(sSubPointPrevious,sSubTempPointer);
	iNumBerBack++;
	return 0;
}

int main()
{
	int iThisMan;
	int iThisRetainer;
	int iThatMan=0;
	int iThatRetainer=0;
	clock_t start, finish;
	double duration;
	while(1)
	{
		iNum=0;//初始化
		iNumBerBack=0;//初始化回溯的次数
		printf("请输入商人 仆人的数目（商人不能小于仆人数）");
		scanf("%d %d",&iThisMan,&iThisRetainer);
		start = clock(); //开始计时
		//pHead为结果链表的头指针为空，pTail为尾指针
		struct sresult *pHead=NULL;
		struct sresult *pTail=pHead;
		struct sship sShip;

		//初始化
		sShip.cFlag='S';//船在this bank
		sShip.iMan=0;
		sShip.iRetainer=0;

		if((pHead=(struct sresult *)malloc(sizeof(struct sresult)))==NULL) exit(1);//为头结点申请空间，判断是否成功
		pTail=pHead;//头尾指向同一点
		pHead->iThisMan=iThisMan;
		pHead->iThisRetainer=iThisRetainer;
		pHead->iThatMan=iThatMan;
		pHead->iThatRetainer=iThatRetainer;
		pHead->sStructShip=sShip;

		//调用函数回溯
		BackTrack(iThisMan,iThisRetainer,iThatMan,iThatRetainer,pHead,pTail,sShip);

		//释放头节点
		free(pHead);
		//free(pTail);
		pHead=NULL;
		pTail=NULL;
		
		printf("共产生%d次回溯",iNumBerBack);
		finish = clock();
		duration = (double)(finish - start)/CLOCKS_PER_SEC; 
		printf( "%f seconds\n", duration ); 
		float flAverageTime=duration/iNumBerBack;
		printf("平均每次回溯耗费%f s",flAverageTime);
		printf("\n结束若没有结果证明没有答案");
		system("pause");
	}
	return 0;
}

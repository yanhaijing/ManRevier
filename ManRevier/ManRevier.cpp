// ManRevier.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}


/*�պ��� ģ�����˹��ӣ�����������������
Ҫ��n�����ˣ�m�����ˣ��ںӵ�һ���ڶɵ���һ����ÿ��ֻ����2����
������������������ʧ��
��������ɣ��ͷ����нڵ�û���ڴ�й©
����ȫ���ýṹ��洢
������δ�Ż�
2011.12.18	�պ��� �ڱ���
*/
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>
#include<time.h>
#include"MyListControlApi.h"

int iNum=0;//�洢�������
int iNumBerBack=0;//���ݵĴ���

int ResultOutPrint(struct sresult *pSubHead)
{
	struct sresult *sSubTempPointer;//ֻ�Ǳ���
	iNum++;//ÿ�ν����1����
	sSubTempPointer=pSubHead;
	printf("��%d�ִ�\n",iNum);
	printf("�˰�	�˰�	��������	����\n");
	while(sSubTempPointer!=NULL)
	{
		printf("(%d,%d)	(%d,%d)	 (%d,%d)		%c\n",sSubTempPointer->iThisMan,sSubTempPointer->iThisRetainer,sSubTempPointer->iThatMan,sSubTempPointer->iThatRetainer,sSubTempPointer->sStructShip.iMan,sSubTempPointer->sStructShip.iRetainer,sSubTempPointer->sStructShip.cFlag);
		sSubTempPointer=sSubTempPointer->pNext;
	}
	
	return 0;
}

int BackTrack(int iSubThisMan,int iSubThisRetainer,int iSubThatMan,int iSubThatRetainer,struct sresult *pSubHead,struct sresult *pSubTail,struct sship sSubShip)
{
	//����ֲ���������ظ�
	int iSubTempThisMan;
	int iSubTempThisRetainer;
	int iSubTempThatMan;
	int iSubTempThatRetainer;
	int i;//������'
	struct sresult *sSubTempPointer;//�����½ڵ��ã���Ϊ����ڵ��ͷ���
	struct sresult *sSubPointCurrent;//ָ�������ָʾ��ǰ�ڵ㣬������ѭ����
	struct sresult *sSubPointPrevious;//��ǰ�ڵ��ǰһ���ڵ�

	if(iSubThisMan==0&&iSubThisRetainer==0)//����
	{
		//��ӡ�������������ͷű����ڵ�
		ResultOutPrint(pSubHead);
		iNumBerBack++;
		return 1;
	}
	//����ռ�
	sSubTempPointer=(struct sresult *)malloc(sizeof(struct sresult));
	if(!sSubTempPointer) exit(0);
	sSubTempPointer->pNext=NULL;
	pSubTail->pNext=sSubTempPointer;//������ռ����ӵ�����
	sSubPointPrevious=pSubTail;//���浱ǰ�ڵ��ǰһ���ڵ�
	pSubTail=pSubTail->pNext;//β�ڵ����

	//����this bank
	if(sSubShip.cFlag=='S')
	{
		for(i=0;i<5;i++)
		{
			int iFlag=0;//Ϊ0��û���߹�
			//ÿ�γ�ʼ����ʱ����Ϊ�ϴεı���
			iSubTempThisMan=iSubThisMan;
			iSubTempThisRetainer=iSubThisRetainer;
			iSubTempThatMan=iSubThatMan;
			iSubTempThatRetainer=iSubThatRetainer;

			//�������
			if(i==0) {iSubTempThisMan-=2;iSubTempThatMan+=2;}
			if(i==1) {iSubTempThisMan-=1;iSubTempThatMan+=1;}
			if(i==2) {iSubTempThisRetainer-=2;iSubTempThatRetainer+=2;}
			if(i==3) {iSubTempThisRetainer-=1;iSubTempThatRetainer+=1;}
			if(i==4) {iSubTempThisMan-=1;iSubTempThisRetainer-=1;iSubTempThatMan+=1;iSubTempThatRetainer+=1;}

			if ((iSubTempThisMan>pSubHead->iThisMan||iSubTempThatMan>pSubHead->iThisMan)||(iSubTempThisRetainer>pSubHead->iThisRetainer||iSubTempThatRetainer>pSubHead->iThisRetainer)) iFlag=1;//����������������༴���˰���1�����˲�����԰���2��
			if ((iSubTempThisMan!=0)&&iSubTempThisMan<iSubTempThisRetainer||(iSubTempThatMan!=0&&iSubTempThatMan<iSubTempThatRetainer)) iFlag=1;//��������������������������������������Ϊ0

			//������ѭ�����������ֱ����ǰ���ǰһ��
			if(!iFlag)
			{
				sSubPointCurrent=pSubHead;//��ǰ�ڵ�ָ��ͷ���
				while(sSubPointCurrent!=sSubTempPointer)
				{
					//�ж��Ƿ��Ѿ��й�
					if(sSubPointCurrent->sStructShip.cFlag=='T'&&(sSubPointCurrent->iThisMan==iSubTempThisMan&&sSubPointCurrent->iThisRetainer==iSubTempThisRetainer))
					{
						iFlag=1;
						break;
					}
					sSubPointCurrent=sSubPointCurrent->pNext;//��ǰָ��ֻ����һ��Ԫ��
				}
			}

			//�жϱ�־λ�Ӷ��ж��Ƿ��߹�
			if(iFlag!=1) 
			{
				struct sship sSubTempShip;
				//������ֵ//��ʼ���²㴬ֵ
				sSubTempShip.iMan=abs(iSubThisMan-iSubTempThisMan);
				sSubTempShip.iRetainer=abs(iSubThisRetainer-iSubTempThisRetainer);
				sSubTempShip.cFlag='T';
				//�������޸ĵ�ǰ��ֵ
				sSubTempPointer->iThisMan=iSubTempThisMan;
				sSubTempPointer->iThisRetainer=iSubTempThisRetainer;
				sSubTempPointer->iThatMan=iSubTempThatMan;
				sSubTempPointer->iThatRetainer=iSubTempThatRetainer;
				sSubTempPointer->sStructShip=sSubTempShip;

				//���˵ݹ�����Լ�
				BackTrack(iSubTempThisMan,iSubTempThisRetainer,iSubTempThatMan,iSubTempThatRetainer,pSubHead,pSubTail,sSubTempShip);
			}
		}
		//�������Ҫ�ͷű�����ֵ
		MyFree(sSubPointPrevious,sSubTempPointer);
		iNumBerBack++;
		return 2;
	}
	
	//����that bank
	for(i=0;i<5;i++)
	{
		int iFlag=0;//Ϊ0��û���߹�
		//ÿ�γ�ʼ����ʱ����Ϊ�ϴεı���
		iSubTempThisMan=iSubThisMan;
		iSubTempThisRetainer=iSubThisRetainer;
		iSubTempThatMan=iSubThatMan;
		iSubTempThatRetainer=iSubThatRetainer;
		//�������
		if(i==0) {iSubTempThisMan+=2;iSubTempThatMan-=2;}
		if(i==1) {iSubTempThisMan+=1;iSubTempThatMan-=1;}
		if(i==2) {iSubTempThisRetainer+=2;iSubTempThatRetainer-=2;}
		if(i==3) {iSubTempThisRetainer+=1;iSubTempThatRetainer-=1;}
		if(i==4) {iSubTempThisMan+=1;iSubTempThisRetainer+=1;iSubTempThatMan-=1;iSubTempThatRetainer-=1;}

		//�ж��Ƿ����,�˺����������ܴ���������
		if ((iSubTempThisMan>pSubHead->iThisMan||iSubTempThatMan>pSubHead->iThisMan)||(iSubTempThisRetainer>pSubHead->iThisRetainer||iSubTempThatRetainer>pSubHead->iThisRetainer)) iFlag=1;//����������������༴���˰���1�����˲�����԰���2��
		if ((iSubTempThisMan!=0)&&iSubTempThisMan<iSubTempThisRetainer||(iSubTempThatMan!=0&&iSubTempThatMan<iSubTempThatRetainer)) iFlag=1;

		//������ѭ�����������ֱ����ǰ���ǰһ��
		if(!iFlag)
		{
			sSubPointCurrent=pSubHead;//��ǰ�ڵ�ָ��ͷ���
			while(sSubPointCurrent!=sSubTempPointer)
			{
				//�ж��Ƿ��Ѿ��й�
				if(sSubPointCurrent->sStructShip.cFlag=='S'&&(sSubPointCurrent->iThisMan== iSubTempThisMan&&sSubPointCurrent->iThisRetainer==iSubTempThisRetainer))
				{
					iFlag=1;
					break;
				}
				sSubPointCurrent=sSubPointCurrent->pNext;//��ǰָ��ֻ����һ��Ԫ��
			}
		}

		//�жϱ�־λ�Ӷ��ж��Ƿ��߹�
		if(iFlag!=1) 
		{
			struct sship sSubTempShip;
			//������ֵ//��ʼ���²㴬ֵ
			sSubTempShip.iMan=abs(iSubThisMan-iSubTempThisMan);
			sSubTempShip.iRetainer=abs(iSubThisRetainer-iSubTempThisRetainer);
			sSubTempShip.cFlag='S';
			//�������޸ĵ�ǰ��ֵ
			sSubTempPointer->iThisMan=iSubTempThisMan;
			sSubTempPointer->iThisRetainer=iSubTempThisRetainer;
			sSubTempPointer->iThatMan=iSubTempThatMan;
			sSubTempPointer->iThatRetainer=iSubTempThatRetainer;
			sSubTempPointer->sStructShip=sSubTempShip;

			//���˵ݹ�����Լ�
			BackTrack(iSubTempThisMan,iSubTempThisRetainer,iSubTempThatMan,iSubTempThatRetainer,pSubHead,pSubTail,sSubTempShip);
		}
	}
	//�������Ҫ�ͷű�����ֵ
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
		iNum=0;//��ʼ��
		iNumBerBack=0;//��ʼ�����ݵĴ���
		printf("���������� ���˵���Ŀ�����˲���С����������");
		scanf("%d %d",&iThisMan,&iThisRetainer);
		start = clock(); //��ʼ��ʱ
		//pHeadΪ��������ͷָ��Ϊ�գ�pTailΪβָ��
		struct sresult *pHead=NULL;
		struct sresult *pTail=pHead;
		struct sship sShip;

		//��ʼ��
		sShip.cFlag='S';//����this bank
		sShip.iMan=0;
		sShip.iRetainer=0;

		if((pHead=(struct sresult *)malloc(sizeof(struct sresult)))==NULL) exit(1);//Ϊͷ�������ռ䣬�ж��Ƿ�ɹ�
		pTail=pHead;//ͷβָ��ͬһ��
		pHead->iThisMan=iThisMan;
		pHead->iThisRetainer=iThisRetainer;
		pHead->iThatMan=iThatMan;
		pHead->iThatRetainer=iThatRetainer;
		pHead->sStructShip=sShip;

		//���ú�������
		BackTrack(iThisMan,iThisRetainer,iThatMan,iThatRetainer,pHead,pTail,sShip);

		//�ͷ�ͷ�ڵ�
		free(pHead);
		//free(pTail);
		pHead=NULL;
		pTail=NULL;
		
		printf("������%d�λ���",iNumBerBack);
		finish = clock();
		duration = (double)(finish - start)/CLOCKS_PER_SEC; 
		printf( "%f seconds\n", duration ); 
		float flAverageTime=duration/iNumBerBack;
		printf("ƽ��ÿ�λ��ݺķ�%f s",flAverageTime);
		printf("\n������û�н��֤��û�д�");
		system("pause");
	}
	return 0;
}

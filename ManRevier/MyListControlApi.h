//MyFree����ʵ������ڵ���ͷ�
//����int ����0�ж��Ƿ����н���
//����Ϊ��ǰ�ڵ��ǰһ���ڵ�͵�ǰҪ�ͷŽڵ�
#include<malloc.h>

struct sship
{
	int iMan;
	int iRetainer;
	char cFlag;//T(that)S(this)
};

struct sresult
{
	int iThisMan;
	int iThisRetainer;
	int iThatMan;
	int iThatRetainer;
	struct sship sStructShip;//�������
	//char cSFlag;//G��this to that��;C(that to this)
	struct sresult *pNext;
};

int MyFree (struct sresult * pPrevious,struct sresult * pPoint)
{
	pPrevious->pNext=pPoint->pNext;
	free(pPoint);
	pPoint=NULL;
	return 0;
}
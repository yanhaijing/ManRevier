//MyFree函数实现链表节点的释放
//返回int 类型0判断是否运行结束
//参数为当前节点的前一个节点和当前要释放节点
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
	struct sship sStructShip;//船上情况
	//char cSFlag;//G（this to that）;C(that to this)
	struct sresult *pNext;
};

int MyFree (struct sresult * pPrevious,struct sresult * pPoint)
{
	pPrevious->pNext=pPoint->pNext;
	free(pPoint);
	pPoint=NULL;
	return 0;
}
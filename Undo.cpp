// Undo.cpp: implementation of the CUndo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BWChess.h"
#include "Undo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUndo::CUndo()
{
	Undos * temp;
	temp=new Undos;
	ASSERT(temp);
	temp->next =NULL;
	temp->prior =NULL;
	temp->color =0;
//	for(int i=0;i<NUMBER;i++)
//		temp->mains[i]=0;
	Head=Tail=temp;
	TopIndex=Tail;
	Length=0;
}

CUndo::~CUndo()
{
	Destroy();
	delete Tail;
}

void CUndo::push(int *x,int flag)
{
	Undos * temp;
	temp=new Undos;
	ASSERT(temp);
	temp->prior =NULL;
	temp->color =flag;

	for(int i=0;i<NUMBER;i++)
		temp->mains[i]=*(x+i);

	temp->next =Head;
	Head->prior =temp;
	Head=temp;
	Length++;
}

void CUndo::pop(int *x)
{
	if(!Length)
		return;
	Undos * temp;
	temp=Head;
	Head=Head->next;
	Head->prior =NULL;

	for(int i=0;i<NUMBER;i++)
		*(x+i)=temp->mains[i];

	delete temp;
	Length--;
}

void CUndo::Destroy()
{
	int num=Length;
	while(num>0)
	{
		Undos * temp;
		temp=Head;
		Head=Head->next;
		delete temp;
		num--;
	}
	TopIndex=Head=Tail;
	Length=0;
}

int CUndo::GetNextPos(int *x, int *flag)
{
	if(!Length)
		return 0;
	TopIndex=TopIndex->prior;
	for(int i=0;i<NUMBER;i++)
		*(x+i)=TopIndex->mains[i];
	*flag=TopIndex->color;
	return TopIndex!=Head;
}


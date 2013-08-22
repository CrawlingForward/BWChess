// stack.cpp: implementation of the stack class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stack.h"
#include "stdlib.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
stack::stack()
{
	GetIndex=NULL;
	sk *temp;
	temp=new sk;
	ASSERT(temp);

	temp->next=NULL;
	temp->x=temp->y=0;
	temp->mark =0;
	top=bottom=temp;
	IsIntoGeting=0;
}

stack::~stack()
{
	destroy();
	delete bottom;
}

void stack::push(int x, int y)
{
	sk *temp;
	temp=new sk;
	ASSERT(temp);

	temp->x=x;
	temp->y=y;
	temp->mark =0;
	temp->next=top;
	top=temp;
	bottom->mark++;
	GetIndex=top;
	IsIntoGeting=0;
}

void stack::pop(int *x, int *y)
{
	sk *temp;

	ASSERT(top!=bottom);
	*x=top->x;
	*y=top->y;
	temp=top;
	top=temp->next;
	bottom->mark--;
	GetIndex=top ;
	delete temp;
	IsIntoGeting=0;
}

void stack::destroy()
{
	sk *temp;
	while(top!=bottom)
	{
		temp=top;
		top=temp->next;
		delete temp;
	}
	GetIndex=top ;
	bottom->mark =0;
	IsIntoGeting=0;
}

int stack::isempty()//if the stack is empty,return 1,else return 0
{
	return bottom->mark==0;
}

int stack::Len()
{
	return bottom->mark;
}

int stack::GetNextPos(int *x, int *y,int *marks)
{
	if(isempty())
		return 0;

	if(IsIntoGeting)
		GetIndex=GetIndex->next;//first time needn't do so
	*x=GetIndex->x;
	*y=GetIndex->y;
	*marks=GetIndex->mark;
	IsIntoGeting=1;
	return GetIndex->next != bottom;
}

void stack::CopyBackIndex()
{
	GetIndex=top ;
	IsIntoGeting=0;
}

int stack::IsThere(int m, int n)
{
	sk* temp1=top;
	int result=0;
	while(temp1!=bottom )
	{
		if((temp1->x==m) && (temp1->y==n))
		{
			result=1;
			break;
		}
		temp1=temp1->next ;
	}
	return result;
}

void stack::SetMarks(int marks)//only used with getnextpos
{
	GetIndex->mark =marks;
}

void stack::Sort()
{
	IsIntoGeting=0;
	GetIndex=top ;
	//begin
	sk * t1;
	sk * t2;
	int tx,ty,tm;
	int leng=Len()-1;
	t1=top ;
	while(leng>0)
	{
		t2=t1->next ;
		do
		{
			if((t1->mark) < (t2->mark))
			{
				tx=t1->x;
				ty=t1->y;
				tm=t1->mark ;
				t1->x    =t2->x;
				t1->y    =t2->y;
				t1->mark =t2->mark ;
				t2->x    =tx;
				t2->y    =ty;
				t2->mark =tm;
			}
			t2=t2->next ;
		}
		while(t2!=bottom );
		t1=t1->next ;
		leng--;
	}
}

int stack::GetMarks(int index)
{
	GetIndex=top;
	int i=0;
	while((i<index) && (GetIndex!=bottom))
	{
		GetIndex=GetIndex->next;
		i++;
	}
	if(GetIndex==bottom)
		return -1;
	i=GetIndex->mark;
	GetIndex=top;
	return i;
}

int stack::GetTop(int &x,int &y)
{
	if(top==bottom)
		return 0;
	x=top->x;
	y=top->y;
	return 1;
}
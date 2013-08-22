// stack.h: interface for the stack class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STACK_H__68683227_5421_11D4_8FD6_9B4C39DFA368__INCLUDED_)
#define AFX_STACK_H__68683227_5421_11D4_8FD6_9B4C39DFA368__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NULL 0
//头节点的x域表示链表的长度
class stack  
{
public:
	int GetMarks(int index);
	int GetTop(int &x,int &y);
	void Sort();
	void SetMarks(int marks);
	int IsThere(int m,int n);
	void CopyBackIndex();
	int GetNextPos(int *x,int *y,int *marks);
	int Len();
	int isempty();
	void destroy();
	void pop(int *x,int *y);
	void push(int x,int y);

	struct sk
	{
		int x;
		int y;
		int mark;
		struct sk *next;
	};

	stack();
	virtual ~stack();

private:
	int IsIntoGeting;
	sk* GetIndex;
	sk *top;
	sk *bottom;
};

#endif // !defined(AFX_STACK_H__68683227_5421_11D4_8FD6_9B4C39DFA368__INCLUDED_)

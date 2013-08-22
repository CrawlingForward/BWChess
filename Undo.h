// Undo.h: interface for the CUndo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNDO_H__9637BF20_6611_11D4_9B45_C40C16A19C31__INCLUDED_)
#define AFX_UNDO_H__9637BF20_6611_11D4_9B45_C40C16A19C31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NUMBER 8*8

class CUndo  
{
public:
	void Destroy();
	int IsEmpty()
	{
		return Length==0;
	}
	void pop(int *x);
	void push(int *x,int flag);
	CUndo();
	virtual ~CUndo();

public:
	int Len()
	{
		return Length;
	}
	int GetNextPos(int *x,int *flag);
	void CopyBackIndex()
	{
		TopIndex=Tail;
	}
	int GetTopColor()
	{
		return Head->color;
	}
	typedef struct tagUndo
	{
		int mains[NUMBER];
		int color;
		struct tagUndo* next;
		struct tagUndo* prior;
	} Undos;
private:
	Undos * TopIndex;
	int Length;
	Undos * Tail;
	Undos * Head;
};		

#endif // !defined(AFX_UNDO_H__9637BF20_6611_11D4_9B45_C40C16A19C31__INCLUDED_)

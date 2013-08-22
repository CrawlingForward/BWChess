// DigitalPlayer.cpp: implementation of the CDigitalPlayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BWChess.h"
#include "DigitalPlayer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

int nDigitFont[11][7]={
	{ 1, 2, 3, 4, 5, 6,-7},
	{-1,-2, 3, 4,-5,-6,-7},
	{-1, 2, 3,-4, 5, 6, 7},
	{-1, 2, 3, 4, 5,-6, 7},
	{ 1,-2, 3, 4,-5,-6, 7},
	{ 1, 2,-3, 4, 5,-6, 7},
	{ 1, 2,-3, 4, 5, 6, 7},
	{-1, 2, 3, 4,-5,-6,-7},
	{ 1, 2, 3, 4, 5, 6, 7},
	{ 1, 2, 3, 4, 5,-6, 7},
	{-1,-2,-3,-4,-5,-6, 7}
};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CDigitalPlayer::Create(CWnd *pWnd,int nX,int nY,
		long lOriginal, int nMaxNumbers, int nSepMics, 
		COLORREF crColor,COLORREF crBkColor)
{
	m_nMaxNumber = nMaxNumbers;
	m_nSepMics = nSepMics;
	m_nX = nX;
	m_nY = nY;
	m_pWnd = pWnd;
	m_nCalculator = lOriginal;
	m_crColor = crColor;
	m_crBkColor = crBkColor;

	long multy=1;
	int i;
	for(i=0;i<m_nMaxNumber;i++)
		multy*=10;
	m_Mulply=multy;	
}

void CDigitalPlayer::ReShow()
{
	CClientDC ClientDC(m_pWnd);
	ClientDC.SelectObject(&Brush);
	ClientDC.SelectObject(&Pen1);
	ClientDC.Rectangle(m_nX,m_nY,
						m_nX+(11+m_nSepMics)*m_nMaxNumber+m_nSepMics,
						m_nY+25);
	
	ClientDC.SelectObject(&Pen2);
	ClientDC.SelectStockObject(NULL_BRUSH);
	ClientDC.MoveTo(m_nX,m_nY+25);
	ClientDC.LineTo(m_nX,m_nY);
	ClientDC.LineTo(m_nX+(11+m_nSepMics)*m_nMaxNumber+m_nSepMics,m_nY);
	ShowDigit();
}

void CDigitalPlayer::ShowOneDigit(int nWhichDigit,int nWhichBit)
{
	CClientDC ClientDC(m_pWnd);
	int nI;
	for (nI=0;nI<7;nI++)
	{
		char nTmp = nDigitFont[nWhichDigit][nI];
		if(nTmp>0)
		{
			ClientDC.SelectObject(&Pen3);
		}
		else
		{
			ClientDC.SelectObject(&Pen4);
			nTmp = -nTmp;
		}
		ClientDC.SelectStockObject(NULL_BRUSH);
		
		int	nStartPosX, nStartPosY,	nJ;

		switch(nTmp)
		{
		case 1:
			nStartPosX = m_nX+(11+m_nSepMics)*nWhichBit+m_nSepMics;
			nStartPosY = m_nY+3;
			for (nJ=0;nJ<3;nJ++)
			{
				ClientDC.MoveTo(nStartPosX+nJ,nStartPosY+nJ);
				ClientDC.LineTo(nStartPosX+nJ,nStartPosY-nJ+9);
			}
			break;
		case 2:
			nStartPosX = m_nX+(11+m_nSepMics)*nWhichBit+m_nSepMics+1;
			for (nJ=0;nJ<3;nJ++)
			{
				ClientDC.MoveTo(nStartPosX+nJ,m_nY+nJ+2);
				ClientDC.LineTo(nStartPosX-nJ+9,m_nY+nJ+2);
			}
			break;
		case 3:
			nStartPosX = m_nX+(11+m_nSepMics)*nWhichBit+m_nSepMics+10;
			for (nJ=0;nJ<3;nJ++)
			{
				ClientDC.MoveTo(nStartPosX-nJ,m_nY+nJ+3);
				ClientDC.LineTo(nStartPosX-nJ,m_nY-nJ+9+3);
			}
			break;
		case 4:
			nStartPosX = m_nX+(11+m_nSepMics)*nWhichBit+10+m_nSepMics;
			nStartPosY = m_nY+13;
			for (nJ=0;nJ<3;nJ++)
			{
				ClientDC.MoveTo(nStartPosX-nJ,nStartPosY+nJ);
				ClientDC.LineTo(nStartPosX-nJ,nStartPosY-nJ+9);
			}
			break;
		case 5:
			nStartPosX = m_nX+(11+m_nSepMics)*nWhichBit+m_nSepMics+1;
			nStartPosY = m_nY+22;
			for (nJ=0;nJ<3;nJ++)
			{
				ClientDC.MoveTo(nStartPosX+nJ,nStartPosY-nJ);
				ClientDC.LineTo(nStartPosX-nJ+9,nStartPosY-nJ);
			}
			break;
		case 6:
			nStartPosX = m_nX+(11+m_nSepMics)*nWhichBit+m_nSepMics;
			nStartPosY = m_nY+13;
			for (nJ=0;nJ<3;nJ++)
			{
				ClientDC.MoveTo(nStartPosX+nJ,nStartPosY+nJ);
				ClientDC.LineTo(nStartPosX+nJ,nStartPosY-nJ+9);
			}
			break;
			
		case 7:
			nStartPosX = m_nX+(11+m_nSepMics)*nWhichBit+m_nSepMics+1;
			nStartPosY = m_nY+12;
			ClientDC.MoveTo(nStartPosX,nStartPosY);
			ClientDC.LineTo(nStartPosX+9,nStartPosY);

			ClientDC.MoveTo(nStartPosX+1,nStartPosY+1);
			ClientDC.LineTo(nStartPosX+8,nStartPosY+1);

			ClientDC.MoveTo(nStartPosX+1,nStartPosY-1);
			ClientDC.LineTo(nStartPosX+8,nStartPosY-1);
			break;
		}
	}
}

void CDigitalPlayer::ShowDigit()
{
	int nI,nJ;
	char cTmp[20];
	if(m_nCalculator<0)
	{
		nJ=1;
		ShowOneDigit(10,0);
		sprintf(cTmp,"%d",-m_nCalculator);
	}
	else
	{
		nJ=0;
		sprintf(cTmp,"%d",m_nCalculator);
	}
	int nLen=strlen(cTmp);
	for (nI=0;nJ<m_nMaxNumber;nJ++)
	{
		if(nJ>=m_nMaxNumber-nLen)
		{
			ShowOneDigit(cTmp[nI]-'0',nJ);
			nI++;
		}
		else
			ShowOneDigit(0,nJ);
	}
}
/*
void CDigitalPlayer::Increase()
{
	m_nCalculator++;
	ReShow();
}
*/

/*
void CDigitalPlayer::Decrease()
{
	m_nCalculator--;
	ReShow();
}
*/
long CDigitalPlayer::GetNumber()
{
	return m_nCalculator;
}
void CDigitalPlayer::SetNumber(long lOriginal)
{
	m_nCalculator = lOriginal%m_Mulply;
	ReShow();
}

CDigitalPlayer::~CDigitalPlayer()
{

}

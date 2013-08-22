// DigitalPlayer.h: interface for the CDigitalPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIGITALPLAYER_H__217C3C41_711C_11D4_9B45_F1E77FF4381F__INCLUDED_)
#define AFX_DIGITALPLAYER_H__217C3C41_711C_11D4_9B45_F1E77FF4381F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDigitalPlayer  
{
private:
	long m_Mulply;
	int m_nMaxNumber;
	int m_nX,m_nY;
	long m_nCalculator;
	int m_nSepMics;
	void ShowOneDigit(int nWhichDigit, int nWhichBit);
	CWnd* m_pWnd;
	COLORREF m_crColor,m_crBkColor;
	CBrush Brush;
	CPen Pen1,Pen2,Pen3,Pen4;
public:
	CDigitalPlayer()
	{
		Brush.CreateSolidBrush(   RGB(  0,  0,  0));//雷数与时间背景色
		Pen1.CreatePen(PS_SOLID,1,RGB(255,255,255));//右下边框色
		Pen2.CreatePen(PS_SOLID,1,RGB(128,128,128));//左上边框色
		Pen3.CreatePen(PS_SOLID,1,RGB(255,  0,  0));//雷数与时间显示部分色
		Pen4.CreatePen(PS_SOLID,1,RGB(  0,  0,  0));//雷数与时间不显示部分色
	};
	void Create(CWnd *pWnd,int nX,int nY,
		long lOriginal=0, int nMaxNumbers=3, int nSepMics=2, 
		COLORREF crColor=RGB(128,0,0),COLORREF crBkColor=RGB(0,0,0));
	void ShowDigit();
//	void Increase();
//	void Decrease();
	long GetNumber();
	void SetNumber(long lOriginal);
	void ReShow();
	virtual ~CDigitalPlayer();
};

#endif // !defined(AFX_DIGITALPLAYER_H__217C3C41_711C_11D4_9B45_F1E77FF4381F__INCLUDED_)

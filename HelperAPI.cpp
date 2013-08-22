#include "stdafx.h"
#include "GlobalVar.h"
#include "HelperAPI.h"
#include "Message1.h"
#include "Message2.h"
// Play sound in resource
//

int MsgBox(CString &con,CString &title, int flag)
{
	if(flag==1)
	{
		CMessage1 dlg;
		dlg.SetContent(con);
		dlg.SetTitle(title);
		return dlg.DoModal();
	}
	if(flag==2)
	{
		CMessage2 dlg;
		dlg.SetContent(con);
		dlg.SetTitle(title);
		return dlg.DoModal();
	}
	return -1;
}

int MsgBox(UINT icon,UINT ititle, int flag)
{
	CString con,title;
	con.LoadString (icon);
	title.LoadString (ititle);
	return MsgBox(con,title,flag);
}

void DynamicShow(CDialog *dlg,int flag)
{
	if(!g_bShowDynamic)
		return;
	CRect rc;
	dlg->GetWindowRect(&rc);
	time_t t2;
	t2=time(NULL);
	srand((unsigned int)t2);
	int swidth,sheight;
	int wwidth,wheight;
	swidth=::GetSystemMetrics(SM_CXSCREEN);
	sheight=::GetSystemMetrics(SM_CYSCREEN);
	wwidth=rc.Width();
	wheight=rc.Height();
	int stepw=1,steph=1;
	if(wwidth<wheight)
	{
		steph=wheight/wwidth+1;
	}
	else if(wwidth>wheight)
	{
		stepw=wwidth/wheight+1;
	}

	int dir=rand()%4;
	const int disstep=4;
	int i,j;

	if(flag)
	{
		switch(dir)
		{
		case 0:
			{
				rc.DeflateRect (0,0,wwidth,wheight);
				dlg->MoveWindow(&rc);
				while((rc.Width () <wwidth) || (rc.Height () <wheight) )
				{
					if(rc.Width()<wwidth)
						i=stepw;
					else
						i=0;
					if(rc.Height ()<wheight )
						j=steph;
					else
						j=0;
					rc.InflateRect (0,0,i,j);
					dlg->MoveWindow(&rc);
				}
			}
			break;
		case 1:
			{
				rc.DeflateRect (wwidth,0,0,wheight);
				dlg->MoveWindow(&rc);
				while((rc.Width () <wwidth) || (rc.Height () <wheight) )
				{
					if(rc.Width()<wwidth)
						i=stepw;
					else
						i=0;
					if(rc.Height ()<wheight )
						j=steph;
					else
						j=0;
					rc.InflateRect (i,0,0,j);
					dlg->MoveWindow(&rc);
				}
			}
			break;
		case 2:
			{
				rc.DeflateRect (0,wheight,wwidth,0);
				dlg->MoveWindow(&rc);
				while((rc.Width () <wwidth) || (rc.Height () <wheight) )
				{
					if(rc.Width()<wwidth)
						i=stepw;
					else
						i=0;
					if(rc.Height ()<wheight )
						j=steph;
					else
						j=0;
					rc.InflateRect (0,j,i,0);
					dlg->MoveWindow(&rc);
				}
			}
			break;
		case 3:
			{
				rc.DeflateRect (wwidth,wheight,0,0);
				dlg->MoveWindow(&rc);
				while((rc.Width () <wwidth) || (rc.Height () <wheight) )
				{
					if(rc.Width()<wwidth)
						i=stepw;
					else
						i=0;

					if(rc.Height ()<wheight )
						j=steph;
					else
						j=0;
					rc.InflateRect (i,j,0,0);
					dlg->MoveWindow(&rc);
				}
			}
			break;
		}
	}
	else
	{
		switch(dir)
		{
		case 0:
			{
				while((rc.Width () >disstep) || (rc.Height () >disstep ))
				{
					if(rc.Width()>disstep)
						i=stepw;
					else
						i=0;
					if(rc.Height ()>disstep)
						j=steph;
					else
						j=0;
					rc.DeflateRect (0,0,i,j);
					dlg->MoveWindow(&rc);
				}
			}
			break;
		case 1:
			{
				while((rc.Width () >disstep) || (rc.Height () >disstep) )
				{
					if(rc.Width()>disstep)
						i=stepw;
					else
						i=0;
					if(rc.Height ()>disstep )
						j=steph;
					else
						j=0;
					rc.DeflateRect (i,0,0,j);
					dlg->MoveWindow(&rc);
				}
			}
			break;
		case 2:
			{
				while((rc.Width () >disstep) || (rc.Height () >disstep) )
				{
					if(rc.Width()>disstep)
						i=stepw;
					else
						i=0;
					if(rc.Height ()>disstep )
						j=steph;
					else
						j=0;
					rc.DeflateRect (0,j,i,0);
					dlg->MoveWindow(&rc);
				}
			}
			break;
		case 3:
			{
				while((rc.Width () >disstep) || (rc.Height () >disstep) )
				{
					if(rc.Width()>disstep)
						i=stepw;
					else
						i=0;

					if(rc.Height ()>disstep )
						j=steph;
					else
						j=0;
					rc.DeflateRect (i,j,0,0);
					dlg->MoveWindow(&rc);
				}
			}
			break;
		}
	}
}


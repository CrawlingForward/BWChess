#ifndef _INC_HELPERAPI
#define _INC_HELPERAPI

int MsgBox(CString &con,CString &title,int flag=1);
int MsgBox(UINT icon,UINT ititle,int flag=1);
void DynamicShow(CDialog *dlg,int flag);

#endif	//_INC_HELPERAPI
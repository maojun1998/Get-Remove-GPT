/*run this prog need the admin power*/ 


#include<windows.h>
#include<stdio.h>
#define BUFF_SIZE 512			/*磁盘一次读入或者写入512字节，也就是一个扇区的大小*/																	
#define GPTSIZE 16896			/*GPT大小，33个扇区*/
int main()
{	
	void getbufferl(char *buffer,char *buff,int i ) ;	
	int j;
	char buffer[BUFF_SIZE]={0x00};																
	char buff[16896];
	int Write_return ;
	int Read_return;
	DWORD Get = BUFF_SIZE;														
	DWORD Temp = GPTSIZE;
	HANDLE  hDevice = CreateFile(													
        "\\\\.\\PHYSICALDRIVE0",
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        NULL,
        0);	
	HANDLE  hFile = CreateFile(																	
         "GPT",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ|FILE_SHARE_WRITE,
        NULL,
        CREATE_ALWAYS,
        NULL,
        NULL);
	if (INVALID_HANDLE_VALUE ==  hDevice){
		printf("open disk fail\n%d\n", GetLastError() );
		MessageBox (NULL, TEXT ("You must run as admin!!!"), TEXT ("Warning"), 0) ;
		return -1;
	}
	if(INVALID_HANDLE_VALUE ==  hFile){
		printf("open mbr fail\n%d\n", GetLastError() );
		return -1;
	}
	for(j = 1; j <= 33; j++ ){
		Read_return = ReadFile(
			hDevice,
			buffer,
			BUFF_SIZE,
			&Get,
			NULL);
		getbufferl(buffer, buff, j );
		if(Read_return == FALSE ){
			printf("read fail \n%d\n", GetLastError() );
			return -1;
		}
	}
	Write_return = WriteFile(
		hFile,
		buff,
		GPTSIZE,
		&Temp,
		NULL);
	if(Write_return == FALSE ){
		printf("write fail \n%d\n", GetLastError() );
		
	}
	MessageBox (NULL, TEXT ("The GPT get successfull!The GTP save to the file named GTP!"), TEXT ("Successful!!"), 0) ;
	CloseHandle(hDevice );
	CloseHandle(hFile );
	return 0;
}
void getbufferl(char *buffer,char *buff, int i ) 
{
	int count;
	for (count = 0; count < 512; count++){
		buff[(i-1)*512 +count] = buffer[count];
	}
}

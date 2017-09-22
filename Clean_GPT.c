#include<windows.h>
#include<stdio.h>
#define BUFF_SIZE 512																			/* the size of mbr */
#define GTPSIZE 16896
int main()

{
	char buffer[BUFF_SIZE]={0xAA};																/* inti the bits number is 0x00 */
	int Write_return ;
	int Read_return;
	int i;
	HANDLE  hDevice = CreateFile(																/* the hard disk handle */
        "\\\\.\\PHYSICALDRIVE0",
        GENERIC_WRITE | GENER_READ,
        FILE_SHARE_READ | GENER_READ,
        NULL,
        OPEN_EXISTING,
        NULL,
        0);	
	DWORD Get = BUFF_SIZE;																		/* the read the write size */
	if (INVALID_HANDLE_VALUE ==  hDevice){
		printf("open disk fail\n%d\n", GetLastError() );
		MessageBox (NULL, TEXT ("You must run as admin!!!"), TEXT ("Warning"), 0) ;
		return -1;
	}
	for (i = 0; i <= 32; i++ ) {
		Write_return = WriteFile(
			hDevice,
			buffer,
			BUFF_SIZE,
			&Get,
			NULL);
	
		if (Write_return == FALSE ){
			printf("write fail \n%d\n", GetLastError() );
			return -1;
		}
	}
	MessageBox (NULL, TEXT ("The GPT remove successfull!Now you can reboot you computer"), TEXT ("Successful!!"), 0) ;
	CloseHandle(hDevice );
	return 0;
}

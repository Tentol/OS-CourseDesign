#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>

void readbuf();
void writebuf();

int temp=20;

int main(int argc,char*argv[])
{

	char buffer[20];
	int fp1,fp2;
	fp1=open(argv[2],O_RDONLY);
	fp2=open(argv[3],O_WRONLY);
	while (temp>0)
	{
		writebuf(buffer,fp1);
		readbuf(buffer,fp2);
	}
	close(fp1);
	close(fp2);

}

void readbuf(char *s,int fp)
{
	write(fp,s,temp);
	return;
}

void writebuf(char *s,int fp)
{
	temp=read(fp,s,20);
	return;
}

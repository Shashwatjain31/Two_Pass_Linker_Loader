/*
	Program : pass1.c 
	This program calculates address of the assembly code which is input.dat and stores that address in a temporary ESTAB struct data structure.
*/
#include<stdio.h>
#include<string.h>
struct estab
{
  char csname[10];
  char extsym[10];
  int address;
  int length;
}es[20];
int main()
{
	//variables declaration for address calculation
	//progaddr is the input address location where program should be loaded in the memory
	//csaddr is the address taken from input.dat control statements
	char input[10],name[10],symbol[10],ch;  int count=0,progaddr,csaddr,add,len;
	//file pointer to read and write to files
	FILE *fp1,*fp2;
	fp1=fopen("INPUT.DAT","r"); // read from compiled assembly program
	fp2=fopen("ESTAB.DAT","w"); // write to temporary data structure
	printf("\n\nEnter the memory location where you want to load the program: ");
	scanf("%x",&progaddr);
	csaddr=progaddr;
	fscanf(fp1,"%s",input);
	//traversing the input.dat file until End of the file occures
	while(strcmp(input,"END")!=0)
	{
		if(strcmp(input,"H")==0)
		{
			fscanf(fp1,"%s",name);
			strcpy(es[count].csname,name);
			strcpy(es[count].extsym,"  ");
			fscanf(fp1,"%x",&add);
			//calculate linking address
			es[count].address=add+csaddr;
			fscanf(fp1,"%x",&len);
			es[count].length=len;
			fprintf(fp2,"%s ** %x %x\n",es[count].csname,es[count].address,es[count].length);
			count++;
		}
		else if(strcmp(input,"D")==0)
		{
			fscanf(fp1,"%s",input);
			while(strcmp(input,"R")!=0)
			{
				// Records
				strcpy(es[count].csname,"  ");
				strcpy(es[count].extsym,input);
				fscanf(fp1,"%x",&add);
				//calculate linking address
				es[count].address=add+csaddr;
				es[count].length=0;
				fprintf(fp2,"** %s %x\n",es[count].extsym,es[count].address);
				count++;
				fscanf(fp1,"%s",input);
			}
			csaddr=csaddr+len;
		}
		else if(strcmp(input,"T")==0)
		{
			// Text Records
			while(strcmp(input,"E")!=0)
			fscanf(fp1,"%s",input);
		}
		fscanf(fp1,"%s",input);
	}
  fclose(fp1);
  fclose(fp2);
  fp2=fopen("ESTAB.DAT","r");
  ch=fgetc(fp2);
  //print on console
  while(ch!=EOF)
  {
   printf("%c",ch);
   ch=fgetc(fp2);
  }
  fclose(fp2);
}
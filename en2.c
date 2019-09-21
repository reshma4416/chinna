#include<reg51.h> 
#include<stdio.h> 
unsigned int i,n,p,z=37;
unsigned char x[10],y[10];
unsigned char msg1[8],enter[]="\nEnter the No of Character : ";
code unsigned char menu[]="\n"
" Encryption Decryption Program "
"\n----------------------------------- "
"\n Press '1': Get Data from keyboard "
"\n Press '2': Display Decrypted Text ";
void serial();
void encrypt();
void decrypt();
void delay(unsigned int );

void main()
{
EA=1; 
ES=1;
serial(); 
delay(100);
while(1); 
}
void serial()
{
SCON = 0x50; 
TMOD |= 0x20; 
TH1 = 0xFD; 
TR1 = 1; 
TI = 1;
i = 0;
while(menu[i] != '\0')
{
SBUF = menu[i];
delay(20);
i++;
z--;
if(z == 0)
{
z =37;
SBUF = 0x0d; 
delay(50);
}
}
}
void delay(unsigned int k)
{
unsigned int a;
for(a=0;a<k;a++);
}


void encrypt()
{ i = 0;
SBUF = 0x0d; 
delay(100);
while(enter[i] != '\0')
{
SBUF = enter[i];
delay(100);
i++;
}
while(RI == 0);
n = SBUF;
RI = 0;
SBUF = n;
delay(100);
SBUF = '\n';
delay(100);
SBUF = '\n';
delay(100);
n = n-0x30;
for(i=0;i<n;i++)
{
while(RI==0);
msg1[i]=SBUF;
delay(100);
printf("\n");
SBUF=msg1[i];
delay(100);
p=(n-i)-1;
printf(":still %d character remaining:\n",p);
printf("\n");
RI=0;
}
printf("Encrypted Text: ");
for(i=0;msg1[i]!='\0';i++) 
{
x[i]=(msg1[i]+10);
delay(100);
printf("%c",x[i]);
}
delay(100);
printf("\n");
EA=1; 
ES=1;
}

void decrypt()
{
printf("\nDecrypted Text: ");
for(i=0;i<n;i++) 
{
y[i]=(x[i]-10);
delay(100);
printf("%c",y[i]);
}
printf("\n");
}

void serin() interrupt 4
{
unsigned char z;
if(RI==1)
{
z=SBUF;
RI=0;
switch(z)
{
case 0x31:
encrypt(); 
break;
case 0x32: 
decrypt(); 
break;
}
}
}
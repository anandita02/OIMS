#include "headerfiles.h"
void intTostring(int count,char c[])
{
    char dig,temp;
    int i,j,len;
    i=0;j=0;
   
    while(count)
    {
      dig='0'+(char)(count%10);
      c[i]=dig;
      i++;
      count=count/10;
    }
    c[i++]=' ';
    c[i]='\0';
    len=i-1;
    for(i=0,j=len-1;i<j;i++,j--)
    {
     temp=c[i];
     c[i]=c[j];
     c[j]=temp;
    }
    
}

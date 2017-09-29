#include "headerfiles.h"
int stringToint(string str)
{
   
    unsigned int i,dig,sum=-1;
    if((str.at(0)-'0')>=0&&(str.at(0)-'0')<=9)
    {sum=(char)str.at(0)-'0';i=1;}
    else if(str.at(0)=='!'&&str.at(1)=='-')
           {sum=0;i=2;}
    
    for(;i<str.length();++i)
    {
    dig=str.at(i)-'0';
    if(dig>=0&&dig<=9)
    sum=sum*10+dig;
    else return -1;
    }
    //cout<<"SUM="<<sum<<endl;
    return sum;
}

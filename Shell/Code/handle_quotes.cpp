#include "headerfiles.h"
void handle_quotes(vector<string>& arglist)
{
  vector<string> tempv2;
  vector<string>::iterator it;
  char buff[1000],buff2[1000];
  int i; 
  for(it=arglist.begin();it!=arglist.end();it++)
        {   
            if((*it)=="\'")
                 continue;
            else if((*it).at(0)=='"'&&(*it).at(((*it).length())-1)=='"')
             {
                 for(i=1;i<(((*it).length())-1);i++)
                   {
                        buff[i-1]=((*it).at(i));
                   }   
                  buff[i]='\0';
                  tempv2.push_back(string(buff));
                  //buff[0]='\0';
             }
             else if((*it).at(0)=='\''&&(*it).at(((*it).length())-1)=='\'')
             {
                 for(i=1;i<(((*it).length())-1);i++)
                   {
                        buff2[i-1]=((*it).at(i));
                   }   
                  buff2[i]='\0';
                 // cout<<"buff2="<<buff2;
                  tempv2.push_back(string(buff2));
             }
            
             else tempv2.push_back(*it);
            
        }

       for(i=0;i<arglist.size();i++)
       arglist.pop_back();
       
       arglist.clear();
    
       for(it=tempv2.begin();it!=tempv2.end();it++)
               {
                  
                     arglist.push_back(*it);
                   
                }

       //cout<<"new arglist";
       /*for(it=arglist.begin();it!=arglist.end();it++)
       cout<<"new arg="<<*it<<endl;  */          



}

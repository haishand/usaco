/*
ID:cyrano63
LANG:C++
TASK:rockers
*/
#include<iostream>
 #include<fstream>
 #include<cstdio>
 #include <time.h>
 #define N 21
 using namespace std;
 
 int ans,maxn,a[N],b[N],n,t,m;
 
 void work(int k,int i,int r)
 {
     if(k==m||i==n)
     {
         if(ans<maxn) ans=maxn;
         return ;
     }
     if(maxn+r<=ans) return ;//减的巧呀！！！
     if(b[k]>=a[i])
     {
         b[k]-=a[i];
         maxn++;
         work(k,i+1,r-1);
         maxn--;
         b[k]+=a[i];
         work(k,i+1,r-1);
     }
     else 
     {
         work(k+1,i,r);
         work(k,i+1,r-1);    
     }
 }
 
 int main()
 {
     freopen("rockers.in","r",stdin);
     freopen("rockers.out","w",stdout);
     int i;
     while(cin>>n>>t>>m)
     {
         maxn=ans=0;
         for(i=0;i<n;i++) 
         {
             cin>>a[i];        
         }
         for(i=0;i<m;i++) b[i]=t;
         work(0,0,n);
         cout<<ans<<endl;
     }
 //    cout<<(double)clock()/CLOCKS_PER_SEC<<endl;
     return 0;
 }

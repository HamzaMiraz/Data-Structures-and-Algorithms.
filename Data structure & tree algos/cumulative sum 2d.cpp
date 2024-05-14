//#include<bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <cctype>
#include <set>
#include <bitset>
#include <algorithm>
#include <list>
#include <utility>
#include <functional>
#include <deque>
#include <numeric>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <assert.h>

#include <unordered_set>
#include <unordered_map>

using namespace std;

#include<cmath>
#include<math.h>

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

//For Debugging
#define debug(a...)          {cout<<__LINE__<<" #--> ";dbg,a; cout<<endl;}
struct debugger
{
    template<typename T> debugger& operator , (const T v)
    {
        cout<<v<<" ";
        return *this;
    }
} dbg;

#define deb(a)     cout<<__LINE__<<"# "<<#a<<" -> "<<a<<endl;
#define GCD(a,b)  __gcd(a,b)
#define LCM(a,b)  (a*b)/__gcd(a,b)
typedef long long LL;
const double PI = acos(-1);
const double EPS = 1e-7; ///1*10^-7
const int oo = 1e8+0.5;

int main()
{
//    freopen("in.txt", "r", stdin);  ///To read from a file.
//    freopen("out.txt", "w", stdout);  ///To write  a file.
///     one based;
    int r,c;
    while(scanf("%d%d",&r,&c) ==2)
    {
        int ar[r+5][c+5],px[r+5][c+5];
        for(int i=1;i<=r;i++)
            for(int j=1;j<=c;j++)
                cin>>ar[i][j];
        
        for(int i=0;i<=r;i++)px[i][0]=0;
        for(int j=0;j<=c;j++)px[0][j]=0;
        
        px[1][1]=ar[1][1];
        for(int i=2;i<=r;i++){
            px[i][1]=px[i-1][1]+ar[i][1];
            
        }
        for(int j=2;j<=c;j++){
            px[1][j]=px[1][j-1]+ar[1][j];
        }

        for(int i=2;i<=r;i++)
            for(int j=2;j<=c;j++){
                px[i][j]=px[i-1][j]+px[i][j-1]+ar[i][j]-px[i-1][j-1];
            }
            cout<<"\nprefix sum array :"<<endl;
        for(int i=1;i<=r;i++){
            for(int j=1;j<=c;j++){
                cout<<px[i][j]<<" ";
            }
            cout<<"\n";
        }

        cout<<"Range of summation array (i1,j1)->(i2,j2)"<<endl;
        int i1,i2,j1,j2,ans;
        cin>>i1>>j1>>i2>>j2;
        if(i1>i2)swap(i1,i2);
        if(j1>j2)swap(j1,j2);

        ans=px[i2][j2]-px[i2][j1-1]-px[i1-1][j2]+px[i1-1][j1-1];

        cout<<"sum of range = "<<ans<<endl;

    }
    return 0;
}

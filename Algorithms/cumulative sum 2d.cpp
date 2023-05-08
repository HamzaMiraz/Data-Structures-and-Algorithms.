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
int ar[100][100],r,c,px[100][100];
    while(scanf("%d%d",&r,&c) ==2)
    {
        for(int i=0;i<r;i++)
            for(int j=0;j<c;j++)
                cin>>ar[i][j];
        px[0][0]=ar[0][0];
        for(int i=1;i<r;i++)px[i][0]=px[i-1][0]+ar[i][0];
        for(int j=1;j<c;j++)px[0][j]=px[0][j-1]+ar[0][j];

        for(int i=1;i<r;i++)
            for(int j=1;j<c;j++){
                px[i][j]=px[i-1][j]+px[i][j-1]+ar[i][j]-px[i-1][j-1];
            }
            cout<<"\nprefix sum array :"<<endl;
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                cout<<px[i][j]<<" ";
            }
            cout<<endl;
        }

        cout<<"Range of summation array (i1,j1)->(i2,j2)"<<endl;
        int i1,i2,j1,j2,ans;
        cin>>i1>>j1>>i2>>j2;

        if(i1==0)ans=px[i2][j2]-px[i2][j1-1];
        else if(j1==0)ans=px[i2][j2]-px[i1-1][j2];
        else if(i1==0&&j1==0)ans=px[i2][j2];
        else ans=px[i2][j2]-px[i2][j1-1]-px[i1-1][j2]+px[i1-1][j1-1];

        cout<<"sum of range = "<<ans<<endl;

    }
    return 0;
}

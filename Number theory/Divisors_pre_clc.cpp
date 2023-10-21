#include<bits/stdc++.h>
using namespace std;

/// divisor pre calculate
///nlog(log(n))
vector<int>divisors[1000010];
void Divisor()
{
    for(int div=1;div<=1000000;div++)
        for(int num=div;num<=1000000;num+=div)///num is a number 
            divisors[num].push_back(div);     //which is contain divisor div
}

int main()
{
    Divisor();
    int n;
    while(scanf("%d",&n)==1)
    {
        int sz = divisors[n].size();
        for(int i=0;i<sz;i++)
            printf("%d ",divisors[n][i]);
        printf("\n");
    }
    return 0;
}

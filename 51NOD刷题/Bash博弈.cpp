#include <cstdio>  
#include <cstring>  
#include <algorithm>  
#include <iostream>  
#include <string>  
#include <vector>  
#include <stack>    
#include <cstdlib>  
#include <cmath>  
#include <set>  
#include <list>  
#include <deque>  
#include <map>  
#include <queue> 
using namespace std;  
typedef long long ll;  
const double PI = acos(-1.0);  
const double eps = 1e-6;  
const int INF = 1000000000;  
const int maxn = 1e6;
const int mod = (1e9+7); 

int main()
{
	ios::sync_with_stdio(false);
	int t,n,k;
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		if(n%(k+1)!=0)
			cout<<"A\n";
		else if(n%(k+1)==0)
			cout<<"B\n";
	}
	return 0;
}
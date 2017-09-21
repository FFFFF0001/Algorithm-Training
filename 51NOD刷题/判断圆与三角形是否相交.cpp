#include <cstdio>  
#include <cstring>  
#include <algorithm>  
#include <iostream>  
#include <string>  
#include <vector>  
#include <stack>    
#include <cstdlib>  
#include <cmath> 
#include <map>  
#include <queue> 
using namespace std;  
typedef long long ll;  
const double PI = acos(-1.0);  
const double eps = 1e-6;  
const int INF = 1000000000;  
const int maxn = 1e6;
const int mod = (1e9+7); 
typedef struct
{
	ll x,y;
}Point;
Point A,B,C,O;
ll r;

//两点距离平方
ll distance(Point *p1,Point *p2)
{
	return (p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2 ->y) * (p1->y - p2 ->y);
}
//  判断线段是否和圆相交
int segOnCircle(Point *p_1, Point *p_2)
{
	ll a, b, c, dist_1, dist_2, angle_1, angle_2;   //  ax + by + c = 0;
	if (p_1->x == p_2->x)                           //  当x相等
	{
		a = 1, b = 0, c = -p_1->x;
	}
	else if (p_1->y == p_2->y)                      //  当y相等
	{
		a = 0, b = 1, c = -p_1->y;
	}
	else
	{
		a = p_1->y - p_2->y;
		b = p_2->x - p_1->x;
		c = p_1->x * p_2->y - p_1->y * p_2->x;
	}
	dist_1 = a * O.x + b * O.y + c;
	dist_1 *= dist_1;
	dist_2 = (a * a + b * b) * r * r;
	if (dist_1 > dist_2)
	{
		return 0;
	}
	angle_1 = (O.x - p_1->x) * (p_2->x - p_1->x) + (O.y - p_1->y) * (p_2->y - p_1->y);
	angle_2 = (O.x - p_2->x) * (p_1->x - p_2->x) + (O.y - p_2->y) * (p_1->y - p_2->y);
	if (angle_1 > 0 && angle_2 > 0)
	{
		return 1;
	}
	return 0;
}
//  判断是否相交，相交返回1，否则返回0
int intersect()
{
	ll distA = distance(&O, &A);    //  OA^2
	ll distB = distance(&O, &B);    //  OB^2
	ll distC = distance(&O, &C);    //  OC^2
	ll r2 = r * r;                  //  r^2
	if (distA < r2 && distB < r2 && distC < r2)         //  圆包含三角形
	{
		return 0;
	}
	else if (distA > r2 && distB > r2 && distC > r2)    //  三点都在圆外
	{
		return segOnCircle(&A, &B) || segOnCircle(&A, &C) || segOnCircle(&B, &C);   //  都不相交返回0，反之，返回1
	}
	return 1;
}

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin>>t;
	while(t--)
	{
		cin>>O.x>>O.y>>r;
		cin>>A.x>>A.y>>B.x>>B.y>>C.x>>C.y;
		bool flag = intersect();
		if(flag)
			cout<<"Yes\n";
		else
			cout<<"No\n";
	}
	return 0;
}
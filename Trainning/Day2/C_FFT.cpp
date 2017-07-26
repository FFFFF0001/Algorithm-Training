#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
//给出n条线段长度，问任取3根，组成三角形的概率
//n<=10^5 用FFT求可以组成三角形的取法有几种 
//复数结构体
const double PI = acos(-1.0);
struct Complex
{
	double x, y; //实部和虚部x+yi
	Complex(double _x = 0.0, double _y = 0.0)
	{
		x = _x;
		y = _y;
	}

	Complex operator-(const Complex &b) const

	{

		return Complex(x - b.x, y - b.y);
	}

	Complex operator+(const Complex &b) const

	{

		return Complex(x + b.x, y + b.y);
	}

	Complex operator*(const Complex &b) const

	{

		return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
	}
};
/*

* 进行FFT和IFFT前的反转变换。

* 位置i和 （i二进制反转后位置）互换

* len必须去2的幂

*/

void change(Complex y[], int len)

{

	int i, j, k;

	for (i = 1, j = len / 2; i < len - 1; i++)

	{

		if (i < j)
			swap(y[i], y[j]);

		//交换互为小标反转的元素，i<j保证交换一次

		//i做正常的+1，j左反转类型的+1,始终保持i和j是反转的

		k = len / 2;

		while (j >= k)

		{

			j -= k;

			k /= 2;
		}

		if (j < k)
			j += k;
	}
}

/*

* 做FFT

* len必须为2^k形式，

* on==1时是DFT，on==-1时是IDFT

*/

void fft(Complex y[], int len, int on)

{

	change(y, len);

	for (int h = 2; h <= len; h <<= 1)

	{

		Complex wn(cos(-on * 2 * PI / h), sin(-on * 2 * PI / h));

		for (int j = 0; j < len; j += h)

		{

			Complex w(1, 0);

			for (int k = j; k < j + h / 2; k++)

			{

				Complex u = y[k];

				Complex t = w * y[k + h / 2];

				y[k] = u + t;

				y[k + h / 2] = u - t;

				w = w * wn;
			}
		}
	}

	if (on == -1)

		for (int i = 0; i < len; i++)

			y[i].x /= len;
}
const int maxn = 400040;
Complex x1[maxn];
int a[maxn/4];
long long num[maxn];//1e5*1e5会超int
long long sum[maxn];
int main()
{
	int t,n;
	cin>>t;
	while(t--)
	{
		cin>>n;
		memset(num,0,sizeof(num));
		for(int i=0;i<n;i++)
		{
			cin>>a[i];
			num[a[i]]++;
		}
		sort(a,a+n);
		int len1 = a[n-1] + 1;
		int len = 1;
		while(len<2*len1)	
			len /= 2;
		for(int i=0;i<len1;i++)
			x1[i] = Complex(num[i],0);
		for(int i=len1;i<len;i++)
			x1[i] = Complex(0,0);
		fft(x1,len,1);
		for(int i=0;i<len;i++)
			x1[i] = x1[i] * x1[i];
		fft(x1,len,-1);
		for(int i=0;i<len;i++)
			num[i] = (long long)(x1[i].x+0.5);
		len = 2 * a[n-1];
		//减掉取两个相同的组合
		for(int i=0;i<n;i++)
			num[a[i]+a[i]]--;
		for(int i=1;i<=len;i++)
			num[i] /= 2;
		sum[0] = 0;
		for(int i=1;i<=len;i++)
			sum[i] = sum[i-1] + num[i];
		long long cnt = 0;
		for(int i=0;i<n;i++)
		{
			cnt += sum[len] - sum[a[i]];
			//减掉一个取大，一个取小的
			cnt -= (long long)(n-1-i) * i;
			//减掉一个取本身，另外一个取其他
			cnt -= (n-1);
			cnt -= (long long)(n-1-i)*(n-i-2)/2;
		}
		long long tot = (long long)n*(n-1)*(n-2)/6;
		cout<<(double)cnt/tot<<"\n";	
	}
	return 0;
}
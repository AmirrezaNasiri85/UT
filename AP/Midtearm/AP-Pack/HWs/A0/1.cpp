#include <iostream>
#include <string>
using namespace std;

int main()
{
	int i = 0, j = 0, n = 0, m = 0, q = 0, p = 0, a = 0, b = 0, s = 0, temp = 0, sign = 1;
	string result;
	cin >> n;
	for (i = 0; i < n; i++)
	{
		s = 0;
		sign = 1;
		cin >> p >> q >> m;
		for (j = 0; j < m; j++)
		{
			cin >> a >> b;
			temp = b - a;
			if (temp > q)
			{
				sign = 0;
				result += "0";
				break;
			}
			s += temp;
			if (s > p)
			{
				sign = 0;
				result += "0";
				break;
			}
		}
		if (sign != 0)
			result += "1";
	}
	cout << result;
	return 0;
}
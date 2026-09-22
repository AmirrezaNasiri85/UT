#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int i = 0, t = 0, k = 0, j = 0, n = 0, m = 0, q = 0, p = 0, a = 0, b = 0, s = 0, temp = 0;
	vector <int> j_arr;
	vector <int> k_arr;
	cin >> n;
	for (i = 0; i < n; i++)
	{
		s = 0;
		k = 0;
		j = 0;
		cin >> p >> q >> m;
		for (t = 0; t < m; t++)
		{
			cin >> a >> b;
			temp = b - a;
			if (temp > q && temp > j)
			{
				j = temp - q;
			}
			s += temp;
		}
		if (s > p)
		{
			k += (s - p);
		}
		j_arr.push_back(j);
		k_arr.push_back(k);
	}
	for (i = 0; i < k_arr.size(); i++)
	{
		cout << k_arr[i] << " " << j_arr[i];
		if (i != k_arr.size() - 1)
			cout << endl;
	}
	return 0;
}
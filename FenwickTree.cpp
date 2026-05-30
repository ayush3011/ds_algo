#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> FenwickTree;

void update(int i, int add)
{
    while (i <= N)
    {
        FenwickTree[i] += add;
        i = i + (i & (-i));
    }
}

int sum(int i)
{
    int rangeSum = 0;

    while (i > 0)
    {
        rangeSum += FenwickTree[i];
        i = i - (i & (-i));
    }

    return rangeSum;
}

int main()
{
    int n;
    cin >> n;

    N = n;

    vector<int> arr(n + 1);
    FenwickTree.resize(N + 1, 0);

    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
        update(i, arr[i]);
    }

    update(1, 3);
    cout << "Prefix Sum till index 3: " << sum(3) << endl;

    return 0;
}

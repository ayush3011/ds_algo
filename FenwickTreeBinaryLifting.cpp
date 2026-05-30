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

// finding the lower bound of the prefix sum
int find(int k)
{
    int currInd = 0;
    int prevSum = 0;

    int maxPow = log2(N);

    for (int i = maxPow; i >= 0; i--)
    {
        int next = currInd + (1 << i);

        if (next <= N &&
            prevSum + FenwickTree[next] < k)
        {
            prevSum += FenwickTree[next];
            currInd = next;
        }
    }

    return currInd + 1;
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

    // update(1, 3);
    cout << "Prefix Sum till index 3: " << sum(3) << endl;
    cout << find(3);

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

void build(int ind, int low, int high, vector<int> &seg, vector<int> &arr)
{

    if (low == high)
    {
        seg[ind] = arr[low];
        return;
    }

    int mid = (low + high) >> 1;
    build(2 * ind + 1, low, mid, seg, arr);
    build(2 * ind + 2, mid + 1, high, seg, arr);
    seg[ind] = max(seg[2 * ind + 1], seg[2 * ind + 2]);
}

int query(int ind, int low, int high, int l, int r, vector<int> &seg)
{
    if (low >= l && high <= r) // completely lies
        return seg[ind];

    if (l > high || r < low) // does not lie at all in the range
        return INT_MIN;

    // overlaps
    int mid = (low + high) >> 1;
    int left = query(2 * ind + 1, low, mid, l, r, seg);
    int right = query(2 * ind + 2, mid + 1, high, l, r, seg);

    return max(left, right);
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    vector<int> segmentTree(4 * n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    build(0, 0, n - 1, segmentTree, arr);

    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        cout << query(0, 0, n - 1, l, r, segmentTree) << endl;
    }

    return 0;
}

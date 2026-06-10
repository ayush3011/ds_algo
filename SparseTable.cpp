// Illustrated through Leetcode 3691

struct Node {
    long long val;
    int l;
    int r;

    bool operator<(const Node& other) const { return val < other.val; }
};

class Solution {
public:
    int n;
    vector<vector<int>> maxSparse;
    vector<vector<int>> minSparse;

    vector<vector<int>> preProcessMax(vector<int>& nums) {
        vector<vector<int>> st(n, vector<int>(log2(n) + 1));
        for (int i = 0; i < n; i++)
            st[i][0] = nums[i];

        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
        return st;
    }

    vector<vector<int>> preProcessMin(vector<int>& nums) {
        vector<vector<int>> st(n, vector<int>(log2(n) + 1));
        for (int i = 0; i < n; i++)
            st[i][0] = nums[i];

        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
        return st;
    }

    int getMax(int low, int high) {
        int l = high - low + 1;
        int k = log2(l);

        return max(maxSparse[low][k], maxSparse[low + l - (1 << k)][k]);
    }

    int getMin(int low, int high) {
        int l = high - low + 1;
        int k = log2(l);

        return min(minSparse[low][k], minSparse[low + l - (1 << k)][k]);
    }

    long long getValue(int l, int r) {
        return 1LL * getMax(l, r) - getMin(l, r);
    }

    long long maxTotalValue(vector<int>& nums, int k) {
        n = nums.size();

        maxSparse = preProcessMax(nums);
        minSparse = preProcessMin(nums);

        priority_queue<Node> pq;

        for (int l = 0; l < n; l++) {
            pq.push({getValue(l, n - 1), l, n - 1});
        }

        long long ans = 0;

        while (k--) {
            auto cur = pq.top();
            pq.pop();

            ans += cur.val;

            int l = cur.l;
            int r = cur.r;

            if (r > l) {
                pq.push({getValue(l, r - 1), l, r - 1});
            }
        }

        return ans;
    }
};

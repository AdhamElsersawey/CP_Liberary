struct MonoStack {
private:
    const vector<int> &a;
 
    vector<int> solve(bool findNext, bool findGreater) {
        int n = a.size();
        vector<int> res(n, -1);
        stack<int> st;
 
        int start = findNext ? n - 1 : 0;
        int end = findNext ? -1 : n;
        int step = findNext ? -1 : 1;
 
        for (int i = start; i != end; i += step) {
            while (!st.empty()) {
                bool shouldPop = findGreater ? (a[st.top()] <= a[i]) : (a[st.top()] >= a[i]);
                if (shouldPop) st.pop();
                else break;
            }
            if (!st.empty()) res[i] = st.top();
            st.push(i);
        }
        return res;
    }
 
public:
    MonoStack(const vector<int> &v) : a(v) {}
 
    vector<int> NextGreater() {
        return solve(true, true);
    }
 
    vector<int> NextSmaller() {
        return solve(true, false);
    }
 
    vector<int> PrevGreater() {
        return solve(false, true);
    }
 
    vector<int> PrevSmaller() {
        return solve(false, false);
    }
};

// Towers of Hanoi using Gray Code

// - Represent each disk by one bit.
// - Bit 0 (LSB) = smallest disk.
// - Bit n-1 (MSB) = largest disk.
// - Generate Gray codes:
//       gray(i) = i ^ (i >> 1)
// - Consecutive Gray codes differ by exactly one bit.
// - The changed bit tells which disk to move.
// - Disk = index of changed bit + 1.

// Destination:
// - Smallest disk has two choices:
//     Odd n : From -> Target -> rem -> From -> ...
//     Even n: From -> rem -> Target -> From -> ...
// - Every other disk has only ONE legal move.
//   Move it to the only rod where it can legally be placed.

// Total moves = (1 << n) - 1.



int main() {
    int n;
    cin >> n;
    stack<int> a, b, c;
    for (int i = n - 1; ~i; --i) {
        a.push(i);
    }
    auto g = [](int x){return x ^ (x >> 1);};
    vi move(3);
    if (n & 1) {
        move = {3, 2, 1};
    }else{
        move = {2, 3, 1};
    }
    int cnt = 0;
    cout << (1 << n) - 1 << el;
    for (int i = 1; i < 1 << n; ++i) {
        int cur = __lg(g(i) ^ g(i - 1));
        if (!a.empty() && a.top() == cur) {
            cout << 1 << ' ';
            a.pop();
            if (cur == 0) {
                if (move[cnt] == 1) {
                    a.push(0);
                } else if (move[cnt] == 2) {
                    b.push(0);
                    cout << 2 << el;
                }else{
                    c.push(0);
                    cout << 3 << el;
                }
                cnt++;
            }else{
                if (b.top() > cur) {
                    b.push(cur);
                    cout << 2 << el;
                }else{
                    c.push(cur);
                    cout << 3 << el;
                }
            }
        } else if (!b.empty() && b.top() == cur) {
            b.pop();
            cout << 2 << ' ';
            if (cur == 0) {
                if (move[cnt] == 1) {
                    a.push(0);
                    cout << 1 << el;
                } else if (move[cnt] == 2) {
                    b.push(0);
                }else{
                    c.push(0);
                    cout << 3 << el;
                }
                cnt++;
            }else{
                if (a.top() > cur) {
                    a.push(cur);
                    cout << 1 << el;
                }else{
                    c.push(cur);
                    cout << 3 << el;
                }
            }
        }else{
            c.pop();
            cout << 3 << ' ';
            if (cur == 0) {
                if (move[cnt] == 1) {
                    a.push(0);
                    cout << 1 << el;
                } else if (move[cnt] == 2) {
                    b.push(0);
                    cout << 2 << el;
                }else{
                    c.push(0);
                }
                cnt++;
            }else{
                if (b.top() > cur) {
                    b.push(cur);
                    cout << 2 << el;
                }else{
                    a.push(cur);
                    cout << 1 << el;
                }
            }
        }
    }
}
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
//     Odd n : From -> To -> Aux -> From -> ...
//     Even n: From -> Aux -> To -> From -> ...
// - Every other disk has only ONE legal move.
//   Move it to the only rod where it can legally be placed.

// Total moves = (1 << n) - 1.

struct Rod {
    stack<int> disks;
};

// Return the index of the changed bit (0 = smallest disk)
int changedBit(int a, int b) {
    return __builtin_ctz(a ^ b);
}

int main() {
    int n;
    cin >> n;

    // Rods:
    // 0 = From
    // 1 = Auxiliary
    // 2 = Target
    Rod rods[3];

    // Initially all disks are on rod 0.
    // Larger number = larger disk.
    for (int i = n; i >= 1; i--)
        rods[0].disks.push(i);

    // Position of every disk.
    // pos[1] = rod containing disk 1.
    vector<int> pos(n + 1, 0);

    // Order in which the smallest disk moves.
    vector<int> cycle;

    if (n & 1)
        cycle = {0, 2, 1};      // From -> Target -> Aux
    else
        cycle = {0, 1, 2};      // From -> Aux -> Target

    // Current position inside the cycle.
    int smallestIndex = 0;

    int totalMoves = (1 << n) - 1;

    int prevGray = 0;

    for (int step = 1; step <= totalMoves; step++) {

        // Current Gray code.
        int gray = step ^ (step >> 1);

        // Which bit changed?
        int bit = changedBit(prevGray, gray);

        // Disk number (1 = smallest)
        int disk = bit + 1;

        if (disk == 1) {
            // -------------------------------
            // Smallest disk:
            // Move according to the fixed cycle.
            // -------------------------------

            int from = cycle[smallestIndex];
            smallestIndex = (smallestIndex + 1) % 3;
            int to = cycle[smallestIndex];

            rods[from].disks.pop();
            rods[to].disks.push(1);

            pos[1] = to;

            cout << from + 1 << " -> " << to + 1 << '\n';
        }
        else {
            // ---------------------------------------
            // Any larger disk:
            // There is exactly ONE legal destination.
            // ---------------------------------------

            int from = pos[disk];

            // Check the other two rods.
            for (int to = 0; to < 3; to++) {

                if (to == from)
                    continue;

                // Can place disk if rod is empty
                // or its top disk is larger.
                if (rods[to].disks.empty() ||
                    rods[to].disks.top() > disk) {

                    // Remove disk from source rod.
                    rods[from].disks.pop();

                    // Put it on destination rod.
                    rods[to].disks.push(disk);

                    pos[disk] = to;

                    cout << from + 1 << " -> " << to + 1 << '\n';

                    break;
                }
            }
        }

        // Save current Gray code.
        prevGray = gray;
    }
}
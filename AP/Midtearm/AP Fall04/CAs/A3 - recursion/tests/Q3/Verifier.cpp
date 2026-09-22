#include <bits/stdc++.h>
using namespace std;

struct Point { int r, c; };

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc != 2) {
        cerr << "Usage: ./validator <test_number>\n";
        cerr << "Example: ./validator 02\n";
        return 1;
    }

    string testNum = argv[1];
    string base = testNum + "/" + testNum;
    string in_path = base + ".in";
    string out_path = base + ".out";
    string prog_path = base + ".output";

    ifstream fin(in_path);
    if (!fin) {
        cerr << "[" << testNum << "] Cannot open input file: " << in_path << "\n";
        return 1;
    }

    int n, m;
    fin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) fin >> grid[i];
    fin.close();

    struct Point S{-1, -1}, M{-1, -1};
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'S') S = {i, j};
            if (grid[i][j] == 'M') M = {i, j};
        }

    if (S.r == -1 || M.r == -1) {
        cerr << "[" << testNum << "] Missing S or M in map.\n";
        return 1;
    }

    ifstream fout(out_path);
    if (!fout) {
        cerr << "[" << testNum << "] Cannot open expected output file: " << out_path << "\n";
        return 1;
    }
    string correct;
    getline(fout, correct);
    fout.close();

    ifstream fprog(prog_path);
    if (!fprog) {
        cerr << "[" << testNum << "] Cannot open program output file: " << prog_path << "\n";
        return 1;
    }
    string output;
    getline(fprog, output);
    fprog.close();

    auto trim = [](string &s) {
        s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
    };
    trim(correct);
    trim(output);

    // --- بررسی NO_PATH ---
    if (correct == "NO_PATH" && output != "NO_PATH") {
        cout << "[" << testNum << "] FAIL: Expected NO_PATH but program returned a path.\n";
        return 1;
    }
    if (correct != "NO_PATH" && output == "NO_PATH") {
        cout << "[" << testNum << "] FAIL: Program returned NO_PATH but a path exists.\n";
        return 1;
    }
    if (correct == "NO_PATH" && output == "NO_PATH") {
        cout << "[" << testNum << "] PASS (Both NO_PATH)\n";
        return 0;
    }

    if (correct.size() != output.size()) {
        cout << "[" << testNum << "] FAIL: Path length mismatch (expected "
             << correct.size() << ", got " << output.size() << ")\n";
        return 1;
    }

    int r = S.r, c = S.c;
    for (char move : output) {
        if (move == 'u') r--;
        else if (move == 'd') r++;
        else if (move == 'l') c--;
        else if (move == 'r') c++;
        else {
            cout << "[" << testNum << "] FAIL: Invalid move character '" << move << "'\n";
            return 1;
        }

        if (r < 0 || r >= n || c < 0 || c >= m) {
            cout << "[" << testNum << "] FAIL: Out of bounds\n";
            return 1;
        }
        if (grid[r][c] == '1') {
            cout << "[" << testNum << "] FAIL: Went through wall at (" << r << "," << c << ")\n";
            return 1;
        }
    }

    if (r == M.r && c == M.c) {
        cout << "[" << testNum << "] PASS\n";
        return 0;
    } else {
        cout << "[" << testNum << "] FAIL: Did not reach M\n";
        return 1;
    }

    return 0;
}

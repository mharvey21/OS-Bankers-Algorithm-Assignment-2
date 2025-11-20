#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
        if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>\n";
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Error: cannot open input file.\n";
        return 1;
    }
    int n, m;
    fin >> n >> m;

    if (!fin) {
        cerr << "Error: invalid format (n m).\n";
        return 1;
    }
    vector<int> total(m);
    for (int j = 0; j < m; ++j) {
        fin >> total[j];
    }
    vector<vector<int>> alloc(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fin >> alloc[i][j];
        }
    }
    vector<vector<int>> maxNeed(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fin >> maxNeed[i][j];
        }
    }
    vector<int> avail(m, 0);
    for (int j = 0; j < m; ++j) {
        int sumAlloc = 0;
        for (int i = 0; i < n; ++i) {
            sumAlloc += alloc[i][j];
        }
        avail[j] = total[j] - sumAlloc;
    }
    
    
    vector<vector<int>> need(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            need[i][j] = maxNeed[i][j] - alloc[i][j];
        }
    }

        vector<int> work = avail;        // Work = Available
    vector<bool> finish(n, false);   // Finish[i] = false for all i
    vector<int> safeSequence;        // Safe sequence

    int countFinished = 0;
    while (countFinished < n) {
        bool foundProcess = false;

        for (int i = 0; i < n; ++i) {
            if (!finish[i]) {
                bool canRun = true;
                for (int j = 0; j < m; ++j) {
                    if (need[i][j] > work[j]) {
                        canRun = false;
                        break;
                    }
                }

                if (canRun) {
                    // This process can safely run to completion
                    for (int j = 0; j < m; ++j) {
                        work[j] += alloc[i][j];
                    }
                    finish[i] = true;
                    safeSequence.push_back(i);
                    countFinished++;
                    foundProcess = true;
                }
            }
        }

        if (!foundProcess) {
            break;
        }
    }
    bool safe = true;
    for (int i = 0; i < n; ++i) {
        if (!finish[i]) {
            safe = false;
            break;
        }
    }

    if (safe) {
        cout << "The system is in a SAFE state.\n";
        cout << "Safe sequence: ";
        for (size_t k = 0; k < safeSequence.size(); ++k) {
            cout << "P" << safeSequence[k];
            if (k + 1 < safeSequence.size()) cout << " -> ";
        }
        cout << "\n";
    } else {
        cout << "The system is in an UNSAFE state (no safe sequence).\n";
    }

    return 0;
}

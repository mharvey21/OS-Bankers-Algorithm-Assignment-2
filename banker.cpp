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
    


    cout << "=== Allocation Table ===\n";
    for (int i = 0; i < n; ++i) {
        cout << "P" << i << " | ";
    for (int j = 0; j < m; ++j) {
        cout << alloc[i][j] << " ";
    }
    cout << "\n";
    }
    cout << "\n";

    cout << "=== Maximum Demand Table ===\n";
    for (int i = 0; i < n; ++i) {
         cout << "P" << i << " | ";
    for (int j = 0; j < m; ++j) {
         cout << maxNeed[i][j] << " ";
         }
     cout << "\n";
     }
     cout << "\n";

     cout << "=== Remaining Need Table ===\n";
     for (int i = 0; i < n; ++i) {
          cout << "P" << i << " | ";
    for (int j = 0; j < m; ++j) {
        cout << need[i][j] << " ";
    }
    cout << "\n";
    }
    cout << "\n";

    cout << "Initial Available Resources | ";
    for (int j = 0; j < m; ++j) {
         cout << avail[j] << " ";
    }
    cout << "\n\n";


    vector<int> work = avail;        
    vector<bool> finish(n, false);   
    vector<int> safeSequence;        

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
    cout << "System Status: SAFE\n";
    cout << "Safe Order: [ ";
    for (size_t k = 0; k < safeSequence.size(); ++k) {
        cout << "P" << safeSequence[k];
        if (k + 1 < safeSequence.size()) {
            cout << " | ";
        } else {
            cout << " ";
        }
    }
    cout << "]\n";
    } else {
    cout << "System Status: UNSAFE\n";
    }



    return 0;
}

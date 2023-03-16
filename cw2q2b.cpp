#include <iostream>
#include <vector>
using namespace std;

void dp(const vector<int>&, int, int);

int main() {

    vector<int> v{0};
    // insert an extra v[0] to avoid dealing with 0/1 indices
    // never actually accessed

    int n, W, M, x;
    cout << "Enter n:" << endl;
    cin >> n;
    cout << "Enter the n values:" << endl;
    for(int i = 0; i < n; i++) {
        cin >> x;
        v.push_back(x);
    }
    cout << "Enter W:" << endl;
    cin >> W;
    cout << "Enter M:" << endl;
    cin >> M;

    dp(v,W,M);

}

void dp(const vector<int>& v, int W, int M) {

    int V[v.size()][M+1]; // v.size() == n+1
    int T[v.size()][M+1]; // for traceback

    // base cases
    for(int i = 1; i < v.size(); i++) {
        V[i][0] = 0;
        T[i][0] = 0;
    }
    for(int j = 0; j <= M; j++) {
        V[0][j] = 0;
        T[0][j] = 0;
    }

    int max, maxj, temp;

    for(int m = 1; m <= M; m++) {
        for(int i = 1; i < v.size(); i++) {

            // don't strike at time i
            max = V[i-1][m];
            maxj = -1;

            // strike with load w
            // note that this means the previous subproblem can only
            // use m-w units of ammo
            for(int w = 1; w <= std::min(m,W); w++) {

                if (i-w-2 >= 0)
                    temp = V[i-w-2][m-w] + std::min(v[i], w*w);
                else // first strike may not be full charge!
                    temp = std::min(std::min(v[i], W*W), m*m);

                if (temp > max) {
                    max = temp;
                    if (i-w-2 >= 0) maxj = w;
                    else maxj = std::min(W, m);
                }
            }

            V[i][m] = max;
            T[i][m] = maxj;
        }
    }

    cout << "optimal damage = " << V[v.size()-1][M] << endl;

    // traceback
    int i = v.size()-1, j = M;
    while(i > 0 && j > 0) {

        int k = T[i][j];
        if (k==-1) i--;
        else {
            cout << "strike at time " << i << " load " << k << endl;
            i = i-k-2;
            j = j-k;
        }
    }
}

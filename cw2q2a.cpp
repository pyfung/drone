#include <iostream>
#include <vector>
#include <limits>
using namespace std;

void dp(const vector<int>&, int);

int main() {

    vector<int> v{0};
    // insert an extra v[0]=0 to avoid dealing with 0/1 indices

    int n, W, x;
    cout << "Enter n:" << endl;
    cin >> n;
    cout << "Enter the n values:" << endl;
    for(int i = 0; i < n; i++) {
        cin >> x;
        v.push_back(x);
    }
    cout << "Enter W:" << endl;
    cin >> W;

    dp(v,W);

}

void dp(const vector<int>& v, int W) {

    int V[v.size()]; // v.size() == n+1
    int T[v.size()]; // for traceback

    // base case
    V[0] = 0;
    T[0] = 0;

    int max, maxj, temp;

    for(int i = 1; i < v.size(); i++) {

        // don't strike at time i
        max = V[i-1];
        maxj = 0;

        for(int w = 1; w <= W; w++) {

            if (i-w-2 >= 0)
                temp = V[i-w-2] + std::min(v[i], w*w);
            else // first strike full charge
                temp = std::min(v[i], W*W);

            if (temp > max) {
                max = temp;
                if (i-w-2 >= 0) maxj = w; else maxj = W;
            }
        }

        V[i] = max;
        T[i] = maxj;
        cout << "V[" << i << "]=" << V[i] << " T[" << i << "]=" << T[i] <<endl;
    }

    cout << "optimal damage = " << V[v.size()-1] << endl;

    // traceback
    int i = v.size() - 1;
    while(i > 0) {

        int j = T[i];

        if (j==0) i--;
        else {
            cout << "strike at time " << i << " load " << T[i] << endl;
            i = i-T[i]-2;
        }
    }
}

#include <iostream>

using namespace std;

bool subset_sum(unsigned int s[], int n, unsigned int sum) {
    size_t numbers = n + 1;
    bool dyn[numbers][sum+1]; 

    for(size_t i = 0; i <= numbers; ++i) {
        for(unsigned int j = 0; j <= sum; ++j) {
            dyn[i][j] = false;
        }
    }

    for(size_t i = 0; i <= numbers; ++i) {
        dyn[i][0] = true;
    }

    for(size_t i = 1; i <= numbers; ++i) {
        for(unsigned int j = 1; j <= sum; ++j) {
            if(s[i-1] > j) {
                dyn[i][j] = dyn[i-1][j];
            } else {
                dyn[i][j] = dyn[i-1][j] || dyn[i-1][j - s[i-1]];
            }
        }
    }
    return dyn[numbers][sum];
}

int main() {
    unsigned int s[] = {5, 1, 4, 3, 10}; 
    cout<<subset_sum(s, 5, 8)<<endl;
    return 0;
}

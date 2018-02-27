#include <iostream>
#include <queue>
#include <cmath>

#define get_digit(num, div) (div > 1 ? (num / div) % 10 : num % 10)

using namespace std;

void radix_sort(int arr[], int size) {
    unsigned long long div = 1;
    queue<int> buckets[10];
    bool larger = false;
    do {
        larger = false;
        for(int i = 0; i < size; ++i) {
            short digit = get_digit(arr[i], div);
            buckets[digit].push(arr[i]);
            if(arr[i] / div > 0) larger = true;
        }
        for(int i = 0, index = 0; i < 10; ++i) {
            while(!buckets[i].empty()) {
                arr[index++] = buckets[i].front();
                buckets[i].pop();
            }
        }
        div *= 10;
    } while(larger);
}

int main() {
    int n;
    cin>>n;
    int arr[n];
    for(int i = 0; i < n; ++i) cin>>arr[i];
    radix_sort(arr, n);
    for(int i = 0; i < n; ++i) cout<<arr[i]<<" ";
    cout<<endl;
}

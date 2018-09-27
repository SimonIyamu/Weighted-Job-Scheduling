#include <iostream>
#include <algorithm>
using namespace std;
 
struct Job{ int start, finish, profit; };
 
bool comparison(Job a, Job b){ 
    return (a.finish < b.finish); 
}
 
// Find the latest job in the sorted array that doesn't run in common time with job[i]
int previousJob(Job arr[], int i){
    for (int j=i-1; j>=0; j--){
        if (arr[j].finish <= arr[i].start)
            return j;
    }
    return -1;
}
 
int findMaxProfit(Job arr[], int n){
    sort(arr, arr+n, comparison);
 
    //table stores the sum of the profits for the jobs until arr[i]
    int *table = new int[n];
    table[0] = arr[0].profit;
 
    for (int i=1; i<n; i++){
        // inclProf is the profit including the current job
        int inclProf = arr[i].profit;
        int l = previousJob(arr, i);
        if (l != -1)
            inclProf += table[l];
 
        table[i] = max(inclProf, table[i-1]);
    }
 
    int result = table[n-1];
    delete[] table;
 
    return result;
}
 
int main(){
    Job arr[] = {{8, 10, 20}, {1, 7, 70}, {6, 19, 100}, {20,50,160},{5, 50, 250}}; //The optimal profit should be 260
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << "The optimal profit is " << findMaxProfit(arr, n) << endl;
    return 0;
}

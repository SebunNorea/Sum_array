int main() {
    int n = 10000000;
    int m = 4;
    Array arr(n, m);
    auto start = chrono::high_resolution_clock::now();
    int total_sum = arr.sum();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Total sum: " << total_sum << endl;
    cout << "Time taken: " << duration.count() << " microseconds" << endl;
    return 0;
}

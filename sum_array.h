class Array {
public:
    Array(int n, int m) {
        // Генерируем случайный массив
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, 1000);
        for (int i = 0; i < n; i++) {
            data.push_back(dist(gen));
        }
        // Вычисляем размер части массива для каждого потока
        int chunk_size = n / m;
        for (int i = 0; i < m; i++) {
            int start = i * chunk_size;
            int end = (i != m - 1) ? (i + 1) * chunk_size - 1 : n - 1;
            chunks.push_back({start, end});
        }
    }

    int sum() {
        // Запускаем потоки на вычисление суммы для каждой части массива
        vector<thread> threads;
        for (const auto& chunk : chunks) {
            threads.emplace_back([this, chunk]() {
                int s = 0;
                for (int i = chunk.first; i <= chunk.second; i++) {
                    s += data[i];
                }
                chunk_sums.push_back(s);
            });
        }
        // Дожидаемся окончания всех потоков
        for (auto& t : threads) {
            t.join();
        }
        // Вычисляем общую сумму
        int total_sum = 0;
        for (int s : chunk_sums) {
            total_sum += s;
        }
        return total_sum;
    }

private:
    vector<int> data;
    vector<pair<int, int>> chunks;
    vector<int> chunk_sums;
};

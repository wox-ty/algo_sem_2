#include <vector>
//#include "iostream"
//#include "algorithm"
#include "string"
#include "blazingio.hpp"

const long long prime_1 = 41;
const long long prime_2 = 75;

struct item {
    std::string key;
    long long counter = 0;

    item() {
        key = "";
        counter = 0;
    };
};

class Hash_map {
private:
    long long capacity;

    long long hashing_1(std::string &key) {
        long long hash = 0;
        for (char c: key) {
            hash *= prime_1;
            hash += c;
        }
        return hash % capacity;
    }

    long long hashing_2(std::string &key) {
        long long hash = 0;
        for (char c: key) {
            hash *= prime_2;
            hash += c;
        }
        return hash % capacity;
    }

public:
    std::vector<item> data;

    Hash_map(long long x) {
        capacity = x * 29;
        data.resize(capacity);
    }

    void add(std::string &val) {
        long long max_iter = capacity;
        item tmp;
        tmp.key = val;
        tmp.counter = 1;
        while (max_iter--) {
            std::string key = tmp.key;
            long long idx_1 = hashing_1(key);
            long long idx_2 = hashing_2(key);
            if (data[idx_1].key.empty() || data[idx_1].key == key) {
                data[idx_1].key = key;
                data[idx_1].counter++;
                return;
            }
            if (data[idx_2].key.empty() || data[idx_2].key == key) {
                data[idx_2].key = key;
                data[idx_2].counter++;
                return;
            }

            item h = data[idx_1];
//            std::swap(data[idx_1], tmp);
            data[idx_1] = tmp;
            tmp = h;

//            std::swap(data[idx_1], data[idx_2]);

        }
    }

    long long contains(std::string &key) {
        long long idx_1 = hashing_1(key);
        long long idx_2 = hashing_2(key);
        if (data[idx_1].key == key) {
            return data[idx_1].counter;
        }
        if (data[idx_2].key == key) {
            return data[idx_2].counter;
        }

        return -1;
    }
};

int main() {
    long long N;
    std::cin >> N;

    std::vector<long long> score(3, 0);
    Hash_map repeats(N);
    std::vector<std::vector<std::string>> tasks(3);

    std::string task;
    for (long long i = 0; i < N; ++i) {
        std::cin >> task;
        tasks[0].push_back(task);
        repeats.add(task);
//        score[0] += 3;
    }
    for (long long i = 0; i < N; ++i) {
        std::cin >> task;
        tasks[1].push_back(task);
        repeats.add(task);
//        score[1] += 3;
    }
    for (long long i = 0; i < N; ++i) {
        std::cin >> task;
        tasks[2].push_back(task);
        repeats.add(task);
//        score[2] += 3;
    }

    for (long long i = 0; i < 3; ++i) {
        for (auto key: tasks[i]) {
            long long r = repeats.contains(key);
            if (r == 1){
                score[i] += 3;
            }
            else if (r == 2) {
                score[i] += 1;
            } else if (r == 3) {
                score[i] += 0;
            }
        }
    }

    std::cout << score[0] << ' ' << score[1] << ' ' << score[2];

    return 0;
}
/*
4
g f d a
g h k l
i o k v

4
baba aacc aabb bbaa
caca baba ccaa bcbc
ccbb bbcc cbcb aacc


*/
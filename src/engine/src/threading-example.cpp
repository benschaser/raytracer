#include <thread>
#include <random>
#include <vector>
#include <iostream>

double random_double() {
    static thread_local std::random_device rd;
    static thread_local std::default_random_engine engine{rd()};
    static thread_local std::uniform_real_distribution<double> distribution{0.0, 1.0};
    return distribution(engine);
}
void trace(double& result) {
    int sum{0};
    for (int i = 0; i < 1000000000; ++i) {
        sum += i;
    }
    result = random_double();
}

int main() {
    int N = 7;
    std::vector<std::thread> threads;
    std::vector<double> results(N);
    for (int i = 1; i < N; ++i) {
        std::thread t{trace, std::ref(results.at(i))};
        threads.push_back(std::move(t));
    }

    trace(results.at(0));
    for (auto& thread : threads) {
        thread.join();
    }
    for (double r : results) {
        std::cout << r << ' ';
    }
    std::cout << '\n';
}
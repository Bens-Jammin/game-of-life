#include <random>

// temp, do a better version
bool randomBool() {
    static std::mt19937 gen(std::random_device{}());
    static std::bernoulli_distribution dist(0.3);
    return dist(gen);
}

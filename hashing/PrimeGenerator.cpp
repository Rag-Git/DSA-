#include <vector>
#include <stdexcept>

class PrimeGenerator {
public:
    PrimeGenerator(const std::vector<int>& primes)
        : prime_sizes(primes) {}

    int get_next_size() {
        if (prime_sizes.empty()) {
            throw std::out_of_range("No more primes available");
        }
        int next = prime_sizes.back();
        prime_sizes.pop_back();
        return next;
    }

private:
    std::vector<int> prime_sizes;
};

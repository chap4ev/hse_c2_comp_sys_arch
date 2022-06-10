#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <random>
#include <unistd.h>

const bool LOGGING = false;

class Thread {
  public:
    virtual ~Thread() {}
    virtual void run() = 0;
    int start() {
        return pthread_create(&_ThreadId, nullptr, Thread::thread_func, this);
    }
    int wait() {
        return pthread_join(_ThreadId, NULL);
    }

  protected:
    pthread_t _ThreadId;
    static void *thread_func(void *d) {
        (static_cast<Thread *>(d))->run();
        return nullptr;
    }
};

class CounterThread : public Thread {
  public:
    static size_t max_counting_range;

    CounterThread(const uint32_t *data, size_t begin, size_t end)
        : _data(data), _begin(begin), _end(end) {}
    virtual void run() {
        if (_end - _begin > max_counting_range) {
            size_t mid = (_begin + _end) / 2;
            if (LOGGING) {
                std::cout << "Splitting range " << _begin << " " << _end << " into "
                          << _begin << " " << mid << " and " << mid << " " << _end
                          << "\n";
            }
            CounterThread left(_data, _begin, mid);
            left.start();
            CounterThread right(_data, mid, _end);
            right.start();
            left.wait();
            right.wait();
            _sum = left.get_sum() + right.get_sum();
        } else {
            if (LOGGING) {
                std::cout << "Counting sum of the range " << _begin << " " << _end
                          << "\n";
            }
            for (size_t i = _begin; i < _end; ++i) {
                _sum += _data[i];
            }
        }
    }

    uint64_t get_sum() {
        return _sum;
    }

  protected:
    const uint32_t *_data;
    size_t _begin, _end;
    uint64_t _sum = 0;

};

size_t CounterThread::max_counting_range = 100;



uint64_t threaded_count_sum(uint32_t *data, size_t size) {
    CounterThread counter(data, 0, size);
    counter.start();
    counter.wait();
    return counter.get_sum();
}

uint64_t basic_count_sum(uint32_t *data, size_t size) {
    uint64_t sum = 0;
    for (size_t i = 0; i < size; ++i) {
        sum += data[i];
    }
    return sum;
}

int main(int argc, char *argv[]) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<std::mt19937::result_type> rand_num(0, 1000);

    if (argc == 3 && !strcmp(argv[1], "-r")) { // random fill
        CounterThread::max_counting_range = 100;
        size_t size = atoi(argv[2]);
        if (10000 < size) {
            std::cout << "random fill size should be in range [0, 10000]" << std::endl;
            return 1;
        }
        std::cout << "random fill " << size << " elements" << std::endl;

        uint32_t *data = new uint32_t[size];

        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<uint32_t>(rand_num(g));
        }

        std::cout << "Start thraded sum" << std::endl;
        auto begin = std::chrono::steady_clock::now();

        std::cout << "Elements sum = " << threaded_count_sum(data, size) << std::endl;

        auto end = std::chrono::steady_clock::now();
        std::cout << "Time elapsed = "
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
                  << "[ms]" << std::endl;

        std::cout << "Start basic sum" << std::endl;
        begin = std::chrono::steady_clock::now();

        std::cout << "Elements sum = " << basic_count_sum(data, size) << std::endl;

        end = std::chrono::steady_clock::now();
        std::cout << "Time elapsed = "
                  << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count()
                  << "[ms]" << std::endl;

        delete[] data;

    } else {
        CounterThread::max_counting_range = 2;
        std::cout << "Enter the probate amount: ";
        size_t expected_sum = 0;
        std::cin >> expected_sum;

        std::cout << "Enter the shares of the 8 heirs: ";
        uint32_t data[8];
        for (auto &i : data) {
            std::cin >> i;
        }

        auto sum = threaded_count_sum(data, 8);

        std::cout << "Calculated total amount of heir's shares = " << sum << std::endl;
        if (sum == expected_sum) {
            std::cout << "All good!";
        } else if (expected_sum > sum) {
            std::cout << "Warning! Amount of theft of a lawyer = " << expected_sum - sum 
                      << "\nExpected " << expected_sum << " got " << sum;
        } else {
            std::cout << "Congrats! The lawyer added extra money! Ammount: " << sum - expected_sum 
                      << "\nExpected: " << expected_sum << " Got: " << sum;
        }
    }
    return 0;
}

#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <unistd.h>

class Thread {
public:
  virtual ~Thread() {}
  virtual void run() = 0;
  int start() {
    return pthread_create(&_ThreadId, nullptr, Thread::thread_func, this);
  }
  int wait() { return pthread_join(_ThreadId, NULL); }

protected:
  pthread_t _ThreadId;
  static void *thread_func(void *d) {
    (static_cast<Thread *>(d))->run();
    return nullptr;
  }
};

class CountingRangeThread : public Thread {
public:
  CountingRangeThread(const int *data, size_t begin, size_t end)
      : _data(data), _begin(begin), _end(end) {}
  virtual void run() {
    if (_end - _begin > stop_range) {
      size_t mid = (_begin + _end) / 2;
      CountingRangeThread left(_data, _begin, mid);
      left.start();
      CountingRangeThread right(_data, mid, _end);
      right.start();
      left.wait();
      right.wait();
      _sum = left.get_sum() + right.get_sum();
    } else {
      for (size_t i = _begin; i < _end; ++i) {
        _sum += _data[i];
      }
    }
  }
  uint64_t get_sum() { return _sum; }

protected:
  const int *_data;
  size_t _begin, _end;
  uint64_t _sum = 0;

  const static size_t stop_range = 2;
};

uint64_t count_sum(int *data, size_t size) {
  CountingRangeThread counter(data, 0, size);
  counter.start();
  counter.wait();
  return counter.get_sum();
}

int main() {
  int data[]{100, 100, 100, 100, 100, 100, 100, 100};
  std::cout << count_sum(data, 8);

  return 0;
}

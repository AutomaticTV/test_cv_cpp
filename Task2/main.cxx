
#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <atomic>

// Thread safe implementation of a Queue using a std::queue
template <typename T> class SafeQueue {
private:
  std::queue<T> m_queue;
  mutable std::mutex m_mutex;

public:
  bool empty() const;

  void enqueue(const T &t);
  bool dequeue(T &t);
};

template <typename T> inline bool SafeQueue<T>::empty() const {
  std::unique_lock<std::mutex> lock(m_mutex);
  return m_queue.empty();
}

template <typename T> inline void SafeQueue<T>::enqueue(const T &t) {
  std::unique_lock<std::mutex> lock(m_mutex);
  m_queue.push(t);
}

template <typename T> inline bool SafeQueue<T>::dequeue(T &t) {
  std::unique_lock<std::mutex> lock(m_mutex);

  if (m_queue.empty())
    return false;

  t = std::move(m_queue.front());

  m_queue.pop();
  return true;
}

////////////////////////////////////////////////////////////////////

SafeQueue<std::function<void()>> tasks_queue;
std::condition_variable has_work_cv;
std::atomic<int> value = 0;
std::mutex mutex;


void producer() {
  while (true) {
    auto task_ptr =
        std::make_shared<std::packaged_task<int()>>([] {
          value++;
          if (value > 42) value = 0;
          return value.load();
        });

    std::shared_future<int> result_future = task_ptr->get_future();

  {
    std::unique_lock<std::mutex> lock(mutex);

    tasks_queue.enqueue([task_ptr, result_future] {
      (*task_ptr)();
    });

    has_work_cv.notify_all();

  }

    std::cout << result_future.get() << std::endl;
  }
}

void consumer() {

  while (true) {
    {
      if (tasks_queue.empty()) {
        std::unique_lock<std::mutex> lock(mutex);
        has_work_cv.wait(lock, [&] { return !tasks_queue.empty(); });
      }
    }

    std::function<void()> func;
    bool dequeued = tasks_queue.dequeue(func);
    if (dequeued) {
      func();
    }

    std::this_thread::yield();
  }
}

int main() {
  std::thread producer_thread{&producer};
  std::thread consumer_thread{&consumer};

  producer_thread.join();
  consumer_thread.join();
}
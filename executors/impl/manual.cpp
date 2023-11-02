#include <meijic/executors/impl/manual.hpp>
namespace exec {
void ManualExecutor::Submit(Runnable *task) { queue_.push(std::move(task)); }

size_t ManualExecutor::RunAtMost(size_t limit) {
  size_t task_number = std::min(limit, queue_.size());
  for (size_t i = 0; i < task_number; ++i) {
    std::move(queue_.front())->Run();
    queue_.pop();
  }
  return task_number;
}

size_t ManualExecutor::Drain() {
  size_t done = 0;
  while (!queue_.empty()) {
    std::move(queue_.front())->Run();
    queue_.pop();
    ++done;
  }
  return done;
}
} // namespace exec
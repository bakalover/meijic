#pragma once
#include <meijic/executors/executor.hpp>
#include <meijic/executors/task.hpp>
#include <queue>
namespace exec {

class ManualExecutor : public Executor {
public:
  ManualExecutor() = default;

  // Non-copyable
  ManualExecutor(const ManualExecutor &) = delete;
  ManualExecutor &operator=(const ManualExecutor &) = delete;

  // Non-movable
  ManualExecutor(ManualExecutor &&) = delete;
  ManualExecutor &operator=(ManualExecutor &&) = delete;

  void Submit(Task *task) override;

  size_t RunAtMost(size_t limit);

  bool RunNext() { return RunAtMost(1) == 1; }

  size_t Drain();

  size_t TaskCount() const { return queue_.size(); }

  bool IsEmpty() const { return queue_.empty(); }

  bool NonEmpty() const { return !IsEmpty(); }

private:
  std::queue<Task *> queue_;
};

} // namespace exec

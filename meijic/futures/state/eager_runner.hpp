#pragma once

#include <meijic/futures/state/rendezvous.hpp>
#include <meijic/futures/state/state.hpp>
#include <meijic/futures/traits/value_of.hpp>
#include <meijic/futures/types/naked.hpp>
namespace futures::state {

template <SomeFuture F>
class EagerRunner final : public IConsumer<traits::ValueOf<F>>,
                          public IState<traits::ValueOf<F>> {
  using ValueType = traits::ValueOf<F>;

public:
  explicit EagerRunner(F &&thunk) : thunk_{std::move(thunk)} {}

  void RunThunk() { thunk_.Start(this); }

  void SetConsumer(IConsumer<ValueType> *consumer) override {
    rendezvous_.SetConsumer(consumer);
  }

private:
  void Consume(Output<ValueType> output) noexcept override {
    rendezvous_.SetOutput(std::move(output));
  }

private:
  F thunk_;
  Rendezvous<ValueType> rendezvous_;
};

} // namespace futures::state

#pragma once

#include <functional>
#include <memory>
#include <vector>

template <typename TSender, typename TData>
struct EventDetails {
  TSender sender;
  TData data;
};

class SubscriptionHandle {
public:
  using ID = size_t;

  SubscriptionHandle() = delete;

  SubscriptionHandle(void* owner, ID id, std::function<void(ID)> unsub)
  : m_owner(owner), m_id(id), m_unsub(unsub) {}

  SubscriptionHandle(const SubscriptionHandle&) = delete;
  SubscriptionHandle& operator=(const SubscriptionHandle&) = delete;

  SubscriptionHandle(SubscriptionHandle&& other) noexcept {
    m_owner = other.m_owner;
    m_id = other.m_id;
    m_unsub = std::move(other.m_unsub);

    other.m_unsub = nullptr;
  }

  ~SubscriptionHandle() {
    Reset();
  }

  bool BelongsTo(void* owner) const {
    return m_owner == owner;
  }

  void Reset() {
    if (m_unsub) {
      m_unsub(m_id);
      m_unsub = nullptr;
    }
  }

  ID GetID() const {
    return m_id;
  }

private:
  void* m_owner;
  ID m_id;
  std::function<void(ID)> m_unsub;
};

template <typename... Args>
class Event {
public:
  using Callback = std::function<void(Args...)>;
  using Handle = SubscriptionHandle;

  Handle Sub(Callback callback) {
    auto id = nextID++;
    auto state = std::make_shared<ConnectionState>();

    listeners.push_back({ id, callback, state });

    return Handle{this, id, [this](size_t id) { Unsub(id); } };
  }

  void Invoke(Args... args) {
    for (auto& listener : listeners) {
      if (listener.state->active) listener.callback(args...);
    }
  }

private:
  struct ConnectionState {
    bool active = true;
  };

  struct Listener {
    size_t id;
    Callback callback;

    std::shared_ptr<ConnectionState> state;
  };

  std::vector<Listener> listeners;
  size_t nextID = 0;

  void Unsub(size_t id) {
    for (auto& listener : listeners) {
      if (listener.id == id) {
        listener.state->active = false;
      }
    }
  }
};
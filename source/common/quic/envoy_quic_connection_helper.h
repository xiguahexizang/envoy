#pragma once

#include "source/common/quic/platform/envoy_quic_clock.h"

#include "quiche/quic/core/crypto/quic_random.h"
#include "quiche/quic/core/quic_connection.h"
#include "quiche/quic/core/quic_simple_buffer_allocator.h"

namespace Envoy {
namespace Quic {

// Derived to provide EnvoyQuicClock and default random generator and buffer
// allocator.
class EnvoyQuicConnectionHelper : public quic::QuicConnectionHelperInterface {
public:
  EnvoyQuicConnectionHelper(Event::Dispatcher& dispatcher)
      : clock_(dispatcher), random_generator_(quic::QuicRandom::GetInstance()) {}

  ~EnvoyQuicConnectionHelper() override = default;

  // QuicConnectionHelperInterface
  const quic::QuicClock* GetClock() const override { return &clock_; }
  quic::QuicRandom* GetRandomGenerator() override { return random_generator_; }
  quic::QuicBufferAllocator* GetStreamSendBufferAllocator() override { return &buffer_allocator_; }

private:
  EnvoyQuicClock clock_;
  quic::QuicRandom* random_generator_ = nullptr;
  quic::SimpleBufferAllocator buffer_allocator_;
};

} // namespace Quic
} // namespace Envoy

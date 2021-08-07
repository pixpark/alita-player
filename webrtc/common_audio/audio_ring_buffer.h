/*
 *  Copyright (c) 2015 The devzhaoyou@dii_media project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */
#ifndef WEBRTC_COMMON_AUDIO_AUDIO_RING_BUFFER_H_
#define WEBRTC_COMMON_AUDIO_AUDIO_RING_BUFFER_H_

#include <stddef.h>

#include <memory>
#include <vector>

struct RingBuffer;

namespace dii_media_kit {

// A ring buffer tailored for float deinterleaved audio. Any operation that
// cannot be performed as requested will cause a crash (e.g. insufficient data
// in the buffer to fulfill a read request.)
class AudioRingBuffer final {
 public:
  // Specify the number of channels and maximum number of frames the buffer will
  // contain.
  AudioRingBuffer(size_t channels, size_t max_frames);
  ~AudioRingBuffer();

  // Copies |data| to the buffer and advances the write pointer. |channels| must
  // be the same as at creation time.
  void Write(const float* const* data, size_t channels, size_t frames);

  // Copies from the buffer to |data| and advances the read pointer. |channels|
  // must be the same as at creation time.
  void Read(float* const* data, size_t channels, size_t frames);

  size_t ReadFramesAvailable() const;
  size_t WriteFramesAvailable() const;

  // Moves the read position. The forward version advances the read pointer
  // towards the write pointer and the backward verison withdraws the read
  // pointer away from the write pointer (i.e. flushing and stuffing the buffer
  // respectively.)
  void MoveReadPositionForward(size_t frames);
  void MoveReadPositionBackward(size_t frames);

 private:
  // TODO(kwiberg): Use std::vector<std::unique_ptr<RingBuffer>> instead.
  std::vector<RingBuffer*> buffers_;
};

}  // namespace dii_media_kit

#endif  // WEBRTC_COMMON_AUDIO_AUDIO_RING_BUFFER_H_

/*
 *  Copyright (c) 2014 The devzhaoyou@dii_media project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef WEBRTC_COMMON_AUDIO_FIR_FILTER_SSE_H_
#define WEBRTC_COMMON_AUDIO_FIR_FILTER_SSE_H_

#include <memory>

#include "webrtc/common_audio/fir_filter.h"
#include "webrtc/system_wrappers/include/aligned_malloc.h"

namespace dii_media_kit {

class FIRFilterSSE2 : public FIRFilter {
 public:
  FIRFilterSSE2(const float* coefficients,
                size_t coefficients_length,
                size_t max_input_length);

  void Filter(const float* in, size_t length, float* out) override;

 private:
  size_t coefficients_length_;
  size_t state_length_;
  std::unique_ptr<float[], AlignedFreeDeleter> coefficients_;
  std::unique_ptr<float[], AlignedFreeDeleter> state_;
};

}  // namespace dii_media_kit

#endif  // WEBRTC_COMMON_AUDIO_FIR_FILTER_SSE_H_

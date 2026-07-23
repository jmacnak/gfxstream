// Copyright 2026 The Android Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either expresso or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <cstdint>
#include <memory>

namespace gfxstream {
namespace host {

namespace gl {
class ColorBufferGl;
}  // namespace gl

namespace vk {
class ColorBufferVk;
}  // namespace vk

// A (mostly) generic interface to a `ColorBuffer` so that the various backends
// interact with `ColorBuffer`s without needing to depend on all of the various
// underlying `ColorBuffer` implementations.
class IColorBuffer {
   public:
    virtual ~IColorBuffer() = default;

    virtual uint32_t getHndl() const = 0;
    virtual uint32_t getWidth() const = 0;
    virtual uint32_t getHeight() const = 0;

    virtual void touch() = 0;

    virtual gl::ColorBufferGl* getColorBufferGl() = 0;
    virtual vk::ColorBufferVk* getColorBufferVk() = 0;
};

// A (mostly) generic shared owning reference  to a `ColorBuffer` so that the
// various backends can have shared ownership of a `ColorBuffer` without needed
// to depend on the underlying `ColorBuffer` implementations.
using IColorBufferRef = std::shared_ptr<IColorBuffer>;

}  // namespace host
}  // namespace gfxstream

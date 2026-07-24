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

#include <functional>
#include <string>

#include "gfxstream/CancelableFuture.h"

namespace gfxstream {
namespace host {

class GlobalState {
   public:
    virtual ~GlobalState() = default;

    virtual void registerProcessCleanupCallback(void* key, uint64_t contextId,
                                                std::function<void()> callback) = 0;
    virtual void unregisterProcessCleanupCallback(void* key) = 0;

    virtual void invalidateColorBuffer(uint32_t colorBufferHandle) = 0;
    virtual void flushColorBuffer(uint32_t colorBufferHandle) = 0;
    virtual void flushColorBufferFromBytes(uint32_t colorBufferHandle, const void* bytes,
                                           size_t bytesSize) = 0;

    virtual CancelableFuture scheduleAsyncWork(std::function<void()> work,
                                               std::string description) = 0;

    virtual void registerVulkanInstance(uint64_t id, const char* appName) const {}
    virtual void unregisterVulkanInstance(uint64_t id) const {}
};

}  // namespace host
}  // namespace gfxstream

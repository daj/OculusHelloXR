// Copyright (c) 2017-2020 The Khronos Group Inc
//
// SPDX-License-Identifier: Apache-2.0

#pragma once

struct PlatformData {
#ifdef XR_USE_PLATFORM_ANDROID
    void* applicationVM;
    void* applicationActivity;
#endif
};

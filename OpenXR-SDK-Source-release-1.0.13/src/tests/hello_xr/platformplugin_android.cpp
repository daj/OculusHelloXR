// Copyright (c) 2017-2020 The Khronos Group Inc.
//
// SPDX-License-Identifier: Apache-2.0

#include "pch.h"
#include "common.h"
#include "platformdata.h"
#include "platformplugin.h"

#ifdef XR_USE_PLATFORM_ANDROID

namespace {
struct AndroidPlatformPlugin : public IPlatformPlugin {
    AndroidPlatformPlugin(const std::shared_ptr<Options>& /*unused*/, const std::shared_ptr<PlatformData>& data) {
        instanceCreateInfoAndroid = {XR_TYPE_INSTANCE_CREATE_INFO_ANDROID_KHR};
        instanceCreateInfoAndroid.applicationVM = data->applicationVM;
        instanceCreateInfoAndroid.applicationActivity = data->applicationActivity;

        PFN_xrInitializeLoaderKHR xrInitializeLoaderKHR;
        xrGetInstanceProcAddr(XR_NULL_HANDLE, "xrInitializeLoaderKHR", (PFN_xrVoidFunction*)&xrInitializeLoaderKHR);
        if (xrInitializeLoaderKHR != NULL) {
            XrLoaderInitInfoAndroidKHR loaderInitializeInfoAndroid;
            memset(&loaderInitializeInfoAndroid, 0, sizeof(loaderInitializeInfoAndroid));
            loaderInitializeInfoAndroid.type = XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR;
            loaderInitializeInfoAndroid.next = nullptr;
            loaderInitializeInfoAndroid.applicationVM = data->applicationVM;
            loaderInitializeInfoAndroid.applicationContext = data->applicationActivity;
            xrInitializeLoaderKHR((XrLoaderInitInfoBaseHeaderKHR*)&loaderInitializeInfoAndroid);
        }
    }

    std::vector<std::string> GetInstanceExtensions() const override { return {XR_KHR_ANDROID_CREATE_INSTANCE_EXTENSION_NAME}; }

    XrBaseInStructure* GetInstanceCreateExtension() const override { return (XrBaseInStructure*)&instanceCreateInfoAndroid; }

    XrInstanceCreateInfoAndroidKHR instanceCreateInfoAndroid;
};
}  // namespace

std::shared_ptr<IPlatformPlugin> CreatePlatformPlugin_Android(const std::shared_ptr<Options>& options,
                                                              const std::shared_ptr<PlatformData>& data) {
    return std::make_shared<AndroidPlatformPlugin>(options, data);
}
#endif

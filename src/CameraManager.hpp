/* SPDX-License-Identifier: GPL-2.0 */

/*
 * Xen para-virtualized camera backend
 *
 * Copyright (C) 2018 EPAM Systems Inc.
 */
#ifndef SRC_CAMERAMANAGER_HPP_
#define SRC_CAMERAMANAGER_HPP_

#include <unordered_map>

#include <xen/be/Log.hpp>

#include "CameraHandler.hpp"

template <typename __Handler__>
class HandlerManager
{
    typedef std::shared_ptr<__Handler__> __HandlerPtr;
    typedef std::weak_ptr<__Handler__> __HandlerWeakPtr;
public:
    HandlerManager(const std::string& name = "unknown manager") : mLog(name) {}
    ~HandlerManager() {}

    __HandlerPtr getHandler(const std::string& uniqueId) {
        std::lock_guard<std::mutex> lock(mLock);
        auto it = mHandlers.find(uniqueId);
        if (it != mHandlers.end()) {
            if (auto handler = it->second.lock()) {
                return handler;
            }
        }

        /* This handler is not on the list yet - create now. */
        auto handler = getNewHandler(uniqueId);
        mHandlers[uniqueId] = handler;
        return handler;
    }


private:
    XenBackend::Log mLog;
    std::mutex mLock;
    std::unordered_map<std::string, __HandlerWeakPtr> mHandlers;
    __HandlerPtr getNewHandler(const std::string& devName) {
        return __HandlerPtr(new __Handler__(devName));
    }
};

#endif /* SRC_CAMERAMANAGER_HPP_ */

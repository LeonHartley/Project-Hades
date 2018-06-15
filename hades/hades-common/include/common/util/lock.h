#pragma once

#include <uv.h>
#include <cstdlib>

namespace hades {
    enum RwLockType {
        READ, WRITE
    };

    class RwMutex {
    public:
        RwMutex() : lock_(static_cast<uv_rwlock_t *>(malloc(sizeof(uv_rwlock_t)))) {
            uv_rwlock_init(lock_);
        }

        ~RwMutex() {
            uv_rwlock_destroy(lock_);
            free(lock_);
        }

        void lock(RwLockType type) {
            switch (type) {
                case READ:
                    uv_rwlock_rdlock(lock_);
                case WRITE:
                    uv_rwlock_wrlock(lock_);
            }
        }

        void unlock(RwLockType type) {
            switch (type) {
                case READ:
                    uv_rwlock_rdunlock(lock_);
                case WRITE:
                    uv_rwlock_wrunlock(lock_);
            }
        }

    private:
        uv_rwlock_t *lock_;
    };

    class RwLockGuard {

    public:
        RwLockGuard(RwMutex *mutex, RwLockType type) : mutex_(mutex), type_(type) {
            mutex_->lock(type);
        }

        ~RwLockGuard() {
            mutex_->unlock(type_);
        }

    private:
        RwLockType type_;
        RwMutex *mutex_;
    };
}

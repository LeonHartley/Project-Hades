#pragma once

#include <iostream>
#include <deque>
#include <memory>
#include <functional>
#include <mutex>

namespace hades {
    template<typename Obj>
    class ObjectPoolFactory {
    public:
        virtual std::shared_ptr<Obj> create() = 0;
    };

    template<typename Obj, typename ObjFactory = ObjectPoolFactory<Obj>>
    class ObjectPool {

    public:
        ObjectPool(int initialSize, ObjFactory factory) : initialSize_(initialSize) {
            for (int i = 0; i < initialSize; i++) {
                this->pool_.push_back(factory.create());
            }
        }

        std::shared_ptr<Obj> pop() {
            std::lock_guard<std::mutex> lock(this->mutex_);
            std::shared_ptr<Obj> obj = this->pool_.front();
            this->pool_.pop_front();

            return std::move(obj);
        }

        void push(std::shared_ptr<Obj> obj) {
            std::lock_guard<std::mutex> lock(this->mutex_);
            this->pool_.push_back(std::move(obj));
        }
    private:
        int initialSize_;

        std::mutex mutex_;
        std::deque<std::shared_ptr<Obj>> pool_;
    };

}
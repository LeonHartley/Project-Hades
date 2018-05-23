#pragma once

#include <memory>
#include <map>

namespace hades {
    template<typename Component>
    class Container {
    public:
        Container() {

        }

        template<typename T>
        std::shared_ptr<T> component() {
            return std::static_pointer_cast<T>(components_[typeid(T).name()]);
        }

        template<typename T>
        void component(std::shared_ptr<T> component) {
            components_[typeid(T).name()] = std::dynamic_pointer_cast<Component>(component);
        }

    protected:
        std::map<std::string, std::shared_ptr<Component>> components_;
    };
}
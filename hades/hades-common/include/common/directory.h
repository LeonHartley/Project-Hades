#pragma once

#include <map>

namespace hades {
    template<typename Key, typename Val>
    class Directory {
    public:
        Directory() : directory_{} {

        }

    private:
        std::map<Key, Val> directory_;
    };

}
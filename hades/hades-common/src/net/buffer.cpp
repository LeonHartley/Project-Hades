#include "common/net/buffer.h"

#include <string>

template<>
int hades::Buffer::read() {
    return 9001;
}

template<typename W>
void hades::Buffer::write(W data) {

}

template<>
std::string hades::Buffer::read() {
    return "Heya :D";
}

template<>
bool hades::Buffer::read() {
    return true;
}

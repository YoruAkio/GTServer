#include <cstdint>
#include <cstring>
#include <string>

using namespace std;

namespace Ventura {
    namespace PacketDecoder {
        string DataToString(uint8_t* data, uint32_t data_len) {
            std::string ret{};
            ret.resize(data_len - 1);
            std::memcpy((void*)ret.data(), data, data_len - 1);
            return ret;
        }
    }
}

#include <string>
#include <cstring>
#include <cstdint>

using namespace std;

namespace Ventura {
    namespace PacketDecoder {
        string DataToString(uint8_t* data, uint32_t data_len);
    }
}

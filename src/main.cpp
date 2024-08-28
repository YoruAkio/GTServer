#include <spdlog/logger.h>
#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <enet/enet.h>

#include "server/server.h"
#include "packet/packet.h"

using namespace std;

int main() {
    Ventura::Server::Initialize(17091);
    Ventura::Server::HandleServer();
    return 0;
}

// int main() {
//     ENetAddress address;
//     ENetHost* host;

//     enet_address_set_host(&address, "0.0.0.0");
//     address.port = 17091;

//     host = enet_host_create(&address, 1024, 20, 0, 0);
//     if (!host) {
//         spdlog::error("An error occurred while creating an ENet host.");
//         return 1;
//     }

//     host->checksum = enet_crc32;
//     enet_host_compress_with_range_coder(host);

//     spdlog::info("Server started on port 17091");

//     bool running = true;
//     ENetEvent event;
//     while (running && enet_host_service(host, &event, 1000) >= 0) {
//         switch (event.type) {
//             case ENET_EVENT_TYPE_CONNECT: {
//                 spdlog::info("Client connected");
//                 break;
//             }
//             case ENET_EVENT_TYPE_RECEIVE: {
//                 // Convert packet data to a string
//                 std::vector<char> data(event.packet->data, event.packet->data + event.packet->dataLength);
//                 std::string packetData(data.begin(), data.end());

//                 spdlog::info("Packet received: {}", packetData);
//                 ENetPacket *packet = enet_packet_create("Hello, world!", 12, ENET_PACKET_FLAG_RELIABLE);
//                 enet_peer_send(event.peer, 0, packet);
//                 break;
//             }
//             case ENET_EVENT_TYPE_DISCONNECT: {
//                 spdlog::info("Client disconnected");
//                 break;
//             }
//             case ENET_EVENT_TYPE_NONE:
//                 break;
//         }
//     }

//     enet_host_destroy(host);
//     return 0;
// }

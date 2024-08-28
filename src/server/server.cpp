#include "enet/enet.h"
#include "spdlog/spdlog.h"
#include "packet/packet.h"

ENetHost* server;
using namespace std;

int GetMessage(ENetPacket* packet) {
   	if (packet->dataLength > 3u) {
  		return *(packet->data);
   	}
   	return 0;
}

namespace Ventura {
    namespace Server {
        void Initialize(int port) {
            if (enet_initialize() != 0) {
                spdlog::error("An error occurred while initializing ENet");
                exit(EXIT_FAILURE);
            }
            spdlog::info("Initializing Enet Server!");

            ENetAddress address;
            enet_address_set_host(&address, "0.0.0.0");
            address.port = port;
            server = enet_host_create(&address, 128, 2, 0, 0);
            if (!server) {
                spdlog::info("An error occurred while trying to create an ENet server host");
                exit(EXIT_FAILURE);
            }

            server->checksum = enet_crc32;
            enet_host_compress_with_range_coder(server);
            spdlog::info("Server initialized and running on port: {}", port);
        }

        void HandleServer() {

            ENetEvent event;
            while (true) {
                while (enet_host_service(server, &event, 2000) > 0) {
                    ENetPeer* peer = event.peer;
                    switch (event.type) {
                        case ENET_EVENT_TYPE_CONNECT:
                            char client_ip[16];
                            enet_address_get_host_ip(&peer->address, client_ip, 16);
                            spdlog::info("A new client connected from {}",
                                         client_ip);

                            spdlog::info("A new client connected from {}:{}",
                                         event.peer->address.host,
                                         event.peer->address.port);
                            break;
                        case ENET_EVENT_TYPE_RECEIVE:
                            if (GetMessage(event.packet) == 2 or GetMessage(event.packet) == 3) {
                                spdlog::info("Received a message from client: {}", Ventura::PacketDecoder::DataToString(event.packet->data + 4, event.packet->dataLength - 4));
                            }
                            else {
                                spdlog::info("Other message from client: {}", Ventura::PacketDecoder::DataToString(event.packet->data + 4, event.packet->dataLength - 4));
                                spdlog::info("A packet of length {} was received on channel {}",
                                             event.packet->dataLength,
                                             event.channelID);
                            }

                            // spdlog::info("A packet of length {} was received on channel {}",
                            //              event.packet->dataLength,
                            //              event.channelID);
                            enet_packet_destroy(event.packet);
                            break;
                        case ENET_EVENT_TYPE_DISCONNECT:
                            spdlog::info("{} disconnected.",
                                         event.peer->data);
                            event.peer->data = NULL;
                            break;
                        case ENET_EVENT_TYPE_NONE:
                            break;
                    }
                }
            }
        }
    }
}


// #include "server.h"
//
// namespace Ventura {
//     Server::Server(const uint8_t& instanceId, const std::string& address, const uint16_t& port, const size_t& max_peers) :
//     m_instance_id(instanceId), m_address(address), m_port(port), m_max_peers(max_peers),
//     // m_player_pool{ std::make_shared<PlayerPool>() },
//     // m_world_pool{ std::make_shared<WorldPool>() } {
//     }
//     Server::~Server() {
//       if (!this->Stop())
//         return;
//       enet_host_destroy(this->GetHost());
//     }
//
//     bool Server::Start() {
//         ENetAddress address;
//         enet_address_set_host(&address, m_address.c_str());
//         address.port = m_port;
//
//         m_host = enet_host_create(&address, m_max_peers, 2, 0, 0);
//         if (!m_host)
//             return false;
//
//         m_host->checksum = enet_crc32;
//         enet_host_compress_with_range_coder(m_host);
//         return true;
//     }
//     // bool Ventura::Stop() {
//     //     for (auto& pair : m_player_pool->GetPlayers())
//     //         pair.second->Disconnect(0U);
//     //     return true;
//     // }
// }

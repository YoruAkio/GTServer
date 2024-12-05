#include "enet/enet.h"
#include "Packet/packet.h"
#include "Utils/Logger.h"

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
                Logger::Error("An error occurred while initializing ENet");
                exit(EXIT_FAILURE);
            }
            Logger::Info("Initializing Enet Server!");

            ENetAddress address;
            enet_address_set_host(&address, "0.0.0.0");
            address.port = port;
            server = enet_host_create(&address, 128, 2, 0, 0);
            if (!server) {
                Logger::Info("An error occurred while trying to create an ENet server host");
                exit(EXIT_FAILURE);
            }

            server->checksum = enet_crc32;
            enet_host_compress_with_range_coder(server);
            Logger::Info("Server initialized and running on port: {}", port);
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
                            Logger::Info("A new client connected from {}",
                                         client_ip);

                            Logger::Info("A new client connected from {}:{}",
                                         event.peer->address.host,
                                         event.peer->address.port);
                            break;
                        case ENET_EVENT_TYPE_RECEIVE:
                            if (GetMessage(event.packet) == 2 or GetMessage(event.packet) == 3) {
                                Logger::Info("Received a message from client: {}", Ventura::PacketDecoder::DataToString(event.packet->data + 4, event.packet->dataLength - 4));
                            }
                            else {
                                Logger::Info("Other message from client: {}", Ventura::PacketDecoder::DataToString(event.packet->data + 4, event.packet->dataLength - 4));
                                Logger::Info("A packet of length {} was received on channel {}",
                                             event.packet->dataLength,
                                             event.channelID);
                            }

                            Logger::Info("A packet of length {} was received on channel {}",
                                         event.packet->dataLength,
                                         event.channelID);
                            enet_packet_destroy(event.packet);
                            break;
                        case ENET_EVENT_TYPE_DISCONNECT:
                            Logger::Info("{} disconnected.",
                                         event.peer->data);
                            event.peer->data = NULL;
                            enet_peer_reset(event.peer);
                            break;
                        case ENET_EVENT_TYPE_NONE:
                            break;
                    }
                }
            }
        }
    }
}

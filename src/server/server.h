#include <enet/enet.h>

namespace Ventura {
    namespace Server {
        void Initialize(int port);
        void HandleServer();
    }
}

// #pragma once
// #include <deque>
// #include <memory>
// #include <string>
// #include <thread>
// #include <vector>
// #include <enet/enet.h>
//
// namespace Ventura {
//     // class PlayerPool;
//     // class WorldPool;
//     class Server {
//     public:
//         Server(const uint8_t& instanceId, const std::string& address, const uint16_t& port, const size_t& max_peers);
//         ~Server();
//
//         bool Start();
//         bool Stop();
//
//         [[nodiscard]] uint8_t GetInstanceId() const { return m_instance_id; }
//         [[nodiscard]] std::string GetAddress() const { return m_address; }
//         [[nodiscard]] uint16_t GetPort() const { return m_port; }
//         [[nodiscard]] ENetHost* GetHost() const { return m_host; }
//
//     private:
//         uint8_t m_instance_id;
//         std::string m_address{ "0.0.0.0" };
//         uint16_t m_port;
//
//         ENetHost* m_host;
//         size_t m_max_peers;
//
//         // std::shared_ptr<PlayerPool> m_player_pool;
//         // std::shared_ptr<WorldPool> m_world_pool;
//     };
// }

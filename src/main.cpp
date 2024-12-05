#include <enet/enet.h>

#include "Server/Server.h"
#include "Packet/Packet.h"
#include "Utils/Logger.h"

using namespace std;

int main() {
    Ventura::Server::Initialize(17091);
    Ventura::Server::HandleServer();
    return 0;
}
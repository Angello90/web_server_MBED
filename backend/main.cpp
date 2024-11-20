#include "mbed.h"
#include "rtos.h"
#include "EthernetInterface.h"
#include "C12832.h"

EthernetInterface eth;
TCPSocket socket;
C12832 lcd(D11, D13, D12, D7, D10);

char buffer[];
char buffer2[2000];

float get_temp()
{
    return 25.0;
}

float get_pot()
{
    return 0.5;
}

void get_data_json()
{
    sprintf(buffer, "{\"temp\": %1.2f, \"pot\": %1.2f}", get_temp(), get_pot());
}


int main() {
    socket.open(&eth);
    socket.bind(80);
    socket.listen(3);
    while (true)
    {
        SocketAddress client_address;
        TCPSocket* client_socket = socket.accept();
        client_socket->resvfrom(&client_address, buffer2, 2000);
        get_data_json();
        client_socket->sendto(client_address, buffer, strlen(buffer));
        client_socket.close();
    }
}
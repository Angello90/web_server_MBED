#include "mbed.h"
#include "rtos.h"
#include "EthernetInterface.h"
#include <fstream>
#include "C12832.h"

EthernetInterface eth;
TCPSocket socket;
C12832 lcd(D11, D13, D12, D7, D10);

char buffer[];

void load_index_html()
{
    std::ifstream file("index.html");
    if (file.is_open())
    {
        file.read(buffer);
        file.close();
    }
}

void error_handler(const char *msg)
{
    lcd.cls();
    lcd.locate(0, 0);
    lcd.printf("Error! %d", msg);
}


int main()
{
    load_index_html();
    nsapi_error_t status = eth.connect();
    if (status != NSAPI_ERROR_OK)
    {
        error_handler("Connection Ethernet impossible!");
        return -1;
    }
    status = socket.open(&eth);
    if (status != NSAPI_ERROR_OK)
    {
        error_handler("Ouverture du Socket impossible!");
        return -1;
    }
    status = socket.bind(80);
    if (status != NSAPI_ERROR_OK)
    {
        error_handler("Socket binding impossible!");
        return -1;
    }
    status = socket.listen(3);
    if (status != NSAPI_ERROR_OK)
    {
        error_handler("Socket listening impossible!");
        return -1;
    }

    while (true)
    {
        SocketAddress client_address;
        TCPSocket* client_socket = server_socket.accept(&client_address);
        clientAddr = socket.accept();
        client_socket->send(buffer, strlen(buffer));
        client_socket.close();
        delete client_socket;
    }
}
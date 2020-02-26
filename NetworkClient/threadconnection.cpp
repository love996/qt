#include "threadconnection.h"
#include "tcpconnection.h"

ThreadConnection::ThreadConnection()
{

}

void ThreadConnection::run()
{
     TcpConnection connection("127.0.0.1", 12345);
     return QThread::run();
}

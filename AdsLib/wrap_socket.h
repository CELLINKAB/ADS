#ifndef WRAP_SOCKET_H
#define WRAP_SOCKET_H

#include <cstdint>
#ifdef _WIN32
#include <WinSock2.h>
inline int InitSocketLibrary(void) {
    WSADATA wsaData;
    return WSAStartup(0x0202, &wsaData);
}

#define NATIVE_SELECT(SOCK, READFDS, WRITEFDS, EXCEPTFDS, TIMEOUT) \
    ::select(0, READFDS, WRITEFDS, EXCEPTFDS, TIMEOUT)

#define s_addr S_un.S_addr
typedef int socklen_t;
#endif

#ifdef __gnu_linux__
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
typedef int SOCKET;
#define INVALID_SOCKET ((int)-1)
#define SOCKET_ERROR ((int)-1)
#define closesocket(X) close(X)
#define WSACleanup()
#define WSAGetLastError() errno
inline int InitSocketLibrary(void) {
    return 0;
};
#define NATIVE_SELECT(SOCK, READFDS, WRITEFDS, EXCEPTFDS, TIMEOUT) \
    ::select(SOCK, READFDS, WRITEFDS, EXCEPTFDS, TIMEOUT)
#endif
#endif // WRAP_SOCKET_H
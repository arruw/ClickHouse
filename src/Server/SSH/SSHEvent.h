#pragma once

#include <memory>

struct ssh_event_struct;
struct ssh_session_struct;
using ssh_event = ssh_event_struct *;
using ssh_session = ssh_session_struct *;
using ssh_event_callback = int (*)(int fd, int revents, void * userdata);

namespace ssh
{

class SSHEvent
{
public:
    SSHEvent();
    ~SSHEvent();

    SSHEvent(const SSHEvent &) = delete;
    SSHEvent & operator=(const SSHEvent &) = delete;

    SSHEvent(SSHEvent &&) noexcept;
    SSHEvent & operator=(SSHEvent &&) noexcept;

    ssh_event get() const;
    void addSession(ssh_session session);
    void removeSession(ssh_session session);
    void addFd(int fd, int events, ssh_event_callback cb, void * userdata);
    void removeFd(int fd);
    int poll(int timeout);
    int poll();

private:
    static void deleter(ssh_event e);

    std::unique_ptr<ssh_event_struct, decltype(&deleter)> event;
};

}

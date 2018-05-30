
#pragma once
#include <memory>

class SlurmDB {
public:
    SlurmDB (); 
    virtual ~SlurmDB ();
    SlurmDB( const SlurmDB& ) = delete; // non construction-copyable
    SlurmDB& operator=( const SlurmDB& ) = delete; // non copyable

    void connect();
    void disconnect();
    void commit(bool c = true);
    void update();

    auto get_connection(){
      return db_conn;
    }

    bool is_connected();

private:
    void* db_conn;
    bool connection_established;
};

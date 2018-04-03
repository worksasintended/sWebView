
#pragma once
#include <memory>

class SlurmDB {
public:
    SlurmDB (); 
    virtual ~SlurmDB ();

    void connect();
    void disconnect();

    auto get_connection(){
      return db_conn;
    }

private:
    void* db_conn;
};

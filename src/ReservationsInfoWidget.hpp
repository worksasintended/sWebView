

#pragma once


#include <Wt/WContainerWidget>
#include <Wt/WTreeTable.h>

#include "Observable.hpp"
#include "UsersInfo.hpp"
#include "ReservationsInfo.hpp"

#include <memory>

class ReservationsInfoWidget : public Wt::WContainerWidget, public Observer{
public:
    ReservationsInfoWidget ( std::shared_ptr<ReservationsInfo> ); 
    virtual ~ReservationsInfoWidget ();
    void update() override;

private:
    std::shared_ptr<ReservationsInfo> reservations_info;
};


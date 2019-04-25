

#pragma once


#include <Wt/WContainerWidget.h>
#include <Wt/WTreeTable.h>

#include "Observable.hpp"
#include "UsersInfo.hpp"
#include "ReservationsInfo.hpp"
#include <regex>
#include <memory>

class ReservationsInfoWidget : public Wt::WContainerWidget, public Observer{
public:
    ReservationsInfoWidget ( std::shared_ptr<ReservationsInfo> ); 
    virtual ~ReservationsInfoWidget ();
    void update() override;

private:
    void make_add_dialog (Wt::WDialog* dialog);
    std::shared_ptr<ReservationsInfo> reservations_info;
    std::string search_regex_string;
};


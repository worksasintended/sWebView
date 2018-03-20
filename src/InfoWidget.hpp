#pragma once
#include <Wt/WContainerWidget.h>
#include "Observable.hpp"
#include "PartitionsInfo.hpp"

class InfoWidget : public Wt::WContainerWidget, public Observer {
public:
    InfoWidget ();
    virtual ~InfoWidget ();
    virtual void update() override;

private:
    PartitionsInfo* partitions_info = nullptr; // perhaps make this a shared_ptr
};


#pragma once

#include <Wt/WContainerWidget.h>
#include "Observer.hpp"

class SlurmOverviewWidget : public Wt::WContainerWidget, public Observer {
public:
    SlurmOverviewWidget (SlurmOverviewData* _data);
    virtual ~SlurmOverviewWidget ();

    virtual void update() override;

private:
    SlurmOverviewData* data;
};

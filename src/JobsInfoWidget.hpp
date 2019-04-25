
#pragma once

#include <Wt/WContainerWidget.h>
#include <Wt/WTreeTable.h>

#include "Observable.hpp"
#include "JobsInfo.hpp"

#include <memory>

class JobsInfoWidget : public Wt::WContainerWidget, public Observer{
public:
    JobsInfoWidget ( std::shared_ptr<JobsInfo> ); 
    virtual ~JobsInfoWidget ();
    void update() override;

private:

    std::shared_ptr<JobsInfo> jobs_info;
};


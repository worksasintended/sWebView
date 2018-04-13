

#include "JobsInfoWidget.hpp"
#include <Wt/WTable.h>
#include <Wt/WPushButton.h>
#include <Wt/WDialog.h>
#include <Wt/WComboBox.h>
#include <Wt/WLineEdit.h>

#include "StandardDialogs.hpp"

using namespace std;
using namespace Wt;

JobsInfoWidget::JobsInfoWidget (
    std::shared_ptr<JobsInfo> _jobs_info
    ){
  jobs_info = _jobs_info;
  jobs_info->add_observer(this);

  this->update();
}

JobsInfoWidget::~JobsInfoWidget()  {

}

void JobsInfoWidget::update(){
  this->clear();

  auto table = this->addWidget( make_unique<WTable>() );

  // optical stuff
  table->setHeaderCount(1);
  table->addStyleClass("table form-inline table-bordered table-hover table-condensed table-striped");

  int column_ctr = 0;
  int line_ctr = 0;
  table->elementAt(line_ctr, column_ctr++)->addWidget(make_unique<WText>("job_id"));
  table->elementAt(line_ctr, column_ctr++)->addWidget(make_unique<WText>("job_name"));
  table->elementAt(line_ctr, column_ctr++)->addWidget(make_unique<WText>("user_name"));
  table->elementAt(line_ctr, column_ctr++)->addWidget(make_unique<WText>("state"));
  table->elementAt(line_ctr, column_ctr++)->addWidget(make_unique<WText>("node list"));
  table->elementAt(line_ctr, column_ctr++)->addWidget(make_unique<WText>("operations"));
  line_ctr++;

  for( auto& job_info : *jobs_info ){
    column_ctr = 0 ;
    table->elementAt( line_ctr, column_ctr++ )
      ->addWidget( make_unique<WText>( to_string(job_info.get_id()) ) ); 
    table->elementAt( line_ctr, column_ctr++ )
      ->addWidget( make_unique<WText>( job_info.get_description()) ); 
    table->elementAt( line_ctr, column_ctr++ )
      ->addWidget( make_unique<WText>( job_info.get_user_name()) ); 
    table->elementAt( line_ctr, column_ctr++ )
      ->addWidget( make_unique<WText>( job_info.get_state()) ); 
    table->elementAt( line_ctr, column_ctr++ )
      ->addWidget( make_unique<WText>( job_info.get_node_list()) ); 

#if 1
    auto cancel_button = table->elementAt( line_ctr, column_ctr++ )
      ->addWidget( make_unique<WPushButton>( "-" ) ); 

    cancel_button->clicked().connect(
      [=](){
        make_confirm_dialog(
          this,
          [=]() {
            jobs_info->cancel_job(job_info);
          },
          "do you really want to cancel the job?"
          );
      }
    );
#endif

    line_ctr++;
  }

}















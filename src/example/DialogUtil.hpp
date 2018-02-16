

#pragma once
#include <Wt/WDialog.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WSuggestionPopup.h>
#include <Wt/WPushButton.h>

#include <memory>

inline void make_ok_cancel_dialog(Wt::WDialog* dialog, std::string content)
{
  dialog->contents()->addWidget( std::make_unique<Wt::WText>(content) );

  auto ok = dialog->contents()->addWidget( std::make_unique<Wt::WPushButton>("ok") );
  ok->clicked().connect(
    [=](){
      dialog->accept();
    }
  );
  auto cancel = dialog->contents()->addWidget( std::make_unique<Wt::WPushButton>("cancel") );
  cancel->clicked().connect(
    [=](){
      dialog->reject();
    }
  );

}

#if 0

inline auto add_suggestions(Wt::WLineEdit* le, Wt::WContainerWidget* container, std::set<std::string> autocomplete_list) {
  using namespace Wt;
  Wt::WSuggestionPopup::Options contactOptions;
  contactOptions.highlightBeginTag = "<span class=\"highlight\">";
  contactOptions.highlightEndTag = "</span>";
  contactOptions.listSeparator = ',';
  contactOptions.whitespace = " \\n";
  contactOptions.wordSeparators = "-., \"@\\n;";

  Wt::WSuggestionPopup *sp =
    container->addWidget(std::make_unique<Wt::WSuggestionPopup>(
            Wt::WSuggestionPopup::generateMatcherJS(contactOptions),
            Wt::WSuggestionPopup::generateReplacerJS(contactOptions)));

  sp->forEdit(le);

  for( auto& element : autocomplete_list ){
    sp->addSuggestion(element);
  }
  
}
#endif

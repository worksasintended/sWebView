#include <Wt/WApplication.h>
#include <Wt/WServer.h>

using namespace Wt;
using namespace std;

class RootApplication : public Wt::WApplication{
  public: 
    RootApplication(const Wt::WEnvironment& env) : Wt::WApplication(env){
      auto bootstrapTheme = make_shared<Wt::WBootstrapTheme>();
      bootstrapTheme->setVersion(Wt::BootstrapVersion::v3);
      bootstrapTheme->setResponsive(true);
      setTheme(bootstrapTheme);
      useStyleSheet("resources/themes/bootstrap/3/bootstrap-theme.min.css");
      auto layout = root()->setLayout(make_unique<WBorderLayout>());
      auto container = layout->addWidget( make_unique<WContainerWidget>(), Wt::LayoutPosition::North );
      auto image = container->addWidget( make_unique<Wt::WImage>(Wt::WLink("banner.png")) );
    }

}

std::unique_ptr<WApplication> createApplication(const Wt::WEnvironment& env){
  return make_unique<RootApplication>(env);
}

int main(int argc, char **argv){
  try {
    Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);
    server.addEntryPoint(Wt::EntryPointType::Application, createApplication);

    server.run();
  } catch (Wt::WServer::Exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cerr << "exception: " << e.what() << std::endl;
  }
}


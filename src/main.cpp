#include <Wt/WApplication.h>
#include <Wt/WServer.h>

using namespace Wt;
using namespace std;


std::unique_ptr<WApplication> createApplication(const Wt::WEnvironment& env){
  return make_unique<InfoApplication>(env);
}

int main(int argc, char **argv){
  try {
    Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);
    server.addEntryPoint(Wt::EntryPointType::Application, createApplication);

//    Session::configureAuth();

    server.run();
  } catch (Wt::WServer::Exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cerr << "exception: " << e.what() << std::endl;
  }
}


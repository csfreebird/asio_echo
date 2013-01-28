#include <iostream>
#include "core/server.h"
#include "business/client.h"
#include <booster/log.h>
#include <booster/shared_ptr.h>
#include <boost/filesystem.hpp>
#include "util/config_error.h"
#include "util/config.h"
#include "util/my_app.h"

using namespace std;

void LoadConfig(string const& xml_path) {
  boost::filesystem::path config_file(xml_path);
  if (!boost::filesystem::exists(config_file)) {
    cout << "The configuration file path specified by paramerter doens't exit, file path:" << xml_path << endl;
    throw ConfigError("The configuration file path specified by paramerter doens't exit,file path:" + xml_path);
  }

  Configuration* config = new Configuration(xml_path);
  MyApp& app = AppHolder::Instance();
  app.set_config(config);
}

void InitLog() {
  booster::shared_ptr<booster::log::sinks::file> f(new booster::log::sinks::file());
  f->append();
  f->max_files(10);
  MyApp& app = AppHolder::Instance();
  Configuration & config = app.config();
  f->open(config.log_folder + "echo.log");
  booster::log::logger::instance().add_sink(f);
  booster::log::logger::instance().set_default_level(booster::log::debug);
}

int main(int argc, char ** argv) {
  try {
    //check argument
    string xml_path;
    if (argc != 2) {
      BOOSTER_ERROR("main") << "The 1st parameter doesn't exist, data_service is using the default value \"config.xml\" as the first parameter now";
      xml_path = "config.xml";
    } else {
      xml_path = argv[1];
    }

    LoadConfig(xml_path);

    InitLog();
    BOOSTER_INFO("main") << "thread id: " << this_thread::get_id() << " Initialization succeeded";
    io_service iosev;
    tcp::endpoint listen_endpoint(tcp::v4(), AppHolder::Instance().config().listen_port);
    Server<Client> server(iosev, listen_endpoint, 10);
    server.Run();
  } catch(std::exception const& ex) {
    BOOSTER_ERROR("main") << "thread id: " << this_thread::get_id() << " Caught an exception: " << ex.what();
  }
}

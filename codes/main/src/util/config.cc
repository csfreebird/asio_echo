#include "util/config.h"
#include "boost/property_tree/ptree_fwd.hpp"
#include "boost/property_tree/xml_parser.hpp"

using namespace std;
using namespace boost;

Configuration::Configuration(string const& path) {
    property_tree::ptree pt;
    read_xml(path, pt);
    log_folder = pt.get<string>("service.log.folder_path");
    listen_port = pt.get<int>("service.socket.port_number");
    request_timeout = pt.get<int>("service.socket.wait_request_timeout");
}

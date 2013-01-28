#ifndef UTIL_MY_APP_H_
#define	UTIL_MY_APP_H_

#define LOKI_CLASS_LEVEL_THREADING

#include <string>
#include <memory>
#include "util/config.h"
#include "loki/Singleton.h"
#include "boost/thread/mutex.hpp"
//#include "bean/displays.h"
//#include "message/init_request.h"
#include <vector>

using namespace Loki;
using namespace std;

class MyApp {
 public:
  MyApp() {
  };

  ~MyApp() {
  };

  void set_config(Configuration* configuration) {
    config_.reset(configuration);
  }

  Configuration& config() const {
    return *config_;
  }

  boost::mutex& mutex() {
    return mutex_;
  }

  // Get the online displays
  /*
  Displays& OnlineDisplays() {
      return displays_;
  }
*/
  /*
  vector<char> const& init_request_data () const {
    return init_request_data_;
  }
  */

 private:
  MyApp(MyApp const&);
  MyApp& operator=(MyApp const&);

 private:
  auto_ptr<Configuration> config_;
  boost::mutex mutex_;
  //  Displays displays_;
  //vector<char> init_request_data_;
};

unsigned int GetLongevity(MyApp*);

template<class T>
class AppCreator: public Loki::CreateUsingNew<T> {
 public:
  static T* Create() {
    return new MyApp();
  }
};

typedef SingletonHolder<MyApp, AppCreator, SingletonWithLongevity, ClassLevelLockable, Mutex> AppHolder;


#endif

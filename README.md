asio_echo
=========

an echo-like server implemented by boost::asio, it's a good beginning for developing high performacing TCP app.

It dependens the following libraries:
1. loki
I modified it, add memory barrier of GCC. You could use the defualt codes of loki, it should be okay.
2. boost
3. booster library from cppcms, its log APIs are useful


usage:
1. cd codes/main
2. mkdir build
3. cd build
4. cmake ..
5. make
6. cd bin
7. execute './service ../../config.xml'


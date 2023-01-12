#include "factory_lib"
#include <iostream>

std::mutex PayOffFactory::myMutex{};
std::shared_ptr<PayOffFactory> PayOffFactory::instance{};

PayOffHelper<PayOffCall> registerCall("call");
PayOffHelper<PayOffPut> registerPut("put");

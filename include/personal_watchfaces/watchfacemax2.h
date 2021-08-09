#ifndef OSW_APP_WATCHFACE_MAX2_H
#define OSW_APP_WATCHFACE_MAX2_H

#include <osw_hal.h>
#include <osw_app.h>

class OswAppWatchfaceMax2 : public OswApp {
 public:
  OswAppWatchfaceMax2(void){};
  void setup(OswHal* hal);
  void loop(OswHal* hal);
  void stop(OswHal* hal);
  ~OswAppWatchfaceMax2(){};
 private:
};

#endif 
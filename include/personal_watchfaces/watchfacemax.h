#ifndef OSW_APP_WATCHFACE_MAX_H
#define OSW_APP_WATCHFACE_MAX_H

#include <osw_hal.h>
#include <osw_ui.h>

#include "osw_app.h"

class OswAppWatchfaceMax : public OswApp {
 public:
  OswAppWatchfaceMax(void){ ui = OswUI::getInstance();};
  void setup(OswHal* hal);
  void loop(OswHal* hal);
  void stop(OswHal* hal);
  ~OswAppWatchfaceMax(){};

 private:
   OswUI* ui;
};

#endif 
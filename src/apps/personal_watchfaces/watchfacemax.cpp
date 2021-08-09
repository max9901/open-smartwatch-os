#include "./personal_watchfaces/watchfacemax.h"
#include "./personal_watchfaces/fonts/Roboto_Condensed_Light_21.h"
#include "./personal_watchfaces/fonts/Roboto_Condensed_Light_75.h"

#include <string>

#include "gfx_util.h"
#include "config.h"
#include "osw_app.h"
#include "osw_hal.h"
#include "time.h"
#include "osw_ui.h"

#include <services/OswServiceTasks.h>
#include <services/OswServiceTaskWiFi.h>


using std::string;

const char * months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

#define COLOR_BLACK rgb565(0, 0, 0)

namespace max_watchface{

  void drawStepHistory(OswHal* hal, OswUI* ui, uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint32_t max) {
    uint32_t weekDay = 0;
    uint32_t dayOfMonth = 0;
    hal->getDate(&dayOfMonth, &weekDay);
    for (uint8_t i = 0; i < 7; i++) {
      uint16_t c = weekDay == i ? ui->getSuccessColor() : ui->getInfoColor();
      uint32_t s = hal->getStepsOnDay(i);
      uint16_t boxHeight = ((float)(s > max ? max : s) / max) * h;
      boxHeight = boxHeight < 2 ? 2 : boxHeight;

      // step bars
      hal->gfx()->fillFrame(x + i * w, y + (h - boxHeight), w, boxHeight, c);
      // bar frames
      uint16_t f = weekDay == i ? ui->getForegroundColor() : ui->getForegroundDimmedColor();
      hal->gfx()->drawRFrame(x + i * w, y, w, h, 2, f);

      // labels
      hal->gfx()->clearFont();
      hal->gfx()->setTextCenterAligned();  // horiz.
      hal->gfx()->setTextBottomAligned();
      hal->gfx()->setTextSize(1);
      hal->gfx()->setTextCursor(DISP_W / 2, y - 1);
      hal->gfx()->print(hal->getStepsToday());
      hal->gfx()->setTextCursor(DISP_W / 2, y + 1 + 8 + w * 4);
      hal->gfx()->print(hal->getStepsTotal());
    }
  }


  void print_time(OswHal* hal){

    //fix timing
    uint32_t second = 0;
    uint32_t minute = 0;
    uint32_t hour   = 0;

    hal->getLocalTime(&hour, &minute, &second);

    // Serial.printf("%d : %d : %d \n",hour,minute,second);
    hal->gfx()->setFont(&Roboto_Condensed_Light_75);
    hal->gfx()->setTextMiddleAligned();
    hal->gfx()->setTextColor(rgb565(200,200,225),0);

    hal->gfx()->setTextCenterAligned();
    hal->gfx()->setTextCursor(hal->gfx()->getWidth()/2, hal->gfx()->getHeight()/2-15);
  
    if(minute > 9){
      hal->gfx()->printf("%d %d",hour,minute);
    }else{
      hal->gfx()->printf("%d 0%d",hour,minute);
    }

  }
  void print_date(OswHal* hal){
    uint32_t dayInt = 0;
    uint32_t monthInt = 0;
    uint32_t yearInt = 0;
    hal->getDate(&dayInt, &monthInt, &yearInt);
    hal->gfx()->setFont(&Roboto_Condensed_Light_21);
    hal->gfx()->setTextCenterAligned();
    hal->gfx()->setTextColor(rgb565(200,200,225),0);
    hal->gfx()->setTextCursor(hal->gfx()->getWidth()/2 ,(hal->gfx()->getHeight()/2)+25);
    hal->gfx()->printf("%d %s",dayInt,months[monthInt-1]);
  }                     
  void draw_battery_round(OswHal* hal){

    uint16_t batproc = hal->getBatteryPercent();
    uint16_t bat = (uint16_t)((float)batproc * 3.6) - 1;

    hal->gfx()->drawArc(120, 120, 0,         360, 180, 116, 3, rgb565(25, 25, 40));
    hal->gfx()->drawArc(120, 120, 0, bat   % 360, 180, 116, 3, rgb565(75, 75, 100));

  }
  void draw_steps_round(OswHal* hal){
    uint32_t steps = ((float)hal->getStepsToday()/1000)*36;
    hal->gfx()->drawArc(120, 120, 0,           360, 180, 107, 3, rgb565(25, 40, 25));
    hal->gfx()->drawArc(120, 120, 0, steps   % 360, 180, 107, 3, rgb565(75, 100, 75));
  }

  void drawWiFi(OswHal* hal, uint16_t x, uint16_t y) {
    if (OswServiceAllTasks::wifi.isWiFiEnabled()) {
      for (uint8_t i = 0; i < OswServiceAllTasks::wifi.getSignalQuality() / 20; i++) {
        hal->getCanvas()->getGraphics2D()->fillFrame(x + 3 * i, y + 12 - i * 2, 2, i * 2,
                                                    OswUI::getInstance()->getForegroundColor());  // outer frame
      }
    }
  }

}

void OswAppWatchfaceMax::setup(OswHal* hal) {

    hal->gfx()->fill(0);
    
    max_watchface::print_time(hal);
    max_watchface::print_date(hal);
    max_watchface::draw_battery_round(hal);
    max_watchface::draw_steps_round(hal);

#ifdef FEATURE_STATS_STEPS
    uint8_t w = 8;
    max_watchface::drawStepHistory(hal, ui, (DISP_W / 2) - w * 3.5, 171, w, w * 4, OswConfigAllKeys::stepsPerDay.get());
#endif

    hal->requestFlush();
}


void OswAppWatchfaceMax::loop(OswHal* hal) {
    if (hal->btnHasGoneDown(BUTTON_3)) {
      // OswServiceAllTasks::wifi.postRequestHAtest();
    }

    max_watchface::print_time(hal);
    max_watchface::print_date(hal);
    max_watchface::draw_steps_round(hal);
    max_watchface::drawWiFi(hal, hal->gfx()->getWidth()/ 2, 20);
    hal->requestFlush();
}

void OswAppWatchfaceMax::stop(OswHal* hal) {
  hal->gfx()->clearFont();
}
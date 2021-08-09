#include "./personal_watchfaces/watchfacemax2.h"
#include "./personal_watchfaces/fonts/roboto_black_79.h"

#include <gfx_util.h>
#include <time.h>
#include <string>

using std::string;


#define COLOR_BLACK rgb565(0, 0, 0)

namespace max_watchface2{

 void print_time(OswHal* hal){
    //fix timing
    uint32_t second = 0;
    uint32_t minute = 0;
    uint32_t hour   = 0;

    hal->getLocalTime(&hour, &minute, &second);

    hal->gfx()->setTextCursor( hal->gfx()->getWidth()/4*2 -24  , hal->gfx()->getHeight()/4+3);
    hal->gfx()->print(1);
    hal->gfx()->setTextCursor( hal->gfx()->getWidth()/4*2 +14  , hal->gfx()->getHeight()/4+3);
    hal->gfx()->print(2);
    hal->gfx()->setTextCursor( hal->gfx()->getWidth()/4*1 +18, hal->gfx()->getHeight()/4*2 + 8);
    hal->gfx()->print(9);
    hal->gfx()->setTextCursor( hal->gfx()->getWidth()/4*3 -18 , hal->gfx()->getHeight()/4*2 + 8);
    hal->gfx()->print(3);
    hal->gfx()->setTextCursor( hal->gfx()->getWidth()/4*2     , hal->gfx()->getHeight()/4*3-7);
    hal->gfx()->print(6);

    hal->gfx()->drawCircle(120, 120, 2, rgb565(255, 255, 255));

    // hours
    hal->gfx()->drawTick(120, 120, 0, 16, 360.0 / 12.0 * (1.0 * hour + minute / 60.0), rgb565(255, 255, 255));
    hal->gfx()->drawThickTick(120, 120, 16, 60, 360.0 / 12.0 * (1.0 * hour + minute / 60.0), 3, rgb565(255, 255, 255));
    hal->gfx()->drawThickTick(120, 120, 16, 60, 360.0 / 12.0 * (1.0 * hour + minute / 60.0), 2, rgb565(0, 0, 0));


    // minutes
    hal->gfx()->drawTick(120, 120, 0, 16, 360.0 / 60.0 * (1.0 * minute + second / 60.0), rgb565(255, 255, 255));
    hal->gfx()->drawThickTick(120, 120, 16, 80, 360.0 / 60.0 * (1.0 * minute + second / 60.0), 3, rgb565(255, 255, 255));
    hal->gfx()->drawThickTick(120, 120, 16, 80, 360.0 / 60.0 * (1.0 * minute + second / 60.0), 2, rgb565(0, 0, 0));


    // seconds
    hal->gfx()->fillCircle(120, 120, 1, rgb565(255, 0, 0));
    hal->gfx()->drawTick(120, 120, 0, 16, 360.0 / 60.0 * second-180,  rgb565(255, 0, 0));
    hal->gfx()->drawTick(120, 120, 0, 16, 360.0 / 60.0 * second,  rgb565(255, 0, 0));
    hal->gfx()->drawTick(120, 120, 0, 65, 360.0 / 60.0 * second, rgb565(255, 0, 0));
  }
}

void OswAppWatchfaceMax2::setup(OswHal* hal) {
    hal->gfx()->fill(0);
    hal->gfx()->setFont(&Roboto_Black_79);
    hal->gfx()->setTextColor(rgb565(255,255,255),rgb565(255,255,255));
    hal->gfx()->setTextMiddleAligned();
    hal->gfx()->setTextCenterAligned();
    max_watchface2::print_time(hal);
    hal->requestFlush();
}

void OswAppWatchfaceMax2::loop(OswHal* hal) {
 
}

void OswAppWatchfaceMax2::stop(OswHal* hal) {
  hal->gfx()->clearFont();
}
#include "overlay/gui.hpp"

namespace edz::ovl {

    static lv_coord_t last_x = 0;
    static lv_coord_t last_y = 0;

    Gui::Gui(Screen *screen) {
        Gui::s_screen = screen;

        last_x = 0;
        last_y = 0;

        Gui::s_screen->clear();

        Gui::s_introAnimationPlaying = true;
        Gui::s_outroAnimationPlaying = false;
        Gui::s_guiOpacity = 0.0F;
    }

    Gui::~Gui() {

    }

    void Gui::initialize() {
        static lv_color_t buf[LV_HOR_RES_MAX * LV_VER_RES_MAX][2];

        lv_disp_drv_init(&Gui::s_displayDriver);
        lv_disp_buf_init(&Gui::s_displayBuffer, buf[0], buf[1], LV_HOR_RES_MAX * LV_VER_RES_MAX);
        Gui::s_displayDriver.flush_cb = Gui::lvglDisplayFlush;
        Gui::s_displayDriver.buffer = &Gui::s_displayBuffer;
        Gui::s_displayDriver.hor_res = LV_HOR_RES_MAX;
        Gui::s_displayDriver.ver_res = LV_VER_RES_MAX;
        lv_disp_drv_register(&Gui::s_displayDriver);

        lv_indev_drv_init(&Gui::s_inputDevice);
        Gui::s_inputDevice.type = LV_INDEV_TYPE_POINTER;
        Gui::s_inputDevice.read_cb = Gui::lvglTouchRead;
        lv_indev_drv_register(&Gui::s_inputDevice);
    }

    bool Gui::shouldClose() {
        return Gui::s_guiOpacity <= 0.0 && !Gui::s_introAnimationPlaying;
    }


    void Gui::lvglDisplayFlush(lv_disp_drv_t *displayDriver, const lv_area_t *area, lv_color_t *color) {
        
        for(u16 y = area->y1; y <= area->y2; y++) {
            for(u16 x = area->x1; x <= area->x2; x++) {
                if (color->ch.alpha > 0)
                    Gui::s_screen->setPixel(x, y, edz::ovl::makeColor<edz::ovl::rgba4444_t>(color->ch.red >> 4, color->ch.green >> 4, color->ch.blue >> 4, (color->ch.alpha >> 4) * Gui::s_guiOpacity));
                else
                    Gui::s_screen->setPixel(x, y, Gui::s_screen->getPixel(x, y));
                color++;
            }
        }
        
        Gui::s_screen->flush();

        lv_disp_flush_ready(displayDriver);
    }

    bool Gui::lvglTouchRead(_lv_indev_drv_t * indev, lv_indev_data_t * data) {
        /*Save the state and save the pressed coordinate*/
        data->state = (hidKeysHeld(CONTROLLER_P1_AUTO) & KEY_TOUCH) ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL; 
        if(data->state == LV_INDEV_STATE_PR) {
            touchPosition pos;
            hidTouchRead(&pos, 0);
            last_x = ((pos.px) * 1280) / 1920;
            last_y = ((pos.py) * LV_VER_RES_MAX) / TS_HEIGHT;
        }
    
        /*Set the coordinates (if released use the last pressed coordinates)*/
        data->point.x = last_x;
        data->point.y = last_y;

        if (last_x > 256)
            Gui::s_outroAnimationPlaying = true;

        return false; /*Return `false` because we are not buffering and no more data to read*/
    }

}
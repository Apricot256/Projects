#include "../include/define.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int InputX, InputY;
    SetMainWindowText(PROGRAM_NAME);
    SetGraphMode(SCREEN_WIDTH, SCREEN_HIGH, SCREEN_COLOR);
    ChangeWindowMode(TRUE); 
    if (DxLib_Init() == -1)  return -1;
    SetDrawScreen(DX_SCREEN_BACK);
    StartJoypadVibration(DX_INPUT_PAD1, 1000, 2000);
    bool re=true;
    while (re) {
        single *obj=new single;
        Fps fps;
        obj->road(filepath);
        while (obj->out == 0||(GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_13)) {
            if (ProcessMessage() == -1)break;
            // ƒpƒbƒh‚P‚Ì“ü—Í‚ðŽæ“¾
            GetJoypadAnalogInput(&InputX, &InputY, DX_INPUT_KEY_PAD1);
            fps.Update(&obj->fps);
            obj->move(InputX, InputY);
            obj->hit_fx();
            ClearDrawScreen();
            obj->draw(InputY);
            ScreenFlip();
            obj->escape();
            fps.Wait();
        }
        ClearDrawScreen();
        obj->cont(&re);
        delete obj;
    }
    DxLib_End();
    return 0;
}
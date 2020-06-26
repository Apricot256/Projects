#include "../include/define.h"

int t = 0;
bool b=false;

bool debug() {
	t++;
	if (CheckHitKey(KEY_INPUT_F3)&&t>=20) {
        if (b) b = false;
		else {
			b = true;
			t = 0;
		}
	}
    return b;
}
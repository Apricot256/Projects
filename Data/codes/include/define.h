#include <string>
#include <fstream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include "debug.h"
#include "Dxlib.h"
#include "map.h"
#include "filepath.h"
using namespace std;

#define PROGRAM_NAME "ゴールするんだよ。"
#define SCREEN_HIGH 720//プログラムの縦解像度(単位：pixel)
#define SCREEN_WIDTH  960//プログラムの横解像度(単位：pixel)
#define SCREEN_COLOR 32//プログラムの最大カラー(単位：bit)

#define FPS 60.0//プログラムのフレームレート(単位：FlamePerSecond)

#define MAP_CHIP_SIZE  50//マップチップのサイズ(単位：pixel)


#define WALK_FLAME 5		//切り替えるフレーム










//************************↓↓ここから下を変更してね。↓↓*********************************


#define PLAYER_START_X 100	//プレイヤーの初期X座標(単位：左からn pixel)
#define PLAYER_START_Y 150	//プレイヤーの初期Y座標(単位：上からn pixel)

#define PLAYER_DEFAULT_TALL 48		//プレイヤーの縦のあたり判定(単位：pixel)
#define PLAYER_DEFAULT_WIDTH 40		//プレイヤーの横の当たり判定(単位：pixel)

#define PLAYER_SPEED 555.00	//プレイヤーの移動速度((単位：倍率)
#define PLAYER_V0 555//プレイヤーのジャンプ力(単位：m/s)
#define PLAYER_WIGHT 50//プレイヤーの重さ(単位：kg)
#define GRAVITY 15.//重力加速度(m/s^s)

#define apex_xm	300		//スクロールを開始する範囲(単位：左右端からn pixel)

#define E_MOVE 1;		//敵の移動速度(単位：ブロック1つ分)
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

#define PROGRAM_NAME "�S�[������񂾂�B"
#define SCREEN_HIGH 720//�v���O�����̏c�𑜓x(�P�ʁFpixel)
#define SCREEN_WIDTH  960//�v���O�����̉��𑜓x(�P�ʁFpixel)
#define SCREEN_COLOR 32//�v���O�����̍ő�J���[(�P�ʁFbit)

#define FPS 60.0//�v���O�����̃t���[�����[�g(�P�ʁFFlamePerSecond)

#define MAP_CHIP_SIZE  50//�}�b�v�`�b�v�̃T�C�Y(�P�ʁFpixel)


#define WALK_FLAME 5		//�؂�ւ���t���[��










//************************�����������牺��ύX���ĂˁB����*********************************


#define PLAYER_START_X 100	//�v���C���[�̏���X���W(�P�ʁF������n pixel)
#define PLAYER_START_Y 150	//�v���C���[�̏���Y���W(�P�ʁF�ォ��n pixel)

#define PLAYER_DEFAULT_TALL 48		//�v���C���[�̏c�̂����蔻��(�P�ʁFpixel)
#define PLAYER_DEFAULT_WIDTH 40		//�v���C���[�̉��̓����蔻��(�P�ʁFpixel)

#define PLAYER_SPEED 555.00	//�v���C���[�̈ړ����x((�P�ʁF�{��)
#define PLAYER_V0 555//�v���C���[�̃W�����v��(�P�ʁFm/s)
#define PLAYER_WIGHT 50//�v���C���[�̏d��(�P�ʁFkg)
#define GRAVITY 15.//�d�͉����x(m/s^s)

#define apex_xm	300		//�X�N���[�����J�n����͈�(�P�ʁF���E�[����n pixel)

#define E_MOVE 1;		//�G�̈ړ����x(�P�ʁF�u���b�N1��)
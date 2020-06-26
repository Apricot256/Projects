#pragma once
#include "define.h"

class enemmy{
private:
	int i;
	bool active;		//�����t���O
	int Ex, Ey;
	int time;
	int defo;
	int count;
	bool direction;
public:
	int type;
	void Edraw(int apexx,int apexy,int *gr);
	void move(vector<vector<int>> &hit);
	void hit(int Px, int Py, int Px_old, int Py_old,bool* dead, vector<vector<int>>& hit,int sound, bool* jump,double* t1,double* t2);
	enemmy(int x, int y,int type);
	~enemmy();
};

class single {
private:
	bool dead;
	bool goal;
	int i;
	int d_time;		//���ɂ߁[�����̎���
	int mapchip_gr[8] = { NULL };	//�}�b�v�`�b�v�̃O���b�t�B�b�N�n���h��
	int player_gr[7] = { NULL };	//�v���C���[�̃O���b�t�B�b�N�n���h��
	int item_gr[2] = {NULL};
	int enemmy_gr[4];
	int sound[5] = { NULL };
	int back_gr;
	int player_point;
	int player_type,player_high, player_width;	//�v���C���[�̎�ށA����,����
	int Px, Py;	//�v���C���[�̍��W
	int Px_old, Py_old;		//�O�t���[���̃v���C���[�̍��W
	int apex_x, apex_y;		//�O���b�t�B�b�N�̕`�撸�_
	double jump_now , jump_old ;	//�v���C���[�̏�����̗́A�O�t���[���̃v���C���[�̏�����̗�
	double t1, t2;		//���R�������ԁA���������グ����
	bool jump_a=false, jump_g=false;	//�W�����v���t���O�A�n�ʂɑ������Ă��邩
	vector<enemmy> mob;		//�GMOB�f�[�^�̃x�N�g��
	vector<vector<int>> data;	//�}�b�v�f�[�^�i�[�p�x�N�g��
	vector<vector<int>> hit;	//�}�b�v�����蔻��i�[�p�x�N�g��
public:
	bool out;		//1:���S	2:�S�[��
	float fps;		//�|�C���^�n���p��Public�����o�ϐ�
	void road(const char* filepath);	//���[�h�֐�
	void draw(int input);		//�`��֐�
	void hit_fx();		//�A�C�e���ƓG�̓����蔻��֐�
	void delete_hit();
	void cont(bool *re);		//���s����
	void move(int inputX, int inputY);	//�ړ��֐�
	void escape();
	single();	//�R���X�g���N�^
	~single();		//�f�X�g���N�^
};
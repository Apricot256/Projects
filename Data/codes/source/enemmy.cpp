#include "../include/define.h"


void enemmy::move(vector<vector<int>> &hit) {
	i++;
	if (i == 20) {
		i = 0;
		time++;
	}
	if (active) {
		for (int i = 0; i < MAP_CHIP_SIZE; i++) {
			for (int k = 0; k < MAP_CHIP_SIZE; k++) {
				hit[i + Ey][k + Ex] = 0;
			}
		}
		if (this->direction) {
			Ex += E_MOVE;
			count+= E_MOVE;
			if (count / MAP_CHIP_SIZE >= abs(defo % 10)) {
				count = 0;
				direction = false;
			}
		}
		else {
			Ex -= E_MOVE;
			count += E_MOVE;
			if (count / MAP_CHIP_SIZE >= abs((defo/100)%10)) {
				count = 0;
				direction = true;
			}
		}
		for (int i = 0; i < MAP_CHIP_SIZE; i++) {
			for (int k = 0; k < MAP_CHIP_SIZE; k++) {
				hit[i + Ey][k + Ex] = defo;
			}
		}
	}
}

void enemmy::hit(int Px, int Py,int Px_old,int Py_old, bool* dead,vector<vector<int>>& hit,int sound, bool* jump,double* t1,double* t2) {
	if (active) {
		for (int i = Py; i < Py + MAP_CHIP_SIZE; i++) {
			for (int k = Px; k < Px + MAP_CHIP_SIZE; k++) {
				if (hit[i - (MAP_CHIP_SIZE)][k - (MAP_CHIP_SIZE / 2)] < -10000) {
					if (Py - Py_old > 0) {
						PlaySoundMem(sound, DX_PLAYTYPE_BACK);
						this->active = false;
						*jump = true; *t1 = 0; *t2 = 0;
						for (int y = Ey; y < Ey + MAP_CHIP_SIZE; y++) {
							for (int x = Ex; x < Ex + MAP_CHIP_SIZE; x++) {
								hit[y][x] = 0;
							}
						}
						break;
					}
					else {
						*dead = true;
					}
				}
			}
		}
	}
}

void enemmy::Edraw(int apexx, int apexy,int *gr){
	if (active) {
		if (this->defo/-10000==1) {
			if (time % 2 == 0) {
				DrawGraph(Ex + apexx, Ey + apexy, gr[0], TRUE);
			}
			else {
				DrawGraph(Ex + apexx, Ey + apexy, gr[1], TRUE);
			}
		}
		if (this->defo / -10000 == 2) {
			if (time % 2 == 0) {
				DrawGraph(Ex + apexx, Ey + apexy, gr[2], TRUE);
			}
			else {
				DrawGraph(Ex + apexx, Ey + apexy, gr[3], TRUE);
			}
		}
	}
}

enemmy::enemmy(int x, int y, int defo) {
	this->active = true;
	this->count = 0;
	this->Ex = x * MAP_CHIP_SIZE;
	this->Ey = y * MAP_CHIP_SIZE;
	this->defo = defo;
	this->type = (defo)/-10000;
	this->direction = true;		//ˆÚ“®•ûŒü‚ð‰EŒü‚«‚ÉÝ’è
	this->i = 0;
	this->time = 0;
}

enemmy::~enemmy() {
}
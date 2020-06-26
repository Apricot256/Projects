#pragma once
#include "define.h"

class enemmy{
private:
	int i;
	bool active;		//生存フラグ
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
	int d_time;		//あにめーしょんの時間
	int mapchip_gr[8] = { NULL };	//マップチップのグラッフィックハンドル
	int player_gr[7] = { NULL };	//プレイヤーのグラッフィックハンドル
	int item_gr[2] = {NULL};
	int enemmy_gr[4];
	int sound[5] = { NULL };
	int back_gr;
	int player_point;
	int player_type,player_high, player_width;	//プレイヤーの種類、高さ,横幅
	int Px, Py;	//プレイヤーの座標
	int Px_old, Py_old;		//前フレームのプレイヤーの座標
	int apex_x, apex_y;		//グラッフィックの描画頂点
	double jump_now , jump_old ;	//プレイヤーの上向きの力、前フレームのプレイヤーの上向きの力
	double t1, t2;		//自由落下時間、鉛直投げ上げ時間
	bool jump_a=false, jump_g=false;	//ジャンプ中フラグ、地面に足がついているか
	vector<enemmy> mob;		//敵MOBデータのベクトル
	vector<vector<int>> data;	//マップデータ格納用ベクトル
	vector<vector<int>> hit;	//マップ当たり判定格納用ベクトル
public:
	bool out;		//1:死亡	2:ゴール
	float fps;		//ポインタ渡し用のPublicメンバ変数
	void road(const char* filepath);	//ロード関数
	void draw(int input);		//描画関数
	void hit_fx();		//アイテムと敵の当たり判定関数
	void delete_hit();
	void cont(bool *re);		//続行処理
	void move(int inputX, int inputY);	//移動関数
	void escape();
	single();	//コンストラクタ
	~single();		//デストラクタ
};
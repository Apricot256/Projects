#include "../include/define.h"

//グラッフィックの描画及びデバッグ関数
void single::draw(int input) {
    DrawGraph(0, 0, back_gr, FALSE);
    for (unsigned int i = 0; i < this->data.size(); i++) {
        for (unsigned int k = 0; k < this->data[i].size(); k++) {
            if (apex_x + (k * MAP_CHIP_SIZE) >= 0 && apex_x + ((k + 1) * MAP_CHIP_SIZE) <= SCREEN_WIDTH + MAP_CHIP_SIZE && apex_y + (i * MAP_CHIP_SIZE) >= 0 && apex_y + ((i + 1) * MAP_CHIP_SIZE) <= SCREEN_HIGH + MAP_CHIP_SIZE) {
                if (this->data[i][k] > 0) {
                    DrawGraph(apex_x + (k * MAP_CHIP_SIZE), apex_y + (i * MAP_CHIP_SIZE), mapchip_gr[(this->data[i][k]) - 1], FALSE);
                }
                if (this->data[i][k] < 0 && this->data[i][k]>-10000) {
                    DrawGraph(apex_x + (k * MAP_CHIP_SIZE), apex_y + (i * MAP_CHIP_SIZE), item_gr[abs(data[i][k]+1)], TRUE);
                }
            }
        }
    }
    for (unsigned int i = 0; i < mob.size(); i++) {
        mob[i].Edraw(this->apex_x, this->apex_y, enemmy_gr);
    }

    if (jump_g && Px!=Px_old) {
        DrawGraph(this->Px + apex_x, Py + apex_y - player_high, player_gr[d_time], TRUE);
    }
    else {
        DrawGraph(this->Px + apex_x, Py + apex_y - player_high, player_gr[2], TRUE);
    }

    DrawFormatString(0, 0,GetColor(225, 225, 225) ,"%d", player_point);
    if (CheckHitKey(KEY_INPUT_F3)!=0) {            //各種変数値の出力
        for (unsigned int i = 0; i < this->data.size(); i++) {
            for (unsigned int k = 0; k < this->data[i].size(); k++) {
                DrawFormatString(apex_x + k * MAP_CHIP_SIZE, apex_y + i * MAP_CHIP_SIZE, GetColor(225, 0, 225), "%d", this->data[i][k]);
            }
        }
        DrawFormatString(0, 0, GetColor(225, 225, 225), "Px:%d Py:%d", int(this->Px), int(this->Py));
        DrawFormatString(0, 15, GetColor(225, 225, 225), "FPS:%1.f", this->fps);
        if (jump_g) {
            DrawFormatString(0, 30, GetColor(225, 225, 225), "Jumping:'False'");
        }
        else {
            DrawFormatString(0, 30, GetColor(225, 225, 225), "Jumping:'True'");
        }
        DrawFormatString(0, 45, GetColor(225, 225, 225), "Displacement.X:%1.f", -1 * (this->Px - this->Px_old));
        DrawFormatString(0, 60, GetColor(225, 225, 225), "Displacement.Y:%1.f", -1 * (this->Py - this->Py_old));
        DrawFormatString(0, 75, GetColor(225, 225, 225), "t1:%1.f", this->t1);
        DrawFormatString(0, 90, GetColor(225, 225, 225), "t2:%1.f", this->t2);
    }
}

//プレイヤーの移動処理
void single::move(int inputX, int inputY) {
    i++;
    if (i == FPS/12) {
        i = 0;
        d_time++;
    }
    if (d_time == 3)d_time = 0;
    //_old変数に前フレーム座標として移動前の座標を代入
    this->Px_old = this->Px;
    this->Py_old = this->Py;
    this->jump_old = ((PLAYER_V0 * t2) - ((GRAVITY * t2 * t2) / 2));

    //空中にいるかつ2,3ボタン押下でジャンプフラグを'True'
    if ((jump_g && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0) || (jump_g && (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4) != 0)) {
        if (hit[Py - player_high-2][Px]<=0 && hit[Py - player_high-2][Px + player_width-1]<=0) {
            PlaySoundMem(sound[2], DX_PLAYTYPE_BACK);
            this->jump_a = true;
            this->jump_g = false;
        }
    }

    //移動処理(X)
    if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0 || (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_3) != 0) {
        this->Px += int(2 * (PLAYER_SPEED * (inputX / (FPS * MAP_CHIP_SIZE))));//ダッシュ時
    }
    else {
        this->Px += int(PLAYER_SPEED * (inputX / (FPS * MAP_CHIP_SIZE)));
    }

    //境界との当たり判定処理(X)
    if (Px <= player_width) Px = player_width;
    if (Px >=hit[Py].size() - player_width)Px = hit[Py].size()- player_width;

     //マップとの当たり判定処理(X)
     //自分の座標のマップチップが当たり判定を有す場合判定がなくなるまで戻す
    if (hit[Py_old-1][Px+player_width - 1]>0|| hit[Py_old-player_high+1][Px + player_width - 1] > 0) {
        //相対距離が正の場合、右移動
        if (this->Px - this->Px_old > 0) {
            while (hit[Py_old - 1][Px + player_width - 1] > 0) {
                Px--;
            }
            while (hit[Py_old - player_high + 1][Px + player_width - 1] > 0) {
                Px--;
            }
        }
    }
    if (hit[Py_old-1][Px] || hit[Py_old - player_high + 1][Px ] > 0) {
        //相対距離が負の場合、左移動
        if (this->Px - this->Px_old < 0) {
            while (hit[Py_old- 1][Px] > 0) {
                Px++;
            }
            while (hit[Py_old - player_high + 1][Px] > 0) {
                Px++;
            }
        }
    }
    //移動処理(Y)
    //ジャンプしている場合の処理
    if (this->jump_a) {
        t2++;
        this->jump_now = ((PLAYER_V0 * t2) - ((GRAVITY * t2 * t2) / 2));
        //力の向きの合計が下向きの場合       
        if (((PLAYER_V0 * t2) - ((GRAVITY * t2 * t2) / 2)) <= 0) {
            jump_a = false;
            t1 = t2 / 2;
            t2 = 0;
        }
        //力の向きの合計が上向きの場合
        else {
            Py -= int((jump_now - jump_old) / FPS);//前フレームとの相対距離を加算
        }
    }
    else {      //ジャンプしていない場合の処理
        Py += int((GRAVITY * t1 * t1) / FPS / MAP_CHIP_SIZE);        //下向きの落下処理
        t1++;
    }

    //境界当たり判定処理(Y)
    if (Py - player_high - 2 <= 0) {
        this->jump_a = false;
        this->t2 = 0;
        Py = player_high+2;
    }
    if (Py >= double(this->data.size()) * MAP_CHIP_SIZE) {
        this->dead = true;
        this->jump_a = false;
        this->t2 = 0;
        Py = 0;
        Py = (this->data.size()) * MAP_CHIP_SIZE - 1;
    }


    //マップ当たり判定(Y)
    //自分の座標のマップチップが当たり判定を有す場合判定がなくなるまで戻す
    //相対距離が正の場合、下移動
    if (hit[Py - 1][Px]>0 || hit[Py - 1][Px + player_width - 1] > 0) {
        if (this->Py - this->Py_old > 0) {
            while (hit[Py - 1][Px + player_width - 1] > 0) {
                Py--;
            }
            while (hit[Py - 1][Px] > 0) {
                Py--;
            }
            this->t1 = 0;
            this->t2 = 0;
            this->jump_a = false;
            this->jump_g = true;
        }
    }
    //相対距離が負の場合、上移動
    if (hit[Py - player_high-1][Px] > 0 || hit[Py - player_high - 1][Px + player_width - 1] > 0) {
        if (this->Py - this->Py_old < 0) {
            while (hit[Py - player_high -1][Px] > 0) {
                Py++;
            }
            while (hit[Py - player_high -1][Px + player_width - 1] > 0) {
                Py++;
            }
            t1 = t2 / 2;
            this->jump_a = false;
        }
    }
    for (int i = 0; i < mob.size();i++) {
        mob[i].move(this->hit);
    }
    //描画頂点の移動処理-
    if (Px + apex_x > SCREEN_WIDTH - (apex_xm) && (this->data[Py / MAP_CHIP_SIZE].size() * MAP_CHIP_SIZE) + apex_x > SCREEN_WIDTH)apex_x -= abs(int(Px - Px_old));
    if (Px + apex_x < (apex_xm) && Px > (apex_xm))apex_x += abs(int(Px - Px_old));

}

void single::hit_fx() {
    //オブジェクト当たり判定
    switch (abs(hit[Py - (MAP_CHIP_SIZE / 2)][Px + (MAP_CHIP_SIZE / 2)])) {
    case 1:     //コインと接触
        this->player_point += 100;
        PlaySoundMem(sound[0], DX_PLAYTYPE_BACK);
        delete_hit();
        break;
    case 2:
        this->goal = true;
        break;
    }
    for (int i = 0; i < mob.size(); i++) {
        mob[i].hit(Px,Py,Px_old, Py_old,&dead,hit, sound[1],&jump_a,&t1,&t2);
    }
}

void single::delete_hit() {
    int xs = (Px + (MAP_CHIP_SIZE / 2)) / MAP_CHIP_SIZE, ys = (Py - (MAP_CHIP_SIZE / 2)) / MAP_CHIP_SIZE;
    for (int i = 0; i < MAP_CHIP_SIZE; i++) {
        for (int k = 0; k < MAP_CHIP_SIZE; k++) {
            hit[k + (ys * MAP_CHIP_SIZE)][i + (xs * MAP_CHIP_SIZE)] = 0;
        }
    }
    data[ys][xs] = 0;
}

void single::escape() {
    if (dead) this->out = 2;
    if (goal) this->out = 1;
}

void single::cont(bool* re) {
    if (dead) {
        PlaySoundMem(sound[3], DX_PLAYTYPE_BACK);
        DrawString(360, 360, "死んじまった！！", GetColor(225, 225, 225));
        DrawString(360, 380, "B", GetColor(225, 0, 0));
        DrawString(375, 380, "：もう一度", GetColor(225, 225, 225));
        DrawString(360, 395, "A", GetColor(0, 225, 0));
        DrawString(375, 395, "：やめる", GetColor(225, 225, 225));
    }
    if (goal) {
        PlaySoundMem(sound[4], DX_PLAYTYPE_BACK);
        DrawString(360, 360, "クリア！！", GetColor(225, 225, 225));
        DrawString(360, 380, "B", GetColor(225, 0, 0));
        DrawString(375, 380, "：もう一度", GetColor(225, 225, 225));
        DrawString(360, 395, "A", GetColor(0, 225, 0));
        DrawString(375, 395, "：やめる", GetColor(225, 225, 225));
    }
    ScreenFlip();
    while (1) {
        if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) != 0) {
            *re = true;
            break;
        }
        if ((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1) != 0) {
            *re = false;
            break;
        }
    }
}

//マップデータの読み込み
void single::road(const char* filepath) {
    ifstream stream(filepath);
    string line;
    vector<int> temp;
    vector<int> temp2;
    const string delim = ",";
    int row = 0;
    int col;
    while (getline(stream, line)) {
        col = 0;
        for (string::size_type spos, epos = 0;
            (spos = line.find_first_not_of(delim, epos)) != string::npos;) {
            string token = line.substr(spos, (epos = line.find_first_of(delim, spos)) - spos);
            temp.emplace_back(stoi(token));
            for (int i = 0; i < MAP_CHIP_SIZE; i++) {
                temp2.emplace_back(stoi(token));
            }
            if (abs(stoi(token)) > 10000) {
                this->mob.push_back(enemmy(col, row, stoi(token)));
            }
            col++;
        }
        this->data.push_back(temp);
        this->hit.push_back(temp2);
        for (int i = 0; i < MAP_CHIP_SIZE - 1; i++) {
            this->hit.push_back(temp2);
        }
        temp.clear();
        temp2.clear();
        row++;
    }
}

//コンストラクタ(グラッフィクの読み込み＆各変数の初期化)
single::single() {
    this->out = 0;
    this->dead = false;
    this->goal = false;
    this->Px_old = PLAYER_START_X;
    this->Py_old = PLAYER_START_Y;
    this->Px = PLAYER_START_X;
    this->Py = PLAYER_START_Y;
    this->apex_x = 0;
    this->apex_y = 0;
    this->jump_now = 0;
    this->jump_old = 0;
    this->i = 0;
    this->t1 = 0;
    this->t2 = 0;
    this->player_type = 0;
    this->player_point = 0;
    this->d_time = 0;
    this->player_high = PLAYER_DEFAULT_TALL;
    this->player_width= PLAYER_DEFAULT_WIDTH;
    this->fps = FPS;
    this->back_gr = LoadGraph(back_gr_data[0]);
    for (int i = 0; i < 8; i++) {
        this->mapchip_gr[i] = LoadGraph(mapchip_gr_data[i]);
    }
    for (int i = 0; i < 3; i++) {
        this->player_gr[i] = LoadGraph(player_gr_data[i]);
    }
    for (int i = 0; i < 2; i++) {
        this->item_gr[i] = LoadGraph(items_gr_data[i]);
    }
    for (int i = 0; i < 4; i++) {
        this->enemmy_gr[i] = LoadGraph(enemy_gr_data[i]);
    }
    for (int i = 0; i < 5; i++) {
        this->sound[i] = LoadSoundMem(sounds_data[i]);
    }
}

//デストラクタ(動的確保したメモリの開放)
single::~single() {
    for (int i = 0; i < 8; i++) {
        DeleteGraph(this->mapchip_gr[i]);
    }
    for (int i = 0; i < 3; i++) {
        DeleteGraph(this->player_gr[i]);
    }
    for (int i = 0; i < 2; i++) {
        DeleteGraph(this->item_gr[i]);
    }
    for (int i = 0; i < 4; i++) {
        DeleteGraph(this->enemmy_gr[i]);
    }
    for (int i = 0; i < 2; i++) {
        DeleteGraph(this->sound[i]);
    }
    this->data.clear();
    this->hit.clear();
    this->mob.clear();
}
#pragma once
#include"Dxlib.h"
#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<sstream>
#include<string>
#include<set>
#include<array>
#define WIN_WIDTH 200
#define WIN_HEIGHT 480
#define FIELD_WIDTH_BLOCK 10//フィールド上の横のブロック数
#define FIELD_HEIGHT_BLOCK 15//フィールド上の縦のブロック数
#define BLOCK_SIZE 20//ブロックの一辺の大きさ
const int FIELD_WIDTH=FIELD_WIDTH_BLOCK*BLOCK_SIZE;
const int FIELD_HEIGHT=FIELD_HEIGHT_BLOCK*BLOCK_SIZE;
const int FIELD_X_COOR=WIN_WIDTH/2-FIELD_WIDTH/2;
const int FIELD_Y_COOR=50;
#define FIELD_GAUGE_SPACE 10
#define GAUGE_SIZE 25
#define GAUGE_SCORE_SPACE 10//ゲージとスコアなどの文字列の間隔
#define SCORE_SPACE 20 //スコアなどの文字同士の間隔

#define LINE_BREAKING_TIME 16 //ライン消去中の光が消えるまでの時間
#define FIRST_SECOND_MOVE_INTERVAL 15//押し続けた時に最初の移動と2回目の間のフレーム
#define MOVE_INTERVAL 3//上下左右移動キーを押しっぱなしにしたときにこの値フレームごとに移動

#define WAITING_TETRO_NUM 3//3で固定
#define BACKGROUND_WAITING_NUM 70//7の倍数にする

#define NONE_COLOR_FACT 64//NONEの色の各要素の値

#define FIELD_SQUARE_SIZE 5//5で固定


const int NONE_COLOR=GetColor(NONE_COLOR_FACT,NONE_COLOR_FACT,NONE_COLOR_FACT);//black
const int I_SHAPE_COLOR=GetColor(255,0,0);//red
const int J_SHAPE_COLOR=GetColor(0,0,255);//blue
const int L_SHAPE_COLOR=GetColor(255,128,0);//orange
const int O_SHAPE_COLOR=GetColor(255,255,0);//yellow
const int S_SHAPE_COLOR=GetColor(255,0,255);//pink
const int T_SHAPE_COLOR=GetColor(0,255,255);//water
const int Z_SHAPE_COLOR=GetColor(0,255,0);//green
const int FALLPOINT_NONE_COLOR=GetColor(NONE_COLOR_FACT,NONE_COLOR_FACT,NONE_COLOR_FACT);//black
const int FALLPOINT_I_SHAPE_COLOR=GetColor(128,0,0);//red
const int FALLPOINT_J_SHAPE_COLOR=GetColor(0,0,128);//blue
const int FALLPOINT_L_SHAPE_COLOR=GetColor(128,64,0);//orange
const int FALLPOINT_O_SHAPE_COLOR=GetColor(128,128,0);//yellow
const int FALLPOINT_S_SHAPE_COLOR=GetColor(128,0,128);//pink
const int FALLPOINT_T_SHAPE_COLOR=GetColor(0,128,128);//water
const int FALLPOINT_Z_SHAPE_COLOR=GetColor(0,128,0);//green
const int TouchingGaugeColor=GetColor(128,128,0);
const int WaitingGaugeColor=GetColor(128,0,0);

const int LEVORO_KEY=KEY_INPUT_Z;//反時計回り
const int CLOCK_KEY=KEY_INPUT_X;//時計回り
const int UP_KEY=KEY_INPUT_UP;
const int RIGHT_KEY=KEY_INPUT_RIGHT;
const int DOWN_KEY=KEY_INPUT_DOWN;
const int LEFT_KEY=KEY_INPUT_LEFT;
const int SOFT_DROP_KEY=KEY_INPUT_DOWN;
const int HARD_DROP_KEY=KEY_INPUT_SPACE;
const int MIDDLE_DROP_KEY=KEY_INPUT_UP;
const int HOLD_KEY=KEY_INPUT_LSHIFT;
const int SNAP_KEY=KEY_INPUT_S;
const int PAUSE_KEY=KEY_INPUT_ESCAPE;
const int DEC_KEY=KEY_INPUT_Z;

char KeyInputBuf[256];

enum Tetro_Shape{EMPTY,I_SHAPE,J_SHAPE,L_SHAPE,O_SHAPE,S_SHAPE,T_SHAPE,Z_SHAPE};
enum Block_Color{NONE,I_COLOR,J_COLOR,L_COLOR,O_COLOR,S_COLOR,T_COLOR,Z_COLOR,WALL};
enum Direction{UP,RIGHT,DOWN,LEFT};
enum FieldStatus{EXCEP=-1,WAITING,FALLING,TOUCHING,BREAKING,PAUSING};
enum KeyInput{HARD_DROP_IN,MIDDLE_DROP_IN,SOFT_DROP_IN,LEVORO_IN,CLOCK_IN,RIGHT_IN,LEFT_IN,HOLD_IN,NONE_IN};
struct Coordinate{
	int x;
	int y;
};
Coordinate GetCoordinate(int x,int y){
	Coordinate TempCoor;
	TempCoor.x=x;
	TempCoor.y=y;
	return TempCoor;
}
bool operator==(Coordinate& coor1,Coordinate& coor2){
		 if(coor1.x==coor2.x&&coor1.y==coor2.y) return true;
		 else return false;
}
bool operator<(Coordinate coor1,Coordinate coor2){
		 if(coor1.x<coor2.x) return true;
		 else return false;
}
bool operator>(Coordinate coor1,Coordinate coor2){
		 if(coor1.x>coor2.x) return true;
		 else return false;
}
int imod(int a, int b){
	if(a>0){
		return (a-b*int(a/b));
	}else if(a<=0){
		if(a%b==0)return 0;
		else return(a-b*(int(a/b)-1));
	}
}
int quot(int a,int b){
	return (a-a%b)/b;
}
int GetLeastMostNum(int a,int b,int c,int d,bool IsGetMost){
	 std::vector<int> nums((a,b,c,d));
	 std::sort(nums.begin(),nums.end());
	 if(IsGetMost)return nums[3];
	 else return nums[0];
}
int GetLeastMostNum(int* array,bool IsGetMost){
	 std::vector<int> nums;
	 for(int d=0;d<sizeof(array)/4;d++){
		nums.push_back(array[d]);  
	 }
	 std::sort(nums.begin(),nums.end());
	 if(IsGetMost)return nums[3];
	 else return nums[0];
}
std::string IntToString(int number)
{
  std::stringstream ss;
  ss << number;
  return ss.str();
}
bool IsOdd(int d){
	 if(d%2==0)return false;
	 else return true;
}
bool IsEven(int d){
	 return !IsOdd(d);
}
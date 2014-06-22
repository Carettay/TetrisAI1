#pragma once
#include"classes.h"
//#include"AItestclasses.h"
#include"definitions.h"
struct FallAttempt{
	 //Field& CurrentField;
	 int TempTetroRiang;
	 Coordinate BlockTempCoor[4];
	 Coordinate TetroAxisCoor;
	 int Score;
	 FallAttempt(/*Field& currentfield*/);
	 bool IsUsed;
};
FallAttempt::FallAttempt(){
		  //CurrentField=currentfield;
		  Score=0;
}

void CalcUnderBlockNoneScore(Field& field,FallAttempt& fallattempt);
void CalcThreeHeightWallScore(Field& field,FallAttempt& fallattempt);
void CalcNearBlockScore(Field& field,FallAttempt& fallattempt);
void CalcDeleteLineScore(Field& field,FallAttempt& fallattempt);
void CalcHighCooryScore(Field& field,FallAttempt& fallattempt);
void CalcHighestCooryScore(Field& field,FallAttempt& fallattempt);
bool IsAbleToMoveAttempt(Field& field,FallAttempt& fallattempt);//FallGが十分に小さい場合のみ使用可能

void AIforField(Field& field,char* keybuf,int RandSeed){
	 //static FallAttempt fallattempt[4][FIELD_WIDTH_BLOCK];//[riang][場所]
	 std::vector<FallAttempt> fallattempt[4];
	 FallAttempt TempFallAttempt;
	 static std::vector<KeyInput> KeyInputPlan;
	 std::vector<FallAttempt> BestAttempt;
	 //static Tetro_Shape PrevTetroShape=EMPTY;
	 static bool IsNextTetro=true;//true→新しいテトロミノになった
	 static bool IsKeyInputPlanPrepared=false;
	 static int keyInputPlanPosition=0;
	 bool IsAICalced=false;
	 Field_Square TestingSq(&field,-1,-1);
	 
	 static int AICalledCounter=0;
	 std::string LogFileName;

	 int UnderBlockNoneNum=0;

	 if(field.GetCurrentTetroShape()!=NULL&&IsNextTetro){
		  //TempFallAttempt.CurrentField=field;
		  AICalledCounter++;
		  /*FILE* LogFP;
		  LogFileName="AIlog/AIlog"+IntToString(AICalledCounter);
		  LogFileName+=".txt";
		  fopen_s(&LogFP,LogFileName.c_str(),"w");*/
		  switch (field.GetCurrentTetroShape()){
				break;case I_SHAPE:{
					 int b=0;
					 TempFallAttempt.TempTetroRiang=0;
					 while(b<FIELD_WIDTH_BLOCK-3){//riang=0
						  TempFallAttempt.BlockTempCoor[0].x=b;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b+1;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[2].x=b+2;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[3].x=b+3;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.TetroAxisCoor=TempFallAttempt.BlockTempCoor[2];
						  fallattempt[0].push_back(TempFallAttempt);
						  b++;
					 }

					 b=0;
					 TempFallAttempt.TempTetroRiang=1;
					 while(b<FIELD_WIDTH_BLOCK){//riang=1
						  TempFallAttempt.BlockTempCoor[0].x=b;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[2].x=b;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-3;
						  TempFallAttempt.BlockTempCoor[3].x=b;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-4;
						  TempFallAttempt.TetroAxisCoor=TempFallAttempt.BlockTempCoor[1];
						  fallattempt[1].push_back(TempFallAttempt);
						  b++;
					 }
				}break;case J_SHAPE:{
					 int b=0;
					 TempFallAttempt.TempTetroRiang=0;
					 while(b<FIELD_WIDTH_BLOCK-2){//riang=0
						  TempFallAttempt.BlockTempCoor[0].x=b;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b+1;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[2].x=b+2;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[3].x=b+2;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.TetroAxisCoor=TempFallAttempt.BlockTempCoor[1];
						  fallattempt[0].push_back(TempFallAttempt);
						  b++;
					 }

					 
					 b=0;
					 TempFallAttempt.TempTetroRiang=1;
					 while(b<FIELD_WIDTH_BLOCK-1){//riang=1
						  TempFallAttempt.BlockTempCoor[0].x=b;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b+1;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[2].x=b;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[3].x=b;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-3;
						  TempFallAttempt.TetroAxisCoor=TempFallAttempt.BlockTempCoor[2];
						  fallattempt[1].push_back(TempFallAttempt);
						  b++;
					 }

					 b=0;
					 TempFallAttempt.TempTetroRiang=2;
					 while(b<FIELD_WIDTH_BLOCK-2){//riang=2
						  TempFallAttempt.BlockTempCoor[0].x=b;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[2].x=b+1;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[3].x=b+2;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.TetroAxisCoor.x=TempFallAttempt.BlockTempCoor[2].x;
						  TempFallAttempt.TetroAxisCoor.y=TempFallAttempt.BlockTempCoor[2].y+1;
						  fallattempt[2].push_back(TempFallAttempt);
						  b++;
					 }

					 b=0;
					 TempFallAttempt.TempTetroRiang=3;
					 while(b<FIELD_WIDTH_BLOCK-1){
						  TempFallAttempt.BlockTempCoor[0].x=b+1;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b+1;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[2].x=b;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-3;
						  TempFallAttempt.BlockTempCoor[3].x=b+1;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-3;
						  TempFallAttempt.TetroAxisCoor=TempFallAttempt.BlockTempCoor[1];
						  fallattempt[3].push_back(TempFallAttempt);
						  b++;
					 } 
				}break;case L_SHAPE:{
					 int b=0;
					 TempFallAttempt.TempTetroRiang=0;
					 while(b<FIELD_WIDTH_BLOCK-2){//riang=0
						  TempFallAttempt.BlockTempCoor[0].x=b;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b+1;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[2].x=b+2;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[3].x=b;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.TetroAxisCoor=TempFallAttempt.BlockTempCoor[1];
						  fallattempt[0].push_back(TempFallAttempt);
						  b++;
					 }

					 
					 b=0;
					 TempFallAttempt.TempTetroRiang=1;
					 while(b<FIELD_WIDTH_BLOCK-1){//riang=1
						  TempFallAttempt.BlockTempCoor[0].x=b;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[2].x=b;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-3;
						  TempFallAttempt.BlockTempCoor[3].x=b+1;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-3;
						  TempFallAttempt.TetroAxisCoor=TempFallAttempt.BlockTempCoor[1];
						  fallattempt[1].push_back(TempFallAttempt);
						  b++;
					 }

					 b=0;
					 TempFallAttempt.TempTetroRiang=2;
					 while(b<FIELD_WIDTH_BLOCK-2){//riang=2
						  TempFallAttempt.BlockTempCoor[0].x=b+2;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[2].x=b+1;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[3].x=b+2;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.TetroAxisCoor.x=TempFallAttempt.BlockTempCoor[2].x;
						  TempFallAttempt.TetroAxisCoor.y=TempFallAttempt.BlockTempCoor[2].y+1;
						  fallattempt[2].push_back(TempFallAttempt);
						  b++;
					 }

					 b=0;
					 TempFallAttempt.TempTetroRiang=3;
					 while(b<FIELD_WIDTH_BLOCK-1){
						  TempFallAttempt.BlockTempCoor[0].x=b;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b+1;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[2].x=b+1;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[3].x=b+1;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-3;
						  TempFallAttempt.TetroAxisCoor=TempFallAttempt.BlockTempCoor[2];
						  fallattempt[3].push_back(TempFallAttempt);
						  b++;
					 }
				}break;case O_SHAPE:{
					 int b=0;
					 TempFallAttempt.TempTetroRiang=0;
					 while(b<FIELD_WIDTH_BLOCK-1){//riang=0
						  TempFallAttempt.BlockTempCoor[0].x=b;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b+1;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[2].x=b;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[3].x=b+1;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.TetroAxisCoor=TempFallAttempt.BlockTempCoor[3];
						  fallattempt[0].push_back(TempFallAttempt);
						  b++;
					 }



				}break;case S_SHAPE:{
					 int b=0;
					 TempFallAttempt.TempTetroRiang=0;
					 while(b<FIELD_WIDTH_BLOCK-2){//riang=0
						  TempFallAttempt.BlockTempCoor[0].x=b+1;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b+2;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[2].x=b;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[3].x=b+1;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.TetroAxisCoor=TempFallAttempt.BlockTempCoor[0];
						  fallattempt[0].push_back(TempFallAttempt);
						  b++;
					 }

					 b=0;
					 TempFallAttempt.TempTetroRiang=1;
					 while(b<FIELD_WIDTH_BLOCK-1){//riang=1
						  TempFallAttempt.BlockTempCoor[0].x=b;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[2].x=b+1;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[3].x=b+1;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-3;
						  TempFallAttempt.TetroAxisCoor=TempFallAttempt.BlockTempCoor[2];
						  fallattempt[1].push_back(TempFallAttempt);
						  b++;
					 }
				}break;case T_SHAPE:{
					 int b=0;
					 TempFallAttempt.TempTetroRiang=0;
					 while(b<FIELD_WIDTH_BLOCK-2){//riang=0
						  TempFallAttempt.BlockTempCoor[0].x=b;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b+1;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[2].x=b+2;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[3].x=b+1;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.TetroAxisCoor=TempFallAttempt.BlockTempCoor[1];
						  fallattempt[0].push_back(TempFallAttempt);
						  b++;
					 }

					 
					 b=0;
					 TempFallAttempt.TempTetroRiang=1;
					 while(b<FIELD_WIDTH_BLOCK-1){//riang=1
						  TempFallAttempt.BlockTempCoor[0].x=b;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[2].x=b+1;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[3].x=b;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-3;
						  TempFallAttempt.TetroAxisCoor=TempFallAttempt.BlockTempCoor[1];
						  fallattempt[1].push_back(TempFallAttempt);
						  b++;
					 }

					 b=0;
					 TempFallAttempt.TempTetroRiang=2;
					 while(b<FIELD_WIDTH_BLOCK-2){//riang=2
						  TempFallAttempt.BlockTempCoor[0].x=b+1;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[2].x=b+1;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[3].x=b+2;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.TetroAxisCoor=TempFallAttempt.BlockTempCoor[0];
						  fallattempt[2].push_back(TempFallAttempt);
						  b++;
					 }

					 b=0;
					 TempFallAttempt.TempTetroRiang=3;
					 while(b<FIELD_WIDTH_BLOCK-1){
						  TempFallAttempt.BlockTempCoor[0].x=b+1;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[2].x=b+1;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[3].x=b+1;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-3;
						  TempFallAttempt.TetroAxisCoor=TempFallAttempt.BlockTempCoor[2];
						  fallattempt[3].push_back(TempFallAttempt);
						  b++;
					 }
				}break;case Z_SHAPE:{
					 int b=0;
					 TempFallAttempt.TempTetroRiang=0;
					 while(b<FIELD_WIDTH_BLOCK-2){//riang=0
						  TempFallAttempt.BlockTempCoor[0].x=b;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b+1;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[2].x=b+1;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[3].x=b+2;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.TetroAxisCoor=TempFallAttempt.BlockTempCoor[1];
						  fallattempt[0].push_back(TempFallAttempt);
						  b++;
					 }

					 b=0;
					 TempFallAttempt.TempTetroRiang=1;
					 while(b<FIELD_WIDTH_BLOCK-1){//riang=1
						  TempFallAttempt.BlockTempCoor[0].x=b+1;
						  TempFallAttempt.BlockTempCoor[0].y=FIELD_HEIGHT_BLOCK-1;
						  TempFallAttempt.BlockTempCoor[1].x=b;
						  TempFallAttempt.BlockTempCoor[1].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[2].x=b+1;
						  TempFallAttempt.BlockTempCoor[2].y=FIELD_HEIGHT_BLOCK-2;
						  TempFallAttempt.BlockTempCoor[3].x=b;
						  TempFallAttempt.BlockTempCoor[3].y=FIELD_HEIGHT_BLOCK-3;
						  TempFallAttempt.TetroAxisCoor=TempFallAttempt.BlockTempCoor[1];
						  fallattempt[1].push_back(TempFallAttempt);
						  b++;
					 }
				}break;
			}
			int FallAttemptMaxRiang;
			switch (field.GetCurrentTetroShape()){
				 break;case I_SHAPE:FallAttemptMaxRiang=2;
				 break;case J_SHAPE:FallAttemptMaxRiang=4;
				 break;case L_SHAPE:FallAttemptMaxRiang=4;
				 break;case O_SHAPE:FallAttemptMaxRiang=1;
				 break;case S_SHAPE:FallAttemptMaxRiang=2;
				 break;case T_SHAPE:FallAttemptMaxRiang=4;
				 break;case Z_SHAPE:FallAttemptMaxRiang=2;
			}
			for(int d=0;d<FallAttemptMaxRiang;d++){//採点
				for(int a=0;a<fallattempt[d].size();a++){
					field.GetTetroLimitFallCoor(fallattempt[d].at(a).BlockTempCoor);
					CalcUnderBlockNoneScore(field,fallattempt[d].at(a));
					CalcThreeHeightWallScore(field,fallattempt[d].at(a));
					CalcNearBlockScore(field,fallattempt[d].at(a));
					CalcDeleteLineScore(field,fallattempt[d].at(a));
					//CalcHighCooryScore(field,fallattempt[d].at(a));
					CalcHighestCooryScore(field,fallattempt[d].at(a));
					//fallattempt[d].at(a).Score-=fallattempt[d].at(a).BlockTempCoor[0].y;
					//fallattempt[d].at(a).IsUsed=IsAbleToMoveAttempt(field,fallattempt[d].at(a));
				}
			}
		
			std::vector<int> DeleteFactNum;
			for(int d=0;d<FallAttemptMaxRiang;d++){//削除
				int SoFardeleteNum=0;
				for(int a=0;a<fallattempt[d].size();a++){
					if(!IsAbleToMoveAttempt(field,fallattempt[d].at(a)))DeleteFactNum.push_back(a);
				}
				for(int b=0;b<DeleteFactNum.size();b++){
					 std::vector<FallAttempt>::iterator it=fallattempt[d].begin();
					 for(int c=0;c<DeleteFactNum[b]-SoFardeleteNum;c++)it++;
					 fallattempt[d].erase(it);
					 SoFardeleteNum++;
				}
				DeleteFactNum.clear();
			}
			if(CheckHitKey(KEY_INPUT_RSHIFT)){
				printfDx("stopped");
			}
			
			IsAICalced=true;

		if(IsAICalced){
		bool IsPushBack=false;
			for(int d=0;d<4;d++){
				for(int a=0;a<fallattempt[d].size();a++){
					if(d==0&&a==0)BestAttempt.push_back(fallattempt[d].at(a));
					else {
						for(int b=0;b<BestAttempt.size();b++){
							if(fallattempt[d].at(a).Score>BestAttempt[b].Score){
								BestAttempt.clear();
								IsPushBack=true;
							}else if(fallattempt[d].at(a).Score==BestAttempt[b].Score){
								IsPushBack=true;
							}else if(fallattempt[d].at(a).Score<BestAttempt[b].Score)IsPushBack=false;
						}if(IsPushBack)BestAttempt.push_back(fallattempt[d].at(a));
					}	
				}
			}

			/*for(int d=0;d<BestAttempt.size();d++){
				fprintf(LogFP,"BestAttempt[d].BlocktempCoor:(%d,%d)(%d,%d)(%d,%d)(%d,%d)\n",d,BestAttempt[d].BlockTempCoor[0].x,BestAttempt[d].BlockTempCoor[0].y,
					BestAttempt[d].BlockTempCoor[1].x,BestAttempt[d].BlockTempCoor[1].y,BestAttempt[d].BlockTempCoor[2].x,BestAttempt[d].BlockTempCoor[2].y,
					BestAttempt[d].BlockTempCoor[3].x,BestAttempt[d].BlockTempCoor[3].y);
				fprintf(LogFP,"  BestAttempt[d].Score:%d\n\n",BestAttempt[d].Score);
			}*/

		SRand(RandSeed);
		int RandNum=GetRand(BestAttempt.size()-1);
		FallAttempt Chosenplan=BestAttempt[RandNum];

		//fprintf(LogFP,"\nBestAttempt[%d] is chosen\n\n",RandNum);

		for(int d=0;d<Chosenplan.TempTetroRiang;d++){//RotateのほうのKeyPlan
			KeyInputPlan.push_back(LEVORO_IN);
			KeyInputPlan.push_back(NONE_IN);
		}
		int CurrentTetroAxisCoorx;
		switch (field.GetCurrentTetroShape()){
			 break;case I_SHAPE:CurrentTetroAxisCoorx=field.GetTetroCoor(2).x;
			 break;case J_SHAPE:CurrentTetroAxisCoorx=field.GetTetroCoor(1).x;
			 break;case L_SHAPE:CurrentTetroAxisCoorx=field.GetTetroCoor(1).x;
			 break;case O_SHAPE:CurrentTetroAxisCoorx=field.GetTetroCoor(3).x;
			 break;case S_SHAPE:CurrentTetroAxisCoorx=field.GetTetroCoor(0).x;
			 break;case T_SHAPE:CurrentTetroAxisCoorx=field.GetTetroCoor(1).x;
			 break;case Z_SHAPE:CurrentTetroAxisCoorx=field.GetTetroCoor(1).x;
		}
		if(Chosenplan.TetroAxisCoor.x<CurrentTetroAxisCoorx){
			for(int d=0;d<CurrentTetroAxisCoorx-Chosenplan.TetroAxisCoor.x;d++){
				KeyInputPlan.push_back(LEFT_IN);
				KeyInputPlan.push_back(NONE_IN);
			}
		}if(Chosenplan.TetroAxisCoor.x>CurrentTetroAxisCoorx){
			for(int d=0;d<Chosenplan.TetroAxisCoor.x-CurrentTetroAxisCoorx;d++){
				KeyInputPlan.push_back(RIGHT_IN);
				KeyInputPlan.push_back(NONE_IN);
			}
		}

		/*for(int d=0;d<KeyInputPlan.size();d++){
			fprintf(LogFP,"KeyInputPlan[%d]=%d\n",d,KeyInputPlan[d]);
		}*/
		
		
		KeyInputPlan.push_back(HARD_DROP_IN);

		IsKeyInputPlanPrepared=true;
					 
		IsNextTetro=false;
		}
		//fclose(LogFP);
		  
	 }
	 if(!IsNextTetro){
		  if(field.GetCurrentStatus()==WAITING)IsNextTetro=true;
	 }
	 
	 if(IsKeyInputPlanPrepared){
		  switch (KeyInputPlan[keyInputPlanPosition]){
				break;case HARD_DROP_IN :keybuf[HARD_DROP_KEY]=true;
				break;case LEVORO_IN :keybuf[LEVORO_KEY]=true;
				break;case CLOCK_IN :keybuf[CLOCK_KEY]=true;
				break;case RIGHT_IN:keybuf[RIGHT_KEY]=true;
				break;case LEFT_IN:keybuf[LEFT_KEY]=true;
		  }
		  keyInputPlanPosition++;
		  if(keyInputPlanPosition>=KeyInputPlan.size()){
				keyInputPlanPosition=0;
				KeyInputPlan.clear();
				IsKeyInputPlanPrepared=false;
		  }
	 }
		  
}
void CalcUnderBlockNoneScore(Field& field,FallAttempt& fallattempt){
	 std::vector<Coordinate> ConsiderBlockCoor;
	 int counter=0;
	 int UnderBlockNoneNum=0;

	 for(int d=0;d<4;d++){
			for(int b=0;b<4;b++){
				 if(fallattempt.BlockTempCoor[d].x==fallattempt.BlockTempCoor[b].x&&
					  fallattempt.BlockTempCoor[d].y==fallattempt.BlockTempCoor[b].y+1)counter++;
			}
			if(counter==0)ConsiderBlockCoor.push_back(fallattempt.BlockTempCoor[d]);
			counter=0;
	 }
	 for(int d=0;d<ConsiderBlockCoor.size();d++){
		  while(!field.IsThereBlock(ConsiderBlockCoor[d].x,ConsiderBlockCoor[d].y-1-UnderBlockNoneNum)){UnderBlockNoneNum++;}
		  fallattempt.Score-=UnderBlockNoneNum*2;
		  UnderBlockNoneNum=0;
	 }
}
void CalcThreeHeightWallScore(Field& field,FallAttempt& fallattempt){
	 std::vector<Coordinate> MostLeftCoor;
	 std::vector<Coordinate> MostRightCoor;
	 Coordinate WallNearCoor[9];
	 MostLeftCoor.push_back(fallattempt.BlockTempCoor[0]);
	 MostRightCoor.push_back(fallattempt.BlockTempCoor[0]);
	 bool IsPushBack=false;
	 
	 for(int d=1;d<4;d++){
		  for(int b=0;b<MostLeftCoor.size();b++){
				if(fallattempt.BlockTempCoor[d].x==MostLeftCoor[b].x)IsPushBack=true;
				if(fallattempt.BlockTempCoor[d].x<MostLeftCoor[b].x){
					 IsPushBack=true;
					 MostLeftCoor.clear();
				}
		  }
		  if(IsPushBack){
				MostLeftCoor.push_back(fallattempt.BlockTempCoor[d]);
				IsPushBack=false;
		  }
	 }

	 for(int d=0;d<3;d++){
		  for(int b=0;b<3;b++){
				WallNearCoor[3*d+b].x=MostLeftCoor[0].x-d;
				WallNearCoor[3*d+b].y=MostLeftCoor[0].y-b;
		  }
	 }
	 if(!field.IsThereBlock(WallNearCoor[3])&&!field.IsThereBlock(WallNearCoor[4])&&!field.IsThereBlock(WallNearCoor[5])&&
		  field.IsThereBlock(WallNearCoor[6]))fallattempt.Score-=3;
	 


	 for(int d=1;d<4;d++){
		  for(int b=0;b<MostRightCoor.size();b++){
				if(fallattempt.BlockTempCoor[d].x==MostRightCoor[b].x)IsPushBack=true;
				if(fallattempt.BlockTempCoor[d].x>MostRightCoor[b].x){
					 IsPushBack=true;
					 MostRightCoor.clear();
				}
		  }
		  if(IsPushBack){
				MostRightCoor.push_back(fallattempt.BlockTempCoor[d]);
				IsPushBack=false;
		  }
	 }

	 for(int d=0;d<3;d++){
		  for(int b=0;b<3;b++){
				WallNearCoor[3*d+b].x=MostRightCoor[0].x+d;
				WallNearCoor[3*d+b].y=MostRightCoor[0].y-b;
		  }
	 }

	 if(!field.IsThereBlock(WallNearCoor[3])&&!field.IsThereBlock(WallNearCoor[4])&&!field.IsThereBlock(WallNearCoor[5])&&
		  field.IsThereBlock(WallNearCoor[6]))fallattempt.Score-=3;
}
void CalcNearBlockScore(Field& field,FallAttempt& fallattempt){
	 std::vector<Coordinate> TetroNearCoor;
	 int counter=0;
	 TetroNearCoor.push_back(GetCoordinate(fallattempt.BlockTempCoor[0].x+1,fallattempt.BlockTempCoor[0].y));
	 for(int d=0;d<4;d++){
		  /*TetroNearCoor.insert(GetCoordinate(fallattempt.BlockTempCoor[d].x+1,fallattempt.BlockTempCoor[d].y));
		  TetroNearCoor.insert(GetCoordinate(fallattempt.BlockTempCoor[d].x,fallattempt.BlockTempCoor[d].y+1));
		  TetroNearCoor.insert(GetCoordinate(fallattempt.BlockTempCoor[d].x-1,fallattempt.BlockTempCoor[d].y));
		  TetroNearCoor.insert(GetCoordinate(fallattempt.BlockTempCoor[d].x,fallattempt.BlockTempCoor[d].y-1));*/
		  for(int b=0;b<TetroNearCoor.size();b++){
				if(TetroNearCoor[b]==GetCoordinate(fallattempt.BlockTempCoor[d].x+1,fallattempt.BlockTempCoor[d].y))counter++;
		  }
		  if(counter==0)TetroNearCoor.push_back(GetCoordinate(fallattempt.BlockTempCoor[d].x+1,fallattempt.BlockTempCoor[d].y));
		  counter=0;

		  for(int b=0;b<TetroNearCoor.size();b++){
				if(TetroNearCoor[b]==GetCoordinate(fallattempt.BlockTempCoor[d].x,fallattempt.BlockTempCoor[d].y+1))counter++;
		  }
		  if(counter==0)TetroNearCoor.push_back(GetCoordinate(fallattempt.BlockTempCoor[d].x,fallattempt.BlockTempCoor[d].y+1));
		  counter=0;

		  for(int b=0;b<TetroNearCoor.size();b++){
				if(TetroNearCoor[b]==GetCoordinate(fallattempt.BlockTempCoor[d].x-1,fallattempt.BlockTempCoor[d].y))counter++;
		  }
		  if(counter==0)TetroNearCoor.push_back(GetCoordinate(fallattempt.BlockTempCoor[d].x-1,fallattempt.BlockTempCoor[d].y));
		  counter=0;

		  for(int b=0;b<TetroNearCoor.size();b++){
				if(TetroNearCoor[b]==GetCoordinate(fallattempt.BlockTempCoor[d].x,fallattempt.BlockTempCoor[d].y-1))counter++;
		  }
		  if(counter==0)TetroNearCoor.push_back(GetCoordinate(fallattempt.BlockTempCoor[d].x,fallattempt.BlockTempCoor[d].y-1));
		  counter=0;
	 }
	 for(int d=0;d<TetroNearCoor.size();d++){
		  if(!field.IsThereBlock(TetroNearCoor[d]))fallattempt.Score-=2;
	 }
	 fallattempt.Score+=8;
}
void CalcDeleteLineScore(Field& field,FallAttempt& fallattempt){
	 /*std::set<int> TetroCoory;
	 for(int d=0;d<4;d++){
		  TetroCoory.insert(fallattempt.BlockTempCoor[d].y);
	 }
	 std::set<int>::iterator it=TetroCoory.begin();
	 
	 std::vector<int> LineBlockNum(TetroCoory.size());
	 for(int d=0;d<LineBlockNum.size();d++){
		  for(int b=0;b<FIELD_WIDTH_BLOCK;b++){
				if(field.GetCoorStatus(b,*it)!=NONE)LineBlockNum[b]++;
				++it;
		  }
	 }*/
	 int LineBlockNum[FIELD_HEIGHT_BLOCK];
	 for(int d=0;d<FIELD_HEIGHT_BLOCK;d++)LineBlockNum[d]=0;
	 for(int d=0;d<FIELD_HEIGHT_BLOCK;d++){
		  for(int b=0;b<FIELD_WIDTH_BLOCK;b++){
				if(field.GetCoorStatus(b,d)!=NONE)LineBlockNum[d]++;
		  }
	 }
	 for(int d=0;d<4;d++){
		  if(fallattempt.BlockTempCoor[d].y<FIELD_HEIGHT_BLOCK)LineBlockNum[fallattempt.BlockTempCoor[d].y]++;
	 }
	 for(int d=0;d<FIELD_HEIGHT_BLOCK;d++)if(LineBlockNum[d]==FIELD_WIDTH_BLOCK){
		if(int(field.GetHeightBar())<FIELD_HEIGHT_BLOCK)fallattempt.Score+=8;//←もともと:+3
		else fallattempt.Score+=16;
	 }
}
void CalcHighCooryScore(Field& field,FallAttempt& fallattempt){
	int MinCoory=fallattempt.BlockTempCoor[0].y;
	for(int b=1;b<4;b++){
		if(MinCoory>fallattempt.BlockTempCoor[b].y){
			MinCoory=fallattempt.BlockTempCoor[b].y;
		}
	}
	if(MinCoory<=FIELD_HEIGHT_BLOCK-2)fallattempt.Score-=6;
}
bool IsAbleToMoveAttempt(Field& field,FallAttempt& fallattempt){
	 int BeforeAttemptTetroCoorx;
	 switch(field.GetCurrentTetroShape()){
		  break;case I_SHAPE:BeforeAttemptTetroCoorx=FIELD_WIDTH_BLOCK/2+1;
		  break;case J_SHAPE:BeforeAttemptTetroCoorx=FIELD_WIDTH_BLOCK/2;
		  break;case L_SHAPE:BeforeAttemptTetroCoorx=FIELD_WIDTH_BLOCK/2;
		  break;case O_SHAPE:BeforeAttemptTetroCoorx=FIELD_WIDTH_BLOCK/2+1;
		  break;case S_SHAPE:BeforeAttemptTetroCoorx=FIELD_WIDTH_BLOCK/2;
		  break;case T_SHAPE:BeforeAttemptTetroCoorx=FIELD_WIDTH_BLOCK/2;
		  break;case Z_SHAPE:BeforeAttemptTetroCoorx=FIELD_WIDTH_BLOCK/2;
	 }
	 Direction MoveDirection;
	 if(BeforeAttemptTetroCoorx<=fallattempt.TetroAxisCoor.x)MoveDirection=RIGHT;
	 else MoveDirection=LEFT;
	 int TotalRotateRiang=0;

	 int FallingFlame=0;
	 Tetromino AttemptTetro(field.GetCurrentTetroShape(),&field);
	 for(int d=0;d<fallattempt.TempTetroRiang;d++)AttemptTetro.TetroRotate(1);
	 FallingFlame++;
	 int d=0;
	 int counter=0;
	 for(int b=0;b<abs(BeforeAttemptTetroCoorx-fallattempt.TetroAxisCoor.x);b++){
		  while(d<int(field.GetFallG()*FallingFlame)){
				if(!AttemptTetro.TetroMove(DOWN))return false;
				d++;
				counter++;
		  }
		  d=0;
		  FallingFlame+=2;
		  if(counter>0)FallingFlame=0;
		  if(!AttemptTetro.TetroMove(MoveDirection))return false;//{
			/*	while(!AttemptTetro.TetroMove(MoveDirection)){
					 if(TotalRotateRiang==fallattempt.TempTetroRiang)return false;
					 AttemptTetro.TetroRotate(1);
					 ++TotalRotateRiang;
				}
		  }*/
		  //if(AttemptTetro.GetIstouched())return false;
	}
	return true;
}
void CalcHighestCooryScore(Field& field,FallAttempt& fallattempt){
	 if(int(field.GetHeightBar())<FIELD_HEIGHT_BLOCK)fallattempt.Score-=fallattempt.BlockTempCoor[0].y;
		else fallattempt.Score-=fallattempt.BlockTempCoor[0].y*3;
}
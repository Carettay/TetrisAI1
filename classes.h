#pragma once
#include"definitions.h"
class Tetromino;
class Field_Square;
class Field;

class Tetromino{
	private:
		Coordinate BlockCoor[4];
		Tetro_Shape Shape;
		Field *m_Field;
		bool IsTouched;
		int TetroRiAng;
	public:
		Tetromino(Tetro_Shape shape,Field* field);
		bool TetroRotate(int dir);//dir直角分反時計回りに回す dir=-1or+1 return=false→失敗
		bool TetroMove(Direction dir);//テトロミノを移動する return=false→失敗
		bool TetroMoveByCoor(Coordinate coor1,Coordinate coor2,Coordinate coor3,Coordinate coor4,int dir);//テトロミノをfield座標を指定して移動させる　true=成功
		bool TetroMoveByCoor(Coordinate* coor,int dir);//テトロミノをfield座標を指定して移動させる　true=成功
		bool TetroCheckRotate(int CoorZeroNum,int CoorOneNum,int CoorTwoNum,int CoorThreeNum,Field_Square* Sqr,int dir);//TetroRotateの中で使う
		bool GetIstouched();//テトロミノが接地しているかを返す true→設置している
		Tetro_Shape GetShape();
		Coordinate GetCoor(int n);
		int GetTetroRiang();
		bool IsThereTetro(int x,int y);//現在落下中のテトロミノが指定した座標にあるかを返す
		bool IsThereTetro(Coordinate coor);//現在落下中のテトロミノが指定した座標にあるかを返す
};
class Field_Square{
	private:
		Block_Color BlockArray[FIELD_SQUARE_SIZE*FIELD_SQUARE_SIZE];
		Coordinate Axis;
	public:
		Field_Square(Field *field,Coordinate axis);
		Field_Square(Field *field,int x,int y);
		Block_Color GetArrayNum(int n);
		Coordinate SqToField(int n);//square座標系をfield座標系にする
		Block_Color operator[](int n);
		void SetAxis(int x,int y);
		void SetAxis(Coordinate coor);
};
class Field{
	private:
		Block_Color field[FIELD_WIDTH_BLOCK][FIELD_HEIGHT_BLOCK];
		FieldStatus CurrentStatus;
		Tetromino* CurrentTetromino;
		//int FallSpeed;//テトロミノが1マス降りるのにかかる時間
		double FallG;
		int FallingFlame;////テトロミノがこれまでに落下している時間
		int TetroTouchingTime;//テトロミノがこれまでに接地している時間
		int LimitTouchingTime;//テトロミノが接地してよい最高時間
		int LineBreakingTime;//ライン消去状態の時間
		int WaitingTime;//待機時間
		int LimitWaitingTime;//待機可能最高時間
		std::vector<int> breakingLine;//現在消去中の行
		bool IsTetroSoftdropping;
		bool IsTetroHarddropping;
		bool IsAlreadyHolded;//落下中にすでにホールドしたか

		int TotalDisappLine;
		int TotalScore;
		int ScoreFontHandle;//スコア表示用のフォントハンドル

		int RandSeed;//乱数シード

		Tetro_Shape HoldingTetro;

		double HeightBar;

		Tetro_Shape WaitingTetro[WAITING_TETRO_NUM];
		Tetro_Shape BackGroundWaitingTetro[BACKGROUND_WAITING_NUM];
		//std::array<Tetro_Shape,BACKGROUND_WAITING_NUM> BackGroundWaitingTetro;
		int BackWaitingTetroPosition;

		int CurrentTetroNum;//今のテトロミノが何個目か

		void CalcHeightBar();

	class HoldingWaitingField{
		private:
			Tetro_Shape Shape[4];//Shape[0]=Holding,Shape[1～3]=Waiting
			int FieldXCoor;
			int FieldYCoor;
			int BlockSize;
			int TetroGHandle[8];
		public:
			HoldingWaitingField();
			void SetShape(Tetro_Shape HoldingTetro,Tetro_Shape* WaitingTetro);
			void DrawHWField();
	} HWField;
public:
		Field();
		Block_Color GetCoorStatus(Coordinate cor);
		Block_Color GetCoorStatus(int x,int y);
		void SetNone(int x,int y);//SetMillerFieldのみに使用
		void SetNone(Coordinate coor);//SetMillerFieldのみに使用
		void SetFieldFromFile(FILE* fieldfile);
		void SetWaitingTetro();//Waitingのテトロミノをセット
		Tetro_Shape SetHoldingTetro();//Holdingのテトロミノをセット
		Tetro_Shape GetWaitingTetro(int n);
		bool GetIsAlreadyHolded();
		bool SetCurrentTetrominoAndIsGameOver(Tetromino* tetro);//true→ゲームオーバ
		bool SetCurrentTetrominoByHoldingAndIsGameOver(Tetromino* tetro);//true→ゲームオーバ
		void SetLimitTouchingTime(int LimitTime);
		//void SetFallSpeed(int Speed);
		void SetFallG();
		int RenewCurrentStatus();
		void RenewTouchingStatus();//接地しているときに、情報を更新する
		void RenewWaitingStatus();
		bool MoveCurrentTetromino(Direction dir);
		bool RotateCurrentTetromino(int riang);
		void AutoFallTetro();
		bool SoftdropCurrentTetromino();
		void MiddleDropCurrentTetromino();
		void HarddropCurrentTetromino();
		//void DeleteLine();
		void RenewDeleteLineStatus();
		void DrawField();
		void DrawBreakingBox();
		void DrawGauge();//TouchingTime/LimitTouchingTime、WaitingTime/LimitwaitingTimeのゲージ
		void DrawTotalLineAndG();//TotalLine,Scoreの表示
		void Field::DrawHWField();
		void DrawFallPoint();//テトロミノの落下地点を表示する
		void DrawCurrentTetroNum();
		FieldStatus GetCurrentStatus();
		int GetCurrentTetroRiang();
		Tetro_Shape GetCurrentTetroShape();
		void GetTetroLimitFallCoor(const Coordinate* FallTetroCoor,Coordinate* LimitFalledCoor);
		void GetTetroLimitFallCoor(Coordinate coor1,Coordinate coor2,Coordinate coor3,Coordinate coor4,Coordinate* LimitFalledCoor);
		void GetTetroLimitFallCoor(Coordinate* FallTetroCoor);
		int GetRandSeed();
		Coordinate GetTetroCoor(int n);
		double GetFallG();
		double GetHeightBar();
		bool IsThereCurrentTetro(int x,int y);//現在落下中のテトロミノが指定した座標にあるかを返す
		bool IsThereCurrentTetro(Coordinate coor);//現在落下中のテトロミノが指定した座標にあるかを返す
		bool IsThereBlock(int x,int y);
		bool IsThereBlock(Coordinate coor);
		bool IsReadyToFall();
		void FieldLoadFromFile(char* filename);
};



Tetromino::Tetromino(Tetro_Shape shape,Field *field){
	Shape=shape;
	m_Field=field;
	TetroRiAng=0;
	switch(shape){
		break;case I_SHAPE:{
			BlockCoor[0].x=FIELD_WIDTH_BLOCK/2-1;
			BlockCoor[0].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[1].x=FIELD_WIDTH_BLOCK/2;
			BlockCoor[1].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[2].x=FIELD_WIDTH_BLOCK/2+1;
			BlockCoor[2].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[3].x=FIELD_WIDTH_BLOCK/2+2;
			BlockCoor[3].y=FIELD_HEIGHT_BLOCK-1;
		}break;case J_SHAPE:{
			BlockCoor[0].x=FIELD_WIDTH_BLOCK/2-1;
			BlockCoor[0].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[1].x=FIELD_WIDTH_BLOCK/2;
			BlockCoor[1].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[2].x=FIELD_WIDTH_BLOCK/2+1;
			BlockCoor[2].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[3].x=FIELD_WIDTH_BLOCK/2+1;
			BlockCoor[3].y=FIELD_HEIGHT_BLOCK-2;
		}break;case L_SHAPE:{
			BlockCoor[0].x=FIELD_WIDTH_BLOCK/2-1;
			BlockCoor[0].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[1].x=FIELD_WIDTH_BLOCK/2;
			BlockCoor[1].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[2].x=FIELD_WIDTH_BLOCK/2+1;
			BlockCoor[2].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[3].x=FIELD_WIDTH_BLOCK/2-1;
			BlockCoor[3].y=FIELD_HEIGHT_BLOCK-2;
		}break;case O_SHAPE:{
			BlockCoor[0].x=FIELD_WIDTH_BLOCK/2;
			BlockCoor[0].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[1].x=FIELD_WIDTH_BLOCK/2+1;
			BlockCoor[1].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[2].x=FIELD_WIDTH_BLOCK/2;
			BlockCoor[2].y=FIELD_HEIGHT_BLOCK-2;
			BlockCoor[3].x=FIELD_WIDTH_BLOCK/2+1;
			BlockCoor[3].y=FIELD_HEIGHT_BLOCK-2;
		}break;case S_SHAPE:{
			BlockCoor[0].x=FIELD_WIDTH_BLOCK/2;
			BlockCoor[0].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[1].x=FIELD_WIDTH_BLOCK/2+1;
			BlockCoor[1].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[2].x=FIELD_WIDTH_BLOCK/2-1;
			BlockCoor[2].y=FIELD_HEIGHT_BLOCK-2;
			BlockCoor[3].x=FIELD_WIDTH_BLOCK/2;
			BlockCoor[3].y=FIELD_HEIGHT_BLOCK-2;
		}break;case T_SHAPE:{
			BlockCoor[0].x=FIELD_WIDTH_BLOCK/2-1;
			BlockCoor[0].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[1].x=FIELD_WIDTH_BLOCK/2;
			BlockCoor[1].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[2].x=FIELD_WIDTH_BLOCK/2+1;
			BlockCoor[2].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[3].x=FIELD_WIDTH_BLOCK/2;
			BlockCoor[3].y=FIELD_HEIGHT_BLOCK-2;
		}break;case Z_SHAPE:{
			BlockCoor[0].x=FIELD_WIDTH_BLOCK/2-1;
			BlockCoor[0].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[1].x=FIELD_WIDTH_BLOCK/2;
			BlockCoor[1].y=FIELD_HEIGHT_BLOCK-1;
			BlockCoor[2].x=FIELD_WIDTH_BLOCK/2;
			BlockCoor[2].y=FIELD_HEIGHT_BLOCK-2;
			BlockCoor[3].x=FIELD_WIDTH_BLOCK/2+1;
			BlockCoor[3].y=FIELD_HEIGHT_BLOCK-2;
		}
	}
}
bool Tetromino::TetroRotate(int dir){
	Coordinate Axis;//5*5正方形に入れた時の「12」の位置,field座標系
	//Field Mirror_Field=m_Field->SetMillerField();
	
	
	switch(Shape){
		break;case I_SHAPE:{
			Coordinate AfterRotateCoor[4];
			switch(imod(TetroRiAng,2)){
				break;case 0:{
					Axis=BlockCoor[2];
				}break;case 1:{
					Axis=BlockCoor[1];
				}	
			}
			switch(dir){
				 break;case 1:{
					  switch(imod(TetroRiAng,2)){
							break;case 0:{
								 for(int d=0;d<4;d++){
									  AfterRotateCoor[d].x=Axis.x;
									  AfterRotateCoor[d].y=Axis.y-d+1;
								 }
								 if(TetroMoveByCoor(AfterRotateCoor,dir))return true;
								 for(int d=0;d<4;d++){
									  AfterRotateCoor[d].y+=-1;
								 }
								 if(TetroMoveByCoor(AfterRotateCoor,dir))return true;
								 for(int d=0;d<4;d++){
									  AfterRotateCoor[d].y+=2;
								 }
								 if(TetroMoveByCoor(AfterRotateCoor,dir))return true;
								 for(int d=0;d<4;d++){
									  AfterRotateCoor[d].y+=1;
								 }
								 if(TetroMoveByCoor(AfterRotateCoor,dir))return true;
							}break;case 1:{
								 for(int d=0;d<4;d++){
									  AfterRotateCoor[d].x=Axis.x+d-2;
									  AfterRotateCoor[d].y=Axis.y;
								 }
								 if(TetroMoveByCoor(AfterRotateCoor,dir))return true;
								 for(int d=0;d<4;d++){
									  AfterRotateCoor[d].x+=-1;
								 }
								 if(TetroMoveByCoor(AfterRotateCoor,dir))return true;
								 for(int d=0;d<4;d++){
									  AfterRotateCoor[d].x+=2;
								 }
								 if(TetroMoveByCoor(AfterRotateCoor,dir))return true;
								 for(int d=0;d<4;d++){
									  AfterRotateCoor[d].x+=1;
								 }
								 if(TetroMoveByCoor(AfterRotateCoor,dir))return true;
							}
					  }
				 }break;case -1:{
					  switch(imod(TetroRiAng,2)){
							break;case 0:{
								 for(int d=0;d<4;d++){
									  AfterRotateCoor[d].x=Axis.x;
									  AfterRotateCoor[d].y=Axis.y-d+1;
								 }
								 if(TetroMoveByCoor(AfterRotateCoor,dir))return true;
								 for(int d=0;d<4;d++){
									  AfterRotateCoor[d].y+=-1;
								 }
								 if(TetroMoveByCoor(AfterRotateCoor,dir))return true;
								 for(int d=0;d<4;d++){
									  AfterRotateCoor[d].y+=2;
								 }
								 if(TetroMoveByCoor(AfterRotateCoor,dir))return true;
								 for(int d=0;d<4;d++){
									  AfterRotateCoor[d].y+=1;
								 }
								 if(TetroMoveByCoor(AfterRotateCoor,dir))return true;
							}break;case 1:{
								 for(int d=0;d<4;d++){
									  AfterRotateCoor[d].x=Axis.x+d-2;
									  AfterRotateCoor[d].y=Axis.y;
								 }
								 if(TetroMoveByCoor(AfterRotateCoor,dir))return true;
								 for(int d=0;d<4;d++){
									  AfterRotateCoor[d].x+=-1;
								 }
								 if(TetroMoveByCoor(AfterRotateCoor,dir))return true;
								 for(int d=0;d<4;d++){
									  AfterRotateCoor[d].x+=2;
								 }
								 if(TetroMoveByCoor(AfterRotateCoor,dir))return true;
								 for(int d=0;d<4;d++){
									  AfterRotateCoor[d].x+=1;
								 }
								 if(TetroMoveByCoor(AfterRotateCoor,dir))return true;
							}
					  }
				 }

			}
		}break;case J_SHAPE:{
			 switch(imod(TetroRiAng,4)){
				break;case 0:{
					Axis=BlockCoor[1];
				}break;case 1:{
					Axis=BlockCoor[2];
				}break;case 2:{
					Axis=BlockCoor[2];
					++Axis.y;
				}break;case 3:{
					Axis=BlockCoor[1];
				}
			}
			 Field_Square F_Sqr(m_Field,Axis);
			 switch (dir){
				  break;case 1:{
						switch(imod(TetroRiAng,4)){
								break;case 0:{
									if(TetroCheckRotate(7,8,12,17,&F_Sqr,1)) return true;	
									if((F_Sqr[7]!=NONE&&F_Sqr[7]!=WALL)||(F_Sqr[8]!=NONE&&F_Sqr[8]!=WALL)){
										  return TetroCheckRotate(12,13,17,22,&F_Sqr,1);
									}if(F_Sqr[17]!=NONE){
										  return TetroCheckRotate(2,3,7,12,&F_Sqr,1);
									}
								}break;case 1:{
					 				if(TetroCheckRotate(11,16,17,18,&F_Sqr,1)) return true;
									if(F_Sqr[6]!=NONE&&F_Sqr[11]!=NONE&&F_Sqr[16]!=NONE){
										  return TetroCheckRotate(12,17,18,19,&F_Sqr,1);
									}if(F_Sqr[18]!=NONE){
										  return TetroCheckRotate(10,15,16,17,&F_Sqr,1);
									}
								}break;case 2:{
									if(TetroCheckRotate(7,12,16,17,&F_Sqr,1)) return true;
									if(F_Sqr[7]!=NONE&&F_Sqr[7]!=WALL){
										  return TetroCheckRotate(12,17,21,22,&F_Sqr,1);
									}
								}break;case 3:{
									 	if(TetroCheckRotate(11,12,13,18,&F_Sqr,1)) return true;
										if(F_Sqr[13]!=NONE||F_Sqr[18]!=NONE){
										  return TetroCheckRotate(10,11,12,17,&F_Sqr,1);
									}if(F_Sqr[11]!=NONE){
										  return TetroCheckRotate(12,13,14,19,&F_Sqr,1);
									}
								}
						}
				  }break;case -1:{
						switch(imod(TetroRiAng,4)){
								break;case 0:{
									if(TetroCheckRotate(7,12,16,17,&F_Sqr,-1)) return true;	
									if(F_Sqr[16]!=NONE||F_Sqr[17]!=NONE){
										  return TetroCheckRotate(2,7,11,12,&F_Sqr,-1);
									}if(F_Sqr[7]!=NONE&&F_Sqr[7]!=WALL){
										  return TetroCheckRotate(12,17,21,22,&F_Sqr,-1);
									}
								}break;case 1:{
					 				if(TetroCheckRotate(11,12,13,18,&F_Sqr,-1)) return true;
									if(F_Sqr[13]!=NONE||F_Sqr[18]!=NONE){
										  return TetroCheckRotate(10,11,12,17,&F_Sqr,-1);
									}if(F_Sqr[11]!=NONE){
										  return TetroCheckRotate(12,13,14,19,&F_Sqr,-1);
									}
								}break;case 2:{
									if(TetroCheckRotate(7,8,12,17,&F_Sqr,-1)) return true;
									if((F_Sqr[7]!=NONE&&F_Sqr[7]!=WALL)||(F_Sqr[8]!=NONE&&F_Sqr[8]!=WALL)){
										  return TetroCheckRotate(12,13,17,22,&F_Sqr,-1);
									}
								}break;case 3:{
									if(TetroCheckRotate(11,16 ,17,18,&F_Sqr,-1)) return true;
									if(F_Sqr[18]!=NONE&&F_Sqr[13]!=NONE){
										  return TetroCheckRotate(10,15,16,17,&F_Sqr,-1);
									}
									if(F_Sqr[18]!=NONE){
										  return TetroCheckRotate(6,11,12,13,&F_Sqr,-1);
									}
								}
						}
				  }
			 }
		}break;case L_SHAPE:{
			 switch(imod(TetroRiAng,4)){
				break;case 0:{
					Axis=BlockCoor[1];
				}break;case 1:{
					Axis=BlockCoor[1];
				}break;case 2:{
					Axis=BlockCoor[2];
					++Axis.y;
				}break;case 3:{
					Axis=BlockCoor[2];
				}
			}

			Field_Square F_Sqr(m_Field,Axis);
			 switch (dir){
				  break;case 1:{
						switch(imod(TetroRiAng,4)){
								break;case 0:{
									if(TetroCheckRotate(7,12,17,18,&F_Sqr,1)) return true;	
									if(F_Sqr[17]!=NONE||F_Sqr[18]!=NONE){
										  return TetroCheckRotate(2,7,12,13,&F_Sqr,1);
									}if(F_Sqr[7]!=NONE&&F_Sqr[7]!=WALL){
										  return TetroCheckRotate(12,17,22,23,&F_Sqr,1);
									}
								}break;case 1:{
					 				if(TetroCheckRotate(13,16,17,18,&F_Sqr,1)) return true;
									if(F_Sqr[13]!=NONE){
										  return TetroCheckRotate(12,15,16,17,&F_Sqr,1);
									}if(F_Sqr[16]!=NONE){
										  return TetroCheckRotate(14,17,18,19,&F_Sqr,1);
									}
								}break;case 2:{
									if(TetroCheckRotate(6,7,12,17,&F_Sqr,1)) return true;
									if((F_Sqr[6]!=NONE&&F_Sqr[6]!=WALL)||(F_Sqr[7]!=NONE&&F_Sqr[7]!=WALL)){
										  return TetroCheckRotate(11,12,17,22,&F_Sqr,1);
									}
								}break;case 3:{
									 	if(TetroCheckRotate(11,12,13,16,&F_Sqr,1)) return true;
										if(F_Sqr[11]!=NONE||F_Sqr[16]!=NONE){
										  return TetroCheckRotate(12,13,14,17,&F_Sqr,1);
									}if(F_Sqr[13]!=NONE){
										  return TetroCheckRotate(10,11,12,15,&F_Sqr,1);
									}
								}
						}
				  }break;case -1:{
						switch(imod(TetroRiAng,4)){
								break;case 0:{
									if(TetroCheckRotate(6,7,12,17,&F_Sqr,-1)) return true;	
									if((F_Sqr[6]!=NONE&&F_Sqr[6]!=WALL)||(F_Sqr[7]!=NONE&&F_Sqr[7]!=WALL)){
										  return TetroCheckRotate(11,12,17,22,&F_Sqr,-1);
									}if(F_Sqr[17]!=NONE){
										  return TetroCheckRotate(1,2,7,12,&F_Sqr,-1);
									}
								}break;case 1:{
					 				if(TetroCheckRotate(11,12,13,16,&F_Sqr,-1)) return true;
									if(F_Sqr[11]!=NONE||F_Sqr[16]!=NONE){
										  return TetroCheckRotate(12,13,14,17,&F_Sqr,-1);
									}if(F_Sqr[13]!=NONE){
										  return TetroCheckRotate(10,11,12,15,&F_Sqr,-1);
									}
								}break;case 2:{
									if(TetroCheckRotate(7,12,17,18,&F_Sqr,-1)) return true;
									if(F_Sqr[7]!=NONE&&F_Sqr[7]!=WALL){
										  return TetroCheckRotate(12,17,22,23,&F_Sqr,-1);
									}
								}break;case 3:{
									 	if(TetroCheckRotate(13,16 ,17,18,&F_Sqr,-1)) return true;
										if(F_Sqr[13]!=NONE&&F_Sqr[18]!=NONE&&F_Sqr[8]!=NONE){
										  return TetroCheckRotate(12,15,16,17,&F_Sqr,-1);
										}if(F_Sqr[16]!=NONE){
										  return TetroCheckRotate(14,17,18,19,&F_Sqr,-1);
									
								}
						}
				  }
			 }
				  }
		}break;case O_SHAPE:{
			return true;
		}break;case S_SHAPE:{
			 switch(imod(TetroRiAng,2)){
				break;case 0:{
					Axis=BlockCoor[0];
				}break;case 1:{
					Axis=BlockCoor[2];
				}
			 }
			 Field_Square F_Sqr(m_Field,Axis);
			 switch (dir){
				  break;case 1:{
						switch(imod(TetroRiAng,2)){
								break;case 0:{
									if(TetroCheckRotate(6,11,12,17,&F_Sqr,1)) return true;	
									if(F_Sqr[6]!=NONE&&F_Sqr[6]!=WALL){
										  return TetroCheckRotate(11,16,17,22,&F_Sqr,1);
									}
								}break;case 1:{
					 				if(TetroCheckRotate(12,13,16,17,&F_Sqr,1)) return true;
									if(F_Sqr[13]!=NONE){
										  return TetroCheckRotate(11,12,15,16,&F_Sqr,1);
									}
								}
						}
				  }break;case -1:{
						switch(imod(TetroRiAng,2)){
								break;case 0:{
									if(TetroCheckRotate(6,11,12,17,&F_Sqr,-1)) return true;	
									if(F_Sqr[6]!=NONE&&F_Sqr[6]!=WALL){
										  return TetroCheckRotate(11,16,17,22,&F_Sqr,-1);
									}
								}break;case 1:{
					 				if(TetroCheckRotate(12,13,16,17,&F_Sqr,-1)) return true;
									if(F_Sqr[13]!=NONE){
										  return TetroCheckRotate(11,12,15,16,&F_Sqr,-1);
									}
								}
						 }
				}
		}
		}break;case T_SHAPE:{
			 switch(imod(TetroRiAng,4)){
				break;case 0:{
					Axis=BlockCoor[1];
				}break;case 1:{
					Axis=BlockCoor[1];
				}break;case 2:{
					Axis=BlockCoor[0];
				}break;case 3:{
					Axis=BlockCoor[2];
				}
			}
			 Field_Square F_Sqr(m_Field,Axis);
			 switch (dir){
				  break;case 1:{
						switch(imod(TetroRiAng,4)){
								break;case 0:{
									if(TetroCheckRotate(7,12,13,17,&F_Sqr,1)) return true;	
									if(F_Sqr[7]!=NONE&&F_Sqr[7]!=WALL){
										  return TetroCheckRotate(12,17,18,22,&F_Sqr,1);
									}
								}break;case 1:{
					 				if(TetroCheckRotate(12,16,17,18,&F_Sqr,1)) return true;
									if(F_Sqr[16]!=NONE&&F_Sqr[18]!=NONE&&(F_Sqr[6]!=NONE||F_Sqr[8]!=NONE)){
										  return TetroCheckRotate(7,11,12,13,&F_Sqr,1);
									}if(F_Sqr[6]!=NONE&&F_Sqr[11]!=NONE&&F_Sqr[16]!=NONE){
										  return TetroCheckRotate(13,17,18,19,&F_Sqr,1);
									}
									if(F_Sqr[6]!=NONE&&F_Sqr[11]!=NONE&&F_Sqr[14]!=NONE&&F_Sqr[16]!=NONE){
										  return TetroCheckRotate(13,17,18,19,&F_Sqr,1);
										  //T-Spin mini
									}
								}break;case 2:{
									if(F_Sqr[21]!=NONE&&F_Sqr[22]!=NONE&&F_Sqr[9]&&F_Sqr[14]!=NONE&&F_Sqr[19]!=NONE&&F_Sqr[24]!=NONE){
										  return TetroCheckRotate(13,17,18,23,&F_Sqr,1);
										  //T-Spin mini
									}
									if(TetroCheckRotate(7,11,12,17,&F_Sqr,1)) return true;
									if(F_Sqr[7]!=NONE&&F_Sqr[7]!=WALL){
										  return TetroCheckRotate(12,16,17,22,&F_Sqr,1);
									}
									if(F_Sqr[21]!=NONE&&F_Sqr[23]!=NONE&&F_Sqr[11]!=NONE){
										  return TetroCheckRotate(12,16,17,22,&F_Sqr,1);
									}
								}break;case 3:{
									 if(F_Sqr[8]!=NONE&&F_Sqr[16]!=NONE&&F_Sqr[18]!=NONE){
										  return TetroCheckRotate(11,12,13,17,&F_Sqr,1);
										}	
									 if(TetroCheckRotate(11,12,13,17,&F_Sqr,1)) return true;
									 if(F_Sqr[13]!=NONE){
										  return TetroCheckRotate(10,11,12,16,&F_Sqr,1);
									}
								}
						}
				  }break;case -1:{
						switch(imod(TetroRiAng,4)){
								break;case 0:{
									if(TetroCheckRotate(7,11,12,17,&F_Sqr,-1)) return true;	
									if(F_Sqr[7]!=NONE&&F_Sqr[7]!=WALL){
										  return TetroCheckRotate(12,16,17,22,&F_Sqr,-1);
									}
								}break;case 1:{
					 				if(F_Sqr[6]!=NONE&&F_Sqr[16]!=NONE&&F_Sqr[18]!=NONE){
										  return TetroCheckRotate(11,12,13,17,&F_Sqr,-1);
										  //T-Spin
									}
									if(TetroCheckRotate(11,12,13,17,&F_Sqr,-1)) return true;
									if(F_Sqr[11]!=NONE){
										  return TetroCheckRotate(12,13,14,18,&F_Sqr,-1);
									}
								}break;case 2:{
									if(F_Sqr[5]!=NONE&&F_Sqr[10]!=NONE&&F_Sqr[15]!=NONE&&F_Sqr[20]!=NONE&&F_Sqr[22]!=NONE&&F_Sqr[23]!=NONE){
										 return TetroCheckRotate(11,16,17,21,&F_Sqr,-1);
										 //T-Spin mini
									}
									if(F_Sqr[21]!=NONE&&F_Sqr[23]!=NONE&&(F_Sqr[11]!=NONE||F_Sqr[13]!=NONE)){
										  return TetroCheckRotate(12,17,18,22,&F_Sqr,-1);
										  //t-sPIN
									}if(TetroCheckRotate(7,12,13,17,&F_Sqr,-1)) return true;
									if(F_Sqr[7]!=NONE&&F_Sqr[7]!=WALL){
										  return TetroCheckRotate(12,17,18,22,&F_Sqr,1);
									}
								}break;case 3:{
									 	if(TetroCheckRotate(12,16,17,18,&F_Sqr,-1)) return true;
										if(F_Sqr[16]!=NONE&&F_Sqr[18]!=NONE&&(F_Sqr[6]!=NONE||F_Sqr[8]!=NONE)){
										  return TetroCheckRotate(7,11,12,13,&F_Sqr,-1);
										}if(F_Sqr[18]!=NONE){
										  return TetroCheckRotate(11,15,16,17,&F_Sqr,-1);
										}
										if(F_Sqr[8]!=NONE&&F_Sqr[10]!=NONE&&F_Sqr[13]!=NONE&&F_Sqr[18]!=NONE){
										  return TetroCheckRotate(11,15,16,17,&F_Sqr,-1);
										  //T-Spin mini
										}
								}
						}
				  }
				  }
		}break;case Z_SHAPE:{
			 switch(imod(TetroRiAng,2)){
				break;case 0:{
					Axis=BlockCoor[1];
				}break;case 1:{
					Axis=BlockCoor[1];
				}
			 }
			 Field_Square F_Sqr(m_Field,Axis);
			 switch (dir){
				  break;case 1:{
						switch(imod(TetroRiAng,2)){
								break;case 0:{
									if(TetroCheckRotate(8,12,13,17,&F_Sqr,1)) return true;	
									if(F_Sqr[8]!=NONE&&F_Sqr[8]!=WALL){
										  return TetroCheckRotate(13,17,18,22,&F_Sqr,1);
									}
								}break;case 1:{
					 				if(TetroCheckRotate(11,12,17,18,&F_Sqr,1)) return true;
									if(F_Sqr[11]!=NONE){
										  return TetroCheckRotate(12,13,18,19,&F_Sqr,1);
									}
								}
						}
				  }break;case -1:{
						switch(imod(TetroRiAng,2)){
								break;case 0:{
									if(TetroCheckRotate(8,12,13,17,&F_Sqr,-1)) return true;	
									if(F_Sqr[8]!=NONE&&F_Sqr[8]!=WALL){
										  return TetroCheckRotate(13,17,18,22,&F_Sqr,-1);
									}
								}break;case 1:{
					 				if(TetroCheckRotate(11,12,17,18,&F_Sqr,-1)) return true;
									if(F_Sqr[11]!=NONE){
										  return TetroCheckRotate(12,13,18,19,&F_Sqr,-1);
									}
								}
						 }
				}
		}
		}
	}
}
bool Tetromino::TetroMove(Direction dir){
	 int counter=0;
	 std::vector<Coordinate> ConsiderBlockCoor;
	 bool ReturnBool;

	 switch (dir)
	 {
	 break;case UP:{
		  for(int d=0;d<4;d++){
				if(!IsThereTetro(BlockCoor[d].x,BlockCoor[d].y+1)){
					 ConsiderBlockCoor.push_back(BlockCoor[d]);
	 		  }
		  }
		  for(int b=0;b<ConsiderBlockCoor.size();b++){
				if((m_Field->IsThereBlock(ConsiderBlockCoor[b].x,ConsiderBlockCoor[b].y+1)&&
					 !m_Field->IsThereCurrentTetro(ConsiderBlockCoor[b].x,ConsiderBlockCoor[b].y+1))&&
					 ConsiderBlockCoor[b].y<FIELD_HEIGHT_BLOCK){
					 ReturnBool=false;
					 goto end;
				}
		  }
		  ReturnBool=true;
			for(int d=0;d<4;d++){
				 BlockCoor[d].y++;
			}
	 }break;case RIGHT:{
		  for(int d=0;d<4;d++){
				if(!IsThereTetro(BlockCoor[d].x+1,BlockCoor[d].y)){
					 ConsiderBlockCoor.push_back(BlockCoor[d]);
	 		  }
		  }
		  for(int b=0;b<ConsiderBlockCoor.size();b++){
				if((m_Field->IsThereBlock(ConsiderBlockCoor[b].x+1,ConsiderBlockCoor[b].y)&&
					 !m_Field->IsThereCurrentTetro(ConsiderBlockCoor[b].x+1,ConsiderBlockCoor[b].y))&&
					 ConsiderBlockCoor[b].y<FIELD_HEIGHT_BLOCK
					 /*&&BlockCoor[b].y<FIELD_HEIGHT_BLOCK)||ConsiderBlockCoor[b].x+1>=FIELD_WIDTH_BLOCK*/){
					 ReturnBool=false;
					 goto end;
				}
		  }
		  ReturnBool=true;
		  for(int d=0;d<4;d++){
				 BlockCoor[d].x++;
		  }
		  
	 }break;case DOWN:{
		  for(int d=0;d<4;d++){
				if(!IsThereTetro(BlockCoor[d].x,BlockCoor[d].y-1)||BlockCoor[d].y>=FIELD_HEIGHT_BLOCK){
					 ConsiderBlockCoor.push_back(BlockCoor[d]);
	 		  }
		  }
		  for(int b=0;b<ConsiderBlockCoor.size();b++){
				if((m_Field->IsThereBlock(ConsiderBlockCoor[b].x,ConsiderBlockCoor[b].y-1)&&
					 !m_Field->IsThereCurrentTetro(ConsiderBlockCoor[b].x,ConsiderBlockCoor[b].y-1))&&
					 ConsiderBlockCoor[b].y<FIELD_HEIGHT_BLOCK
					 /*&&BlockCoor[b].y<FIELD_HEIGHT_BLOCK*/){
					 ReturnBool=false;
					 goto end;
				}
		  }
		  ReturnBool=true;
		  for(int d=0;d<4;d++){
					 BlockCoor[d].y--;
		  }
	 }break;case LEFT:{
		  for(int d=0;d<4;d++){
				if(!IsThereTetro(BlockCoor[d].x-1,BlockCoor[d].y)){
					 ConsiderBlockCoor.push_back(BlockCoor[d]);
	 		  }
		  }
		  for(int b=0;b<ConsiderBlockCoor.size();b++){
				if((m_Field->IsThereBlock(ConsiderBlockCoor[b].x-1,ConsiderBlockCoor[b].y)&&
					 !m_Field->IsThereCurrentTetro(ConsiderBlockCoor[b].x-1,ConsiderBlockCoor[b].y))&&
					 ConsiderBlockCoor[b].y<FIELD_HEIGHT_BLOCK
					 /*&&BlockCoor[b].y<FIELD_HEIGHT_BLOCK)
					 ||ConsiderBlockCoor[b].x-1<0)*/){
					 /*ReturnBool=false;
					 goto end;*/
					return false;
				}
		  }
		  ReturnBool=true;
		  for(int d=0;d<4;d++){
					 BlockCoor[d].x--;
		  }
		  return true;
	 }
	 }
	 end:
	 return ReturnBool;
}
bool Tetromino::TetroMoveByCoor(Coordinate coor1,Coordinate coor2,Coordinate coor3,Coordinate coor4,int dir){
	 if((m_Field->GetCoorStatus(coor1)==NONE||coor1.y>=FIELD_HEIGHT_BLOCK||m_Field->IsThereCurrentTetro(coor1))&&
		  (m_Field->GetCoorStatus(coor2)==NONE||coor2.y>=FIELD_HEIGHT_BLOCK||m_Field->IsThereCurrentTetro(coor2))&&
		  (m_Field->GetCoorStatus(coor3)==NONE||coor3.y>=FIELD_HEIGHT_BLOCK||m_Field->IsThereCurrentTetro(coor3))&&
		  (m_Field->GetCoorStatus(coor4)==NONE||coor4.y>=FIELD_HEIGHT_BLOCK||m_Field->IsThereCurrentTetro(coor4))){
		  BlockCoor[0]=coor1;
		  BlockCoor[1]=coor2;
		  BlockCoor[2]=coor3;
		  BlockCoor[3]=coor4;
		  TetroRiAng+=dir;
		return true;
	 }else return false;	 
}
bool Tetromino::TetroMoveByCoor(Coordinate* coor,int dir){
	 return TetroMoveByCoor(coor[0],coor[1],coor[2],coor[3],dir);
}
bool Tetromino::TetroCheckRotate(int CoorZeroNum,int CoorOneNum,int CoorTwoNum,int CoorThreeNum,Field_Square* Sqr,int dir){
	if((Sqr->GetArrayNum(CoorZeroNum)==NONE||Sqr->SqToField(CoorZeroNum).y>=FIELD_HEIGHT_BLOCK)
		 &&(Sqr->GetArrayNum(CoorOneNum)==NONE||Sqr->SqToField(CoorOneNum).y>=FIELD_HEIGHT_BLOCK)
		 &&(Sqr->GetArrayNum(CoorTwoNum)==NONE||Sqr->SqToField(CoorTwoNum).y>=FIELD_HEIGHT_BLOCK)
		 &&(Sqr->GetArrayNum(CoorThreeNum)==NONE||Sqr->SqToField(CoorThreeNum).y>=FIELD_HEIGHT_BLOCK)){
		BlockCoor[0]=Sqr->SqToField(CoorZeroNum);
		BlockCoor[1]=Sqr->SqToField(CoorOneNum);
		BlockCoor[2]=Sqr->SqToField(CoorTwoNum);
		BlockCoor[3]=Sqr->SqToField(CoorThreeNum);
		TetroRiAng+=dir;
		return true;
	}else{return false;}
}
bool Tetromino::GetIstouched(){
	 std::vector<Coordinate> ConsiderBlockCoor; 
	 for(int d=0;d<4;d++){
		  if(!IsThereTetro(BlockCoor[d].x,BlockCoor[d].y-1)/*&&BlockCoor[d].y<=FIELD_HEIGHT_BLOCK*/){
				ConsiderBlockCoor.push_back(BlockCoor[d]);
		  }
	 }
	 for(int b=0;b<ConsiderBlockCoor.size();b++){
		  if(m_Field->IsThereBlock(ConsiderBlockCoor[b].x,ConsiderBlockCoor[b].y-1)&&
				/*ConsiderBlockCoor[b].y<FIELD_HEIGHT_BLOCK&&*/
				!m_Field->IsThereCurrentTetro(ConsiderBlockCoor[b].x,ConsiderBlockCoor[b].y-1))return true;
	 }
	 return false;	 
}
Tetro_Shape Tetromino::GetShape(){return Shape;}
Coordinate Tetromino::GetCoor(int n){return BlockCoor[n];}
bool Tetromino::IsThereTetro(int x,int y){
	 Coordinate coor;
	 coor.x=x;
	 coor.y=y;
	 for(int d=0;d<4;d++){
		  if(BlockCoor[d]==coor)return true;
	 }
	 return false;
}
bool Tetromino::IsThereTetro(Coordinate coor){
	 return IsThereTetro(coor.x,coor.y);
}




Field_Square::Field_Square(Field *field,Coordinate axis){
	Axis=axis;
	for(int a=0;a<FIELD_SQUARE_SIZE*FIELD_SQUARE_SIZE;a++){
		/*if(field->IsThereCurrentTetro(axis.x+a%FIELD_SQUARE_SIZE-1,axis.y-quot(a,FIELD_SQUARE_SIZE)+1))BlockArray[a]=NONE;
		else{BlockArray[a]=field->GetCoorStatus(axis.x+a%FIELD_SQUARE_SIZE-1,axis.y-quot(a,FIELD_SQUARE_SIZE)+1);}*/
		 if(field->GetCurrentTetroShape()!=EMPTY){
				if(field->IsThereCurrentTetro(axis.x+a%FIELD_SQUARE_SIZE-int(FIELD_SQUARE_SIZE/2),axis.y-quot(a,FIELD_SQUARE_SIZE)+int(FIELD_SQUARE_SIZE/2)))BlockArray[a]=NONE;
				else{BlockArray[a]=field->GetCoorStatus(axis.x+a%FIELD_SQUARE_SIZE-int(FIELD_SQUARE_SIZE/2),axis.y-quot(a,FIELD_SQUARE_SIZE)+int(FIELD_SQUARE_SIZE/2));}
		 }else {BlockArray[a]=field->GetCoorStatus(axis.x+a%FIELD_SQUARE_SIZE-int(FIELD_SQUARE_SIZE/2),axis.y-quot(a,FIELD_SQUARE_SIZE)+int(FIELD_SQUARE_SIZE/2));}
	}
}
Field_Square::Field_Square(Field *field,int x,int y){
	 Coordinate axis;
	 axis.x=x;
	 axis.y=y;
	 Axis=axis;
	for(int a=0;a<FIELD_SQUARE_SIZE*FIELD_SQUARE_SIZE;a++){
		/*if(field->IsThereCurrentTetro(axis.x+a%FIELD_SQUARE_SIZE-1,axis.y-quot(a,FIELD_SQUARE_SIZE)+1))BlockArray[a]=NONE;
		else{BlockArray[a]=field->GetCoorStatus(axis.x+a%FIELD_SQUARE_SIZE-1,axis.y-quot(a,FIELD_SQUARE_SIZE)+1);}*/
		 if(field->GetCurrentTetroShape()!=EMPTY){
				if(field->IsThereCurrentTetro(axis.x+a%FIELD_SQUARE_SIZE-int(FIELD_SQUARE_SIZE/2),axis.y-quot(a,FIELD_SQUARE_SIZE)+int(FIELD_SQUARE_SIZE/2)))BlockArray[a]=NONE;
				else{BlockArray[a]=field->GetCoorStatus(axis.x+a%FIELD_SQUARE_SIZE-int(FIELD_SQUARE_SIZE/2),axis.y-quot(a,FIELD_SQUARE_SIZE)+int(FIELD_SQUARE_SIZE/2));}
		 }else {BlockArray[a]=field->GetCoorStatus(axis.x+a%FIELD_SQUARE_SIZE-int(FIELD_SQUARE_SIZE/2),axis.y-quot(a,FIELD_SQUARE_SIZE)+int(FIELD_SQUARE_SIZE/2));}
	}
	 //Field_Square(field,tempcoor);
}
Block_Color Field_Square::GetArrayNum(int n){return BlockArray[n];}
Coordinate Field_Square::SqToField(int n){
	Coordinate ReturnCoor;
	ReturnCoor.x=Axis.x+(n%FIELD_SQUARE_SIZE)-int(FIELD_SQUARE_SIZE/2);
	ReturnCoor.y=Axis.y-quot(n,FIELD_SQUARE_SIZE)+int(FIELD_SQUARE_SIZE/2);
	return ReturnCoor;
}
int Tetromino::GetTetroRiang(){return TetroRiAng;}
Block_Color Field_Square::operator[](int n){return GetArrayNum(n);}
void Field_Square::SetAxis(int x,int y){
	 Coordinate tempcoor;
	 tempcoor.x=x;
	 tempcoor.y=y;
	 Axis=tempcoor;
}
void Field_Square::SetAxis(Coordinate coor){SetAxis(coor.x,coor.y);}


void SetBackGroundWaitingTetro(Tetro_Shape* BackGroundWaitingTetro){
	 std::vector<int> OrdinalNum;
	 for(int d=0;d<BACKGROUND_WAITING_NUM;d++)OrdinalNum.push_back(d);
	 for(int d=0;d<7;d++){
		  for(int b=0;b<BACKGROUND_WAITING_NUM/7;b++){
				int rand=GetRand(OrdinalNum.size()-1);
				BackGroundWaitingTetro[ OrdinalNum[rand] ]=static_cast<Tetro_Shape>(d+1);
				auto OrdinalNumErase=OrdinalNum.begin();
				for(int d=0;d<rand;d++)OrdinalNumErase++;
				OrdinalNum.erase(OrdinalNumErase);
				//BackGroundWaitingTetro[BACKGROUND_WAITING_NUM/7*d+b]=static_cast<Tetro_Shape>(d+1);
		  }
	}
	//std::shuffle(BackGroundWaitingTetro.begin(),BackGroundWaitingTetro.end(),GetRand(RAND_MAX));
	
	//for(int d=0;d<BACKGROUND_WAITING_NUM;d++)BackGroundWaitingTetro[d]=O_SHAPE;
}

Field::Field(){
	for(int x=0;x<FIELD_WIDTH_BLOCK;x++){
		for(int y=0;y<FIELD_HEIGHT_BLOCK;y++){
			field[x][y]=NONE;
		}
	}
	/*for(int x=7;x<FIELD_WIDTH_BLOCK;x++){
		 for(int y=0;y<FIELD_HEIGHT_BLOCK-2;y++){
			  field[x][y]=I_COLOR;
		 }
	}*/
	/*for(int d=0;d<FIELD_HEIGHT_BLOCK;d++){
		 field[3][d]=I_COLOR;
		 field[7][d]=I_COLOR;
	}*/
	CurrentTetromino=NULL;
	CurrentStatus=WAITING;
	//IsTetrominoFalling=false;
	TotalDisappLine=0;
	TotalScore=0;
	FallingFlame=0;
	TetroTouchingTime=0;
	LimitTouchingTime=30;
	WaitingTime=0;
	LimitWaitingTime=30;
	LineBreakingTime=0;
	HoldingTetro=EMPTY;
	IsTetroSoftdropping=false;
	IsTetroHarddropping=false;
	ScoreFontHandle=CreateFontToHandle("PixelMplus12",12,-1,-1);
	for(int d=0;d<WAITING_TETRO_NUM;d++){
		 WaitingTetro[d]=EMPTY;
	 }
	DATEDATA date;
	GetDateTime(&date);
	RandSeed=date.Sec+date.Min;
	CurrentTetroNum=0;
	SRand(RandSeed);
	FallG=0.02;
	
	BackWaitingTetroPosition=WAITING_TETRO_NUM-1;
	SetBackGroundWaitingTetro(BackGroundWaitingTetro);
}
Block_Color Field::GetCoorStatus(int x,int y){
	if(x<0 || x>=FIELD_WIDTH_BLOCK || y<0 || y>=FIELD_HEIGHT_BLOCK){
		return WALL;
	}
	else{
		return field[x][y];
	}
}
Block_Color Field::GetCoorStatus(Coordinate cor){
	return GetCoorStatus(cor.x,cor.y);
}
void Field::SetNone(int x,int y){field[x][y]=NONE;}
void Field::SetNone(Coordinate coor){field[coor.x][coor.y]=NONE;}
//Field Field::SetMillerField(){
//	Field ReturnField;
//
//	ReturnField=*this;
//	for(int d=0;d<4;d++){
//		ReturnField.SetNone(CurrentTetromino->GetCoor(d));
//	}
//	return ReturnField;
//}
void Field::SetWaitingTetro(){
	if(BackWaitingTetroPosition==BACKGROUND_WAITING_NUM){
		 /*std::vector<int> OrdinalNum(BACKGROUND_WAITING_NUM);
		 std::vector<int>::iterator OrdinalNumErase;
		 for(int d=0;d<BACKGROUND_WAITING_NUM;d++) OrdinalNum[d]=d;

		 for(int d=0;d<7;d++){
			  for(int b=0;b<BACKGROUND_WAITING_NUM/7;b++){
					int rand=GetRand(OrdinalNum.size()-1);
					BackGroundWaitingTetro[ OrdinalNum[rand] ]=static_cast<Tetro_Shape>(d+1);
					OrdinalNumErase=OrdinalNum.begin();
					for(int d=0;d<rand;d++)OrdinalNumErase++;
					OrdinalNum.erase(OrdinalNumErase);
			  }
		 }*/
		 SetBackGroundWaitingTetro(BackGroundWaitingTetro);
		 BackWaitingTetroPosition=WAITING_TETRO_NUM-1;
	}
	for(int d=0;d<WAITING_TETRO_NUM;d++){
		 WaitingTetro[d]=BackGroundWaitingTetro[BackWaitingTetroPosition-(WAITING_TETRO_NUM-d-1)];
	}
	HWField.SetShape(HoldingTetro,WaitingTetro);
}
Tetro_Shape Field::SetHoldingTetro(){
	if(!IsAlreadyHolded){
		for(int d=0;d<4;d++){
			field[CurrentTetromino->GetCoor(d).x][CurrentTetromino->GetCoor(d).y]=NONE;
		}
		Tetro_Shape ReservedShape=HoldingTetro;	
	 	HoldingTetro=CurrentTetromino->GetShape();
	 	delete CurrentTetromino;
	 	CurrentTetromino=NULL;
	  	CurrentStatus=WAITING;
		IsAlreadyHolded=true;
	 	return ReservedShape;
	}else return EMPTY;
}
Tetro_Shape Field::GetWaitingTetro(int n){return WaitingTetro[n];}
bool Field::GetIsAlreadyHolded(){return IsAlreadyHolded;}
bool Field::SetCurrentTetrominoAndIsGameOver(Tetromino* tetro){
	CurrentTetromino=tetro;
	Block_Color color;
	//WaitingTetro[0]=EMPTY;
	BackWaitingTetroPosition++;
	//if(BackWaitingTetroPosition==BACKGROUND_WAITING_NUM)BackWaitingTetroPosition=WAITING_TETRO_NUM-1;
	IsTetroSoftdropping=false;
	IsTetroHarddropping=false;
	IsAlreadyHolded=false;
	CurrentTetroNum++;
	CalcHeightBar();
	
	switch (CurrentTetromino->GetShape()){
		break;case I_SHAPE: color=I_COLOR;
		break;case J_SHAPE: color=J_COLOR;
		break;case L_SHAPE: color=L_COLOR;
		break;case O_SHAPE: color=O_COLOR;
		break;case S_SHAPE: color=S_COLOR;
		break;case T_SHAPE: color=T_COLOR;
		break;case Z_SHAPE: color=Z_COLOR;
	}
	for(int d=0;d<4;d++){
		if(IsThereBlock(CurrentTetromino->GetCoor(d)))return true;
	}
	for(int d=0;d<4;d++){
		field[CurrentTetromino->GetCoor(d).x][CurrentTetromino->GetCoor(d).y]=color;
	}
	return false;
}
bool Field::SetCurrentTetrominoByHoldingAndIsGameOver(Tetromino* tetro){
	CurrentTetromino=tetro;
	Block_Color color;
	IsTetroSoftdropping=false;
	IsTetroHarddropping=false;
	IsAlreadyHolded=false;
	CurrentTetroNum++;
	CalcHeightBar();

	switch (CurrentTetromino->GetShape()){
		break;case I_SHAPE: color=I_COLOR;
		break;case J_SHAPE: color=J_COLOR;
		break;case L_SHAPE: color=L_COLOR;
		break;case O_SHAPE: color=O_COLOR;
		break;case S_SHAPE: color=S_COLOR;
		break;case T_SHAPE: color=T_COLOR;
		break;case Z_SHAPE: color=Z_COLOR;
	}
	for(int d=0;d<4;d++){
		if(IsThereBlock(CurrentTetromino->GetCoor(d)))return true;
	}
	for(int d=0;d<4;d++){
		field[CurrentTetromino->GetCoor(d).x][CurrentTetromino->GetCoor(d).y]=color;
	}
	return false;
}
void Field::SetLimitTouchingTime(int LimitTime){
	LimitTouchingTime=LimitTime;
}
//void Field::SetFallSpeed(int Speed){FallSpeed=Speed;}
void Field::SetFallG(){
	 /*if(quot(TotalDisappLine,10)<3)FallG=0.02;
	 if(3<=quot(TotalDisappLine,10)&&quot(TotalDisappLine,10)<5)FallG=0.05;
	 if(5<=quot(TotalDisappLine,10)&&quot(TotalDisappLine,10)<7)FallG=0.10;
	 if(7<=quot(TotalDisappLine,10)&&quot(TotalDisappLine,10)<10)FallG=0.50;
	 if(10<=quot(TotalDisappLine,10)&&quot(TotalDisappLine,10)<12)FallG=1;
	 if(12<=quot(TotalDisappLine,10)&&quot(TotalDisappLine,10)<15)FallG=3;
	 if(15<=quot(TotalDisappLine,10)&&quot(TotalDisappLine,10)<17)FallG=7;
	 if(17<=quot(TotalDisappLine,10)&&quot(TotalDisappLine,10)<20)FallG=10;
	 if(20<=quot(TotalDisappLine,10))FallG=20;*/
}
bool Field::MoveCurrentTetromino(Direction dir){
	for(int d=0;d<4;d++){
		if(CurrentTetromino->GetCoor(d).x>=0&&CurrentTetromino->GetCoor(d).x<FIELD_WIDTH_BLOCK
			&&CurrentTetromino->GetCoor(d).y>=0&&CurrentTetromino->GetCoor(d).y<FIELD_HEIGHT_BLOCK)
		 field[CurrentTetromino->GetCoor(d).x][CurrentTetromino->GetCoor(d).y]=NONE;
	}
	bool ReturnBool;
	Block_Color color;

	ReturnBool=CurrentTetromino->TetroMove(dir);
	
	switch (CurrentTetromino->GetShape()){
		break;case I_SHAPE: color=I_COLOR;
		break;case J_SHAPE: color=J_COLOR;
		break;case L_SHAPE: color=L_COLOR;
		break;case O_SHAPE: color=O_COLOR;
		break;case S_SHAPE: color=S_COLOR;
		break;case T_SHAPE: color=T_COLOR;
		break;case Z_SHAPE: color=Z_COLOR;
	}
	 for(int d=0;d<4;d++){
		  if(CurrentTetromino->GetCoor(d).x>=0&&CurrentTetromino->GetCoor(d).x<FIELD_WIDTH_BLOCK&&
				CurrentTetromino->GetCoor(d).y>=0&&CurrentTetromino->GetCoor(d).y<FIELD_HEIGHT_BLOCK){
				field[CurrentTetromino->GetCoor(d).x][CurrentTetromino->GetCoor(d).y]=color;
		  }
	}
		
	
	return ReturnBool;
}
int Field::RenewCurrentStatus(){
	if(CurrentStatus==BREAKING){return 3;}
	if(CurrentTetromino==NULL){CurrentStatus=WAITING;return 0;}
	else if(CurrentTetromino->GetIstouched()==true){CurrentStatus=TOUCHING;return 2;}
	else if(CurrentTetromino->GetIstouched()==false){CurrentStatus=FALLING;return 1;}
	else{CurrentStatus=EXCEP;return -1;}
}
void Field::RenewTouchingStatus(){
	TetroTouchingTime++;
	

	if(TetroTouchingTime>LimitTouchingTime&&CurrentTetromino->GetIstouched()){
		int counter=0;
		int d=0;
		
		TetroTouchingTime=0;
		delete CurrentTetromino;
		CurrentTetromino=NULL;
		for(int y=0;y<FIELD_HEIGHT_BLOCK;y++){
			for(int x=0;x<FIELD_WIDTH_BLOCK;x++){
				if(field[x][y]!=NONE){counter++;}
			}
			if(counter==FIELD_WIDTH_BLOCK){
				CurrentStatus=BREAKING;
				breakingLine.push_back(y);
				d++;
			}
			counter=0;
		}
	}
}
void Field::RenewWaitingStatus(){
	 //if(IsTetroHarddropping)WaitingTime=LimitWaitingTime;
	 WaitingTime++;
	 if(WaitingTime>LimitWaitingTime)WaitingTime=0; 
}
bool Field::RotateCurrentTetromino(int riang){
	for(int d=0;d<4;d++){
		if(CurrentTetromino->GetCoor(d).x>=0&&CurrentTetromino->GetCoor(d).x<FIELD_WIDTH_BLOCK
			&&CurrentTetromino->GetCoor(d).y>=0&&CurrentTetromino->GetCoor(d).y<FIELD_HEIGHT_BLOCK)
		 field[CurrentTetromino->GetCoor(d).x][CurrentTetromino->GetCoor(d).y]=NONE;
	}
	bool ReturnBool;
	Block_Color color;
	
	ReturnBool=CurrentTetromino->TetroRotate(riang);
	
	switch (CurrentTetromino->GetShape()){
		break;case I_SHAPE: color=I_COLOR;
		break;case J_SHAPE: color=J_COLOR;
		break;case L_SHAPE: color=L_COLOR;
		break;case O_SHAPE: color=O_COLOR;
		break;case S_SHAPE: color=S_COLOR;
		break;case T_SHAPE: color=T_COLOR;
		break;case Z_SHAPE: color=Z_COLOR;
	}
	for(int d=0;d<4;d++){
		if(CurrentTetromino->GetCoor(d).x>=0&&CurrentTetromino->GetCoor(d).x<FIELD_WIDTH_BLOCK&&
		  CurrentTetromino->GetCoor(d).y>=0&&CurrentTetromino->GetCoor(d).y<FIELD_HEIGHT_BLOCK){
			field[CurrentTetromino->GetCoor(d).x][CurrentTetromino->GetCoor(d).y]=color;
		}
	}
	/*for(int d=0;d<4;d++){
		DrawFormatString(0,50*(d+5),GetColor(255,255,255),"BlockCoor[%d]=(%d,%d)",d,CurrentTetromino->GetCoor(d).x,CurrentTetromino->GetCoor(d).y);
	}*/
	
	return ReturnBool;
}
bool Field::SoftdropCurrentTetromino(){
	if(FallG<1.0){
		IsTetroSoftdropping=true;
	 	return this->MoveCurrentTetromino(DOWN);
	}else return false;
}
void Field::MiddleDropCurrentTetromino(){
	 for(int d=0;d<15;d++){
		  MoveCurrentTetromino(DOWN);
	 }
}
void Field::HarddropCurrentTetromino(){
	 for(int d=0;d<FIELD_HEIGHT_BLOCK;d++){
		  MoveCurrentTetromino(DOWN);
	 }
	 IsTetroHarddropping=true;
	 TetroTouchingTime=LimitTouchingTime;
	 WaitingTime=LimitWaitingTime;	
}
void Field::AutoFallTetro(){
	FallingFlame++;
	int counter=0;
	int d=0;
	while(d<int(FallG*FallingFlame)){
		 MoveCurrentTetromino(DOWN);
		 counter++;
		 d++;
	}
	if(counter!=0)FallingFlame=0;
}
void Field::RenewDeleteLineStatus(){
	LineBreakingTime++;
	int d=0;
	int counter=0;
	

	if(LineBreakingTime>LINE_BREAKING_TIME){
		LineBreakingTime=0;
			for(int x=0;x<breakingLine.size();x++){
				for(int d=0;d<FIELD_WIDTH_BLOCK;d++){
					field[d][breakingLine[x]]=NONE;
				}
				TotalDisappLine++;
			}
			SetFallG();
			/*for(int y=0;y<FIELD_HEIGHT_BLOCK;y++){
				for(int x=0;x<FIELD_WIDTH_BLOCK;x++){
					if(field[x][y]==NONE) counter++;
				}
				if(counter==FIELD_WIDTH_BLOCK){
					for(int y2=y+1;y2<FIELD_HEIGHT_BLOCK;y2++){
						for(int x=0;x<FIELD_WIDTH_BLOCK;x++){
							if(field[x][y2]==NONE)counter++;
						}
						if(counter<FIELD_WIDTH_BLOCK){
							for(int x=0;x<FIELD_WIDTH_BLOCK;x++){
								field[x][y]=field[x][y2];
								field[x][y2]=NONE;
							}
							break;
						}
						counter=0;
					}
				}
				counter=0;
			}*/
			std::vector<int> NewField;//field[]の消されたライン以外
			for(int y=0;y<FIELD_HEIGHT_BLOCK;y++){
				 for(int d=0;d<breakingLine.size();d++){
					  if(breakingLine[d]==y){counter++;}
				 }
				 if(counter==0){
					  NewField.push_back(y);
				 }
				 counter=0;
			}
			for(int y2=0;y2<FIELD_HEIGHT_BLOCK;y2++){
				 if(y2<NewField.size()){
					  for(int x=0;x<FIELD_WIDTH_BLOCK;x++){
							field[x][y2]=field[x][NewField[y2]];
					  }
				 }else{
					  for(int x=0;x<FIELD_WIDTH_BLOCK;x++){
							field[x][y2]=NONE;
					  }
				}
			}
				 
			breakingLine.clear();
			CurrentStatus=WAITING;
	}
	
}
void Field::DrawField(){
	 for(int x=0;x<FIELD_WIDTH_BLOCK;x++){
			for(int y=0;y<FIELD_HEIGHT_BLOCK;y++){
				int color;
				switch (field[x][y]){
					break;case NONE:color=NONE_COLOR;
					break;case I_COLOR:color=I_SHAPE_COLOR;
					break;case J_COLOR:color=J_SHAPE_COLOR;
					break;case L_COLOR:color=L_SHAPE_COLOR;
					break;case O_COLOR:color=O_SHAPE_COLOR;
					break;case S_COLOR:color=S_SHAPE_COLOR;
					break;case T_COLOR:color=T_SHAPE_COLOR;
					break;case Z_COLOR:color=Z_SHAPE_COLOR;
					//break;case BREAKING_COLOR:color=BREAKING_SHAPE_COLOR;
				}
				DrawBox(FIELD_X_COOR+BLOCK_SIZE*x,FIELD_Y_COOR+FIELD_HEIGHT-BLOCK_SIZE*(y+1),FIELD_X_COOR+BLOCK_SIZE*(x+1),FIELD_Y_COOR+FIELD_HEIGHT-BLOCK_SIZE*y,color,true);
			}
		}
}
void Field::DrawBreakingBox(){
	int ColorFact=255-(255-NONE_COLOR_FACT)*LineBreakingTime/LINE_BREAKING_TIME;
	for(int d=0;d<breakingLine.size();d++){
		DrawBox(FIELD_X_COOR,FIELD_Y_COOR+FIELD_HEIGHT-BLOCK_SIZE*(breakingLine[d]+1),
		FIELD_X_COOR+FIELD_WIDTH,
		FIELD_Y_COOR+FIELD_HEIGHT-BLOCK_SIZE*breakingLine[d],
		GetColor(ColorFact,ColorFact,ColorFact),true);
	}
}
void Field::DrawGauge(){
	if(CurrentStatus==TOUCHING){
		if(!IsTetroHarddropping){	 
		 DrawBox(FIELD_X_COOR,FIELD_Y_COOR+FIELD_HEIGHT+FIELD_GAUGE_SPACE,
				FIELD_X_COOR+(FIELD_WIDTH)/2,
				FIELD_Y_COOR+FIELD_HEIGHT+FIELD_GAUGE_SPACE+GAUGE_SIZE,
				WaitingGaugeColor,true);
		}if(TetroTouchingTime>1&&!IsTetroHarddropping){
		 DrawBox(FIELD_X_COOR+FIELD_WIDTH/2,FIELD_Y_COOR+FIELD_HEIGHT+FIELD_GAUGE_SPACE,
			 FIELD_X_COOR+FIELD_WIDTH/2+(FIELD_WIDTH*(1-double(TetroTouchingTime)/double(LimitTouchingTime)))/2,
			 FIELD_Y_COOR+FIELD_HEIGHT+FIELD_GAUGE_SPACE+GAUGE_SIZE,
			 TouchingGaugeColor,true);
		}
		//DrawFormatString(FIELD_X_COOR,FIELD_Y_COOR+FIELD_HEIGHT+FIELD_GAUGE_SPACE,GetColor(255,255,255),"%d/%d",TetroTouchingTime,LimitTouchingTime);
	}if(CurrentStatus==WAITING&&WaitingTime<LimitWaitingTime){
		DrawBox(FIELD_X_COOR,FIELD_Y_COOR+FIELD_HEIGHT+FIELD_GAUGE_SPACE,
			 FIELD_X_COOR+(FIELD_WIDTH*(1-double(WaitingTime)/double(LimitWaitingTime)))/2,
			 FIELD_Y_COOR+FIELD_HEIGHT+FIELD_GAUGE_SPACE+GAUGE_SIZE,
			 WaitingGaugeColor,true);
	}
}
void Field::DrawHWField(){
	HWField.DrawHWField();
}
void Field::DrawFallPoint(){
	 Coordinate FallPointCoor[4];
	 int counter=0;
	 int color;


	 /*for(int d=0;d<4;d++){
		  FallPointCoor[d].x=CurrentTetromino->GetCoor(d).x;
		  FallPointCoor[d].y=CurrentTetromino->GetCoor(d).y;
	 }
	 while(1){
		  for(int d=0;d<4;d++){
				if(IsThereBlock(FallPointCoor[d])&&!IsThereCurrentTetro(FallPointCoor[d])){
					 break;
				}
				counter++;
		  }
		  if(counter==4){
				for(int b=0;b<4;b++){
					--FallPointCoor[b].y;
				}
		  }else{break;}
		  counter=0;
	 }
	 for(int b=0;b<4;b++){
		  ++FallPointCoor[b].y;
	 }*/
	 GetTetroLimitFallCoor(CurrentTetromino->GetCoor(0),CurrentTetromino->GetCoor(1),
		  CurrentTetromino->GetCoor(2),CurrentTetromino->GetCoor(3),FallPointCoor);
	 for(int d=0;d<4;d++){
		  int x=FallPointCoor[d].x;
		  int y=FallPointCoor[d].y;
		  switch (CurrentTetromino->GetShape()){
	 			break;case EMPTY:color=NONE_COLOR;
	 		  	break;case I_SHAPE:color=FALLPOINT_I_SHAPE_COLOR;
		  	  	break;case J_SHAPE:color=FALLPOINT_J_SHAPE_COLOR;
				break;case L_SHAPE:color=FALLPOINT_L_SHAPE_COLOR;
	 		  	break;case O_SHAPE:color=FALLPOINT_O_SHAPE_COLOR;
	 			break;case S_SHAPE:color=FALLPOINT_S_SHAPE_COLOR;
		  	  	break;case T_SHAPE:color=FALLPOINT_T_SHAPE_COLOR;
	 			break;case Z_SHAPE:color=FALLPOINT_Z_SHAPE_COLOR;
		  }
		  if(!IsThereCurrentTetro(FallPointCoor[d])){
				DrawBox(FIELD_X_COOR+BLOCK_SIZE*x,FIELD_Y_COOR+FIELD_HEIGHT-BLOCK_SIZE*(y+1),FIELD_X_COOR+BLOCK_SIZE*(x+1),FIELD_Y_COOR+FIELD_HEIGHT-BLOCK_SIZE*y,color,true);
		  }
	 }
}
void Field::DrawTotalLineAndG(){
	 DrawFormatString(FIELD_X_COOR,
		  FIELD_Y_COOR+FIELD_HEIGHT+FIELD_GAUGE_SPACE+GAUGE_SIZE+GAUGE_SCORE_SPACE,
		  GetColor(255,255,255),"TOTAL LINE %d",TotalDisappLine);
	 DrawFormatString(FIELD_X_COOR,
		  FIELD_Y_COOR+FIELD_HEIGHT+FIELD_GAUGE_SPACE+GAUGE_SIZE+GAUGE_SCORE_SPACE+SCORE_SPACE,
		  GetColor(255,255,255),"G %.2f",FallG);
	 DrawFormatString(FIELD_X_COOR,
		  FIELD_Y_COOR+FIELD_HEIGHT+FIELD_GAUGE_SPACE+GAUGE_SIZE+GAUGE_SCORE_SPACE+SCORE_SPACE*2,
		  GetColor(255,255,255),"LIM_TOUCHING_FLAME %d",LimitTouchingTime);
	 DrawFormatString(FIELD_X_COOR,
		  FIELD_Y_COOR+FIELD_HEIGHT+FIELD_GAUGE_SPACE+GAUGE_SIZE+GAUGE_SCORE_SPACE+SCORE_SPACE*3,
		  GetColor(255,255,255),"WAITING_FLAME %d",LimitWaitingTime);
}
void Field::DrawCurrentTetroNum(){DrawFormatString(0,50,GetColor(255,255,255),"%d",CurrentTetroNum);}
FieldStatus Field::GetCurrentStatus(){return CurrentStatus;}
int Field::GetCurrentTetroRiang(){return CurrentTetromino->GetTetroRiang();}
Tetro_Shape Field::GetCurrentTetroShape(){if(CurrentTetromino==NULL)return EMPTY;else return CurrentTetromino->GetShape();}
void Field::GetTetroLimitFallCoor(const Coordinate* FallTetroCoor,Coordinate* LimitFalledCoor){
	 
	 Coordinate FallPointCoor[4];
	 int counter=0;
	 
	 for(int d=0;d<4;d++){
		  FallPointCoor[d].x=FallTetroCoor[d].x;
		  FallPointCoor[d].y=FallTetroCoor[d].y;
	 }
	 while(1){
		  for(int d=0;d<4;d++){
				if(IsThereBlock(FallPointCoor[d])&&!IsThereCurrentTetro(FallPointCoor[d])){
					 break;
				}
				counter++;
		  }
		  if(counter==4){
				for(int b=0;b<4;b++){
					--FallPointCoor[b].y;
				}
		  }else{break;}
		  counter=0;
	 }
	 for(int b=0;b<4;b++){
		  ++FallPointCoor[b].y;
	 }

	 for(int d=0;d<4;d++){
		  LimitFalledCoor[d]=FallPointCoor[d];
	 }
}
void Field::GetTetroLimitFallCoor(Coordinate coor1,Coordinate coor2,Coordinate coor3,Coordinate coor4,Coordinate* LimitFalledCoor){
	 Coordinate FallCoor[4];
	 FallCoor[0]=coor1;
	 FallCoor[1]=coor2;
	 FallCoor[2]=coor3;
	 FallCoor[3]=coor4;
	 return GetTetroLimitFallCoor(FallCoor,LimitFalledCoor);
}
void Field::GetTetroLimitFallCoor(Coordinate* FallTetroCoor){
	 Coordinate AnsCoor[4];
	 GetTetroLimitFallCoor(FallTetroCoor,AnsCoor);
	 for(int d=0;d<4;d++) FallTetroCoor[d]=AnsCoor[d];
}
int Field::GetRandSeed(){return RandSeed;}
Coordinate Field::GetTetroCoor(int n){return CurrentTetromino->GetCoor(n);}
double Field::GetFallG(){return FallG;}
void Field::CalcHeightBar(){
	 int HeightCounter=0;
	 int BlockNum=0;
	 for(int x=0;x<FIELD_WIDTH_BLOCK;x++){
		  for(int y=0;y<FIELD_HEIGHT_BLOCK;y++){
				if(field[x][y]!=NONE){
					 HeightCounter+=y;
					 BlockNum++;
				}
		  }
	 }
	 if(BlockNum==0)HeightBar=0;
	 HeightBar=double(double(HeightCounter)/double(BlockNum));
}
double Field::GetHeightBar(){return HeightBar;}
bool Field::IsThereCurrentTetro(int x,int y){
	 Coordinate coor;
	 coor.x=x;
	 coor.y=y;
	 for(int d=0;d<4;d++){
		  if(CurrentTetromino->GetCoor(d)==coor)return true;
	 }
	 return false;
}
bool Field::IsThereCurrentTetro(Coordinate coor){
	 for(int d=0;d<4;d++){
		  if(CurrentTetromino->GetCoor(d)==coor)return true;
	 }
	 return false;
}
bool Field::IsThereBlock(int x,int y){
	 return GetCoorStatus(x,y)!=NONE;
}
bool Field::IsThereBlock(Coordinate coor){
	 return IsThereBlock(coor.x,coor.y);
}
bool Field::IsReadyToFall(){
	 return LimitWaitingTime<=WaitingTime;
}

Field::HoldingWaitingField::HoldingWaitingField(){
	BlockSize=BLOCK_SIZE/2;
	FieldXCoor=FIELD_X_COOR;
	FieldYCoor=FIELD_Y_COOR-BlockSize*4;
	for(int d=0;d<4;d++){
		Shape[d]=EMPTY;
	}
	LoadDivGraph("WaitHoldPic.png",8,4,2,40,40,TetroGHandle);
}
void Field::HoldingWaitingField::SetShape(Tetro_Shape HoldingTetro,Tetro_Shape* WaitingTetro){
	Shape[0]=HoldingTetro;
	for(int d=1;d<4;d++){
		Shape[d]=WaitingTetro[d-1];
	}
}
void Field::HoldingWaitingField::DrawHWField(){
	DrawGraph(FieldXCoor,FieldYCoor,TetroGHandle[Shape[0]],true);
	for(int d=1;d<=3;d++){
		DrawGraph(FieldXCoor+BlockSize*4*(1+d),FieldYCoor,TetroGHandle[Shape[d]],true);
	}
}
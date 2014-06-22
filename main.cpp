//2014 4/5～
//moshikame
#include"classes.h"
#include"AItest.h"
#include"definitions.h"
int counter=0,FpsTime[2]={0,},FpsTime_i=0;
int color_white;
double Fps=0.0;
char Key[256];
//int FontHandle=CreateFontToHandle("PixelMplus12",12,-1,DX_FONTTYPE_EDGE);
void FpsTimeFanction(){
        if(FpsTime_i== 0)
                FpsTime[0]=GetNowCount();               //1周目の時間取得
        if(FpsTime_i==49){
                FpsTime[1]=GetNowCount();               //50周目の時間取得
                Fps = 1000.0f / ((FpsTime[1] - FpsTime[0]) / 50.0f);//測定した値からfpsを計算
                FpsTime_i=0;//カウントを初期化
        }
        else
                FpsTime_i++;//現在何周目かカウント
        if(Fps != 0)
                DrawFormatString(0,0,GetColor(255,255,255),"FPS %.1f",Fps); //fpsを表示
        return;
}
int PauseMenu(int BackGHandle);//0→resume 1→quit
void GameOver(int GHandle);
void SnapShot();
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(true);
	SetGraphMode(WIN_WIDTH,WIN_HEIGHT,16);
	 if(DxLib_Init()==-1){
		return -1;
	}
	int Screenstatus=SetDrawScreen(DX_SCREEN_BACK);
	
	//ChangeFont("PixelMplus12");
	//SetFontSize(24);
	//PlaySoundFile("a.ogg",DX_PLAYTYPE_LOOP);
	


	bool LevoroKeyStatus=false;//true→押されている,false→押されていない
	bool ClockKeyStatus=false;//true→押されている,false→押されていない
	int SoftDropKeyLastHit=0;//最後に押されたのが何フレーム前か
	int UpKeyLastHit=0;//最後に押されたのが何フレーム前か
	int RightKeyLastHit=0;//最後に押されたのが何フレーム前か
	int DownKeyLastHit=0;//最後に押されたのが何フレーム前か
	int LeftKeyLastHit=0;//最後に押されたのが何フレーム前か
	int SoftDropKeyMoveNum=0;
	int UpKeyMoveNum=0;//キーを押している間に何回移動したか
	int RightKeyMoveNum=0;//キーを押している間に何回移動したか
	int DownKeyMoveNum=0;//キーを押している間に何回移動したか
	int LeftKeyMoveNum=0;//キーを押している間に何回移動したか
	bool HoldKeyStatus=false;//true→押されている,false→押されていない
	bool SnapKeyStatus=false;//true→押されている,false→押されていない
	bool HardDropKeyStatus=false;//true→押されている,false→押されていない
	bool MiddleDropKeyStatus=false;//true→押されている,false→押されていない
	bool PauseKeyStatus=false;//true→押されている,false→押されていない

	int MoveSHandle=LoadSoundMem("SE/move.wav");
	 int RotateSHandle=LoadSoundMem("SE/ta_ta_tyupi01.mp3");
	 int HardDropSHandle=LoadSoundMem("SE/harddrop.wav");
	 int PauseSHandle=LoadSoundMem("SE/pause_.wav");

	int* KeyLastHit=0;
	int* KeyMoveNum=0;
	
	Field field;
	Tetromino* Tetro;
	field.SetFallG();
	int t=0;
	Tetro_Shape ReservedShape=EMPTY;
	int ScreenGHandle=MakeGraph(WIN_WIDTH,WIN_HEIGHT);
	bool IsGameOver=false;
	while(1){
		 SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();

	
		
		field.RenewCurrentStatus();
		field.SetWaitingTetro();
		GetHitKeyStateAll(KeyInputBuf);
		AIforField(field,KeyInputBuf,field.GetRandSeed());

		if(field.GetCurrentStatus()==WAITING&&field.IsReadyToFall()){
			if(ReservedShape==EMPTY){
				Tetro=new Tetromino(field.GetWaitingTetro(0),&field);
				if(field.SetCurrentTetrominoAndIsGameOver(Tetro)){
					 IsGameOver=true;
				}
			}else{
				Tetro=new Tetromino(ReservedShape,&field);
				if(field.SetCurrentTetrominoByHoldingAndIsGameOver(Tetro)){
					 IsGameOver=true;
				}
				ReservedShape=EMPTY;
			}
		}
		if(field.GetCurrentStatus()==WAITING)field.RenewWaitingStatus();
		if(field.GetCurrentStatus()==FALLING||field.GetCurrentStatus()==TOUCHING){
			if(!KeyInputBuf[SOFT_DROP_KEY])field.AutoFallTetro();
			
			if(KeyInputBuf[HARD_DROP_KEY]){
				if(!HardDropKeyStatus){
					PlaySoundMem(HardDropSHandle,DX_PLAYTYPE_BACK);
					field.HarddropCurrentTetromino();
					HardDropKeyStatus=true;
				}
			}else HardDropKeyStatus=false;

			if(KeyInputBuf[MIDDLE_DROP_KEY]){
				if(!MiddleDropKeyStatus){
					 //PlaySoundMem(HardDropSHandle,DX_PLAYTYPE_BACK);
					field.MiddleDropCurrentTetromino();
					MiddleDropKeyStatus=true;
				}
			}else MiddleDropKeyStatus=false;
			
			if(KeyInputBuf[LEVORO_KEY]){
				if(!LevoroKeyStatus){
					field.RotateCurrentTetromino(1);
					if(!CheckSoundMem(MoveSHandle))PlaySoundMem(RotateSHandle,DX_PLAYTYPE_BACK);
					else{
						 StopSoundMem(MoveSHandle);
						 PlaySoundMem(RotateSHandle,DX_PLAYTYPE_BACK);
					}
					LevoroKeyStatus=true;
				}
			}else LevoroKeyStatus=false;
			
			if(KeyInputBuf[CLOCK_KEY]){
				if(!ClockKeyStatus){
					field.RotateCurrentTetromino(-1);
					if(!CheckSoundMem(MoveSHandle))PlaySoundMem(RotateSHandle,DX_PLAYTYPE_BACK);
					else{
						 StopSoundMem(MoveSHandle);
						 PlaySoundMem(RotateSHandle,DX_PLAYTYPE_BACK);
					}
					ClockKeyStatus=true;
				}
			}else ClockKeyStatus=false;
		
			
			if(KeyInputBuf[RIGHT_KEY]){
				RightKeyLastHit++;
				 if(RightKeyMoveNum==0){
					 if(field.MoveCurrentTetromino(RIGHT))PlaySoundMem(MoveSHandle,DX_PLAYTYPE_BACK);
					 RightKeyLastHit=0;
					 RightKeyMoveNum++;
				}else if(RightKeyMoveNum==1){
					 if(RightKeyLastHit>FIRST_SECOND_MOVE_INTERVAL){
						  if(field.MoveCurrentTetromino(RIGHT))PlaySoundMem(MoveSHandle,DX_PLAYTYPE_BACK);
						  RightKeyLastHit=0;
						  RightKeyMoveNum++;
					 }
				}else if(RightKeyMoveNum>1){
					 if(RightKeyLastHit>MOVE_INTERVAL){
						  if(field.MoveCurrentTetromino(RIGHT))PlaySoundMem(MoveSHandle,DX_PLAYTYPE_BACK);
						  RightKeyLastHit=0;
						  RightKeyMoveNum++;
					 }
				}
			}else RightKeyMoveNum=0;
			
			if(KeyInputBuf[SOFT_DROP_KEY]){
				SoftDropKeyLastHit++;
				 if(RightKeyMoveNum==0){
					 field.SoftdropCurrentTetromino();
					 SoftDropKeyLastHit=0;
					 SoftDropKeyMoveNum++;
				}else if(SoftDropKeyMoveNum==1){
					 if(SoftDropKeyLastHit>FIRST_SECOND_MOVE_INTERVAL){
						  field.SoftdropCurrentTetromino();
						  SoftDropKeyLastHit=0;
						  SoftDropKeyMoveNum++;
					 }
				}else if(SoftDropKeyMoveNum>1){
					 if(SoftDropKeyLastHit>MOVE_INTERVAL){
						  field.SoftdropCurrentTetromino();
						  SoftDropKeyLastHit=0;
						  SoftDropKeyMoveNum++;
					 }
				}
			}else SoftDropKeyMoveNum=0;

			if(KeyInputBuf[LEFT_KEY]){
				LeftKeyLastHit++;
				 if(LeftKeyMoveNum==0){
					 if(field.MoveCurrentTetromino(LEFT))PlaySoundMem(MoveSHandle,DX_PLAYTYPE_BACK);
					 LeftKeyLastHit=0;
					 LeftKeyMoveNum++;
				}else if(LeftKeyMoveNum==1){
					 if(LeftKeyLastHit>FIRST_SECOND_MOVE_INTERVAL){
						  if(field.MoveCurrentTetromino(LEFT))PlaySoundMem(MoveSHandle,DX_PLAYTYPE_BACK);
						  LeftKeyLastHit=0;
						  LeftKeyMoveNum++;
					 }
				}else if(LeftKeyMoveNum>1){
					 if(LeftKeyLastHit>MOVE_INTERVAL){
						  if(field.MoveCurrentTetromino(LEFT))PlaySoundMem(MoveSHandle,DX_PLAYTYPE_BACK);
						  LeftKeyLastHit=0;
						  LeftKeyMoveNum++;
					 }
				}
			}else LeftKeyMoveNum=0;
						
			if(KeyInputBuf[HOLD_KEY]/*&&!field.GetIsAlreadyHolded()*/){
				if(!HoldKeyStatus){
					ReservedShape=field.SetHoldingTetro();
					HoldKeyStatus=true;
				}
			}else HoldKeyStatus=false;
		}
		if(field.GetCurrentStatus()==TOUCHING){
			field.RenewTouchingStatus();
		}
		if(field.GetCurrentStatus()==BREAKING){
			field.RenewDeleteLineStatus();
		}
		UpKeyLastHit++;
		RightKeyLastHit++;
		DownKeyLastHit++;
		LeftKeyLastHit++;

		
			
	
		


		//以下グラフィック

		
		field.DrawField();
		if(field.GetCurrentStatus()==FALLING)field.DrawFallPoint();
		field.DrawBreakingBox();
		field.DrawGauge();
		field.DrawHWField();
		FpsTimeFanction();
		field.DrawTotalLineAndG();
		field.DrawCurrentTetroNum();
		
		
		if(CheckHitKey(SNAP_KEY)){
		  if(!SnapKeyStatus){
				SnapShot();
				SnapKeyStatus=true;
			 }
			 else SnapKeyStatus=false;
		}
		if(CheckHitKey(PAUSE_KEY)){
			if(!PauseKeyStatus){
				 GetDrawScreenGraph(0,0,WIN_WIDTH,WIN_HEIGHT,ScreenGHandle);
				 PlaySoundMem(PauseSHandle,DX_PLAYTYPE_BACK);
				if(PauseMenu(ScreenGHandle)==1)break;
				PauseKeyStatus=true;
			}
		}else PauseKeyStatus=false;

		if(IsGameOver){
			 GetDrawScreenGraph(0,0,WIN_WIDTH,WIN_HEIGHT,ScreenGHandle);
			 GameOver(ScreenGHandle);
		}

		//if(CheckHitKey(KEY_INPUT_Q))break;
		
		ScreenFlip();
		WaitTimer(16);
		if( ProcessMessage() == -1 ) break ;
		++t;
		}
	DxLib_End();
	return 0;
}	
int PauseMenu(int BackGHandle){
	 static int CursolPositioon;
	 GraphFilter(BackGHandle,DX_GRAPH_FILTER_HSB,0,0,0,-160);

	 bool ZKeyStatus=false;
	 bool UpKeyStatus=true;
	 bool DownKeyStatus=false;

	 while(1){
		  SetDrawScreen(DX_SCREEN_BACK);
		  ClearDrawScreen();
		  
		  DrawGraph(0,0,BackGHandle,true);
		  DrawBox(FIELD_X_COOR,FIELD_Y_COOR,FIELD_X_COOR+FIELD_WIDTH,
				FIELD_Y_COOR+FIELD_HEIGHT,GetColor(0,0,0),true);
		  DrawFormatString(WIN_WIDTH/2-GetDrawStringWidth("RESUME",16)/2,
				WIN_HEIGHT/2-50,
				GetColor(255,255,255),
				"RESUME");
		  DrawFormatString(WIN_WIDTH/2-GetDrawStringWidth("QUIT",19)/2,
				WIN_HEIGHT/2+50,
				GetColor(255,255,255),
				"QUIT");
		  switch(imod(CursolPositioon,2)){
				break;case 0:{
					 DrawFormatString(WIN_WIDTH/2-GetDrawStringWidth("RESUME",16)/2-10,
						  WIN_HEIGHT/2-50,
						  GetColor(255,0,0),">");
					 if(CheckHitKey(KEY_INPUT_Z)){
						  if(!ZKeyStatus){
								int t=0;
								while(1){
		  							 SetDrawScreen(DX_SCREEN_BACK);
									 ClearDrawScreen();

									 DrawGraph(0,0,BackGHandle,true);
									 if(quot(t,60)==0){
										  DrawString(0,0,"3.",GetColor(255,255,255));
									 }if(quot(t,60)==1){
										  DrawString(0,0,"3.2.",GetColor(255,255,255));
									 }if(quot(t,60)==2){
										  DrawString(0,0,"3.2.1",GetColor(255,255,255));
									 }if(quot(t,60)==3){
										  return 0;
									 }

									 t++;
		  						  	 ScreenFlip();
									 WaitTimer(16);
								}
						  }
					 }else ZKeyStatus=false;
				}break;case 1:{
					 DrawFormatString(WIN_WIDTH/2-GetDrawStringWidth("QUIT",16)/2-10,
						  WIN_HEIGHT/2+50,
						  GetColor(255,0,0),">");
					 if(CheckHitKey(KEY_INPUT_Z)){
						  if(!ZKeyStatus){
								return 1;
						  }
					 }else ZKeyStatus=false;
				}
		  }
		  if(CheckHitKey(UP_KEY)){
				if(!UpKeyStatus){
					 UpKeyStatus=true;
					 --CursolPositioon;
	 		  }
		  }else UpKeyStatus=false;

		  if(CheckHitKey(DOWN_KEY)){
				if(!DownKeyStatus){
					 DownKeyStatus=true;
					 ++CursolPositioon;
	 		  }
		  }else DownKeyStatus=false;
		  /*if(CheckHitKey(KEY_INPUT_ESCAPE)){
				if(!EscapeKeyStatus)return 1;
		  }else EscapeKeyStatus=false;
		  if(CheckHitKey(KEY_INPUT_Z)){
				if(!ZKeyStatus){
				int t=0;
				while(1){
		  			 SetDrawScreen(DX_SCREEN_BACK);
					 ClearDrawScreen();

					 DrawGraph(0,0,BackGHandle,true);
					 if(quot(t,60)==0){
						  DrawString(0,0,"3.",GetColor(255,255,255));
					 }if(quot(t,60)==1){
						  DrawString(0,0,"3.2.",GetColor(255,255,255));
					 }if(quot(t,60)==2){
						  DrawString(0,0,"3.2.1",GetColor(255,255,255));
					 }if(quot(t,60)==3){
						  return 0;
					 }

					 t++;
					 ScreenFlip();
					 WaitTimer(16);
				}
				}
		  }*/
		  /*if(CheckHitKey(UP_KEY)){
				if(!UpKeyStatus){
					 --CursolPositioon;
	 		  }
		  			else UpKeyStatus=false;
			}

		  if(CheckHitKey(DOWN_KEY)){
				if(!DownKeyStatus){
					 ++CursolPositioon;
	 		  }
		  			else DownKeyStatus=false;
			}
		  switch(imod(CursolPositioon,2)){
				break;case 0:{//resume
					 DrawFormatString(40,WIN_HEIGHT/2-50,GetColor(255,0,0),">");
					 if(CheckKeyInput(DEC_KEY)){
						  if(!DecKeyStatus){
								return 0;
								DecKeyStatus=true;
						  }
					 }else{DecKeyStatus=false;}
				}break;case 1:{//quit
					 DrawFormatString(40,WIN_HEIGHT/2+50,GetColor(255,0,0),">");
					 if(CheckKeyInput(DEC_KEY)){
						  if(!DecKeyStatus){
								return 1;
								DecKeyStatus=true;
						  }
					 }else{DecKeyStatus=false;}
				}
		  }

	 ScreenFlip();
	 WaitTimer(16);
	 }
}*/
		  ScreenFlip();
		  WaitTimer(16);
	}
}
void GameOver(int GHandle){
	 int SnapKeyStatus=false;
	 GraphFilter(GHandle,DX_GRAPH_FILTER_HSB,0,0,0,-160);
	 while(1){
		  SetDrawScreen(DX_SCREEN_BACK);
		  ClearDrawScreen();
		  
		  DrawGraph(0,0,GHandle,false);
		  DrawString(WIN_WIDTH/2-GetDrawStringWidth("GAMEOVER",8)/2,WIN_HEIGHT/2,"GAMEOVER",GetColor(255,0,0));
		  if(CheckHitKey(KEY_INPUT_ESCAPE)){DxLib_End();exit(0);}
		  if(CheckHitKey(SNAP_KEY)){
		  if(!SnapKeyStatus){
				SnapShot();
				SnapKeyStatus=true;
			 }
			 else SnapKeyStatus=false;
		  }

		  ScreenFlip();
		  WaitTimer(16);
	 }
}
void SnapShot(){
	 DATEDATA Date;
	 GetDateTime(&Date);
	 std::string Filename=IntToString(Date.Year)+IntToString(Date.Mon)+IntToString(Date.Day)+IntToString(Date.Hour)+IntToString(Date.Min)+IntToString(Date.Sec)+".bmp";
	 SaveDrawScreen(0,0,WIN_WIDTH,WIN_HEIGHT,Filename.c_str());
}
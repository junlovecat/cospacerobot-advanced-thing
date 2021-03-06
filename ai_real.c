////////////////////////////////////////
//
//	File : ai.c
//	CoSpace Robot
//	Version 1.0.0
//	Jan 1 2021
//	Copyright (C) 2021 CoSpace Robot. All Rights Reserved
//
//////////////////////////////////////
//
// ONLY C Code can be compiled.
//
/////////////////////////////////////

#define CsBot_AI_H//DO NOT delete this line
#ifndef CSBOT_REAL
#include <windows.h>
#include <stdio.h>
#include <math.h>
#define DLL_EXPORT extern __declspec(dllexport)
#define false 0
#define true 1
#endif
//The robot ID : six chars unique CID.
//Find it from your CoSpace Robot label or CoSpace program download GUI.
//Don't write the below line into two lines or more lines.
char AI_MyID[6] = {'1','2','3','4','5','6'};

int Duration = 0;
int SuperDuration = 0;
int bGameEnd = false;
int CurAction = -1;
int CurGame = 0;
int SuperObj_Num = 0;
int SuperObj_X = 0;
int SuperObj_Y = 0;
int Teleport = 0;
int LoadedObjects = 0;
int LoadedBlackObjects = 0;
int LoadedRedObjects = 0;
int LoadedCyanObjects = 0;
int IL = 0;
int isin = 0;
int US_Front = 0;
int US_Left = 0;
int US_Right = 0;
int CSLeft_R = 0;
int CSLeft_G = 0;
int CSLeft_B = 0;
int CSRight_R = 0;
int CSRight_G = 0;
int CSRight_B = 0;
int PositionX = 0;
int PositionY = 0;
int TM_State = 0;
int Compass = 0;
int Time = 0;
int WheelLeft = 0;
int WheelRight = 0;
int LED_1 = 0;
int MyState = 0;
int AI_SensorNum = 13;
int AI_TeamID = 1;   //Robot Team ID. 1:Blue Ream; 2:Red Team.
int MySMS; //A integer value which you want to send to the other robot.
           //In Super Team mode, you can use this value to inform your another robot of your status.
           //In Indiviual Mode, you should keep this value to 0.  

//The following three variables save the information of the other robot.
int OtherRob_SMS; //Keep the recieved value of the other robot MySMS value.
            //In Super Team mode, this value is sent by your another robot.
            //In Indiviual Mode, this value has no meaning.
int OtherRob_PositionX;//The X coordinate of the other robot. 
int OtherRob_PositionY;//The Y coordinate of the other robot. 

//The following four variables keep the information of the last state-changed object.
int ObjState;    //The state (0: Disappear; 1:Appear.) of the last state changed object.
int ObjPositionX;//The X coordinate of the last state-changed object.
int ObjPositionY;//The Y coordinate of the last state-changed object.
int ObjDuration; //The duration(seconds) of the object maintains the current state;


#define CsBot_AI_C//DO NOT delete this line

DLL_EXPORT void SetGameID(int GameID)
{
    CurGame = GameID;
    bGameEnd = 0;
}

DLL_EXPORT int GetGameID()
{
    return CurGame;
}

//Only Used by CsBot Dance Platform
DLL_EXPORT int IsGameEnd()
{
    return bGameEnd;
}

#ifndef CSBOT_REAL

DLL_EXPORT char* GetDebugInfo()
{
    char info[3000];
    sprintf(info, "Duration=%d;SuperDuration=%d;bGameEnd=%d;CurAction=%d;CurGame=%d;SuperObj_Num=%d;SuperObj_X=%d;SuperObj_Y=%d;Teleport=%d;LoadedObjects=%d;LoadedBlackObjects=%d;LoadedRedObjects=%d;LoadedCyanObjects=%d;IL=%d;isin=%d;US_Front=%d;US_Left=%d;US_Right=%d;CSLeft_R=%d;CSLeft_G=%d;CSLeft_B=%d;CSRight_R=%d;CSRight_G=%d;CSRight_B=%d;PositionX=%d;PositionY=%d;TM_State=%d;Compass=%d;Time=%d;WheelLeft=%d;WheelRight=%d;LED_1=%d;MyState=%d;",Duration,SuperDuration,bGameEnd,CurAction,CurGame,SuperObj_Num,SuperObj_X,SuperObj_Y,Teleport,LoadedObjects,LoadedBlackObjects,LoadedRedObjects,LoadedCyanObjects,IL,isin,US_Front,US_Left,US_Right,CSLeft_R,CSLeft_G,CSLeft_B,CSRight_R,CSRight_G,CSRight_B,PositionX,PositionY,TM_State,Compass,Time,WheelLeft,WheelRight,LED_1,MyState);
    return info;
}
 
DLL_EXPORT char* GetTeamName()
{
     return "robot";
}

DLL_EXPORT int GetCurAction()
{
    return CurAction;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT int GetTeleport()
{
    return Teleport;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT void SetSuperObj(int X, int Y, int num)
{
    SuperObj_X = X;
    SuperObj_Y = Y;
    SuperObj_Num = num;
}
//Only Used by CsBot Rescue Platform
DLL_EXPORT void GetSuperObj(int *X, int *Y, int *num)
{
    *X = SuperObj_X;
    *Y = SuperObj_Y;
    *num = SuperObj_Num;
}
//Used by CoSpace Rescue Simulation. 
///Called each time frame by simulator to update the other robot information.
DLL_EXPORT void UpdateRobInfo(int sms, int X, int Y)
{
	OtherRob_SMS = sms;
	OtherRob_PositionX = X;
	OtherRob_PositionY = Y;
}

//Used by Only Used by CsBot Rescue Platform
DLL_EXPORT void UpdateObjectInfo(int X, int Y, int state, int duration)
{
	ObjState = state;
	ObjPositionX = X;
	ObjPositionY = Y;
	ObjDuration = duration;
}

#endif ////CSBOT_REAL

DLL_EXPORT void SetDataAI(volatile int* packet, volatile int *AI_IN)
{

    int sum = 0;

    US_Front = AI_IN[0]; packet[0] = US_Front; sum += US_Front;
    US_Left = AI_IN[1]; packet[1] = US_Left; sum += US_Left;
    US_Right = AI_IN[2]; packet[2] = US_Right; sum += US_Right;
    CSLeft_R = AI_IN[3]; packet[3] = CSLeft_R; sum += CSLeft_R;
    CSLeft_G = AI_IN[4]; packet[4] = CSLeft_G; sum += CSLeft_G;
    CSLeft_B = AI_IN[5]; packet[5] = CSLeft_B; sum += CSLeft_B;
    CSRight_R = AI_IN[6]; packet[6] = CSRight_R; sum += CSRight_R;
    CSRight_G = AI_IN[7]; packet[7] = CSRight_G; sum += CSRight_G;
    CSRight_B = AI_IN[8]; packet[8] = CSRight_B; sum += CSRight_B;
    PositionX = AI_IN[9]; packet[9] = PositionX; sum += PositionX;
    PositionY = AI_IN[10]; packet[10] = PositionY; sum += PositionY;
    TM_State = AI_IN[11]; packet[11] = TM_State; sum += TM_State;
    Compass = AI_IN[12]; packet[12] = Compass; sum += Compass;
    Time = AI_IN[13]; packet[13] = Time; sum += Time;
    packet[14] = sum;

}
DLL_EXPORT void GetCommand(int *AI_OUT)
{
    AI_OUT[0] = WheelLeft;
    AI_OUT[1] = WheelRight;
    AI_OUT[2] = LED_1;
    AI_OUT[3] = MyState;
}
void TurnTo(int curRot, int targetRot)
{
    int p0 = targetRot;
    int p3 = (targetRot + 3) % 360;
    int p15 = (targetRot + 15) % 360;
    int n3 = (targetRot - 3 + 360) % 360;
    int n15 = (targetRot - 15 + 360) % 360;
    int p180 = (targetRot + 180) % 360;
    int l = 0, r = 0;
    Duration = 6;
    //Within(-3,+3)deg, stop turing.
    l = n3; r = p3;
    if ((l < r && curRot > l && curRot < r) ||
    (l > r && (curRot > l || curRot < r)))
    {
        WheelLeft = 0;
        WheelRight = 0;
        Duration = 0;
        return;
    }
    //Within[3,15]deg,Turn Slowly
    l = p3; r = p15;
    if ((l < r && curRot >= l && curRot <= r) ||
        (l > r && (curRot >= l || curRot <= r)))
    {
        WheelLeft = 10;
        WheelRight = -10;
        return;
    }
    //Within[15,180]deg,Turn Faast
    l = p15; r = p180;
    if ((l < r && curRot >= l && curRot <= r) ||
       (l > r && (curRot >= l || curRot <= r)))
    {
        WheelLeft = 30;
        WheelRight = -30;
        return;
    }
    //Within[-15,-3]deg,Turn Slowly
    l = n15; r = n3;
    if ((l < r && curRot >= l && curRot <= r) ||
    (l > r && (curRot >= l || curRot <= r)))
    {
        WheelLeft = -10;
        WheelRight = 10;
        return;
    }
    //Within[-180,-15]deg,Turn Fast
    l = p180; r = n15;
    if ((l < r && curRot >= l && curRot <= r) ||
    (l > r && (curRot >= l || curRot <= r)))
    {
        WheelLeft = -30;
        WheelRight = 30;
        return;
    }
}
void Game0()
{

    if(Duration>0)
    {
        Duration--;
    }
    else if(Time<=1)
    {
        Duration = 4;
        CurAction =1;
    }
    else if(Time>=280 && Time<=290&&(LoadedObjects<1))
    {
        Duration = 0;
        CurAction =2;
    }
    else if(Time>=295 && Time<=298)
    {
        Duration = 0;
        CurAction =3;
    }
    else if(CSLeft_R>=226 && CSLeft_R<=246 && CSLeft_G>=131 && CSLeft_G<=151 && CSLeft_B<=20 && CSRight_R>=226 && CSRight_R<=246 && CSRight_G>=131 && CSRight_G<=151 && CSRight_B<=20&&(LoadedObjects>2))
    {
        Duration = 61;
        CurAction =4;
    }
    else if(CSLeft_R>=226 && CSLeft_R<=246 && CSLeft_G>=131 && CSLeft_G<=151 && CSLeft_B<=20&&(LoadedObjects>2))
    {
        Duration = 0;
        CurAction =5;
    }
    else if(CSRight_R>=226 && CSRight_R<=246 && CSRight_G>=131 && CSRight_G<=151 && CSRight_B<=20&&(LoadedObjects>2))
    {
        Duration = 0;
        CurAction =6;
    }
    else if(CSLeft_R>=226 && CSLeft_R<=246 && CSLeft_G>=226 && CSLeft_G<=246 && CSLeft_B<=20&&(LoadedObjects>0))
    {
        Duration = 1;
        CurAction =7;
    }
    else if(CSRight_R>=226 && CSRight_R<=246 && CSRight_G>=226 && CSRight_G<=246 && CSRight_B<=20&&(LoadedObjects>0
))
    {
        Duration = 1;
        CurAction =8;
    }
    else if(CSLeft_R>=53 && CSLeft_R<=73 && CSLeft_G>=95 && CSLeft_G<=115 && CSLeft_B>=171 && CSLeft_B<=191)
    {
        Duration = 6;
        CurAction =9;
    }
    else if(CSRight_R>=52 && CSRight_R<=72 && CSRight_G>=101 && CSRight_G<=121 && CSRight_B>=235)
    {
        Duration = 6;
        CurAction =10;
    }
    else if(CSLeft_R<=20 && CSLeft_G<=20 && CSLeft_B<=20&&(LoadedObjects<6&&LoadedBlackObjects<2))
    {
        Duration = 55;
        CurAction =11;
    }
    else if(CSRight_R<=20 && CSRight_G<=20 && CSRight_B<=20&&(LoadedObjects<6&&LoadedBlackObjects<2))
    {
        Duration = 55;
        CurAction =12;
    }
    else if(CSLeft_R>=227 && CSLeft_R<=247 && CSLeft_G<=20 && CSLeft_B<=20&&(LoadedObjects<6&&LoadedRedObjects<2
))
    {
        Duration = 55;
        CurAction =13;
    }
    else if(CSRight_R>=227 && CSRight_R<=247 && CSRight_G<=20 && CSRight_B<=0&&(LoadedObjects<6&&LoadedRedObjects<2))
    {
        Duration = 55;
        CurAction =14;
    }
    else if(CSLeft_R<=20 && CSLeft_G>=226 && CSLeft_G<=246 && CSLeft_B>=226 && CSLeft_B<=246&&(LoadedObjects<6&&LoadedCyanObjects<2))
    {
        Duration = 55;
        CurAction =15;
    }
    else if(CSRight_R<=20 && CSRight_G>=226 && CSRight_G<=246 && CSRight_B>=226 && CSRight_B<=246&&(LoadedObjects<6&&LoadedCyanObjects<2))
    {
        Duration = 55;
        CurAction =16;
    }
    else if(US_Front<=10 && US_Left<=7 && US_Right<=7)
    {
        Duration = 3;
        CurAction =17;
    }
    else if(US_Front<=10 && US_Right<=10)
    {
        Duration = 0;
        CurAction =18;
    }
    else if(US_Front<=10 && US_Left<=10)
    {
        Duration = 0;
        CurAction =19;
    }
    else if(US_Left<=10)
    {
        Duration = 0;
        CurAction =20;
    }
    else if(US_Right<=10)
    {
        Duration = 0;
        CurAction =21;
    }
    else if(US_Front<=7)
    {
        Duration = 0;
        CurAction =22;
    }
    else if(true)
    {
        Duration = 0;
        CurAction =23;
    }
    switch(CurAction)
    {
        case 1:
            WheelLeft=15;
            WheelRight=0;
            LED_1=0;
            MyState=-100;
            break;
        case 2:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=-100;
             Teleport =2;  
            LoadedObjects = 0;
            WheelLeft = 0;  WheelRight = 0;  LED_1=0;
            Duration = 0;   SuperDuration = 0;
            if(IL==1){
IL=0;
                    
}

            break;
        case 3:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=-100;
             Teleport =2;  
            LoadedObjects = 0;
            WheelLeft = 0;  WheelRight = 0;  LED_1=0;
            Duration = 0;   SuperDuration = 0;
            if(IL==1){
IL=0;
                    
}

            break;
        case 4:
            WheelLeft=0;
            WheelRight=0;
            LED_1=2;
            MyState=0;
            if(Duration == 1) {LoadedObjects = 0;} 
            if(Duration < 12)
            {
                WheelLeft = 60;
                WheelRight = 60;
            }
            LoadedBlackObjects=0;
                    
LoadedCyanObjects=0;
                    
LoadedRedObjects=0;
                    
if(IL==1){
IL=0;
                    
}

            break;
        case 5:
            WheelLeft=0;
            WheelRight=40;
            LED_1=0;
            MyState=0;
            if(IL==1){
IL=0;
                    
}

            break;
        case 6:
            WheelLeft=40;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            if(IL==1){
IL=0;
                    
}

            break;
        case 7:
            WheelLeft=-50;
            WheelRight=-30;
            LED_1=0;
            MyState=0;
            if(IL==1){
IL=0;
                    
}

            break;
        case 8:
            WheelLeft=-50;
            WheelRight=-30;
            LED_1=0;
            MyState=0;
            if(IL==1){
IL=0;
                    
}

            break;
        case 9:
            WheelLeft=-100;
            WheelRight=-60;
            LED_1=0;
            MyState=0;
            if(IL==1){
IL=0;
                    
}
LoadedBlackObjects=0;
                    
LoadedCyanObjects=0;
                    
LoadedRedObjects=0;
                    
            break;
        case 10:
            WheelLeft=-60;
            WheelRight=-100;
            LED_1=0;
            MyState=0;
            if(IL==1){
IL=0;
                    
}
LoadedBlackObjects=0;
                    
LoadedCyanObjects=0;
                    
LoadedRedObjects=0;
                    
            break;
        case 11:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 40;
                WheelRight = 40;
            }
            if(IL==0){
LoadedBlackObjects++;
                    
IL=1;
                    
}
            break;
        case 12:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 40;
                WheelRight = 40;
            }
            if(IL==0){
LoadedBlackObjects++;
                    
IL=1;
                    
}
            break;
        case 13:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 40;
                WheelRight = 40;
            }
            if(IL==0){
LoadedRedObjects++;
                    
IL=1;
                    
}

            break;
        case 14:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 40;
                WheelRight = 40;
            }
            if(IL==0){
LoadedRedObjects++;
                    
IL=1;
                    
}


            break;
        case 15:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 40;
                WheelRight = 40;
            }
            if(IL==0){
LoadedCyanObjects++;
                    
IL=1;
                    
}


            break;
        case 16:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            if(Duration == 1) LoadedObjects++;
            if(Duration < 6)
            {
                WheelLeft = 40;
                WheelRight = 40;
            }
            if(IL==0){
LoadedCyanObjects++;
                    
IL=1;
                    
}



            break;
        case 17:
            WheelLeft=-40;
            WheelRight=50;
            LED_1=0;
            MyState=0;
            if(IL==1){
IL=0;
                    
}

            break;
        case 18:
            WheelLeft=-40;
            WheelRight=-10;
            LED_1=0;
            MyState=0;
            if(IL==1){
IL=0;
                    
}

            break;
        case 19:
            WheelLeft=-10;
            WheelRight=-40;
            LED_1=0;
            MyState=0;
            if(IL==1){
IL=0;
                    
}

            break;
        case 20:
            WheelLeft=50;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            if(IL==1){
IL=0;
                    
}

            break;
        case 21:
            WheelLeft=0;
            WheelRight=50;
            LED_1=0;
            MyState=0;
            if(IL==1){
IL=0;
                    
}

            break;
        case 22:
            WheelLeft=-50;
            WheelRight=-40;
            LED_1=0;
            MyState=0;
            if(IL==1){
IL=0;
                    
}

            break;
        case 23:
            WheelLeft=37;
            WheelRight=37;
            LED_1=0;
            MyState=0;
            if(IL==1){
IL=0;
                    
}
            break;
        default:
            break;
    }

}


DLL_EXPORT void OnTimer()
{
    switch (CurGame)
    {
        case 9:
            break;
        case 10:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            break;
        case 0:
            Game0();
            break;
        default:
            break;
    }
}


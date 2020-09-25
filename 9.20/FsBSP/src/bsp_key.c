#include "bsp_key.h"

u8 keyVal_o = 0;					//按键通码断码缓冲

/* **************************************************
 * 函数名称 : key_detection
 * 函数描述 ：比较按键前后状态
 * 输入参数 ： GPIOx 端口 ,Pinx 引脚
* 输出参数 ：key_dn  1: 按键与上次状态不一致  
****************************************************/
bit key_detection(u8 GPIOx , u8 Pinx)
{
	 bit key_dn;
	 static bit key_o = 1;    //上一次按键状态
   bit key_n;                 //当前按键状态
   if(GPIO_ReadPin(GPIOx , Pinx) != LOW) //按键没被按下
     key_n = 1;
   else
     key_n = 0;
   key_dn = (key_n ^ key_o) & key_o; //判断按键是否按下
	 key_o = key_n;
	 return key_dn;
}

/* **************************************************
 * 函数名称 : ReadLine
 * 函数描述 : 行列式键盘读取一行值
 * 输入参数 ：KeyState *keystate
 * 输出参数 ：无
****************************************************/
void ReadLine(KeyState *keystate, u8 *isTime2GetKeyVal)
{
	static u8 keyPress_o = 0x00;		//上一次按键状态
	u8 keyVal = 0x00;		//本次读取值
	keyVal = ~((P3 & 0x0f) | 0xf0); //读取按键,行列值拼接取反
	if((keyVal ^ keyPress_o) & keyVal)		//若与上一次该行的记录值不同
	{
		*isTime2GetKeyVal = 1;						//产生译码标记	 
		if(keyVal & 0x0f)								//若按下行为
		{	
			*keystate = KeyDn;						//修改按键状态值（目前不构成状态机，留个坑）
			keyVal_o = keyVal;		//按键缓存，支持延迟响应
		}
		else										//若释放按键
		{
			*keystate = KeyUp;						//修改按键状态值（目前不构成状态机，留个坑）
			keyVal_o = 0xaa;		//产生断码，支持延迟响应	
		}
	}
	else if(keyVal & 0x0f)		//若按住
	{	
		*keystate = KeyHd;	
	}	
	else
		*keystate = NoKey;		//无按键
	keyPress_o = keyVal;	//记录本行读取值
}

u8 GetKeyNum(void)
{
	u8 keyNum = 0xff;			//无码
	switch(keyVal_o)
	{
		case 0x01:	keyNum = 1; break;
		case 0x02:	keyNum = 2; break;	
		case 0x04:	keyNum = 3; break;
		case 0x08:	keyNum = 4; break;
		case 0xaa:	keyNum = 0xaa; break;	//转发断码标记
		default:	break;
	}
	return keyNum;	
}

#define POWER_KEY   		P15
#define KEY_VALUE			1
#define KEY_NULL			0

//定义长按键的TICK数,以及连_发间隔的TICK数
#define KEY_LONG_PERIOD		100
#define KEY_CONTINUE_PERIOD	25
//定义按键返回值状态(按下,长按,连_发,释放)
#define KEY_DOWN		1
#define KEY_short		2
#define KEY_LONG		3
#define KEY_CONTINUE	4
#define KEY_UP			5
//定义按键状态
#define KEY_STATE_INIT		0	//初始状态
#define KEY_STATE_WOBBLE	1	//消抖状态
#define KEY_STATE_PRESS		2	//按下状态
#define KEY_STATE_LONG		3	//长按状态
#define KEY_STATE_CONTINUE	4	//连按状态
#define KEY_STATE_RELEASE	5	//释放状态

void KeyInit(void) 
{
	POWER_KEY = 1;
}
static uint8 KeyScan(void) 
{ 
	if(POWER_KEY == 0)return KEY_VALUE;
	return KEY_NULL; 
}�
void GetKey( uint8 *pKeyValue )
{
	static uint8 s_u8KeyState = KEY_STATE_INIT;
	static uint8 s_u8KeyTimeCount = 0;
	static uint8 s_u8LastKey = KEY_NULL;
	uint8 KeyTemp = KEY_NULL;
	
	KeyTemp = KeyScan();
	switch(s_u8KeyState)
	{
		case	KEY_STATE_INIT:
			if( KEY_NULL != KeyTemp )
			{
				s_u8KeyState = KEY_STATE_WOBBLE;
			}
			break;
			
		case	KEY_STATE_WOBBLE:
			s_u8KeyState = KEY_STATE_PRESS;
			break;
		
		case	KEY_STATE_PRESS:
			if( KEY_NULL != KeyTemp )
			{
				s_u8LastKey = KeyTemp;
				KeyTemp |= KEY_DOWN;
				s_u8KeyState = KEY_STATE_LONG;
			}
			else
			{
				s_u8KeyState = KEY_STATE_INIT;
			}
			break;
			
		case	KEY_STATE_LONG:
			if( KEY_NULL != KeyTemp )
			{
				if( ++s_u8KeyTimeCount > KEY_LONG_PERIOD )
				{
					s_u8KeyTimeCount = 0;
					POWER_KEY_4052++;
					s_u8KeyState = KEY_STATE_CONTINUE;
				}
			}
			else
			{
				KeyTemp |= KEY_short;
				s_u8KeyState = KEY_STATE_RELEASE;
			}
			break;
			
		case	KEY_STATE_CONTINUE:
			if( KEY_NULL != KeyTemp )
			{
				if( ++s_u8KeyTimeCount > KEY_CONTINUE_PERIOD )
				{
					s_u8KeyTimeCount = 0;
					KeyTemp |= KEY_CONTINUE;
				}
			}
			else
			{
				s_u8KeyState = KEY_STATE_RELEASE;
			}
			break;
		
		case	KEY_STATE_RELEASE:
			s_u8LastKey = KEY_UP;
			KeyTemp = s_u8LastKey;
			s_u8KeyState = KEY_STATE_INIT;
			break;
		
		default:
			break;
	}
	*pKeyValue = KeyTemp;
}


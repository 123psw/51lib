# ifndef __common_h__
# define __common_h__
#include <STC15F2K60S2.h>
typedef enum{NoKey, KeyDn, KeyHd, KeyUp}KeyState;		
typedef enum{ParameterSettings,ConfirmTheAcquisition,TemperatureDisplay
}TemperatureRecordStatus;

typedef enum{FALSE,TRUE} BOOL;

# endif
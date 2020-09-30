#include "main.h"
#include "GDEHDotDisp.h"
/***** for test u shotld configure your ports in Display_EPD_W21.h*************/
/******U should remake definitions for work with ports*************************/
/******In Display_EPD_W21.c u need to edit Port_Configs()**********************
*******function to configue input/output ports*********************************
******************************************************************************/
int main()
{
/*******************Here U Should Configure your Ports**************************************/
Port_Configs();
/*******************Now test parameters for GDEH Disp***************************************/
/*******************This parameters was tested in stm32f0Discovery with display GDEH0213z98*/

  GDEH_GATE_VOLTAGE VOLT=VGH_20;
  GDEH_ENTRY_SEQ SQ=0x00;
  GDEH_WFM_CTL WFM={0x00,0x00,0x00,0x05};
  GDEH_Display_Update UPD={0x00, 0x80, EN_CLK_EN_AN_T_LUTM1_DSB_CLK_DSB_OSC};
  GDEH GDE={3,GDEH_DEFAULT_GATE_SCAN_DIR,128,296,VOLT,SQ,WFM,UPD};
  
  while(1)
  {

	  GDEH_INIT(GDE); //initialization 
	  //GDEH_CLEAR(4000);//clear
	  GDEH_WRITE(gImage_BW,gImage_R,4000, 1); // write Image, SIZE=(GDEH.height/8)*GDEH.width
	  GDEH_GO_SLEEP(GDEH_SM_1); //deep Sleep
	  driver_delay_xms(15000);
  }
return 0;
}

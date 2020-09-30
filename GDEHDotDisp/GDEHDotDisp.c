#include "GDEHDotDisp.h"

void GDEH_BUSY_CHECK()
{
while(isEPD_W21_BUSY);
}

void GDEH_INIT(GDEH GDE)
{
	EPD_W21_Init();

	GDEH_BUSY_CHECK();
	GDEH_RESET;

	EPD_W21_WriteCMD(GDEH_DRIVER_CONTROL_CMD);

	uint8_t temp=((GDE.width-1)&0xFF);
	EPD_W21_WriteDATA(temp);

	temp=GDE.width>>8&0xff;
	EPD_W21_WriteDATA(temp);

	if(!GDE.gate_drive)EPD_W21_WriteDATA(GDEH_DEFAULT_GATE_SCAN_DIR);
    else EPD_W21_WriteDATA(GDE.gate_drive);

	/*if(!GDE.VOLTAGE)GDEH_WRITE_VOLTAGE(GDEH_DEFAULT_VOLTAGE);
	else GDEH_WRITE_VOLTAGE(GDE.VOLTAGE);

	GDEH_WRITE_SOURCE_VOLTAGE(15,-15);
	 */
	//GDEH_INITIAL_CODE;

	if(!GDE.SEQUENCE)GDEH_ENTRYMODE_SETTINGS(0x01);
	else GDEH_ENTRYMODE_SETTINGS(GDE.SEQUENCE);

	GDEH_SET_POSITION(0,GDE.height, GDE.width,0);

	if(!GDE.WFV.TRANS_CNTL)
	{
		GDEH_WFM_CTL WFM={0x00, 0x00,0x00,GDEH_WFM_CTL_DEFAULT};
		GDEH_WAVEFORM_CTL(GDE.WFV);
	}
	else GDEH_WAVEFORM_CTL(GDE.WFV);

	if(!GDE.UPD.ColorOpt)
	{
		GDEH_Display_Update UPD;
		UPD.ColorOpt=0x00;
		UPD.SourceMode=0x80;
		UPD.StageMaster=0xF7;
		GDEH_UPD_CNT(UPD);
	}
	else GDEH_UPD_CNT(GDE.UPD);

	GDEH_SET_ADDRESS_CNTR(0, GDE.width);

}

void GDEH_WRITE_VOLTAGE(GDEH_GATE_VOLTAGE Voltage)
{
	EPD_W21_WriteCMD(GDEH_DRIVING_VOLTAGE_CMD);
	EPD_W21_WriteDATA(Voltage);
}

void GDEH_WRITE_SOURCE_VOLTAGE(float Voltage, float VSL)
{
  uint8_t V;
  if(Voltage>8.9) V=Voltage*10;
  else V=Voltage*5;
  EPD_W21_WriteCMD(GDEH_DRIVING_VOTLTAGE_SRC_CMD);
  EPD_W21_WriteDATA(V);
  EPD_W21_WriteDATA(0x01);
  EPD_W21_WriteDATA(abs(VSL*2));
}




void GDEH_WRITE_REG_INI_CODE()
{
	EPD_W21_WriteCMD(GDEH_INITIAL_CODE_SETTING_CMD);
	EPD_W21_WriteDATA(0x01);
	EPD_W21_WriteDATA(0x01);
	EPD_W21_WriteDATA(0x01);
}

uint8_t GDEH_READ_REG()
{
	EPD_W21_WriteCMD(GDEH_READ_INITIAL_CODE_SETTINGS_CMD);
	return SPI_Read();
}

void GDEH_BOOST_START(GDEH_SOFT_START SOFT)
{
	EPD_W21_WriteCMD(GDEH_READ_INITIAL_CODE_SETTINGS_CMD);
	EPD_W21_WriteDATA(SOFT.A_phase);
	EPD_W21_WriteDATA(SOFT.B_phase);
	EPD_W21_WriteDATA(SOFT.C_phase);
	EPD_W21_WriteDATA(SOFT.D_duration);
}

void GDEH_GO_SLEEP(GDEH_DEEP_SLEEP Sleep)
{
	EPD_W21_WriteCMD(GDEH_DEEP_SLEEP_MODE_CMD);
	EPD_W21_WriteDATA(Sleep);
	driver_delay_xms(100);
}

void GDEH_ENTRYMODE_SETTINGS(GDEH_ENTRY_SEQ SEQ)
{
	EPD_W21_WriteCMD(GDEH_DATA_ENTRY_MODE_SETTING_CMD);
	EPD_W21_WriteDATA(SEQ);
}



void GDEH_VCI_DETECTION(GDEH_VCI_DETECT VCI)
{
	EPD_W21_WriteCMD(GDEH_VCI_DETECTION_CMD);
	EPD_W21_WriteDATA(VCI);
	GDEH_BUSY_CHECK();
}


void GDEH_TEMP_CNTL(uint16_t SensCNT)
{
	EPD_W21_WriteCMD(GDEH_TEMP_SENSOR_CNTL_CHS_CMD);
	EPD_W21_WriteDATA(SensCNT&0xFF);
	EPD_W21_WriteDATA((SensCNT>>8)&0xFF);
	GDEH_BUSY_CHECK();
}


uint16_t GDEH_TEMP_READ()
{
	uint16_t temp=0;

	return 	temp;
}



void GDEH_UPD_CNT(GDEH_Display_Update UPD)
{
	EPD_W21_WriteCMD(GDEH_DISPLAY_UPD_CNTL_CMD);
	EPD_W21_WriteDATA(UPD.ColorOpt);
	EPD_W21_WriteDATA(UPD.SourceMode);
	EPD_W21_WriteCMD(GDEH_DISPLAY_UPD_CNTL_2_CMD);
	EPD_W21_WriteDATA(UPD.StageMaster);

}


uint8_t GDEH_READ_RAM()
{
uint8_t readed=0;

return readed;
}

void GDEH_VCOM_SENSE_Duration(uint8_t Duration)
{
	EPD_W21_WriteCMD(GDEH_VCOM_SENS_CMD);
	EPD_W21_WriteCMD(GDEH_VCOM_SENSE_DURATION_CMD);
	EPD_W21_WriteDATA(Duration);
	GDEH_BUSY_CHECK();
}




uint8_t GDEH_WRITE_VCOM(float VCOM) //return
{
	uint8_t temp= abs(VCOM*10)*4;
	EPD_W21_WriteCMD(GDEH_WR_VCOM_REG_CMD);
	EPD_W21_WriteDATA(temp);
	GDEH_BUSY_CHECK();
	return temp;
}



void GDEH_WRITE_REGS_FOR_DISP_OPT_USER(uint8_t* DATA, uint8_t user)
{
	if(user) EPD_W21_WriteCMD(GDEH_WR_REG_USER_ID_CMD);
	else EPD_W21_WriteCMD(GDEH_WR_REG_DISP_IOT_CMD);
	for(uint8_t i=0; i<10;i++)
	{
		EPD_W21_WriteDATA(DATA+i);
	}

}

void GDEH_WAVEFORM_CTL(GDEH_WFM_CTL WFM)
{
	EPD_W21_WriteCMD(GDEH_WVF_CNTL_CMD);
	uint8_t WF=WFM.VBD<<6|WFM.VBD_FLS<<4|WFM.TRANS_CNTL<<2|WFM.VBD_LUT;
	EPD_W21_WriteDATA(WF);
	//EPD_W21_WriteDATA(0x05);
}


void GDEH_SET_POSITION(uint8_t X_Start, uint8_t X_End, uint16_t Y_Start, uint16_t Y_End)
{
	EPD_W21_WriteCMD(GDEH_SET_X_ADDR_START_END_CMD);
	EPD_W21_WriteDATA(X_Start);
	uint8_t temp= (X_End/8)-1;
	EPD_W21_WriteDATA(temp);
	EPD_W21_WriteCMD(GDEH_SET_Y_ADDR_START_END_CMD);
	EPD_W21_WriteDATA(Y_Start);
	EPD_W21_WriteDATA((Y_Start>>8)&0x01);
	EPD_W21_WriteDATA(Y_End);
	EPD_W21_WriteDATA((Y_End>>8)&0x01);

}

void GDEH_SET_ADDRESS_CNTR(uint8_t ADRX, uint16_t ADRY)
{
	ADRY=ADRY-1;
	EPD_W21_WriteCMD(GDEH_XSET_CNTR_CMD);
	EPD_W21_WriteDATA(ADRX);

	EPD_W21_WriteCMD(GDEH_YSET_CNTR_CMD);
	EPD_W21_WriteDATA(ADRY&0xFF);
	EPD_W21_WriteDATA((ADRY>>8)&0xFF);
	GDEH_BUSY_CHECK();
}

/*******************USER FUNCTIONS***************/
void GDEH_UPDATE()
{
	  EPD_W21_WriteCMD(GDEH_DISPLAY_UPD_CNTL_2_CMD ); //Display Update Control
	  EPD_W21_WriteDATA(EN_CLK_EN_AN_T_LUTM1_DSB_CLK_DSB_OSC);
	  EPD_W21_WriteCMD(GDEH_MASTER_ACTIVATION_CMD);  //Activate Display Update Sequence
	  GDEH_BUSY_CHECK();
}



void GDEH_WRITE(uint8_t *BLACK_WHITE, uint8_t* RED, int SIZE, uint8_t INVERSE)
{
	GDEH_Write_BW;
	for(int i=0; i<SIZE; i++)
	{
		EPD_W21_WriteDATA(*BLACK_WHITE);
		BLACK_WHITE++;
	}
	GDEH_Write_RED;
	for(int i=0; i<SIZE; i++)
	{
		if(!INVERSE) EPD_W21_WriteDATA(*RED);
		else EPD_W21_WriteDATA(~(*RED));
		RED++;
	}
	GDEH_UPDATE();
}

void GDEH_CLEAR(int SIZE)
{
	GDEH_Write_BW;
	for(int i=0; i<SIZE; i++)
	{
		EPD_W21_WriteDATA(0xFF);
	}
	GDEH_Write_RED;
	for(int i=0; i<SIZE; i++)
	{
		EPD_W21_WriteDATA(0x00);
	}
	GDEH_UPDATE();
}


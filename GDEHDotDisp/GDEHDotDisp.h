#ifndef __GDEHDOTDISP_H
#define __GDEHDOTDISP_H

#include "Display_EPD_W21_spi.h"
#include "Display_EPD_W21.h"

#define GDEH_DRIVER_CONTROL_CMD 0X01
#define GDEH_DRIVING_VOLTAGE_CMD 0x03
#define GDEH_DRIVING_VOTLTAGE_SRC_CMD 0x04
#define GDEH_INITIAL_CODE_SETTING_CMD 0x08
#define GDEH_WRITE_INITIAL_CODE_SETTINGS_CMD 0x09
#define GDEH_READ_INITIAL_CODE_SETTINGS_CMD 0x0A //don't use at 3-wire SPI
#define GDEH_BOOSTED_SOFT_START_CONTROL_CMD 0x0C
#define GDEH_DEEP_SLEEP_MODE_CMD 0x10
#define GDEH_DATA_ENTRY_MODE_SETTING_CMD 0x11 //filling display
#define GDEH_SW_RESET_CMD 0x12
#define GDEH_HV_READY_DETECTION_CMD 0x14
#define GDEH_VCI_DETECTION_CMD 0x15

#define GDEH_TEMP_SENSOR_CNTL_CHS_CMD 0x18
#define GDEH_TEMP_SENSOR_CNTL_WRITE_CMD 0x1A
#define GDEH_TEMP_SENSOR_CNTL_READ_CMD 0x1B
#define GDEH_TEMP_SENSOR_CNTL_EXTERNALCMD_CMD 0x1C

#define GDEH_MASTER_ACTIVATION_CMD 0x20
#define GDEH_DISPLAY_UPD_CNTL_CMD 0x21
#define GDEH_DISPLAY_UPD_CNTL_2_CMD 0x22

#define GDEH_WRITE_BW_CMD 0x24
#define GDEH_WRITE_RED_CMD 0x26
#define GDEH_READ_RAM_CMD 0x27

#define GDEH_VCOM_SENS_CMD 0x28
#define GDEH_VCOM_SENSE_DURATION_CMD 0x29
#define GDEH_PRG_VCOM_OTP_CMD 0x2A
#define GDEH_WR_VCOM_CNTL_CMD 0x2B
#define GDEH_WR_VCOM_REG_CMD 0x2C
#define GDEH_OTP_REG_READ_CMD 0x2D

#define GDEH_USER_ID_READ_CMD 0x2E
#define GDEH_STATUS_BIT_READ_CMD 0x2F
#define GDEH_WR_REG_DISP_IOT_CMD 0x37
#define GDEH_WR_REG_USER_ID_CMD 0x38

#define GDEH_WVF_CNTL_CMD 0x3C
#define GDEH_READ_RAM_OPT_CMD 0x41
#define GDEH_SET_X_ADDR_START_END_CMD 0x44
#define GDEH_SET_Y_ADDR_START_END_CMD 0x45
#define GDEH_AUTO_RED_CMD 0x46
#define GDEH_AUTO_BW_CMD 0x47
#define GDEH_XSET_CNTR_CMD 0x4E
#define GDEH_YSET_CNTR_CMD 0x4F
#define GDEH_TERMINATOR_CMD 0x7F

/********************Commands***********************/
#define GDEH_RESET {EPD_W21_WriteCMD(GDEH_SW_RESET_CMD);GDEH_BUSY_CHECK();}
#define GDEH_INITIAL_CODE EPD_W21_WriteCMD(GDEH_INITIAL_CODE_SETTING_CMD);
#define GDEH_MASTER_ACTIVATE EPD_W21_WriteCMD(GDEH_MASTER_ACTIVATION_CMD);
#define GDEH_Write_BW {EPD_W21_WriteCMD(GDEH_WRITE_BW_CMD);}
#define GDEH_Write_RED {EPD_W21_WriteCMD(GDEH_WRITE_RED_CMD);}
#define GDEH_PROGRAM_OTP EPD_W21_WriteCMD(GDEH_PRG_VCOM_OTP_CMD)
#define GDEH_WRITE_REG_VCOM_CNTL {EPD_W21_WriteCMD(GDEH_WR_VCOM_CNTL_CMD);\
EPD_W21_WriteDATA(0x04);\
EPD_W21_WriteDATA(0x63);}
#define GDEH_AUTO_RED(_byte) {EPD_W21_WriteCMD(GDEH_AUTO_RED_CMD);EPD_W21_WriteDATA(_byte);}
#define GDEH_AUTO_BW(_byte) {EPD_W21_WriteCMD(GDEH_AUTO_BW_CMD);EPD_W21_WriteDATA(_byte);}
#define GDEH_TERMINATOR EPD_W21_WriteCMD(GDEH_TERMINATOR_CMD )
/************Gate Scanning*****************/

#define GDEH_GD 0x04
#define GDEH_SM 0x02
#define GDEH_TB 0x01
#define GDEH_DEFAULT_GATE_SCAN_DIR 0x00


/*****Voltage Parameters*****/
#define GDEH_DEFAULT_VOLTAGE VGH_20

typedef enum GDEH_Gate_Voltage
{
	VGH_20=0x00,
	VGH_10=0x03,
	VGH_10_5=0x04,
	VGH_11=0x05,
	VGH_11_5=0x06,
	VGH_12=0x07,
	VGH_12_5=0x08,
	VGH_13=0x09,
	VGH_13_5=0x0A,
	VGH_14=0x0B,
	VGH_14_5=0x0C,
	VGH_15=0x0D,
	VGH_15_5=0x0E,
	VGH_16=0x0F,
	VGH_16_5=0x10,
	VGH_17=0x11,
	VGH_17_5=0x12,
	VGH_18=0x13,
	VGH_18_5=0x14,
	VGH_19=0x15,
	VGH_19_5=0x16,
	VGH_20_0=0x17
}GDEH_GATE_VOLTAGE;

/***********Soft start*****************/
typedef struct GDEH_SOFT_START  //default 0x17
{
	uint8_t A_phase;
	uint8_t B_phase;
	uint8_t C_phase;
	uint8_t D_duration;
}GDEH_SOFT_START;

/*******Deep Sleep************/
typedef enum GDEH_DEEP_SLEEP
{
	GDEH_NM_SL=0x00,
	GDEH_SM_1=0x01,
	GDHE_SM_2=0x02
}GDEH_DEEP_SLEEP;

/**********Enter data sequence************/
typedef enum GDEH_ENTRY_SEQ // AM- high bit 0- address update from X, 1- from Y
{
    Ax_Yd_Xd=0x00,
    Ax_Yd_Xi=0x01,
    Ax_Yi_Xd=0x02,
    Ax_Yi_Xi=0x03,
    Ay_Yd_Xd=0x04,
    Ay_Yd_Xi=0x05,
    Ay_Yi_Xd=0x06,
    Ay_Yi_Xi=0x07,
}GDEH_ENTRY_SEQ;
/*****************VCI DETECTION**********************/
typedef enum GDEH_VCI_DETECT
{
	VCI_2_2=0x03,
	VCI_2_3=0x04,
	VCI_2_4=0x05,
	VCI_2_5=0x06,
	VCI_2_6=0x07
}GDEH_VCI_DETECT;

/************RAM content Options********/
typedef enum GDEH_STAGE_MASTER
{
 EN_CLK=0x80,
 DSB_CLK=0x01,
 EN_CLK_EN_AN=0xC0,
 DSB_AN_DSB_CLK=0x03,
 EN_CLK_LUTM1_DSB_CLK=0x91,
 EN_CLK_LUTM2_DSB_CLK=0x99,
 EN_CLK_T_LUTM1_DSB_CLK=0xB1,
 EN_CLK_T_LUTM2_DSB_CLK=0xB9,
 EN_CLK_T_LUTM1_DSB_CLK_DSB_OSC=0xC7,
 EN_CLK_T_LUTM2_DSB_CLK_DSB_OSC=0xCF,
 EN_CLK_EN_AN_T_LUTM1_DSB_CLK_DSB_OSC=0xF7,
 EN_CLK_EN_AN_T_LUTM2_DSB_CLK_DSB_OSC=0xFF,
}GDEH_STAGE_MASTER;


typedef struct GDEH_DISPLAY_UPDATE
{
	uint8_t ColorOpt;
	uint8_t SourceMode;
	GDEH_STAGE_MASTER StageMaster;
}GDEH_Display_Update;
/****************Write VCOM reg*****************/
uint8_t GDEH_WRITE_VCOM(float VCOM); //return


/***************Border Waveform Conrol**********************/

typedef enum GDEH_VDB_OPT
{
	GS_TRANSITION=0x00,
	FIX_LEVEL=0x01,
	VCOM=0x02,
	Hiz=0x04
}GDEH_VDB_OPT;

typedef enum GDEH_FLS_VBD
{
	VSS=0x00,
	VSH1=0x01,
	VSL=0x02,
	VSH2=0x04
}GDEH_FLS_VBD;


typedef enum GDEH_TRANS_CNTL
{
	VCOM_RED=0x00,
	FOLLOW_LUT=0x01
}GDEH_TRANS_CNTL;

typedef enum GDEH_TRANS_ST_VBD
{
	LUT0=0x00,
	LUT1=0x01,
	LUT2=0x02,
	LUT3=0x04
}GDEH_TRANS_ST_VBD;


typedef struct GDEH_WFM_CTL
{
	GDEH_VDB_OPT VBD;
	GDEH_FLS_VBD VBD_FLS;
	GDEH_TRANS_CNTL TRANS_CNTL;
	GDEH_TRANS_ST_VBD VBD_LUT;
}GDEH_WFM_CTL;

#define GDEH_WFM_CTL_DEFAULT 0x05
/**********Display structure****************/

typedef struct GDEH
{
	uint8_t connect_type;
	uint8_t gate_drive;
	uint8_t height;
	uint16_t width;
	GDEH_GATE_VOLTAGE VOLTAGE;
	GDEH_ENTRY_SEQ SEQUENCE;
	GDEH_WFM_CTL WFV;
	GDEH_Display_Update UPD;

}GDEH;

void GDEH_INIT(GDEH);
void GDEH_WRITE_VOLTAGE(GDEH_GATE_VOLTAGE);
void GDEH_WRITE_SOURCE_VOLTAGE(float,float);
void GDEH_WRITE_REG_INI_CODE();
void GDEH_BUSY_CHECK();
uint8_t GDEH_READ_REG();
void GDEH_BOOST_START(GDEH_SOFT_START);
void GDEH_GO_SLEEP(GDEH_DEEP_SLEEP);
void GDEH_ENTRYMODE_SETTINGS(GDEH_ENTRY_SEQ);
void GDEH_VCI_DETECTION(GDEH_VCI_DETECT);
void GDEH_TEMP_CNTL(uint16_t);
void GDEH_UPD_CNT(GDEH_Display_Update);
void GDEH_VCOM_SENSE_Duration(uint8_t);
uint8_t GDEH_WRITE_VCOM(float);
void GDEH_WRITE_REGS_FOR_DISP_OPT_USER(uint8_t* , uint8_t);
void GDEH_WAVEFORM_CTL(GDEH_WFM_CTL );
void GDEH_SET_POSITION(uint8_t X_Start, uint8_t X_End, uint16_t Y_Start, uint16_t Y_End);
void GDEH_SET_ADDRESS_CNTR(uint8_t ADRX, uint16_t ADRY);
void GDEH_UPDATE();
void GDEH_WRITE(uint8_t *BLACK_WHITE, uint8_t* RED, int SIZE, uint8_t INVERSE);
void GDEH_CLEAR(int SIZE);

/*********Read Functions (not working yet)*****/
void GDEH_RAM_READ();
void GDEH_READ_OTP();
void GDEH_READ_USER_ID();
void GDEH_READ_STATUS_Bit();

#endif


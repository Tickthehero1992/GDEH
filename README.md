GDEH library
Structures info:
GDEH_GATE_VOLTAGE - enum, voltage Variations,
GDEH_SOFT_START-   structure, soft start, usually 0x17, 0x17, 0x17
GDEH_DEEP_SLEEP - enum, sleep variations,
GDEH_ENTRY_SEQ - enum, sequence of display
GDEH_VCI_DETECT - enum, VCI detection parameters
GDEH_STAGE_MASTER - enum, display sequence options, default EN_CLK_EN_AN_T_LUTM1_DSB_CLK_DSB_OSC,
GDEH_Display_Update - struct, display update parameters,
GDEH_VDB_OPT- enum, VBD options,
GDEH_FLS_VBD - enum, VBD fixed level,
GDEH_TRANS_CNTL - enum, transitional control,
GDEH_TRANS_ST_VBD - enum, GS transition settings for VBD,
GDEH_WFM_CTL - struct, waveform parameters
GDEH - structure, display parameters. 
 -connect_type - 3|4-wire SPI (not realized yet),
 -gate_drive- display gates parameter, usually 0x00,
 -height-height,
 -width-width (p.s width>height),
 -VOLTAGE - diplay voltage, defualt VGH_20,
 -SEQ - display sequence, default 0x01,
 -UPD - update type, default 0x00, 0x80, 0xF7.
 -WFV - waveform, default 0x00,0x00,0x00,0x01,0x01
	
Main functions:

GDEH_RESET -reset display,
GDEH_INITIAL_CODE - initial command,
GDEH_MASTER_ACTIVATE - activate command
GDEH_Write_BW - write Black White pallet command
GDEH_Write_RED - write Red pallet command
GDEH_PROGRAM_OTP - Write OTP_VCOM
GDEH_WRITE_REG_VCOM_CNTL - Write Register Vcom Control
GDEH_AUTO_RED(_byte) - auto filling red bytes,
GDEH_AUTO_BW(_byte)  - auto filling black and white
GDEH_TERMINATOR - terminate command creation.

void GDEH_INIT(GDEH)- init GDEH display;
void GDEH_WRITE_VOLTAGE(GDEH_GATE_VOLTAGE) - setup Voltage;
void GDEH_WRITE_SOURCE_VOLTAGE(float,float) - source of Voltage
void GDEH_WRITE_REG_INI_CODE() - 
void GDEH_BUSY_CHECK() - check busy state.
uint8_t GDEH_READ_REG()- read register.
void GDEH_BOOST_START(GDEH_SOFT_START) - soft start with own parameters.
void GDEH_GO_SLEEP(GDEH_DEEP_SLEEP) - GDEH sleep 
void GDEH_ENTRYMODE_SETTINGS(GDEH_ENTRY_SEQ) - squence to fill display.
void GDEH_VCI_DETECTION(GDEH_VCI_DETECT) - detect VCI.
void GDEH_TEMP_CNTL(uint16_t) - temperature sensor control setups
void GDEH_UPD_CNT(GDEH_Display_Update) - setup display updates
void GDEH_VCOM_SENSE_Duration(uint8_t) - ground sense duration setup
uint8_t GDEH_WRITE_VCOM(float) - Write VCOM voltage
void GDEH_WRITE_REGS_FOR_DISP_OPT_USER(uint8_t* , uint8_t) - write display options
void GDEH_WAVEFORM_CTL(GDEH_WFM_CTL )- edit waveform control
void GDEH_SET_POSITION(uint8_t X_Start, uint8_t X_End, uint16_t Y_Start, uint16_t Y_End)-position of start painting
void GDEH_SET_ADDRESS_CNTR(uint8_t ADRX, uint16_t ADRY)-cntr address // usually all addreses
void GDEH_UPDATE() - update display
void GDEH_WRITE(uint8_t *BLACK_WHITE, uint8_t* RED, int SIZE, uint8_t INVERSE) - paint Picture array
void GDEH_CLEAR(int SIZE) - clear Display

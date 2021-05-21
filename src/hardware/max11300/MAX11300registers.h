
#ifndef __MAX11300_REG_H__
#define __MAX11300_REG_H__

// Configuration registers
#define MAX_DEVICE_ID 		0x00
#define MAX_INT				0x01
#define MAX_ADCST			0x02
#define MAX_ADCST_LEN		2
#define MAX_ADCST_L			0x02
#define MAX_ADCST_H			0x03
#define MAX_DACOI			0x04
#define MAX_DACOI_LEN		2
#define MAX_DACOI_L			0x04
#define MAX_DACOI_H			0x05
#define MAX_GPIST			0x06
#define MAX_GPIST_LEN		2
#define MAX_GPIST_L			0x06
#define MAX_GPIST_H			0x07
#define MAX_DEVCTL			0x10
#define MAX_INTMASK			0x11
#define MAX_GPIMD			0x12
#define MAX_GPIMD_LEN		3
#define MAX_GPIMD_0_7		0x12
#define MAX_GPIMD_8_15		0x13
#define MAX_GPIMD_16_19		0x14
#define MAX_DACPRSTDAT1		0x16
#define MAX_DACPRSTDAT2		0x17
#define MAX_TMPMONCFG		0x18
#define MAX_TMPINTHI		0x19
#define MAX_TMPINTLO		0x1a
#define MAX_TMPEXT1HI		0x1b
#define MAX_TMPEXT1LO		0x1c
#define MAX_TMPEXT2HI		0x1d
#define MAX_TMPEXT2LO		0x1e

// Port configuration registers
#define MAX_FUNC_BASE		0x20
#define MAX_FUNC_0			0x20
#define MAX_FUNC_1			0x21
#define MAX_FUNC_2			0x22
#define MAX_FUNC_3			0x23
#define MAX_FUNC_4			0x24
#define MAX_FUNC_5			0x25
#define MAX_FUNC_6			0x26
#define MAX_FUNC_7			0x27
#define MAX_FUNC_8			0x28
#define MAX_FUNC_9			0x29
#define MAX_FUNC_10			0x2a
#define MAX_FUNC_11			0x2b
#define MAX_FUNC_12			0x2c
#define MAX_FUNC_13			0x2d
#define MAX_FUNC_14			0x2e
#define MAX_FUNC_15			0x2f
#define MAX_FUNC_16			0x30
#define MAX_FUNC_17			0x31
#define MAX_FUNC_18			0x32
#define MAX_FUNC_19			0x33

// Temperature data registers
#define MAX_TMPINTDAT		0x08
#define MAX_TMPEXT1DAT		0x09
#define MAX_TMPEXT2DAT		0x0a

// GPIO data registers
#define MAX_GPIDAT			0x0b
#define MAX_GPIDAT_LEN		2
#define MAX_GPIDAT_L		0x0b
#define MAX_GPIDAT_H		0x0c
#define MAX_GPODAT			0x0d
#define MAX_GPODAT_LEN		2
#define MAX_GPODAT_L		0x0d
#define MAX_GPODAT_H		0x0e

// ADC data registers
#define MAX_ADCDAT_BASE		0x40
#define MAX_ADCDAT_0		0x40
#define MAX_ADCDAT_1		0x41
#define MAX_ADCDAT_2		0x42
#define MAX_ADCDAT_3		0x43
#define MAX_ADCDAT_4		0x44
#define MAX_ADCDAT_5		0x45
#define MAX_ADCDAT_6		0x46
#define MAX_ADCDAT_7		0x47
#define MAX_ADCDAT_8		0x48
#define MAX_ADCDAT_9		0x49
#define MAX_ADCDAT_10		0x4a
#define MAX_ADCDAT_11		0x4b
#define MAX_ADCDAT_12		0x4c
#define MAX_ADCDAT_13		0x4d
#define MAX_ADCDAT_14		0x4e
#define MAX_ADCDAT_15		0x4f
#define MAX_ADCDAT_16		0x50
#define MAX_ADCDAT_17		0x51
#define MAX_ADCDAT_18		0x52
#define MAX_ADCDAT_19		0x53

// DAC data registers
#define MAX_DACDAT_BASE		0x60
#define MAX_DACDAT_0		0x60
#define MAX_DACDAT_1		0x61
#define MAX_DACDAT_2		0x62
#define MAX_DACDAT_3		0x63
#define MAX_DACDAT_4		0x64
#define MAX_DACDAT_5		0x65
#define MAX_DACDAT_6		0x66
#define MAX_DACDAT_7		0x67
#define MAX_DACDAT_8		0x68
#define MAX_DACDAT_9		0x69
#define MAX_DACDAT_10		0x6a
#define MAX_DACDAT_11		0x6b
#define MAX_DACDAT_12		0x6c
#define MAX_DACDAT_13		0x6d
#define MAX_DACDAT_14		0x6e
#define MAX_DACDAT_15		0x6f
#define MAX_DACDAT_16		0x70
#define MAX_DACDAT_17		0x71
#define MAX_DACDAT_18		0x72
#define MAX_DACDAT_19		0x73

// Interrupt register fields
#define MAX_VMON			0x0f
#define MAX_TMPEXT2			0x0c
#define MAX_TMPEXT2_AVAIL	0x0c
#define MAX_TMPEXT2_LO		0x0d
#define MAX_TMPEXT2_HI		0x0e
#define MAX_TMPEXT1			0x09
#define MAX_TMPEXT1_AVAIL	0x09
#define MAX_TMPEXT1_LO		0x0a
#define MAX_TMPEXT1_HI		0x0b
#define MAX_TMPINT			0x06
#define MAX_TMPINT_AVAIL	0x06
#define MAX_TMPINT_LO		0x07
#define MAX_TMPINT_HI		0x08
#define MAX_GPIDM			0x04
#define MAX_GPIDR			0x03
#define MAX_ADCDM			0x02
#define MAX_ADCDR			0x01
#define MAX_ADCFLAG			0x00
#define MAX_VMON_MASK		0x8000
#define MAX_TMPEXT2_MASK	0x7000
#define MAX_TMPEXT1_MASK	0x0e00
#define MAX_TMPINT_MASK		0x01c0
#define MAX_DACOI_MASK		0x0020
#define MAX_GPIDM_MASK		0x0010
#define MAX_GPIDR_MASK		0x0008
#define MAX_ADCDM_MASK		0x0004
#define MAX_ADCDR_MASK		0x0002
#define MAX_ADCFLAG_MASK	0x0001

// Device Control register fields
#define MAX_RESET			0x0f
#define MAX_BRST			0x0e
#define MAX_LPEN			0x0d
#define MAX_RS_CANCEL		0x0c
#define MAX_TMPPER			0x0b
#define MAX_TMPCTL			0x08
#define MAX_TMPCTL_0		0x08
#define MAX_TMPCTL_1		0x09
#define MAX_TMPCTL_2		0x0a
#define MAX_THSDN			0x07
#define MAX_DACREF			0x06
#define MAX_ADCCONV			0x04
#define MAX_ADCCONV_0		0x04
#define MAX_ADCCONV_1		0x05
#define MAX_DACCTL			0x02
#define MAX_DACCTL_0		0x02
#define MAX_DACCTL_1		0x03
#define MAX_ADCCTL			0x00
#define MAX_ADCCTL_0		0x00
#define MAX_ADCCTL_1		0x01
#define MAX_TMPCTL_MASK		0x0700
#define MAX_ADCCONV_MASK	0x0030
#define MAX_DACCTL_MASK		0x000c
#define MAX_ADCCTL_MASK		0x0003

// ADC modes
#define MAX_ADC_IDLE				0x0000
#define MAX_ADC_SINGLE_SWEEP		0x0001
#define MAX_ADC_SINGLE_CONVERSION	0x0002
#define MAX_ADC_CONTINUOUS			0x0003

// DAC modes
#define MAX_DAC_SEQUENTIAL		0x0000
#define MAX_DAC_IMMEDIATE		0x0004
#define MAX_DAC_DAT1			0x0008
#define MAX_DAC_DAT2			0x000c

// ADC conversion rate selection
#define MAX_RATE_200			0x0000
#define MAX_RATE_250			0x0010
#define MAX_RATE_333			0x0020
#define MAX_RATE_400			0x0030

// GPIMD register fields
#define MAX_GPIMD_7			0x0e
#define MAX_GPIMD_7_0		0x0e
#define MAX_GPIMD_7_1		0x0f
#define MAX_GPIMD_6			0x0c
#define MAX_GPIMD_6_0		0x0c
#define MAX_GPIMD_6_1		0x0d
#define MAX_GPIMD_5			0x0a
#define MAX_GPIMD_5_0		0x0a
#define MAX_GPIMD_5_1		0x0b
#define MAX_GPIMD_4			0x08
#define MAX_GPIMD_4_0		0x08
#define MAX_GPIMD_4_1		0x09
#define MAX_GPIMD_3			0x06
#define MAX_GPIMD_3_0		0x06
#define MAX_GPIMD_3_1		0x07
#define MAX_GPIMD_2			0x04
#define MAX_GPIMD_2_0		0x04
#define MAX_GPIMD_2_1		0x05
#define MAX_GPIMD_1			0x02
#define MAX_GPIMD_1_0		0x02
#define MAX_GPIMD_1_1		0x03
#define MAX_GPIMD_0			0x00
#define MAX_GPIMD_0_0		0x00
#define MAX_GPIMD_0_1		0x01
#define MAX_GPIMD_15		0x0e
#define MAX_GPIMD_15_0		0x0e
#define MAX_GPIMD_15_1		0x0f
#define MAX_GPIMD_14		0x0c
#define MAX_GPIMD_14_0		0x0c
#define MAX_GPIMD_14_1		0x0d
#define MAX_GPIMD_13		0x0a
#define MAX_GPIMD_13_0		0x0a
#define MAX_GPIMD_13_1		0x0b
#define MAX_GPIMD_12		0x08
#define MAX_GPIMD_12_0		0x08
#define MAX_GPIMD_12_1		0x09
#define MAX_GPIMD_11		0x06
#define MAX_GPIMD_11_0		0x06
#define MAX_GPIMD_11_1		0x07
#define MAX_GPIMD_10		0x04
#define MAX_GPIMD_10_0		0x04
#define MAX_GPIMD_10_1		0x05
#define MAX_GPIMD_9			0x02
#define MAX_GPIMD_9_0		0x02
#define MAX_GPIMD_9_1		0x03
#define MAX_GPIMD_8			0x00
#define MAX_GPIMD_8_0		0x00
#define MAX_GPIMD_8_1		0x01
#define MAX_GPIMD_19		0x06
#define MAX_GPIMD_19_0		0x06
#define MAX_GPIMD_19_1		0x07
#define MAX_GPIMD_18		0x04
#define MAX_GPIMD_18_0		0x04
#define MAX_GPIMD_18_1		0x05
#define MAX_GPIMD_17		0x02
#define MAX_GPIMD_17_0		0x02
#define MAX_GPIMD_17_1		0x03
#define MAX_GPIMD_16		0x00
#define MAX_GPIMD_16_0		0x00
#define MAX_GPIMD_16_1		0x01

// Temperature monitor config register fields
#define MAX_TMPEXT2MONCFG			0x04
#define MAX_TMPEXT2MONCFG_0			0x04
#define MAX_TMPEXT2MONCFG_1			0x05
#define MAX_TMPEXT1MONCFG			0x02
#define MAX_TMPEXT1MONCFG_0			0x02
#define MAX_TMPEXT1MONCFG_1			0x03
#define MAX_TMPINTMONCFG			0x00
#define MAX_TMPINTMONCFG_0			0x00
#define MAX_TMPINTMONCFG_1			0x01
#define MAX_TMPEXT2MONCFG_MASK		0x0030
#define MAX_TMPEXT1MONCFG_MASK		0x000c
#define MAX_TMPINTMONCFG_MASK		0x0003

// Port configuration register fields
#define MAX_FUNCID					0x0c
#define MAX_FUNCPRM					0x00
#define MAX_FUNCPRM_ASSOC			0x00
#define MAX_FUNCPRM_AVG				0x05
#define MAX_FUNCPRM_RANGE			0x08
#define MAX_FUNCPRM_AVR				0x0b
#define MAX_FUNCPRM_INV				0x0b
#define MAX_FUNCID_MASK				0xf000
#define MAX_FUNCPRM_MASK			0x0fff
#define MAX_FUNCPRM_ASSOC_MASK		0x001f
#define MAX_FUNCPRM_AVG_MASK		0x00e0
#define MAX_FUNCPRM_RANGE_MASK		0x0700
#define MAX_FUNCPRM_AVR_MASK		0x0800
#define MAX_FUNCPRM_INV_MASK		0x0800

// Port modes
#define MAX_FUNCID_HI_Z				0x0000
#define MAX_FUNCID_GPI				0x1000
#define MAX_FUNCID_LVL_TRANS_BI		0x2000
#define MAX_FUNCID_GPO				0x3000
#define MAX_FUNCID_GPO_LVL_TRANS	0x4000
#define MAX_FUNCID_DAC				0x5000
#define MAX_FUNCID_DAC_ADCMON		0x6000
#define MAX_FUNCID_ADC				0x7000
#define MAX_FUNCID_ADC_DIFF_POS		0x8000
#define MAX_FUNCID_ADC_DIFF_NEG		0x9000
#define MAX_FUNCID_ADC_DAC_NEG		0xa000
#define MAX_FUNCID_GPI_SWITCH		0xb000
#define MAX_FUNCID_REG_SWITCH		0xc000

// ADC voltage range codes
#define MAX_ADC_RANGE_0_10			0x0100
#define MAX_ADC_RANGE_5_5			0x0200
#define MAX_ADC_RANGE_10_0			0x0300
#define MAX_ADC_RANGE_0_2_5			0x0400

// DAC voltage range codes
#define MAX_DAC_RANGE_0_10			0x0100
#define MAX_DAC_RANGE_5_5			0x0200
#define MAX_DAC_RANGE_10_0			0x0300

// Data register masks
#define MAX_ADC_MASK				0x0fff
#define MAX_DAC_MASK				0x0fff

#endif

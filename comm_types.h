#include "include.h"

/* CONFIG register (0x00)
 * Controls CRC settings, power state, RX/TX mode, and interrupt masks.
 */
typedef struct {
    uint8_t MASK_RX_DR:1;  /* mask RX data ready interrupt */
    uint8_t MASK_TX_DS:1;  /* mask TX data sent interrupt */
    uint8_t MASK_MAX_RT:1; /* mask max retransmit interrupt */
    uint8_t EN_CRC:1;      /* enable CRC */
    uint8_t CRCO:1;        /* CRC length: 0 = 1 byte, 1 = 2 bytes */
    uint8_t PWR_UP:1;      /* power up */
    uint8_t PRIM_RX:1;     /* 1 = RX mode, 0 = TX mode */
    uint8_t RESERVED:1;    /* reserved */
} NRF_ConfigReg_t;

/* RF_SETUP register (0x06)
 * Configures data rate, PA level, and LNA gain.
 */
typedef struct {
    uint8_t CONT_WAVE:1;   /* test mode */
    uint8_t RESERVED:1;    /* reserved */
    uint8_t RF_DR_LOW:1;   /* 250 kbps if 1 and RF_DR_HIGH = 0 */
    uint8_t PLL_LOCK:1;    /* test mode */
    uint8_t RF_DR_HIGH:1;  /* 2 Mbps if 1 and RF_DR_LOW = 0 */
    uint8_t RF_PWR:2;      /* PA level: 00 = MIN, 01 = LOW, 10 = HIGH, 11 = MAX */
    uint8_t LNA_HCUR:1;    /* LNA gain, usually 1 */
} NRF_RFSetupReg_t;

/* STATUS register (0x07)
 * Reports interrupt flags, RX pipe number, and TX FIFO status.
 */
typedef struct {
    uint8_t RX_DR:1;       /* data ready interrupt */
    uint8_t TX_DS:1;       /* data sent interrupt */
    uint8_t MAX_RT:1;      /* max retransmit interrupt */
    uint8_t RX_P_NO:4;     /* pipe number of received payload */
    uint8_t TX_FULL:1;     /* TX FIFO full flag */
} NRF_StatusReg_t;

/* FIFO_STATUS register (0x17)
 * Indicates TX/RX FIFO empty/full and reuse flags.
 */
typedef struct {
    uint8_t TX_REUSE:1;    /* retransmit last payload */
    uint8_t TX_FIFO_FULL:1;/* TX FIFO full flag */
    uint8_t TX_EMPTY:1;    /* TX FIFO empty flag */
    uint8_t RESERVED:1;    /* reserved */
    uint8_t RX_FULL:1;     /* RX FIFO full flag */
    uint8_t RX_EMPTY:1;    /* RX FIFO empty flag */
    uint8_t RESERVED2:2;   /* reserved */
} NRF_FIFOStatusReg_t;

/* EN_AA register (0x01)
 * Enables auto acknowledgment per pipe.
 */
typedef struct {
    uint8_t EN_AA:6;       /* enable auto acknowledgment per pipe */
    uint8_t RESERVED:2;
} NRF_EnableAAReg_t;

/* EN_RXADDR register (0x02)
 * Enables RX addresses for pipes 0–5.
 */
typedef struct {
    uint8_t EN_RXADDR:6;   /* enable RX address per pipe */
    uint8_t RESERVED:2;
} NRF_EnableRxAddrReg_t;

/* SETUP_AW register (0x03)
 * Sets address width (3–5 bytes).
 */
typedef struct {
    uint8_t SETUP_AW:2;    /* address width of TX/RX */
    uint8_t RESERVED:6;
} NRF_SetupAWReg_t;

/* SETUP_RETR register (0x04)
 * Configures auto retransmit delay and retry count.
 */
typedef struct {
    uint8_t ARD:4;         /* auto retransmit delay (250 µs steps) */
    uint8_t ARC:4;         /* auto retransmit count (0–15 retries) */
} NRF_SetupRetrReg_t;

/* RF_CH register (0x05)
 * Sets RF channel frequency (2.400–2.525 GHz).
 */
typedef struct {
    uint8_t RF_CH:7;       /* RF channel (0–125) */
    uint8_t RESERVED:1;
} NRF_RFChannelReg_t;

/* OBSERVE_TX register (0x08)
 * Reports packet loss and retransmit counters.
 */
typedef struct {
    uint8_t PLOS_CNT:4;    /* packet loss counter */
    uint8_t ARC_CNT:4;     /* retransmit counter */
} NRF_ObserveTxReg_t;

/* RPD register (0x09)
 * Received Power Detector (> –64 dBm).
 */
typedef struct {
    uint8_t RPD:1;         /* received power detector */
    uint8_t RESERVED:7;
} NRF_RPDReg_t;

/* RX_ADDR_Px registers (0x0A–0x0F)
 * Receive address for each pipe (3–5 bytes).
 */
typedef struct {
    uint8_t RX_ADDR[5];    /* receive address */
} NRF_RxAddrReg_t;

/* TX_ADDR register (0x10)
 * Transmit address (3–5 bytes).
 */
typedef struct {
    uint8_t TX_ADDR[5];    /* transmit address */
} NRF_TxAddrReg_t;

/* RX_PW_Px registers (0x11–0x16)
 * Payload width for each RX pipe.
 */
typedef struct {
    uint8_t RX_PW:6;       /* payload width (1–32 bytes) */
    uint8_t RESERVED:2;
} NRF_RxPayloadWidthReg_t;

/* FEATURE register (0x1D)
 * Enables dynamic payload, ACK payload, and NOACK command.
 */
typedef struct {
    uint8_t EN_DPL:1;      /* enable dynamic payload length */
    uint8_t EN_ACK_PAY:1;  /* enable payload in ACK packet */
    uint8_t EN_DYN_ACK:1;  /* enable W_TX_PAYLOAD_NOACK command */
    uint8_t RESERVED:5;
} NRF_FeatureReg_t;

/* DYNPD register (0x1C)
 * Enables dynamic payload per pipe.
 */
typedef struct {
    uint8_t DYNPD:6;       /* enable dynamic payload per pipe */
    uint8_t RESERVED:2;
} NRF_DynPayloadReg_t;

/* Master structure: represents the entire nRF24L01+ register map */
typedef struct {
    NRF_ConfigReg_t        CONFIG;        /* 0x00: Configuration register */
    NRF_EnableAAReg_t      EN_AA;         /* 0x01: Enable Auto Acknowledge */
    NRF_EnableRxAddrReg_t  EN_RXADDR;     /* 0x02: Enable RX Addresses */
    NRF_SetupAWReg_t       SETUP_AW;      /* 0x03: Setup Address Width */
    NRF_SetupRetrReg_t     SETUP_RETR;    /* 0x04: Setup Auto Retransmit */
    NRF_RFChannelReg_t     RF_CH;         /* 0x05: RF Channel */
    NRF_RFSetupReg_t       RF_SETUP;      /* 0x06: RF Setup */
    NRF_StatusReg_t        STATUS;        /* 0x07: Status */
    NRF_ObserveTxReg_t     OBSERVE_TX;    /* 0x08: Observe TX */
    NRF_RPDReg_t           RPD;           /* 0x09: Received Power Detector */
    NRF_RxAddrReg_t        RX_ADDR_P0;    /* 0x0A: RX Address Pipe 0 */
    NRF_RxAddrReg_t        RX_ADDR_P1;    /* 0x0B: RX Address Pipe 1 */
    NRF_RxAddrReg_t        RX_ADDR_P2;    /* 0x0C: RX Address Pipe 2 */
    NRF_RxAddrReg_t        RX_ADDR_P3;    /* 0x0D: RX Address Pipe 3 */
    NRF_RxAddrReg_t        RX_ADDR_P4;    /* 0x0E: RX Address Pipe 4 */
    NRF_RxAddrReg_t        RX_ADDR_P5;    /* 0x0F: RX Address Pipe 5 */
    NRF_TxAddrReg_t        TX_ADDR;       /* 0x10: TX Address */
    NRF_RxPayloadWidthReg_t RX_PW_P0;     /* 0x11: RX Payload Width Pipe 0 */
    NRF_RxPayloadWidthReg_t RX_PW_P1;     /* 0x12: RX Payload Width Pipe 1 */
    NRF_RxPayloadWidthReg_t RX_PW_P2;     /* 0x13: RX Payload Width Pipe 2 */
    NRF_RxPayloadWidthReg_t RX_PW_P3;     /* 0x14: RX Payload Width Pipe 3 */
    NRF_RxPayloadWidthReg_t RX_PW_P4;     /* 0x15: RX Payload Width Pipe 4 */
    NRF_RxPayloadWidthReg_t RX_PW_P5;     /* 0x16: RX Payload Width Pipe 5 */
    NRF_FIFOStatusReg_t    FIFO_STATUS;   /* 0x17: FIFO Status */
    NRF_DynPayloadReg_t    DYNPD;         /* 0x1C: Dynamic Payload Enable */
    NRF_FeatureReg_t       FEATURE;       /* 0x1D: Feature Register */
} NRF_Registers_t;

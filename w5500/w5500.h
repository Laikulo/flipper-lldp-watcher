#pragma once

#include <stdint.h>

// Control phase structure constants
#define W5500_C_BSB_MASK 0b11111000
#define W5500_C_RW_MASK  0b00000100
#define W5500_C_OM_MASK  0b00000011

#define W5500_BSB_COMMON 0b00000

#define W5500_BSB_SOCKET0 0b00000
#define W5500_BSB_SOCKET1 0b00100
#define W5500_BSB_SOCKET2 0b01000
#define W5500_BSB_SOCKET3 0b01100
#define W5500_BSB_SOCKET4 0b10000
#define W5500_BSB_SOCKET5 0b10100
#define W5500_BSB_SOCKET6 0b11100
#define W5500_BSB_SOCKET7 0b11100

#define W5500_BSB_SOCK_REGISTER  0b01
#define W5500_BSB_SOCK_TX_BUFFER 0b10
#define W5500_BSB_SOCK_RX_BUFFER 0b11

#define WS500_RWB_READ  0b0
#define WS500_RWB_WRITE 0b1

#define W5500_OM_VARIABLE     0b00
#define W5500_OM_FIXED_1_BYTE 0b01
#define W5500_OM_FIXED_2_BYTE 0b10
#define W5500_OM_FIXED_4_BYTE 0b11

// LUT for socket selection
const uint8_t W5500_SOCKETS[] = {
    W5500_BSB_SOCKET0,
    W5500_BSB_SOCKET1,
    W5500_BSB_SOCKET2,
    W5500_BSB_SOCKET3,
    W5500_BSB_SOCKET4,
    W5500_BSB_SOCKET5,
    W5500_BSB_SOCKET6,
    W5500_BSB_SOCKET7};

typedef uint8_t W5500IpAddr[4];
typedef uint8_t W5500MacAddr[6];

// Common registers

#define W5500_COMMON_MR 0x0000
#define W5500_MR_FARP   0x02 // Force Arp: ARP for every send
#define W5500_MR_PPPOE  0x08
#define W5500_MR_PB     0x10 // Ping Block: if 1, do not respond to pings
#define W5500_MR_WOL    0x20 // WOL: if 1, raise interupt on magic packet
#define W5500_MR_RST    0x80 // Soft reset

typedef union W5500RegMr {
    struct __attribute__((packed)) {
        uint8_t _reserved_0 : 1;
        uint8_t FARP        : 1;
        uint8_t _reserved_2 : 1;
        uint8_t PPPOE       : 1;
        uint8_t PB          : 1;
        uint8_t WOL         : 1;
        uint8_t _reserved_6 : 1;
        uint8_t RST         : 1;
    } bits;
    uint8_t value;
} W5500RegMr;

#define W5500_COMMON_GWR  0x0001 // Gateway IP Addr
#define W5500_COMMON_SUBR 0x0005 // Subnet Mask
#define W5500_COMMON_SHAR 0x0009 // Source MAC "Source Hardware"
#define W5500_COMMON_SIPR 0x000F // Source IP

#define W5500_COMMON_INTLEVEL 0x0013 // Assert time for interupt (datasheet page 34)
#define W5500_COMMON_IR       0x0015 // Interupt [status] register
#define W5500_IR_MP           0x10 // Magic packet (WOL)
#define W5500_IR_PPPOE        0x20 // PPPOE disconnected
#define W5500_IR_UNREACH      0x40 // ICMP Port unreachable: See UIPR and UPORTR for what
#define W5500_IR_CONFLICT     0x80 // IP Address conflict

typedef union W5500Interupts {
    struct __attribute__((packed)) {
        uint8_t _reserved_0 : 4;
        uint8_t MP          : 1;
        uint8_t PPPOE       : 1;
        uint8_t UNREACH     : 1;
        uint8_t CONFLICT    : 1;
    } bits;
    uint8_t value;
} W5500Interupts;

typedef W5500Interupts W5500RegIr;

#define W5500_COMMON_IMR 0x0016 // Interupt Mask register
// Uses the same values as IR

typedef W5500Interupts W5500RegImr;

#define W5500_COMMON_SIR  0x0017 // Socket Interupt [flag] register
#define W5500_COMMON_SIMR 0x0018 // Socket Interupt Mask register

#define W5500_COMMON_RTR 0x0019 // Retry Time
#define W5500_COMMON_RCR 0x001B // Retry Count

#define W5500_COMMON_PTIME  0x001C // PPPoE request timer
#define W5500_COMMON_PMAGIC 0x001D // PPPoE Magic Number
#define W5500_COMMON_PHAR   0x001E // PPPoE Destination MAC
#define W5500_COMMON_PSID   0x0024 // PPPoE Session ID
#define W5500_COMMON_PMRU   0x0026 // PPPoE MRU

#define W5500_COMMON_UIPR   0x0028 // Unreachable address
#define W5500_COMMON_UPORTR 0x002C // Unreachable port

#define W5500_COMMON_PHYCFGR 0x002E // PHY Configuration
#define W5500_PHYCFGR_LNK    0x01 // Link Status (up/down)
#define W5500_PHYCFGR_SPD    0x02 // Link Speed (100/10)
#define W5500_PHYCFGR_DPX    0x04 // Duplex (full/half)

#define W5500_PHYCFGR_OPMDC_MASK    0b00111000
#define W5500_PHYCFGR_OPMDC_AUTO    0b00111000
#define W5500_PHYCFGR_OPMDC_DOWN    0b00110000
#define W5500_PHYCFGR_OPMDC_10HALF  0b00000000
#define W5500_PHYCFGR_OPMDC_10FULL  0b00001000
#define W5500_PHYCFGR_OPMDC_100HALF 0b00010000
#define W5500_PHYCFGR_OPMDC_100FULL 0b00011000
#define W5500_PHYCFGR_OPMDC_100AUTO 0b00100000

/*
typedef enum {
  10HALF = W5500_PHYCFGR_OPMDC_10HALF,
  10FULL = W5500_PHYCFGR_OPMDC_10FULL,
  100HALF = W5500_PHYCFGR_OPMDC_100HALF,
  100FULL = W5500_PHYCFGR_OPMDC_100FULL,
  100AUTO = W5500_PHYCFGR_OPMDC_100AUTO,
  DOWN = W5500_PHYCFGR_OPMDC_DOWN,
  AUTO = W5500_PHYCFGR_OPMDC_AUTO
} W5500OperatingMode;
*/

#define W5500_PHYCFGR_OPMD 0x40 // If 1, configure mode with OPMDC, if 0, pin strap
#define W5500_PHYCFGR_RST  0x80 // Reset the PHY. 0 causes reset, reads back as 1 after reset

typedef union {
    struct __attribute__((packed)) {
        uint8_t LNK   : 1;
        uint8_t SPD   : 1;
        uint8_t DPX   : 1;
        uint8_t OPMDC : 3;
        uint8_t OPMD  : 1;
        uint8_t RST   : 1;
    } bits;
    uint8_t value;
} W5500RegPhyCfg;

#define W5500_COMMON_VERSIONR 0x0039 // Version register. DS states should always be 0x04

// Socket specific registers

#define W5500_SOCK_MR              0x0000 // Socket mode register
#define W5500_SOCK_MR_PROTO_MASK   0x0F
#define W5500_SOCK_MR_PROTO_CLOSED 0x00
#define W5500_SOCK_MR_PROTO_TCP    0x01
#define W5500_SOCK_MR_PROTO_UDP    0x02
#define W5500_SOCK_MR_PROTO_MACRAW 0x04 // Should only be used for socket 0
#define W5500_SOCK_MR_UCASTB       0x10 // Block unicast in UDP mode
#define W5500_SOCK_MR_MIP6B        0x10 // Block V6 traffic in MACRAW mode
#define W5500_SOCK_MR_ND           0x20 // Disable delayed ACK in TCP mode
#define W5500_SOCK_MR_MC           0x20 // IGMP Version in UDP mode
#define W5500_SOCK_MR_MMB          0x20 // Block multicast traffic in MACRAW mode
#define W5500_SOCK_MR_BCASTB       0x40 // Block bradcast traffic in UDP/MACRAW modes
#define W5500_SOCK_MR_MULTI        0x80 // Enable multicast in UDP
#define W5500_SOCK_MR_MFEN         0x80 // Enable MAC filtering in MACRAW mode

#define W5500_SOCK_CR                0x0001
#define W5500_SOCK_CR_CMD_OPEN       0x01
#define W5500_SOCK_CR_CMD_LISTEN     0x02
#define W5500_SOCK_CR_CMD_CONNECT    0x04
#define W5500_SOCK_CR_CMD_DISCONNECT 0x08
#define W5500_SOCK_CR_CMD_CLOSE      0x10
#define W5500_SOCK_CR_CMD_SEND       0x20
#define W5500_SOCK_CR_CMD_SEND_MAC   0x21
#define W5500_SOCK_CR_CMD_SEND_KEEP  0x22
#define W5500_SOCK_CR_CMD_RECV       0x40

#define W5500_SOCK_IR    0x0002 // Socket interrupt [status] register
#define W5500_SOCK_SR    0x0003 // Socket status register
#define W5500_SOCK_PORT  0x0004 // Source port
#define W5500_SOCK_DHAR  0x0006 // Destination MAC (used in SEND_MAC in UDP)
#define W5500_SOCK_DIPR  0x000C // Destination IP
#define W5500_SOCK_DPORT 0x0010 // Destination Port
#define W5500_SOCK_MSSR  0x0012 // TCP MSS
#define W5500_SOCK_TOS   0x0015 // IP ToS
#define W5500_SOCK_TTL   0x0016 // IP TTl

#define W5500_SOCK_RXBUF_SIZE  0x001E
#define W5500_SOCK_TXBUF_SIZE  0x001F
#define W5500_SOCK_TXBUF_FREE  0x0020
#define W5500_SOCK_TXBUF_RDPTR 0x0022
#define W5500_SOCK_TXBUF_WRPTR 0x0024
#define W5500_SOCK_RXBUF_RSR   0x0026
#define W5500_SOCK_RXBUF_RDPTR 0x0028
#define W5500_SOCK_RXBUF_WRPTR 0x002A

#define W5500_SOCK_IMR     0x002C // Interupt mask register
#define W5500_SOCK_KPALVTR 0x002F // Keep alive timer

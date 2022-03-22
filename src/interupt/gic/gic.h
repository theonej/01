#ifndef GIC_H
#define GIC_H

#include <stdint.h>

typedef volatile struct __attribute__((packed))
{
    uint32_t DCTLR;                     //0x0               - Distributor Control register
    const uint32_t DTYPER;              //0x4               - Control Type register
    const uint32_t DIIDR;               //0x8               - Implementer Identification register
    const uint32_t _RESERVED0[29];      //0xC   - 0x80;     - Reserved and Implementation Defined
    uint32_t DIGROUPR[32];              //0x80  - 0xFC;     - Interupt Group registers
    uint32_t DISENABLER[32];            //0x100 - 0x17C;    - Interupt Set-Enable registers 
    uint32_t DICENABLER[32];            //0x180 - 0x1FC;    - Interupt Clear-Enable registers
    uint32_t DISPENDR[32];              //0x200 - 0x27C;    - Interupt Set-Pending registers
    uint32_t DICPENDR[32];              //0x300 - 0x3FC;    - Interupt Clear-Pending registers
    uint32_t DICDABR[32];               //0x380 - 0x3FC;    - Active Bit registers (GIC v1)
    const uint32_t _RESERVED1;          //0x380 - 0x3FC;    - Reserved on Gic V1
    uint32_t DIPRIORITY[255];           //0x400 - 0x7F8;    - Interupt Priority registers
    const uint32_t _RESERVED2;          //0x7FC             - Reserved
    const uint32_t DITARGETSRO[8];      //0x800 - 0x81C;    - Interupt CPU Targets, Read Only
    uint32_t DITARGETSR[246];           //0x820 - 0xBF8;    - Interupt CPU Targets
    const uint32_t _RESERVED3;          //0xBFC             - Reserved
    uint32_t DICFGR[64];                //0xC00 - 0xCFC;    - Interupt Config registers
    
} gic_distributor_registers;

typedef volatile struct __attribute__((packed))
{
    uint32_t CCTLR;                     //0x0               - CPU Interface Control register
    uint32_t CCPMR;                     //0x4               - Interupt Priority Mask register
    uint32_t CBPR;                      //0x8               - Binary Point register
    const uint32_t CIAR;                //0xC               - Interupt Acknowledge register
    uint32_t CEOIR;                     //0x10              - End of Interupt register
    const uint32_t CRPR;                //0x14              - Running Priority register
    const uint32_t CHPPIR;              //0x18              - Higher Priority Pending Interupt register
    uint32_t CABPR;                     //0x1C              - Aliased Binary Point register
    const uint32_t CAIAR;               //0x20              - Aliased Interupt Acknowledge register
    uint32_t CAEOIR;                    //0x24              - Aliased End of Interupt register
    const uint32_t CAHPPIR;             //0x28              - Aliased Highest Priority Pending Interupt register

} gic_cpu_interface_registers;

#endif
#ifndef BIT_UTILS_H
#define BIT_UTILS_H

#define SET_BIT(REG,Bit_NO)     (REG) |= (1<<(Bit_NO))
#define CLR_BIT(REG,Bit_NO)     (REG) &= ~(1<<(Bit_NO))
#define GET_BIT(REG,Bit_NO)     ((REG>>Bit_NO)&(0x01))
#define RSHFT_REG(REG,NO)       (REG) >>= NO
#define LSHFT_REG(REG,NO)       (REG) <<= NO
#define CRSHFT_REG(REG,NO)      (REG) = (REG >> NO) | (REG<<((sizeof(REG) * 8) - NO))
#define CLSHFT_REG(REG,NO)      (REG) = (REG << NO) | (REG>>((sizeof(REG) * 8) - NO))
#define ASSIGN_REG(REG,VALUE)   (REG) = (VALUE)
#define SET_REG(REG)            (REG) = ~(0);
#define CLR_REG(REG)            (REG) = 0;
#define TGL_BIT(REG,Bit_NO)     (REG) ^= 1<<(Bit_NO)
#define TGL_REG(REG)            (REG) ^= ~(0)
#define SET_H_NIB(REG)          (REG) |= 0xF0
#define SET_L_NIB(REG)          (REG) |= 0x0F
#define CLR_H_NIB(REG)          (REG) &= 0x0F
#define CLR_L_NIB(REG)          (REG) &= 0xF0
#define GET_H_NIB(REG)          (REG) >> 4
#define GET_L_NIB(REG)          ((REG) &  0x0F)
#define ASSIGN_H_NIB(REG,VALUE) (REG) = ((REG&0x0F) | (VALUE<<4))
#define ASSIGN_L_NIB(REG,VALUE) (REG) = ((REG & 0xF0) | VALUE)
#define TGL_H_NIB(REG)          (REG) ^= (0xF0)
#define TGL_L_NIB(REG)          (REG) ^= (0x0F)
#define SWAP_NIB(REG)           (REG) = (REG>>4) | (REG<<4)
#define CONC(B7,B6,B5,B4,B3,B2,B1,B0)		CONC_HELP(B7,B6,B5,B4,B3,B2,B1,B0)
#define CONC_HELP(B7,B6,B5,B4,B3,B2,B1,B0)	0b##B7##B6##B5##B4##B3##B2##B1##B0





#endif

// skI2Cslave.h
// $B!)(Bh$B!)(BQ$B!)(Bb$B!)!)!)(BM$B!)!)!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)(Bp$B!)!)!)(BC$B!)(Bu$B!)!)!)!)!)(Bp$B!)(BC$B!)!)!)(BN$B!)!)!)(B[$B!)(Bh$B!)(Bt$B!)(B@$B!)(BC$B!)!)(B
// $B!)!)!)!)!)(BM$B!)!)!)(Bs$B!)!)!)(Bf$B!)(B[$B!)(B^$B!)!)!)(BT$B!)(BC$B!)(BY$B!)!)!)!)!)!)(BSND_DATA_LEN/RCV_DATA_LEN$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(BB
#ifndef _SKI2CSLAVE_H_
#define _SKI2CSLAVE_H_

#define SND_DATA_LEN 8                  // $B!)!)!)(BM$B!)(Bf$B!)(B[$B!)(B^$B!)(Bo$B!)(Bb$B!)(Bt$B!)(B@$B!)!)!)(BT$B!)(BC$B!)(BY
#define RCV_DATA_LEN 8                  // $B!)!)!)(BM$B!)(Bf$B!)(B[$B!)(B^$B!)(Bo$B!)(Bb$B!)(Bt$B!)(B@$B!)!)!)(BT$B!)(BC$B!)(BY

unsigned char rcv_data[RCV_DATA_LEN]; // $B!)!)!)(BM$B!)(Bf$B!)(B[$B!)(B^$B!)(Bo$B!)(Bb$B!)(Bt$B!)(B@
unsigned char snd_data[SND_DATA_LEN]; // $B!)!)!)(BM$B!)(Bf$B!)(B[$B!)(B^$B!)(Bo$B!)(Bb$B!)(Bt$B!)(B@


unsigned int rcv_flg; // $B!)!)!)(BM$B!)!)!)!)(B($B!)!)!)(BM$B!)(Bf$B!)(B[$B!)(B^$B!)!)!)!)!)!)!)!)!)(Bi$B!)(B[)
unsigned char *Sdtp; // $B!)!)!)(BM$B!)(Bf$B!)(B[$B!)(B^$B!)(Bo$B!)(Bb$B!)(Bt$B!)(B@$B!)!)!)(BA$B!)(Bh$B!)!)!)(BX$B!)(B|$B!)(BC$B!)!)!)(B^$B!)(B[
unsigned char *Rdtp; // $B!)!)!)(BM$B!)(Bf$B!)(B[$B!)(B^$B!)(Bo$B!)(Bb$B!)(Bt$B!)(B@$B!)!)!)(BA$B!)(Bh$B!)!)!)(BX$B!)(B|$B!)(BC$B!)!)!)(B^$B!)(B 

void interrupt InterI2C(void);
void InitI2C_Slave(int address);
int I2C_ReceiveCheck();

#endif

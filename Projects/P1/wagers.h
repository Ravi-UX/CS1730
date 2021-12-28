#ifndef WAGERS_H
#define WAGERS_H

extern void printGameRules(void);
extern double getBankBalance(void);
extern int checkWager(double wager, double balance);
extern double getWager(void);
extern double adjustBalance(double bankbalance, double wageamount, int addOrSubtractToBalance);
extern int getYESorNO(void);

#endif

#ifndef MOTOR_H
#define MOTOR_H

struct Motor;

// Control
extern void init(struct Motor *m);
extern void step_to_pos(int pos, struct Motor *m);

// UART
int read_trans_count(struct Motor *m);

#endif

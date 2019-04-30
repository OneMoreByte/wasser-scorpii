#ifndef MOTOR_H
#define MOTOR_H

extern struct Motor;

// Control
extern void init(struct motor *m);
extern void step_to_pos(int pos, struct motor *m);

// UART
int read_trans_count(struct motor *m);

#endif

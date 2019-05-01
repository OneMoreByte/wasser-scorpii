#ifndef MOTOR_H
#define MOTOR_H

struct Motor;

typedef struct Motor {
	int id;
  int step_pin;
  int dir_pin;
	float pos;
	void *uart_port;
} Motor;

// Control
extern void init(Motor *m);
extern void step_to_pos(int pos, Motor *m);
extern void toggle_dir(Motor *M);

// UART
int read_trans_count(Motor *m);

#endif

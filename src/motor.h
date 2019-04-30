#pragma once

struct motor;

void init(struct motor *m);
int read_trans_count(struct motor *m);
void step_to_deg(float theta, struct motor *m);

#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);

    int reg[6] = {0};

    for (int i = 0; i < n; i++) {
        unsigned int x;
        scanf("%x", &x);
        int opcode = x >> 13;
        int reg1 = (x >> 10) & 0x7;
        int reg2 = (x >> 7) & 0x7;
        int imm = x & 0x7F;
        if (opcode == 0)
            reg[reg1] += reg[reg2];
        else if (opcode == 1)
            reg[reg1] -= reg[reg2];
        else if (opcode == 2)
            reg[reg1] *= reg[reg2];
        else if (opcode == 3)
            reg[reg1] /= reg[reg2];
        else if (opcode == 4)
            reg[reg1] = imm;
        else if (opcode == 5)
            printf("x%d = %d\n", reg1, reg[reg1]);
        reg[0] = 0;
    }

    return 0;
}
#include <stdio.h>
#include <stdint.h>

uint8_t mem[256] = {0};
uint8_t reg[4] = {0};
uint8_t pc = 0, zf = 0, running = 1;
int ciclo = 0;

void fetch(uint8_t *op, uint8_t *a, uint8_t *b) {
    *op = mem[pc]; *a = mem[pc+1]; *b = mem[pc+2];
    pc += 3;
}

void decode_execute(uint8_t op, uint8_t a, uint8_t b) {
    switch (op) {
        case 0x01: reg[a] = mem[b]; break;
        case 0x02: mem[b] = reg[a]; break;
        case 0x03: reg[a] = reg[a] + reg[b]; break;
        case 0x04: reg[a] = reg[a] - reg[b]; break;
        case 0x05: reg[a] = b; break;
        case 0x06: zf = (reg[a] == reg[b]) ? 1 : 0; break;
        case 0x07: pc = a; break;
        case 0x08: if (zf) pc = a; break;
        case 0x09: if (!zf) pc = a; break;
        case 0x0A: running = 0; break;
    }
}

void trace(uint8_t op, uint8_t a, uint8_t b) {
    const char *nomes[] = {"","LOAD","STORE","ADD",
        "SUB","MOV","CMP","JMP","JZ","JNZ","HALT"};
    printf("Ciclo %d: %-5s %d,%d | R0=%3d R1=%3d"
           " R2=%3d R3=%3d | PC=%3d ZF=%d\n",
           ciclo, nomes[op], a, b,
           reg[0], reg[1], reg[2], reg[3], pc, zf);
}

void potencia(void){

    mem[0x10] = 3; /* BASE = 3 */
    mem[0x11] = 4; /* EXP = 4 */

    mem[0x00] = 0x07; mem[0x01] = 0x20; mem[0x02] = 0x00; /* JMP 0x20 */

    mem[0x20] = 0x05; mem[0x21] = 0x00; mem[0x22] = 0x01; /* MOV R0, 1 */
    mem[0x23] = 0x01; mem[0x24] = 0x01; mem[0x25] = 0x10; /* LOAD R1, [0x10] */
    mem[0x26] = 0x01; mem[0x27] = 0x02; mem[0x28] = 0x11; /* LOAD R2, [0x11] */

    /* loop exponencial */
    mem[0x29] = 0x05; mem[0x2A] = 0x03; mem[0x2B] = 0x00; /* MOV R3, 0 */
    mem[0x2C] = 0x06; mem[0x2D] = 0x02; mem[0x2E] = 0x03; /* CMP R2, R3 */
    mem[0x2F] = 0x08; mem[0x30] = 0x4D; mem[0x31] = 0x00; /* JZ FIM */

    /* salvar resultado */
    mem[0x32] = 0x05; mem[0x33] = 0x03; mem[0x34] = 0x00; /* MOV R3, 0 */
    mem[0x35] = 0x03; mem[0x36] = 0x03; mem[0x37] = 0x00; /* ADD R3, R0 */

    mem[0x38] = 0x05; mem[0x39] = 0x00; mem[0x3A] = 0x00; /* MOV R0, 0 */

    mem[0x3B] = 0x01; mem[0x3C] = 0x01; mem[0x3D] = 0x10; /* LOAD R1, [0x10] */

    /* loop multiplicação */
    mem[0x3E] = 0x05; mem[0x3F] = 0x02; mem[0x40] = 0x00; /* MOV R2, 0 */
    mem[0x41] = 0x06; mem[0x42] = 0x01; mem[0x43] = 0x02; /* CMP R1, R2 */
    mem[0x44] = 0x08; mem[0x45] = 0x4A; mem[0x46] = 0x00; /* JZ sai mult */

    mem[0x47] = 0x03; mem[0x48] = 0x00; mem[0x49] = 0x03; /* ADD R0, R3 */

    mem[0x4A] = 0x05; mem[0x4B] = 0x02; mem[0x4C] = 0x01; /* MOV R2, 1 */
    mem[0x4D] = 0x04; mem[0x4E] = 0x01; mem[0x4F] = 0x02; /* SUB R1, R2 */

    mem[0x50] = 0x07; mem[0x51] = 0x3E; mem[0x52] = 0x00; /* JMP LOOP MULT */

    /* decrementa exponencial */
    mem[0x53] = 0x05; mem[0x54] = 0x03; mem[0x55] = 0x01; /* MOV R3, 1 */
    mem[0x56] = 0x04; mem[0x57] = 0x02; mem[0x58] = 0x03; /* SUB R2, R3 */

    mem[0x59] = 0x07; mem[0x5A] = 0x29; mem[0x5B] = 0x00; /* JMP LOOP EXP */

    /* fim */
    mem[0x4D] = 0x02; mem[0x4E] = 0x00; mem[0x4F] = 0x20; /* STORE R0, [0x20] */
    mem[0x50] = 0x0A; mem[0x51] = 0x00; mem[0x52] = 0x00; /* HALT */
}

int main() {

    potencia();

    while (running && pc < 256) {
        uint8_t op, a, b;
        ciclo++;
        fetch(&op, &a, &b);
        decode_execute(op, a, b);
        trace(op, a, b);
    }
    return 0;
}
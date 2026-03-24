#include <stdio.h>
#include <stdint.h>

/* Memoria ram, 4 registradores, Contador de programa, Zero flag, ciclos*/
uint8_t mem[256] = {0};
uint8_t reg[4]   = {0};
uint8_t pc = 0, zf = 0, running = 1;
int ciclo = 0;

/*FETCH, acessa a memória e busca a prox instrução*/
void fetch(uint8_t *op, uint8_t *a, uint8_t *b) {
    *op = mem[pc]; *a = mem[pc+1]; *b = mem[pc+2];
    pc += 3;
}

/*DECODE + EXECUTE, recebe os valores do fetch, identifica e executa a instrução*/
void decode_execute(uint8_t op, uint8_t a, uint8_t b) {
    switch (op) {

        /*LOAD: busca um valor na memoria e traz para um registrador*/
        case 0x01: reg[a] = mem[b];                        
        break;

        /*STORE: Pega o valor de um registrador e salva na memória*/
        case 0x02: mem[b] = reg[a];  
        break;

        /*ADD: soma dois registradores e guarda o resultado*/
        case 0x03: reg[a] = reg[a] + reg[b];               
        break;

        /*SUB: Subtrai dois registradores e guarda o resultado*/
        case 0x04: reg[a] = reg[a] - reg[b];               
        break;

        /*MOV: Coloca um valor fixo diretamente num registrador*/
        case 0x05: reg[a] = b;                             
        break;

        /*CMP: Compara dois registradores, se forem iguais ativa a Zero Flag = 1, se diferentes apaga zf = 0*/
        case 0x06: zf = (reg[a] == reg[b]) ? 1 : 0;       
        break; 

        /*JMP: muda o PC para o endereço a, o processador para de executar em sequência e pula para outro ponto*/
        case 0x07: pc = a;                                 
        break;

        /*JZ: Salto condicional, só pula se zf = 1*/
        case 0x08: if (zf)  pc = a;                        
        break;

        /*JNZ: Salto condicional, só pula se zf = 0*/
        case 0x09: if (!zf) pc = a;                        
        break;

        /*HALT: para o processador, running vira 0 e loop main encerra*/
        case 0x0A: running = 0;                            
        break;

    }
}

/*TRACE: mostra na tela o que acontece a cada ciclo*/
void trace(uint8_t op, uint8_t a, uint8_t b) {

    const char *nomes[] = {"","LOAD","STORE","ADD","SUB","MOV","CMP","JMP","JZ","JNZ","HALT"};

    printf("Ciclo %2d: %-5s %d,%d | R0=%3d R1=%3d R2=%3d R3=%3d | PC=%3d ZF=%d\n", ciclo, nomes[op], a, b, reg[0], reg[1], reg[2], reg[3], pc, zf);
}

/*Instruções do processador*/
void potencia(void) {

    /*PRIMEIROS DADOS*/
    mem[0x10] = 3;
    mem[0x11] = 4;

    /*JMP: pula direto para endereço 0x20*/
    mem[0x00]=0x07; mem[0x01]=0x20; mem[0x02]=0x00;

    /*Inicialização: salva o contador do expoente em 0x12*/
    mem[0x20]=0x05; mem[0x21]=0x00; mem[0x22]=0x01;
    mem[0x23]=0x01; mem[0x24]=0x01; mem[0x25]=0x11;
    mem[0x26]=0x02; mem[0x27]=0x01; mem[0x28]=0x12;

    /*Loop externo (expoente): repete a quantidade do expoente, multiplicação por iteração*/
    mem[0x29]=0x01; mem[0x2A]=0x02; mem[0x2B]=0x12;
    mem[0x2C]=0x05; mem[0x2D]=0x03; mem[0x2E]=0x00;
    mem[0x2F]=0x06; mem[0x30]=0x02; mem[0x31]=0x03;
    mem[0x32]=0x08; mem[0x33]=0x62; mem[0x34]=0x00;

    /*Prepara multiplicação*/
    mem[0x35]=0x03; mem[0x36]=0x03; mem[0x37]=0x00;
    mem[0x38]=0x05; mem[0x39]=0x00; mem[0x3A]=0x00;
    mem[0x3B]=0x01; mem[0x3C]=0x01; mem[0x3D]=0x10;

    /* Loop interno: multiplica por soma repetida*/
    mem[0x3E]=0x05; mem[0x3F]=0x02; mem[0x40]=0x00;
    mem[0x41]=0x06; mem[0x42]=0x01; mem[0x43]=0x02;
    mem[0x44]=0x08; mem[0x45]=0x53; mem[0x46]=0x00;
    mem[0x47]=0x03; mem[0x48]=0x00; mem[0x49]=0x03;
    mem[0x4A]=0x05; mem[0x4B]=0x02; mem[0x4C]=0x01;
    mem[0x4D]=0x04; mem[0x4E]=0x01; mem[0x4F]=0x02;
    mem[0x50]=0x07; mem[0x51]=0x3E; mem[0x52]=0x00;

    /* Fim da multiplicação, decrementa o expoente e volta ao loop externo*/
    mem[0x53]=0x01; mem[0x54]=0x01; mem[0x55]=0x12;
    mem[0x56]=0x05; mem[0x57]=0x02; mem[0x58]=0x01;
    mem[0x59]=0x04; mem[0x5A]=0x01; mem[0x5B]=0x02;
    mem[0x5C]=0x02; mem[0x5D]=0x01; mem[0x5E]=0x12;
    mem[0x5F]=0x07; mem[0x60]=0x29; mem[0x61]=0x00;

    /*Final: salva resultado em 0x20 e encerra o processador*/
    mem[0x62]=0x02; mem[0x63]=0x00; mem[0x64]=0x20;
    mem[0x65]=0x0A; mem[0x66]=0x00; mem[0x67]=0x00;
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

    printf("\n==> Resultado em MEM[0x20] = %d (esperado: 81)\n", mem[0x20]);

    return 0;
}

#include "cpu.h"
#include "load_prog.h"

MODE HEX_TO_MODE[256] = {
12,  6,  4,  4,  4,  9,  9,  4, 12,  4,  3,  4,  4,  0,  0,  4,
 8,  7,  4,  4,  4, 10, 10,  4, 12,  2,  4,  4,  4,  1,  1,  4,
 0,  6,  4,  4,  9,  9,  9,  4, 12,  4,  3,  4,  0,  0,  0,  4,
 8,  7,  4,  4,  4, 10, 10,  4, 12,  2,  4,  4,  4,  1,  1,  4,
12,  6,  4,  4,  4,  9,  9,  4, 12,  4,  3,  4,  0,  0,  0,  4,
 8,  7,  4,  4,  4, 10, 10,  4, 12,  2,  4,  4,  4,  1,  1,  4,
12,  6,  4,  4,  4,  9,  9,  4, 12,  4,  3,  4,  5,  0,  0,  4,
 8,  7,  4,  4,  4, 10, 10,  4, 12,  2,  4,  4,  4,  1,  1,  4,
 4,  6,  4,  4,  9,  9,  9,  4, 12,  4, 12,  4,  0,  0,  0,  4,
 8,  7,  4,  4, 10, 10, 11,  4, 12,  2, 12,  4,  4,  1,  4,  4,
 4,  6,  4,  4,  9,  9,  9,  4, 12,  4, 12,  4,  0,  0,  0,  4,
 8,  7,  4,  4, 10, 10, 11,  4, 12,  2, 12,  4,  1,  1,  2,  4,
 4,  6,  4,  4,  9,  9,  9,  4, 12,  4, 12, 12,  0,  0,  0,  4,
 8,  7,  4,  4,  4, 10, 10,  4, 12,  2,  4,  4,  4,  1,  1,  4,
 4,  6,  4,  4,  9,  9,  9,  4, 12,  4, 12,  4,  0,  0,  0,  4,
 8,  7,  4,  4,  4, 10, 10,  4, 12,  2,  4,  4,  4,  1,  1,  4  };
 
void (*HEX_TO_FUNC[256])(CPU *c, OP_CODE_INFO *o) = {
dum, ora, dum, dum, dum, ora, asl, dum, php, ora, asl, dum, dum, ora, asl, dum,
bpl, ora, dum, dum, dum, ora, asl, dum, clc, ora, dum, dum, dum, ora, asl, dum,
jsr, and, dum, dum, bit, and, dum, dum, plp, and, dum, dum, bit, and, dum, dum,
bmi, and, dum, dum, dum, and, dum, dum, sec, and, dum, dum, dum, and, dum, dum,
dum, dum, dum, dum, dum, dum, lsr, dum, pha, dum, lsr, dum, jmp, dum, lsr, dum,
bvc, dum, dum, dum, dum, dum, lsr, dum, cli, dum, dum, dum, dum, dum, lsr, dum,
dum, adc, dum, dum, dum, adc, dum, dum, pla, adc, dum, dum, jmp, adc, dum, dum,
bvs, adc, dum, dum, dum, adc, dum, dum, dum, adc, dum, dum, dum, adc, dum, dum,
dum, sta, dum, dum, dum, sta, stx, dum, dey, dum, txa, dum, dum, sta, stx, dum,
bcc, sta, dum, dum, dum, sta, stx, dum, tya, sta, dum, dum, dum, sta, dum, dum,
ldy, lda, ldx, dum, ldy, lda, ldx, dum, tay, lda, dum, dum, ldy, lda, ldx, dum,
bcs, lda, dum, dum, ldy, lda, ldx, dum, clv, lda, dum, dum, ldy, lda, ldx, dum,
cpy, cmp, dum, dum, cpy, cmp, dec, dum, dum, cmp, dex, dum, cpy, cmp, dec, dum,
bne, cmp, dum, dum, dum, cmp, dec, dum, cld, cmp, dum, dum, dum, cmp, dec, dum,
cpx, sbc, dum, dum, cpx, sbc, inc, dum, inx, sbc, nop, dum, cpx, sbc, inc, dum,
beq, sbc, dum, dum, dum, sbc, inc, dum, dum, sbc, dum, dum, dum, sbc, inc, dum};

/* sets a single bit of one of the eight bit 
 * registers on CPU to val */
void setRegBit(CPU *c, REG name, int8_t bit, int8_t val){
    //bit must be between 0 and 7 since registers
    //are 8 bits
    assert(bit > -1 && bit < 8);
    //only setting one bit so val must be 0 or 1
    assert (val == 0 || val == 1);
    c->regs[name] = (c->regs[name] & ~(1 << bit)) | 
                    (val << bit);
}

int8_t getRegBit(CPU *c, REG name, int8_t bit){
    //bit must be between 0 and 7 since registers
    //are 8 bits
    assert(bit > -1 && bit < 8);
    return (c->regs[name] & (1 << bit)) > 0 ? 1 : 0;
}

/* CPU initializer */
CPU * getCPU(){
    CPU *c = malloc(sizeof(CPU));
    c-> PC = 0;
    //initialize 8 bit registers
    int NUM_REG = 5;
    int8_t *r = calloc(NUM_REG,sizeof(int8_t));
    c-> regs = r;
    //initialize address space
    int ADDR_SPACE_SIZE = 65536;
    int8_t *a= calloc(ADDR_SPACE_SIZE,sizeof(int8_t));
    c-> addressSpace = a;
    //set bit 5 of status register to 1
    //to match specifications
    setRegBit(c, STATUS, 5, 1);
    return c;
}

void resetCPU(CPU *c){
    //resets CPU to initial state as if it has just been initialized
    int NUM_REG = 5;
    memset(c->regs, 0, NUM_REG*sizeof(int8_t));
    int ADDR_SPACE_SIZE = 65536;
    memset(c->addressSpace, 0, ADDR_SPACE_SIZE*sizeof(int8_t));
    c->PC = 0;
    setRegBit(c, STATUS, 5, 1);
}

void freeCPU(CPU *c){
    free(c->regs);
    free(c->addressSpace);
    free(c);
}

/* prints state of CPU registers */
void print(CPU *c){
    printf("PC: ");
    printf("%x\n", c->PC);
    printf("SVUBDIZC\n");
    printf("%s\n",getStatus(c));
    printf("STACK REG: ");
    printf("%d\n", c->regs[STACK]);
    printf("ACCUM REG: ");
    printf("%d\n", c->regs[ACCUM]);
    printf("IND_X REG: ");
    printf("%d\n", c->regs[IND_X]);
    printf("IND_Y REG: ");
    printf("%d\n", c->regs[IND_Y]);
}

char *getStatus(CPU *c){
    return byte_to_binary(c->regs[STATUS]);
}

char *byte_to_binary(int x){
    char *b = malloc(sizeof(char)*9);
    b[0] = '\0';
    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }
    return b;
}

/* set byte value in one of the eight bit 
 * registers to val */
void setRegByte(CPU *c, REG name, int8_t val){
    c->regs[name] = val;
}

int8_t getRegByte(CPU *c, REG name){
    return c->regs[name];
}

void setFlag(CPU *c, FLAG name, int8_t val){
    //bit 5 of the status register is not to be set
    //and should always be 1
    assert(name != NOT_USED_FLAG);
    setRegBit(c, STATUS, name, val);
}

int8_t getFlag(CPU *c, FLAG name){
    //bit 5 of the status register is not to be set
    //and should always be 1
    assert(name != NOT_USED_FLAG);
    return getRegBit(c, STATUS, name);
}

int8_t read(CPU *c, uint16_t addr){
    return c->addressSpace[addr];
}

void write(CPU *c, uint16_t addr, int8_t val){
    c->addressSpace[addr] = val;
}

/* FLAG REG OPERATIONS */

void setCarry(CPU *c, int16_t val){
    //sets carry flag if
    //val > 0b11111111, largest
    //eight bit val
    int8_t carry = val > 0xFF ? 1 : 0;
    setFlag(c,C,carry);
}

void setCarryBCD(CPU *c, int16_t val){
    //sets carry flag if
    //val > 0x99, for addition in BCD mode
    int8_t carry = val > 0x99 ? 1 : 0;
    setFlag(c,C,carry);
}

void setOverflow(CPU *c, int8_t a, int8_t b, int8_t val){
    //sets overflow if overflow in twos complement 
    //occurred when adding a and b to get val
    //this bit twiddling from:
    //http://nesdev.com/6502.txt
    int8_t overflow = !((a ^ b) & 0x80) && ((a ^ val) & 0x80);
    //overflow = signs of operands are the same AND
    //          sign of result not equal to sign of operands
    setFlag(c,V,overflow);
}

void setOverflowSubtract(CPU *c, int8_t a, int8_t b, int8_t val){
    //sets overflow if overflow in twos complement 
    //occurred when subtracting b from a to get val
    //this bit twiddling from:
    //http://nesdev.com/6502.txt
    int8_t overflow = ((a ^ b) & 0x80) && ((a ^ val) & 0x80);
    //overflow = signs of operands are the same AND
    //          sign of result not equal to sign of operands
    setFlag(c,V,overflow);
}

void setSign(CPU *c, int8_t val){
    //sets sign flag equal to sign
    //of bit 7 of val
    int8_t sign = val & 0x80? 1 : 0;
    setFlag(c,S,sign);
}

void setZero(CPU *c, int8_t val){
    //sets zero flag to 0 if val == 0
    //and zero flag to 1 otherwise
    int8_t isZero = val? 0 : 1 ;
    setFlag(c,Z,isZero);
}

OP_CODE_INFO * getOP_CODE_INFO(int8_t operand, uint16_t address, MODE mode){
    OP_CODE_INFO *o = malloc(sizeof(OP_CODE_INFO));
    o->operand = operand;
    o->address = address;
    o->mode = mode;
    return o;
}

void freeOP_CODE_INFO(OP_CODE_INFO *o){
    free(o);
}

/* RUN PROGRAM IN MEMORY */
void run_ops(CPU *c, int16_t end) {
    // MODES = IMM, ZP, ZPX, ZPY, AB, ABX, ABY, IN, INX, INY, IMP, REL
    OP_CODE_INFO *op = malloc(sizeof(OP_CODE_INFO));
    int16_t start = c->PC;
    int16_t *pc = &(c->PC);
    int i, cur_op;
    print(c);
    
    while (c->PC < end) {
        printf("\n");
        cur_op = c->addressSpace[*pc] & 0xFF;
        printf("op: %x\n", cur_op, cur_op);
        op->mode = HEX_TO_MODE[c->addressSpace[*pc] & 0xFF];
        switch (op->mode) {
            case AB:
                printf("mode: AB\n");
                break;
            case ABX:
                printf("mode: ABX\n");
                break;
            case ABY:
                printf("mode: ABY\n");
                break;
            case ACC:
                printf("mode: ACC\n");
                break;
            case IMM:
                printf("mode: IMM\n");
                op->operand = c->addressSpace[++(*pc)];
                HEX_TO_FUNC[cur_op](c, op);
                (*pc)++;
                break;
            case IN:
                printf("mode: IN\n");
                break;
            case INX:
                printf("mode: INX\n");
                break;
            case INY:
                printf("mode: INY\n");
                break;
            case REL:
                printf("mode: REL\n");
                (*pc)++;
                op->address = (int) (*pc) + (int) c->addressSpace[*pc];
                HEX_TO_FUNC[cur_op](c, op);
                (*pc)++;
                break;
            case ZP:
                printf("mode: ZP\n");
                (*pc)++;
                op->operand = c->addressSpace[c->addressSpace[(*pc)]];
                op->address = 0x00FF & c->addressSpace[(*pc)];
                HEX_TO_FUNC[cur_op](c, op);
                (*pc)++;
                break;
            case ZPX:
                printf("mode: ZPX\n");
                op->operand = c->addressSpace[getRegByte(c, IND_X)+c->addressSpace[++(*pc)]];
                HEX_TO_FUNC[cur_op](c, op);
                (*pc)++;
                break;
            case ZPY:
                printf("mode: ZPY\n");
                (*pc)++;
                break;
            case IMP:
                printf("mode: IMP\n");
                HEX_TO_FUNC[cur_op](c, op);
                (*pc)++;
                break;
            default:
                printf("unknown mode number %d\n", op->mode);
                break;
        }
        print(c);
        char step_char;
        while ((step_char = getchar()) != '\n') { /* wait for enter */ }
    }
    print(c);
    printf("\n");
}

/* STACK OPERATIONS HERE */
void PUSH( __attribute__ ((unused)) CPU *c, 
        __attribute__ ((unused)) OP_CODE_INFO *o, 
        __attribute__ ((unused)) int8_t operand){
    //TODO: implement pushing operand onto stack
}

/* OP CODE IMPLEMENTATIONS HERE */

//Add with carry
void adc(CPU *c, OP_CODE_INFO *o){
    int8_t carry = getFlag(c,C);
    int8_t accum = getRegByte(c,ACCUM);
    int8_t operand = o->operand;
    int16_t sum = (0x00FF&carry) + (0x00FF&accum) + (0x00FF&operand);
    int8_t sumByte = sum & 0x00FF;
    setZero(c,sumByte);
    if(getFlag(c,D)){ //in decimal mode
        //if lower 4 bits of operands plus
        //the carry in are larger than 9,
        //then we need to apply conversions
        //to remain in binary coded decimal format.
        if((accum & 0xF) + (operand & 0xF)
            + carry > 9){
            sum += 6;
        }
        setSign(c,sum&0xFF);
        setOverflow(c,accum,operand,sum&0xFF);
        //if the higher bits aren't in
        //BCD format we need to add 96 to convert.
        //Black magic from http://nesdev.com/6502.txt
        sum += sum > 0x99 ? 96 : 0;
        setCarryBCD(c, sum);
    } else {
        setSign(c,sumByte);
        setOverflow(c,accum,operand,sumByte);
        setCarry(c,sum);
    }
    setRegByte(c,ACCUM,sum&0xFF);
}

void and(CPU *c, OP_CODE_INFO *o){
    int8_t accum = getRegByte(c,ACCUM);
    int8_t operand = o->operand;
    int8_t res = accum & operand;
    setSign(c,res);
    setZero(c,res);
    setRegByte(c,ACCUM,res);
}

//Dummy function
void dum(CPU *c, OP_CODE_INFO *o) {
    // this function should not do anything
    printf("dummy function used\n");
}

//Arithmetic shift left
void asl(CPU *c, OP_CODE_INFO *o){
    int8_t operand = o->operand;
    int16_t res = (0x00FF&operand) << 1;
    int8_t resByte = res & 0x00FF;
    setCarry(c,res);
    setSign(c,resByte);
    setZero(c,resByte);
    if(o->mode == ACC){
        setRegByte(c,ACCUM,res);
    } else {
        write(c,o->address,res);
    }
}

//Branch if carry clear
void bcc(CPU *c, OP_CODE_INFO *o){
    if(!getFlag(c,C)){
        c->PC = o->address;
        //TODO: cpu add branch cycles here
    }
}

//Branch if carry set
void bcs(CPU *c, OP_CODE_INFO *o){
    if(getFlag(c,C)){
        c->PC = o->address;
        //TODO: cpu add branch cycles here
    }
}

//Branch if equals
void beq(CPU *c, OP_CODE_INFO *o){
    if(getFlag(c,Z)){
        c->PC = o->address;
        //TODO: cpu add branch cycles here
    }
}

// Test bits in memory with accumulator
void bit(CPU *c, OP_CODE_INFO *o){
    int8_t src = o->operand;
    int8_t accum = getRegByte(c, ACCUM);
    setFlag(c, V, (src & 0x40) ? 1 : 0); // get 6th bit of src
    setFlag(c, S, (src & 0x80) ? 1 : 0); // get 7th bit of src
    setFlag(c, Z, (src & accum) ? 0 : 1);
}

// Branch if result minus
void bmi(CPU *c, OP_CODE_INFO *o){
    if (getFlag(c, S)) {
        c->PC = o->address;
        //TODO: cpu add branch cycles here
    }
}

// Branch if not equals
void bne(CPU *c, OP_CODE_INFO *o){
    if(!(getFlag(c,Z))){
        c->PC = o->address;
        //TODO: cpu add branch cycles here
    }
}

// Branch if result plus
void bpl(CPU *c, OP_CODE_INFO *o){
    if(!(getFlag(c,S))){
        c->PC = o->address;
        //TODO: cpu add branch cycles here
    }
}

// TODO BRK
// Force Break
void brk(CPU *c, OP_CODE_INFO *o){
    (c->PC)++; // this could be between 0 and 3.
    PUSH(c, o, (c->PC >> 8) & 0xff); // Push return address onto the stack.
    PUSH(c, o, c->PC & 0xff); // (push Program Counter AND 0xFF)
    setFlag(c, B, 1);
    PUSH(c, o, getRegByte(c, STATUS)); // (push status register onto top of stack)
    setFlag(c, D, 1);
    // PC = (LOAD(0xFFFE) | (LOAD(0xFFFF) << 8)); change PC
}

// Branch if overflow clear
void bvc(CPU *c, OP_CODE_INFO *o){
    if (!(getFlag(c, V))){
        c->PC = o->address;
        //TODO: add clk cycles here
    }
}

//Branch on overflow set
void bvs(CPU *c, OP_CODE_INFO *o){
    if (getFlag(c, V)){
        c->PC = o->address;
        //TODO: add clk cycles here
    }
}

//Clear carry flag
void clc(CPU *c, __attribute__ ((unused)) OP_CODE_INFO *o){
    setFlag(c, C, 0);
}

//Clear decimal mode
void cld(CPU *c, __attribute__ ((unused)) OP_CODE_INFO *o){
    setFlag(c, D, 0);
}

//Clear interrupt disable bit
void cli(CPU *c, __attribute__ ((unused)) OP_CODE_INFO *o){
    setFlag(c, I, 0);
}

//Clear overflow flag
void clv(CPU *c, __attribute__ ((unused)) OP_CODE_INFO *o){
    setFlag(c, V, 0);
}

//Compare memory and accumulator
void cmp(CPU *c, OP_CODE_INFO *o){
    int8_t accum = getRegByte(c,ACCUM);
    int8_t operand = o->operand;
    int8_t diff = accum-operand;
    //longdiff is used to calculate whether a carry occurred
    uint16_t longDiff = (0x00FF&accum) - (0x00FF&operand);
    setFlag(c, C, longDiff < 0x100);
    setFlag(c, S, (diff & 0x80) ? 1 : 0);    // get 7th bit of src
    setFlag(c, Z, diff ? 0 : 1);
}

//Compare memory and index x
void cpx(CPU *c, OP_CODE_INFO *o){
    int8_t xVal = getRegByte(c,IND_X);
    int8_t operand = o->operand;
    int8_t diff = xVal-operand;
    //longdiff is used to calculate whether a carry occurred
    uint16_t longDiff = (0x00FF&xVal) - (0x00FF&operand);
    setFlag(c, C, longDiff < 0x100);
    setFlag(c, S, (diff & 0x80) ? 1 : 0);    // get 7th bit of src
    setFlag(c, Z, diff ? 0 : 1);
}

//Compare memory and index y
void cpy(CPU *c, OP_CODE_INFO *o){
    int8_t yVal = getRegByte(c,IND_Y);
    int8_t operand = o->operand;
    int8_t diff = yVal-operand;
    //longdiff is used to calculate whether a carry occurred
    uint16_t longDiff = (0x00FF&yVal) - (0x0FF&operand);
    setFlag(c, C, longDiff < 0x100);
    setFlag(c, S, (diff & 0x80) ? 1 : 0);    // get 7th bit of src
    setFlag(c, Z, diff ? 0 : 1);
}

//Decrement accum by 1
void dec(CPU *c, OP_CODE_INFO *o){
    uint8_t accumVal = getRegByte(c, ACCUM);
    uint8_t res = accumVal - 1;
    setSign(c,res);
    setZero(c,res);
    setRegByte(c, ACCUM, res);
}

//Decrement X index by 1
void dex(CPU *c, OP_CODE_INFO *o){
    uint8_t xVal = getRegByte(c, IND_X);
    uint8_t res = xVal - 1;
    setSign(c,res);
    setZero(c,res);
    setRegByte(c, IND_X, res);
}

//Decrement Y index by 1
void dey(CPU *c, OP_CODE_INFO *o){
    uint8_t yVal = getRegByte(c, IND_Y);
    uint8_t res = yVal - 1;
    setSign(c,res);
    setZero(c,res);
    setRegByte(c, IND_Y, res);
}

//Increment accum by 1
void inc(CPU *c, OP_CODE_INFO *o){
    uint8_t accumVal = getRegByte(c, ACCUM);
    uint8_t res = accumVal + 1;
    setSign(c,res);
    setZero(c,res);
    setRegByte(c, ACCUM, res);
}

//Increment X index by 1
void inx(CPU *c, OP_CODE_INFO *o){
    uint8_t xVal = getRegByte(c, IND_X);
    uint8_t res = xVal + 1;
    setSign(c,res);
    setZero(c,res);
    setRegByte(c, IND_X, res);
}

//Jump PC to 16 bit operand
void jmp(CPU *c, OP_CODE_INFO *o){
    c->PC = 0xFFFF&(o->address);
}

//Jump to subroutine
void jsr(CPU *c, OP_CODE_INFO *o){
    //decrement PC because PC will be
    //incremented by one when it jumps back
    c->PC--;
    //STACK holds eight bit values
    //so we push the 16 bit address
    //onto the stack in two parts
    PUSH(c, o, ((c->PC)>>8) & 0xFF);
    PUSH(c, o, c->PC & 0xFF);
    c->PC = o->operand;
}

//Load value into accumulator
void lda(CPU *c, OP_CODE_INFO *o){
    setSign(c, o->operand);
    setZero(c, o->operand);
    setRegByte(c, ACCUM, o->operand);
}

//Load value into x reg
void ldx(CPU *c, OP_CODE_INFO *o){
    setSign(c, o->operand);
    setZero(c, o->operand);
    setRegByte(c, IND_X, o->operand);
}

//Load value into y reg
void ldy(CPU *c, OP_CODE_INFO *o){
    setSign(c, o->operand);
    setZero(c, o->operand);
    setRegByte(c, IND_Y, o->operand);
}

//Logical shift right with zero fill
void lsr(CPU *c, OP_CODE_INFO *o){
    //shift rightmost bit into carry
    setFlag(c, C, o->operand & 0x01);
    //cast to uint8_t to force zero fill
    int8_t shifted = ((uint8_t)o->operand) >> 1;
    setSign(c, shifted);
    setZero(c, shifted);
    if(o->mode == ACC){
        setRegByte(c, ACCUM, shifted);
    } else {
        write(c, o->address, shifted);
    }
}

// No operation
void nop(CPU *c, OP_CODE_INFO *o){}

// OR memory with accumulator
void ora(CPU *c, OP_CODE_INFO *o){
    int8_t src = o->operand | getRegByte(c, ACCUM);
    setFlag(c, Z, src);
    setFlag(c, S, src);
    setRegByte(c, ACCUM, src);
}

// Push accumulator onto stack
void pha(CPU *c, OP_CODE_INFO *o){
    PUSH(c, o, getRegByte(c, ACCUM));
}

// Push status register onto stack
void php(CPU *c, OP_CODE_INFO *o){
    PUSH(c, o, getRegByte(c, STATUS));
}

// Pull accumulator from stack
void pla(CPU *c, OP_CODE_INFO *o){
    // setRegByte(c, ACCUM, PULL(c));
}

// Pull status register from stack
void plp(CPU *c, OP_CODE_INFO *o){
    // setRegByte(c, STATUS, PULL(c));
}

// Subtract operand from accumulator with borrow
void sbc(CPU *c, OP_CODE_INFO *o){
    //we want to subtract the opposite of the carry bit
    int8_t carry = getFlag(c,C) ? 0 : 1; 
    int8_t accum = getRegByte(c,ACCUM);
    int8_t operand = o->operand;
    uint16_t diff = (0x00FF&accum) - (0x00FF&operand) - (0x00FF&carry);
    setSign(c,diff&0xFF);
    setZero(c,diff&0xFF);
    setOverflowSubtract(c,accum,operand,diff&0xFF);
    if(getFlag(c,D)){ //in decimal mode
        if(((accum & 0xF) - carry) < (operand & 0xF)){
            diff -= 6;
        }
        if(diff > 0x99){
            diff -= 0x60;
        }
    }
    setFlag(c,C, diff < 0x100);
    setRegByte(c,ACCUM,diff&0xFF);
}

// Set carry flag to 1
void sec(CPU *c, OP_CODE_INFO *o){
    setFlag(c, C, 1);
}

// Store accumulator reg into memory
void sta(CPU *c, OP_CODE_INFO *o){
    write(c, o->address, getRegByte(c,ACCUM));
}

// Store X reg into memory
void stx(CPU *c, OP_CODE_INFO *o){
    write(c, o->address, getRegByte(c,IND_X));
}

// Transfer accumulator to Y reg
void tay(CPU *c, OP_CODE_INFO *o){
    int8_t accumVal = getRegByte(c,ACCUM);
    setSign(c,accumVal);
    setZero(c,accumVal);
    setRegByte(c,IND_Y,accumVal);
}

// Transfer Y to accumulator
void tya(CPU *c, OP_CODE_INFO *o){
    int8_t yVal = getRegByte(c,IND_Y);
    setSign(c,yVal);
    setZero(c,yVal);
    setRegByte(c,ACCUM,yVal);
}

// Transfer x to accumulator
void txa(CPU *c, OP_CODE_INFO *o){
    int8_t xVal = getRegByte(c,IND_X);
    setSign(c,xVal);
    setZero(c,xVal);
    setRegByte(c,ACCUM,xVal);
}



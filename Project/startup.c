#define RAM_START  0x20000000U
#define RAM_LENGTH 8192U
#define RAM_END    RAM_START + RAM_LENGTH
#define STACK      RAM_END - 4

int main() {
    while(1);
};


int reset_hdlr() {
    main();
    while(1) {}
}

volatile unsigned int __attribute__((section(".vector_table"))) vector_table [83] = {
    [0] = STACK,
    [1] = (unsigned int)&reset_hdlr
};
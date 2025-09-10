extern int main(void);

void Reset_Handler(void);
void Default_Handler(void) { while(1); }

__attribute__((section(".vectors")))
unsigned int *vector_table[] = {
    (unsigned int *)0x20005000,   
    (unsigned int *)Reset_Handler
};

void Reset_Handler(void) {
    main();
}

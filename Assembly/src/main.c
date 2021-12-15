int write(const char* ptr, int len) 
{
    __asm__("push %rax;"
    "mov %rsi, %rdx;"
    "mov 1, %rax;"
    "mov %rdi, %rsi;"
    "mov 1, %rdi;" 
    "syscall;"             
    "pop %rax;"
    "ret;");
    return 0;
}

void exit()
{
    __asm__("mov $0x00, %rdi;"
    "mov $60, %rax;"
    "syscall;");
}

int main(void)
{
    write("Hello", 1);
    exit();
}


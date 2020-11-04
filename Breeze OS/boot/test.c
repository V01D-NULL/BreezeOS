void _start() {
    int* mem = (int*)0xb8000;
    *mem = 0x50505050;
    return;
}


void kmain(void) {
    // Show we're here
    char *video = (char*)0xB8000;
    video[0] = 'S';
    video[1] = 0x07;
    video[2] = 'T';
    video[3] = 0x07;
    video[4] = 'A';
    video[5] = 0x07;
    video[6] = 'R';
    video[7] = 0x07;
    video[8] = 'T';
    video[9] = 0x07;
    while(1);

}

/*/////////////////
show.h 입니다.
*//////////////////

#define BUF_SIZE 1020 // Buffer size
#define NAME_SIZE 100 // NameSize
#define same 0 //strcmp
void error_handling(char * message) //error
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void desertMessengerIntro(void) // Desert Mssenger Intro
{
    printf("  mmmm                                 m     \n");
    printf("  #   \"m  mmm    mmm    mmm    m mm  mm#mm   \n");
    printf("  #    # #\"  #  #   \"  #\"  #   #\"  \"   #     \n");
    printf("  #    # #\"\"\"\"   \"\"\"m  #\"\"\"\"   #       #     \n");
    printf("  #mmm\"  \"#mm\"  \"mmm\"  \"#mm\"   #       \"mm\n");

    puts(" ");

    printf("                   m    m                                                        \n");
    printf("                   ##  ##  mmm    mmm    mmm    mmm   m mm    mmmm   mmm    m mm \n");
    printf("                   # ## # #\"  #  #   \"  #   \"  #\"  #  #\"  #  #\" \"#  #\"  #   #\"  \"\n");
    printf("                   # \"\" # #\"\"\"\"   \"\"\"m   \"\"\"m  #\"\"\"\"  #   #  #   #  #\"\"\"\"   #    \n");
    printf("                   #    # \"#mm\"  \"mmm\"  \"mmm\"  \"#mm\"  #   #  \"#m\"#  \"#mm\"   #    \n");
    printf("                                                              m  #               \n");
    printf("                                                               ""                \n");
    return;
}

void _help(void) 
{
    printf("pass : 말할 수 있는 권한을 상대에게 넘겨줍니다.\n");
    printf("quit : 대화를 종료합니다.\n");
    return;
}

void spectatMode(void)
{
    printf("======================\n       관전 모드\n======================\n");
    return;
}

void inputMode(void)
{
    printf("======================\n       입력 모드\n======================\n");
    return;
}


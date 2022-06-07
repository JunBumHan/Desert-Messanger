/*/////////////////
need.h 입니다.
*//////////////////
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

int terms_of_service(void) //이용약관
{

    char userInput[1000];

    printf("범행의 의도로 사용하지 않을 것을 약속하시겠습니까?\n");
    printf("동의합니다 : 거절합니다>"); 

    scanf("%s",userInput);
   
    if(!strcmp(userInput, "동의합니다"))
        return 1;
    if(!strcmp(userInput, "거절합니다"))
        return 0;
    
    printf("입력하진 정보가 알맞지 않습니다.\n");
    exit(1);

}

void _help(void) // 이용방법 /// 이용되는 곳 server.c , client.c 에서 사용
{
    printf("pass : 관전모드 또는 입력모드로 전환합니다, 말할 수 있는 권한을 상대에게 넘겨줍니다.\n");
    printf("quit : 대화를 종료합니다.\n");
    return;
}
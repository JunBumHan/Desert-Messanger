void desertMessengerIntro(void)
{
    printf("  mmmm                                 m     \n");
    printf("  #   \"m  mmm    mmm    mmm    m mm  mm#mm   \n");
    printf("  #    # #\"  #  #   \"  #\"  #   #\"  \"   #     \n");
    printf("  #    # #\"\"\"\"   \"\"\"m  #\"\"\"\"   #       #     \n");
    printf("  #mmm\"  \"#mm\"  \"mmm\"  \"#mm\"   #       \"mm\n");

    puts("");

    printf("                   m    m                                                        \n");
    printf("                   ##  ##  mmm    mmm    mmm    mmm   m mm    mmmm   mmm    m mm \n");
    printf("                   # ## # #\"  #  #   \"  #   \"  #\"  #  #\"  #  #\" \"#  #\"  #   #\"  \"\n");
    printf("                   # \"\" # #\"\"\"\"   \"\"\"m   \"\"\"m  #\"\"\"\"  #   #  #   #  #\"\"\"\"   #    \n");
    printf("                   #    # \"#mm\"  \"mmm\"  \"mmm\"  \"#mm\"  #   #  \"#m\"#  \"#mm\"   #    \n");
    printf("                                                              m  #               \n");
    printf("                                                               ""                \n");
    return;
}

int terms_of_service(void)
{

    char userInput[1000];

    printf("법행의 도로 안 사용하실 것을 약속하시나요?\n");
    printf("동의합니다 : 거절합니다>"); 
   
    if(!strcmp(userInput, "동의합니다"))
        return 1;
    if(!strcmp(userInput, "거절합니다"))
        return 0;
    
    printf("입력하진 정보가 알맞지 않습니다.\n");
    exit(1);

}
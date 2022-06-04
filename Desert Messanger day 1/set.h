void cleanConsole(void)
{
    system("clear");
    return;
}

int termsOfService(void)
{
    char userInput;

    printf("Desert Messenger 프로그램을 절대로 범행 목적으로 사용되서는 안됩니다\n");
    printf("이점에 대해 동의하십니까?\n");

    printf("(Y / n) : ");
    scanf(" %c",&userInput);

    if(userInput == 'Y') return 0;
    else return 1;
}

void error_handling(char *message)
{
    cleanConsole();
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
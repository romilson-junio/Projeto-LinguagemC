#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED
#include <time.h>
#include <string.h>

struct DATA{
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int secund;
};

struct DATA Data[1];

void newDate(){
    struct tm * tm;
    time_t t;
    int diaSemana;
    char data[20];
    time(&t);
    tm = localtime(&t);

    strftime(data, 20, "%d", tm);
    Data[0].day = atoi(data);
    strftime(data, 20, "%m", tm);
    Data[0].month = atoi(data);
    strftime(data, 20, "%Y", tm);
    Data[0].year = atoi(data);
    strftime(data, 20, "%H", tm);
    Data[0].hour = atoi(data);
    strftime(data, 20, "%M", tm);
    Data[0].minute = atoi(data);
    strftime(data, 20, "%S", tm);
    Data[0].secund = atoi(data);
}

void setDate(char data[], char hora[]){
    if(strlen(data) == 10 && (strlen(hora) == 8) || strcmp(hora, "NULL") == 0){
        int i;
        char day[3];
        char month[3];
        char year[5];
        char hour[3];
        char minute[3];
        char secund[3];

        day[0] = data[0];
        day[1] = data[1];
        Data[0].day = atoi(day);
        month[0] = data[3];
        month[1] = data[4];
        Data[0].month = atoi(month);
        year[0] = data[6];
        year[1] = data[7];
        year[2] = data[8];
        year[3] = data[9];
        Data[0].year = atoi(year);

        if(strcmp(hora, "NULL")==0){
            struct tm * tm;
            time_t t;;
            char data[20];
            time(&t);
            tm = localtime(&t);
            strftime(data, 20, "%H", tm);
            Data[0].hour = atoi(data);
            strftime(data, 20, "%M", tm);
            Data[0].minute = atoi(data);
            strftime(data, 20, "%S", tm);
            Data[0].secund = atoi(data);
        }else{
            hour[0] = hora[0];
            hour[1] = hora[1];
            Data[0].hour = atoi(hour);
            minute[0] = hora[3];
            minute[1] = hora[4];
            Data[0].minute = atoi(minute);
            secund[0] = hora[6];
            secund[1] = hora[7];
            Data[0].secund = atoi(secund);
        }
    }
}

void dataFormat(char data[]){
    char mes[20];
    if(strcmp(data, "d/m/Y") == 0){

        printf("%d/%d/%d\n", getDia(), getMes(), yyyy());

    } else if(strcmp(data, "d/m/y") == 0){

        printf("%d/%d/%d\n", getDia(), getMes(), yy());

    } else if(strcmp(data, "d/m/y h:m:s") == 0){

        printf("%d/%d/%d %d:%d:%d\n", getDia(), getMes(), yy(), getHora(), getMinuto(), getSegundo());

    } else if(strcmp(data, "d/m/Y h:m:s") == 0){

        printf("%d/%d/%d %d:%d:%d\n", getDia(), getMes(), yyyy(), getHora(), getMinuto(), getSegundo());

    } else if(strcmp(data, "d/m/y h:m") == 0){

        printf("%d/%d/%d %d:%d\n", getDia(), getMes(), yy(), getHora(), getMinuto());

    } else if(strcmp(data, "d/m/Y h:m") == 0){

        printf("%d/%d/%d %d:%d\n", getDia(), getMes(), yyyy(), getHora(), getMinuto());

    } else if(strcmp(data, "d/M/Y h:m") == 0){

        getMesExtenso(mes, 0);
        printf("%d de %s de %d %d:%d\n", getDia(), mes, yyyy(), getHora(), getMinuto());

    } else if(strcmp(data, "d/m/Y h:m") == 0){

        getMesExtenso(mes, 1);
        printf("%d %s %d %d:%d\n", getDia(), mes, yyyy(), getHora(), getMinuto());

    } else if(strcmp(data, "d/M/Y h:m:s") == 0){

        getMesExtenso(mes, 0);
        printf("%d de %s de %d %d:%d:%d\n", getDia(), mes, yyyy(), getHora(), getMinuto(), getSegundo());

    } else if(strcmp(data, "d/m/Y h:m:s") == 0){

        getMesExtenso(mes, 1);
        printf("%d %s %d %d:%d:%d\n", getDia(), mes, yyyy(), getHora(), getMinuto(), getSegundo());

    } else if(strcmp(data, "m") == 0){

        getMesExtenso(mes, 1);
        printf("%s\n", mes);

    } else if(strcmp(data, "M") == 0){

        getMesExtenso(mes, 0);
        printf("%s\n", mes);

    }else if(strcmp(data, "D, d/m/Y h:m:s") == 0){

        getMesExtenso(mes, 1);
        diaDaSemana();
        printf(", %d %s %d %d:%d:%d\n", getDia(), mes, yyyy(), getHora(), getMinuto(), getSegundo());

    } else if(strcmp(data, "D, d/M/Y h:m:s") == 0){

        getMesExtenso(mes, 0);
        diaDaSemana();
        printf(", %d de %s de %d %d:%d:%d\n", getDia(), mes, yyyy(), getHora(), getMinuto(), getSegundo());

    }else if(strcmp(data, "D, d/M/y h:m:s") == 0){

        getMesExtenso(mes, 0);
        diaDaSemana();
        printf(", %d/%s/%d %d:%d:%d\n", getDia(), mes, yy(), getHora(), getMinuto(), getSegundo());

    }else if(strcmp(data, "D, d/M/y h:m") == 0){

        getMesExtenso(mes, 0);
        diaDaSemana();
        printf(", %d/%s/%d %d:%d:%d\n", getDia(), mes, yy(), getHora(), getMinuto(), getSegundo());

    }else if(strcmp(data, "D, d/M/Y h:m") == 0){

        getMesExtenso(mes, 0);
        diaDaSemana();
        printf(", %d de %s de %d %d:%d\n", getDia(), mes, yyyy(), getHora(), getMinuto());

    }else if(strcmp(data, "D, d/m/Y h:m") == 0){

        getMesExtenso(mes, 1);
        diaDaSemana();
        printf(", %d %s %d %d:%d\n", getDia(), mes, yyyy(), getHora(), getMinuto());

    }else if(strcmp(data, "D, d/m/y h:m") == 0){

        getMesExtenso(mes, 1);
        diaDaSemana();
        printf(", %d/%s/%d %d:%d\n", getDia(), mes, yy(), getHora(), getMinuto());

    }else if(strcmp(data, "D, d/m/y h:m:s") == 0){

        getMesExtenso(mes, 1);
        diaDaSemana();
        printf(", %d/%s/%d %d:%d:%d\n", getDia(), mes, yy(), getHora(), getMinuto(), getSegundo());

    } else {

        getMesExtenso(mes, 0);
        diaDaSemana();
        printf(", %d de %s de %d %d:%d:%d\n", getDia(), mes, yyyy(), getHora(), getMinuto(), getSegundo());

    }

}
void getMesExtenso(char* mes, int abreviado){
    switch(getMes()){
        case 1:
            if(abreviado){
                strcpy(mes, "Jan");
            } else {
                strcpy(mes, "Janeiro");
            }
        break;
        case 2:
            if(abreviado){
                strcpy(mes, "Fev");
            } else {
                strcpy(mes, "Fevereiro");
            }
        break;
        case 3:
            if(abreviado){
                strcpy(mes, "Mar");
            } else {
                strcpy(mes, "Março");
            }
        break;
        case 4:
            if(abreviado){
                strcpy(mes, "Abr");
            } else {
                strcpy(mes, "Abril");
            }
        break;
        case 5:
            if(abreviado){
                strcpy(mes, "Mai");
            } else {
                strcpy(mes, "Maio");
            }
        break;
        case 6:
            if(abreviado){
                strcpy(mes, "Jun");
            } else {
                strcpy(mes, "Junho");
            }
        break;
        case 7:
            if(abreviado){
                strcpy(mes, "Jul");
            } else {
                strcpy(mes, "Julho");
            }
        break;
        case 8:
            if(abreviado){
                strcpy(mes, "Ago");
            } else {
                strcpy(mes, "Agosto");
            }
        break;
        case 9:
            if(abreviado){
                strcpy(mes, "Set");
            } else {
                strcpy(mes, "Setembro");
            }
        break;
        case 10:
            if(abreviado){
                strcpy(mes, "Out");
            } else {
                strcpy(mes, "Outubro");
            }
        break;
        case 11:
            if(abreviado){
                strcpy(mes, "Nov");
            } else {
                strcpy(mes, "Novembro");
            }
        break;
        case 12:
            if(abreviado){
                strcpy(mes, "Dez");
            } else {
                strcpy(mes, "Dezembro");
            }
        break;
    }
}


int getDia(){
    return Data[0].day;
}
int getMes(){
    return Data[0].month;
}
int getAno(){
    return Data[0].year;
}
int getHora(){
    return Data[0].hour;
}
int getMinuto(){
    return Data[0].minute;
}
int getSegundo(){
    return Data[0].secund;
}

int yyyy(){
    return getAno();
}
int yy(){
    char buffer[4];
    int ano;
    char stringAno[3];
    itoa(Data[0].year, buffer, 10);
    stringAno[0] = buffer[2];
    stringAno[1] = buffer[3];
    ano = atoi(stringAno);
    return ano;
}

void diaDaSemana(){
    time_t rawtime;
    struct tm * timeinfo;
    int year, month ,day;
    const char * weekday[] = { "Domingo",
                               "Segunda-Feira",
                               "Terça-Feira",
                               "Quarta-Feira",
                               "Quinta-Feira",
                               "Sexta-Feira",
                               "Sábado"};

    /* prompt user for date */
    year = Data[0].year;
    month = Data[0].month;
    day = Data[0].day;

    /* get current timeinfo and modify it to the user's choice */
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    timeinfo->tm_year = year - 1900;
    timeinfo->tm_mon = month - 1;
    timeinfo->tm_mday = day;

    /* call mktime: timeinfo->tm_wday will be set */
    mktime ( timeinfo );

    printf("%s", weekday[timeinfo->tm_wday]);

}

#endif // DATA_H_INCLUDED

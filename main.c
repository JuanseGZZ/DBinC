#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void createHelloWorldFile(char filename[30],char *argv[]);
void extraerPartes(const char *fuente, char *type, char *name, char *size, char *required, char *security);

int main(int argc,char *argv[]){
    if(argc>=1){
        printf("\n------\n%s\n-----\n",argv[0]);
        for(int i=0;i<argc;i++){
            printf("position[%d]: ",i);
            printf("%s\n",argv[i]);
            if(strcmp(argv[i], "/hola") == 0){
                printf("HOLAAAA!");
            }
            if(strcmp(argv[i], "create_module") == 0){
                printf("\ncreando modulo llamado %s\n",argv[i+1]);
                createHelloWorldFile(argv[i+1],argv);
            }
        }
    }
}


void createHelloWorldFile(char filename[30],char *argv[]) {
    FILE *file;
    unsigned short i = 0,count = 0;
    char registro[500] = {"    printf(\""};

    // Conteo de los argumentos (argv)
    while (argv[count] != NULL) {
        count++;
    }

    strcat(filename,".c");

    // Abre el archivo en modo escritura
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("No se puede abrir el archivo %s.\n", filename);
        exit(EXIT_FAILURE);
    }

    // Escribe el c�digo de "Hola Mundo" en el archivo
    fprintf(file, "#include <stdio.h>\n\n");
    fprintf(file, "int main(int argc,char *argv[]) {\n");
    fprintf(file, "//// aca las variables\n");

    char type[50], name[50], size[50], required[50], security[50];
    for(i=3;i<count;i++){
        memset(type, 0, sizeof(type));
        memset(name, 0, sizeof(name));
        memset(size, 0, sizeof(size));
        memset(required, 0, sizeof(required));
        memset(security, 0, sizeof(security));

        extraerPartes(argv[i], type, name, size, required, security);
        //printf("Type: %s, Name: %s, Size: %s, Required: %s, Security: %s\n", type, name, size, required, security);
        if (strcmp(type,"char")==0){
            strcat(registro," %%s");
            printf("\nSe agrego char\n");
        }
        if (strcmp(type,"int")==0){
            strcat(registro," %%d");
            printf("\nSe agrego int\n");
        }
    }
    strcat(registro," \\n\");\n");
    fprintf(file,registro);

    fprintf(file, "    printf(\"Hola Mundo\\n\");\n");
    fprintf(file, "    return 0;\n");
    fprintf(file, "}\n");

    // Cierra el archivo
    fclose(file);

    printf("Archivo %s creado exitosamente.\n", filename);
}


void extraerPartes(const char *fuente, char *type, char *name, char *size, char *required, char *security) {
    // Buscar la primera parte antes del parentesis
    const char *inicio = fuente;
    const char *parentesis = strchr(fuente, '(');
    if (parentesis) {
        strncpy(type, inicio, parentesis - inicio);
        type[parentesis - inicio] = '\0';
    } else {
        strcpy(type, "");
    }

    // Buscar la segunda parte entre los parentesis
    inicio = parentesis + 1;
    parentesis = strchr(inicio, ')');
    if (parentesis) {
        strncpy(name, inicio, parentesis - inicio);
        name[parentesis - inicio] = '\0';
    } else {
        strcpy(name, "");
    }

    // Buscar las partes entre los corchetes
    inicio = parentesis + 1;
    const char *corcheteApertura = strchr(inicio, '[');
    const char *corcheteCierre = strchr(inicio, ']');
    if (corcheteApertura && corcheteCierre && corcheteCierre > corcheteApertura) {
        strncpy(size, corcheteApertura + 1, corcheteCierre - corcheteApertura - 1);
        size[corcheteCierre - corcheteApertura - 1] = '\0';
    } else {
        strcpy(size, "");
    }

    inicio = corcheteCierre + 1;
    corcheteApertura = strchr(inicio, '[');
    corcheteCierre = strchr(inicio, ']');
    if (corcheteApertura && corcheteCierre && corcheteCierre > corcheteApertura) {
        strncpy(required, corcheteApertura + 1, corcheteCierre - corcheteApertura - 1);
        required[corcheteCierre - corcheteApertura - 1] = '\0';
    } else {
        strcpy(required, "");
    }

    inicio = corcheteCierre + 1;
    corcheteApertura = strchr(inicio, '[');
    corcheteCierre = strchr(inicio, ']');
    if (corcheteApertura && corcheteCierre && corcheteCierre > corcheteApertura) {
        strncpy(security, corcheteApertura + 1, corcheteCierre - corcheteApertura - 1);
        security[corcheteCierre - corcheteApertura - 1] = '\0';
    } else {
        strcpy(security, "");
    }
}

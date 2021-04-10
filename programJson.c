/* The file was created by imad in 09/04/2021*/

#include "cJSON.h"
#include<stdio.h>
#include <stdlib.h>

/*main program */
int main(int argc, const char * argv[]) {

    FILE *file = fopen(argv[1],"r");;

    if ( file == NULL ) {
        fprintf( stderr, "Cannot open file for reading\n" );
        exit( -1 );
    }

    char fileBuffer[1024];
    fread(fileBuffer, 1024, 1, file);
    fclose(file);

    // First, parse the whole thing
    cJSON *root = cJSON_Parse(fileBuffer);
    // Let's get some values
    cJSON *valeurChamp = NULL;
    valeurChamp = cJSON_GetObjectItemCaseSensitive(root, argv[2]);

    if (cJSON_IsNumber(valeurChamp)){
        //Here i consider only int values, it is the same thing for double ones
        int resultat = valeurChamp->valueint;
        printf("%s <int> : %d \n", argv[2], resultat);
    }
    else if (cJSON_IsBool(valeurChamp)){
        // Here i treat the case of boolean
        if(cJSON_IsFalse(valeurChamp)){
            printf("%s <bool> : False \n", argv[2]);
        }else if(cJSON_IsTrue(valeurChamp)){
            printf("%s <bool> : True \n", argv[2]);
        }
    }
    else if (cJSON_IsString(valeurChamp) && (valeurChamp->valuestring != NULL)){
        // Here is the case of string
        char *resultat = valeurChamp->valuestring;
        printf("%s <string> : %s \n", argv[2], resultat);
    }
    else if(cJSON_IsArray(valeurChamp)){
        // Here we treat the case of an array
        int champCount = cJSON_GetArraySize(valeurChamp);
        int i;
        printf("The field: %s\n", argv[2]);
        for (i = 0; i < champCount; i++) {

            // Get the JSON element and then get the values
            cJSON *element = cJSON_GetArrayItem(valeurChamp, i);
            char *elementCaracter = cJSON_Print(element);
            printf("%s\n", elementCaracter);
        }
    }
    else if(cJSON_IsObject(valeurChamp)){
        // Here we treat the case of an object the same thing like an array
        int champCount = cJSON_GetArraySize(valeurChamp);
        int i;
        printf("The field: %s\n", argv[2]);
        for (i = 0; i < champCount; i++) {

            // Get the JSON element and then get the values
            cJSON *element = cJSON_GetArrayItem(valeurChamp, i);
            char *elementCaracter = cJSON_Print(element);
            printf("%s\n", elementCaracter);
        }
    }
    else if (valeurChamp == NULL){
        // If the field doesn't exist
        printf("%s is not present \n", argv[2]);
    }
    else if (cJSON_IsInvalid(valeurChamp)){
        // If the value of the field is invalid
        printf("The value of %s is invalid", argv[2]);
    }
    else if(cJSON_IsNull(valeurChamp)){
        //If the value of the field is null
        printf("%s represents a null value", argv[2]);
    }else{
        printf("This type is not treated yet in the program");
    }

    // Finally we free the memory!
    cJSON_Delete(root);
    return 0;
}
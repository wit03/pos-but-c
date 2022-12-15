#include <stdio.h>
#include <string.h>
#include "StructOrganize.h"

int ExportStockFile(struct Shop *ptr)
{
    int i;
    FILE *file;
    file = fopen("stock.csv", "w");
    if (file == NULL)
    {
        printf("Import Error: opening stock.csv file. \n");
        return 1;
    }
    for (i = 0; i < 50; i++)
    {
        fprintf(file,
                "%d,%s,%.2f,%.2f,%d,%s,%d,%d,%d,%s",
                ptr[i].id,
                ptr[i].name,
                ptr[i].price,
                ptr[i].cost,
                ptr[i].quantity,
                ptr[i].description,
                ptr[i].minimum_sale_quantity,
                ptr[i].sale_quantity,
                ptr[i].lost_quantity,
                ptr[i].date);
        if (ferror(file))
        {
            printf("Error writing to file.\n");
            return 1;
        }
    }
    if (!ferror(file))
    {
        printf("\n stock record successfully written.");
    }
    fclose(file);
    return 0;
}

int ExportTransactionFile(struct Shop *ptr, int id, int qty, int is_lost, char date[50])
{
    FILE *file;
    file = fopen("transaction.csv", "a");

    if (file == NULL)
    {
        printf("\nError openning transaction.csv");
    }
    fprintf(file, "%d,%s,%f,%f,%d,%d,%s", id, ptr[id].name, ptr[id].price, ptr[id].cost, qty, is_lost, date);
    if (ferror(file))
    {
        printf("\nError writing to file\n");
    }
    else
    {
        printf("\nTransaction record successfuly written");
    }
    fclose(file);
    return 0;
}

int importStockData(struct Shop *ptr)
{
    // read stock.csv => run on start
    FILE *file;
    file = fopen("stock.csv", "r");
    if (file == NULL)
    {
        printf("Import Error: opening stock.csv file. \n");
        return 1;
    }
    char tempLine[1000];
    char *sp;
    int records = 0;

    while (fgets(tempLine, 1000, file) != NULL)
    {
        sp = strtok(tempLine, ",");
        ptr[records].id = atoi(sp);

        sp = strtok(NULL, ",");
        strcpy(ptr[records].name, sp);

        sp = strtok(NULL, ",");
        ptr[records].price = atof(sp);

        sp = strtok(NULL, ",");
        ptr[records].cost = atof(sp);

        sp = strtok(NULL, ",");
        ptr[records].quantity = atoi(sp);

        sp = strtok(NULL, ",");
        strcpy(ptr[records].description, sp);

        sp = strtok(NULL, ",");
        ptr[records].minimum_sale_quantity = atoi(sp);

        sp = strtok(NULL, ",");
        ptr[records].sale_quantity = atoi(sp);

        sp = strtok(NULL, ",");
        ptr[records].lost_quantity = atoi(sp);

        sp = strtok(NULL, ",");
        strcpy(ptr[records].date, sp);

        records++;
    }
    fclose(file);

    printf("\nStock: %d records read.\n", records);
    return 0;
}

int importTransactionData(struct Shop *ptr)
{
    FILE *file;
    file = fopen("transaction.csv", "r");
    if (file == NULL)
    {
        printf("Import Error: opening transaction.csv file. \n");
        return 1;
    }
    char tempLine[500];
    char *sp;
    int records = 0;
    while (fgets(tempLine, 500, file) != NULL)
    {
        sp = strtok(tempLine, ",");
        ptr[records].id = atoi(sp);

        sp = strtok(NULL, ",");
        strcpy(ptr[records].name, sp);

        sp = strtok(NULL, ",");
        ptr[records].price = atof(sp);

        sp = strtok(NULL, ",");
        ptr[records].cost = atof(sp);

        sp = strtok(NULL, ",");
        ptr[records].quantity = atoi(sp);

        sp = strtok(NULL, ",");
        ptr[records].is_lost = atoi(sp);

        sp = strtok(NULL, ",");
        strcpy(ptr[records].date, sp);
        records++;
    }
    fclose(file);
    printf("Transaction: %d records read.\n", records);
    return 0;
}
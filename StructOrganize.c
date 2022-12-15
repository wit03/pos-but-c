#include <stdio.h>
#include <string.h>
#include "StructOrganize.h"

int ExportStockFile(struct Shop *ptr)
{
    int i;
    FILE *filed;
    filed = fopen("stock.csv", "w");
    if (filed == NULL)
    {
        printf("Import Error: opening stock.csv file. \n");
        return 1;
    }
    for (i = 0; i < 50; i++)
    {
        fprintf(filed,
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
        if (ferror(filed))
        {
            printf("Error writing to file.\n");
            return 1;
        }
    }
    if (!ferror(filed))
    {
        printf("\n stock record successfully written.");
    }
    fclose(filed);
    return 0;
}

int ExportTransactionFile(struct Shop *ptr, int id, int qty, int is_lost, char date[50])
{
    FILE *filess;
    filess = fopen("transaction.csv", "a");

    if (filess == NULL)
    {
        printf("\nError openning transaction.csv");
    }
    fprintf(filess, "%d,%s,%f,%f,%d,%d,%s", id, ptr[id].name, ptr[id].price, ptr[id].cost, qty, is_lost, date);
    if (ferror(filess))
    {
        printf("\nError writing to file\n");
    }
    else
    {
        printf("\nTransaction record successfuly written");
    }
    fclose(filess);
    return 0;
}
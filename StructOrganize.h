#ifndef Struct_Organize   /* Include guard */
#define Struct_Organize

struct Shop
{
    int id;
    char name[50];
    float price;
    float cost;
    int quantity;
    char description[200];
    int minimum_sale_quantity;
    int sale_quantity;
    int lost_quantity;
    int is_lost;
    char date[50];
};

int ExportStockFile(struct Shop *ptr);   
int ExportTransactionFile(struct Shop *ptr, int id, int qty, int is_lost, char date[50]);
int importStockData(struct Shop *ptr);
int importTransactionData(struct Shop *ptr);

#endif // FOO_H_
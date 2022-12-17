#include "StructOrganize.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int mainMode = 0;
int ALLPRODUCT = 50;
int ALLTRANSACTION = 0;

int flag;
int check;
int element;
int i;
char temp_name[50];
float temp_price;
float temp_cost;
int temp_quantity;
char temp_description[200];
int temp_minimum_sale_quantity;
int temp_sale_quantity;
int temp_lost_quantity;
int temp;
time_t t;
struct tm *info;

void pos(struct Shop *ptr, struct Shop *ptr2);
void inventory(struct Shop *ptr, struct Shop *ptr2);
void viewsummary(struct Shop *ptr, struct Shop *ptr2);
void music(struct Shop *ptr, struct Shop *ptr2);

void menuSelection(int *mode, struct Shop *ptr, struct Shop *ptr2)
{
    printf("\n***********************************\n");
    printf("*           Select a tools:         *\n");
    printf("*                                   *\n");
    printf("*  1. Inventory Manager             *\n");
    printf("*  2. Accounting System             *\n");
    printf("*  3. POS System                    *\n");
    printf("*  4. Music Player (Windows only)   *\n");
    printf("*                                   *\n");
    printf("*************************************\n");
    printf("Select: ");
    scanf("%d", mode);

    switch (*mode)
    {
    case 1:
        printf("Selected: 1. Inventory Manager\n\n");
        inventory(ptr, ptr2);
        break;
    case 2:
        printf("Selected: 2. Accounting System\n\n");
        viewsummary(ptr, ptr2);
        break;
    case 3:
        printf("Selected: 3. POS System\n\n");
        pos(ptr, ptr2);
        break;
    case 4:
        printf("Selected: 4. Music Player\n\n");
        music(ptr, ptr2);
        break;
    default:
        menuSelection(mode, ptr, ptr2);
    }
}

void inventory(struct Shop *ptr, struct Shop *ptr2)
{
    int in_mode = 0;
    printf("\n****************************\n");
    printf("*   %cInventory manager%c    *\n", '"', '"');
    printf("*    Select a function:    *\n");
    printf("*  1. Create a product     *\n");
    printf("*  2. Find a product       *\n");
    printf("*  3. Update a product     *\n");
    printf("*  4. Delete a product     *\n");
    printf("*  0. Back to main menu    *\n");
    printf("****************************\n");
    printf("Select: ");
    scanf("%d", &in_mode);

    switch (in_mode)
    {
    case 0:
        // back to main menu
        menuSelection(&mainMode, ptr, ptr2);
    case 1:
        // Create a product
        for (i = 0; i < ALLPRODUCT; i++)
        { // check until the g one or new one
            if (strcmp(ptr[i].name, "DELETED") == 0)
            {
                break;
            }
        }
        flag = 1;
        do
        { // get a new product info
            switch (flag)
            {
            case 1:
                printf("\nPlease Input new product information\n");
                printf("Product ID : %d\n", i);
                printf("Name       : ");
                scanf(" %[^\t\n]s", temp_name);
                printf("Price      : ");
                scanf("%f", &temp_price);
                printf("Cost       : ");
                scanf("%f", &temp_cost);
                printf("Quantity   : ");
                scanf("%d", &temp_quantity);
                printf("Description: ");
                scanf(" %[^\t\n]s", temp_description);
                printf("Minimum Sale Quantity : ");
                scanf("%d", &temp_minimum_sale_quantity);
                printf("Sale Quantity(should be zero): ");
                scanf("%d", &temp_sale_quantity);
                printf("Lost Quantity         : ");
                scanf("%d", &temp_lost_quantity);
                printf("\n************************\n");
                printf("* Is it correct? (0/1) *\n");
                printf("*    0. Correct        *\n");
                printf("*    1. Incorrect      *\n");
                printf("************************\n");
                printf("Select : ");
                scanf("%d", &flag);

            case 0:
                break;

            default:
                flag = 1;
            }
        } while (flag != 0);

        // assigning new info to the variable
        ptr[i].id = i;
        strcpy(ptr[i].name, temp_name);
        ptr[i].price = temp_price;
        ptr[i].cost = temp_cost;
        ptr[i].quantity = temp_quantity;
        strcpy(ptr[i].description, temp_description);
        ptr[i].minimum_sale_quantity = temp_minimum_sale_quantity;
        ptr[i].sale_quantity = temp_sale_quantity;
        ptr[i].lost_quantity = temp_lost_quantity;
        time(&t);
        info = localtime(&t);
        strcpy(ptr[i].date, asctime(info));
        printf("\nADDED %s on -> %s\n", ptr[i].name, ptr[i].date);
        ExportStockFile(ptr);
        inventory(ptr, ptr2); // back to menu

    case 2:
        // Find a product
        flag = 0;
        do
        {
            printf("\n*************************************\n");
            printf("*     Search by :                   *\n");
            printf("*     1. ID                         *\n");
            printf("*     2. Name                       *\n");
            printf("*     3. Back to inventory menu     *\n");
            printf("*************************************\n");
            printf("Select: ");
            scanf("%d", &flag); // select Mode
            switch (flag)
            {
            case 1:
                // ID searching
                printf("Enter ID: ");
                int search_id = 0;
                scanf("%d", &search_id);
                if (strcmp(ptr[search_id].name, "DELETED") == 0)
                {
                    printf("\nThis product ID does not exist\n\n");
                }
                else
                {
                    printf("\nProduct ID : %d\n", ptr[search_id].id);
                    printf("Name       : %s\n", ptr[search_id].name);
                    printf("Price      : %f\n", ptr[search_id].price);
                    printf("Cost       : %f\n", ptr[search_id].cost);
                    printf("Quantity   : %d\n", ptr[search_id].quantity);
                    printf("Description: %s\n", ptr[search_id].description);
                    printf("Minimum Sale Quantity : %d\n",
                           ptr[search_id].minimum_sale_quantity);
                    printf("Sale Quantity         : %d\n", ptr[search_id].sale_quantity);
                    printf("Lost Quantity         : %d\n", ptr[search_id].lost_quantity);
                    printf("Time Created          : %s\n\n", ptr[search_id].date);
                }
                break;

            case 2:
                // Name searching
                printf("Enter Name: ");
                char search_name[50];
                scanf(" %[^\t\n]s", search_name);
                check = 0;
                for (element = 0; element < ALLPRODUCT; element++)
                {
                    if (strcmp(search_name, ptr[element].name) ==
                        0)
                    { // return 0 if after comparing and it is the same
                        break;
                    }
                    else if (element == ALLPRODUCT - 1)
                    {
                        check = 1;
                    }
                }
                if (check == 1)
                {
                    printf("\nThis product ID does not exist\n\n");
                }
                else if (check == 0)
                {
                    printf("\nProduct ID : %d\n", ptr[element].id);
                    printf("Name       : %s\n", ptr[element].name);
                    printf("Price      : %f\n", ptr[element].price);
                    printf("Cost       : %f\n", ptr[element].cost);
                    printf("Quantity   : %d\n", ptr[element].quantity);
                    printf("Description: %s\n", ptr[element].description);
                    printf("Minimum Sale Quantity : %d\n",
                           ptr[element].minimum_sale_quantity);
                    printf("Sale Quantity         : %d\n", ptr[element].sale_quantity);
                    printf("Lost Quantity         : %d\n", ptr[element].lost_quantity);
                    printf("Time Created          : %s\n\n", ptr[element].date);
                }
                break;
            }
        } while (flag != 3);
        ExportStockFile(ptr);
        inventory(ptr, ptr2);

    case 3:
        // Find a product and update the product
        flag = 0;
        do
        {
            printf("\n*************************************\n");
            printf("*     Search by :                   *\n");
            printf("*     1. ID                         *\n");
            printf("*     2. Name                       *\n");
            printf("*     3. Back to inventory menu     *\n");
            printf("*************************************\n");
            printf("Select: ");
            scanf("%d", &flag);
            switch (flag)
            {
            case 1:
                printf("Enter ID: ");
                int search_id = 0;
                scanf("%d", &search_id);
                if (strcmp(ptr[search_id].name, "DELETED") == 0)
                {
                    printf("\nThis product ID does not exist\n\n");
                }
                else
                {
                    printf("\n*Current information*\n");
                    printf("Product ID : %d\n", ptr[search_id].id);
                    printf("Name       : %s\n", ptr[search_id].name);
                    printf("Price      : %f\n", ptr[search_id].price);
                    printf("Cost       : %f\n", ptr[search_id].cost);
                    printf("Quantity   : %d\n", ptr[search_id].quantity);
                    printf("Description: %s\n", ptr[search_id].description);
                    printf("Minimum Sale Quantity : %d\n",
                           ptr[search_id].minimum_sale_quantity);
                    printf("Sale Quantity         : %d\n", ptr[search_id].sale_quantity);
                    printf("Lost Quantity         : %d\n", ptr[search_id].lost_quantity);
                    printf("Time Created          : %s\n\n", ptr[search_id].date);
                    // new
                    printf("\nPlease input new information\n");
                    printf("Product ID : %d\n", ptr[search_id].id);
                    printf("Name       : ");
                    scanf(" %[^\t\n]s", ptr[search_id].name);
                    printf("Price      : ");
                    scanf("%f", &ptr[search_id].price);
                    printf("Cost       : ");
                    scanf("%f", &ptr[search_id].cost);
                    printf("Quantity   : ");
                    scanf("%d", &ptr[search_id].quantity);
                    printf("Description: ");
                    scanf(" %[^\t\n]s", ptr[search_id].description);
                    printf("Minimum Sale Quantity : ");
                    scanf("%d", &ptr[search_id].minimum_sale_quantity);
                    printf("Sale Quantity         : ");
                    scanf("%d", &ptr[search_id].sale_quantity);
                    printf("Lost Quantity         : ");
                    scanf("%d", &ptr[search_id].lost_quantity);
                    time(&t);
                    info = localtime(&t);
                    strcpy(ptr[search_id].date, asctime(info));
                    ExportStockFile(ptr);
                    printf("New information has been successfully updated\n\n");
                }
                break;

            case 2:
                printf("Enter Name: ");
                char search_name[50];
                scanf(" %[^\t\n]s", search_name);
                check = 0;
                for (element = 0; element < ALLPRODUCT; element++)
                {
                    if (strcmp(search_name, ptr[element].name) == 0)
                    {
                        break;
                    }
                    else if (element == ALLPRODUCT - 1)
                    {
                        check = 1;
                    }
                }
                if (check == 1)
                {
                    printf("\nThis product ID does not exist\n\n");
                }
                else if (check == 0)
                {
                    printf("Current \n");
                    printf("\nProduct ID : %d\n", ptr[element].id);
                    printf("Name       : %s\n", ptr[element].name);
                    printf("Price      : %f\n", ptr[element].price);
                    printf("Cost       : %f\n", ptr[element].cost);
                    printf("Quantity   : %d\n", ptr[element].quantity);
                    printf("Description: %s\n", ptr[element].description);
                    printf("Minimum Sale Quantity : %d\n",
                           ptr[element].minimum_sale_quantity);
                    printf("Sale Quantity         : %d\n", ptr[element].sale_quantity);
                    printf("Lost Quantity         : %d\n\n", ptr[element].lost_quantity);
                    // New update
                    printf("\nPlease input new information\n");
                    printf("Product ID : %d\n", ptr[element].id);
                    printf("Name       : ");
                    scanf(" %[^\t\n]s", ptr[element].name);
                    printf("Price      : ");
                    scanf("%f", &ptr[element].price);
                    printf("Cost       : ");
                    scanf("%f", &ptr[element].cost);
                    printf("Quantity   : ");
                    scanf("%d", &ptr[element].quantity);
                    printf("Description: ");
                    scanf(" %[^\t\n]s", ptr[element].description);
                    printf("Minimum Sale Quantity : ");
                    scanf("%d", &ptr[element].minimum_sale_quantity);
                    printf("Sale Quantity         : ");
                    scanf("%d", &ptr[element].sale_quantity);
                    printf("Lost Quantity         : ");
                    scanf("%d", &ptr[element].lost_quantity);
                    time(&t);
                    info = localtime(&t);
                    strcpy(ptr[search_id].date, asctime(info));
                    ExportStockFile(ptr);
                    printf("New information has been successfully updated\n\n");
                }
                break;
            }
        } while (flag != 3);
        inventory(ptr, ptr2);

    case 4:
        // Find a product and delete the product
        flag = 0;
        do
        {
            printf("\n*************************************\n");
            printf("*     Search by :                   *\n");
            printf("*     1. ID                         *\n");
            printf("*     2. Name                       *\n");
            printf("*     3. Back to inventory menu     *\n");
            printf("*************************************\n");
            printf("Select: ");
            scanf("%d", &flag); // select Mode
            switch (flag)
            {
            case 1:
                // ID searching
                printf("Enter ID: ");
                int search_id = 0;
                scanf("%d", &search_id);
                if (strcmp(ptr[search_id].name, "DELETED") == 0)
                {
                    printf("\nThis product ID does not exist\n\n");
                }
                else
                {
                    printf("\nProduct ID : %d\n", ptr[search_id].id);
                    printf("Name       : %s\n", ptr[search_id].name);
                    printf("Price      : %f\n", ptr[search_id].price);
                    printf("Cost       : %f\n", ptr[search_id].cost);
                    printf("Quantity   : %d\n", ptr[search_id].quantity);
                    printf("Description: %s\n", ptr[search_id].description);
                    printf("Minimum Sale Quantity : %d\n",
                           ptr[search_id].minimum_sale_quantity);
                    printf("Sale Quantity         : %d\n", ptr[search_id].sale_quantity);
                    printf("Lost Quantity         : %d\n\n",
                           ptr[search_id].lost_quantity);
                    printf("Time Created          : %s\n\n", ptr[search_id].date);
                    do
                    { // delete part
                        temp = 0;
                        printf("\n*******************************\n");
                        printf("* Do you wish to delete (0/1) *\n");
                        printf("*         0. Yes              *\n");
                        printf("*         1. No               *\n");
                        printf("*******************************\n");
                        printf("Select: ");
                        scanf("%d", &temp);
                        switch (temp)
                        {
                        case 0:
                            strcpy(ptr[search_id].name, "DELETED");
                            ptr[search_id].price = 0;
                            ptr[search_id].cost = 0;
                            ptr[search_id].quantity = 0;
                            strcpy(ptr[search_id].description, "DELETED");
                            ptr[search_id].minimum_sale_quantity = 0;
                            ptr[search_id].sale_quantity = 0;
                            ptr[search_id].lost_quantity = 0;
                            strcpy(ptr[search_id].date, "DELETED");
                            printf("\nThis product is successfully deleted\n\n");
                            temp = 1;
                        }
                    } while (temp != 1);
                }
                ExportStockFile(ptr);
                inventory(ptr, ptr2);
            case 2:
                // Name searching
                printf("Enter Name: ");
                char search_name[50];
                scanf(" %[^\t\n]s", search_name);
                check = 0;
                for (element = 0; element < ALLPRODUCT; element++)
                {
                    if (strcmp(search_name, ptr[element].name) ==
                        0)
                    { // return 0 if after comparing and it is the same
                        break;
                    }
                    else if (element == ALLPRODUCT - 1)
                    {
                        check = 1;
                    }
                }
                if (check == 1)
                {
                    printf("\nThis product ID does not exist\n\n");
                }
                else if (check == 0)
                {
                    printf("\nProduct ID : %d\n", ptr[element].id);
                    printf("Name       : %s\n", ptr[element].name);
                    printf("Price      : %f\n", ptr[element].price);
                    printf("Cost       : %f\n", ptr[element].cost);
                    printf("Quantity   : %d\n", ptr[element].quantity);
                    printf("Description: %s\n", ptr[element].description);
                    printf("Minimum Sale Quantity : %d\n",
                           ptr[element].minimum_sale_quantity);
                    printf("Sale Quantity         : %d\n", ptr[element].sale_quantity);
                    printf("Lost Quantity         : %d\n\n", ptr[element].lost_quantity);
                    printf("Time Created          : %s\n\n", ptr[element].date);
                    do
                    {
                        temp = 0;
                        printf("\n*******************************\n");
                        printf("* Do you wish to delete (0/1) *\n");
                        printf("*         0. Yes              *\n");
                        printf("*         1. No               *\n");
                        printf("*******************************\n");
                        printf("Select: ");
                        scanf("%d", &temp);
                        switch (temp)
                        {
                        case 0:
                            strcpy(ptr[element].name, "DELETED");
                            ptr[element].price = 0;
                            ptr[element].cost = 0;
                            ptr[element].quantity = 0;
                            strcpy(ptr[element].description, "DELETED");
                            ptr[element].minimum_sale_quantity = 0;
                            ptr[element].sale_quantity = 0;
                            ptr[element].lost_quantity = 0;
                            strcpy(ptr[element].date, "DELETED");
                            printf("\nThis product is successfully deleted\n\n");
                            temp = 1;
                        }
                    } while (temp != 1);
                }
                break;
            }
        } while (flag != 3);
        ExportStockFile(ptr);
        inventory(ptr, ptr2);

    default:
        inventory(ptr, ptr2);
    }
}

void pos(struct Shop *ptr, struct Shop *ptr2)
{
    int subMode = -1;
    int id = 0;
    int qty = 0;
    int i = 0;

    printf("****************************\n");
    printf("*     Select a function:   *\n");
    printf("*                          *\n");
    printf("*  1. Sell                 *\n");
    printf("*  2. Report lost items    *\n");
    printf("*  0. back to main menu    *\n");
    printf("*                          *\n");
    printf("****************************\n");
    printf("Select: ");
    scanf("%d", &subMode);

    switch (subMode)
    {
    case 0:
        menuSelection(&mainMode, ptr, ptr2);
        break;

    case 1:
        printf("Selected: 1. Sell\n");
        printf("Enter ID: ");
        scanf("%d", &id);
        printf("Enter Quantity: ");
        scanf("%d", &qty);

        for (i = 0; i < ALLPRODUCT; i++)
        { // check until the g one or new one
            if (strcmp(ptr[i].name, ptr[id].name) == 0)
            {
                break;
            }
        }
        ALLTRANSACTION++;
        // update in struct array
        ptr[i].quantity -= qty;
        ptr[i].sale_quantity += qty;
        // update in stock.csv
        ExportStockFile(ptr);
        // write on transaction.csv
        info = localtime(&t);
        ExportTransactionFile(ptr, id, qty, 0, info->tm_yday);

        printf("\n=======Summary=======\n");
        printf("Name: %s\n", ptr[id].name);
        printf("Sold quantity: %d\n", qty);
        printf("Total Sold: %d\n", ptr[id].sale_quantity);
        printf("Stock Left: %d\n", ptr[id].quantity);
        printf("Profit Make: %f\n", (ptr[id].price - ptr[id].cost) * qty);
        printf("Total Price: %f\n", (ptr[id].price * qty));
        printf("=====================\n\n");
        id = 0;
        qty = 0;
        i = 0;
        pos(ptr, ptr2);
        break;
    case 2:
        printf("Selected: 2. Report lost items\n");
        printf("Enter ID: ");
        scanf("%d", &id);
        printf("Enter Quantity: ");
        scanf("%d", &qty);

        for (i = 0; i < ALLPRODUCT; i++)
        { // check until the g one or new one
            if (strcmp(ptr[i].name, ptr[id].name) == 0)
            {
                break;
            }
        }
        ALLTRANSACTION++;
        // update in struct array
        ptr[i].quantity -= qty;
        ptr[i].lost_quantity += qty;
        // update in stock.csv
        ExportStockFile(ptr);
        // write on transaction
        info = localtime(&t);
        ExportTransactionFile(ptr, id, qty, 1, info->tm_yday);

        printf("\n=======Summary=======\n");
        printf("Name: %s\n", ptr[id].name);
        printf("Lost quantity: %d\n", qty);
        printf("Total Lost: %d\n", ptr[id].lost_quantity);
        printf("Stock Left: %d\n", ptr[id].quantity);
        printf("Total Loss: %f\n", ptr[id].cost * qty);
        printf("=====================\n\n");
        id = 0;
        qty = 0;
        pos(ptr, ptr2);
        break;
    default:
        printf("\n!Wrong option Please reselect!\n");
        subMode = 0;
        pos(ptr, ptr2);
    }
}

void viewsummary(struct Shop *ptr, struct Shop *ptr2)
{
    float totalSaleSummary = 0;
    float costOfTotalSale = 0;
    float costOfTotalLost = 0;
    float profit = 0;

    int subMode = -1;
    printf("\n************************************\n");
    printf("*     Select to View:              *\n");
    printf("*                                  *\n");
    printf("*  1. View Day Summary             *\n");
    printf("*  2. View Week Summary            *\n");
    printf("*  3. View Month Summary           *\n");
    printf("*  0. Back to main menu            *\n");
    printf("*                                  *\n");
    printf("************************************\n");
    printf("Select: ");
    scanf("%d", &subMode);

    switch (subMode)
    {
    case 0:
        menuSelection(&mainMode, ptr, ptr2);
        break;
    case 1:
        info = localtime(&t);
        for (int i = 0; i < ALLTRANSACTION; i++)
        {
            if (ptr2[i].selldays == info->tm_yday)
            {
                totalSaleSummary = totalSaleSummary + (ptr2[i].price * ptr2[i].quantity);
                if (ptr2[i].is_lost == 0)
                {
                    costOfTotalSale = costOfTotalSale + (ptr2[i].cost * ptr2[i].quantity);
                }
                else
                {
                    costOfTotalLost = costOfTotalLost + (ptr2[i].cost * ptr2[i].quantity);
                }
            }
        }

        printf("Selected: 1. View Day Summary\n");
        printf("\n************************************\n");
        printf("            Day Summary:          \n");
        printf("                                  \n");
        printf("  Total Sell: %.2f                \n", totalSaleSummary);
        printf("  Cost of Total Sell: %.2f        \n", costOfTotalSale);
        printf("  Cost of Loss and Broken: %.2f   \n", costOfTotalLost);
        printf("  Profit of Total Sell: %.2f      \n", totalSaleSummary - costOfTotalLost - costOfTotalSale);
        printf("                                  \n");
        printf("************************************\n");
        totalSaleSummary = 0;
        costOfTotalSale = 0;
        costOfTotalLost = 0;
        viewsummary(ptr, ptr2);
        break;
    case 2:
        info = localtime(&t);
        for (int i = 0; i < ALLTRANSACTION; i++)
        {
            if (ptr2[i].selldays >= info->tm_yday - 7 && ptr2[i].selldays <= info->tm_yday)
            {
                totalSaleSummary += (ptr2[i].price * ptr2[i].quantity);
                if (ptr2[i].is_lost == 0)
                {
                    costOfTotalSale += (ptr2[i].cost * ptr2[i].quantity);
                }
                else
                {
                    costOfTotalLost += (ptr2[i].cost * ptr2[i].quantity);
                }
            }
        }
        printf("Selected: 2. View Week Summary\n");
        printf("\n************************************\n");
        printf("           Week Summary:          \n");
        printf("                                  \n");
        printf("  Total Sell: %.2f                \n", totalSaleSummary);
        printf("  Cost of Total Sell: %.2f        \n", costOfTotalSale);
        printf("  Cost of Loss and Broken: %.2f   \n", costOfTotalLost);
        printf("  Profit of Total Sell: %.2f      \n", totalSaleSummary - costOfTotalLost - costOfTotalSale);
        printf("                                  \n");
        printf("************************************\n");
        totalSaleSummary = 0;
        costOfTotalSale = 0;
        costOfTotalLost = 0;
        viewsummary(ptr, ptr2);
        break;
    case 3:
        info = localtime(&t);
        for (int i = 0; i < ALLTRANSACTION; i++)
        {
            if (ptr2[i].selldays >= info->tm_yday - 30 && ptr2[i].selldays <= info->tm_yday)
            {
                totalSaleSummary += (ptr2[i].price * ptr2[i].quantity);
                if (ptr2[i].is_lost == 0)
                {
                    costOfTotalSale += (ptr2[i].cost * ptr2[i].quantity);
                }
                else
                {
                    costOfTotalLost += (ptr2[i].cost * ptr2[i].quantity);
                }
            }
        }
        printf("Selected: 3. View Month Summary\n");
        printf("\n************************************\n");
        printf("          Month Summary:          \n");
        printf("                                  \n");
        printf("  Total Sell: %.2f                \n", totalSaleSummary);
        printf("  Cost of Total Sell: %.2f        \n", costOfTotalSale);
        printf("  Cost of Loss and Broken: %.2f   \n", costOfTotalLost);
        printf("  Profit of Total Sell: %.2f      \n", totalSaleSummary - costOfTotalLost - costOfTotalSale);
        printf("                                  \n");
        printf("************************************\n");
        totalSaleSummary = 0;
        costOfTotalSale = 0;
        costOfTotalLost = 0;
        viewsummary(ptr, ptr2);
        break;
    default:
        printf("\n!Wrong option Please reselect!\n");
        subMode = 0;
        viewsummary(ptr, ptr2);
    }
}

void music(struct Shop *ptr, struct Shop *ptr2){
    int n;
    printf("Choose your song\n1.QLER - Jeep\n2.Blackbeans - Dance with me\n3.Landokmai - Summertime\n4.Rick Astley - Never Gonna Give You Up\n5.yuji - Old Love\n");
    printf("6.SLAPKISS - My Favorite Ex\n7.The Weeknd - Die For You\n8.Safeplanet - With You\n9.Safeplanet - Carry\n10.Newery - Fall in love\n");
    do{
        printf("If you want to exit please type 11\nPlease enter number : ");
        scanf("%d",&n);
        printf("\n");
        switch(n){
            case 1:system("START https://www.youtube.com/watch?v=pk4q4-U891E");
                    break;
            case 2:system("START https://www.youtube.com/watch?v=10GeHGvHUsA");
                    break;
            case 3:system("START https://www.youtube.com/watch?v=6234mV5dsl4");
                    break;
            case 4:system("START https://www.youtube.com/watch?v=dQw4w9WgXcQ");
                    break;
            case 5:system("START https://www.youtube.com/watch?v=5YkYwiSJKDI");
                    break;
            case 6:system("START https://www.youtube.com/watch?v=FT9yCalL10k");
                    break;
            case 7:system("START https://www.youtube.com/watch?v=QLCpqdqeoII");
                    break;
            case 8:system("START https://www.youtube.com/watch?v=4xvSFYbVa0U");
                    break;
            case 9:system("START https://www.youtube.com/watch?v=DJ-t5-CRSZY");
                    break;
            case 10:system("START https://www.youtube.com/watch?v=CSZozBW7xMI");
                    break;
        }
    }while(n!=11);
    menuSelection(&mainMode, ptr, ptr2);
}

int main(void)
{
    struct Shop stock[ALLPRODUCT];
    struct Shop transaction[50];
    printf("Welcome to POS System\n");
    t = time(NULL);
    importStockData(stock);
    importTransactionData(transaction, &ALLTRANSACTION);
    menuSelection(&mainMode, stock, transaction);

    return 0;
}
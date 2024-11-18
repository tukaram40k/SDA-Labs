struct Date{
    int day:8;
    int month:8;
    int year:24;
};

union Info{
    int number;
    char string[10];
    struct Date date;
};

void scan_Number(union Info arr[]){
    printf("Input account number: ");
    scanf("%d", &arr[0].number);
    getchar();
}

void scan_Name(union Info arr[]){
    printf("Input the name: ");
    fgets(arr[1].string, 10, stdin);
    arr[1].string[strcspn(arr[1].string, "\n")] = '\0';
}

void scan_Surname(union Info arr[]){
    printf("Input the surname: ");
    fgets(arr[2].string, 10, stdin);
    arr[2].string[strcspn(arr[2].string, "\n")] = '\0';
}

void scan_Type(union Info arr[]){
    printf("Input account type: ");
    fgets(arr[3].string, 10, stdin);
    arr[3].string[strcspn(arr[3].string, "\n")] = '\0';
}

void scan_Opening_date(union Info arr[]){
    int day_input=0, month_input=0, year_input=0;
    printf("Input opening date:\n");
    printf("Input day: ");
    scanf("%d", &day_input);
    printf("Input month: ");
    scanf("%d", &month_input);
    printf("Input year: ");
    scanf("%d", &year_input);
    arr[4].date.day=day_input;
    arr[4].date.month=month_input;
    arr[4].date.year=year_input;
    getchar();
}

void scan_Balance(union Info arr[]){
    printf("Input opening balance: ");
    scanf("%d", &arr[5].number);
    getchar();
}

void scan_Last_access_date(union Info arr[]){
    int day_input=0, month_input=0, year_input=0;
    printf("Input last access date:\n");
    printf("Input day: ");
    scanf("%d", &day_input);
    printf("Input month: ");
    scanf("%d", &month_input);
    printf("Input year: ");
    scanf("%d", &year_input);
    arr[6].date.day=day_input;
    arr[6].date.month=month_input;
    arr[6].date.year=year_input;
    getchar();
}

void Compare_date(union Info arr1[], union Info arr2[], union Info arr3[], bool ascending, int days[], int months[], int years[]){
    if (ascending){
        printf("%s, %s, %s\n", arr3[1].string, arr1[1].string, arr2[1].string);
    }
    else{
        printf("%s, %s, %s\n", arr2[1].string, arr1[1].string, arr3[1].string);
    }
}

void Merge(int arr[], int left, int middle, int right, bool ascending){
    int i, j, k;
    int size1=middle-left+1;
    int size2=right-middle;
    int left_arr[size1], right_arr[size2];
    for (i=0; i<size1; i++){
        left_arr[i]=arr[left+i];
    }
    for (j=0; j<size2; j++){
        right_arr[j]=arr[middle+1+j];
    }
    i=0;
    j=0;
    k=left;
    while (i<size1 && j<size2){
        if (ascending){
            if (left_arr[i] <= right_arr[j]){
                arr[k]=left_arr[i];
                i++;
            } 
            else{
                arr[k]=right_arr[j];
                j++;
            }
            k++;
        }
        else{
            if (left_arr[i] >= right_arr[j]){
                arr[k]=left_arr[i];
                i++;
            } 
            else{
                arr[k]=right_arr[j];
                j++;
            }
            k++;
        }
    }
    while (i<size1){
        arr[k]=left_arr[i];
        i++;
        k++;
    }
    while (j<size2){
        arr[k]=right_arr[j];
        j++;
        k++;
    }
}

void Merge_sort(int arr[], int left, int right, bool ascending){
    if (left<right){
        int middle=(left+right)/2;
        Merge_sort(arr, left, middle, ascending);
        Merge_sort(arr, middle+1, right, ascending);
        Merge(arr, left, middle, right, ascending);
    }
}

void print_Info(union Info arr[]){
    printf("\nAccount number: %d\n", arr[0].number);
    printf("Name: %s\n", arr[1].string);
    printf("Surname: %s\n", arr[2].string);
    printf("Account type: %s\n", arr[3].string);
    printf("Opening date: %d.%d.%d\n", arr[4].date.day, arr[4].date.month, arr[4].date.year);
    printf("Opening balance: %d\n", arr[5].number);
    printf("Last access date: %d.%d.%d\n\n", arr[6].date.day, arr[6].date.month, arr[6].date.year);
}

void modify_Field(union Info arr[], int field_num){
    getchar();
    switch (field_num){
        case 1: scan_Number(arr);
            break;
        case 2: scan_Name(arr);
            break;
        case 3: scan_Surname(arr);
            break;
        case 4: scan_Type(arr);
            break;
        case 5: scan_Opening_date(arr);
            break;
        case 6: scan_Balance(arr);
            break;
        case 7: scan_Last_access_date(arr);
            break;
    }
}

int Partition(int arr[], int left_index, int right_index, bool ascending){
    int pivot=arr[right_index];
    int i=left_index-1;
    for (int j=left_index; j<=right_index-1; j++){
        if ((ascending && arr[j]<pivot) || (!ascending && arr[j]>pivot)){
            i++;
            int temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }
    }
    int temp=arr[i+1];
    arr[i+1]=arr[right_index];
    arr[right_index]=temp;
    return (i+1);
}

void Quicksort(int arr[], int left_index, int right_index, bool ascending){
    if (left_index<right_index){
        int pivot=Partition(arr, left_index, right_index, ascending);
        Quicksort(arr, left_index, pivot-1, ascending);
        Quicksort(arr, pivot+1, right_index, ascending);
    }
}

void sort_Data(union Info arr1[], union Info arr2[], union Info arr3[]){
    int days[3];
    int months[3];
    int years[4];
    days[0]=arr1[4].date.day;
    days[1]=arr2[4].date.day;
    days[2]=arr3[4].date.day;
    months[0]=arr1[4].date.month;
    months[1]=arr2[4].date.month;
    months[2]=arr3[4].date.month;
    years[0]=arr1[4].date.year;
    years[1]=arr2[4].date.year;
    years[2]=arr3[4].date.year;
    printf("\nSorted by opening date in ascending order:\n");
    Quicksort(days, 0, 2, true);
    Quicksort(months, 0, 2, true);
    Quicksort(years, 0, 2, true);
    Compare_date(arr1, arr2, arr3, true, days, months, years);
    printf("\nSorted by opening date in descending order:\n");
    Merge_sort(days, 0, 2, false);
    Merge_sort(months, 0, 2, false);
    Merge_sort(years, 0, 2, false);
    Compare_date(arr1, arr2, arr3, false, days, months, years);
}

void modify_Data(union Info arr[]){
    int num=0;
    printf("\nInput the number of criteria for modification: ");
    scanf("%d", &num);
    int *criteria=(int*)malloc(num*sizeof(int));
    printf("Select the criteria:\n");
    printf("1. Account number\n2. Name\n3. Surname\n4. Account type\n5. Opening date\n6. Opening balance\n7. Last access\n");
    for (int i=0; i<num; i++){
        scanf("%d", &criteria[i]);
    }
    getchar();
    for (int i=0; i<num; i++){
        int day=0, month=0, year=0;
        int int_input=0;
        char str_input[50];
        switch (criteria[i]){
            case 1:
                printf("Input account number: ");
                scanf("%d", &int_input);
                getchar();
                if (int_input!=arr[0].number){
                    printf("\nIncorrect input. No changes were made.");
                    free(criteria);
                    return;
                }
                break;
            case 2:
                printf("Input the name: ");
                fgets(str_input, 50, stdin);
                str_input[strcspn(str_input, "\n")] = '\0';
                if (strcmp(str_input, arr[1].string)!=0){
                    printf("\nIncorrect input. No changes were made.");
                    free(criteria);
                    return;
                }
                break;
            case 3:
                printf("Input the surname: ");
                fgets(str_input, 50, stdin);
                str_input[strcspn(str_input, "\n")] = '\0';
                if (strcmp(str_input, arr[2].string)!=0){
                    printf("\nIncorrect input. No changes were made.");
                    free(criteria);
                    return;
                }
                break;
            case 4:
                printf("Input account type: ");
                fgets(str_input, 50, stdin);
                str_input[strcspn(str_input, "\n")] = '\0';
                if (strcmp(str_input, arr[3].string)!=0){
                    printf("\nIncorrect input. No changes were made.");
                    free(criteria);
                    return;
                }
                break;
            case 5:
                printf("Input the opening date:\n");
                day=0; 
                month=0; 
                year=0;
                printf("Input day: ");
                scanf("%d", &day);
                printf("Input month: ");
                scanf("%d", &month);
                printf("Input year: ");
                scanf("%d", &year);
                if ((arr[4].date.day!=day)||(arr[4].date.month!=month)||(arr[4].date.year!=year)){
                    printf("\nIncorrect input. No changes were made.");
                    free(criteria);
                    return;
                }
                break;
            case 6:
                printf("Input opening balance: ");
                scanf("%d", &int_input);
                getchar();
                if (int_input!=arr[5].number){
                    printf("\nIncorrect input. No changes were made.");
                    free(criteria);
                    return;
                }
                break;
            case 7:
                printf("Input last access date: ");
                day=0; 
                month=0; 
                year=0;
                printf("Input day: ");
                scanf("%d", &day);
                printf("Input month: ");
                scanf("%d", &month);
                printf("Input year: ");
                scanf("%d", &year);
                if ((arr[6].date.day!=day)||(arr[6].date.month!=month)||(arr[6].date.year!=year)){
                    printf("\nIncorrect input. No changes were made.");
                    free(criteria);
                    return;
                }
                break;
        }
    }    
    printf("Select the field to modify:\n");
    printf("1. Account number\n2. Name\n3. Surname\n4. Account type\n5. Opening date\n6. Opening balance\n7. Last access\n");
    int field;
    scanf("%d", &field);
    modify_Field(arr, field);
    printf("Modified data:\n");
    print_Info(arr);
    free(criteria);
}

void Get_data(union Info arr[], int num){
    if (num==1){
        arr[0].number=45;
        strcpy(arr[1].string, "Mihail");
        strcpy(arr[2].string, "Petrov");
        strcpy(arr[3].string, "type 1");
        arr[4].date.day=5;
        arr[4].date.month=7;
        arr[4].date.year=1998;
        arr[5].number=5000;
        arr[6].date.day=24;
        arr[6].date.month=11;
        arr[6].date.year=2023;
    }
    else{
        arr[0].number=52;
        strcpy(arr[1].string, "Alex");
        strcpy(arr[2].string, "Parker");
        strcpy(arr[3].string, "type 2");
        arr[4].date.day=24;
        arr[4].date.month=3;
        arr[4].date.year=2020;
        arr[5].number=1000;
        arr[6].date.day=8;
        arr[6].date.month=6;
        arr[6].date.year=2021;
    }
    print_Info(arr);
}
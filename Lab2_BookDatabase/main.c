#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
    char title[255];
    char author_name[50];
    char ISBN[10];
    int pages;
    int year_published;
    }book_struct;

void parse_file(char filename[],book_struct books[]){
    FILE *fp;
   char data[360];
   int i = 0; int j = 0;
   fp = fopen(filename, "r");
   fscanf(fp, "%[^\n]", data);
   while (!feof(fp)){
        for(char *p = strtok(data,","); p!=NULL; p = strtok(NULL, ",")){
        switch(j){
            case 0:
                strcpy(books[i].title,p);
                //printf("TITLE: %s\n", books[i].title,p);
                j=1;
                break;
            case 1:
                strcpy(books[i].author_name,p);
                //printf("AUTHOR: %s\n", books[i].author_name);
                j=2;
                break;

            case 2:
                strcpy(books[i].ISBN,p);
                //printf("ISBN: %s\n", books[i].ISBN);
                j=3;
                break;

            case 3:
                books[i].pages = atoi(p);
                //printf("PAGES: %d\n", books[i].pages);
                j=4;
                break;

            case 4:
                books[i].year_published = atoi(p);
                //printf("YEAR: %d\n", books[i].year_published);
                j = 0;
                break;

        }}
        fscanf(fp, " %[^\n]", data);
        i++;
   }
   fclose(fp);//closes the text document
}

void print_book(book_struct book){
    printf("\nTitle:%s \nAuthor Name: %s\nISBN: %s\n", book.title, book.author_name, book.ISBN);
    if(book.pages == 0){
        printf("Pages: N/A");
    }else{
    printf("Pages: %d\n");
    }
    if(book.year_published == 0){
        printf("Year Published: N/A");
    }else{
    printf("Year Published: %d\n", book.year_published);
    }
}

void search_title(book_struct book[], int size, char title[]){
    int j = 0;
    for(int i=0; i<size; i++){
        if(strcmp(book[i].title, title) == 0){
            print_book(book[i]);
            j=1;
    }
    }
    if(j==0){
        printf("\nNo Results\n");
    }
}



void search_author(book_struct book[], int size, char author[]){
    int j = 0;
    for(int i=0; i<size; i++){
        if(strcmp(book[i].author_name, author) == 0){
            print_book(book[i]);
            j = 1;
    }
    }
    if(j==0){
        printf("\nNo Results\n");
    }
}
void search_ISBN(book_struct book[], int size, char ISBN[]){
    int j = 0;
    for(int i=0; i<size; i++){
        if(strcmp(book[i].ISBN, ISBN) == 0){
            print_book(book[i]);
            j=1;
    }
    }
    if(j==0){
        printf("\nNo Results\n");
    }
}

int isNumber(char input[]){
    int rtn =1;
    int length = strlen(input);
    for (int i=0;i<length;i++){
        if (!isdigit(input[i])){
            rtn = 0;
            break;
        }
    }
    if(atoi(input) == 1 || atoi(input) == 2 || atoi(input) == 3){
        rtn = 1;
    }
    return rtn;
}

int main()
{
    char title[100];
    char author[50];
    char ISBN[10];
    book_struct books[360];
    char filename[20] = "BookList.csv";
    parse_file(filename, books);
    int i = 0; int k;
    char j[20];

    while(i==0){
        printf("[0] Search by Title\n[1] Search by Author Name\n[2] Search by ISBN\n");
        scanf("%s", &j);
        if(isNumber(j) == 1){
        k = atoi(j);
        switch (k){
        case 0:
            printf("Enter a Title: ");
            fflush(stdin);
            gets(title);
            search_title(books, 360, title);
            break;

        case 1:
            printf("Enter an Author: ");
            fflush(stdin);
            gets(author);
            search_author(books, 360, author);
            break;

        case 2:
            printf("Enter an ISBN: ");
            fflush(stdin);
            gets(ISBN);
            search_ISBN(books, 360, ISBN);
            break;

    }
    }else{
    printf("Please enter 1, 2, or 3");
    }
    printf("\n");
    }

    return 0;
}

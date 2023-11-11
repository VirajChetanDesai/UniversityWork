#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lex_analyzer.h"
#include "rcd.h"

struct Token tkn;
FILE *f1;

void valid();
void invalid();
void Program();
void identifier_list();
int data_type(char *lx);
void declarations();
int statement();
void statement_list();
void assign_stat();
void expn();
void eprime();
void simple_expn();
void seprime();
void term();
void tprime();
void factor();
int relop();
int addop();
int mulop();

void valid()
{
    printf("----------------SUCCESS!---------------\n");
    exit(0);
}

void invalid(struct Token *tkn){
	printf("Error at (%d %d) for lexeme |%s| \n",tkn->row,tkn->col,tkn->lexeme);
	exit(0);
}

void Program() {
    tkn = getNextToken(f1);
    if (strcmp(tkn.lexeme, "main") == 0) {
        tkn = getNextToken(f1);
        if (strcmp(tkn.lexeme, "(") == 0) {
            tkn = getNextToken(f1);
            if (strcmp(tkn.lexeme, ")") == 0) {
                tkn = getNextToken(f1);
                if (strcmp(tkn.lexeme, "{") == 0) {
                	tkn = getNextToken(f1);
                    declarations();
                    tkn = getNextToken(f1);
                    statement_list();
                    tkn = getNextToken(f1);
                    if (strcmp(tkn.lexeme, "}") == 0) {
                        tkn = getNextToken(f1);
                        return;
                    } else {
                        invalid(&tkn);
                    }
                } else {
                    invalid(&tkn);
                }
            } else {
                invalid(&tkn);
            }
        } else {
            invalid(&tkn);
        }
    } else {
        invalid(&tkn);
    }
}


void identifier_list(){
	printf("%s\n",tkn.lexeme);
	if(strcmp(tkn.type,"identifier")==0){
		tkn = getNextToken(f1);
		if(tkn.lexeme == NULL) return;
		else if(strcmp(tkn.lexeme,",")==0){
			tkn = getNextToken(f1);
			identifier_list();
		}else if(strcmp(tkn.lexeme,"[")==0){
			tkn = getNextToken(f1);
			if(strcmp(tkn.type,"number")){
				tkn = getNextToken(f1);
				if(strcmp(tkn.lexeme,"]")==0){
					tkn = getNextToken(f1);
					if(strcmp(tkn.lexeme,",")==0){
						tkn = getNextToken(f1);
						identifier_list();
					}else if(tkn.lexeme == NULL){
						return;
					}else invalid(&tkn);
				}else invalid(&tkn);
			}else invalid(&tkn);
		};
	}else invalid(&tkn);
}

int data_type(char *lx)
{
    if (strcmp(lx, "int") == 0 || strcmp(lx, "char") == 0)
        return 1;
    else
        return 0;
}

void declarations() {
	printf("%s\n",tkn.lexeme);
    if (data_type(tkn.lexeme)) {
		tkn = getNextToken(f1);
        identifier_list();
        //tkn = getNextToken(f1); 
        printf("%s\n",tkn.lexeme);
        if (strcmp(tkn.lexeme, ";") == 0){
			printf("%s\n",tkn.lexeme);
			tkn = getNextToken(f1);
            declarations();
        }
        else
            invalid(&tkn);
    }
}

int statement() {
    assign_stat();
    tkn = getNextToken(f1);
    printf("aaaa");
    if (strcmp(tkn.lexeme, ";") == 0) {
        return 1;
    } else {
        return 0;
    }
}

void statement_list() {
    if (tkn.lexeme == NULL) {
        return;
    } else {
       resetToken(f1);
        if(!statement()) return;
        tkn = getNextToken(f1);
        statement_list();
    }
}

void assign_stat() {
    if (strcmp(tkn.type, "identifier") == 0) {
        tkn = getNextToken(f1);
        if (strcmp(tkn.lexeme, "=") == 0) {
        	tkn = getNextToken(f1);
        	printf("%s",tkn.lexeme);
            expn();
        } else {
            invalid(&tkn);
        }
    } else {
        invalid(&tkn);
    }
}

void expn(){
	simple_expn();
	tkn = getNextToken(f1);
	eprime();
}

void eprime(){
	if(tkn.lexeme == NULL){
		return;
	}else{	
		resetToken(f1);
		if(!relop()) return;
		tkn = getNextToken(f1);
		simple_expn();	
	}
}

void simple_expn(){
	term();
	tkn = getNextToken(f1);
	seprime();
}

void seprime() {
    if (tkn.lexeme == NULL) {
        return;
    } else {
        resetToken(f1);
        if(!addop()) return;
        tkn = getNextToken(f1);
        term();
        tkn = getNextToken(f1);
        seprime();
    }
}

void term(){
	factor();
	tkn = getNextToken(f1);
	tprime();
}

void tprime() {
    if (tkn.lexeme == NULL) {
        return;
    } else {
        resetToken(f1);
        if(!mulop()) return;
        tkn = getNextToken(f1);
        factor();
        tkn = getNextToken(f1);
        tprime();
    }
}

void factor() {
    if (strcmp(tkn.type, "identifier") == 0) {
        return;
    } else if (strcmp(tkn.type, "number") == 0) {
        return;
    } else {
        invalid(&tkn);
    }
}

int relop() {
    if (strcmp(tkn.lexeme, "==") == 0) {
        return 1;
    } else if (strcmp(tkn.lexeme, "!=") == 0) {
        return 1;
    } else if (strcmp(tkn.lexeme, "<=") == 0) {
        return 1;
    } else if (strcmp(tkn.lexeme, ">=") == 0) {
        return 1;
    } else if (strcmp(tkn.lexeme, ">") == 0) {
        return 1;
    } else if (strcmp(tkn.lexeme, "<") == 0) {
        return 1;
    } else {
        return 0;
    }
}


int addop() {
    if (strcmp(tkn.lexeme, "+") == 0) {
        return 1;
    } else if (strcmp(tkn.lexeme, "-") == 0) {
        return 1;
    } else {
        return 0;
    }
}


int mulop() {
    if (strcmp(tkn.lexeme, "*") == 0) {
        return 1;
    } else if (strcmp(tkn.lexeme, "/") == 0) {
        return 1;
    } else if (strcmp(tkn.lexeme, "%") == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main()
{
    f1 = fopen("sample.c", "r");
    if (f1 == NULL)
    {
        printf("Error! File cannot be opened!\n");
        return 0;
    }
    removeCommentsAndDirectives("sample.c","sample_output.txt");
    fclose(f1);
    f1 = fopen("sample_output.txt","r");
    struct sttable st[10][100];
    int flag = 0, i = 0, j = 0;
    int tabsz[10];
    char w[25];
    w[0] = '\0';
    Program();
    valid();
}
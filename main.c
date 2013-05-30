/*
 * main.c
 *
 *  Created on: 28-May-2013
 *      Author: safiyat
 */


#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *kw[]={
				"double", "int", "long", "char", "float", "short", "void",
				"enum", "typedef", "struct", "union",
				"extern", "static", "auto", "register",
				"const", "sizeof", "volatile", "signed", "unsigned",
				"continue", "goto", "return", "switch", "break",
				"while", "else", "case", "for", "default", "do",		//Leaders.
				"if"													//Statement right before a leader.
			};
int kwcount=32;

int whattype(int ch)
{
	if(isalpha(ch))
		return 2;			//Valid anywhere in the token.
	if(isdigit(ch))
		return 3;			//Valid only from the second place in the token.
	if(!isspace(ch))
	{
		if(ch=='_')
			return 2;		//Valid anywhere in the token.
		if(ch=='(')
			return 5;		//Something's beginning. Func param, or expr.
		if(ch==')')
			return 7;		//Something's Ending. Func param, or expr.
		if(ch=='{')
			return 11;		//A block, beginning.
		if(ch=='}')
			return 13;		//A block, ends.
		if(ch=='"')
			return 17;		/*Something like print.
							  Skip in whattoken if preceded immediately by a \
							  Skip anything in between, if not skipped in whattoken*/
		if(ch==';')
			return 19;		//A statement, ends.
		else
			return 23;		//Some operator.
	}
	return 0;				//White spaces be it.
}
/*
 * Return Values:
 * 			2		Is an alphabet or a '_'.
 * 			3		Is a digit.
 * 			5		Is a '('.
 * 			7		Is a ')'.
 * 			11		Is a '{'.
 * 			13		Is a '}'.
 * 			17		Is a '"'.
 *			19		Is a ';'.
 * 			23		Is a non-space special symbol.
 * 			0		Is a whitespace.
 */

int whattoken(char *token)
{
	int i, chartype, prevchartype;
	char *ptr;
	if(isdigit(token[0]))
		return 0;									//Unknown.
	if(isalpha(token[0])||token[0]=='_')
	{
		for(i=0; i<kwcount; i++)
		{
			if(strcmp(token, kw[i])==0)			//Is a keyword
			{
					if(24<i&&i<31)					//control instruction.
						return 2;					//One among for, while, do, if, break, continue.
					if(i==31)
						return 3;
				return 4;							//A keyword, but NOT a CI.
			}
		}
		ptr=token;

		while(*ptr!='\0')
		{
			i=whattype(*ptr);
			if(i!=2&&i!=3)
				return 0;							//Unidentified expr.
//			printf("while");
			ptr++;
		}

	}
	return 1;										//An identifier.
}
/*
 * Return Values:
 * 			0		Beginning with a digit. Unknown.
 * 			1		Beginning with '_' or alpha. Identifier.
 * 			2		A control instruction.
 * 			3		Instruction right before CI.
 * 			4		A keyword, but not a control instruction.
 */



int main(int argc, char *argv[])
{
		int tokenlen, i;
		char file[256], token[32], *sc, *ptr;
		long fsize;
		FILE *fp;
		if(argc<2)
        {
			__fpurge(stdin);
			printf("Enter the filename: ");
			scanf("%s", file);
        }
		else
			strcpy(file, argv[1]);
		fp=fopen(file, "rb");
		if(fp==NULL)
		{
			printf("Error opening file!!!\n");
			return 0;
		}
		fseek(fp, 0L, SEEK_END);
		fsize=ftell(fp);
		fclose(fp);
		sc=(char *)malloc(sizeof(char)*fsize);
		ptr=sc;
		fp=fopen(file, "r");
		if(fp==NULL)
		{
			printf("Error opening file!!!\n");
			return 0;
		}
		while((*ptr++=fgetc(fp))!=EOF)
			;
		fclose(fp);
		ptr=sc;
/*
		printf("\nYour file:\n");
		while(*ptr!=EOF)
			printf("%c", *ptr++);
*/
//		chartype=1;
//		prevchartype=-1;
/*
		while(*ptr!=EOF)
		{
			if(whattype(*ptr)==2||whattype(*ptr)==3)
			{
				token[i++]=*ptr;
				ptr++;
			}
			else if(whattype(*ptr)==5)
			{
				parenthesis++;
				ptr++;
				while(parenthesis!=0)
				{
					if(whattype(*ptr)==5)
						parenthesis++;
					if(whattype(*ptr)==7)
						parenthesis--;
					ptr++;
				}
			}

		}
*
		while(*ptr!=EOF)
		{
			i=0;
			if(whattype(*ptr)==2)
			{
				token[i++]=*ptr++;
				while(whattype(*ptr)==2||whattype(*ptr)==3)
				{
					token[i++]=*ptr++;
				}
				token[i]='\0';
				printf("\n\nValid token: %s\n", token);
			}
			i=0;
			if(whattype(*ptr)!=2)
			{
				while(whattype(*ptr)!=19&&whattype(*ptr)!=0&&whattype(*ptr)!=5&&whattype(*ptr)!=7)
				{
					if(i==31)
					{
						token[i]='\0';
//						printf("\nInvalid token: %s", token);
						i=0;
					}
					token[i++]=*ptr;
					ptr++;
				}
				ptr++;
				token[i]='\0';
//				printf("\nInvalid token: %s", token);
			}
		}
*/
		strcpy(sc, "if this is so then do this");
		ptr=sc;
		while(*ptr!='\0')
		{
			i=0;
                        if(whattype(*ptr)==2)
                        {
                                token[i++]=*ptr++;
                                while((whattype(*ptr)==2||whattype(*ptr)==3)&&(*ptr!='\0'))
                                {
                                        token[i++]=*ptr++;
                                }
                                token[i]='\0';
                                printf("\n\nValid token: %s, of type %d\n", token, whattoken(token));
                        }
                        i=0;
                        if(whattype(*ptr)!=2)
                        {
                                while(whattype(*ptr)!=19&&whattype(*ptr)!=0&&whattype(*ptr)!=5&&whattype(*ptr)!=7&&(*ptr!='\0'))
                                        ptr++;
			}
			if(whattype(*ptr)!=2&&(*ptr!='\0'))
				ptr++;
		}
		return 0;
}

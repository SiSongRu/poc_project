#include "MathForm.h"

using namespace std;
int Lexical_Analysis(FILE *fp, FILE *fp_output);
void Grammar_Analysis();
int main()
{
    FILE *fp, *fp_output;
    if((fp=fopen("C:\\Users\\rusis\\Documents\\code\\PrincipalOfComplier\\test_file\\test05.txt","r"))==NULL)
    {
        printf("can't find the file!");
        exit(0);
    }
    if((fp_output=fopen("C:\\Users\\rusis\\Documents\\code\\PrincipalOfComplier\\test_file\\test05_output.txt","a"))==NULL)
    {
        printf("can't find the file!");
        exit(0);
    }
    Lexical_Analysis(fp, fp_output);
    fclose(fp);
    fclose(fp_output);
    Grammar_Analysis();

    return 0;
}

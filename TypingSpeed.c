///Typing Speed in terms of words per minute(WPM) and Accuracy

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main()
{
    const int PARAGRAPH_NUMBER = 10;
    const int TIME_LIMIT = 15000;

    int i, j;
    int randomParagraph;
    int errorCount = 0, errorCountTotal = 0;
    int inputWordErrorCount = 0, inputWordCount = 0;
    int sourceWordCount = 0, sourceLength = 0;
    int paragraphCount = 0;
    int charCount = 0;
    int inputLength = 0;
    int netLength = 0;

    static char ch, sourceStr[100][20], inputStr[100][20];
    float accuracy, grossWPM, netWPM;
    time_t start, diff;

    //Random seed
    srand(time(NULL));

    //Open source file in read mode
    FILE *source = fopen("source.txt", "r");

    //Print error if source file is not present
    if (source == NULL)
    {
        printf ("Error");
        return -1;
    }

    printf ("\n");

    //Select a random paragraph
    randomParagraph = rand()%PARAGRAPH_NUMBER;
    do
    {
        fseek(source, 0, SEEK_CUR);
        if ((ch = fgetc(source)) == '\n')
        {
            fseek(source, 3, SEEK_CUR);
            paragraphCount++;
        }
    }while(paragraphCount < randomParagraph);

    fseek(source, -1, SEEK_CUR);

    //Get text from file and put in array
    for (i=0 ; (ch = fgetc(source)) != '\n'  && ch != EOF; i++)
    {
        //Divide string into words
        for (j=0 ; ch != ' ' && ch != '\n' && ch != EOF; j++)
        {
            sourceStr[i][j] = ch;
            printf ("%c", ch);
            ch = fgetc(source);
        }
        printf (" ");
        sourceWordCount++;
    }
    fclose(source);

    //Instructions
    printf ("\n\nINSTRUCTIONS:\n");
    printf ("Type the given text.\n");
    printf ("Type quickly and accurately for 15 seconds.\n");
    printf ("Press Enter when you are ready and start typing.\n");

    //Wait for a key before starting the timer
    ch = getchar();
    start = clock();

    //Count no. of milliseconds after start of timer
    diff = clock() - start;

    //Get input string for 15 seconds
    i=0;
    while (diff < TIME_LIMIT)
    {
        ch = _getch();
        if (isalpha(ch))
        {
            //Divide string into words
            j=0;
            while (ch != ' ')
            {
                //Fix backspace and other unprintable characters
                if (isalpha(ch))
                {
                    printf ("%c", ch);
                    inputStr[i][j] = ch;
                    j++;
                }
                else
                {
                    //Only backspace the current word
                    if (j>0)
                    {
                        printf ("\b \b");
                        j--;
                    }
                }

                //Get another character
                ch = _getch();

                //Calculate time difference
                diff = clock() - start;
            }

            i++;
            printf (" ");
            inputWordCount++;
        }
    }

    printf ("\n\nTime Up!\n");

    //Check for errors
    for (i=0; i<inputWordCount ; i++)
    {
        errorCount = 0;
        for (j=0; j < ((strlen(sourceStr[i]) > strlen(inputstr[i]))? strlen(sourceStr[i]) : strlen(inputstr[i])); j++)
        {
            //Count total no. of characters
            charCount++;
            if(sourceStr[i][j] != inputstr[i][j])
            {
                //Count no. of mistyped characters
                errorCount = 1;
                errorCountTotal++;
            }
        }

        //Count no. of mistyped words
        if (errorCount == 1)
            inputWordErrorCount++;
    }

    //Display results
    printf ("\n\nRESULTS:");

    //Calculate word accuracy
    accuracy = (float)inputWordErrorCount/inputWordCount;
    printf("\n\n%.2f\% Word Accuracy", 100*(1-accuracy));

    //Calculate character accuracy
    accuracy = (float)errorCountTotal/charCount;
    printf("\n%.2f\% Character Accuracy", 100*(1-accuracy));

    //Calculate Gross WPM
    grossWPM = (float)charCount/5;
    printf ("\n%.2f Gross WPM", grossWPM*(60000/timelen));

    //Calculate Net WPM
    netLength = charCount - errorCountTotal;
    netWPM = (float)netLength/5;
    printf ("\n%.2f Net WPM", netWPM*(60000/timelen));

    //Miscellaneous info
    printf ("\n\nMISC:");
    printf ("\n%d Character mistyped", errorCountTotal);
    printf ("\n%d Characters typed", charCount);
    printf ("\n%d Words mistyped", inputWordErrorCount);
    printf ("\n%d Words typed", inputWordCount);

    delay(60000);
    return 0;
}


#include <time.h> //Calculate the time
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ictclas.h"
#include "Utility/Utility.h"

ICTCLAS::ICTCLAS()
{
    m_nTime=0;
    m_nResultNum=1;
    m_ICTCLAS.m_nOutputFormat=0;
    m_ICTCLAS.m_nOperateType=2;
    m_sScore = 0;
    m_bDisable=true;
    m_sResult = NULL;
    m_sSource = NULL;
    if(!IsDataExists())
    {
        m_sResult="错误：Data文件夹不存在或者缺少数据文件！";
    } 
}

ICTCLAS::~ICTCLAS()
{
    if (m_sResult != NULL)
        delete[] m_sResult;
    if (m_sSource != NULL)
        delete[] m_sSource;
    m_sResult = NULL;
    m_sSource = NULL;
}

void ICTCLAS::SetSource(char* sSource)
{
    if (sSource == NULL)
    {
        return;
    }
    if (m_sSource != NULL)
    {
        delete [] m_sSource;
        m_sSource = NULL;
    }
    // m_sSource = new char[strlen(sSource)+1];
    m_sSource = new char[40*1024];
    strcpy(m_sSource, sSource);
    if (m_sResult != NULL)
    {
        delete [] m_sResult;
        m_sResult = NULL;
    }
}

void ICTCLAS::Run(char* sSource)
{
    if (sSource == NULL)
        return;
    if (!CheckGB2312(sSource))
    {
        if (m_sResult != NULL)
            delete [] m_sResult;
        m_sResult = "";
        return;
    }
    clock_t start, finish;
    if (m_sResult != NULL)
    {
        delete [] m_sResult;
        m_sResult = NULL;
    }
    if(m_ICTCLAS.m_nOutputFormat!=2)
        m_sResult=new char [(strlen(sSource)+13)*5];
    else
        m_sResult=new char [(strlen(sSource)+13)*50];
    if(m_nResultNum==1)
    {
        start=clock();
        if(!m_ICTCLAS.ParagraphProcessing(sSource,m_sResult))
        {
            delete[] m_sResult;
            m_sResult = "错误：程序初始化异常！";
        }
        finish=clock();
        m_nTime=1000*(finish-start)/CLOCKS_PER_SEC;
        m_sScore = m_ICTCLAS.m_dResultPossibility[0];
    }

}

void ICTCLAS::OpenFile(char* sSourceFile)
{
    char sResultFile[100];
    clock_t start, finish;
    strcpy(sResultFile,sSourceFile);//Set the result file name and path
    unsigned int nLen=strlen(sSourceFile);
    strncpy(sResultFile+nLen-4,"_cla.txt",10);//Change the extension
    sResultFile[nLen+4]=0;
    start=clock();
    if(!m_ICTCLAS.FileProcessing(sSourceFile,sResultFile))
        m_sResult = "错误：程序初始化异常！";
    else
    {
        finish=clock();
        m_nTime=1000*(finish-start)/CLOCKS_PER_SEC;
        m_sResult = new char[100];
        sprintf(m_sResult, "%s => %s", sSourceFile, sResultFile);
    }
}

void ICTCLAS::ShowResult()
{
    printf("%s: %dms\n", m_sResult, m_nTime);
}

bool ICTCLAS::IsDataExists()
{
    m_bDisable=false;
    return true;
}

bool ICTCLAS::CheckGB2312(const char *s)
{
    const unsigned char* u_s = (const unsigned char*) s;
    int nLen = strlen(s);

    if (nLen == 0)
        /* Incomplete multibyte sequence */
        return false;

    int i = 0;
    while (i < nLen - 1) 
    {
        if (s[i] >= 0) 
        {
            i++;
        }
        else 
        {
            if (u_s[i] >= 0xa1 && u_s[i] <= 0xfe
                    && u_s[i] >= 0xa1 && u_s[i] <= 0xfe)
            {
                return false;
            }
            else
                return false;
        }
    }
    return true;
}

int main(int argc, char* argv[])
{ 
    char* fileName = "test/test.txt";
    int nTimes = 1;
    int nTimeSum = 0;
    clock_t start = clock(), finish;
    if (argc > 1)
    { 
        fileName = argv[1];
        if (argc > 2)
        {
            nTimes = atoi(argv[2]);
            if (nTimes < 1) {
                nTimes = 1;
            }
        }
    }
    ICTCLAS clas;
    for (int i=0; i<nTimes; i++) {
        clas.OpenFile(fileName);
        // clas.Run("恩................................");
        // clas.ShowResult();
        nTimeSum += clas.getTime();
    }

    finish=clock();
    int nTime = 1000*(finish-start)/CLOCKS_PER_SEC;
    printf("Average Time: %d/%d = %dms\n",
            nTimeSum, nTimes, nTimeSum/nTimes); 
    printf("Total time: %dms\n", nTime);

    return 0; 
}


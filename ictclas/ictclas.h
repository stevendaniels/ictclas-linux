#ifndef ICTCLAS_H
#define ICTCLAS_H

#include "Result/Result.h"

class ICTCLAS
{
public: 


    ICTCLAS();
    ~ICTCLAS();

    void Run(char* sSource);
    void OpenFile(char* sSourceFile);
    // char* ProcessParagraph(char* sSource);
    void ShowResult();

    char* GetResult()
    { return m_sResult; }

    void SetSource(char* sSource);

    void SetOutputFormat(int nOutputFormat)
    { m_ICTCLAS.m_nOutputFormat = nOutputFormat; }

    void SetOperateType(int nOperateType)
    { m_ICTCLAS.m_nOperateType = nOperateType; }
    
    unsigned int getTime()
    { return m_nTime; }

// Implementation
protected:
    bool IsDataExists();
	bool CheckGB2312(const char* str);

	CResult m_ICTCLAS;
	unsigned int	m_nTime;
	unsigned int	m_nResultNum;
	double	m_sScore;
	bool    m_bDisable;
	char*	m_sResult;
	char*	m_sSource;
};

#endif // ifndef ICTCLAS_H

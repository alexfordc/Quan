/*******************************************************************************
* (C) Copyright 2011 
* 
* These computer program listings and specifications are the property of Jerry 
* Lee and shall not be reproduced or copied or used in whole or in 
* part without written permission from Jerry Lee.
*
* Project:      IAdvertising 
* File Name:	FileInterface.h 
* Programer(s):	Jerry Lee 
* Created:      20110104 
* Description:	�����ļ������Ľӿ�
* History:
*******************************************************************************/

#ifndef _FILE_INTERFACE_H
#define _FILE_INTERFACE_H

// ��ȡ�ļ��ӿ�
template<typename T>
class FileReader
{
public:
    void Read(T &value) = 0;
protected:
private:
};


// д���ļ��ӿ�
template<typename T>
class FileWriter
{
public:
    void Write(T &value) = 0;
protected:
private:
};

#endif // _FILE_INTERFACE_H
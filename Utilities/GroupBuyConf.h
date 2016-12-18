
#ifndef _GROUPBUY_CONF_H
#define _GROUPBUY_CONF_H

#include "GroupBuyDef.h"

// �Ź���Ϣ��վ
typedef struct tagGroupBuySite
{
    string name;      // ��վ����
    string cityUrl;   // ��ȡ������Ϣ��url
    string productUrl;// ��ȡ��Ʒ��Ϣ��url
    string decodeDll; // ������̬��
    string filename;  // �������ļ���
} GroupBuySite;


// �����Ź���վ�б�
typedef vector<GroupBuySite> VT_GROUPBYSITE;


// �Ź���Ϣ����
typedef struct tagGroupBuyConf
{
    string downloadPath;    // ���ر���·��
    VT_GROUPBYSITE sites;   // �Ź�վ����Ϣ   
} GroupBuyConf;


// �Ź���Ϣ��ȡ��
class GroupBuyConfReader
{
public:
    virtual bool Read(const string &filename, GroupBuyConf &groupBuyConf) = 0;

};


#endif

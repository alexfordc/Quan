/*******************************************************************************
* (C) Copyright 2011 
* 
* These computer program listings and specifications are the property of Jerry 
* Lee and shall not be reproduced or copied or used in whole or in 
* part without written permission from Jerry Lee.
*
* Project:      IAdvertising 
* File Name:	GroupBuyDef.h 
* Programer(s):	Jerry Lee 
* Created:      20110104 
* Description:	RSS���ݶ��嵥Ԫ
* History:
*******************************************************************************/

#ifndef _GROUP_BUY_H
#define _GROUP_BUY_H

#include <vector>
#include <string>

using namespace std;

#ifndef XML_HEADER
#define XML_HEADER       "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\r"
#endif

// �Ź�������Ϣ
typedef struct tagCityInfo
{
    string id;
    string name;
} CityInfo;


// �Ź������б�
typedef struct tagCities
{
    vector<CityInfo> items;
} Cities;


// �Ź���Ϣ
typedef struct tagGroupBuyInfo
{
    string name;
    string title;
    int price;
    int time;
    string url;
    string imageUrl;
    string category;
    string description;
    string cityId;
    string cityName;
} GroupBuyInfo;


// �Ź���Ϣ�б�
typedef vector<GroupBuyInfo> VT_GROUPBUYINFO;

typedef struct tagGroupBuyFeed
{
    int version;
    CityInfo cityInfo;
    VT_GROUPBUYINFO items;
} GroupBuyFeed;


// GroupBuy Feed��ȡ���ӿ�
class GroupBuyFeedReader
{
public:
    virtual bool Read(const string &filename, GroupBuyFeed &feed) = 0;

protected:
    virtual void ReadItem(GroupBuyInfo &item) = 0;
};


// GroupBuy Feedд�����ӿ�
class GroupBuyFeedWriter
{
public:
    virtual bool Write(const string &filename, const GroupBuyFeed &feed) = 0;

protected:
    virtual void WriteItem(const GroupBuyInfo &item) = 0;
};


#endif // _GROUP_BUY_H

/*******************************************************************************
* (C) Copyright 2011 
* 
* These computer program listings and specifications are the property of Jerry 
* Lee and shall not be reproduced or copied or used in whole or in 
* part without written permission from Jerry Lee.
*
* Project:      IAdvertising 
* File Name:	RSSFeedDef.h 
* Programer(s):	Jerry Lee 
* Created:      20110104 
* Description:	RSS���ݶ��嵥Ԫ
* History:
*******************************************************************************/

#ifndef _RSS_FEED_DEF_H
#define _RSS_FEED_DEF_H

#include <vector>
#include <string>

using namespace std;


// RSS Header
#define RSS_HEADER          ("rss") // RSSͷ 

#define RSS_CHANNEL         ("channel") // channel

#define RSS_ITEM            ("item")  // item

// RSS Channel definition
#define CHAN_LANGUAGE       ("language") // Ƶ��ʹ�õ��������࣬����en-us������������zh-cn��������ۼ�����֯
                                            // ͬһ���Ե�վ�㡣 ������ʹW3CԤ�����ֵ
#define CHAN_COPYRIGHT      ("copyright")       // Ƶ�����ݵİ�Ȩ����
#define CHAN_MEDITOR        ("managingEditor") // �Ը�Ƶ�����ݸ���ĸ��˵�Email ��ַ
#define CHAN_WEBMASTER      ("webMaster") // �Ը�Ƶ���ļ���֧�ָ���ĸ��˵�Email ��ַ
#define CHAN_PUBDATE        ("pubDate")   // ��Ƶ�����ݵĹ������ڡ����磬һ������ŦԼʱ�䰴�ո��µ�Ƶ��ÿ24 С
                                             // ʱ�������ھ͹���һ�Ρ�����Ƶ����pubDate���ĵ�ʱ�䡣����RSS ��ʹ
                                             // �õ�����ʱ������RFC 822 �淶����ݿ�������λ������λ����ѡ��λ��
#define CHAN_LASTBUILDDATE  ("lastBuildDate") // �ϴ�Ƶ�����ݸ��ĵ�ʱ��
#define CHAN_CATEGORY       ("category")  // ˵��Ƶ��������һ���������࣬������<item>�����categoryԪ��
                                             // һ��
#define CHAN_GENERATOR      ("generator") // ˵���������ɸ�Ƶ���ĳ���
#define CHAN_DOCS           ("docs")      // RSS�ļ���ʹ�ø�ʽ��˵���ĵ����ڵ�URL��������ָ���ĵ�����������
                                             // ��������RSS�ļ���
#define CHAN_CLOUD          ("cloud")     // �������ע��Ϊ��cloud����Ƶ������ʱ֪ͨ����Ϊ RSS ��Ҫʵ����һ������
                                             // ���ķ���-����Э��
#define CHAN_TTL            ("ttl")       // ttl ������ʱ�䣬���ʱ����һ�����֣���ʾ��Ҫ��ˢ��֮ǰ����ķ�����
#define CHAN_IMAGE          ("image")     // ָ��һ������Ƶ������ʾ��GIF��JPEG ��PNG ͼ��
#define CHAN_RATING         ("rating")    // ���ڸ�Ƶ���� PICS ����
#define CHAN_TEXTINPUT      ("textInput") // �������Ƶ��һ����ʾ�������
#define CHAN_SKIPHOURS      ("skipHours") // ���߾ۼ�����ЩСʱ�ĸ��¿��Ժ���
#define CHAN_SKIPDAYS       ("skipDays")  // ���߾ۼ�����һ��ĸ��¿��Ժ���

// RSS Item definition
#define ITEM_TITLE          ("title")       // �item���ı���
#define ITEM_LINK           ("link")        // �item����URL
#define ITEM_DESC           ("description") // �item���Ĵ��
#define ITEM_AUTHOR         ("author")      // �item�����ߵ�Email ��ַ
#define ITEM_CATEGORY       ("category")    // �����item����һ����������
#define ITEM_COMMENTS       ("comments")    // �����item����ע��ҳ��URL
#define ITEM_ENCLOSURE      ("enclosure")   // ֧�ֺ͸��item���йص�ý�����
#define ITEM_GUID           ("guid")        // Ψһ����item����ϵ��һ�������������
#define ITEM_PUBDATE        ("pubDate")     // ���item����ʲôʱ�򷢲���
#define ITEM_SOURCE         ("source")      // ���item�������ĸ�RSS Ƶ���������item���ۺ���һ��ʱ�ǳ�����

// RSS Attribute name
#define ATTIBUTE_URL        ("url")      
#define ATTIBUTE_LEGNTH     ("length")
#define ATTIBUTE_TYPE       ("type")
//

// below are standard MIME types
//��չ��    ����/������                 IIS 4.0     IIS 5.0 
// *        application/octet-stream    ��          �� 
// 323      text/h323                   ��          �� 
// acx      application/internet-property-stream �� �� 
// ai       application/postscript �� �� 
// aif      audio/x-aiff �� �� 
// aifc     audio/x-aiff �� �� 
// aiff     audio/x-aiff �� �� 
// asf      video/x-ms-asf �� �� 
// asr      video/x-ms-asf �� �� 
// asx      video/x-ms-asf �� �� 
// au       audio/basic �� �� 
// avi      video/x-msvideo �� �� 
// axs      application/olescript �� �� 
// bas      text/plain �� �� 
// bcpio    application/x-bcpio �� �� 
// bin      application/octet-stream �� �� 
// bmp      image/bmp �� �� 
// c        text/plain �� �� 
// cat      application/vnd.ms-pkiseccat �� �� 
// cdf      application/x-cdf �� �� 
// cer      application/x-x509-ca-cert �� �� 
// class    application/octet-stream �� �� 
// clp      application/x-msclip �� �� 
// cmx      image/x-cmx �� �� 
// cod      image/cis-cod �� �� 
// cpio     application/x-cpio �� �� 
// crd      application/x-mscardfile �� �� 
// crl      application/pkix-crl �� �� 
// crt      application/x-x509-ca-cert �� �� 
// csh      application/x-csh �� �� 
// css      text/css �� �� 
// dcr      application/x-director �� �� 
// der      application/x-x509-ca-cert �� �� 
// dir      application/x-director �� �� 
// dll      application/x-msdownload �� �� 
// dms      application/octet-stream �� �� 
// doc      application/msword �� �� 
// dot      application/msword �� �� 
// dvi      application/x-dvi �� �� 
// dxr      application/x-director �� �� 
// eps      application/postscript �� �� 
// etx      text/x-setext �� �� 
// evy      application/envoy �� �� 
// exe      application/octet-stream �� �� 
// fif      application/fractals �� �� 
// flr      x-world/x-vrml �� �� 
// gif      image/gif �� �� 
// gtar     application/x-gtar �� �� 
// gz       application/x-gzip �� �� 
// h        text/plain �� �� 
// hdf      application/x-hdf �� �� 
// hlp      application/winhlp �� �� 
// hqx      application/mac-binhex40 �� �� 
// hta      application/hta �� �� 
// htc      text/x-component �� �� 
// htm      text/html �� �� 
// html     text/html �� �� 
// htt      text/webviewhtml �� �� 
// ico      image/x-icon �� �� 
// ief      image/ief �� �� 
// iii      application/x-iphone �� �� 
// ins      application/x-internet-signup �� �� 
// isp      application/x-internet-signup �� �� 
// jfif     image/pipeg �� �� 
// jpe      image/jpeg �� �� 
// jpeg     image/jpeg �� �� 
// jpg      image/jpeg �� �� 
// js       application/x-javascript �� �� 
// latex    application/x-latex �� �� 
// lha      application/octet-stream �� �� 
// lsf      video/x-la-asf �� �� 
// lsx      video/x-la-asf �� �� 
// lzh      application/octet-stream �� �� 
// m13      application/x-msmediaview �� �� 
// m14      application/x-msmediaview �� �� 
// m3u      audio/x-mpegurl �� �� 
// man      application/x-troff-man �� �� 
// mdb      application/x-msaccess �� �� 
// me       application/x-troff-me �� �� 
// mht      message/rfc822 �� �� 
// mhtml    message/rfc822 �� �� 
// mid      audio/mid �� �� 
// mny      application/x-msmoney �� �� 
// mov      video/quicktime �� �� 
// movie    video/x-sgi-movie �� �� 
// mp2      video/mpeg �� �� 
// mp3      audio/mpeg �� �� 
// mpa      video/mpeg �� �� 
// mpe      video/mpeg �� �� 
// mpeg     video/mpeg �� �� 
// mpg      video/mpeg �� �� 
// mpp      application/vnd.ms-project �� �� 
// mpv2     video/mpeg �� �� 
// ms       application/x-troff-ms �� �� 
// mvb      application/x-msmediaview �� �� 
// nws      message/rfc822 �� �� 
// oda      application/oda �� �� 
// p10      application/pkcs10 �� �� 
// p12      application/x-pkcs12 �� �� 
// p7b      application/x-pkcs7-certificates �� �� 
// p7c      application/x-pkcs7-mime �� �� 
// p7m      application/x-pkcs7-mime �� �� 
// p7r      application/x-pkcs7-certreqresp �� �� 
// p7s      application/x-pkcs7-signature �� �� 
// pbm      image/x-portable-bitmap �� �� 
// pdf      application/pdf �� �� 
// pfx      application/x-pkcs12 �� �� 
// pgm      image/x-portable-graymap �� �� 
// pko      application/ynd.ms-pkipko �� �� 
// pma      application/x-perfmon �� �� 
// pmc      application/x-perfmon �� �� 
// pml      application/x-perfmon �� �� 
// pmr      application/x-perfmon �� �� 
// pmw      application/x-perfmon �� �� 
// pnm      image/x-portable-anymap �� �� 
// pot      application/vnd.ms-powerpoint �� �� 
// ppm      image/x-portable-pixmap �� �� 
// pps      application/vnd.ms-powerpoint �� �� 
// ppt      application/vnd.ms-powerpoint �� �� 
// prf      application/pics-rules �� �� 
// ps       application/postscript �� �� 
// pub      application/x-mspublisher �� �� 
// qt       video/quicktime �� �� 
// ra       audio/x-pn-realaudio �� �� 
// ram      audio/x-pn-realaudio �� �� 
// ras      image/x-cmu-raster �� �� 
// rgb      image/x-rgb �� �� 
// rmi      audio/mid �� �� 
// roff     application/x-troff �� �� 
// rtf      application/rtf �� �� 
// rtx      text/richtext �� �� 
// scd      application/x-msschedule �� �� 
// sct      text/scriptlet �� �� 
// setpay   application/set-payment-initiation �� �� 
// setreg   application/set-registration-initiation �� �� 
// sh       application/x-sh �� �� 
// shar     application/x-shar �� �� 
// sit      application/x-stuffit �� �� 
// snd      audio/basic �� �� 
// spc      application/x-pkcs7-certificates �� �� 
// spl      application/futuresplash �� �� 
// src      application/x-wais-source �� �� 
// sst      application/vnd.ms-pkicertstore �� �� 
// stl      application/vnd.ms-pkistl �� �� 
// stm      text/html �� �� 
// sv4cpio  application/x-sv4cpio �� �� 
// sv4crc   application/x-sv4crc �� �� 
// t        application/x-troff �� �� 
// tar      application/x-tar �� �� 
// tcl      application/x-tcl �� �� 
// tex      application/x-tex �� �� 
// texi     application/x-texinfo �� �� 
// texinfo  application/x-texinfo �� �� 
// tgz      application/x-compressed �� �� 
// tif      image/tiff �� �� 
// tiff     image/tiff �� �� 
// tr       application/x-troff �� �� 
// trm      application/x-msterminal �� �� 
// tsv      text/tab-separated-values �� �� 
// txt      text/plain �� �� 
// uls      text/iuls �� �� 
// ustar    application/x-ustar �� �� 
// vcf      text/x-vcard �� �� 
// vrml     x-world/x-vrml �� �� 
// wav      audio/x-wav �� �� 
// wcm      application/vnd.ms-works �� �� 
// wdb      application/vnd.ms-works �� �� 
// wks      application/vnd.ms-works �� �� 
// wmf      application/x-msmetafile �� �� 
// wps      application/vnd.ms-works �� �� 
// wri      application/x-mswrite �� �� 
// wrl      x-world/x-vrml �� �� 
// wrz      x-world/x-vrml �� �� 
// xaf      x-world/x-vrml �� �� 
// xbm      image/x-xbitmap �� �� 
// xla      application/vnd.ms-excel �� �� 
// xlc      application/vnd.ms-excel �� �� 
// xlm      application/vnd.ms-excel �� �� 
// xls      application/vnd.ms-excel �� �� 
// xlt      application/vnd.ms-excel �� �� 
// xlw      application/vnd.ms-excel �� �� 
// xof      x-world/x-vrml �� �� 
// xpm      image/x-xpixmap �� �� 
// xwd      image/x-xwindowdump �� �� 
// z        application/x-compress �� �� 
// zip      application/zip �� �� 
// evy      application/envoy �� �� 
// fif      application/fractals  �� �� 
// spl      application/futuresplash  �� �� 
// hta      application/hta �� �� 
// acx      application/internet-property-stream �� �� 
// hqx      application/mac-binhex40 �� �� 
// doc      application/msword �� �� 
// dot      application/msword �� �� 
// *        application/octet-stream �� �� 
// bin      application/octet-stream �� �� 
// class    application/octet-stream �� �� 
// dms      application/octet-stream �� �� 
// exe      application/octet-stream  �� �� 
// lha      application/octet-stream �� �� 
// lzh      application/octet-stream �� �� 
// oda      application/oda �� �� 
// axs      application/olescript �� �� 
// pdf      application/pdf �� �� 
// prf      application/pics-rules �� �� 
// p10      application/pkcs10 �� �� 
// crl      application/pkix-crl �� �� 
// ai       application/postscript �� �� 
// eps      application/postscript �� �� 
// ps       application/postscript �� �� 
// rtf      application/rtf �� �� 
// setpay   application/set-payment-initiation  �� �� 
// setreg   application/set-registration-initiation  �� �� 
// xla      application/vnd.ms-excel �� �� 
// xlc      application/vnd.ms-excel �� �� 
// xlm      application/vnd.ms-excel �� �� 
// xls      application/vnd.ms-excel  �� �� 
// xlt      application/vnd.ms-excel �� �� 
// xlw      application/vnd.ms-excel �� �� 

#define TITLE_SIZE 128
#define URL_SIZE   128
#define DATE_SIZE  32
#define DESC_SIZE  512

#ifndef XML_HEADER
#define XML_HEADER       "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\r"
#endif

#define MEDIA_FORMAT_AUDIO  ("WMA,WAV,MP1,MP2,MP3,MPA,OGG,M4A,M4B")
#define MEDIA_FORMAT_VIDEO  ("MP4,MOV,3GP,K3G,MQV,WMV,AVI,DIVX,GVI,OGM,M4V,MPEG,MPG")


// RSSƵ������Category�ṹ����
typedef struct tagRSSCategory
{
    string domain;	// Category��domain URL
    string title;	// Category������

    tagRSSCategory::tagRSSCategory()
    {
        
    }

    tagRSSCategory::tagRSSCategory(const tagRSSCategory &category)
    {
        domain = category.domain;
        title = category.title;
    }

    tagRSSCategory &tagRSSCategory::operator=(const tagRSSCategory &category)
    {
        if (this != &category)
        {
            this->domain = category.domain;
            this->title = category.title;
        }

        return *this;
    }
} RSSCategory, * PRSSCategory;


// RSSƵ������Enclosure�ṹ����
typedef struct tagRSSEnclosure
{
    unsigned long length;   // length �������ж����ֽ�
    string url;	            // һ��http URL
    string type;	        // ����������(һ����׼��MIME����)

    tagRSSEnclosure::tagRSSEnclosure()
    {

    }

    tagRSSEnclosure::tagRSSEnclosure(const tagRSSEnclosure &enclosure)
    {
        length = enclosure.length;
        url = enclosure.url;
        type = enclosure.type;
    }

    tagRSSEnclosure &tagRSSEnclosure::operator=(const tagRSSEnclosure &enclosure)
    {
        if (this != &enclosure)
        {
            length = enclosure.length;
            url = enclosure.url;
            type = enclosure.type;
        }

        return *this;
    }
} RSSEnclosure, * PRSSEnclosure;


// RSSƵ������GUID�ṹ����
typedef struct tagRSSGUID
{
    bool isPermaLink;   // �Ƿ�Ϊ�־�����
    string url;	        // guid��URL

    tagRSSGUID::tagRSSGUID()
    {

    }

    tagRSSGUID::tagRSSGUID(const tagRSSGUID &guid)
    {
        isPermaLink = guid.isPermaLink;
        url = guid.url;
    }

    tagRSSGUID &tagRSSGUID::operator=(const tagRSSGUID &guid)
    {
        if (this != &guid)
        {
            isPermaLink = guid.isPermaLink;
            url = guid.url;
        }

        return *this;
    }
} RSSGUID, * PRSSGUID;


// RSSƵ������Source�ṹ����
typedef struct tagRSSSource
{
    string url;	    // item�ı���
    string content;	// item��URL

    tagRSSSource::tagRSSSource()
    {
        
    }

    tagRSSSource::tagRSSSource(const tagRSSSource &source)
    {
        url = source.url;
        content = source.content;
    }

    tagRSSSource &tagRSSSource::operator=(const tagRSSSource &source)
    {
        if (this != &source)
        {
            url = source.url;
            content = source.content;
        }

        return *this;
    }
} RSSSource, * PRSSSource;


// RSSƵ������Image�ṹ����
typedef struct tagRSSImage
{
    string title;	// ͼƬ�ı���
    string url;	    // ͼƬ��URL
    string link;	// ͼƬ�������URL

    tagRSSImage::tagRSSImage()
    {

    }

    tagRSSImage::tagRSSImage(const tagRSSImage &image)
    {
        title = image.title;
        url = image.url;
        link = image.link;
    }

    tagRSSImage &tagRSSImage::operator=(const tagRSSImage &image)
    {
        if (this != &image)
        {
            title = image.title;
            url = image.url;
            link = image.link;
        }

        return *this;
    }
} RSSImage, * PRSSImage;


// RSSƵ������Cloud�ṹ����
typedef struct tagRSSCloud
{
    int port;		        // �õ�ַ�ṩ�Ķ˿�
    string domain;	        // ����Ƶ��֪ͨ�ĵ�ַ
    string path;	        // ��֪ͨ���ڵ�·��
    string registerProc;    // �����õĹ�����
    string protocol;	    // ʹ�õ�Э������

    tagRSSCloud::tagRSSCloud()
    {

    }

    tagRSSCloud::tagRSSCloud(const tagRSSCloud &cloud)
    {
        port = cloud.port;
        domain = cloud.domain;
        path = cloud.path;
        registerProc = cloud.registerProc;
        protocol = cloud.protocol;
    }

    tagRSSCloud &tagRSSCloud::operator=(const tagRSSCloud &cloud)
    {
        if (this != &cloud)
        {
            port = cloud.port;
            domain = cloud.domain;
            path = cloud.path;
            registerProc = cloud.registerProc;
            protocol = cloud.protocol;
        }

        return *this;
    }
} RSSCloud, * PRSSCloud;


// RSSƵ������textInput�ṹ����
typedef struct tagRSSTextInput
{
    string title;       // �����ֶεı��⣬����Submit��Search
    string description; // ��̵������ֶε���;˵��
    string name;        // �����ֶε�����
    string link;        // ���������ֶ�����ķ�����CGI�ű���URL

    tagRSSTextInput::tagRSSTextInput()
    {

    }

    tagRSSTextInput::tagRSSTextInput(const tagRSSTextInput &textInput)
    {
        title = textInput.title;
        description = textInput.description;
        name = textInput.name;
        link = textInput.link;
    }

    tagRSSTextInput &tagRSSTextInput::operator=(const tagRSSTextInput &textInput)
    {
        if (this != &textInput)
        {
            title = textInput.title;
            description = textInput.description;
            name = textInput.name;
            link = textInput.link;
        }
        
        return *this;
    }
} RSSTextInput, * PRSSTextInput;


// RSSƵ������ṹ����
typedef struct tagRSSItem
{
    string title;	        // item�ı���
    string link;	        // item��URL
    string description;	    // item���
    string author;          // �������ص����ߵ�email��ַ
    string comments;        // ������Ŀ�ĵ�ע��ҳ��URL
    RSSCategory category;   // �����������ڵķ���
    RSSEnclosure enclosure; // ֧�ֺ͸�item�йص�ý�����
    RSSGUID guid;		    // Ψһ���item��ϵ��һ�������������
    string pubDate;         // ����Ŀ������ʱ��
    RSSSource source;	    // ��item�����ĸ�RSS Ƶ��������item�ۺ���һ��ʱ�ǳ�����

    tagRSSItem::tagRSSItem()
    {

    }

    tagRSSItem::tagRSSItem(const tagRSSItem &item)
    {
        title = item.title;
        link = item.link;
        description = item.description;
        author = item.author;
        comments = item.comments;
        category = item.category;
        enclosure = item.enclosure;
        guid = item.guid;
        pubDate = item.pubDate;
        source = item.source;
    }

    tagRSSItem &tagRSSItem::operator=(const tagRSSItem &item)
    {
        if (this != &item)
        {
            title = item.title;
            link = item.link;
            description = item.description;
            author = item.author;
            comments = item.comments;
            category = item.category;
            enclosure = item.enclosure;
            guid = item.guid;
            pubDate = item.pubDate;
            source = item.source;
        }

        return *this;
    }
} RSSItem, * PRSSItem;


// RSSƵ���ṹ����
typedef vector<RSSItem> VT_RSSITEM;

typedef struct tagRSSChannel
{
    string title;               // Ƶ��������
    string link;                // ���Ƶ��������webվ�����վ�������URL
    string description;         // �Ը�Ƶ����һ�μ�Ҫ����
    string language;	        // Ƶ��ʹ�õ���������,��en-us������zh-cn,����ʹ��W3CԤ�����ֵ
    string copyright;           // Ƶ�����ݵİ�Ȩ����
    string managingEditor;      // ��Ƶ�����ݸ���ĸ��˵�Email
    string pubDate;             // ��Ƶ������������
    string lastBuildDate;       // �ϴ�Ƶ�����ݸ��µ�����
    RSSCategory category;       // ��Ƶ�������ķ��࣬��item��Ķ�����ͬ
    string generator;           // ˵���������ɸ�Ƶ���ĳ���
    string docs;	            // RSS�ļ����ø�ʽ��˵���ĵ����ڵ�URL
    RSSCloud cloud;		        // �������ע��Ϊ"cloud",Ƶ������ʱ֪ͨ��,ΪRSS��Ҫʵ����һ���������ķ���-����Э��
    int ttl;	                // ttl ������ʱ�䣬���ʱ����һ�����֣���ʾ��Ҫ��ˢ��֮ǰ����ķ�����
    RSSImage image;		        // ָ��һ������Ƶ������ʾ��GIF,JPEG ��PNG ͼ��
    int rating;		            // ���ڸ�Ƶ���� PICS ����
    RSSTextInput textInput;	    // �������Ƶ��һ����ʾ�������
    int skipHours;	            // ���߾ۼ�����ЩСʱ�ĸ��¿��Ժ���
    int skipDays;		        // ���߾ۼ�����һ��ĸ��¿��Ժ���
    VT_RSSITEM items;	        // һ��Ƶ�����԰������������item
                                // һ��item����һ��"����"--����һ�ű�ֽ����һ����־�ϵ�һ������

    tagRSSChannel::tagRSSChannel()
    {

    }

    tagRSSChannel::tagRSSChannel(const tagRSSChannel &channel)
    {
        title = channel.title;
        link = channel.link;
        description = channel.description;
        language = channel.language;
        copyright = channel.copyright;
        managingEditor = channel.managingEditor;
        pubDate = channel.pubDate;
        lastBuildDate = channel.lastBuildDate;
        category = channel.category;
        generator = channel.generator;
        docs = channel.docs;
        cloud = channel.cloud;
        ttl = channel.ttl;
        image = channel.image;
        rating = channel.rating;
        textInput = channel.textInput;
        skipDays = channel.skipDays;
        skipHours = channel.skipHours;

        items.clear();
        items.assign(channel.items.begin(), channel.items.end());
    }
    
    tagRSSChannel &tagRSSChannel::operator=(const tagRSSChannel &channel)
    {
        if (this != &channel)
        {
            title = channel.title;
            link = channel.link;
            description = channel.description;
            language = channel.language;
            copyright = channel.copyright;
            managingEditor = channel.managingEditor;
            pubDate = channel.pubDate;
            lastBuildDate = channel.lastBuildDate;
            category = channel.category;
            generator = channel.generator;
            docs = channel.docs;
            cloud = channel.cloud;
            ttl = channel.ttl;
            image = channel.image;
            rating = channel.rating;
            textInput = channel.textInput;
            skipDays = channel.skipDays;
            skipHours = channel.skipHours;

            items.clear();
            items.assign(channel.items.begin(), channel.items.end());
        }

        return *this;
    }
} RSSChannel, * PRSSChannel;


// RSS�ṹ����
typedef struct tagRSSFeed
{
    char version[4];
    RSSChannel channel;

    tagRSSFeed::tagRSSFeed()
    {

    }

    tagRSSFeed::tagRSSFeed(const tagRSSFeed &feed)
    {
        memcpy(version, feed.version, sizeof(version));
        channel = feed.channel;
    }

    tagRSSFeed &tagRSSFeed::operator=(const tagRSSFeed &feed)
    {
        if (this != &feed)
        {
            memcpy(version, feed.version, sizeof(version));
            channel = feed.channel;
        }

        return *this;
    }
 } RSSFeed, * PRSSFeed;


// RSS Feed��ȡ���ӿ�
class RSSFeedReader
{
public:
    virtual bool Read(const string &filename, RSSFeed &feed) = 0;

protected:
    virtual void ReadChannel(RSSChannel &channel) = 0;
    virtual void ReadItem(RSSItem &item) = 0;
    virtual void ReadCategory(RSSCategory &category) = 0;
    virtual void ReadEnclosure(RSSEnclosure &enclosure) = 0;
    virtual void ReadGuid(RSSGUID &guid) = 0;
    virtual void ReadImage(RSSImage &image) = 0;
    virtual void ReadCloud(RSSCloud &cloud) = 0;
    virtual void ReadSource(RSSSource &source) = 0;
};

// RSS Feedд�����ӿ�
class RSSFeedWriter
{
public:
    virtual bool Write(const string &filename, const RSSFeed &feed) = 0;

protected:
    virtual void WriteChannel(const RSSChannel &channel) = 0;
    virtual void WriteItem(const RSSItem &item) = 0;
    virtual void WriteCategory(const RSSCategory &category) = 0;
    virtual void WriteEnclosure(const RSSEnclosure &enclosure) = 0;
    virtual void WriteGuid(const RSSGUID &guid) = 0;
    virtual void WriteImage(const RSSImage &image) = 0;
    virtual void WriteCloud(const RSSCloud &cloud) = 0;
    virtual void WriteSource(const RSSSource &source) = 0;
};


#endif // _RSS_FEED_DEF_H

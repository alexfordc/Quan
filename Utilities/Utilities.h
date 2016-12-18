#ifndef _UTILITIES_
#define _UTILITIES_

#include <time.h>
#include <sys/timeb.h>
#include <stdarg.h>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

//
/*
#define foreach(container,it,type) \
	for(type::iterator it = (container).begin();it!=(container).end();++it)*/

#define foreach(container,it,type) \
	for(type::const_iterator it = (container).begin();it!=(container).end();++it)

// Singleton pattern
template <typename T>
class Singleton
{
public:
    static T &getInstance()
    {
        Init();
        return *instance_;
    }

protected:
    static void Init()
    {
        if (instance_ == 0)
        {
            instance_ = new T;
            atexit(Destroy); //�������ʱ����ע��ĺ���
        }
    }

    static void Destroy()
    {
        delete instance_;
    }

	Singleton(){}
	~Singleton(){}

    static T *instance_;
};

template <typename T>
T *Singleton<T>::instance_ = 0;

// Logger class
#define MAXLOGSIZE 20000
#define MAXLINSIZE 16000

// Logger writer
class LoggerWriter
{
public:
	virtual void write(const char* msg) = 0;
protected:
private:
};

//
class FileLoggerWriter : public LoggerWriter
{
public:
	FileLoggerWriter()
	{
		time_t timep; 
		time(&timep); 
		struct tm *p = localtime(&timep); 

		char buf[64] = {0};

		sprintf(buf, "QA_%04d%02d%02d%02d%02d%02d.log", p->tm_year+1900,
			p->tm_mon+1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);

		ofFile.open(buf);
	}

	~FileLoggerWriter()
	{
		ofFile.close();
	}

	virtual void write(const char* msg)
	{
		ofFile<<msg<<endl;
	}
private:
	ofstream ofFile;
};




// Logger class
class Logger : public Singleton<Logger>
{
	friend class Singleton<Logger>;
public:
#ifdef WIN32
	Logger()
	{
		InitializeCriticalSection(&cs_log);
	}

	~Logger()
	{
		DeleteCriticalSection(&cs_log);
	}

	void Lock(CRITICAL_SECTION *l) {
		EnterCriticalSection(l);
	}

	void Unlock(CRITICAL_SECTION *l) {
		LeaveCriticalSection(l);
	}
#else
	void Lock(CRITICAL_SECTION *l) {
		pthread_mutex_lock(l);
	}
	
	void Unlock(CRITICAL_SECTION *l) {
		pthread_mutex_unlock(l);
	}
#endif

	void LogV(const char *pszFmt,va_list argp) 
	{
		struct tm *now;
		struct timeb tb;
		char logstr[MAXLINSIZE+1];
		char flog[MAXLOGSIZE] = {0};
		char datestr[16];
		char timestr[16];
		char mss[4];

		if (NULL == pszFmt|| 0 == pszFmt[0]) return;

		_vsnprintf(logstr,MAXLINSIZE,pszFmt,argp);

		ftime(&tb);

		now = localtime(&tb.time);

		sprintf(datestr,"%04d-%02d-%02d",now->tm_year+1900,now->tm_mon+1,now->tm_mday);

		sprintf(timestr,"%02d:%02d:%02d",now->tm_hour     ,now->tm_min  ,now->tm_sec );

		sprintf(mss,"%03d",tb.millitm);

		sprintf(flog,"[%s %s.%s] %s",datestr,timestr,mss,logstr);

		if (m_pLoggerWriter)
		{
			m_pLoggerWriter->write(flog);
		}
		else
		{
			 
		}
	}

	void Log(const char *pszFmt,...) 
	{
		va_list argp;

		Lock(&cs_log);
		
		va_start(argp,pszFmt);
		LogV(pszFmt,argp);
		va_end(argp);

		Unlock(&cs_log);
	}

	void setLoggerWriter(LoggerWriter* pWriter)
	{
		m_pLoggerWriter = pWriter;
	}

private:
	CRITICAL_SECTION cs_log;
	LoggerWriter* m_pLoggerWriter;
};


#define LOG(format, ...)  \
	do \
{\
	Logger::getInstance().Log(format, ##__VA_ARGS__); \
} while (0);

// Date class
class Date
{
public:
	Date();

	void fromString(const char* value);

	void fromStringYYYYMMDD(const char* value);

	void fromStringYYYYMMDDHHNNSS(const char* value);

	bool isInSameWeek(const Date& value);

	bool isInSameMonth(const Date& value);

	bool isInSameDay(const Date& value);

	static string GetDateOfToday();

	static Date Today();

	int operator-(const Date& value);

	bool operator>(const Date& value);

	bool operator>=(const Date& value);

	bool operator==(const Date& value);

	int year;
	int month;
	int day;
    int weekday;
	int hour;
	int minute;
	int second;

	enum WEEKDAY
	{
		MONDAY=1,
		TUESDAY=2,
		WEDNESDAY=3,
		THURSDAY=4,
		FRIDAY=5,
		SATURDAY=6,
		SUNDAY=7
	};
protected:
private:
};


//
class Observable;

class Observer
{
public:
	virtual void update(Observable* observable, void* arg) = 0;	
};

//
class Observable
{
public:
	void addObserver(Observer* observer)
	{
		observers.push_back(observer);
	}

	void removeObserver(Observer* observer)
	{
		vector<Observer*>::iterator it = find(observers.begin(), observers.end(), observer);

		if (it != observers.end())
		{
			observers.erase(it);
		}
	}

	void notifyObservers(void* arg)
	{
		foreach(observers, it, vector<Observer*>)
		{
			(*it)->update(this, arg);
		}
	}

protected:
	vector<Observer*> observers;
};

// ����ת������
template<class in_value,class out_type>
out_type convert(const in_value& t)
{
	stringstream stream;

	stream<<t;//�����д�ֵ

	out_type result;//����洢ת�����

	stream>>result;//��result��д��ֵ

	return result;
}



// ��Ϣ��
class Msg
{
public:
	Msg(void* sender, int msgCode)
		:_msgCode(msgCode), _sender(sender)
	{

	}

	int getMsgCode() { return _msgCode; }

	void* getSender() { return _sender; }

	virtual Msg* clone() = 0;

protected:
	int _msgCode;
	void* _sender;
};


// �㲥��Ϣģ����
// ��Ϣģ��
template<class MSGBODY>
class Notification : public Msg
{
public:
	Notification(void* sender, int msgCode, const MSGBODY data)
		:Msg(sender, msgCode), _body(data)
	{
	}

	MSGBODY& getBody()
	{
		return _body;
	}

	Notification<MSGBODY>* clone()
	{
		Notification<MSGBODY>* msg = new Notification<MSGBODY>(_sender, _msgCode, _body);

		return msg;
	}

private:
	MSGBODY _body;
};

//
// ���ڴ���㲥��Ϣ�����ģ����
template<class T, class PARAM>
class MsgReleaser
{
public:
	MsgReleaser(PARAM param) { _msg = (T*) param; }
	~MsgReleaser() { delete _msg; }

	T* operator()()
	{
		return _msg;
	}

	T* operator->()
	{
		return _msg;
	}

	T& operator*()
	{
		return *_msg;
	}
private:
	T* _msg;
};

//
#define sendNotification(msgcode,islast) \
	if (islast)						\
{								\
	Notification<string> msg(this, msgcode, string(""));			\
	notifyObservers(&msg);	\
}

// ����֪ͨ
#define sendNotificationMsg(msgcode,MSGBODYTYPE,body,islast) \
	if (islast)						\
{								\
	Notification<MSGBODYTYPE> msg(this, msgcode, body);			\
	notifyObservers(&msg);		\
}

// ������
#define handle_error(errcode,errmsg,outerr,lastmsg) \
	if ((errcode) != 0) {	\
	(lastmsg) = (errmsg); \
	Notification<string> msg(this, (outerr), string(""));			\
	notifyObservers(&msg);	\
	return; \
	}


//  
class RowInfo
{
public:
	void AddField(const string& field)
	{
		fields.push_back(field);
	}

	size_t GetCount()
	{
		return fields.size();
	}
protected:
	vector<string> fields;
};


// T ����ΪRowInfo������
template <class T>
class TSVFileReader
{
public:
	void Read(const char* strFileName, vector<T>& vtItems, const size_t columns)
	{
		string line, field;    //lineΪÿ�����ݣ�fieldΪÿ���ֶ�

		//���ļ�
		ifstream in;
		in.open(strFileName);    //�Զ��Ÿ���

		//�����ļ�����
		if(in.is_open())
		{
			//ѭ��ȡ��ÿһ������
			while(getline(in,line))
			{
				istringstream stream(line);

				//��һ�еĶ���ֶ�ȡ��
				T RowContext;

				//�ԡ�,����ȡÿ���ֶ�
				while(getline(stream, field, '	'))
				{
					//����
					RowContext.AddField(field);
				}

				if (RowContext.GetCount() < columns)
				{
					continue;
				}

				vtItems.push_back(RowContext);
			}

			// �ر��ļ�
			in.close();
		}
		else
		{
			//�ļ���ʧ��
			cout << "���ļ�ʧ�ܣ�";
		}
	}
};

// ���ݴ���
class DataHandler
{
public:
	void Load(const char* filename)
	{
		// һ�� 
		string strRow;

		//���ļ�
		ifstream in;

		in.open(filename);    //�Զ��Ÿ���

		//�����ļ�����
		if(in.is_open())
		{
			//ѭ��ȡ��ÿһ������
			while(getline(in, strRow))
			{
				istringstream stream(strRow);

				//��һ�еĶ���ֶ�ȡ��
				vector<string> RowContext;

				string field("");

				//��ȡÿ���ֶ�
				while(getline(stream, field, '='))
				{
					//����
					RowContext.push_back(field);
				}

				if (RowContext.size() != 2)
				{
					continue;
				}

				items_.insert(make_pair(RowContext[0], RowContext[1]));
			}

			in.close();
		}
	}

	// �������ļ�
	void Save(const char* filename)
	{
		ofstream os(filename, ios::out);

		if (os)
		{
			foreach(items_, it, MAPITEM)
			{
				stringstream ss;

				ss<<it->first<<"="<<it->second;

				os<<ss.str()<<endl;

				ss.clear();
			}

			os.close();
		}
	}

	// ��ȡһ�������� 
	template<class T>
	T GetItem(const string& key, const T& default_value) const
	{
		T ret = default_value;

		map<string, string>::const_iterator it = items_.find(key);

		if (it != items_.end())
		{
			ret = convert<string, T>(it->second); 
		}

		return ret;
	}

	// ����һ�������� 
	template<class T>
	void SetItem(const string& key, const T& value)
	{
		map<string, string>::iterator it = items_.find(key);

		string str = convert<T, string>(value);

		if (it != items_.end())
		{
			items_.erase(it);
		}

		items_.insert(make_pair(key, str));
	}

	// ����һ�������� 
	template<class T>
	void GetArray(const string& key, vector<T>& vtr, char delimiter)
	{
		map<string, string>::iterator it = items_.find(key);

		string str("");

		if (it != items_.end())
		{
			str = it->second;
		}
		else
		{
			return;
		}

		istringstream stream(str);

		string field("");

		//��ȡÿ���ֶ�
		while(getline(stream, field, delimiter))
		{
			T value = convert<string, T>(field);

			//����
			vtr.push_back(value);
		}
	}

	// ����һ�������� 
	template<class T>
	void SetArray(const string& key, const vector<T>& vtr, char delimiter)
	{
		stringstream ss;

		vector<T>::const_iterator itEnd = vtr.begin();

		foreach(vtr, it, vector<T>)
		{
			itEnd++;

			ss<<*it;

			if (itEnd != vtr.end())
			{
				ss<<delimiter;
			}
		}

		//items_.insert(make_pair(key, ss.str()));
		SetItem<string>(key, ss.str());
	}

	DataHandler& operator=(const DataHandler& value)
	{
		this->items_ = value.items_;

		return *this;
	}

private:
	typedef map<string, string> MAPITEM;
	map<string, string> items_;
};

// �����࣬����ͨ�ú���
class CommonUtil
{
public:
	// ��ʽ������
	static string FormatDouble(double d)
	{
		string str = "";

		char buf[64] = {0};

		sprintf(buf, "%.2f", d);

		str = buf;

		return str;
	}

};

#endif
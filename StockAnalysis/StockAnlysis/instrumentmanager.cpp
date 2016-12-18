#include "StdAfx.h"
#include "instrumentmanager.h"
#include "Configuration.h"


InstrumentManager& g_InstrumentMgr = InstrumentManager::getInstance();

InstrumentManager::InstrumentManager(void)
: sector_(SH)
{
}

InstrumentManager::~InstrumentManager(void)
{
}

vector<Instrument>& InstrumentManager::GetInstruments(SECTOR sector)
{
	const string INSTRUMENT_FILE[] = {"SH_Stock.txt", "SZ_Stock.txt", "CYB_Stock.txt", "ZXB_Stock.txt", "ZXBK_Stock.txt", "Indexs.txt", "instruments.csv"};

	vector<Instrument>& instruments = vtInstrument[sector];

	if (instruments.empty())
	{
		string strStockProductFile = g_Configuration.GetInstrumentFilePath();

		strStockProductFile += INSTRUMENT_FILE[sector];

		Load(strStockProductFile.c_str(), instruments);
	}

	return instruments;	
}

void InstrumentManager::Load(const char* strFileName, vector<Instrument>& vtInstrument)
{
	string line, field;    //lineΪÿ�����ݣ�fieldΪÿ���ֶ�

	cout << "��ȡ�����ļ�: " << strFileName << endl;

	//���ļ�
	ifstream in;
	in.open(strFileName);    //�Զ��Ÿ���

	//�����ļ�����
	if(in.is_open())
	{
		// remove the first row because it's column headers
		getline(in, line);

		//ѭ��ȡ��ÿһ������
		while(getline(in,line))
		{
			istringstream stream(line);

			//��һ�еĶ���ֶ�ȡ��
			vector<string> RowContext;

			//�ԡ�,����ȡÿ���ֶ�
			while(getline(stream, field, '\t'))
			{
				//����
				RowContext.push_back(field);
			}

			if (RowContext.size() < 2)
			{
				continue;
			}

			Instrument instrument;

			string strMarket;
			strMarket.append(RowContext[0], 0, 2);

			string strCode;
			strCode.append(RowContext[0], 2, RowContext[0].length());

			instrument.Code = RowContext[0];

			instrument.Market = (instrument.Code[0] == '6')?"SH":"SZ";

			instrument.Name = RowContext[1];

			vtInstrument.push_back(instrument);
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

InstrumentManager::SECTOR InstrumentManager::GetCurrentSector()
{
	return sector_;
}

void InstrumentManager::SetCurrentSector(SECTOR sector)
{
	sector_ = sector;
}

Instrument InstrumentManager::GetInstrument(const char* code)
{
	string str = "";

	vector<Instrument>& instruments = GetInstruments(ALL);

	Instrument instr;

	foreach(instruments, it, vector<Instrument>)
	{
		if (it->Code == string(code))
		{
			instr = *it;

			break;
		}
	}

	return instr;
}
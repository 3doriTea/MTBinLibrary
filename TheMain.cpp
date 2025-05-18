#include <iostream>
#include <iomanip>
#include <string>
#include "MTBin/MemoryStream.h"

const size_t BUFFER_SIZE{ 32 };
const size_t NAME_LENGTH{ 4 };

struct Status
{
	int hp;
	int mp;
	char* name;
};

// �o�b�t�@�̒��g��\������
static void PrintBuffer(const mtbin::Byte* _pBuffer);
// ����\������
static void PrintInfo(const std::string& _title, const mtbin::Byte* _pBuffer, const Status& _status);

int main()
{
	using mtbin::MemoryStream;
	using mtbin::Byte;

	Byte* pBuffer{ new Byte[BUFFER_SIZE]{} };
	MemoryStream ms{ pBuffer, BUFFER_SIZE };

	int hp = 100;
	int mp = 100;
	char name[] = "Tom";

	PrintInfo("Init", pBuffer, { hp, mp, name });

	ms.Write(hp);
	ms.Write(mp);
	ms.Write(name, sizeof(name));

	PrintInfo("Saved", pBuffer, { hp, mp, name });

	hp = 50;
	mp = 0;
	name[2] = 'p';

	PrintInfo("Changed", pBuffer, { hp, mp, name });
	
	// NOTE: �������ݎ��Ɉړ��������߁A���Ă���ꏊ�𓪂ɖ߂��K�v������
	ms.Seek(MemoryStream::SeekDir::Head);
	hp = ms.Read<int>();
	mp = ms.Read<int>();
	ms.Read(name, sizeof(name), NAME_LENGTH);

	PrintInfo("Loaded", pBuffer, { hp, mp, name });

	return 0;
}

inline void PrintBuffer(const mtbin::Byte* _pBuffer)
{
	std::cout << std::hex;
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		std::cout << std::setw(2) << std::setfill('0') << +_pBuffer[i];
	}
	std::cout << std::dec << std::endl << std::endl;
}

inline void PrintInfo(const std::string& _title, const mtbin::Byte* _pBuffer, const Status& _status)
{
	std::cout << std::string(30, '-') << _title << std::string(30, '-') << std::endl << std::endl;
	std::cout << "status: hp:" << _status.hp << ", mp:" << _status.mp << ", name:" << _status.name << std::endl << std::endl;
	std::cout << "buffer:";
	PrintBuffer(_pBuffer);
}

#pragma once

#include <functional>
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>
#include <cassert>
#include <new>

namespace cli
{
	const char base64keys[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	enum CodecType {
		E_ENCODE = 0x00,
		E_DECODE = 0x01 //
	};

	using pair_us = std::pair<unsigned, std::string>;

	class cmp
	{
	public:
		bool operator()(const pair_us & l, const pair_us & r) const
		{
			return l.first > r.first;
		}
	};

	using prioque = std::priority_queue<pair_us, std::vector<pair_us>, cmp>;

	class Base64Table
	{
	protected:
		unsigned short * amappi;
	public:
		Base64Table()
		{
			amappi = new unsigned short[128];
			for (unsigned short i = 0; i < 64; i++)
				amappi[base64keys[i]] = i;
		}
		~Base64Table()
		{
			delete[] amappi;
		}
		unsigned short operator[](char _c) const
		{
			return amappi[_c];
		}
	};

	void GroupsEncode(pair_us, prioque &);
	void GroupsDecode(pair_us, prioque &);

	class Base64
	{
	public:
		Base64() {}
		static std::string encode_or_decode(const char * cpstr, CodecType valueType, bool isopen, std::size_t threads_num);

	};
}

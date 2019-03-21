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
	std::mutex m;
	const char base64keys[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	class cmp
	{
	public:
		bool operator()(const std::pair<unsigned, std::string> & l, const std::pair<unsigned, std::string> & r) const
		{
			return l.first > r.first;
		}
	};

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

	void GroupsEncode(std::pair<unsigned, std::string>,
		std::priority_queue<std::pair<unsigned, std::string>, std::vector<std::pair<unsigned, std::string>>, cmp> &);
	void GroupsDecode(std::pair<unsigned, std::string>,
		std::priority_queue<std::pair<unsigned, std::string>, std::vector<std::pair<unsigned, std::string>>, cmp> &);

	class Base64
	{
	public:
		Base64() {}
		static std::string & encode(const char * cpstr, bool isopen = false, std::size_t threads_num = 1);
		static std::string & decode(const char * cpstr, bool isopen = false, std::size_t threads_num = 1);
	};
}

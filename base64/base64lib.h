#pragma once
#ifndef BASE64_DLL_H
#define BASE64_DLL_H

#include <functional>
#include <string>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <chrono>
#include <new>

std::mutex m;
const char * base64keys = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

class SplitPloy {
public:
	unsigned w;
	std::string three;
	std::string four;

	SplitPloy() : w(0u), three(), four() {}
	SplitPloy(unsigned weight, std::string ps) : w(weight) {
		three = ps;
		four = ps;
	}
};

class cmp {
public:
	bool operator()(const std::pair<unsigned, std::string> & l, const std::pair<unsigned, std::string> & r) const
	{
		return l.first > r.first;
	}
};

class Base64Table {
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

void GroupsEncode(SplitPloy & sp,
	std::priority_queue<std::pair<unsigned, std::string>, std::vector<std::pair<unsigned, std::string>>, cmp> & sque);
void GroupsDecode(SplitPloy & sp,
	std::priority_queue<std::pair<unsigned, std::string>, std::vector<std::pair<unsigned, std::string>>, cmp> & sque);

class Base64 {
	std::string bucket;
public:
	Base64() : bucket() {}
	std::string & encode(const char *, bool, std::size_t);
	std::string & decode(const char *, bool, std::size_t);
};

#endif
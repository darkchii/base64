#include "base64lib.h"

void GroupsEncode(
	SplitPloy & sp,
	std::priority_queue<std::pair<unsigned, std::string>, std::vector<std::pair<unsigned, std::string>>, cmp> & sque)
{
	std::lock_guard<std::mutex> lock(m);
	std::string four = "";
	unsigned prev[6] = { 0u };
	unsigned i = 0u;
	for (; i < 3 && sp.three[i]; i++)
	{
		unsigned inx = int(sp.three[i]);
		unsigned pre_bit[6] = { 0u };

		for (unsigned k = 0; k < 2 * (i + 1); k++, inx >>= 1)
			pre_bit[k] = inx & 1;
		if (i > 0u) {
			for (unsigned k = 0; k < 2 * i; k++)
				inx += prev[k] << (5 - k);
		}
		four += base64keys[inx];
		for (unsigned k = 0; k < 2 * (i + 1); k++)
			prev[2 * i - k + 1] = pre_bit[k];
	}
	if (i > 0) {
		unsigned inx = 0u;
		for (unsigned k = 0; k < 2 * i; k++)
			inx += prev[k] << (5 - k);
		four += base64keys[inx];
		while (i < 3) four += '=', i++;
	}
	sque.push(std::pair<unsigned, std::string>(sp.w, four));
}

void GroupsDecode(
	SplitPloy & sp,
	std::priority_queue<std::pair<unsigned, std::string>, std::vector<std::pair<unsigned, std::string>>, cmp> & sque)
{
	std::lock_guard<std::mutex> lock(m);
	Base64Table v;
	std::string three = "";
	unsigned suffix_bit[6] = { 0u };

	unsigned y1 = v[sp.four[0]] << 2, w1 = v[sp.four[1]];
	for (unsigned k = 0u; k < 4; k++, w1 >>= 1)
		suffix_bit[k] = w1 & 1;
	unsigned x1 = y1 + w1;
	three += char(x1);

	unsigned y2 = 0u, w2 = sp.four[2] == '=' ? 0u : v[sp.four[2]];
	for (unsigned k = 0u; k < 4; k++)
		y2 += suffix_bit[4 - k - 1] << (7 - k);
	for (unsigned k = 0u; k < 2; k++, w2 >>= 1)
		suffix_bit[k] = w2 & 1;
	unsigned x2 = y2 + w2;
	three += char(x2);

	unsigned y3 = 0u, w3 = sp.four[3] == '=' ? 0u : v[sp.four[3]];
	for (unsigned k = 0u; k < 2; k++)
		y3 += suffix_bit[2 - k - 1] << (7 - k);
	unsigned x3 = y3 + w3;
	three += char(x3);

	sque.push(std::pair<unsigned, std::string>(sp.w, three));
}

std::string & Base64::encode(const char * cpstr, bool isopen = false, std::size_t threads_num = 1)
{
	std::priority_queue<std::pair<unsigned, std::string>, std::vector<std::pair<unsigned, std::string>>, cmp> sque;
	std::queue<std::pair<unsigned, std::string>> que;
	std::vector<std::thread> threads;
	std::pair<unsigned, std::string> p;

	for (unsigned w = 0u; *cpstr; w++)
	{
		p.second.clear();
		for (unsigned i = 0u; i < 3 && *cpstr; i++, cpstr++)
			p.second += *cpstr;
		p.first = w;
		que.push(p);
	}

	while (!que.empty())
	{
		for (unsigned i = 0; i < threads_num; i++)
		{
			if (!que.empty())
			{
				SplitPloy sp(que.front().first, que.front().second);
				que.pop();
				if (!isopen) GroupsEncode(sp, sque);
				else threads.push_back(std::thread(GroupsEncode, std::ref(sp), std::ref(sque)));
			}
		}
		for (auto & thread : threads) thread.join();
		threads.clear();
	}

	while (!sque.empty()) bucket += sque.top().second, sque.pop();
	return bucket;
}

std::string & Base64::decode(const char * cpstr, bool isopen = false, std::size_t threads_num = 1)
{
	std::priority_queue<std::pair<unsigned, std::string>, std::vector<std::pair<unsigned, std::string>>, cmp> sque;
	std::queue<std::pair<unsigned, std::string>> que;
	std::vector<std::thread> threads;
	std::pair<unsigned, std::string> p;

	for (unsigned w = 0u; *cpstr; w++)
	{
		p.second.clear();
		for (unsigned i = 0u; i < 4 && *cpstr; i++, cpstr++)
			p.second += *cpstr;
		p.first = w;
		que.push(p);
	}

	while (!que.empty())
	{
		for (unsigned i = 0; i < threads_num; i++)
		{
			if (!que.empty())
			{
				SplitPloy sp(que.front().first, que.front().second);
				que.pop();
				if (!isopen) GroupsDecode(sp, sque);
				else threads.push_back(std::thread(GroupsDecode, std::ref(sp), std::ref(sque)));
			}
		}
		for (auto & thread : threads) thread.join();
		threads.clear();
	}

	while (!sque.empty()) bucket += sque.top().second, sque.pop();
	return bucket;
}
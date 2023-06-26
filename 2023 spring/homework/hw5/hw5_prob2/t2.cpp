#include <string> 
#include <vector>
#include <cassert>
#include <cctype>
#include <iostream>

std::string strip(const std::string &s) {
	std::size_t begin = 0;
	std::size_t end = s.size();
	while (begin < end && std::isspace(s[begin]))
		++begin;
	while (begin < end && std::isspace(s[end - 1]))
		--end;
	return s.substr(begin, end - begin);
}


std::string join(const std::string &sep, const std::vector<std::string> &strings)
{
	// oncatenate the strings strings, during which the string sep is inserted in between each given string. Then return the result.
	std::string result("");
	for (std::size_t i = 0; i < strings.size(); ++i)
	{
		result += strings[i];
		if (i != strings.size() - 1)
			result += sep;
	}
	return result;
}


std::vector<std::string> split(const std::string &str, const std::string &sep)
{
	// Using sep as the delimiter, split the string str into a vector of strings and return that vector. 
	std::vector<std::string> result;
	std::size_t begin = 0;
	std::size_t pos = str.find(sep);
	// std::cout<<std::string::npos<<std::endl;
	while (pos != std::string::npos)
	{
		result.push_back(str.substr(begin, pos - begin));
        begin = pos + sep.length();
        pos = str.find(sep, begin);
	}
	result.push_back(str.substr(begin));
	// for(auto &s : result)std::cout<<s<<",";std::cout<<'\n';
	return result;
}

std::string swapcase(std::string str)
{
	/*
		Returns the string obtained from str with cases swapped,
		i.e. lowercase letters are changed to their uppercase forms,
		and uppercase letters are changed to their lowercase forms.
		Other characters remain unchanged.
	*/
	for(auto &c : str)
	{
		if(std::islower(c))
			c = std::toupper(c);
		else if(std::isupper(c))
			c = std::tolower(c);
	}
	return str;
}

int main()
{
	puts("testing strip()...");
	assert(strip("   wefafwefw    \n") == "wefafwefw");

	puts("testing join()...");
	std::vector<std::string> strings = {"hello", "world", "cxx23"};
	assert(join(", ", strings) == "hello, world, cxx23");

	puts("testing split()...");
	std::vector<std::string> ans{"", "aaa", "", "bbb", "cdefg"};
	assert(split("xaaaxxbbbxcdefg", "x") == ans);
	ans = {"", "x"};
	assert(split("xxx", "xx") == ans);

	puts("testing swapcase()...");
	std::cout<<swapcase("123..abcDEF")<<std::endl;
	return 0;
}

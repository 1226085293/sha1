#pragma once
#include <string>

// ±àÂë
namespace tool::encode {
	// sha1
	std::string& sha1(std::string& data_);
	std::string sha1(std::string&& data_);
	// base64
	void base64(std::string& str_);
}
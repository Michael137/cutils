#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>

std::string exec( const char* cmd )
{
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype( &pclose )> pipe( popen( cmd, "r" ),
	                                                 pclose );
	if( !pipe )
	{
		throw std::runtime_error( "popen() failed!" );
	}
	while( fgets( buffer.data(), buffer.size(), pipe.get() ) != nullptr )
	{
		result += buffer.data();
	}
	return result;
}

int main()
{
	std::string output = exec(
	    "adb shell ls "
	    "\"/sdcard/mlperf_datasets/imagenet/img/ILSVRC2012_val_00000*\"" );
	size_t pos = 0;
	std::string token;
	std::string delimiter = "\n";
	std::vector<std::string> output_vec;
	while( ( pos = output.find( delimiter ) ) != std::string::npos )
	{
		token = output.substr( 0, pos );
		output_vec.push_back(token);
		output.erase( 0, pos + delimiter.length() );
	}

	std::smatch match;
	std::regex pattern{R"(/sdcard/mlperf_datasets/imagenet/img/ILSVRC2012_val_([0-9]+)\.*)"};
	int sum = 0;
	for(auto&& e : output_vec)
	{
		if(std::regex_search(e, match, pattern))
			sum += std::stoi(match[1].str());
	}

	std::cout << sum << std::endl;

	return 0;
}

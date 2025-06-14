#include "logger.h"

void print_log(std::string filename, std::string msg, bool append) {
	std::ofstream log; //if the file desnt exist it creates it
	if (append) { log.open(filename, std::fstream::app); } //flag ensures append
	else { log.open(filename); }

	char tmp[1000];
	struct tm p;
	time_t now = time(0);
	localtime_s(&p, &now);
	strftime(tmp, 1000, "%B %d, %H:%M:%S", &p);

	if (!log) { std::cout << "Error: " << filename << " failed to open.\n"; return; }
	msg = (std::string)tmp + " " + msg + "\n";
	log << msg;
	log.close();
}
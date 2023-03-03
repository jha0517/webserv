#ifndef REPONSE_H
# define REPONSE_H
# include <map>
# include <string>
# include <unistd.h>

enum URIType { DIRECTORY, MYFILE, FILE_TO_CREATE, CGI_PROGRAM };
enum TransferType { GENERAL, CHUNKED };
enum Phase { READY, ON_HEADER, ON_BODY, COMPLETE };

class Response
{
private:
	std::map<std::string, std::string> start;
	std::map<std::string, std::string> header;
	std::map<std::string, std::string> body;
	
public:
	Response();
	~Response();
	void	send(int fd);
};

#endif
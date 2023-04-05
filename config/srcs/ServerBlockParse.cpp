/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerBlockParse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 00:07:25 by yhwang            #+#    #+#             */
/*   Updated: 2023/04/05 14:45:13 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ServerBlockParse.hpp"

ServerBlockParse::ServerBlockParse()
			: _server_keyword_check(0), _server_braket_open(0), _server_block_count(0),
			_listen_flag(0), _host_flag(0), _client_max_body_size_flag(0),
			_index_flag(0), _allow_methods_flag(0), _save_path_flag(0),
			_listen(0), _host(""), _client_max_body_size(0), _index(""),
			_allow_methods_get(0), _allow_methods_post(0), _allow_methods_delete(0),
			_save_path(""), _server_parse_done(0), _config_file_name(""), _err_msg(""),
			_total_location_block(0), _location_block_ended(0), _http_braket_close(0)
{
}

ServerBlockParse::ServerBlockParse(const ServerBlockParse& serverblockparse): HttpBlockParse(serverblockparse)
{
	*this = serverblockparse;
}

ServerBlockParse& ServerBlockParse::operator=(const ServerBlockParse& serverblockparse)
{
	if (this == &serverblockparse)
		return (*this);
	HttpBlockParse::operator=(serverblockparse);
	this->_server_keyword_check = serverblockparse._server_keyword_check;
	this->_server_braket_open = serverblockparse._server_braket_open;
	this->_server_block_count = serverblockparse._server_block_count;
	this->_listen_flag = serverblockparse._listen_flag;
	this->_host_flag = serverblockparse._host_flag;
	this->_client_max_body_size_flag = serverblockparse._client_max_body_size_flag;
	this->_index_flag = serverblockparse._index_flag;
	this->_allow_methods_flag = serverblockparse._allow_methods_flag;
	this->_save_path_flag = serverblockparse._save_path_flag;
	this->_listen = serverblockparse._listen;
	this->_host = serverblockparse._host;
	this->_client_max_body_size = serverblockparse._client_max_body_size;
	this->_index = serverblockparse._index;
	this->_allow_methods_get = serverblockparse._allow_methods_get;
	this->_allow_methods_post = serverblockparse._allow_methods_post;
	this->_allow_methods_delete = serverblockparse._allow_methods_delete;
	this->_save_path = serverblockparse._save_path;
	this->_server_parse_done = serverblockparse._server_parse_done;
	this->_config_file_name = serverblockparse._config_file_name;
	this->_err_msg = serverblockparse._err_msg;
	this->_total_location_block = serverblockparse._total_location_block;
	this->_location_block_ended = serverblockparse._location_block_ended;
	this->_http_braket_close = serverblockparse._http_braket_close;
	this->_server_block = serverblockparse._server_block;
	return (*this);
}

ServerBlockParse::~ServerBlockParse()
{
}

int	ServerBlockParse::GetListen(void) const
{
	return (this->_listen);
}

std::string	ServerBlockParse::GetHost(void) const
{
	return (this->_host);
}

int	ServerBlockParse::GetClientMaxBodySize(void) const
{
	return (this->_client_max_body_size);
}

std::string	ServerBlockParse::GetIndex(void) const
{
	return (this->_index);
}

int	ServerBlockParse::GetAllowMethodsGet(void) const
{
	return (this->_allow_methods_get);
}

int	ServerBlockParse::GetAllowMethodsPost(void) const
{
	return (this->_allow_methods_post);
}

int	ServerBlockParse::GetAllowMethodsDelete(void) const
{
	return (this->_allow_methods_delete);
}

int	ServerBlockParse::GetAllowMethodsFlag(void) const
{
	return (this->_allow_methods_flag);
}

std::string	ServerBlockParse::GetSavePath(void) const
{
	return (this->_save_path);
}

int	ServerBlockParse::GetServerParseDone(void) const
{
	return (this->_server_parse_done);
}

int	ServerBlockParse::GetServerBlockCount(void) const
{
	return (this->_server_block_count);
}

int	ServerBlockParse::GetTotalLocationBlock(void) const
{
	return (this->_total_location_block);
}

int	ServerBlockParse::GetHttpBraketClose(void) const
{
	return (this->_http_braket_close);
}

void	ServerBlockParse::SetConfigFileName(std::string config_file_name)
{
	this->_config_file_name = config_file_name;
}

void	ServerBlockParse::SetLocationBlockEnded(int i)
{
	this->_location_block_ended = i;
}

void	ServerBlockParse::SetHttpBraketCloseSaveHttp(void)
{
	this->_http_braket_close = 1;
	HttpBlockParse::SaveHttpBlock(this->_server_block);
}

void	ServerBlockParse::IncreaseTotalLocationBlock(void)
{
	this->_total_location_block++;
}

void	ServerBlockParse::SaveServerBlock(std::vector<t_redirection> redirection_location,
			std::vector<t_index> index_location, std::vector<t_cgi> cgi_location)
{
	t_server_block	save;

	save.listen = this->_listen;
	save.host = this->_host;
	save.client_max_body_size = this->_client_max_body_size;
	save.index = this->_index;
	save.allow_methods_get = this->_allow_methods_get;
	save.allow_methods_post = this->_allow_methods_post;
	save.allow_methods_delete = this->_allow_methods_delete;
	save.save_path = this->_save_path;
	save.redirection_location_block = redirection_location;
	save.index_location_block = index_location;
	save.cgi_location_block = cgi_location;
	
	this->_server_block.push_back(save);
}

void	ServerBlockParse::InitServerBlockParseData(void)
{
	this->_server_keyword_check = 0;
	this->_server_braket_open = 0;
	this->_listen_flag = 0;
	this->_host_flag = 0;
	this->_client_max_body_size_flag = 0;
	this->_index_flag = 0;
	this->_allow_methods_flag = 0;
	this->_save_path_flag = 0;
	this->_listen = 0;
	this->_host = "";
	this->_client_max_body_size = 0;
	this->_index = "";
	this->_allow_methods_get = 0;
	this->_allow_methods_post = 0;
	this->_allow_methods_delete = 0;
	this->_save_path = "";
	this->_server_parse_done = 0;
	this->_err_msg = "";
	this->_total_location_block = 0;
	this->_location_block_ended = 0;
}

void	ServerBlockParse::ServerBlockCheck(std::string *line, int i)
{
	std::string	temp = *line;

	HttpMissedKeywordCheck(line, temp, i);
	
	/* when the line includes keyword "location", regard as server block parsing is done */
	if (temp.find("location") != std::string::npos)
		this->_server_parse_done++;

	/* if server block parsing is done, it will not be handled on this function */
	if (this->_server_parse_done)
		return ;

	/* check if there is invalid character(s) after closing http block curved braket */
	if (this->_http_braket_close == 1 && StringCheck(temp))
	{
		this->_err_msg = ErrMsg(this->_config_file_name, HTTP_BRAKET_CLOSE, *line, i);
		throw (this->_err_msg);
	}

	/* for http block closing */
	if (this->_location_block_ended == 1 && temp.find("}") != std::string::npos)
	{
		if (StringCheck(temp, '}'))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_INVALID_KWD, *line, i);
			throw (this->_err_msg);
		}
		SetHttpBraketCloseSaveHttp();
		this->_location_block_ended--;
		temp = temp.substr(temp.find("}") + strlen("}"), std::string::npos);
		if (temp == "" || !StringCheck(temp))
			return ;
		else
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_BRAKET_CLOSE, *line, i);
			throw (this->_err_msg);
		}
	}

	if (temp.find("}") != std::string::npos)
	{
		if (!this->_server_keyword_check)
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_SERVER_MISSED, *line, i);
		else
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_CLOSE, *line, i);
		throw (this->_err_msg);
	}
	if (this->_server_braket_open && temp.find("{") != std::string::npos)
	{
		this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_OPEN, *line, i);
		throw (this->_err_msg);
	}

	if (temp.find("server") != std::string::npos)
		ServerKeywordServerCheck(line, temp, i);
	else if (temp.find("{") != std::string::npos)
		ServerBraketOpenCheck(line, temp, i);
	else if (temp.find("listen") != std::string::npos
		|| temp.find("host") != std::string::npos
		|| temp.find("client_max_body_size") != std::string::npos
		|| temp.find("index") != std::string::npos
		|| temp.find("allow_methods") != std::string::npos
		|| temp.find("save_path") != std::string::npos)
	{
		if (temp.find("listen") != std::string::npos)
			ServerKeywordCheck(line, temp, i, "listen");
		if (temp.find("host") != std::string::npos)
			ServerKeywordCheck(line, temp, i, "host");
		if (temp.find("client_max_body_size") != std::string::npos)
			ServerKeywordCheck(line, temp, i, "client_max_body_size");
		if (temp.find("index") != std::string::npos)
			ServerKeywordCheck(line, temp, i, "index");
		if (temp.find("allow_methods") != std::string::npos)
			ServerKeywordCheck(line, temp, i, "allow_methods");
		if (temp.find("save_path") != std::string::npos)
			ServerKeywordCheck(line, temp, i, "save_path");
		ServerKeywordTokenCheck(line, temp, i);
	}
	else
	{
		if (StringCheck(temp))
		{
			if (this->_http_braket_close)
				this->_err_msg = ErrMsg(this->_config_file_name, HTTP_INVALID_KWD, *line, i);
			else
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_INVALID_KWD, *line, i);
			throw (this->_err_msg);
		}
	}
}

void	ServerBlockParse::HttpMissedKeywordCheck(std::string *line, std::string temp, int i)
{
	if (_server_braket_open)
		return ;

	if (HttpBlockParse::GetHttpParseDone() && temp.find("server") == std::string::npos)
	{
		if (temp.find("root") != std::string::npos)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_KWD_ROOT_EXISTS, *line, i);
			throw (this->_err_msg);
		}
		if (temp.find("autoindex") != std::string::npos)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_KWD_AUTOINDEX_EXISTS, *line, i);
			throw (this->_err_msg);
		}
		if (temp.find("default_error_page") != std::string::npos)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_KWD_DEFAULT_ERROR_PAGE_EXISTS, *line, i);
			throw (this->_err_msg);
		}
	}
	if (HttpBlockParse::GetRoot() == "")
	{
		this->_err_msg = ErrMsg(this->_config_file_name, HTTP_KWD_ROOT_MISSED, *line, i);
		throw (this->_err_msg);
	}
	if (HttpBlockParse::GetAutoIndex() == "")
	{
		this->_err_msg = ErrMsg(this->_config_file_name, HTTP_KWD_AUTOINDEX_MISSED, *line, i);
		throw (this->_err_msg);
	}
	if (HttpBlockParse::GetDefaultErrorPage() == "")
	{
		this->_err_msg = ErrMsg(this->_config_file_name, HTTP_KWD_DEFAULT_ERROR_PAGE_MISSED, *line, i);
		throw (this->_err_msg);
	}
}

void	ServerBlockParse::ServerKeywordCheck(std::string *line, std::string temp, int i, std::string keyword)
{
	if (StringCheck(temp.substr(0, temp.find(keyword)))
		|| !(temp[temp.find(keyword) + strlen(keyword.c_str())] == ' ' || temp[temp.find(keyword) + strlen(keyword.c_str())] == '\t'))
	{
		if (keyword == "server")
		{
			if (temp[temp.find(keyword) + strlen(keyword.c_str())] == '{'
				|| temp[temp.find(keyword) + strlen(keyword.c_str())] == '\0')
				return ;
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_SERVER, *line, i);
		}
		else if (keyword == "listen")
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_LISTEN, *line, i);
		else if (keyword == "host")
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_HOST, *line, i);
		else if (keyword == "client_max_body_size")
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_CLIENT_MAX_BODY_SIZE, *line, i);
		else if (keyword == "index")
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_INDEX, *line, i);
		else if (keyword == "allow_methods")
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_ALLOW_METHODS, *line, i);
		else if (keyword == "save_keyword")
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_SAVE_PATH, *line, i);
		throw (this->_err_msg);
	}
}

void	ServerBlockParse::ServerKeywordServerCheck(std::string *line, std::string temp, int i)
{
	/* keyword "server" exists only once in the each server block */
	ServerKeywordCheck(line, temp, i, "server");
	this->_server_keyword_check++;

	/* opening curved braket should be exists after the keyword "server" */
	if (this->_server_keyword_check == 0 && StringCheck(temp.substr(temp.find("server") + strlen("server"), std::string::npos), '{'))
	{
		this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_OPEN, *line, i);
		throw (this->_err_msg);
	}

	if (temp.find("{") != std::string::npos)
	{
		temp = temp.substr(temp.find("server") + strlen("server"), std::string::npos);
		ServerBraketOpenCheck(line, temp, i);
	}
}

void	ServerBlockParse::ServerBraketOpenCheck(std::string *line, std::string temp, int i)
{
	this->_server_braket_open++;
	if (temp.find("{") != 0 && !StringCheck(temp.substr(0, temp.find("{"))))
		temp = temp.substr(temp.find("{"), std::string::npos);
	
	/* opening curved braket exists only once in the each server block */
	if (temp.substr(temp.find("{") + strlen("{"), std::string::npos).find("{") != std::string::npos)
	{
		this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_OPEN, *line, i);
		throw (this->_err_msg);
	}
	if (temp.find("listen") != std::string::npos
		|| temp.find("host") != std::string::npos
		|| temp.find("client_max_body_size") != std::string::npos
		|| temp.find("index") != std::string::npos
		|| temp.find("allow_methods") != std::string::npos
		|| temp.find("save_path") != std::string::npos)
	{
		temp = temp.substr(temp.find("{") + 1, std::string::npos);
		if (temp.find("listen") != std::string::npos)
			ServerKeywordCheck(line, temp, i, "listen");
		if (temp.find("host") != std::string::npos)
			ServerKeywordCheck(line, temp, i, "host");
		if (temp.find("client_max_body_size") != std::string::npos)
			ServerKeywordCheck(line, temp, i, "client_max_body_size");
		if (temp.find("index") != std::string::npos)
			ServerKeywordCheck(line, temp, i, "index");
		if (temp.find("allow_methods") != std::string::npos)
			ServerKeywordCheck(line, temp, i, "allow_methods");
		if (temp.find("save_path") != std::string::npos)
			ServerKeywordCheck(line, temp, i, "save_path");
		ServerKeywordTokenCheck(line, temp, i);
	}	

	/* after finding opening braket, there should be keyword "server" too */
	if (this->_server_keyword_check == 1 && this->_server_braket_open == 1)
		this->_server_block_count++;
	else
	{
		this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_OPEN, *line, i);
		throw (this->_err_msg);
	}
}

void	ServerBlockParse::ServerKeywordTokenCheck(std::string *line, std::string temp, int i)
{
	std::string	token[100] = {"", };

	if (temp.find("listen") != std::string::npos)
	{
		if (!this->_server_braket_open)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_OPEN, *line, i);
			throw (this->_err_msg);
		}
		if (this->_listen_flag == 1)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_LISTEN_EXISTS, *line, i);
			throw (this->_err_msg);
		}
		if (TokenCount(2, temp, token) && !this->_server_parse_done)
		{
			if (!(TokenCount(temp, token) == 3 && token[1].find(";") == std::string::npos))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_LISTEN, *line, i);
				throw (this->_err_msg);
			}
		}
	}
	else if (temp.find("host") != std::string::npos)
	{
		if (!this->_server_braket_open)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_OPEN, *line, i);
			throw (this->_err_msg);
		}
		if (this->_host_flag == 1)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_HOST_EXISTS, *line, i);
			throw (this->_err_msg);
		}
		if (TokenCount(2, temp, token) && !this->_server_parse_done)
		{
			if (!(TokenCount(temp, token) == 3 && token[1].find(";") == std::string::npos))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_HOST, *line, i);
				throw (this->_err_msg);
			}
		}
	}
	else if (temp.find("client_max_body_size") != std::string::npos)
	{
		if (!this->_server_braket_open)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_OPEN, *line, i);
			throw (this->_err_msg);
		}
		if (this->_client_max_body_size_flag == 1)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_CLIENT_MAX_BODY_SIZE_EXISTS, *line, i);
			throw (this->_err_msg);
		}
		if (TokenCount(2, temp, token) && !this->_server_parse_done)
		{
			if (!(TokenCount(temp, token) == 3 && token[1].find(";") == std::string::npos))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_CLIENT_MAX_BODY_SIZE, *line, i);
				throw (this->_err_msg);
			}
		}
	}
	else if (temp.find("index") != std::string::npos)
	{
		if (!this->_server_braket_open)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_OPEN, *line, i);
			throw (this->_err_msg);
		}
		if (this->_index_flag == 1)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_INDEX_EXISTS, *line, i);
			throw (this->_err_msg);
		}
		if (TokenCount(2, temp, token) && !this->_server_parse_done)
		{
			if (!(TokenCount(temp, token) == 3 && token[1].find(";") == std::string::npos))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_INDEX, *line, i);
				throw (this->_err_msg);
			}
		}
	}
	else if (temp.find("allow_methods") != std::string::npos)
	{
		if (!this->_server_braket_open)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_OPEN, *line, i);
			throw (this->_err_msg);
		}
		if (this->_allow_methods_flag == 1)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_ALLOW_METHODS_EXISTS, *line, i);
			throw (this->_err_msg);
		}
		if (!(TokenCount(temp, token) == 2 || TokenCount(temp, token) == 3 || TokenCount(temp, token) == 4))
		{
			if (!(TokenCount(temp, token) == 5 && token[3].find(";") == std::string::npos))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_ALLOW_METHODS, *line, i);
				throw (this->_err_msg);
			}
		}
		this->_allow_methods_flag = TokenCount(temp, token) - 1;
	}
	else if (temp.find("save_path") != std::string::npos)
	{
		if (!this->_server_braket_open)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_OPEN, *line, i);
			throw (this->_err_msg);
		}
		if (this->_save_path_flag == 1)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_SAVE_PATH_EXISTS, *line, i);
			throw (this->_err_msg);
		}
		if (TokenCount(2, temp, token) && !this->_server_parse_done)
		{
			if (!(TokenCount(temp, token) == 3 && token[1].find(";") == std::string::npos))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_SAVE_PATH, *line, i);
				throw (this->_err_msg);
			}
		}
	}
	ServerBlockGetInfo(token, line, i);
	if (this->_listen != 0 && this->_host != "" && this->_client_max_body_size != 0 && this->_index != ""
		&& this->_allow_methods_flag != 0 && this->_save_path != "")
		this->_server_parse_done = 1;
}

void	ServerBlockParse::ServerBlockGetInfo(std::string *token, std::string *line, int i)
{
	if (token[0] == "listen" && !this->_server_parse_done)
	{
		//number check, number range check
		if (SemicolonCheck(token[1]))
		{
			if (!(token[2] != "" && token[1].find(";") == std::string::npos && !SemicolonCheck(token[2])))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_SEMICOLON, *line, i);
				throw (this->_err_msg);
			}
		}
		if (token[2] == "")
		{
			token[1] = token[1].substr(0, token[1].find(";"));
			token[1] = RemoveSpaceTab(token[1]);
		}
		this->_listen_flag++;
		this->_listen = atoi(token[1].c_str());
	}
	if (token[0] == "host" && !this->_server_parse_done)
	{
		//ip address check
		if (SemicolonCheck(token[1]))
		{
			if (!(token[2] != "" && token[1].find(";") == std::string::npos && !SemicolonCheck(token[2])))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_SEMICOLON, *line, i);
				throw (this->_err_msg);
			}
		}
		if (token[2] == "")
		{
			token[1] = token[1].substr(0, token[1].find(";"));
			token[1] = RemoveSpaceTab(token[1]);
		}
		this->_host_flag++;
		this->_host = token[1];
	}
	if (token[0] == "client_max_body_size" && !this->_server_parse_done)
	{
		//number check, number range check
		if (SemicolonCheck(token[1]))
		{
			if (!(token[2] != "" && token[1].find(";") == std::string::npos && !SemicolonCheck(token[2])))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_SEMICOLON, *line, i);
				throw (this->_err_msg);
			}
		}
		if (token[2] == "")
		{
			token[1] = token[1].substr(0, token[1].find(";"));
			token[1] = RemoveSpaceTab(token[1]);
		}
		this->_client_max_body_size_flag++;
		this->_client_max_body_size = atoi(token[1].c_str());
	}
	if (token[0] == "index" && !this->_server_parse_done)
	{
		//check if the path is valid
		if (SemicolonCheck(token[1]))
		{
			if (!(token[2] != "" && token[1].find(";") == std::string::npos && !SemicolonCheck(token[2])))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_SEMICOLON, *line, i);
				throw (this->_err_msg);
			}
		}
		if (token[2] == "")
		{
			token[1] = token[1].substr(0, token[1].find(";"));
			token[1] = RemoveSpaceTab(token[1]);
		}
		this->_index_flag++;
		//this->_index = HttpBlockParse::GetRoot().append("/") + token[1];
		this->_index = token[1];
	}
	if (token[0] == "allow_methods" && !this->_server_parse_done)
	{
		if (this->_allow_methods_flag == 1)
		{
			if (SemicolonCheck(token[1]))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_SEMICOLON, *line, i);
				throw (this->_err_msg);
			}
			token[1] = token[1].substr(0, token[1].find(";"));
			token[1] = RemoveSpaceTab(token[1]);

			if (token[1] == "GET")
			{
				this->_allow_methods_get = 1;
				this->_allow_methods_flag = 1;
			}
			else if (token[1] == "POST")
			{
				this->_allow_methods_post = 1;
				this->_allow_methods_flag = 1;
			}
			else if (token[1] == "DELETE")
			{
				this->_allow_methods_delete = 1;
				this->_allow_methods_flag = 1;
			}
			else if (token[1] == "UNKNOWN")
				this->_allow_methods_flag = -1;
			else
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_ALLOW_METHODS, *line, i);
				throw (this->_err_msg);
			}
		}
		else if (this->_allow_methods_flag == 2)
		{
			if (SemicolonCheck(token[2]))
			{
				if (!(token[2].find(";") == std::string::npos))
				{
					this->_err_msg = ErrMsg(this->_config_file_name, SERVER_SEMICOLON, *line, i);
					throw (this->_err_msg);
				}
			}
			if (!(token[2] == ";"))
			{
				token[2] = token[2].substr(0, token[2].find(";"));
				token[2] = RemoveSpaceTab(token[2]);
			}

			if (token[1] == "GET" && token[2] == ";")
			{
				this->_allow_methods_get = 1;
				this->_allow_methods_flag = 1;
			}
			else if (token[1] == "POST" && token[2] == ";")
			{
				this->_allow_methods_post = 1;
				this->_allow_methods_flag = 1;
			}
			else if (token[1] == "DELETE" && token[2] == ";")
			{
				this->_allow_methods_delete = 1;
				this->_allow_methods_flag = 1;
			}
			else if (token[1] == "UNKNOWN" && token[2] == ";")
				this->_allow_methods_flag = -1;
			else if ((token[1] == "GET" && token[2] == "POST")
				|| (token[1] == "POST" && token[2] == "GET"))
			{
				this->_allow_methods_get = 1;
				this->_allow_methods_post = 1;
				this->_allow_methods_flag = 1;
			}
			else if ((token[1] == "GET" && token[2] == "DELETE")
				|| (token[1] == "DELETE" && token[2] == "GET"))
			{
				this->_allow_methods_get = 1;
				this->_allow_methods_delete = 1;
				this->_allow_methods_flag = 1;
			}
			else if ((token[1] == "POST" && token[2] == "DELETE")
				|| (token[1] == "DELETE" && token[2] == "POST"))
			{
				this->_allow_methods_post = 1;
				this->_allow_methods_delete = 1;
				this->_allow_methods_flag = 1;
			}
			else
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_ALLOW_METHODS, *line, i);
				throw (this->_err_msg);
			}
		}
		else if (this->_allow_methods_flag == 3)
		{
			if (SemicolonCheck(token[3]))
			{
				if (!(token[3].find(";") == std::string::npos))
				{
					this->_err_msg = ErrMsg(this->_config_file_name, SERVER_SEMICOLON, *line, i);
					throw (this->_err_msg);
				}
			}
			if (!(token[3] == ";"))
			{
				token[3] = token[3].substr(0, token[3].find(";"));
				token[3] = RemoveSpaceTab(token[3]);
			}

			if ((token[1] == "GET" && token[2] == "POST" && token[3] == ";")
				|| (token[1] == "POST" && token[2] == "GET" && token[3] == ";"))
			{
				this->_allow_methods_get = 1;
				this->_allow_methods_post = 1;
				this->_allow_methods_flag = 1;
			}
			else if ((token[1] == "GET" && token[2] == "DELETE" && token[3] == ";")
				|| (token[1] == "DELETE" && token[2] == "GET" && token[3] == ";"))
			{
				this->_allow_methods_get = 1;
				this->_allow_methods_delete = 1;
				this->_allow_methods_flag = 1;
			}
			else if ((token[1] == "POST" && token[2] == "DELETE" && token[3] == ";")
				|| (token[1] == "DELETE" && token[2] == "POST" && token[3] == ";"))
			{
				this->_allow_methods_post = 1;
				this->_allow_methods_delete = 1;
				this->_allow_methods_flag = 1;
			}
			else if ((token[1] == "GET" && token[2] == "POST" && token[3] == "DELETE")
				|| (token[1] == "GET" && token[2] == "DELETE" && token[3] == "POST")
				|| (token[1] == "POST" && token[2] == "GET" && token[3] == "DELETE")
				|| (token[1] == "POST" && token[2] == "DELETE" && token[3] == "GET")
				|| (token[1] == "DELETE" && token[2] == "GET" && token[3] == "POST")
				|| (token[1] == "DELETE" && token[2] == "POST" && token[3] == "GET"))
			{
				this->_allow_methods_get = 1;
				this->_allow_methods_post = 1;
				this->_allow_methods_delete = 1;
				this->_allow_methods_flag = 1;
			}
			else
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_ALLOW_METHODS, *line, i);
				throw (this->_err_msg);
			}
		}
		else
		{
			if (SemicolonCheck(token[4]))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_SEMICOLON, *line, i);
				throw (this->_err_msg);
			}

			if ((token[1] == "GET" && token[2] == "POST" && token[3] == "DELETE" && token[4] == ";")
				|| (token[1] == "GET" && token[2] == "DELETE" && token[3] == "POST" && token[4] == ";")
				|| (token[1] == "POST" && token[2] == "GET" && token[3] == "DELETE" && token[4] == ";")
				|| (token[1] == "POST" && token[2] == "DELETE" && token[3] == "GET" && token[4] == ";")
				|| (token[1] == "DELETE" && token[2] == "GET" && token[3] == "POST" && token[4] == ";")
				|| (token[1] == "DELETE" && token[2] == "POST" && token[3] == "GET" && token[4] == ";"))
			{
				this->_allow_methods_get = 1;
				this->_allow_methods_post = 1;
				this->_allow_methods_delete = 1;
				this->_allow_methods_flag = 1;
			}
			else
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_ALLOW_METHODS, *line, i);
				throw (this->_err_msg);
			}
		}
	}
	else if (token[0] == "save_path" && !this->_server_parse_done)
	{
		//path check
		if (SemicolonCheck(token[1]))
		{
			if (!(token[2] != "" && token[1].find(";") == std::string::npos && !SemicolonCheck(token[2])))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_SEMICOLON, *line, i);
				throw (this->_err_msg);
			}
		}
		if (token[2] == "")
		{
			token[1] = token[1].substr(0, token[1].find(";"));
			token[1] = RemoveSpaceTab(token[1]);
		}
		this->_save_path_flag++;
		this->_save_path = HttpBlockParse::GetRoot() + token[1];
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageHeaders.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:24:00 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/04 23:24:03 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MessageHeaders.hpp"

MessageHeaders::MessageHeaders()
{
}

MessageHeaders::~MessageHeaders()
{
}

std::string	stripMarginWhitespace(const std::string &s)
{
	const	char	*whitespace = " \t\r\n";
	std::size_t		marginLeft;
	std::size_t		marginRight;

	marginLeft = s.find_first_not_of(whitespace);
	marginRight = s.find_last_not_of(whitespace);
	if (marginLeft == std::string::npos)
		return "";
	else
		return s.substr(marginLeft, marginRight - marginLeft + 1);
}

bool	MessageHeaders::parseFromString(const std::string &rawMsg){
	std::size_t	offset = 0;
	std::size_t lineTerminator;
	std::size_t nameTerminator;
	std::string	rest;
	std::string	header;
	std::string	endl = "\r\n";

	lineTerminator = rawMsg.find(endl, offset);
	if (lineTerminator != std::string::npos)
		rest = rawMsg;
	while (lineTerminator != std::string::npos)
	{
		if (lineTerminator == 0)
			break;
		header = rest.substr(0, lineTerminator);
		nameTerminator = header.find(":");
		if (nameTerminator == std::string::npos)
			return false;
		Header tmp;
		tmp.name = stripMarginWhitespace(header.substr(0, nameTerminator));
		tmp.value = stripMarginWhitespace(header.substr(nameTerminator + 1));
		headers.emplace_back(tmp);
		rest = rest.substr(lineTerminator + endl.length());
		lineTerminator = rest.find(endl, offset);
	}
	body = rest.substr(endl.length());
	return (true);
}

MessageHeaders::Headers	MessageHeaders::getHeaders() const{
	return (headers);
}

bool	MessageHeaders::hasHeader(const std::string& name) const{
	for (unsigned i=0; i != headers.size(); i++)
	{
		if (headers[i].name == name)
			return (true);
	}
	return (false);
}

std::string	MessageHeaders::getBody() const{
	return (body);
}

std::string	MessageHeaders::generateRawMsg(){
	std::ostringstream buffer;

	for (unsigned i=0; i != headers.size(); i++)
	{
		buffer << headers[i].name << ": " << headers[i].value << "\r\n";
	}	
	buffer << "\r\n";
	buffer << body;
	return (buffer.str());
}
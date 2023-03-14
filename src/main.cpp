/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:44:30 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/14 10:26:24 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include <csignal>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8000

void	signalHandler(int signum)
{
	(void) signum;
	std::cout << "\nLeaving the server...Bye!" << std::endl;
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	signal(SIGINT, signalHandler);

	(void)			av;
	(void)			env;
	Server			server;
	int				clientSocket;
	int				serverSocket;
	fd_set			currentSockets, readySockets;
	if (ac != 2)
	{
		std::cerr << "Need 1 config file OR default path." << std::endl;
		return (EXIT_FAILURE);
	}
	serverSocket = server.startListen("127.0.0.1", PORT);
	if (serverSocket < 0)
		return (EXIT_FAILURE);

	FD_ZERO(&currentSockets);
	FD_SET(serverSocket, &currentSockets);
	while (true)
	{
		readySockets = currentSockets;
		if (select(FD_SETSIZE, &readySockets, NULL, NULL, NULL) <= 0)
		{
			std::cerr << "Select Error" << std::endl;
			return (EXIT_FAILURE);
		}
		for (int i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, &readySockets)){
				if (i == serverSocket)
				{
					clientSocket = server.acceptConnection();
					if (clientSocket < 0)
						return (EXIT_FAILURE);
					FD_SET(clientSocket, &currentSockets);
					printf("clientSocket: %d\n", clientSocket);
				}
				else
				{
					printf("New Connection!\n");
					server.newConnection(i);
					FD_CLR(i, &currentSockets);
				}
			}
		}
	}
   return (EXIT_SUCCESS);
}
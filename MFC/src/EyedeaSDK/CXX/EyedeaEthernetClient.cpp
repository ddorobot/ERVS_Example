#include "EyedeaEthernetClient.h"
#include "EyedeaErrorType.h"
#include <string>

CEyedeaEthernetClient::CEyedeaEthernetClient(void) :
	m_s(NULL)
	,m_resolver(NULL)

{
	//m_s = new tcp::socket(m_io_service);
	//m_resolver = new tcp::resolver(m_io_service);

	//boost::asio::connect(*m_s, m_resolver->resolve({ ip, port }));
#if 0
	client_socket = INVALID_SOCKET;

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
	{
		printf("error WSAStartup\n");
	}

	client_socket = socket(PF_INET, SOCK_STREAM, 0);

	if (client_socket == -1) {
		printf("[eyedea] Socket Open failed\n");
	}
	else {
		memset(&server_addr, 0, sizeof(server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(PORT);
		//server_addr.sin_addr.s_addr = inet_addr(IPADDR);
		server_addr.sin_addr.s_addr = inet_addr(IPADDR);

		if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
			printf("[eyedea] Socket connect error\n");
			closesocket(client_socket);
		}
	}
#endif
}

CEyedeaEthernetClient::~CEyedeaEthernetClient(void)
{
	if (m_s != NULL)
	{
		delete m_s;
		m_s = NULL;
	}

	if (m_resolver != NULL)
	{
		delete m_resolver;
		m_resolver = NULL;
	}

	if (m_timer != NULL)
	{
		delete m_timer;
		m_timer = NULL;
	}

	if (m_io_service != NULL)
	{
		delete m_io_service;
		m_io_service = NULL;
	}
}

int CEyedeaEthernetClient::Open(char* ip, int port)
{
	boost::system::error_code ec;

	m_io_service = new io_service();
	m_s = new tcp::socket(*m_io_service);
	m_resolver = new tcp::resolver(*m_io_service);
	m_timer = new deadline_timer(*m_io_service);


	//boost::asio::connect(*m_s, m_resolver->resolve({ ip, "4000" }), ec);
	//boost::asio::connect(*m_s, m_resolver->resolve({ ip, std::to_string(port) }), ec);
	try
	{
		m_s->async_connect(tcp::endpoint(ip::address::from_string(ip), port), boost::bind(&CEyedeaEthernetClient::handle_connect, this, boost::asio::placeholders::error));
		//m_s->async_connect(tcp::endpoint(ip::address::from_string(ip), port), boost::bind(&CEyedeaEthernetClient::handle_connect));

		m_timer->expires_from_now(boost::posix_time::seconds(3));
		m_timer->async_wait(boost::bind(&CEyedeaEthernetClient::Close, this));

		do {
			m_io_service->run_one();
		} while (ec == boost::asio::error::would_block);
		if (ec || !m_s->is_open())
		{
			//cout << "error happend in socket connect" << endl;

			delete m_s;
			m_s = NULL;
			return EYEDEA_ERROR_SOCKET_CONNECT;
		}
		m_timer->cancel();
	}
	catch (boost::system::system_error const &e)
	{
		//cout << "Warning : could not connect : " << e.what() << endl;
		//Close();
		delete m_s;
		m_s = NULL;
		return EYEDEA_ERROR_SOCKET_CONNECT;
	}

	return EYEDEA_SUCCESS;

}

int CEyedeaEthernetClient::handle_connect(const boost::system::error_code& err)
{
	//cout << "handle_connect call " << err << endl;

	if (err)
	{
		//fail
		throw boost::system::system_error(
			err ? err : boost::asio::error::operation_aborted);
		return -1;
	}
	else
	{
		//success
		return 1;
	}
}


void CEyedeaEthernetClient::Close()
{
#if 0
	closesocket(client_socket);
#endif

	//cout << "close call" << endl;
	//m_s->cancel();
	m_s->close();
	delete m_timer;
	//delete m_s;
	delete m_resolver;
	delete m_io_service;
	m_timer = NULL;
	//m_s = NULL;
	m_resolver = NULL;
	m_io_service = NULL;
}

int CEyedeaEthernetClient::Send(char command, unsigned int* scalefactor, unsigned char** out_data, int* len) 
{
#if 0
	if (client_socket < 0)
	{
		*len = 0;
		return ;
	}
#else
	if (m_s == NULL || m_resolver == NULL)
	{
		*len = 0;
		return EYEDEA_ERROR_INVALID_MEMORY;
	}
#endif

	int cnt = 0;
	//char recvbuf[DEFAULT_BUFLEN];
	//char buf[DEFAULT_BUFLEN];
	//if ((*out_data) == NULL)
	//{
	//	return;
	//}

	//cout << "data send" << ":" << command << " " << sizeof(command) << endl;
	//write(client_socket, &command, sizeof(command));

	unsigned int leng = (*len);
	if (command == COMMAND_GET_ZOOM_IMAGE || command == COMMAND_GET_IMAGE || command == COMMAND_GET_BASE_IMAGE ||
		command == COMMAND_GET_RESULT_IMAGE || command == COMMAND_GET_RESULT_IMAGE_LOCAL || command == COMMAND_GET_RESULT_IMAGE_GLOBAL ||
		command == COMMAND_GET_OBJECT_IMAGE || command == GET_IMAGE_SEARCH_AREA_INFO )
	{
		leng = 0;
	}
	else if (command == COMMAND_GET_IMAGE_W_OPTION || command == COMMAND_GET_RESULT_IMAGE_FIND_OBJECTS)
	{
		leng = 8;
	}
	else if (command == COMMAND_CALIBRATION_GET_IMAGE || command == COMMAND_GET_FIND_OBJECT_IMAGE )
	{
		leng = 4;
	}

	//printf("command = %d\n", command);

	unsigned char *m_command = NULL;
	m_command = new unsigned char[18 + leng];

	m_command[0] = 'd';
	m_command[1] = 'o';
	m_command[2] = 'o';
	m_command[3] = 's';
	m_command[4] = 'a';
	m_command[5] = 'n';
	m_command[6] = command;

	//scale factor
	m_command[7] = (unsigned char)(((*scalefactor) & 0xFF000000) >> 24);
	m_command[8] = (unsigned char)(((*scalefactor) & 0x00FF0000) >> 16);
	m_command[9] = (unsigned char)(((*scalefactor) & 0x0000FF00) >> 8);
	m_command[10] = (unsigned char)(((*scalefactor) & 0x000000FF));

	if (leng <= 0) leng = 0;

	m_command[11] = (unsigned char)((leng & 0xFF000000) >> 24);
	m_command[12] = (unsigned char)((leng & 0x00FF0000) >> 16);
	m_command[13] = (unsigned char)((leng & 0x0000FF00) >> 8);
	m_command[14] = (unsigned char)((leng & 0x000000FF));

	if (leng > 0)
	{
		memcpy(m_command + 15, (*out_data), leng);
	}

	m_command[15 + leng + 0] = 'D';
	m_command[15 + leng + 1] = 'R';
	m_command[15 + leng + 2] = 'A';

	if (m_command != NULL)
	{
		//send(client_socket, &command, sizeof(command), 0);
		//printf("sizeof(m_command) = %d\n", sizeof(m_command));

#if 0
		send(client_socket, m_command, sizeof(char)*(2+(*len)), 0);
#else
		//printf("send len = %d\n", sizeof(char)*(2 + (*len)));
		//printf("m_command[0] = %d\n", m_command[0]);
		//printf("m_command[1] = %d\n", m_command[1]);
        try{
       		boost::asio::write(*m_s, boost::asio::buffer(m_command, sizeof(unsigned char)*(leng+18)));
        }
        catch(exception& e)
        {
        	m_s->close();
        	m_resolver = NULL;
            return EYEDEA_ERROR_SOCKET_WRITE;
        }

#endif

		delete m_command;
		m_command = NULL;

		int get_size = 0;
		
		//unsigned char get_data[5];
		//int get_data_index = 0;

		unsigned char* buf = NULL;

		unsigned char get_command = 0;
		do
		{
			do
			{
#if 1
				//cnt = recv(client_socket, m_buf, DEFAULT_BUFLEN, 0);
				//cnt = recv(client_socket, m_buf, DEFAULT_BUFLEN, 0);
                try{
				    boost::system::error_code error;
    				//cnt = m_s->read_some(boost::asio::buffer(m_buf), error);
	    			//cnt = m_s->read_some(boost::asio::buffer(m_buf), error);
		    		cnt = m_s->receive(boost::asio::buffer(m_buf));
			    	//cnt = m_s->async_read_some(boost::asio::buffer(m_buf), error);

    				if (error == boost::asio::error::eof)
	    				break; // Connection closed cleanly by peer.
		    		else if (error)
			    		throw boost::system::system_error(error); // Some other error.
                }
                catch(exception& e)
                {
                	m_s->close();
                	m_resolver = NULL;
                    m_cls_check_data.init_variable();
                    return EYEDEA_ERROR_SOCKET_READ;
                }


				int out_size = 0;
				buf = m_cls_check_data.FindData(m_buf, cnt, &out_size);
			} while (buf == NULL);

			get_command = buf[0];
		} while (get_command != command);

		//-------------------------------------------------------------
		//head data
		unsigned int i_get_data = (unsigned int)buf[1];
		unsigned int scale_factor = (i_get_data << 24) & 0xFF000000;
		i_get_data = (unsigned int)buf[2];
		scale_factor |= (i_get_data << 16) & 0x00FF0000;
		i_get_data = (unsigned int)buf[3];
		scale_factor |= (i_get_data << 8) & 0x0000FF00;
		i_get_data = (unsigned int)buf[4];
		scale_factor |= (i_get_data) & 0x000000FF;

		i_get_data = (unsigned int)buf[5];
		unsigned int data_length = (i_get_data << 24) & 0xFF000000;
		i_get_data = (unsigned int)buf[6];
		data_length |= (i_get_data << 16) & 0x00FF0000;
		i_get_data = (unsigned int)buf[7];
		data_length |= (i_get_data << 8) & 0x0000FF00;
		i_get_data = (unsigned int)buf[8];
		data_length |= (i_get_data) & 0x000000FF;
		//head data
		//-------------------------------------------------------------

		if (data_length > (*len))
		{
			if ((*out_data) != NULL)
			{
				delete (*out_data);
				(*out_data) = NULL;
			}

			//printf("new data\n");

			(*out_data) = new unsigned char[data_length];
		}
		//printf("get_command = %d\n", get_command);
		//printf(" = data_length = %d\n", data_length);

		//if (data_length > 0)
		{
			*len = data_length;
			memcpy((*out_data), buf+9, data_length);
			*scalefactor = scale_factor;
		}

#if 1
#endif

#else
			//cnt = boost::asio::read(*m_s, boost::asio::buffer(m_buf, DEFAULT_BUFLEN2));

			//printf("command = %d\n", command);

			if (command == COMMAND_SET_SEARCH_AREA	|| command == COMMAND_SET_MASTER_AREA || 
				command == COMMAND_SET_OPTION		|| command == COMMAND_SET_BASE || 
				command == COMMAND_SET_NEXT_IMAGE	|| command == COMMAND_SET_OBJECT_POSITION ||
				command == COMMAND_SAVE_INFORMATION || command == COMMAND_LOAD_INFORMATION ||
				command == COMMAND_SET_OBJECT_CIRCLE ) break;

			//cnt = recv(client_socket, m_buf, DEFAULT_BUFLEN, 0);
#if 0
			cnt = recv(client_socket, m_buf, DEFAULT_BUFLEN, 0);
#else
			//cnt = recv(client_socket, m_buf, DEFAULT_BUFLEN, 0);
			//cnt = boost::asio::read(*m_s, boost::asio::buffer(m_buf, 12));
			boost::system::error_code error;
			//cnt = m_s->read_some(boost::asio::buffer(m_buf), error);
			cnt = m_s->read_some(boost::asio::buffer(m_buf), error);

			//int length = m_s->read_some(boost::asio::buffer(m_buf), error);
#endif
			if (cnt < 0) break;

			if (command == COMMAND_GET_IMAGE			|| command == COMMAND_GET_OBJECT_IMAGE || 
				command == COMMAND_GET_USER_AREA_IMAGE	|| command == COMMAND_GET_BASE_IMAGE ||
				command == COMMAND_GET_RESULT_IMAGE		|| command == COMMAND_GET_ZOOM_IMAGE ||
				command == COMMAND_GET_RESULT_IMAGE_LOCAL || command == COMMAND_GET_RESULT_IMAGE_GLOBAL)
			{
				memcpy((*out_data) + get_size, m_buf, cnt);
				get_size += cnt;

				if (get_size >= 640 * 480 * 3)
				{
					break;
				}
			}
			else if (command == COMMAND_GET_SEARCH_AREA || command == COMMAND_GET_MASTER_AREA)
			{
				memcpy((*out_data) + get_size, m_buf, cnt);
				get_size += cnt;

				if (get_size >= 16 )
				{
					break;
				}
			}
			else if (command == COMMAND_GET_CIRCLE_INFO || command == COMMAND_GET_MAIN_OBJECT_INFO)
			{
				memcpy((*out_data) + get_size, m_buf, cnt);
				get_size += cnt;

				if (get_size >= 12)
				{
					break;
				}
			}
			else if (command == COMMAND_RUN_FIND_OBJECT_WITHOUT_PCA || command == COMMAND_RUN_FIND_OBJECT_WITH_PCA)
			{
				memcpy((*out_data) + get_size, m_buf, cnt);
				get_size += cnt;

				if (get_size >= 1)
				{
					break;
				}
			}
#endif
	}
    return EYEDEA_SUCCESS;
}

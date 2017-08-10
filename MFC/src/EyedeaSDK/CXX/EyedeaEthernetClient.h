#ifndef _EYEDEA_ETHERNET_CLIENT_H_
#define _EYEDEA_ETHERNET_CLIENT_H_

//#define _WINSOCK_DEPRECATED_NO_WARNINGS

//#include <sys/socket.h>
#include <string>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
//#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
#include <iostream>
//#include <winsock.h>
//#include <winsock2.h>

#include <stdint.h>
//typedef uint32_t socklen_t;

#include "EyedeaCheckData.h"
#include "EyedeaDef.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

using namespace boost::asio;
using boost::asio::ip::tcp;
using namespace std;

#define PORT "4000"
#define IPADDR "192.168.56.1"
//#define IPADDR "192.168.123.77"
//#define IPADDR "192.168.123.60"
//#define IPADDR "192.168.123.60"

using namespace std;

#define DEFAULT_BUFLEN 4096
#define DEFAULT_BUFLEN2 1024

enum Comand
{
	COMMAND_GET_IMAGE = 1,
	COMMAND_GET_SEARCH_AREA,
	COMMAND_SET_SEARCH_AREA,
	COMMAND_GET_MASTER_AREA,
	COMMAND_SET_MASTER_AREA,
	COMMAND_GET_OBJECT_IMAGE,
	COMMAND_GET_USER_AREA_IMAGE,
	COMMAND_SET_OPTION,
	COMMAND_RUN_FIND_OBJECT_WITHOUT_PCA,
	COMMAND_SET_BASE=10,
	COMMAND_GET_BASE_IMAGE,
	COMMAND_GET_RESULT_IMAGE,
	COMMAND_SET_NEXT_IMAGE,
	COMMAND_SET_OBJECT_POSITION,
	COMMAND_GET_ZOOM_IMAGE,
	COMMAND_RUN_FIND_OBJECT_WITH_PCA,
	COMMAND_GET_RESULT_IMAGE_LOCAL,
	COMMAND_GET_RESULT_IMAGE_GLOBAL,
	COMMAND_GET_CIRCLE_INFO,
	COMMAND_GET_MAIN_OBJECT_INFO=20,
	COMMAND_SAVE_INFORMATION,
	COMMAND_LOAD_INFORMATION,
	COMMAND_SET_OBJECT_CIRCLE,
	COMMAND_GET_OPTION,
	COMMAND_CHECKDEFECT_USEROPTION,
	COMMAND_CHECKDEFECT,
	COMMAND_CHECKDEFECT_SET,
	COMMAND_CHECKDEFECT_GET,
	COMMAND_CHECKDEFECT_LIST,
	COMMAND_CHECKDEFECT_LIST_DEL=30,
	COMMAND_CHECKDEFECT_LIST_FILESAVE,
	COMMAND_CHECKDEFECT_LIST_FILELOAD,
	COMMAND_OBJECT_SET,
	COMMAND_OBJECT_GET,
	COMMAND_OBJECT_LIST_DEL,
	COMMAND_OBJECT_LIST_FILESAVE,
	COMMAND_OBJECT_LIST_FILELOAD,
	COMMAND_RUN_FIND_ALL_OBJECT_WITH_PCA,
	COMMAND_SET_SELECT_LIST_BY_ID,
	COMMAND_VISION_CONFIG_SET=40,
	COMMAND_VISION_CONFIG_GET,
	COMMAND_RUN_FIND_OBJECT,
	COMMAND_GET_OBJECT_POSITION,
	COMMAND_GET_OBJECT,
	COMMAND_GET_IMAGE_W_OPTION,
	COMMAND_GET_BASE_INFO,
	COMMAND_SET_ENV,
	COMMAND_GET_RESULT_INFO,
	COMMAND_GET_MODE,
	COMMAND_SET_MODE=50,
	COMMAND_SELECT_BASE_OBJECT,
	COMMAND_GET_FIND_OBJECT_COUNT,
	COMMAND_GET_FIND_OBJECT_INFO,
	COMMAND_GET_FIND_OBJECT_ANGLE,
	COMMAND_GET_FIND_OBJECT_TYPE_FROM_DB,
	COMMAND_GET_TEACH_COUNT,
	COMMAND_GET_TEACH_SUB_COUNT,
	COMMAND_DB_ADD_OBJECT,
	COMMAND_RESET_OBJECT,
	COMMAND_SET_OBJECT=60,
	COMMAND_GET_TEACH_SUB_INFO,
	COMMAND_DB_ADD_SUB_OBJECT,
	COMMAND_CALIBRATION_ADD,
	COMMAND_CALIBRATION_GET_COUNT,
	COMMAND_CALIBRATION_GET_IMAGE,
	COMMAND_CALIBRATION_GET_INFO,
	COMMAND_CALIBRATION_DEL,
	COMMAND_CALIBRATION_CLEAR,
	COMMAND_CALIBRATION_RUN,
	COMMAND_CALIBRATION_GEPOINT=70,
	COMMAND_CALIBRATION_IS_OK,
	COMMAND_GET_CIRCLE_INFO_CAMERA_BASE,
	COMMAND_GET_CIRCLE_INFO_ROBOT_BASE,
	COMMAND_SET_LOG,
	COMMAND_VISION_CONFIG_FILE_SAVE,
	COMMAND_VISION_CONFIG_FILE_LOAD,
	COMMAND_GET_VERSION,
	COMMAND_CALIBRATION_SAVE,
	COMMAND_CALIBRATION_LOAD,
	COMMAND_DB_GET_COUNT=80,
	COMMAND_DB_GET_ID,
	COMMAND_DB_GET_SELECT_ID,
	COMMAND_DB_DEL_ID,
	COMMAND_DB_GET_MODE,
	COMMAND_BASE_SET_GLOBAL_CONFIG,
	COMMAND_BASE_SET_LOCAL_CONFIG,
	COMMAND_GET_FIND_OBJECT_POSE,
	COMMAND_GET_FIND_OBJECT_IMAGE,
	COMMAND_GET_FIND_OBJECT_INFO2,
	COMMAND_SET_CAMERA_CONFIG = 90,
	COMMAND_BACKGROUND_LEARN,
	COMMAND_FIND_SEARCH_AREA,
	COMMAND_SEARCH_AREA_SET_LOCAL_CONFIG,
	COMMAND_SET_ZOOM_AREA,
	COMMAND_RESET_ZOOM_AREA,
	COMMAND_GET_RESULT_IMAGE_FIND_OBJECTS,
	COMMAND_GET_FIND_OBJECT_INFO_RESULT
};

class  CEyedeaEthernetClient
{
public:
	CEyedeaEthernetClient(void);
	~CEyedeaEthernetClient(void);

	int Send(char command, unsigned int* scalefactor, unsigned char** out_data, int* len);
	int Open(char* ip, int port);
	void Close();
	int handle_connect(const boost::system::error_code& err);

private:
	//int client_socket;
	//SOCKET client_socket;
	//struct sockaddr_in server_addr;
	//boost::asio::io_service m_io_service;
	boost::asio::io_service *m_io_service;
	tcp::socket *m_s;
	tcp::resolver *m_resolver;
	deadline_timer *m_timer;

	//char *m_buf;
	char m_buf[DEFAULT_BUFLEN2];

	CEyedeaCheckData m_cls_check_data;
};

#endif

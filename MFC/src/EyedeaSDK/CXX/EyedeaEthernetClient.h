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
	COMMAND_SET_OPTION,
	COMMAND_SET_BASE,
	COMMAND_SET_NEXT_IMAGE,
	COMMAND_SET_OBJECT_CIRCLE,
	COMMAND_GET_OPTION,
	COMMAND_OBJECT_LIST_FILESAVE,
	COMMAND_OBJECT_LIST_FILELOAD,
	COMMAND_VISION_CONFIG_SET,
	COMMAND_VISION_CONFIG_GET,
	COMMAND_GET_IMAGE_W_OPTION,
	COMMAND_SELECT_BASE_OBJECT,
	COMMAND_GET_FIND_OBJECT_INFO,
	COMMAND_GET_FIND_OBJECT_ANGLE,
	COMMAND_GET_FIND_OBJECT_TYPE_FROM_DB,
	COMMAND_GET_TEACH_COUNT,
	COMMAND_DB_ADD_OBJECT,
	COMMAND_SET_OBJECT,
	COMMAND_CALIBRATION_ADD,
	COMMAND_CALIBRATION_GET_COUNT,
	COMMAND_CALIBRATION_GET_IMAGE,
	COMMAND_CALIBRATION_GET_INFO,
	COMMAND_CALIBRATION_DEL,
	COMMAND_CALIBRATION_CLEAR,
	COMMAND_CALIBRATION_RUN,
	COMMAND_CALIBRATION_GEPOINT,
	COMMAND_CALIBRATION_IS_OK,
	COMMAND_GET_VERSION,
	COMMAND_CALIBRATION_SAVE,
	COMMAND_CALIBRATION_LOAD,
	COMMAND_DB_GET_COUNT,
	COMMAND_DB_GET_ID,
	COMMAND_DB_GET_SELECT_ID,
	COMMAND_DB_DEL_ID,
	COMMAND_DB_GET_MODE,
	COMMAND_SET_CAMERA_CONFIG,
	COMMAND_BACKGROUND_LEARN,
	COMMAND_SET_ZOOM_AREA,
	COMMAND_RESET_ZOOM_AREA,
	COMMAND_GET_RESULT_IMAGE_FIND_OBJECTS,
	COMMAND_GET_FIND_OBJECT_INFO_RESULT,
	COMMAND_CALIBRATION_GETCHESSPOINT,
	COMMAND_CALIBRATION_COPY,
	COMMAND_SET_OBJECT_LINE,
	COMMAND_CALIBRATION_GET_ID,
	COMMAND_GEOMETRY_DISTANCE,
	COMMAND_GEOMETRY_ANGLE,
	COMMAND_GEOMETRY_CLEAR,
	COMMAND_SET_MASK_AREA,
	COMMAND_UNDO_MASK_AREA,
	COMMAND_DEL_MASK_AREA,
	COMMAND_CAMERA_CONFIG_GET,
	COMMAND_CAMERA_CONFIG_SET,
	COMMAND_CAMERA_CONFIG_SAVE,
	COMMAND_CAMERA_CONFIG_LOAD,
	COMMAND_CAMERA_CONFIG_SET_DEFAULT,
	COMMAND_CAMERA_CONFIG_SAVE_WITH_ID,
	COMMAND_CAMERA_CONFIG_LOAD_WITH_ID,
	COMMAND_HISTOGRAM_SET_RANGE,
	COMMAND_HISTOGRAM_GET_RANGE,
	COMMAND_HISTOGRAM_GET_GRAPH,
	COMMAND_HISTOGRAM_SET_USE_ELEMENT,
	COMMAND_HISTOGRAM_GET_USE_ELEMENT,
	COMMAND_HISTOGRAM_GET_PIXEL_COUNT_RESULT,
	COMMAND_HISTOGRAM_GET_PIXEL_COUNT_ID,
	COMMAND_HISTOGRAM_SET_INSPECTION_PIXEL_COUNT,
	COMMAND_HISTOGRAM_GET_INSPECTION_PIXEL_COUNT,
	COMMAND_HISTOGRAM_SET_INSPECTION_PIXEL_COUNT_TOL_RATE,
	COMMAND_HISTOGRAM_GET_INSPECTION_PIXEL_COUNT_TOL_RATE,
	COMMAND_GEOMETRY_GET_DISTANCE,
	COMMAND_GEOMETRY_SET_INSPECTION_DISTANCE,
	COMMAND_GEOMETRY_GET_INSPECTION_DISTANCE,
	COMMAND_GEOMETRY_SET_INSPECTION_DISTANCE_TOL_RATE,
	COMMAND_GEOMETRY_GET_INSPECTION_DISTANCE_TOL_RATE,
	COMMAND_GEOMETRY_GET_ANGLE,
	COMMAND_GEOMETRY_SET_INSPECTION_ANGLE,
	COMMAND_GEOMETRY_GET_INSPECTION_ANGLE,
	COMMAND_GEOMETRY_SET_INSPECTION_ANGLE_TOL_RATE,
	COMMAND_GEOMETRY_GET_INSPECTION_ANGLE_TOL_RATE,
	COMMAND_GEOMETRY_GET_MEET_POINT,
	COMMAND_SET_JOB_NAME,
	COMMAND_GET_JOB_NAME,
	COMMAND_SET_TOOL_NAME,
	COMMAND_GET_TOOL_NAME,
	COMMAND_SET_TOOL_TYPE,
	COMMAND_GET_TOOL_TYPE,
	COMMAND_SET_TOOL_STATE,
	COMMAND_GET_TOOL_STATE,
	COMMAND_SET_ROBOT_POSE,
	COMMAND_GET_ROBOT_POSE,
	COMMAND_SET_OBJECT_TWO_LINE,
	COMMAND_SET_OBJECT_TWO_LINE_BASE_DISTANCE,
	COMMAND_GET_OBJECT_TWO_LINE_BASE_DISTANCE,
	COMMAND_GET_OBJECT_TWO_LINE_CALC_DISTANCE,
	COMMAND_SET_OBJECT_TWO_LINE_DISTANCE_TOL,
	COMMAND_GET_OBJECT_TWO_LINE_DISTANCE_TOL,
	COMMAND_SET_OBJECT_TWO_LINE_DISTANCE_TYPE,
	COMMAND_GET_OBJECT_TWO_LINE_DISTANCE_TYPE,
	COMMAND_SET_OBJECT_TWO_LINE_DISTANCE_INSPECTION_USE,
	COMMAND_GET_OBJECT_TWO_LINE_DISTANCE_INSPECTION_USE,
	COMMAND_DEL_OBJECT_LINE,
	COMMAND_CLR_OBJECT_LINE,
	COMMAND_SET_OBJECT_TWO_LINE_BASE_ANGLE,
	COMMAND_GET_OBJECT_TWO_LINE_BASE_ANGLE,
	COMMAND_GET_OBJECT_TWO_LINE_CALC_ANGLE,
	COMMAND_SET_OBJECT_TWO_LINE_ANGLE_TOL,
	COMMAND_GET_OBJECT_TWO_LINE_ANGLE_TOL,
	COMMAND_SET_OBJECT_TWO_LINE_ANGLE_INSPECTION_USE,
	COMMAND_GET_OBJECT_TWO_LINE_ANGLE_INSPECTION_USE,
	COMMAND_SET_OBJECT_CIRCLE_WITH_BOUND,
	COMMAND_SET_OBJECT_CIRCLE_BASE_DIAMETER,
	COMMAND_GET_OBJECT_CIRCLE_BASE_DIAMETER,
	COMMAND_SET_OBJECT_CIRCLE_DIAMETER_TOL,
	COMMAND_GET_OBJECT_CIRCLE_DIAMETER_TOL,
	COMMAND_SET_OBJECT_CIRCLE_DIAMETER_INSPECTION_USE,
	COMMAND_GET_OBJECT_CIRCLE_DIAMETER_INSPECTION_USE,
	COMMAND_GET_OBJECT_CIRCLE_CALC_DIAMETER,
	COMMAND_HISTOGRAM_SET_INSPECTION_PIXEL_COUNT_TOL,
	COMMAND_HISTOGRAM_GET_INSPECTION_PIXEL_COUNT_TOL,
	COMMAND_GET_FIND_OBJECT_INFO2,
	COMMAND_CALC_FOCUS_RATE,
	COMMAND_SET_FOCUS_RATE,
	COMMAND_GET_FOCUS_RATE,
	COMMAND_CALC_CONTRAST_RATE,
	COMMAND_SET_CONTRAST_RATE,
	COMMAND_GET_CONTRAST_RATE,
	COMMAND_CALIB_STANDALONE_INIT,	
	COMMAND_CALIB_STANDALONE_RUN,
	COMMAND_CALIB_STANDALONE_GET_IMAGE_COUNT,
	COMMAND_CALIB_STANDALONE_GET_FEATURE_POSE,
	COMMAND_CALIB_STANDALONE_SET_CALIB_MAT,
	COMMAND_CALIB_STANDALONE_GET_CALIB_MAT,
	COMMAND_CALIB_STANDALONE_CALC_CALIB_MAT,
	COMMAND_GET_DETECT_DATA,
	COMMAND_SET_DETECT_DATA_INIT,
	COMMAND_GET_DETECT_DATA_INIT,
	COMMAND_GET_SELECT_BASE_OBJECT,
	COMMAND_GET_MASK_AREA,
	COMMAND_GET_OBJECT_CIRCLE_WITH_BOUND,
	COMMAND_GET_OBJECT_LINE,
	COMMAND_SET_BASE_TEMP,
	COMMAND_GET_SAVE_DB_INFO_LIST,
	COMMAND_SET_BASE_JOB_DETECTION_RETRY,
	COMMAND_GET_BASE_JOB_DETECTION_RETRY
};

class  CEyedeaEthernetClient
{
public:
	CEyedeaEthernetClient(void);
	~CEyedeaEthernetClient(void);

	int Send(unsigned char command, unsigned int* scalefactor, unsigned char** out_data, int* len);
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

	int TimeOut = 0;
};

#endif

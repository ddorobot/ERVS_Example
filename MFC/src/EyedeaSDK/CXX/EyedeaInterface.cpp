#include "EyedeaInterface.h"
#include "EyedeaErrorType.h"

CEyedeaInterface::CEyedeaInterface(void) :
	m_cls_eth_client(NULL)
{
#if 0
	//start
	m_run_thread_net = true;

	m_thread_net = boost::thread(boost::bind(&CEyedeaInterface::ThreadFunctionNetwork, this));
#endif
}

CEyedeaInterface::~CEyedeaInterface(void)
{
	if(m_cls_eth_client)
	{
		m_cls_eth_client->Close();

		delete m_cls_eth_client;
		m_cls_eth_client = NULL;
	}

	Close();
}

void CEyedeaInterface::Close(void)
{
#if 0
	m_run_thread_net = false;		//thread close

	m_thread_net.join();			//wait
#endif
}

#if 0
int CEyedeaInterface::Connect(char* ip, char* port)
{
	if (m_cls_eth_client)
	{
		m_cls_eth_client->Close();

		delete m_cls_eth_client;
		m_cls_eth_client = NULL;
	}

	m_cls_eth_client = new CEyedeaEthernetClient(ip, port);
}
#endif

int CEyedeaInterface::SetVisionConfigOption(int option, float value)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_VISION_CONFIG_SET;

	int len = 8;
	unsigned char* data = new unsigned char[len];
	
	//option
	data[0] = (option & 0xFF000000) >> 24;
	data[1] = (option & 0x00FF0000) >> 16;
	data[2] = (option & 0x0000FF00) >> 8;
	data[3] = (option & 0x000000FF);

	//x
	int i_value = value * 1000.0;
	data[4] = (i_value & 0xFF000000) >> 24;
	data[5] = (i_value & 0x00FF0000) >> 16;
	data[6] = (i_value & 0x0000FF00) >> 8;
	data[7] = (i_value & 0x000000FF);

	unsigned int scale_factor = 1000;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

float CEyedeaInterface::GetVisionConfigOption(int option)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_VISION_CONFIG_GET;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (option & 0xFF000000) >> 24;
	data[1] = (option & 0x00FF0000) >> 16;
	data[2] = (option & 0x0000FF00) >> 8;
	data[3] = (option & 0x000000FF);

	unsigned int scale_factor = 1;
	float ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0.0;

	if (len >= 4)
	{
		//x
		int i_value = ((int)data[0] << 24) & 0xFF000000;
		i_value |= ((int)data[1] << 16) & 0x00FF0000;
		i_value |= ((int)data[2] << 8) & 0x0000FF00;
		i_value |= ((int)data[3]) & 0x000000FF;

		ret =(float)i_value / (float)scale_factor;
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::SetObjectInformation(int id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_OBJECT_SET;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//id
	data[0] = (id & 0xFF000000) >> 24;
	data[1] = (id & 0x00FF0000) >> 16;
	data[2] = (id & 0x0000FF00) >> 8;
	data[3] = (id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::GetImage(char** out_data, int* len)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_IMAGE;

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			boost::this_thread::sleep(boost::posix_time::millisec(1000));
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if(sec >= 60)
					return ret;
				continue;
			}
		}
	}
 	//return m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
	return ret;
}

int CEyedeaInterface::GetResultFindSearchAreaCameraBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_RESULT_INFO;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_RESULT_SEARCH_AREA_CAMERA_BASE & 0xFF000000) >> 24;
	data[1] = (GET_RESULT_SEARCH_AREA_CAMERA_BASE & 0x00FF0000) >> 16;
	data[2] = (GET_RESULT_SEARCH_AREA_CAMERA_BASE & 0x0000FF00) >> 8;
	data[3] = (GET_RESULT_SEARCH_AREA_CAMERA_BASE & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	float x1 = 0;
	float y1 = 0;
	float x2 = 0;
	float y2 = 0;
	float x3 = 0;
	float y3 = 0;
	float x4 = 0;
	float y4 = 0;
	float f_angle = 0;

	if (len >= 36)
	{
		//w
		int x = 0;
		x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		x1 = (float)x / (float)scale_factor;

		int y = 0;
		y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		y1 = (float)y / (float)scale_factor;

		//

		x = 0;
		x = ((int)data[8] << 24) & 0xFF000000;
		x |= ((int)data[9] << 16) & 0x00FF0000;
		x |= ((int)data[10] << 8) & 0x0000FF00;
		x |= ((int)data[11]) & 0x000000FF;

		x2 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[12] << 24) & 0xFF000000;
		y |= ((int)data[13] << 16) & 0x00FF0000;
		y |= ((int)data[14] << 8) & 0x0000FF00;
		y |= ((int)data[15]) & 0x000000FF;

		y2 = (float)y / (float)scale_factor;

		x = 0;
		x = ((int)data[16] << 24) & 0xFF000000;
		x |= ((int)data[17] << 16) & 0x00FF0000;
		x |= ((int)data[18] << 8) & 0x0000FF00;
		x |= ((int)data[19]) & 0x000000FF;

		x3 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[20] << 24) & 0xFF000000;
		y |= ((int)data[21] << 16) & 0x00FF0000;
		y |= ((int)data[22] << 8) & 0x0000FF00;
		y |= ((int)data[23]) & 0x000000FF;

		y3 = (float)y / (float)scale_factor;

		//4
		x = 0;
		x = ((int)data[24] << 24) & 0xFF000000;
		x |= ((int)data[25] << 16) & 0x00FF0000;
		x |= ((int)data[26] << 8) & 0x0000FF00;
		x |= ((int)data[27]) & 0x000000FF;

		x4 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[28] << 24) & 0xFF000000;
		y |= ((int)data[29] << 16) & 0x00FF0000;
		y |= ((int)data[30] << 8) & 0x0000FF00;
		y |= ((int)data[31]) & 0x000000FF;

		y4 = (float)y / (float)scale_factor;

		//w
		int angle = 0;
		angle = ((int)data[32] << 24) & 0xFF000000;
		angle |= ((int)data[33] << 16) & 0x00FF0000;
		angle |= ((int)data[34] << 8) & 0x0000FF00;
		angle |= ((int)data[35]) & 0x000000FF;

		f_angle = (float)angle / (float)scale_factor;
	}

	delete (data);
	data = NULL;

	(*out_x1) = x1;
	(*out_y1) = y1;
	(*out_x2) = x2;
	(*out_y2) = y2;
	(*out_x3) = x3;
	(*out_y3) = y3;
	(*out_x4) = x4;
	(*out_y4) = y4;
	(*out_angle) = f_angle;

    return ret;
}

int CEyedeaInterface::GetResultFindMasterAreaCameraBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_RESULT_INFO;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_RESULT_MASTER_AREA_CAMERA_BASE & 0xFF000000) >> 24;
	data[1] = (GET_RESULT_MASTER_AREA_CAMERA_BASE & 0x00FF0000) >> 16;
	data[2] = (GET_RESULT_MASTER_AREA_CAMERA_BASE & 0x0000FF00) >> 8;
	data[3] = (GET_RESULT_MASTER_AREA_CAMERA_BASE & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	float x1 = 0;
	float y1 = 0;
	float x2 = 0;
	float y2 = 0;
	float x3 = 0;
	float y3 = 0;
	float x4 = 0;
	float y4 = 0;
	float f_angle = 0;

	if (len >= 36)
	{
		//w
		int x = 0;
		x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		x1 = (float)x / (float)scale_factor;

		int y = 0;
		y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		y1 = (float)y / (float)scale_factor;

		//

		x = 0;
		x = ((int)data[8] << 24) & 0xFF000000;
		x |= ((int)data[9] << 16) & 0x00FF0000;
		x |= ((int)data[10] << 8) & 0x0000FF00;
		x |= ((int)data[11]) & 0x000000FF;

		x2 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[12] << 24) & 0xFF000000;
		y |= ((int)data[13] << 16) & 0x00FF0000;
		y |= ((int)data[14] << 8) & 0x0000FF00;
		y |= ((int)data[15]) & 0x000000FF;

		y2 = (float)y / (float)scale_factor;

		x = 0;
		x = ((int)data[16] << 24) & 0xFF000000;
		x |= ((int)data[17] << 16) & 0x00FF0000;
		x |= ((int)data[18] << 8) & 0x0000FF00;
		x |= ((int)data[19]) & 0x000000FF;

		x3 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[20] << 24) & 0xFF000000;
		y |= ((int)data[21] << 16) & 0x00FF0000;
		y |= ((int)data[22] << 8) & 0x0000FF00;
		y |= ((int)data[23]) & 0x000000FF;

		y3 = (float)y / (float)scale_factor;

		//4
		x = 0;
		x = ((int)data[24] << 24) & 0xFF000000;
		x |= ((int)data[25] << 16) & 0x00FF0000;
		x |= ((int)data[26] << 8) & 0x0000FF00;
		x |= ((int)data[27]) & 0x000000FF;

		x4 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[28] << 24) & 0xFF000000;
		y |= ((int)data[29] << 16) & 0x00FF0000;
		y |= ((int)data[30] << 8) & 0x0000FF00;
		y |= ((int)data[31]) & 0x000000FF;

		y4 = (float)y / (float)scale_factor;

		//w
		int angle = 0;
		angle = ((int)data[32] << 24) & 0xFF000000;
		angle |= ((int)data[33] << 16) & 0x00FF0000;
		angle |= ((int)data[34] << 8) & 0x0000FF00;
		angle |= ((int)data[35]) & 0x000000FF;

		f_angle = (float)angle / (float)scale_factor;
	}

	delete (data);
	data = NULL;

	(*out_x1) = x1;
	(*out_y1) = y1;
	(*out_x2) = x2;
	(*out_y2) = y2;
	(*out_x3) = x3;
	(*out_y3) = y3;
	(*out_x4) = x4;
	(*out_y4) = y4;
	(*out_angle) = f_angle;

    return ret;
}

int CEyedeaInterface::GetResultFindSearchAreaRobotBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_RESULT_INFO;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_RESULT_SEARCH_AREA_ROBOT_BASE & 0xFF000000) >> 24;
	data[1] = (GET_RESULT_SEARCH_AREA_ROBOT_BASE & 0x00FF0000) >> 16;
	data[2] = (GET_RESULT_SEARCH_AREA_ROBOT_BASE & 0x0000FF00) >> 8;
	data[3] = (GET_RESULT_SEARCH_AREA_ROBOT_BASE & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	float x1 = 0;
	float y1 = 0;
	float x2 = 0;
	float y2 = 0;
	float x3 = 0;
	float y3 = 0;
	float x4 = 0;
	float y4 = 0;
	float f_angle = 0;

	if (len >= 36)
	{
		//w
		int x = 0;
		x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		x1 = (float)x / (float)scale_factor;

		int y = 0;
		y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		y1 = (float)y / (float)scale_factor;

		//

		x = 0;
		x = ((int)data[8] << 24) & 0xFF000000;
		x |= ((int)data[9] << 16) & 0x00FF0000;
		x |= ((int)data[10] << 8) & 0x0000FF00;
		x |= ((int)data[11]) & 0x000000FF;

		x2 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[12] << 24) & 0xFF000000;
		y |= ((int)data[13] << 16) & 0x00FF0000;
		y |= ((int)data[14] << 8) & 0x0000FF00;
		y |= ((int)data[15]) & 0x000000FF;

		y2 = (float)y / (float)scale_factor;

		x = 0;
		x = ((int)data[16] << 24) & 0xFF000000;
		x |= ((int)data[17] << 16) & 0x00FF0000;
		x |= ((int)data[18] << 8) & 0x0000FF00;
		x |= ((int)data[19]) & 0x000000FF;

		x3 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[20] << 24) & 0xFF000000;
		y |= ((int)data[21] << 16) & 0x00FF0000;
		y |= ((int)data[22] << 8) & 0x0000FF00;
		y |= ((int)data[23]) & 0x000000FF;

		y3 = (float)y / (float)scale_factor;

		//4
		x = 0;
		x = ((int)data[24] << 24) & 0xFF000000;
		x |= ((int)data[25] << 16) & 0x00FF0000;
		x |= ((int)data[26] << 8) & 0x0000FF00;
		x |= ((int)data[27]) & 0x000000FF;

		x4 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[28] << 24) & 0xFF000000;
		y |= ((int)data[29] << 16) & 0x00FF0000;
		y |= ((int)data[30] << 8) & 0x0000FF00;
		y |= ((int)data[31]) & 0x000000FF;

		y4 = (float)y / (float)scale_factor;

		//w
		int angle = 0;
		angle = ((int)data[32] << 24) & 0xFF000000;
		angle |= ((int)data[33] << 16) & 0x00FF0000;
		angle |= ((int)data[34] << 8) & 0x0000FF00;
		angle |= ((int)data[35]) & 0x000000FF;

		f_angle = (float)angle / (float)scale_factor;
	}

	delete (data);
	data = NULL;

	(*out_x1) = x1;
	(*out_y1) = y1;
	(*out_x2) = x2;
	(*out_y2) = y2;
	(*out_x3) = x3;
	(*out_y3) = y3;
	(*out_x4) = x4;
	(*out_y4) = y4;
	(*out_angle) = f_angle;

    return ret;
}

int CEyedeaInterface::GetResultFindMasterAreaRobotBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_RESULT_INFO;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_RESULT_MASTER_AREA_ROBOT_BASE & 0xFF000000) >> 24;
	data[1] = (GET_RESULT_MASTER_AREA_ROBOT_BASE & 0x00FF0000) >> 16;
	data[2] = (GET_RESULT_MASTER_AREA_ROBOT_BASE & 0x0000FF00) >> 8;
	data[3] = (GET_RESULT_MASTER_AREA_ROBOT_BASE & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	float x1 = 0;
	float y1 = 0;
	float x2 = 0;
	float y2 = 0;
	float x3 = 0;
	float y3 = 0;
	float x4 = 0;
	float y4 = 0;
	float f_angle = 0;

	if (len >= 36)
	{
		//w
		int x = 0;
		x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		x1 = (float)x / (float)scale_factor;

		int y = 0;
		y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		y1 = (float)y / (float)scale_factor;

		//

		x = 0;
		x = ((int)data[8] << 24) & 0xFF000000;
		x |= ((int)data[9] << 16) & 0x00FF0000;
		x |= ((int)data[10] << 8) & 0x0000FF00;
		x |= ((int)data[11]) & 0x000000FF;

		x2 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[12] << 24) & 0xFF000000;
		y |= ((int)data[13] << 16) & 0x00FF0000;
		y |= ((int)data[14] << 8) & 0x0000FF00;
		y |= ((int)data[15]) & 0x000000FF;

		y2 = (float)y / (float)scale_factor;

		x = 0;
		x = ((int)data[16] << 24) & 0xFF000000;
		x |= ((int)data[17] << 16) & 0x00FF0000;
		x |= ((int)data[18] << 8) & 0x0000FF00;
		x |= ((int)data[19]) & 0x000000FF;

		x3 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[20] << 24) & 0xFF000000;
		y |= ((int)data[21] << 16) & 0x00FF0000;
		y |= ((int)data[22] << 8) & 0x0000FF00;
		y |= ((int)data[23]) & 0x000000FF;

		y3 = (float)y / (float)scale_factor;

		//4
		x = 0;
		x = ((int)data[24] << 24) & 0xFF000000;
		x |= ((int)data[25] << 16) & 0x00FF0000;
		x |= ((int)data[26] << 8) & 0x0000FF00;
		x |= ((int)data[27]) & 0x000000FF;

		x4 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[28] << 24) & 0xFF000000;
		y |= ((int)data[29] << 16) & 0x00FF0000;
		y |= ((int)data[30] << 8) & 0x0000FF00;
		y |= ((int)data[31]) & 0x000000FF;

		y4 = (float)y / (float)scale_factor;

		//w
		int angle = 0;
		angle = ((int)data[32] << 24) & 0xFF000000;
		angle |= ((int)data[33] << 16) & 0x00FF0000;
		angle |= ((int)data[34] << 8) & 0x0000FF00;
		angle |= ((int)data[35]) & 0x000000FF;

		f_angle = (float)angle / (float)scale_factor;
	}

	delete (data);
	data = NULL;

	(*out_x1) = x1;
	(*out_y1) = y1;
	(*out_x2) = x2;
	(*out_y2) = y2;
	(*out_x3) = x3;
	(*out_y3) = y3;
	(*out_x4) = x4;
	(*out_y4) = y4;
	(*out_angle) = f_angle;

    return ret;
}

int CEyedeaInterface::GetResultFindSearchAreaImageBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_RESULT_INFO;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_RESULT_SEARCH_AREA_IMAGE_BASE & 0xFF000000) >> 24;
	data[1] = (GET_RESULT_SEARCH_AREA_IMAGE_BASE & 0x00FF0000) >> 16;
	data[2] = (GET_RESULT_SEARCH_AREA_IMAGE_BASE & 0x0000FF00) >> 8;
	data[3] = (GET_RESULT_SEARCH_AREA_IMAGE_BASE & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	float x1 = 0;
	float y1 = 0;
	float x2 = 0;
	float y2 = 0;
	float x3 = 0;
	float y3 = 0;
	float x4 = 0;
	float y4 = 0;
	float f_angle = 0;

	if (len >= 36)
	{
		//w
		int x = 0;
		x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		x1 = (float)x / (float)scale_factor;

		int y = 0;
		y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		y1 = (float)y / (float)scale_factor;

		//

		x = 0;
		x = ((int)data[8] << 24) & 0xFF000000;
		x |= ((int)data[9] << 16) & 0x00FF0000;
		x |= ((int)data[10] << 8) & 0x0000FF00;
		x |= ((int)data[11]) & 0x000000FF;

		x2 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[12] << 24) & 0xFF000000;
		y |= ((int)data[13] << 16) & 0x00FF0000;
		y |= ((int)data[14] << 8) & 0x0000FF00;
		y |= ((int)data[15]) & 0x000000FF;

		y2 = (float)y / (float)scale_factor;

		x = 0;
		x = ((int)data[16] << 24) & 0xFF000000;
		x |= ((int)data[17] << 16) & 0x00FF0000;
		x |= ((int)data[18] << 8) & 0x0000FF00;
		x |= ((int)data[19]) & 0x000000FF;

		x3 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[20] << 24) & 0xFF000000;
		y |= ((int)data[21] << 16) & 0x00FF0000;
		y |= ((int)data[22] << 8) & 0x0000FF00;
		y |= ((int)data[23]) & 0x000000FF;

		y3 = (float)y / (float)scale_factor;

		//4
		x = 0;
		x = ((int)data[24] << 24) & 0xFF000000;
		x |= ((int)data[25] << 16) & 0x00FF0000;
		x |= ((int)data[26] << 8) & 0x0000FF00;
		x |= ((int)data[27]) & 0x000000FF;

		x4 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[28] << 24) & 0xFF000000;
		y |= ((int)data[29] << 16) & 0x00FF0000;
		y |= ((int)data[30] << 8) & 0x0000FF00;
		y |= ((int)data[31]) & 0x000000FF;

		y4 = (float)y / (float)scale_factor;

		//w
		int angle = 0;
		angle = ((int)data[32] << 24) & 0xFF000000;
		angle |= ((int)data[33] << 16) & 0x00FF0000;
		angle |= ((int)data[34] << 8) & 0x0000FF00;
		angle |= ((int)data[35]) & 0x000000FF;

		f_angle = (float)angle / (float)scale_factor;
	}

	delete (data);
	data = NULL;

	(*out_x1) = x1;
	(*out_y1) = y1;
	(*out_x2) = x2;
	(*out_y2) = y2;
	(*out_x3) = x3;
	(*out_y3) = y3;
	(*out_x4) = x4;
	(*out_y4) = y4;
	(*out_angle) = f_angle;

    return ret;
}

int CEyedeaInterface::GetResultFindMasterAreaImageBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_RESULT_INFO;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_RESULT_MASTER_AREA_IMAGE_BASE & 0xFF000000) >> 24;
	data[1] = (GET_RESULT_MASTER_AREA_IMAGE_BASE & 0x00FF0000) >> 16;
	data[2] = (GET_RESULT_MASTER_AREA_IMAGE_BASE & 0x0000FF00) >> 8;
	data[3] = (GET_RESULT_MASTER_AREA_IMAGE_BASE & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	float x1 = 0;
	float y1 = 0;
	float x2 = 0;
	float y2 = 0;
	float x3 = 0;
	float y3 = 0;
	float x4 = 0;
	float y4 = 0;
	float f_angle = 0;

	if (len >= 36)
	{
		//w
		int x = 0;
		x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		x1 = (float)x / (float)scale_factor;

		int y = 0;
		y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		y1 = (float)y / (float)scale_factor;

		//

		x = 0;
		x = ((int)data[8] << 24) & 0xFF000000;
		x |= ((int)data[9] << 16) & 0x00FF0000;
		x |= ((int)data[10] << 8) & 0x0000FF00;
		x |= ((int)data[11]) & 0x000000FF;

		x2 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[12] << 24) & 0xFF000000;
		y |= ((int)data[13] << 16) & 0x00FF0000;
		y |= ((int)data[14] << 8) & 0x0000FF00;
		y |= ((int)data[15]) & 0x000000FF;

		y2 = (float)y / (float)scale_factor;

		x = 0;
		x = ((int)data[16] << 24) & 0xFF000000;
		x |= ((int)data[17] << 16) & 0x00FF0000;
		x |= ((int)data[18] << 8) & 0x0000FF00;
		x |= ((int)data[19]) & 0x000000FF;

		x3 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[20] << 24) & 0xFF000000;
		y |= ((int)data[21] << 16) & 0x00FF0000;
		y |= ((int)data[22] << 8) & 0x0000FF00;
		y |= ((int)data[23]) & 0x000000FF;

		y3 = (float)y / (float)scale_factor;

		//4
		x = 0;
		x = ((int)data[24] << 24) & 0xFF000000;
		x |= ((int)data[25] << 16) & 0x00FF0000;
		x |= ((int)data[26] << 8) & 0x0000FF00;
		x |= ((int)data[27]) & 0x000000FF;

		x4 = (float)x / (float)scale_factor;

		y = 0;
		y = ((int)data[28] << 24) & 0xFF000000;
		y |= ((int)data[29] << 16) & 0x00FF0000;
		y |= ((int)data[30] << 8) & 0x0000FF00;
		y |= ((int)data[31]) & 0x000000FF;

		y4 = (float)y / (float)scale_factor;

		//w
		int angle = 0;
		angle = ((int)data[32] << 24) & 0xFF000000;
		angle |= ((int)data[33] << 16) & 0x00FF0000;
		angle |= ((int)data[34] << 8) & 0x0000FF00;
		angle |= ((int)data[35]) & 0x000000FF;

		f_angle = (float)angle / (float)scale_factor;
	}

	delete (data);
	data = NULL;

	(*out_x1) = x1;
	(*out_y1) = y1;
	(*out_x2) = x2;
	(*out_y2) = y2;
	(*out_x3) = x3;
	(*out_y3) = y3;
	(*out_x4) = x4;
	(*out_y4) = y4;
	(*out_angle) = f_angle;

    return ret;
}

int CEyedeaInterface::ERVS_DBAddSubObject(int id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_DB_ADD_SUB_OBJECT;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//sub info
	data[0] = (id & 0xFF000000) >> 24;
	data[1] = (id & 0x00FF0000) >> 16;
	data[2] = (id & 0x0000FF00) >> 8;
	data[3] = (id & 0x000000FF);

	unsigned int scale_factor = 1;

	int new_id = 0;
    new_id = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(new_id == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			new_id = m_cls_eth_client->Open(m_ip, m_port);
			if(new_id == 0){
				new_id = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return new_id;
				}
				continue;
			}
		}
	}
	if (new_id != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return new_id;
	}

	new_id = -1;

	if (len >= 4)
	{
		new_id = ((int)data[0] << 24) & 0xFF000000;
		new_id |= ((int)data[1] << 16) & 0x00FF0000;
		new_id |= ((int)data[2] << 8) & 0x0000FF00;
		new_id |= ((int)data[3]) & 0x000000FF;
	}

	if (data != NULL)
	{
		delete (data);
		data = NULL;
	}

	return new_id;
}

int CEyedeaInterface::DBAddObject(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_DB_ADD_OBJECT;
	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int new_id = 0;
    new_id = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(new_id == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			new_id = m_cls_eth_client->Open(m_ip, m_port);
			if(new_id == 0){
				new_id = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return new_id;
				}
				continue;
			}
		}
	}
	if (new_id != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return new_id;
	}

	new_id = -1;

	if (len >= 4)
	{
		new_id = ((int)data[0] << 24) & 0xFF000000;
		new_id |= ((int)data[1] << 16) & 0x00FF0000;
		new_id |= ((int)data[2] << 8) & 0x0000FF00;
		new_id |= ((int)data[3]) & 0x000000FF;
	}

	if (data != NULL)
	{
		delete (data);
		data = NULL;
	}

	return new_id;
}

int CEyedeaInterface::ResetObject(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_RESET_OBJECT;
	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::GetSubObjectSearchAreaByIdId(const int host_id, const int sub_id, float* out_search_area_x, float* out_search_area_y, float* out_search_area_w, float* out_search_area_h)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_TEACH_SUB_INFO;
	int len = 12;
	unsigned char* data = new unsigned char[len];

	//sub info
	data[0] = (GET_DB_SUB_INFO_SEARCHAREA_BY_IDID & 0xFF000000) >> 24;
	data[1] = (GET_DB_SUB_INFO_SEARCHAREA_BY_IDID & 0x00FF0000) >> 16;
	data[2] = (GET_DB_SUB_INFO_SEARCHAREA_BY_IDID & 0x0000FF00) >> 8;
	data[3] = (GET_DB_SUB_INFO_SEARCHAREA_BY_IDID & 0x000000FF);

	//option
	data[4] = (host_id & 0xFF000000) >> 24;
	data[5] = (host_id & 0x00FF0000) >> 16;
	data[6] = (host_id & 0x0000FF00) >> 8;
	data[7] = (host_id & 0x000000FF);

	//option
	data[8] = (sub_id & 0xFF000000) >> 24;
	data[9] = (sub_id & 0x00FF0000) >> 16;
	data[10] = (sub_id & 0x0000FF00) >> 8;
	data[11] = (sub_id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	if (len >= 16)
	{
		//x
		int x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		//y
		int y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		//w
		int w = ((int)data[8] << 24) & 0xFF000000;
		w |= ((int)data[9] << 16) & 0x00FF0000;
		w |= ((int)data[10] << 8) & 0x0000FF00;
		w |= ((int)data[11]) & 0x000000FF;

		//h
		int h = ((int)data[12] << 24) & 0xFF000000;
		h |= ((int)data[13] << 16) & 0x00FF0000;
		h |= ((int)data[14] << 8) & 0x0000FF00;
		h |= ((int)data[15]) & 0x000000FF;

		float _x = (float)x / (float)scale_factor;
		//x = (int)((float)TRANS_IAMGE_WIDTH * _x);

		float _y = (float)y / (float)scale_factor;
		//y = (int)((float)TRANS_IAMGE_HEIGHT * _y);

		float _w = (float)w / (float)scale_factor;
		//w = (int)((float)TRANS_IAMGE_WIDTH * _w);

		float _h = (float)h / (float)scale_factor;
		//h = (int)((float)TRANS_IAMGE_HEIGHT * _h);

		(*out_search_area_x) = _x;
		(*out_search_area_y) = _y;
		(*out_search_area_w) = _w;
		(*out_search_area_h) = _h;
	}

	delete data;
	data = NULL;

    return ret;
}

int CEyedeaInterface::GetSubObjectSearchAreaByIdIndex(const int host_id, const int index, float* out_search_area_x, float* out_search_area_y, float* out_search_area_w, float* out_search_area_h)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_TEACH_SUB_INFO;
	int len = 12;
	unsigned char* data = new unsigned char[len];

	//sub info
	data[0] = (GET_DB_SUB_INFO_SEARCHAREA_BY_IDINDEX & 0xFF000000) >> 24;
	data[1] = (GET_DB_SUB_INFO_SEARCHAREA_BY_IDINDEX & 0x00FF0000) >> 16;
	data[2] = (GET_DB_SUB_INFO_SEARCHAREA_BY_IDINDEX & 0x0000FF00) >> 8;
	data[3] = (GET_DB_SUB_INFO_SEARCHAREA_BY_IDINDEX & 0x000000FF);

	//option
	data[4] = (host_id & 0xFF000000) >> 24;
	data[5] = (host_id & 0x00FF0000) >> 16;
	data[6] = (host_id & 0x0000FF00) >> 8;
	data[7] = (host_id & 0x000000FF);

	//option
	data[8] = (index & 0xFF000000) >> 24;
	data[9] = (index & 0x00FF0000) >> 16;
	data[10] = (index & 0x0000FF00) >> 8;
	data[11] = (index & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	if (len >= 16)
	{
		//x
		int x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		//y
		int y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		//w
		int w = ((int)data[8] << 24) & 0xFF000000;
		w |= ((int)data[9] << 16) & 0x00FF0000;
		w |= ((int)data[10] << 8) & 0x0000FF00;
		w |= ((int)data[11]) & 0x000000FF;

		//h
		int h = ((int)data[12] << 24) & 0xFF000000;
		h |= ((int)data[13] << 16) & 0x00FF0000;
		h |= ((int)data[14] << 8) & 0x0000FF00;
		h |= ((int)data[15]) & 0x000000FF;

		float _x = (float)x / (float)scale_factor;
		//x = (int)((float)TRANS_IAMGE_WIDTH * _x);

		float _y = (float)y / (float)scale_factor;
		//y = (int)((float)TRANS_IAMGE_HEIGHT * _y);

		float _w = (float)w / (float)scale_factor;
		//w = (int)((float)TRANS_IAMGE_WIDTH * _w);

		float _h = (float)h / (float)scale_factor;
		//h = (int)((float)TRANS_IAMGE_HEIGHT * _h);

		(*out_search_area_x) = _x;
		(*out_search_area_y) = _y;
		(*out_search_area_w) = _w;
		(*out_search_area_h) = _h;
	}

	delete data;
	data = NULL;

    return ret;
}

int CEyedeaInterface::GetSubObjectUseInspectionByIdId(const int host_id, const int sub_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_TEACH_SUB_INFO;
	int len = 12;
	unsigned char* data = new unsigned char[len];

	//sub info
	data[0] = (GET_DB_SUB_INFO_USE_INSPECTION_BY_IDID & 0xFF000000) >> 24;
	data[1] = (GET_DB_SUB_INFO_USE_INSPECTION_BY_IDID & 0x00FF0000) >> 16;
	data[2] = (GET_DB_SUB_INFO_USE_INSPECTION_BY_IDID & 0x0000FF00) >> 8;
	data[3] = (GET_DB_SUB_INFO_USE_INSPECTION_BY_IDID & 0x000000FF);

	//option
	data[4] = (host_id & 0xFF000000) >> 24;
	data[5] = (host_id & 0x00FF0000) >> 16;
	data[6] = (host_id & 0x0000FF00) >> 8;
	data[7] = (host_id & 0x000000FF);

	//option
	data[8] = (sub_id & 0xFF000000) >> 24;
	data[9] = (sub_id & 0x00FF0000) >> 16;
	data[10] = (sub_id & 0x0000FF00) >> 8;
	data[11] = (sub_id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0;
	if (len >= 4)
	{
		//x
		ret =((int)data[0] << 24) & 0xFF000000;
		ret =((int)data[1] << 16) & 0x00FF0000;
		ret =((int)data[2] << 8) & 0x0000FF00;
		ret =((int)data[3]) & 0x000000FF;

	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::GetSubObjectUseInspectionByIdIndex(const int host_id, const int index)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_TEACH_SUB_INFO;
	int len = 12;
	unsigned char* data = new unsigned char[len];

	//sub info
	data[0] = (GET_DB_SUB_INFO_USE_INSPECTION_BY_IDINDEX & 0xFF000000) >> 24;
	data[1] = (GET_DB_SUB_INFO_USE_INSPECTION_BY_IDINDEX & 0x00FF0000) >> 16;
	data[2] = (GET_DB_SUB_INFO_USE_INSPECTION_BY_IDINDEX & 0x0000FF00) >> 8;
	data[3] = (GET_DB_SUB_INFO_USE_INSPECTION_BY_IDINDEX & 0x000000FF);

	//option
	data[4] = (host_id & 0xFF000000) >> 24;
	data[5] = (host_id & 0x00FF0000) >> 16;
	data[6] = (host_id & 0x0000FF00) >> 8;
	data[7] = (host_id & 0x000000FF);

	//option
	data[8] = (index & 0xFF000000) >> 24;
	data[9] = (index & 0x00FF0000) >> 16;
	data[10] = (index & 0x0000FF00) >> 8;
	data[11] = (index & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	ret =0;

	if (len >= 4)
	{
		//x
		ret =((int)data[0] << 24) & 0xFF000000;
		ret =((int)data[1] << 16) & 0x00FF0000;
		ret =((int)data[2] << 8) & 0x0000FF00;
		ret =((int)data[3]) & 0x000000FF;
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::GetSubObjectCircleByIdIndex(const int host_id, const int index, float* out_circle_x, float* out_circle_y, float* out_circle_rx, float* out_circle_ry)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_TEACH_SUB_INFO;
	int len = 12;
	unsigned char* data = new unsigned char[len];

	//sub info
	data[0] = (GET_DB_SUB_INFO_CIRCLE_BY_IDINDEX & 0xFF000000) >> 24;
	data[1] = (GET_DB_SUB_INFO_CIRCLE_BY_IDINDEX & 0x00FF0000) >> 16;
	data[2] = (GET_DB_SUB_INFO_CIRCLE_BY_IDINDEX & 0x0000FF00) >> 8;
	data[3] = (GET_DB_SUB_INFO_CIRCLE_BY_IDINDEX & 0x000000FF);

	//option
	data[4] = (host_id & 0xFF000000) >> 24;
	data[5] = (host_id & 0x00FF0000) >> 16;
	data[6] = (host_id & 0x0000FF00) >> 8;
	data[7] = (host_id & 0x000000FF);

	//option
	data[8] = (index & 0xFF000000) >> 24;
	data[9] = (index & 0x00FF0000) >> 16;
	data[10] = (index & 0x0000FF00) >> 8;
	data[11] = (index & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	if (len >= 16)
	{
		//x
		int x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		//y
		int y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		//w
		int w = ((int)data[8] << 24) & 0xFF000000;
		w |= ((int)data[9] << 16) & 0x00FF0000;
		w |= ((int)data[10] << 8) & 0x0000FF00;
		w |= ((int)data[11]) & 0x000000FF;

		//h
		int h = ((int)data[12] << 24) & 0xFF000000;
		h |= ((int)data[13] << 16) & 0x00FF0000;
		h |= ((int)data[14] << 8) & 0x0000FF00;
		h |= ((int)data[15]) & 0x000000FF;

		float _x = (float)x / (float)scale_factor;
		//x = (int)((float)TRANS_IAMGE_WIDTH * _x);

		float _y = (float)y / (float)scale_factor;
		//y = (int)((float)TRANS_IAMGE_HEIGHT * _y);

		float _w = (float)w / (float)scale_factor;
		//w = (int)((float)TRANS_IAMGE_WIDTH * _w);

		float _h = (float)h / (float)scale_factor;
		//h = (int)((float)TRANS_IAMGE_HEIGHT * _h);

		(*out_circle_x) = _x;
		(*out_circle_y) = _y;
		(*out_circle_rx) = _w;
		(*out_circle_ry) = _h;
	}

	delete data;
	data = NULL;

    return ret;
}

int CEyedeaInterface::GetSubObjectCircleByIdId(const int host_id, const int sub_id, float* out_circle_x, float* out_circle_y, float* out_circle_rx, float* out_circle_ry)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_TEACH_SUB_INFO;
	int len = 12;
	unsigned char* data = new unsigned char[len];

	//sub info
	data[0] = (GET_DB_SUB_INFO_CIRCLE_BY_IDID & 0xFF000000) >> 24;
	data[1] = (GET_DB_SUB_INFO_CIRCLE_BY_IDID & 0x00FF0000) >> 16;
	data[2] = (GET_DB_SUB_INFO_CIRCLE_BY_IDID & 0x0000FF00) >> 8;
	data[3] = (GET_DB_SUB_INFO_CIRCLE_BY_IDID & 0x000000FF);

	//option
	data[4] = (host_id & 0xFF000000) >> 24;
	data[5] = (host_id & 0x00FF0000) >> 16;
	data[6] = (host_id & 0x0000FF00) >> 8;
	data[7] = (host_id & 0x000000FF);

	//option
	data[8] = (sub_id & 0xFF000000) >> 24;
	data[9] = (sub_id & 0x00FF0000) >> 16;
	data[10] = (sub_id & 0x0000FF00) >> 8;
	data[11] = (sub_id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	if (len >= 16)
	{
		//x
		int x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		//y
		int y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		//w
		int w = ((int)data[8] << 24) & 0xFF000000;
		w |= ((int)data[9] << 16) & 0x00FF0000;
		w |= ((int)data[10] << 8) & 0x0000FF00;
		w |= ((int)data[11]) & 0x000000FF;

		//h
		int h = ((int)data[12] << 24) & 0xFF000000;
		h |= ((int)data[13] << 16) & 0x00FF0000;
		h |= ((int)data[14] << 8) & 0x0000FF00;
		h |= ((int)data[15]) & 0x000000FF;

		float _x = (float)x / (float)scale_factor;
		//x = (int)((float)TRANS_IAMGE_WIDTH * _x);

		float _y = (float)y / (float)scale_factor;
		//y = (int)((float)TRANS_IAMGE_HEIGHT * _y);

		float _w = (float)w / (float)scale_factor;
		//w = (int)((float)TRANS_IAMGE_WIDTH * _w);

		float _h = (float)h / (float)scale_factor;
		//h = (int)((float)TRANS_IAMGE_HEIGHT * _h);

		(*out_circle_x) = _x;
		(*out_circle_y) = _y;
		(*out_circle_rx) = _w;
		(*out_circle_ry) = _h;
	}

	delete data;
	data = NULL;

    return ret;
}

int CEyedeaInterface::GetSubObjectMasterAreaByIdId(const int host_id, const int sub_id, float* out_master_area_x, float* out_master_area_y, float* out_master_area_w, float* out_master_area_h)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_TEACH_SUB_INFO;
	int len = 12;
	unsigned char* data = new unsigned char[len];

	//sub info
	data[0] = (GET_DB_SUB_INFO_MASTERAREA_BY_IDID & 0xFF000000) >> 24;
	data[1] = (GET_DB_SUB_INFO_MASTERAREA_BY_IDID & 0x00FF0000) >> 16;
	data[2] = (GET_DB_SUB_INFO_MASTERAREA_BY_IDID & 0x0000FF00) >> 8;
	data[3] = (GET_DB_SUB_INFO_MASTERAREA_BY_IDID & 0x000000FF);

	//option
	data[4] = (host_id & 0xFF000000) >> 24;
	data[5] = (host_id & 0x00FF0000) >> 16;
	data[6] = (host_id & 0x0000FF00) >> 8;
	data[7] = (host_id & 0x000000FF);

	//option
	data[8] = (sub_id & 0xFF000000) >> 24;
	data[9] = (sub_id & 0x00FF0000) >> 16;
	data[10] = (sub_id & 0x0000FF00) >> 8;
	data[11] = (sub_id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	if (len >= 16)
	{
		//x
		int x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		//y
		int y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		//w
		int w = ((int)data[8] << 24) & 0xFF000000;
		w |= ((int)data[9] << 16) & 0x00FF0000;
		w |= ((int)data[10] << 8) & 0x0000FF00;
		w |= ((int)data[11]) & 0x000000FF;

		//h
		int h = ((int)data[12] << 24) & 0xFF000000;
		h |= ((int)data[13] << 16) & 0x00FF0000;
		h |= ((int)data[14] << 8) & 0x0000FF00;
		h |= ((int)data[15]) & 0x000000FF;

		float _x = (float)x / (float)scale_factor;
		//x = (int)((float)TRANS_IAMGE_WIDTH * _x);

		float _y = (float)y / (float)scale_factor;
		//y = (int)((float)TRANS_IAMGE_HEIGHT * _y);

		float _w = (float)w / (float)scale_factor;
		//w = (int)((float)TRANS_IAMGE_WIDTH * _w);

		float _h = (float)h / (float)scale_factor;
		//h = (int)((float)TRANS_IAMGE_HEIGHT * _h);

		(*out_master_area_x) = _x;
		(*out_master_area_y) = _y;
		(*out_master_area_w) = _w;
		(*out_master_area_h) = _h;
	}

	delete data;
	data = NULL;

    return ret;
}

int CEyedeaInterface::GetSubObjectMasterAreaByIdIndex(const int host_id, const int index, float* out_master_area_x, float* out_master_area_y, float* out_master_area_w, float* out_master_area_h)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_TEACH_SUB_INFO;
	int len = 12;
	unsigned char* data = new unsigned char[len];

	//sub info
	data[0] = (GET_DB_SUB_INFO_MASTERAREA_BY_IDINDEX & 0xFF000000) >> 24;
	data[1] = (GET_DB_SUB_INFO_MASTERAREA_BY_IDINDEX & 0x00FF0000) >> 16;
	data[2] = (GET_DB_SUB_INFO_MASTERAREA_BY_IDINDEX & 0x0000FF00) >> 8;
	data[3] = (GET_DB_SUB_INFO_MASTERAREA_BY_IDINDEX & 0x000000FF);

	//option
	data[4] = (host_id & 0xFF000000) >> 24;
	data[5] = (host_id & 0x00FF0000) >> 16;
	data[6] = (host_id & 0x0000FF00) >> 8;
	data[7] = (host_id & 0x000000FF);

	//option
	data[8] = (index & 0xFF000000) >> 24;
	data[9] = (index & 0x00FF0000) >> 16;
	data[10] = (index & 0x0000FF00) >> 8;
	data[11] = (index & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	if (len >= 16)
	{
		//x
		int x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		//y
		int y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		//w
		int w = ((int)data[8] << 24) & 0xFF000000;
		w |= ((int)data[9] << 16) & 0x00FF0000;
		w |= ((int)data[10] << 8) & 0x0000FF00;
		w |= ((int)data[11]) & 0x000000FF;

		//h
		int h = ((int)data[12] << 24) & 0xFF000000;
		h |= ((int)data[13] << 16) & 0x00FF0000;
		h |= ((int)data[14] << 8) & 0x0000FF00;
		h |= ((int)data[15]) & 0x000000FF;

		float _x = (float)x / (float)scale_factor;
		//x = (int)((float)TRANS_IAMGE_WIDTH * _x);

		float _y = (float)y / (float)scale_factor;
		//y = (int)((float)TRANS_IAMGE_HEIGHT * _y);

		float _w = (float)w / (float)scale_factor;
		//w = (int)((float)TRANS_IAMGE_WIDTH * _w);

		float _h = (float)h / (float)scale_factor;
		//h = (int)((float)TRANS_IAMGE_HEIGHT * _h);

		(*out_master_area_x) = _x;
		(*out_master_area_y) = _y;
		(*out_master_area_w) = _w;
		(*out_master_area_h) = _h;
	}

	delete data;
	data = NULL;

    return ret;
}

unsigned int CEyedeaInterface::GetSubObjectID(int host_id, int index)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_TEACH_SUB_INFO;
	int len = 12;
	unsigned char* data = new unsigned char[len];

	//sub info
	data[0] = (GET_DB_SUB_INFO_ID_BY_IDINDEX & 0xFF000000) >> 24;
	data[1] = (GET_DB_SUB_INFO_ID_BY_IDINDEX & 0x00FF0000) >> 16;
	data[2] = (GET_DB_SUB_INFO_ID_BY_IDINDEX & 0x0000FF00) >> 8;
	data[3] = (GET_DB_SUB_INFO_ID_BY_IDINDEX & 0x000000FF);

	//option
	data[4] = (host_id & 0xFF000000) >> 24;
	data[5] = (host_id & 0x00FF0000) >> 16;
	data[6] = (host_id & 0x0000FF00) >> 8;
	data[7] = (host_id & 0x000000FF);

	//option
	data[8] = (index & 0xFF000000) >> 24;
	data[9] = (index & 0x00FF0000) >> 16;
	data[10] = (index & 0x0000FF00) >> 8;
	data[11] = (index & 0x000000FF);

	unsigned int scale_factor = 1;
	unsigned int id = 0;
    id = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(id == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			id = m_cls_eth_client->Open(m_ip, m_port);
			if(id == 0){
				id = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return id;
				}
				continue;
			}
		}
	}
	if (id != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return id;
	}

	id = 0;

	printf("len = %d\n", len);

	if (len >= 4)
	{
		printf("data[0] = %d\n", data[0]);
		printf("data[1] = %d\n", data[1]);
		printf("data[2] = %d\n", data[2]);
		printf("data[3] = %d\n", data[3]);

		printf("data[0] = %c\n", data[0]);
		printf("data[1] = %c\n", data[1]);
		printf("data[2] = %c\n", data[2]);
		printf("data[3] = %c\n", data[3]);

		unsigned int tmp = data[0];
		id = (tmp << 24) & 0xFF000000;
		tmp = data[1];
		id |= (tmp << 16) & 0x00FF0000;
		tmp = data[2];
		id |= (tmp << 8) & 0x0000FF00;
		tmp = data[3];
		id |= (tmp) & 0x000000FF;
	}

	if (data != NULL)
	{
		delete (data);
		data = NULL;
	}

	return id;
}

int CEyedeaInterface::GetSubObjectCount(int id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_TEACH_SUB_COUNT;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (id & 0xFF000000) >> 24;
	data[1] = (id & 0x00FF0000) >> 16;
	data[2] = (id & 0x0000FF00) >> 8;
	data[3] = (id & 0x000000FF);

	unsigned int scale_factor = 1;
	int count = 0;
    count = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(count == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			count = m_cls_eth_client->Open(m_ip, m_port);
			if(count == 0){
				count = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return count;
				}
				continue;
			}
		}
	}
	if (count != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return count;
	}

	count = 0;

	if (len >= 4)
	{
		count = ((int)data[0] << 24) & 0xFF000000;
		count |= ((int)data[1] << 16) & 0x00FF0000;
		count |= ((int)data[2] << 8) & 0x0000FF00;
		count |= ((int)data[3]) & 0x000000FF;
	}

	if (data != NULL)
	{
		delete (data);
		data = NULL;
	}

	return count;
}

int CEyedeaInterface::DB_Del_ID(int id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_DB_DEL_ID;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (id & 0xFF000000) >> 24;
	data[1] = (id & 0x00FF0000) >> 16;
	data[2] = (id & 0x0000FF00) >> 8;
	data[3] = (id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::GetDB_Select_ID(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_DB_GET_SELECT_ID;
	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	int ret_id = 0;
	if (len >= 4)
	{
		ret_id = ((int)data[0] << 24) & 0xFF000000;
		ret_id |= ((int)data[1] << 16) & 0x00FF0000;
		ret_id |= ((int)data[2] << 8) & 0x0000FF00;
		ret_id |= ((int)data[3]) & 0x000000FF;
	}

	ret = ret_id;

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::GetDB_Info_Id(int index)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_DB_GET_ID;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (index & 0xFF000000) >> 24;
	data[1] = (index & 0x00FF0000) >> 16;
	data[2] = (index & 0x0000FF00) >> 8;
	data[3] = (index & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	int ret_id = 0;
	if (len >= 4)
	{
		ret_id = ((int)data[0] << 24) & 0xFF000000;
		ret_id |= ((int)data[1] << 16) & 0x00FF0000;
		ret_id |= ((int)data[2] << 8) & 0x0000FF00;
		ret_id |= ((int)data[3]) & 0x000000FF;
	}

	ret = ret_id;

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::GetDBCount(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_DB_GET_COUNT;
	int len = 0;
	unsigned char* data = NULL ;

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	int count = 0;
	if (len >= 4)
	{
		count = ((int)data[0] << 24) & 0xFF000000;
		count |= ((int)data[1] << 16) & 0x00FF0000;
		count |= ((int)data[2] << 8) & 0x0000FF00;
		count |= ((int)data[3]) & 0x000000FF;
	}

	ret = count;

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::SetObject(int id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_OBJECT;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (id & 0xFF000000) >> 24;
	data[1] = (id & 0x00FF0000) >> 16;
	data[2] = (id & 0x0000FF00) >> 8;
	data[3] = (id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	int ret_id = 0;
	if (len >= 4)
	{
		ret_id = ((int)data[0] << 24) & 0xFF000000;
		ret_id |= ((int)data[1] << 16) & 0x00FF0000;
		ret_id |= ((int)data[2] << 8) & 0x0000FF00;
		ret_id |= ((int)data[3]) & 0x000000FF;
	}

	ret = ret_id;

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::SetMode(int option)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_MODE;
	int len = 4;
	unsigned char* data = new unsigned  char[len];

	//option
	data[0] = (option & 0xFF000000) >> 24;
	data[1] = (option & 0x00FF0000) >> 16;
	data[2] = (option & 0x0000FF00) >> 8;
	data[3] = (option & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::GetMode(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_MODE;
	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int mode = 0;
    mode = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(mode == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			mode = m_cls_eth_client->Open(m_ip, m_port);
			if(mode == 0){
				mode = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return mode;
				}
				continue;
			}
		}
	}
	if (mode != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return mode;
	}

	mode = -1;

	if (len >= 4)
	{
		mode = ((int)data[0] << 24) & 0xFF000000;
		mode |= ((int)data[1] << 16) & 0x00FF0000;
		mode |= ((int)data[2] << 8) & 0x0000FF00;
		mode |= ((int)data[3]) & 0x000000FF;
	}

	if (data != NULL)
	{
		delete (data);
		data = NULL;
	}

	return mode;

}

float CEyedeaInterface::GetResultFindScale(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_RESULT_INFO;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_RESULT_SCALE & 0xFF000000) >> 24;
	data[1] = (GET_RESULT_SCALE & 0x00FF0000) >> 16;
	data[2] = (GET_RESULT_SCALE & 0x0000FF00) >> 8;
	data[3] = (GET_RESULT_SCALE & 0x000000FF);

	unsigned int scale_factor = 1;
	float scale = 0;
    scale = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(scale == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			scale = m_cls_eth_client->Open(m_ip, m_port);
			if(scale == 0){
				scale = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return scale;
				}
				continue;
			}
		}
	}
	if (scale != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return scale;
	}

	scale = 0;

	if (len >= 4)
	{
		//w
		int x = 0;
		x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		scale = (float)x / (float)scale_factor;
	}

	delete (data);
	data = NULL;

	return scale;
}

float CEyedeaInterface::GetResultFindScore(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_GET_RESULT_INFO;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_RESULT_SCORE & 0xFF000000) >> 24;
	data[1] = (GET_RESULT_SCORE & 0x00FF0000) >> 16;
	data[2] = (GET_RESULT_SCORE & 0x0000FF00) >> 8;
	data[3] = (GET_RESULT_SCORE & 0x000000FF);

	unsigned int scale_factor = 1;
	float score = 0;
    score = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(score == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			score = m_cls_eth_client->Open(m_ip, m_port);
			if(score == 0){
				score = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return score;
				}
				continue;
			}
		}
	}
	if (score != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return score;
	}

	score = 0;

	if (len >= 4)
	{
		//w
		int x = 0;
		x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		score = (float)x / (float)scale_factor;
	}

	delete (data);
	data = NULL;

	return score;
}

int CEyedeaInterface::GetImage(int option, int option2, char** out_data, int* len)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_IMAGE_W_OPTION;
	
	//option
	(*out_data)[0] = (option & 0xFF000000) >> 24;
	(*out_data)[1] = (option & 0x00FF0000) >> 16;
	(*out_data)[2] = (option & 0x0000FF00) >> 8;
	(*out_data)[3] = (option & 0x000000FF);

	//option
	(*out_data)[4] = (option2 & 0xFF000000) >> 24;
	(*out_data)[5] = (option2 & 0x00FF0000) >> 16;
	(*out_data)[6] = (option2 & 0x0000FF00) >> 8;
	(*out_data)[7] = (option2 & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if(sec >= 60)
					return ret;
				continue;
			}
		}
	}
	return ret;
}

int CEyedeaInterface::GetResultImage(int option, int option2, char** out_data, int* len)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_RESULT_IMAGE_FIND_OBJECTS;

	//option
	(*out_data)[0] = (option & 0xFF000000) >> 24;
	(*out_data)[1] = (option & 0x00FF0000) >> 16;
	(*out_data)[2] = (option & 0x0000FF00) >> 8;
	(*out_data)[3] = (option & 0x000000FF);

	//option
	(*out_data)[4] = (option2 & 0xFF000000) >> 24;
	(*out_data)[5] = (option2 & 0x00FF0000) >> 16;
	(*out_data)[6] = (option2 & 0x0000FF00) >> 8;
	(*out_data)[7] = (option2 & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
	if (ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while (1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if (ret == 0) {
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
					return ret;
				continue;
			}
		}
	}
	return ret;
}

int CEyedeaInterface::GetObjectImage(char** out_data, int* len)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_OBJECT_IMAGE;

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if(sec >= 60)
					return ret;
				continue;
			}
		}
	}
	return ret;
}

int CEyedeaInterface::GetFindObjectImage(int index, char** data, int* len)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_FIND_OBJECT_IMAGE;

	//option
	(*data)[0] = (index & 0xFF000000) >> 24;
	(*data)[1] = (index & 0x00FF0000) >> 16;
	(*data)[2] = (index & 0x0000FF00) >> 8;
	(*data)[3] = (index & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)data, len);
	return ret;
}

int CEyedeaInterface::GetZoomImage(char** out_data, int* len)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_ZOOM_IMAGE;

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if(sec >= 60)
					return ret;
				continue;
			}
		}
	}
	return ret;
}

int CEyedeaInterface::GetBaseImage(char** out_data, int* len)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_BASE_IMAGE;

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if(sec >= 60)
					return ret;
				continue;
			}
		}
	}
	return ret;
}

int CEyedeaInterface::GetResultImage(char** out_data, int* len)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_RESULT_IMAGE;

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if(sec >= 60)
					return ret;
				continue;
			}
		}
	}
	return ret;
}

int CEyedeaInterface::GetResultImageGlobal(char** out_data, int* len)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_RESULT_IMAGE_GLOBAL;

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if(sec >= 60)
					return ret;
				continue;
			}
		}
	}
	return ret;
}

int CEyedeaInterface::GetResultImageLocal(char** out_data, int* len, int id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//// select list  ------------------------------------------------------------------------
	int len2 = 4;
	unsigned char* data2 = new unsigned char[4];
	char command = COMMAND_SET_SELECT_LIST_BY_ID;

	id += 1;

	//x
	data2[0] = (id & 0xFF000000) >> 24;
	data2[1] = (id & 0x00FF0000) >> 16;
	data2[2] = (id & 0x0000FF00) >> 8;
	data2[3] = (id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data2, &len2);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data2, &len2);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data2 != NULL)
					{
						delete data2;
						data2 = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data2 != NULL)
		{
			delete data2;
			data2 = NULL;
		}
		return ret;
	}

	delete (data2);
	data2 = NULL;

	//// Get Image ------------------------------------------------------------------------
	command = COMMAND_GET_RESULT_IMAGE_LOCAL;

	scale_factor = 1;
	ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
					return ret;
				continue;
			}
		}
	}
	return ret;
}

int CEyedeaInterface::GetImageWidthUserArea(char** out_data, int* len)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_USER_AREA_IMAGE;

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
					return ret;
				continue;
			}
		}
	}
	return ret;
}

int CEyedeaInterface::SetSearchArea(float x, float y, float w, float h)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_SEARCH_AREA;
	unsigned char* data = new unsigned char[16];
	int len = 16;

	int _x = x*10000;
	int _y = y*10000;
	int _w = w*10000;
	int _h = h*10000;
	
	//x
	data[0] = (_x & 0xFF000000) >> 24;
	data[1] = (_x & 0x00FF0000) >> 16;
	data[2] = (_x & 0x0000FF00) >> 8;
	data[3] = (_x & 0x000000FF);

	//y
	data[4] = (_y & 0xFF000000) >> 24;
	data[5] = (_y & 0x00FF0000) >> 16;
	data[6] = (_y & 0x0000FF00) >> 8;
	data[7] = (_y & 0x000000FF);

	//w
	data[8] = (_w & 0xFF000000) >> 24;
	data[9] = (_w & 0x00FF0000) >> 16;
	data[10] = (_w & 0x0000FF00) >> 8;
	data[11] = (_w & 0x000000FF);

	//h
	data[12] = (_h & 0xFF000000) >> 24;
	data[13] = (_h & 0x00FF0000) >> 16;
	data[14] = (_h & 0x0000FF00) >> 8;
	data[15] = (_h & 0x000000FF);

	unsigned int scale_factor = 10000;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::SetSearchAreaWidth(int width)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 8;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (SET_SEARCH_AREA_LINE_WIDTH & 0xFF000000) >> 24;
	data[1] = (SET_SEARCH_AREA_LINE_WIDTH & 0x00FF0000) >> 16;
	data[2] = (SET_SEARCH_AREA_LINE_WIDTH & 0x0000FF00) >> 8;
	data[3] = (SET_SEARCH_AREA_LINE_WIDTH & 0x000000FF);

	//width
	data[4] = (width & 0xFF000000) >> 24;
	data[5] = (width & 0x00FF0000) >> 16;
	data[6] = (width & 0x0000FF00) >> 8;
	data[7] = (width & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}


int CEyedeaInterface::SetSearchAreaColor(int r, int g, int b)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 16;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (SET_SEARCH_AREA_COLOR & 0xFF000000) >> 24;
	data[1] = (SET_SEARCH_AREA_COLOR & 0x00FF0000) >> 16;
	data[2] = (SET_SEARCH_AREA_COLOR & 0x0000FF00) >> 8;
	data[3] = (SET_SEARCH_AREA_COLOR & 0x000000FF);

	//x
	data[4] = (r & 0xFF000000) >> 24;
	data[5] = (r & 0x00FF0000) >> 16;
	data[6] = (r & 0x0000FF00) >> 8;
	data[7] = (r & 0x000000FF);

	//y
	data[8] = (g & 0xFF000000) >> 24;
	data[9] = (g & 0x00FF0000) >> 16;
	data[10] = (g & 0x0000FF00) >> 8;
	data[11] = (g & 0x000000FF);

	//w
	data[12] = (b & 0xFF000000) >> 24;
	data[13] = (b & 0x00FF0000) >> 16;
	data[14] = (b & 0x0000FF00) >> 8;
	data[15] = (b & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::GetSearchAreaWidth(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_SEARCH_AREA_LINE_WIDTH & 0xFF000000) >> 24;
	data[1] = (GET_SEARCH_AREA_LINE_WIDTH & 0x00FF0000) >> 16;
	data[2] = (GET_SEARCH_AREA_LINE_WIDTH & 0x0000FF00) >> 8;
	data[3] = (GET_SEARCH_AREA_LINE_WIDTH & 0x000000FF);

	unsigned int scale_factor = 1;
	int width = 0;
    width = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(width == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			width = m_cls_eth_client->Open(m_ip, m_port);
			if(width == 0){
				width = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return width;
				}
				continue;
			}
		}
	}
	if (width != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return width;
	}

	width = 0;

	if (len >= 4)
	{
		//w
		width = ((int)data[0] << 24) & 0xFF000000;
		width |= ((int)data[1] << 16) & 0x00FF0000;
		width |= ((int)data[2] << 8) & 0x0000FF00;
		width |= ((int)data[3]) & 0x000000FF;

	}

	delete (data);
	data = NULL;

	return width;
}

int CEyedeaInterface::GetSearchAreaColor(int* out_r, int* out_g, int* out_b)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_SEARCH_AREA_COLOR & 0xFF000000) >> 24;
	data[1] = (GET_SEARCH_AREA_COLOR & 0x00FF0000) >> 16;
	data[2] = (GET_SEARCH_AREA_COLOR & 0x0000FF00) >> 8;
	data[3] = (GET_SEARCH_AREA_COLOR & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	int color_r = 0;
	int color_g = 0;
	int color_b = 0;

	if (len >= 12)
	{
		//r
		color_r = ((int)data[0] << 24) & 0xFF000000;
		color_r |= ((int)data[1] << 16) & 0x00FF0000;
		color_r |= ((int)data[2] << 8) & 0x0000FF00;
		color_r |= ((int)data[3]) & 0x000000FF;

		//g
		color_g = ((int)data[4] << 24) & 0xFF000000;
		color_g |= ((int)data[5] << 16) & 0x00FF0000;
		color_g |= ((int)data[6] << 8) & 0x0000FF00;
		color_g |= ((int)data[7]) & 0x000000FF;

		//b
		color_b = ((int)data[8] << 24) & 0xFF000000;
		color_b |= ((int)data[9] << 16) & 0x00FF0000;
		color_b |= ((int)data[10] << 8) & 0x0000FF00;
		color_b |= ((int)data[11]) & 0x000000FF;

	}

	(*out_r) = color_r;
	(*out_g) = color_g;
	(*out_b) = color_b;

	delete (data);
	data = NULL;

    return ret;
}


int CEyedeaInterface::SetMasterAreaWidth(int width)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 8;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (SET_MASTER_AREA_LINE_WIDTH & 0xFF000000) >> 24;
	data[1] = (SET_MASTER_AREA_LINE_WIDTH & 0x00FF0000) >> 16;
	data[2] = (SET_MASTER_AREA_LINE_WIDTH & 0x0000FF00) >> 8;
	data[3] = (SET_MASTER_AREA_LINE_WIDTH & 0x000000FF);

	//width
	data[4] = (width & 0xFF000000) >> 24;
	data[5] = (width & 0x00FF0000) >> 16;
	data[6] = (width & 0x0000FF00) >> 8;
	data[7] = (width & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}


int CEyedeaInterface::SetMasterAreaColor(int r, int g, int b)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 16;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (SET_MASTER_AREA_COLOR & 0xFF000000) >> 24;
	data[1] = (SET_MASTER_AREA_COLOR & 0x00FF0000) >> 16;
	data[2] = (SET_MASTER_AREA_COLOR & 0x0000FF00) >> 8;
	data[3] = (SET_MASTER_AREA_COLOR & 0x000000FF);

	//x
	data[4] = (r & 0xFF000000) >> 24;
	data[5] = (r & 0x00FF0000) >> 16;
	data[6] = (r & 0x0000FF00) >> 8;
	data[7] = (r & 0x000000FF);

	//y
	data[8] = (g & 0xFF000000) >> 24;
	data[9] = (g & 0x00FF0000) >> 16;
	data[10] = (g & 0x0000FF00) >> 8;
	data[11] = (g & 0x000000FF);

	//w
	data[12] = (b & 0xFF000000) >> 24;
	data[13] = (b & 0x00FF0000) >> 16;
	data[14] = (b & 0x0000FF00) >> 8;
	data[15] = (b & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::GetMasterAreaWidth(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_MASTER_AREA_LINE_WIDTH & 0xFF000000) >> 24;
	data[1] = (GET_MASTER_AREA_LINE_WIDTH & 0x00FF0000) >> 16;
	data[2] = (GET_MASTER_AREA_LINE_WIDTH & 0x0000FF00) >> 8;
	data[3] = (GET_MASTER_AREA_LINE_WIDTH & 0x000000FF);

	unsigned int scale_factor = 1;
	int width = 0;
    width = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(width == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			width = m_cls_eth_client->Open(m_ip, m_port);
			if(width == 0){
				width = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return width;
				}
				continue;
			}
		}
	}
	if (width != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return width;
	}

	width = 0;

	if (len >= 4)
	{
		//w
		width = ((int)data[0] << 24) & 0xFF000000;
		width |= ((int)data[1] << 16) & 0x00FF0000;
		width |= ((int)data[2] << 8) & 0x0000FF00;
		width |= ((int)data[3]) & 0x000000FF;

	}

	delete (data);
	data = NULL;

	return width;
}

int CEyedeaInterface::GetMasterAreaColor(int* out_r, int* out_g, int* out_b)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_MASTER_AREA_COLOR & 0xFF000000) >> 24;
	data[1] = (GET_MASTER_AREA_COLOR & 0x00FF0000) >> 16;
	data[2] = (GET_MASTER_AREA_COLOR & 0x0000FF00) >> 8;
	data[3] = (GET_MASTER_AREA_COLOR & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	int color_r = 0;
	int color_g = 0;
	int color_b = 0;

	if (len >= 12)
	{
		//r
		color_r = ((int)data[0] << 24) & 0xFF000000;
		color_r |= ((int)data[1] << 16) & 0x00FF0000;
		color_r |= ((int)data[2] << 8) & 0x0000FF00;
		color_r |= ((int)data[3]) & 0x000000FF;

		//g
		color_g = ((int)data[4] << 24) & 0xFF000000;
		color_g |= ((int)data[5] << 16) & 0x00FF0000;
		color_g |= ((int)data[6] << 8) & 0x0000FF00;
		color_g |= ((int)data[7]) & 0x000000FF;

		//b
		color_b = ((int)data[8] << 24) & 0xFF000000;
		color_b |= ((int)data[9] << 16) & 0x00FF0000;
		color_b |= ((int)data[10] << 8) & 0x0000FF00;
		color_b |= ((int)data[11]) & 0x000000FF;

	}

	(*out_r) = color_r;
	(*out_g) = color_g;
	(*out_b) = color_b;

	delete (data);
	data = NULL;

    return ret;
}

int CEyedeaInterface::GetSearchArea(float* out_x, float* out_y, float* out_w, float* out_h)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_SEARCH_AREA;
	unsigned char* data = new unsigned char[16];
	int len = 0;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	if (len >= 16)
	{
		//x
		int x = ((int)data[0] << 24)	&	0xFF000000 ;
		x |=	((int)data[1] << 16)	&	0x00FF0000;
		x |=	((int)data[2] << 8)		&	0x0000FF00;
		x |=	((int)data[3] )			&	0x000000FF;

		//y
		int y = ((int)data[4] << 24)	& 0xFF000000;
		y |=	((int)data[5] << 16)	& 0x00FF0000;
		y |=	((int)data[6] << 8)		& 0x0000FF00;
		y |=	((int)data[7])			& 0x000000FF;

		//w
		int w = ((int)data[8] << 24) & 0xFF000000;
		w |= ((int)data[9] << 16) & 0x00FF0000;
		w |= ((int)data[10] << 8) & 0x0000FF00;
		w |= ((int)data[11]) & 0x000000FF;

		//h
		int h = ((int)data[12] << 24) & 0xFF000000;
		h |= ((int)data[13] << 16) & 0x00FF0000;
		h |= ((int)data[14] << 8) & 0x0000FF00;
		h |= ((int)data[15]) & 0x000000FF;

		float _x = (float)x / (float)scale_factor;
		//x = (int)((float)TRANS_IAMGE_WIDTH * _x);

		float _y = (float)y / (float)scale_factor;
		//y = (int)((float)TRANS_IAMGE_HEIGHT * _y);

		float _w = (float)w / (float)scale_factor;
		//w = (int)((float)TRANS_IAMGE_WIDTH * _w);

		float _h = (float)h / (float)scale_factor;
		//h = (int)((float)TRANS_IAMGE_HEIGHT * _h);

		(*out_x) = _x;
		(*out_y) = _y;
		(*out_w) = _w;
		(*out_h) = _h;
	}

	delete data;
	data = NULL;

    return ret;
}

int CEyedeaInterface::SetObjectColor(int object, int r, int g, int b)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 20;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (SET_OBJECT_COLOR & 0xFF000000) >> 24;
	data[1] = (SET_OBJECT_COLOR & 0x00FF0000) >> 16;
	data[2] = (SET_OBJECT_COLOR & 0x0000FF00) >> 8;
	data[3] = (SET_OBJECT_COLOR & 0x000000FF);

	//x
	data[4] = (object & 0xFF000000) >> 24;
	data[5] = (object & 0x00FF0000) >> 16;
	data[6] = (object & 0x0000FF00) >> 8;
	data[7] = (object & 0x000000FF);

	//x
	data[8] = (r & 0xFF000000) >> 24;
	data[9] = (r & 0x00FF0000) >> 16;
	data[10] = (r & 0x0000FF00) >> 8;
	data[11] = (r & 0x000000FF);

	//y
	data[12] = (g & 0xFF000000) >> 24;
	data[13] = (g & 0x00FF0000) >> 16;
	data[14] = (g & 0x0000FF00) >> 8;
	data[15] = (g & 0x000000FF);

	//w
	data[16] = (b & 0xFF000000) >> 24;
	data[17] = (b & 0x00FF0000) >> 16;
	data[18] = (b & 0x0000FF00) >> 8;
	data[19] = (b & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::GetObjectColor(int object, int* out_r, int* out_g, int* out_b)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 8;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_OBJECT_COLOR & 0xFF000000) >> 24;
	data[1] = (GET_OBJECT_COLOR & 0x00FF0000) >> 16;
	data[2] = (GET_OBJECT_COLOR & 0x0000FF00) >> 8;
	data[3] = (GET_OBJECT_COLOR & 0x000000FF);

	data[4] = (object & 0xFF000000) >> 24;
	data[5] = (object & 0x00FF0000) >> 16;
	data[6] = (object & 0x0000FF00) >> 8;
	data[7] = (object & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	int color_r = 0;
	int color_g = 0;
	int color_b = 0;

	if (len >= 12)
	{
		//r
		color_r = ((int)data[0] << 24) & 0xFF000000;
		color_r |= ((int)data[1] << 16) & 0x00FF0000;
		color_r |= ((int)data[2] << 8) & 0x0000FF00;
		color_r |= ((int)data[3]) & 0x000000FF;

		//g
		color_g = ((int)data[4] << 24) & 0xFF000000;
		color_g |= ((int)data[5] << 16) & 0x00FF0000;
		color_g |= ((int)data[6] << 8) & 0x0000FF00;
		color_g |= ((int)data[7]) & 0x000000FF;

		//b
		color_b = ((int)data[8] << 24) & 0xFF000000;
		color_b |= ((int)data[9] << 16) & 0x00FF0000;
		color_b |= ((int)data[10] << 8) & 0x0000FF00;
		color_b |= ((int)data[11]) & 0x000000FF;

	}

	(*out_r) = color_r;
	(*out_g) = color_g;
	(*out_b) = color_b;

	delete (data);
	data = NULL;

    return ret;
}

int CEyedeaInterface::SetObjectWidth(int object, int width)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 12;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (SET_OBJECT_LINE_WIDTH & 0xFF000000) >> 24;
	data[1] = (SET_OBJECT_LINE_WIDTH & 0x00FF0000) >> 16;
	data[2] = (SET_OBJECT_LINE_WIDTH & 0x0000FF00) >> 8;
	data[3] = (SET_OBJECT_LINE_WIDTH & 0x000000FF);

	//object
	data[4] = (object & 0xFF000000) >> 24;
	data[5] = (object & 0x00FF0000) >> 16;
	data[6] = (object & 0x0000FF00) >> 8;
	data[7] = (object & 0x000000FF);

	//width
	data[8] = (width & 0xFF000000) >> 24;
	data[9] = (width & 0x00FF0000) >> 16;
	data[10] = (width & 0x0000FF00) >> 8;
	data[11] = (width & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::GetObjectWidth(int object)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 8;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_OBJECT_LINE_WIDTH & 0xFF000000) >> 24;
	data[1] = (GET_OBJECT_LINE_WIDTH & 0x00FF0000) >> 16;
	data[2] = (GET_OBJECT_LINE_WIDTH & 0x0000FF00) >> 8;
	data[3] = (GET_OBJECT_LINE_WIDTH & 0x000000FF);

	data[4] = (object & 0xFF000000) >> 24;
	data[5] = (object & 0x00FF0000) >> 16;
	data[6] = (object & 0x0000FF00) >> 8;
	data[7] = (object & 0x000000FF);

	unsigned int scale_factor = 1;
	int width = 0;
    width = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(width == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			width = m_cls_eth_client->Open(m_ip, m_port);
			if(width == 0){
				width = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return width;
				}
				continue;
			}
		}
	}
	if (width != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return width;
	}

	width = 0;

	if (len >= 4)
	{
		//w
		width = ((int)data[0] << 24) & 0xFF000000;
		width |= ((int)data[1] << 16) & 0x00FF0000;
		width |= ((int)data[2] << 8) & 0x0000FF00;
		width |= ((int)data[3]) & 0x000000FF;

	}

	delete (data);
	data = NULL;

	return width;
}

int CEyedeaInterface::SetMasterArea(float x, float y, float w, float h)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetMasterArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_MASTER_AREA;
	unsigned char* data = new unsigned char[16];
	int len = 16;

	int _x = x*10000;
	int _y = y*10000;
	int _w = w*10000;
	int _h = h*10000;

	//x
	data[0] = (_x & 0xFF000000) >> 24;
	data[1] = (_x & 0x00FF0000) >> 16;
	data[2] = (_x & 0x0000FF00) >> 8;
	data[3] = (_x & 0x000000FF);

	//y
	data[4] = (_y & 0xFF000000) >> 24;
	data[5] = (_y & 0x00FF0000) >> 16;
	data[6] = (_y & 0x0000FF00) >> 8;
	data[7] = (_y & 0x000000FF);

	//w
	data[8] = (_w & 0xFF000000) >> 24;
	data[9] = (_w & 0x00FF0000) >> 16;
	data[10] = (_w & 0x0000FF00) >> 8;
	data[11] = (_w & 0x000000FF);

	//h
	data[12] = (_h & 0xFF000000) >> 24;
	data[13] = (_h & 0x00FF0000) >> 16;
	data[14] = (_h & 0x0000FF00) >> 8;
	data[15] = (_h & 0x000000FF);

	unsigned int scale_factor = 10000;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::SetSelectBaseObject(float x, float y, float w, float h)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetMasterArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SELECT_BASE_OBJECT;
	unsigned char* data = new unsigned char[16];
	int len = 16;

	int _x = x * 10000;
	int _y = y * 10000;
	int _w = w * 10000;
	int _h = h * 10000;

	//x
	data[0] = (_x & 0xFF000000) >> 24;
	data[1] = (_x & 0x00FF0000) >> 16;
	data[2] = (_x & 0x0000FF00) >> 8;
	data[3] = (_x & 0x000000FF);

	//y
	data[4] = (_y & 0xFF000000) >> 24;
	data[5] = (_y & 0x00FF0000) >> 16;
	data[6] = (_y & 0x0000FF00) >> 8;
	data[7] = (_y & 0x000000FF);

	//w
	data[8] = (_w & 0xFF000000) >> 24;
	data[9] = (_w & 0x00FF0000) >> 16;
	data[10] = (_w & 0x0000FF00) >> 8;
	data[11] = (_w & 0x000000FF);

	//h
	data[12] = (_h & 0xFF000000) >> 24;
	data[13] = (_h & 0x00FF0000) >> 16;
	data[14] = (_h & 0x0000FF00) >> 8;
	data[15] = (_h & 0x000000FF);

	unsigned int scale_factor = 10000;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::SetZoomArea(float x, float y, float w, float h)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetMasterArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ZOOM_AREA;
	unsigned char* data = new unsigned char[16];
	int len = 16;

	int _x = x * 10000;
	int _y = y * 10000;
	int _w = w * 10000;
	int _h = h * 10000;

	//x
	data[0] = (_x & 0xFF000000) >> 24;
	data[1] = (_x & 0x00FF0000) >> 16;
	data[2] = (_x & 0x0000FF00) >> 8;
	data[3] = (_x & 0x000000FF);

	//y
	data[4] = (_y & 0xFF000000) >> 24;
	data[5] = (_y & 0x00FF0000) >> 16;
	data[6] = (_y & 0x0000FF00) >> 8;
	data[7] = (_y & 0x000000FF);

	//w
	data[8] = (_w & 0xFF000000) >> 24;
	data[9] = (_w & 0x00FF0000) >> 16;
	data[10] = (_w & 0x0000FF00) >> 8;
	data[11] = (_w & 0x000000FF);

	//h
	data[12] = (_h & 0xFF000000) >> 24;
	data[13] = (_h & 0x00FF0000) >> 16;
	data[14] = (_h & 0x0000FF00) >> 8;
	data[15] = (_h & 0x000000FF);

	unsigned int scale_factor = 10000;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while (1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if (ret == 0) {
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::SetMaskArea(float x, float y, float w, float h, bool inverse)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetMasterArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_MASK_AREA;
	int len = 20;
	unsigned char* data = new unsigned char[len];

	int _x = x * 10000;
	int _y = y * 10000;
	int _w = w * 10000;
	int _h = h * 10000;
	int i = 0;
	if (inverse) i = 1;
	int _i = i * 10000;

	//x
	data[0] = (_x & 0xFF000000) >> 24;
	data[1] = (_x & 0x00FF0000) >> 16;
	data[2] = (_x & 0x0000FF00) >> 8;
	data[3] = (_x & 0x000000FF);

	//y
	data[4] = (_y & 0xFF000000) >> 24;
	data[5] = (_y & 0x00FF0000) >> 16;
	data[6] = (_y & 0x0000FF00) >> 8;
	data[7] = (_y & 0x000000FF);

	//w
	data[8] = (_w & 0xFF000000) >> 24;
	data[9] = (_w & 0x00FF0000) >> 16;
	data[10] = (_w & 0x0000FF00) >> 8;
	data[11] = (_w & 0x000000FF);

	//h
	data[12] = (_h & 0xFF000000) >> 24;
	data[13] = (_h & 0x00FF0000) >> 16;
	data[14] = (_h & 0x0000FF00) >> 8;
	data[15] = (_h & 0x000000FF);

	//i
	data[16] = (_i & 0xFF000000) >> 24;
	data[17] = (_i & 0x00FF0000) >> 16;
	data[18] = (_i & 0x0000FF00) >> 8;
	data[19] = (_i & 0x000000FF);

	unsigned int scale_factor = 10000;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while (1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if (ret == 0) {
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::UndoMaskArea(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetMasterArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_UNDO_MASK_AREA;
	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 10000;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while (1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if (ret == 0) {
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::DelMaskArea(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetMasterArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_DEL_MASK_AREA;
	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 10000;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while (1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if (ret == 0) {
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::ResetZoomArea(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetMasterArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_RESET_ZOOM_AREA;
	unsigned char* data = NULL;
	int len = 0;

	unsigned int scale_factor = 10000;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while (1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if (ret == 0) {
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::GetObjectCircle(float *out_x, float *out_y, float *out_r1, float *out_r2)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_OBJECT;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	int type = 1;		//circle

	//x
	data[0] = (type & 0xFF000000) >> 24;
	data[1] = (type & 0x00FF0000) >> 16;
	data[2] = (type & 0x0000FF00) >> 8;
	data[3] = (type & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	if (len >= 16)
	{
		//x
		int x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		//y
		int y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		//r1
		int r1 = ((int)data[8] << 24) & 0xFF000000;
		r1 |= ((int)data[9] << 16) & 0x00FF0000;
		r1 |= ((int)data[10] << 8) & 0x0000FF00;
		r1 |= ((int)data[11]) & 0x000000FF;

		//r2
		int r2 = ((int)data[12] << 24) & 0xFF000000;
		r2 |= ((int)data[13] << 16) & 0x00FF0000;
		r2 |= ((int)data[14] << 8) & 0x0000FF00;
		r2 |= ((int)data[15]) & 0x000000FF;

		float _x = (float)x / (float)scale_factor;
		//_x = (float)(((_x*640.0) * (float)TRANS_IAMGE_WIDTH) / 640.0);
		//x = (int)((float)m_source.gray.cols*((_x*640.0))/((float)m_source.gray.cols)) ;
		//x = (int)((float)m_source.gray.cols * _x) ;

		float _y = (float)y / (float)scale_factor;
		//_y = (float)(((_y*480.0) * (float)TRANS_IAMGE_HEIGHT) / 480.0);
		//y = (int)((float)m_source.gray.rows*((_y*480.0)/((float)m_source.gray.rows))) ;
		//y = (int)((float)m_source.gray.rows * _y) ;

		float _r1 = (float)r1 / (float)scale_factor;
		//_r1 = (float)(((_r1*640.0) * (float)TRANS_IAMGE_WIDTH) / 640.0);
		//w = (int)((float)m_source.gray.cols*((_w*640.0))/((float)m_source.gray.cols)) ;
		//w = (int)((float)m_source.gray.cols * _w) ;

		float _r2 = (float)r2 / (float)scale_factor;
		//_r2 = (float)(((_r2*480.0) * (float)TRANS_IAMGE_HEIGHT) / 480.0);
		//h = (int)((float)m_source.gray.rows*((_h*480.0)/((float)m_source.gray.rows))) ;
		//h = (int)((float)m_source.gray.rows * _h) ;

		(*out_x) = _x ;
		(*out_y) = _y ;
		(*out_r1) = _r1 ;
		(*out_r2) = _r2 ;
	}

	delete (data);
	data = NULL;

    return ret;
}

int CEyedeaInterface::SetObjectCircle(float x, float y, float r1, float r2)
{
	//printf("test = %f, %f, %f, %f\n", x, y, r1, r2);

	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_SET_OBJECT_CIRCLE;
	unsigned char* data = new unsigned char[16];
	int len = 16;

	int _x = x*10000;
	int _y = y*10000;
	int _r1 = r1*10000;
	int _r2 = r2*10000;
	

	//x
	data[0] = (_x & 0xFF000000) >> 24;
	data[1] = (_x & 0x00FF0000) >> 16;
	data[2] = (_x & 0x0000FF00) >> 8;
	data[3] = (_x & 0x000000FF);

	//y
	data[4] = (_y & 0xFF000000) >> 24;
	data[5] = (_y & 0x00FF0000) >> 16;
	data[6] = (_y & 0x0000FF00) >> 8;
	data[7] = (_y & 0x000000FF);

	//r1
	data[8] = (_r1 & 0xFF000000) >> 24;
	data[9] = (_r1 & 0x00FF0000) >> 16;
	data[10] = (_r1 & 0x0000FF00) >> 8;
	data[11] = (_r1 & 0x000000FF);

	//r2
	data[12] = (_r2 & 0xFF000000) >> 24;
	data[13] = (_r2 & 0x00FF0000) >> 16;
	data[14] = (_r2 & 0x0000FF00) >> 8;
	data[15] = (_r2 & 0x000000FF);


	unsigned int scale_factor = 10000;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::SetObjectLine(float x, float y, float w, float h)
{
	//printf("test = %f, %f, %f, %f\n", x, y, r1, r2);

	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_SET_OBJECT_LINE;
	unsigned char* data = new unsigned char[16];
	int len = 16;

	int _x = x * 10000;
	int _y = y * 10000;
	int _w = w * 10000;
	int _h = h * 10000;


	//x
	data[0] = (_x & 0xFF000000) >> 24;
	data[1] = (_x & 0x00FF0000) >> 16;
	data[2] = (_x & 0x0000FF00) >> 8;
	data[3] = (_x & 0x000000FF);

	//y
	data[4] = (_y & 0xFF000000) >> 24;
	data[5] = (_y & 0x00FF0000) >> 16;
	data[6] = (_y & 0x0000FF00) >> 8;
	data[7] = (_y & 0x000000FF);

	//r1
	data[8] = (_w & 0xFF000000) >> 24;
	data[9] = (_w & 0x00FF0000) >> 16;
	data[10] = (_w & 0x0000FF00) >> 8;
	data[11] = (_w & 0x000000FF);

	//r2
	data[12] = (_h & 0xFF000000) >> 24;
	data[13] = (_h & 0x00FF0000) >> 16;
	data[14] = (_h & 0x0000FF00) >> 8;
	data[15] = (_h & 0x000000FF);


	unsigned int scale_factor = 10000;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while (1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if (ret == 0) {
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::GetMainObjectInfo(float* out_x, float* out_y, float* out_a)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_MAIN_OBJECT_INFO;
	unsigned char* data = new unsigned char[12];
	int len = 0;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	if (len >= 12)
	{
		//x
		int x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		//y
		int y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		//w
		int a = ((int)data[8] << 24) & 0xFF000000;
		a |= ((int)data[9] << 16) & 0x00FF0000;
		a |= ((int)data[10] << 8) & 0x0000FF00;
		a |= ((int)data[11]) & 0x000000FF;


		float _x = (float)x / (float)scale_factor;
		float _y = (float)y / (float)scale_factor;
		float _a = (float)a / (float)scale_factor;

		(*out_x) = _x;
		(*out_y) = _y;
		(*out_a) = _a;
	}

	delete data;
	data = NULL;

    return ret;
}

int CEyedeaInterface::GetCircleInfoCameraBase(float* out_x, float* out_y, float* out_r, int id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//// select list  ------------------------------------------------------------------------
	int len2 = 4;
	unsigned char* data2 = new unsigned char[4];
	char command = COMMAND_SET_SELECT_LIST_BY_ID;

	id += 1;

	//x
	data2[0] = (id & 0xFF000000) >> 24;
	data2[1] = (id & 0x00FF0000) >> 16;
	data2[2] = (id & 0x0000FF00) >> 8;
	data2[3] = (id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data2, &len2);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data2, &len2);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data2 != NULL)
					{
						delete data2;
						data2 = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data2 != NULL)
		{
			delete data2;
			data2 = NULL;
		}
		return ret;
	}

	delete (data2);
	data2 = NULL;

	command = COMMAND_GET_CIRCLE_INFO_CAMERA_BASE;
	unsigned char* data = new unsigned char[12];
	int len = 0;

	scale_factor = 1;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	if (len >= 12)
	{
		//x
		int x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		//y
		int y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		//w
		int r = ((int)data[8] << 24) & 0xFF000000;
		r |= ((int)data[9] << 16) & 0x00FF0000;
		r |= ((int)data[10] << 8) & 0x0000FF00;
		r |= ((int)data[11]) & 0x000000FF;


		float _x = (float)x / (float)scale_factor;
		float _y = (float)y / (float)scale_factor;
		float _r = (float)r / (float)scale_factor;

		(*out_x) = _x;
		(*out_y) = _y;
		(*out_r) = _r;
	}

	delete data;
	data = NULL;

    return ret;
}

int CEyedeaInterface::GetCircleInfoRobotBase(float* out_x, float* out_y, float* out_r, int id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//// select list  ------------------------------------------------------------------------
	int len2 = 4;
	unsigned char* data2 = new unsigned char[4];
	char command = COMMAND_SET_SELECT_LIST_BY_ID;

	id += 1;

	//x
	data2[0] = (id & 0xFF000000) >> 24;
	data2[1] = (id & 0x00FF0000) >> 16;
	data2[2] = (id & 0x0000FF00) >> 8;
	data2[3] = (id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data2, &len2);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data2, &len2);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data2 != NULL)
					{
						delete data2;
						data2 = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data2 != NULL)
		{
			delete data2;
			data2 = NULL;
		}
		return ret;
	}

	delete (data2);
	data2 = NULL;

	command = COMMAND_GET_CIRCLE_INFO_ROBOT_BASE;
	unsigned char* data = new unsigned char[12];
	int len = 0;

	scale_factor = 1;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	if (len >= 12)
	{
		//x
		int x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		//y
		int y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		//w
		int r = ((int)data[8] << 24) & 0xFF000000;
		r |= ((int)data[9] << 16) & 0x00FF0000;
		r |= ((int)data[10] << 8) & 0x0000FF00;
		r |= ((int)data[11]) & 0x000000FF;


		float _x = (float)x / (float)scale_factor;
		float _y = (float)y / (float)scale_factor;
		float _r = (float)r / (float)scale_factor;

		(*out_x) = _x;
		(*out_y) = _y;
		(*out_r) = _r;
	}

	delete data;
	data = NULL;

    return ret;
}

int CEyedeaInterface::GetCircleInfoImageBase(float* out_x, float* out_y, float* out_r, int id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//// select list  ------------------------------------------------------------------------
	int len2 = 4;
	unsigned char* data2 = new unsigned char[4];
	char command = COMMAND_SET_SELECT_LIST_BY_ID;

	id += 1;

	//x
	data2[0] = (id & 0xFF000000) >> 24;
	data2[1] = (id & 0x00FF0000) >> 16;
	data2[2] = (id & 0x0000FF00) >> 8;
	data2[3] = (id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data2, &len2);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data2, &len2);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data2 != NULL)
					{
						delete data2;
						data2 = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data2 != NULL)
		{
			delete data2;
			data2 = NULL;
		}
		return ret;
	}

	delete (data2);
	data2 = NULL;

	command = COMMAND_GET_CIRCLE_INFO;
	unsigned char* data = new unsigned char[12];
	int len = 0;

	scale_factor = 1;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	if (len >= 12)
	{
		//x
		int x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		//y
		int y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		//w
		int r = ((int)data[8] << 24) & 0xFF000000;
		r |= ((int)data[9] << 16) & 0x00FF0000;
		r |= ((int)data[10] << 8) & 0x0000FF00;
		r |= ((int)data[11]) & 0x000000FF;


		float _x = (float)x / (float)scale_factor;
		float _y = (float)y / (float)scale_factor;
		float _r = (float)r / (float)scale_factor;

		(*out_x) = _x;
		(*out_y) = _y;
		(*out_r) = _r;
	}

	delete data;
	data = NULL;

    return ret;
}

int CEyedeaInterface::GetMasterArea(float* out_x, float* out_y, float* out_w, float* out_h)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_MASTER_AREA;
	unsigned char* data = new unsigned char[16];
	int len = 0;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	if (len >= 16)
	{
		//x
		int x = ((int)data[0] << 24) & 0xFF000000;
		x |= ((int)data[1] << 16) & 0x00FF0000;
		x |= ((int)data[2] << 8) & 0x0000FF00;
		x |= ((int)data[3]) & 0x000000FF;

		//y
		int y = ((int)data[4] << 24) & 0xFF000000;
		y |= ((int)data[5] << 16) & 0x00FF0000;
		y |= ((int)data[6] << 8) & 0x0000FF00;
		y |= ((int)data[7]) & 0x000000FF;

		//w
		int w = ((int)data[8] << 24) & 0xFF000000;
		w |= ((int)data[9] << 16) & 0x00FF0000;
		w |= ((int)data[10] << 8) & 0x0000FF00;
		w |= ((int)data[11]) & 0x000000FF;

		//h
		int h = ((int)data[12] << 24) & 0xFF000000;
		h |= ((int)data[13] << 16) & 0x00FF0000;
		h |= ((int)data[14] << 8) & 0x0000FF00;
		h |= ((int)data[15]) & 0x000000FF;

		float _x = (float)x / (float)scale_factor;
		//x = (int)((float)TRANS_IAMGE_WIDTH * _x);

		float _y = (float)y / (float)scale_factor;
		//y = (int)((float)TRANS_IAMGE_HEIGHT * _y);

		float _w = (float)w / (float)scale_factor;
		//w = (int)((float)TRANS_IAMGE_WIDTH * _w);

		float _h = (float)h / (float)scale_factor;
		//h = (int)((float)TRANS_IAMGE_HEIGHT * _h);

		(*out_x) = _x;
		(*out_y) = _y;
		(*out_w) = _w;
		(*out_h) = _h;
	}

	delete data;
	data = NULL;

    return ret;
}

int CEyedeaInterface::OptionPCAOn(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_SET_OPTION;
	unsigned char* data = new unsigned char[1];

	data[0] = 0x01;		//set option - pca on

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}
    return ret;
}

int CEyedeaInterface::SetOptionFindWithCheckDefectOn(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_SET_OPTION;
	unsigned char* data = new unsigned char[1];

	data[0] = 0x07;		//set option 

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::SetOptionFindWithCheckDefectOff(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_SET_OPTION;
	unsigned char* data = new unsigned char[1];

	data[0] = 0x08;		//set option 

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::GetOptionFindWithCheckDefect(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_OPTION;
	unsigned char* data = new unsigned char[1];

	data[0] = 0x07;		//get option - with check defect

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0;

	if (len >= 1)
	{
		ret = data[0];
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::SetNextImage(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_SET_NEXT_IMAGE;
	unsigned char* data = new unsigned char[1];

	data[0] = 0x01;		//set option - pca on

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::GetOptionPCA(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_OPTION;
	unsigned char* data = new unsigned char[1];

	data[0] = 0x06;		//get option - pca

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0;
	
	if (len >= 1)
	{
		ret = data[0];
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::OptionPCAOff(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_SET_OPTION;
	unsigned char* data = new unsigned char[1];
	
	data[0] = 0x02;		//set option - pca off

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::OptionFixSearchAreaOn(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_SET_OPTION;
	unsigned char* data = new unsigned char[1];

	data[0] = 0x03;		//set option - OptionFixSearchAreaOn

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}if (data != NULL)
				{
					delete data;
					data = NULL;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::OptionFixSearchAreaOff(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_SET_OPTION;
	unsigned char* data = new unsigned char[1];

	data[0] = 0x04;		//set option - OptionFixSearchAreaOn

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
				
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::OptionFixSearchUserRoiOn(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_SET_OPTION;
	unsigned char* data = new unsigned char[1];

	data[0] = 0x05;		//set option - OptionFixSearchAreaOn

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::OptionFixSearchUserRoiOff(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_SET_OPTION;
	unsigned char* data = new unsigned char[1];

	data[0] = 0x06;		//set option - OptionFixSearchAreaOn

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::FindObject(int id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_RUN_FIND_OBJECT;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//id
	data[0] = (id & 0xFF000000) >> 24;
	data[1] = (id & 0x00FF0000) >> 16;
	data[2] = (id & 0x0000FF00) >> 8;
	data[3] = (id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0;

	if (len >= 1)
	{
		ret = (int)data[0];
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::FindObjectWithoutPCA(int id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_RUN_FIND_OBJECT_WITHOUT_PCA;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//id
	data[0] = (id & 0xFF000000) >> 24;
	data[1] = (id & 0x00FF0000) >> 16;
	data[2] = (id & 0x0000FF00) >> 8;
	data[3] = (id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0;

	if (len >= 1)
	{
	    ret = (int)data[0];
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::FindAllObjectWithPCA(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_RUN_FIND_ALL_OBJECT_WITH_PCA;
	unsigned char* data = new unsigned char[1];

	data[0] = 0x00;

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0;

	if (len >= 1)
	{
		ret = (int)data[0];
	}

	delete data;
	data = NULL;

	return EYEDEA_ERROR_INVALID_MEMORY;
}

int CEyedeaInterface::FindObjectWithPCA(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_RUN_FIND_OBJECT_WITH_PCA;
	unsigned char* data = new unsigned char[1];

	data[0] = 0x00;

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	ret = 0;

	if (len >= 1)
	{
		ret = (int)data[0];
	}

	delete data;
	data = NULL;

	return EYEDEA_ERROR_INVALID_MEMORY;
}

int CEyedeaInterface::GetOptionFixSearchArea(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_OPTION;
	unsigned char* data = new unsigned char[1];

	data[0] = 0x01;		//get status of fix search area option 

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0;
	
	if (len >= 1)
	{
		ret = (int)data[0];
	}

	//printf("int ret = 0;	//printf("len = %d\n", len);

	delete data;
	data = NULL;

	return ret ;

}

int CEyedeaInterface::GetOptionFixSearchUserRoi(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_OPTION;
	unsigned char* data = new unsigned char[1];

	data[0] = 0x05;		//get status of fix search uroi option 

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	ret = 0;

	if (len >= 1)
	{
		ret = (int)data[0];
	}

	//printf("int ret = 0;	//printf("len = %d\n", len);

	delete data;
	data = NULL;

	return ret;

}

unsigned int CEyedeaInterface::GetNewID(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_OPTION;
	unsigned char* data = new unsigned char[1];

	data[0] = 0x02;		//get new ID 

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0;

	if (len >= 1)
	{
		ret = (int)data[0];
	}

	//printf("int ret = 0;	//printf("len = %d\n", len);

	delete data;
	data = NULL;

	return ret;

}

int CEyedeaInterface::FileLoadObjectListInfo(std::string path)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_OBJECT_LIST_FILELOAD;

	int len = path.length() + 1;
	unsigned char* data = new unsigned char[len];
	memset(data, 0, len);

	std::copy(path.begin(), path.end(), data);

	//id
#if 0
	data[0] = (id & 0xFF000000) >> 24;
	data[1] = (id & 0x00FF0000) >> 16;
	data[2] = (id & 0x0000FF00) >> 8;
	data[3] = (id & 0x000000FF);
#endif

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0;

	if (len >= 4)
	{
		//w
		ret = ((int)data[0] << 24) & 0xFF000000;
		ret |= ((int)data[1] << 16) & 0x00FF0000;
		ret |= ((int)data[2] << 8) & 0x0000FF00;
		ret |= ((int)data[3]) & 0x000000FF;
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::FileSaveObjectListInfo(std::string path)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_OBJECT_LIST_FILESAVE;

	int len = path.length()+1;
	unsigned char* data = new unsigned char[len];
	memset(data, 0, len);

	std::copy(path.begin(), path.end(), data);

	//id
#if 0
	data[0] = (id & 0xFF000000) >> 24;
	data[1] = (id & 0x00FF0000) >> 16;
	data[2] = (id & 0x0000FF00) >> 8;
	data[3] = (id & 0x000000FF);
#endif

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

    ret = 0;

	if (len >= 1)
	{
		ret = (int)data[0];
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::FileLoadCheckDefectListInfo(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_CHECKDEFECT_LIST_FILELOAD;

	
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//id
#if 0
	data[0] = (id & 0xFF000000) >> 24;
	data[1] = (id & 0x00FF0000) >> 16;
	data[2] = (id & 0x0000FF00) >> 8;
	data[3] = (id & 0x000000FF);
#endif

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0;

	if (len >= 4)
	{
		//w
		ret = ((int)data[0] << 24) & 0xFF000000;
		ret |= ((int)data[1] << 16) & 0x00FF0000;
		ret |= ((int)data[2] << 8) & 0x0000FF00;
		ret |= ((int)data[3]) & 0x000000FF;
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::FileSaveCheckDefectListInfo(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_CHECKDEFECT_LIST_FILESAVE;

	int len = 4;
	unsigned char* data = new unsigned char[len] ;

	//id
#if 0
	data[0] = (id & 0xFF000000) >> 24;
	data[1] = (id & 0x00FF0000) >> 16;
	data[2] = (id & 0x0000FF00) >> 8;
	data[3] = (id & 0x000000FF);
#endif

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0;

	if (len >= 1)
	{
		ret = (int)data[0];
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::DelObjectListInfo(int id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_OBJECT_LIST_DEL;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//id
	data[0] = (id & 0xFF000000) >> 24;
	data[1] = (id & 0x00FF0000) >> 16;
	data[2] = (id & 0x0000FF00) >> 8;
	data[3] = (id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0;

	if (len >= 1)
	{
		ret = (int)data[0];
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::DelCheckDefectListInfo(int id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_CHECKDEFECT_LIST_DEL;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//id
	data[0] = (id & 0xFF000000) >> 24;
	data[1] = (id & 0x00FF0000) >> 16;
	data[2] = (id & 0x0000FF00) >> 8;
	data[3] = (id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

    ret = 0;

	if (len >= 1)
	{
	    ret = (int)data[0];
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::SetBase(int dep_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMAMND_RUN_FIND_OBJECT_WITHOUT_PCA
	char command = COMMAND_SET_BASE;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//id
	data[0] = (dep_id & 0xFF000000) >> 24;
	data[1] = (dep_id & 0x00FF0000) >> 16;
	data[2] = (dep_id & 0x0000FF00) >> 8;
	data[3] = (dep_id & 0x000000FF);


	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::SaveInformation(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMAMND_RUN_FIND_OBJECT_WITHOUT_PCA
	char command = COMMAND_SAVE_INFORMATION;
	unsigned char* data = new unsigned char[1];
	data[0] = 0x00;
	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::LoadInformation(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMAMND_RUN_FIND_OBJECT_WITHOUT_PCA
	char command = COMMAND_LOAD_INFORMATION;
	unsigned char* data = new unsigned char[1];
	data[0] = 0x00;
	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::GetSelectObject(float* out_x, float* out_y, int* out_width, int* out_height)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_SET_OBJECT_POSITION;

	int len = 0;
	unsigned char* data = NULL; // new char[len];

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	if (len >= 16)
	{
		//x
		int i_x = ((int)data[0] << 24) & 0xFF000000;
		i_x |= ((int)data[1] << 16) & 0x00FF0000;
		i_x |= ((int)data[2] << 8) & 0x0000FF00;
		i_x |= ((int)data[3]) & 0x000000FF;

		(*out_x) = i_x / (float)scale_factor;

		//y
		int i_y = ((int)data[4] << 24) & 0xFF000000;
		i_y |= ((int)data[5] << 16) & 0x00FF0000;
		i_y |= ((int)data[6] << 8) & 0x0000FF00;
		i_y |= ((int)data[7]) & 0x000000FF;

		(*out_y) = i_y / (float)scale_factor;

		//w
		int i_w = ((int)data[8] << 24) & 0xFF000000;
		i_w |= ((int)data[9] << 16) & 0x00FF0000;
		i_w |= ((int)data[10] << 8) & 0x0000FF00;
		i_w |= ((int)data[11]) & 0x000000FF;

		(*out_width) = i_w;

		//h
		int i_h = ((int)data[12] << 24) & 0xFF000000;
		i_h |= ((int)data[13] << 16) & 0x00FF0000;
		i_h |= ((int)data[14] << 8) & 0x0000FF00;
		i_h |= ((int)data[15]) & 0x000000FF;

		(*out_height) = i_h;
	}

	delete data;
	data = NULL;

    return ret;
}

int CEyedeaInterface::SetSelectObject(float x, float y, int width, int height)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_SET_OBJECT_POSITION;

	int len = 16;
	unsigned char* data = new unsigned char[len];

	int _x = x * 10000;
	int _y = y * 10000;

	//x
	data[0] = (_x & 0xFF000000) >> 24;
	data[1] = (_x & 0x00FF0000) >> 16;
	data[2] = (_x & 0x0000FF00) >> 8;
	data[3] = (_x & 0x000000FF);

	//y
	data[4] = (_y & 0xFF000000) >> 24;
	data[5] = (_y & 0x00FF0000) >> 16;
	data[6] = (_y & 0x0000FF00) >> 8;
	data[7] = (_y & 0x000000FF);

	//w
	data[8] = (width & 0xFF000000) >> 24;
	data[9] = (width & 0x00FF0000) >> 16;
	data[10] = (width & 0x0000FF00) >> 8;
	data[11] = (width & 0x000000FF);

	//h
	data[12] = (height & 0xFF000000) >> 24;
	data[13] = (height & 0x00FF0000) >> 16;
	data[14] = (height & 0x0000FF00) >> 8;
	data[15] = (height & 0x000000FF);

	unsigned int scale_factor = 10000;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::SetCheckDefect(int id, bool fixarea, bool checkoption1, float optionscore1, bool checkoption2, float optionscore2, int OptionAndOr)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_CHECKDEFECT_SET;

	int len = 13;
	unsigned char* data = new unsigned char[len];

	data[0] = id ;

	if (checkoption1)
		data[1] = 1;
	else
		data[1] = 0;

	unsigned int i_optionscore1 = (unsigned int)(optionscore1 * 100.0);

	//score1
	data[2] = (i_optionscore1 & 0xFF000000) >> 24;
	data[3] = (i_optionscore1 & 0x00FF0000) >> 16;
	data[4] = (i_optionscore1 & 0x0000FF00) >> 8;
	data[5] = (i_optionscore1 & 0x000000FF);

	if (checkoption2)
		data[6] = 1;
	else
		data[6] = 0;

	unsigned int i_optionscore2 = (unsigned int)(optionscore2 * 100.0);

	//score1
	data[7] = (i_optionscore2 & 0xFF000000) >> 24;
	data[8] = (i_optionscore2 & 0x00FF0000) >> 16;
	data[9] = (i_optionscore2 & 0x0000FF00) >> 8;
	data[10] = (i_optionscore2 & 0x000000FF);

	//OptionAndOr
	data[11] = OptionAndOr + 1;

	if (fixarea)
		data[12] = 1;
	else
		data[12] = 0;

	unsigned int scale_factor = 100;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}
    return ret;
}

unsigned int CEyedeaInterface::GetCheckDefectLinstNum(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_OPTION;
	unsigned char* data = new unsigned char[1];

	data[0] = 0x03;		//get Check Defect List Num 

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	ret = 0;

	if (len >= 1)
	{
		ret = (int)data[0];
	}

	//printf("int ret = 0;	//printf("len = %d\n", len);

	delete data;
	data = NULL;

	return ret;
}

unsigned int CEyedeaInterface::GetObjectLinstNum(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_OPTION;
	unsigned char* data = new unsigned char[1];

	data[0] = 0x04;		//get Object List Num 

	int len = 1;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0;

	if (len >= 1)
	{
		ret = (int)data[0];
	}

	//printf("int ret = 0;	//printf("len = %d\n", len);

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::CreateSocket(char* ip, int port)
{
	m_ip = new char[strlen(ip)];
	strcpy(m_ip, ip);
	m_port = port;

	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client)
	{
		//m_cls_eth_client->Close();

		//delete m_cls_eth_client;
		//m_cls_eth_client = NULL;
        return EYEDEA_ERROR_ALREADY_CONNECT;
	}

	m_cls_eth_client = new CEyedeaEthernetClient();

	int ret;

	//int sec = 0;

	/*
	while(1){
		ret = m_cls_eth_client->Open(ip, port);
		if(ret == 0)
			break;
		else
		{
			boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
			sec++;
			if(sec >= 60)
				break;
			continue;
		}
	}
	//return m_cls_eth_client->Open(ip, port);
	*/
	ret = m_cls_eth_client->Open(ip, port);

	if (ret != 0)
	{
		delete m_cls_eth_client;
		m_cls_eth_client = NULL;
	}

	return ret;
}

void CEyedeaInterface::DeleteSocket()
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return;
	}

	m_cls_eth_client->Close();
    delete(m_cls_eth_client);
    m_cls_eth_client = NULL;
}

int CEyedeaInterface::GetObjectListInfo(const int index, int *id, int *type)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_OBJECT_GET;

	int len = 17;
	unsigned char* data = new unsigned char[len];

	//index
	data[0] = (index & 0xFF000000) >> 24;
	data[1] = (index & 0x00FF0000) >> 16;
	data[2] = (index & 0x0000FF00) >> 8;
	data[3] = (index & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	if (len >= 5)
	{
		//id
		int get_id = ((int)data[0] << 24) & 0xFF000000;
		get_id |= ((int)data[1] << 16) & 0x00FF0000;
		get_id |= ((int)data[2] << 8) & 0x0000FF00;
		get_id |= ((int)data[3]) & 0x000000FF;
		(*id) = get_id;

		//type
		(*type) = (int)data[4] ;

	}

	delete data;
	data = NULL;

    return ret;
}

float CEyedeaInterface::GetBaseInfo(int option)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_GET_BASE_INFO;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (option & 0xFF000000) >> 24;
	data[1] = (option & 0x00FF0000) >> 16;
	data[2] = (option & 0x0000FF00) >> 8;
	data[3] = (option & 0x000000FF);

	unsigned int scale_factor = 1;
	float ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0.0;

	if (len >= 4)
	{
		//value
		int get_value = ((int)data[0] << 24) & 0xFF000000;
		get_value |= ((int)data[1] << 16) & 0x00FF0000;
		get_value |= ((int)data[2] << 8) & 0x0000FF00;
		get_value |= ((int)data[3]) & 0x000000FF;
		ret = (float)get_value/ (float)scale_factor;

	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::GetCheckDefectListInfo(const int index, int *id, bool *fixarea, bool *checkoption1, float *optionscore1, bool *checkoption2, float *optionscore2, int *OptionAndOr)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_CHECKDEFECT_GET;

	int len = 17;
	unsigned char* data = new unsigned char[len];

	//score1
	data[0] = (index & 0xFF000000) >> 24;
	data[1] = (index & 0x00FF0000) >> 16;
	data[2] = (index & 0x0000FF00) >> 8;
	data[3] = (index & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	if (len >= 16)
	{
		//id
		int get_id = ((int)data[0] << 24) & 0xFF000000;
		get_id |= ((int)data[1] << 16) & 0x00FF0000;
		get_id |= ((int)data[2] << 8) & 0x0000FF00;
		get_id |= ((int)data[3]) & 0x000000FF;
		(*id) = get_id ;

		//checkoption1
		bool get_checkoption1 = (int)data[4];
		(*checkoption1) = get_checkoption1;

		//optionscore1
		int get_optionscore1 = ((int)data[5] << 24) & 0xFF000000;
		get_optionscore1 |= ((int)data[6] << 16) & 0x00FF0000;
		get_optionscore1 |= ((int)data[7] << 8) & 0x0000FF00;
		get_optionscore1 |= ((int)data[8]) & 0x000000FF;

		float f_optionscore1 = (float)get_optionscore1 / (float)scale_factor;
		(*optionscore1) = f_optionscore1;

		//checkoption2
		bool get_checkoption2 = (int)data[9];
		(*checkoption2) = get_checkoption2;

		//optionscore2
		int get_optionscore2 = ((int)data[10] << 24) & 0xFF000000;
		get_optionscore2 |= ((int)data[11] << 16) & 0x00FF0000;
		get_optionscore2 |= ((int)data[12] << 8) & 0x0000FF00;
		get_optionscore2 |= ((int)data[13]) & 0x000000FF;

		float f_optionscore2 = (float)get_optionscore2 / (float)scale_factor;
		(*optionscore2) = f_optionscore2;

		//OptionAndOr
		int get_OptionAndOr = (int)data[14];
		(*OptionAndOr) = get_OptionAndOr;

		//OptionAndOr
		bool get_fixarea = (int)data[15];
		(*fixarea) = get_fixarea;
	}

	delete data;
	data = NULL;

    return ret;
}

int CEyedeaInterface::CheckDefectList(int id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_CHECKDEFECT_LIST;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//score1
	data[0] = (id & 0xFF000000) >> 24;
	data[1] = (id & 0x00FF0000) >> 16;
	data[2] = (id & 0x0000FF00) >> 8;
	data[3] = (id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	ret = 0;

	if (len >= 1)
	{
		ret = (int)data[0];
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::CheckDefectUserOption(bool checkoption1, float optionscore1, bool checkoption2, float optionscore2, int OptionAndOr)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_CHECKDEFECT_USEROPTION;

	int len = 11;
	unsigned char* data = new unsigned char[len];

	if (checkoption1)
		data[0] = 1;
	else
		data[0] = 0;

	unsigned int i_optionscore1 = (unsigned int)(optionscore1 * 100.0);

	//score1
	data[1] = (i_optionscore1 & 0xFF000000) >> 24;
	data[2] = (i_optionscore1 & 0x00FF0000) >> 16;
	data[3] = (i_optionscore1 & 0x0000FF00) >> 8;
	data[4] = (i_optionscore1 & 0x000000FF);

	if (checkoption2)
		data[5] = 1;
	else
		data[5] = 0;

	unsigned int i_optionscore2 = (unsigned int)(optionscore2 * 100.0);

	//score1
	data[6] = (i_optionscore2 & 0xFF000000) >> 24;
	data[7] = (i_optionscore2 & 0x00FF0000) >> 16;
	data[8] = (i_optionscore2 & 0x0000FF00) >> 8;
	data[9] = (i_optionscore2 & 0x000000FF);

	//OptionAndOr
	data[10] = OptionAndOr + 1;

	unsigned int scale_factor = 100;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	ret = 0;
	if (len >= 1)
	{
		ret = data[0];
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::CheckDefect(float threshold)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_CHECKDEFECT;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//threshold
	int i_threshold = (int)(threshold * 10000.0);

	data[0] = (i_threshold & 0xFF000000) >> 24;
	data[1] = (i_threshold & 0x00FF0000) >> 16;
	data[2] = (i_threshold & 0x0000FF00) >> 8;
	data[3] = (i_threshold & 0x000000FF);

	unsigned int scale_factor = 10000;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0;
	if (len >= 1)
	{
		ret = data[0];
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::GetObjectFeatureUse(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_SET_ENV;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	data[0] = (GET_OBJECT_USE_FEATURE & 0xFF000000) >> 24;
	data[1] = (GET_OBJECT_USE_FEATURE & 0x00FF0000) >> 16;
	data[2] = (GET_OBJECT_USE_FEATURE & 0x0000FF00) >> 8;
	data[3] = (GET_OBJECT_USE_FEATURE & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0;
	if (len >= 1)
	{
		ret = data[0];
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::GetObjectFeatureColor(int* out_r, int* out_g, int* out_b)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_OBJECT_FEATURE_COLOR & 0xFF000000) >> 24;
	data[1] = (GET_OBJECT_FEATURE_COLOR & 0x00FF0000) >> 16;
	data[2] = (GET_OBJECT_FEATURE_COLOR & 0x0000FF00) >> 8;
	data[3] = (GET_OBJECT_FEATURE_COLOR & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	int color_r = 0;
	int color_g = 0;
	int color_b = 0;

	if (len >= 12)
	{
		//r
		color_r = ((int)data[0] << 24) & 0xFF000000;
		color_r |= ((int)data[1] << 16) & 0x00FF0000;
		color_r |= ((int)data[2] << 8) & 0x0000FF00;
		color_r |= ((int)data[3]) & 0x000000FF;

		//g
		color_g = ((int)data[4] << 24) & 0xFF000000;
		color_g |= ((int)data[5] << 16) & 0x00FF0000;
		color_g |= ((int)data[6] << 8) & 0x0000FF00;
		color_g |= ((int)data[7]) & 0x000000FF;

		//b
		color_b = ((int)data[8] << 24) & 0xFF000000;
		color_b |= ((int)data[9] << 16) & 0x00FF0000;
		color_b |= ((int)data[10] << 8) & 0x0000FF00;
		color_b |= ((int)data[11]) & 0x000000FF;

	}

	(*out_r) = color_r;
	(*out_g) = color_g;
	(*out_b) = color_b;

	delete (data);
	data = NULL;

    return ret;
}

int CEyedeaInterface::GetObjectFeatureWidth(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_OBJECT_FEATURE_WIDTH & 0xFF000000) >> 24;
	data[1] = (GET_OBJECT_FEATURE_WIDTH & 0x00FF0000) >> 16;
	data[2] = (GET_OBJECT_FEATURE_WIDTH & 0x0000FF00) >> 8;
	data[3] = (GET_OBJECT_FEATURE_WIDTH & 0x000000FF);

	unsigned int scale_factor = 1;
	int width = 0;
    width = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(width == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			width = m_cls_eth_client->Open(m_ip, m_port);
			if(width == 0){
				width = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return width;
				}
				continue;
			}
		}
	}
	if (width != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return width;
	}

	width = 0;

	if (len >= 4)
	{
		//w
		width = ((int)data[0] << 24) & 0xFF000000;
		width |= ((int)data[1] << 16) & 0x00FF0000;
		width |= ((int)data[2] << 8) & 0x0000FF00;
		width |= ((int)data[3]) & 0x000000FF;

	}

	delete (data);
	data = NULL;

	return width;
}

int CEyedeaInterface::SetObjectFeatureUse(int use)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_SET_ENV;

	int len = 8;
	unsigned char* data = new unsigned char[len];

	data[0] = (SET_OBJECT_USE_FEATURE & 0xFF000000) >> 24;
	data[1] = (SET_OBJECT_USE_FEATURE & 0x00FF0000) >> 16;
	data[2] = (SET_OBJECT_USE_FEATURE & 0x0000FF00) >> 8;
	data[3] = (SET_OBJECT_USE_FEATURE & 0x000000FF);

	data[4] = (use & 0xFF000000) >> 24;
	data[5] = (use & 0x00FF0000) >> 16;
	data[6] = (use & 0x0000FF00) >> 8;
	data[7] = (use & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::SetObjectFeatureColor(int r, int g, int b)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 16;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (SET_OBJECT_FEATURE_COLOR & 0xFF000000) >> 24;
	data[1] = (SET_OBJECT_FEATURE_COLOR & 0x00FF0000) >> 16;
	data[2] = (SET_OBJECT_FEATURE_COLOR & 0x0000FF00) >> 8;
	data[3] = (SET_OBJECT_FEATURE_COLOR & 0x000000FF);

	//x
	data[4] = (r & 0xFF000000) >> 24;
	data[5] = (r & 0x00FF0000) >> 16;
	data[6] = (r & 0x0000FF00) >> 8;
	data[7] = (r & 0x000000FF);

	//y
	data[8] = (g & 0xFF000000) >> 24;
	data[9] = (g & 0x00FF0000) >> 16;
	data[10] = (g & 0x0000FF00) >> 8;
	data[11] = (g & 0x000000FF);

	//w
	data[12] = (b & 0xFF000000) >> 24;
	data[13] = (b & 0x00FF0000) >> 16;
	data[14] = (b & 0x0000FF00) >> 8;
	data[15] = (b & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::SetObjectFeatureWidth(int width)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 8;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (SET_OBJECT_FEATURE_WIDTH & 0xFF000000) >> 24;
	data[1] = (SET_OBJECT_FEATURE_WIDTH & 0x00FF0000) >> 16;
	data[2] = (SET_OBJECT_FEATURE_WIDTH & 0x0000FF00) >> 8;
	data[3] = (SET_OBJECT_FEATURE_WIDTH & 0x000000FF);

	//width
	data[4] = (width & 0xFF000000) >> 24;
	data[5] = (width & 0x00FF0000) >> 16;
	data[6] = (width & 0x0000FF00) >> 8;
	data[7] = (width & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	delete (data);
	data = NULL;

    return ret;
}

int CEyedeaInterface::GetObjectOutlineUse(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_SET_ENV;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	data[0] = (GET_OBJECT_USE_OUTLINE & 0xFF000000) >> 24;
	data[1] = (GET_OBJECT_USE_OUTLINE & 0x00FF0000) >> 16;
	data[2] = (GET_OBJECT_USE_OUTLINE & 0x0000FF00) >> 8;
	data[3] = (GET_OBJECT_USE_OUTLINE & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0;
	if (len >= 1)
	{
		ret = data[0];
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::GetObjectOutlineColor(int* out_r, int* out_g, int* out_b)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_OBJECT_OUTLINE_COLOR & 0xFF000000) >> 24;
	data[1] = (GET_OBJECT_OUTLINE_COLOR & 0x00FF0000) >> 16;
	data[2] = (GET_OBJECT_OUTLINE_COLOR & 0x0000FF00) >> 8;
	data[3] = (GET_OBJECT_OUTLINE_COLOR & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	int color_r = 0;
	int color_g = 0;
	int color_b = 0;

	if (len >= 12)
	{
		//r
		color_r = ((int)data[0] << 24) & 0xFF000000;
		color_r |= ((int)data[1] << 16) & 0x00FF0000;
		color_r |= ((int)data[2] << 8) & 0x0000FF00;
		color_r |= ((int)data[3]) & 0x000000FF;

		//g
		color_g = ((int)data[4] << 24) & 0xFF000000;
		color_g |= ((int)data[5] << 16) & 0x00FF0000;
		color_g |= ((int)data[6] << 8) & 0x0000FF00;
		color_g |= ((int)data[7]) & 0x000000FF;

		//b
		color_b = ((int)data[8] << 24) & 0xFF000000;
		color_b |= ((int)data[9] << 16) & 0x00FF0000;
		color_b |= ((int)data[10] << 8) & 0x0000FF00;
		color_b |= ((int)data[11]) & 0x000000FF;

	}

	(*out_r) = color_r;
	(*out_g) = color_g;
	(*out_b) = color_b;

	delete (data);
	data = NULL;

    return ret;
}

int CEyedeaInterface::GetObjectOutlineWidth(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_OBJECT_OUTLINE_WIDTH & 0xFF000000) >> 24;
	data[1] = (GET_OBJECT_OUTLINE_WIDTH & 0x00FF0000) >> 16;
	data[2] = (GET_OBJECT_OUTLINE_WIDTH & 0x0000FF00) >> 8;
	data[3] = (GET_OBJECT_OUTLINE_WIDTH & 0x000000FF);

	unsigned int scale_factor = 1;
	int width = 0;
    width = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(width == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			width = m_cls_eth_client->Open(m_ip, m_port);
			if(width == 0){
				width = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return width;
				}
				continue;
			}
		}
	}
	if (width != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return width;
	}

	width = 0;

	if (len >= 4)
	{
		//w
		width = ((int)data[0] << 24) & 0xFF000000;
		width |= ((int)data[1] << 16) & 0x00FF0000;
		width |= ((int)data[2] << 8) & 0x0000FF00;
		width |= ((int)data[3]) & 0x000000FF;

	}

	delete (data);
	data = NULL;

	return width;
}

int CEyedeaInterface::SetObjectOutlineUse(int use)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_SET_ENV;

	int len = 8;
	unsigned char* data = new unsigned char[len];

	data[0] = (SET_OBJECT_USE_OUTLINE & 0xFF000000) >> 24;
	data[1] = (SET_OBJECT_USE_OUTLINE & 0x00FF0000) >> 16;
	data[2] = (SET_OBJECT_USE_OUTLINE & 0x0000FF00) >> 8;
	data[3] = (SET_OBJECT_USE_OUTLINE & 0x000000FF);

	data[4] = (use & 0xFF000000) >> 24;
	data[5] = (use & 0x00FF0000) >> 16;
	data[6] = (use & 0x0000FF00) >> 8;
	data[7] = (use & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::SetObjectOutlineColor(int r, int g, int b)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 16;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (SET_OBJECT_OUTLINE_COLOR & 0xFF000000) >> 24;
	data[1] = (SET_OBJECT_OUTLINE_COLOR & 0x00FF0000) >> 16;
	data[2] = (SET_OBJECT_OUTLINE_COLOR & 0x0000FF00) >> 8;
	data[3] = (SET_OBJECT_OUTLINE_COLOR & 0x000000FF);

	//x
	data[4] = (r & 0xFF000000) >> 24;
	data[5] = (r & 0x00FF0000) >> 16;
	data[6] = (r & 0x0000FF00) >> 8;
	data[7] = (r & 0x000000FF);

	//y
	data[8] = (g & 0xFF000000) >> 24;
	data[9] = (g & 0x00FF0000) >> 16;
	data[10] = (g & 0x0000FF00) >> 8;
	data[11] = (g & 0x000000FF);

	//w
	data[12] = (b & 0xFF000000) >> 24;
	data[13] = (b & 0x00FF0000) >> 16;
	data[14] = (b & 0x0000FF00) >> 8;
	data[15] = (b & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::SetObjectOutlineWidth(int width)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 8;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (SET_OBJECT_OUTLINE_WIDTH & 0xFF000000) >> 24;
	data[1] = (SET_OBJECT_OUTLINE_WIDTH & 0x00FF0000) >> 16;
	data[2] = (SET_OBJECT_OUTLINE_WIDTH & 0x0000FF00) >> 8;
	data[3] = (SET_OBJECT_OUTLINE_WIDTH & 0x000000FF);

	//width
	data[4] = (width & 0xFF000000) >> 24;
	data[5] = (width & 0x00FF0000) >> 16;
	data[6] = (width & 0x0000FF00) >> 8;
	data[7] = (width & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

//

int CEyedeaInterface::GetObjectRectUse(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_SET_ENV;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	data[0] = (GET_OBJECT_USE_RECT & 0xFF000000) >> 24;
	data[1] = (GET_OBJECT_USE_RECT & 0x00FF0000) >> 16;
	data[2] = (GET_OBJECT_USE_RECT & 0x0000FF00) >> 8;
	data[3] = (GET_OBJECT_USE_RECT & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	ret = 0;
	if (len >= 1)
	{
		ret = data[0];
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::GetObjectRectColor(int* out_r, int* out_g, int* out_b)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_OBJECT_RECT_COLOR & 0xFF000000) >> 24;
	data[1] = (GET_OBJECT_RECT_COLOR & 0x00FF0000) >> 16;
	data[2] = (GET_OBJECT_RECT_COLOR & 0x0000FF00) >> 8;
	data[3] = (GET_OBJECT_RECT_COLOR & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	int color_r = 0;
	int color_g = 0;
	int color_b = 0;

	if (len >= 12)
	{
		//r
		color_r = ((int)data[0] << 24) & 0xFF000000;
		color_r |= ((int)data[1] << 16) & 0x00FF0000;
		color_r |= ((int)data[2] << 8) & 0x0000FF00;
		color_r |= ((int)data[3]) & 0x000000FF;

		//g
		color_g = ((int)data[4] << 24) & 0xFF000000;
		color_g |= ((int)data[5] << 16) & 0x00FF0000;
		color_g |= ((int)data[6] << 8) & 0x0000FF00;
		color_g |= ((int)data[7]) & 0x000000FF;

		//b
		color_b = ((int)data[8] << 24) & 0xFF000000;
		color_b |= ((int)data[9] << 16) & 0x00FF0000;
		color_b |= ((int)data[10] << 8) & 0x0000FF00;
		color_b |= ((int)data[11]) & 0x000000FF;

	}

	(*out_r) = color_r;
	(*out_g) = color_g;
	(*out_b) = color_b;

	delete (data);
	data = NULL;

    return ret;
}

int CEyedeaInterface::GetObjectRectWidth(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_OBJECT_RECT_WIDTH & 0xFF000000) >> 24;
	data[1] = (GET_OBJECT_RECT_WIDTH & 0x00FF0000) >> 16;
	data[2] = (GET_OBJECT_RECT_WIDTH & 0x0000FF00) >> 8;
	data[3] = (GET_OBJECT_RECT_WIDTH & 0x000000FF);

	unsigned int scale_factor = 1;
	int width = 0;
    width = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(width == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			width = m_cls_eth_client->Open(m_ip, m_port);
			if(width == 0){
				width = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return width;
				}
				continue;
			}
		}
	}
	if (width != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return width;
	}

	width = 0;

	if (len >= 4)
	{
		//w
		width = ((int)data[0] << 24) & 0xFF000000;
		width |= ((int)data[1] << 16) & 0x00FF0000;
		width |= ((int)data[2] << 8) & 0x0000FF00;
		width |= ((int)data[3]) & 0x000000FF;

	}

	delete (data);
	data = NULL;

	return width;
}

int CEyedeaInterface::SetObjectRectUse(int use)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_SET_ENV;

	int len = 8;
	unsigned char* data = new unsigned char[len];

	data[0] = (SET_OBJECT_USE_RECT & 0xFF000000) >> 24;
	data[1] = (SET_OBJECT_USE_RECT & 0x00FF0000) >> 16;
	data[2] = (SET_OBJECT_USE_RECT & 0x0000FF00) >> 8;
	data[3] = (SET_OBJECT_USE_RECT & 0x000000FF);

	data[4] = (use & 0xFF000000) >> 24;
	data[5] = (use & 0x00FF0000) >> 16;
	data[6] = (use & 0x0000FF00) >> 8;
	data[7] = (use & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::SetObjectRectColor(int r, int g, int b)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 16;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (SET_OBJECT_RECT_COLOR & 0xFF000000) >> 24;
	data[1] = (SET_OBJECT_RECT_COLOR & 0x00FF0000) >> 16;
	data[2] = (SET_OBJECT_RECT_COLOR & 0x0000FF00) >> 8;
	data[3] = (SET_OBJECT_RECT_COLOR & 0x000000FF);

	//x
	data[4] = (r & 0xFF000000) >> 24;
	data[5] = (r & 0x00FF0000) >> 16;
	data[6] = (r & 0x0000FF00) >> 8;
	data[7] = (r & 0x000000FF);

	//y
	data[8] = (g & 0xFF000000) >> 24;
	data[9] = (g & 0x00FF0000) >> 16;
	data[10] = (g & 0x0000FF00) >> 8;
	data[11] = (g & 0x000000FF);

	//w
	data[12] = (b & 0xFF000000) >> 24;
	data[13] = (b & 0x00FF0000) >> 16;
	data[14] = (b & 0x0000FF00) >> 8;
	data[15] = (b & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}
    return ret;
}

int CEyedeaInterface::SetObjectRectWidth(int width)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 8;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (SET_OBJECT_RECT_WIDTH & 0xFF000000) >> 24;
	data[1] = (SET_OBJECT_RECT_WIDTH & 0x00FF0000) >> 16;
	data[2] = (SET_OBJECT_RECT_WIDTH & 0x0000FF00) >> 8;
	data[3] = (SET_OBJECT_RECT_WIDTH & 0x000000FF);

	//width
	data[4] = (width & 0xFF000000) >> 24;
	data[5] = (width & 0x00FF0000) >> 16;
	data[6] = (width & 0x0000FF00) >> 8;
	data[7] = (width & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

//

int CEyedeaInterface::GetObjectCenterUse(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_SET_ENV;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	data[0] = (GET_OBJECT_USE_CENTER & 0xFF000000) >> 24;
	data[1] = (GET_OBJECT_USE_CENTER & 0x00FF0000) >> 16;
	data[2] = (GET_OBJECT_USE_CENTER & 0x0000FF00) >> 8;
	data[3] = (GET_OBJECT_USE_CENTER & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	ret = 0;

	if (len >= 1)
	{
		ret = data[0];
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::GetObjectCenterColor(int* out_r, int* out_g, int* out_b)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_OBJECT_CENTER_COLOR & 0xFF000000) >> 24;
	data[1] = (GET_OBJECT_CENTER_COLOR & 0x00FF0000) >> 16;
	data[2] = (GET_OBJECT_CENTER_COLOR & 0x0000FF00) >> 8;
	data[3] = (GET_OBJECT_CENTER_COLOR & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	int color_r = 0;
	int color_g = 0;
	int color_b = 0;

	if (len >= 12)
	{
		//r
		color_r = ((int)data[0] << 24) & 0xFF000000;
		color_r |= ((int)data[1] << 16) & 0x00FF0000;
		color_r |= ((int)data[2] << 8) & 0x0000FF00;
		color_r |= ((int)data[3]) & 0x000000FF;

		//g
		color_g = ((int)data[4] << 24) & 0xFF000000;
		color_g |= ((int)data[5] << 16) & 0x00FF0000;
		color_g |= ((int)data[6] << 8) & 0x0000FF00;
		color_g |= ((int)data[7]) & 0x000000FF;

		//b
		color_b = ((int)data[8] << 24) & 0xFF000000;
		color_b |= ((int)data[9] << 16) & 0x00FF0000;
		color_b |= ((int)data[10] << 8) & 0x0000FF00;
		color_b |= ((int)data[11]) & 0x000000FF;

	}

	(*out_r) = color_r;
	(*out_g) = color_g;
	(*out_b) = color_b;

	delete (data);
	data = NULL;

    return ret;
}

int CEyedeaInterface::GetObjectCenterWidth(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_OBJECT_CENTER_WIDTH & 0xFF000000) >> 24;
	data[1] = (GET_OBJECT_CENTER_WIDTH & 0x00FF0000) >> 16;
	data[2] = (GET_OBJECT_CENTER_WIDTH & 0x0000FF00) >> 8;
	data[3] = (GET_OBJECT_CENTER_WIDTH & 0x000000FF);

	unsigned int scale_factor = 1;
	int width = 0;
    width = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(width == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			width = m_cls_eth_client->Open(m_ip, m_port);
			if(width == 0){
				width = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return width;
				}
				continue;
			}
		}
	}
	if (width != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return width;
	}

	width = 0;

	if (len >= 4)
	{
		//w
		width = ((int)data[0] << 24) & 0xFF000000;
		width |= ((int)data[1] << 16) & 0x00FF0000;
		width |= ((int)data[2] << 8) & 0x0000FF00;
		width |= ((int)data[3]) & 0x000000FF;

	}

	delete (data);
	data = NULL;

	return width;
}

int CEyedeaInterface::SetObjectCenterUse(int use)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_SET_ENV;

	int len = 8;
	unsigned char* data = new unsigned char[len];

	data[0] = (SET_OBJECT_USE_CENTER & 0xFF000000) >> 24;
	data[1] = (SET_OBJECT_USE_CENTER & 0x00FF0000) >> 16;
	data[2] = (SET_OBJECT_USE_CENTER & 0x0000FF00) >> 8;
	data[3] = (SET_OBJECT_USE_CENTER & 0x000000FF);

	data[4] = (use & 0xFF000000) >> 24;
	data[5] = (use & 0x00FF0000) >> 16;
	data[6] = (use & 0x0000FF00) >> 8;
	data[7] = (use & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::SetObjectCenterColor(int r, int g, int b)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 16;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (SET_OBJECT_CENTER_COLOR & 0xFF000000) >> 24;
	data[1] = (SET_OBJECT_CENTER_COLOR & 0x00FF0000) >> 16;
	data[2] = (SET_OBJECT_CENTER_COLOR & 0x0000FF00) >> 8;
	data[3] = (SET_OBJECT_CENTER_COLOR & 0x000000FF);

	//x
	data[4] = (r & 0xFF000000) >> 24;
	data[5] = (r & 0x00FF0000) >> 16;
	data[6] = (r & 0x0000FF00) >> 8;
	data[7] = (r & 0x000000FF);

	//y
	data[8] = (g & 0xFF000000) >> 24;
	data[9] = (g & 0x00FF0000) >> 16;
	data[10] = (g & 0x0000FF00) >> 8;
	data[11] = (g & 0x000000FF);

	//w
	data[12] = (b & 0xFF000000) >> 24;
	data[13] = (b & 0x00FF0000) >> 16;
	data[14] = (b & 0x0000FF00) >> 8;
	data[15] = (b & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::SetObjectCenterWidth(int width)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 8;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (SET_OBJECT_CENTER_WIDTH & 0xFF000000) >> 24;
	data[1] = (SET_OBJECT_CENTER_WIDTH & 0x00FF0000) >> 16;
	data[2] = (SET_OBJECT_CENTER_WIDTH & 0x0000FF00) >> 8;
	data[3] = (SET_OBJECT_CENTER_WIDTH & 0x000000FF);

	//width
	data[4] = (width & 0xFF000000) >> 24;
	data[5] = (width & 0x00FF0000) >> 16;
	data[6] = (width & 0x0000FF00) >> 8;
	data[7] = (width & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

//

int CEyedeaInterface::GetObjectAngleUse(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_SET_ENV;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	data[0] = (GET_OBJECT_USE_ANGLE & 0xFF000000) >> 24;
	data[1] = (GET_OBJECT_USE_ANGLE & 0x00FF0000) >> 16;
	data[2] = (GET_OBJECT_USE_ANGLE & 0x0000FF00) >> 8;
	data[3] = (GET_OBJECT_USE_ANGLE & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	ret = 0;
	if (len >= 1)
	{
		ret = data[0];
	}

	delete data;
	data = NULL;

	return ret;
}

int CEyedeaInterface::GetObjectAngleColor(int* out_r, int* out_g, int* out_b)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_OBJECT_ANGLE_COLOR & 0xFF000000) >> 24;
	data[1] = (GET_OBJECT_ANGLE_COLOR & 0x00FF0000) >> 16;
	data[2] = (GET_OBJECT_ANGLE_COLOR & 0x0000FF00) >> 8;
	data[3] = (GET_OBJECT_ANGLE_COLOR & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	int color_r = 0;
	int color_g = 0;
	int color_b = 0;

	if (len >= 12)
	{
		//r
		color_r = ((int)data[0] << 24) & 0xFF000000;
		color_r |= ((int)data[1] << 16) & 0x00FF0000;
		color_r |= ((int)data[2] << 8) & 0x0000FF00;
		color_r |= ((int)data[3]) & 0x000000FF;

		//g
		color_g = ((int)data[4] << 24) & 0xFF000000;
		color_g |= ((int)data[5] << 16) & 0x00FF0000;
		color_g |= ((int)data[6] << 8) & 0x0000FF00;
		color_g |= ((int)data[7]) & 0x000000FF;

		//b
		color_b = ((int)data[8] << 24) & 0xFF000000;
		color_b |= ((int)data[9] << 16) & 0x00FF0000;
		color_b |= ((int)data[10] << 8) & 0x0000FF00;
		color_b |= ((int)data[11]) & 0x000000FF;

	}

	(*out_r) = color_r;
	(*out_g) = color_g;
	(*out_b) = color_b;

	delete (data);
	data = NULL;

    return ret;
}

int CEyedeaInterface::GetObjectAngleWidth(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 4;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (GET_OBJECT_ANGLE_WIDTH & 0xFF000000) >> 24;
	data[1] = (GET_OBJECT_ANGLE_WIDTH & 0x00FF0000) >> 16;
	data[2] = (GET_OBJECT_ANGLE_WIDTH & 0x0000FF00) >> 8;
	data[3] = (GET_OBJECT_ANGLE_WIDTH & 0x000000FF);

	unsigned int scale_factor = 1;
	int width = 0;
    width = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(width == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			width = m_cls_eth_client->Open(m_ip, m_port);
			if(width == 0){
				width = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return width;
				}
				continue;
			}
		}
	}
	if (width != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return width;
	}

	width = 0;

	if (len >= 4)
	{
		//w
		width = ((int)data[0] << 24) & 0xFF000000;
		width |= ((int)data[1] << 16) & 0x00FF0000;
		width |= ((int)data[2] << 8) & 0x0000FF00;
		width |= ((int)data[3]) & 0x000000FF;

	}

	delete (data);
	data = NULL;

	return width;
}

int CEyedeaInterface::SetObjectAngleUse(int use)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//COMMAND_SET_OBJECT_POSITION
	char command = COMMAND_SET_ENV;

	int len = 8;
	unsigned char* data = new unsigned char[len];

	data[0] = (SET_OBJECT_USE_ANGLE & 0xFF000000) >> 24;
	data[1] = (SET_OBJECT_USE_ANGLE & 0x00FF0000) >> 16;
	data[2] = (SET_OBJECT_USE_ANGLE & 0x0000FF00) >> 8;
	data[3] = (SET_OBJECT_USE_ANGLE & 0x000000FF);

	data[4] = (use & 0xFF000000) >> 24;
	data[5] = (use & 0x00FF0000) >> 16;
	data[6] = (use & 0x0000FF00) >> 8;
	data[7] = (use & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::SetObjectAngleColor(int r, int g, int b)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 16;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (SET_OBJECT_ANGLE_COLOR & 0xFF000000) >> 24;
	data[1] = (SET_OBJECT_ANGLE_COLOR & 0x00FF0000) >> 16;
	data[2] = (SET_OBJECT_ANGLE_COLOR & 0x0000FF00) >> 8;
	data[3] = (SET_OBJECT_ANGLE_COLOR & 0x000000FF);

	//x
	data[4] = (r & 0xFF000000) >> 24;
	data[5] = (r & 0x00FF0000) >> 16;
	data[6] = (r & 0x0000FF00) >> 8;
	data[7] = (r & 0x000000FF);

	//y
	data[8] = (g & 0xFF000000) >> 24;
	data[9] = (g & 0x00FF0000) >> 16;
	data[10] = (g & 0x0000FF00) >> 8;
	data[11] = (g & 0x000000FF);

	//w
	data[12] = (b & 0xFF000000) >> 24;
	data[13] = (b & 0x00FF0000) >> 16;
	data[14] = (b & 0x0000FF00) >> 8;
	data[15] = (b & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
    
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::SetObjectAngleWidth(int width)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_SET_ENV;
	int len = 8;
	unsigned char* data = new unsigned char[len];

	//option
	data[0] = (SET_OBJECT_ANGLE_WIDTH & 0xFF000000) >> 24;
	data[1] = (SET_OBJECT_ANGLE_WIDTH & 0x00FF0000) >> 16;
	data[2] = (SET_OBJECT_ANGLE_WIDTH & 0x0000FF00) >> 8;
	data[3] = (SET_OBJECT_ANGLE_WIDTH & 0x000000FF);

	//width
	data[4] = (width & 0xFF000000) >> 24;
	data[5] = (width & 0x00FF0000) >> 16;
	data[6] = (width & 0x0000FF00) >> 8;
	data[7] = (width & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	delete (data);
	data = NULL;

    return ret;
}

int CEyedeaInterface::Calibration_GetID(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_CALIBRATION_GET_ID;
	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while (1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if (ret == 0) {
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	ret = 0;

	if (len >= 4)
	{
		//w
		ret = ((int)data[0] << 24) & 0xFF000000;
		ret |= ((int)data[1] << 16) & 0x00FF0000;
		ret |= ((int)data[2] << 8) & 0x0000FF00;
		ret |= ((int)data[3]) & 0x000000FF;

	}

	delete (data);
	data = NULL;

	return ret;
}

int CEyedeaInterface::Calibration_isOK(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_CALIBRATION_IS_OK;
	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	ret =0;

	if (len >= 4)
	{
		//w
		ret = ((int)data[0] << 24) & 0xFF000000;
		ret |= ((int)data[1] << 16) & 0x00FF0000;
		ret |= ((int)data[2] << 8) & 0x0000FF00;
		ret |= ((int)data[3]) & 0x000000FF;

	}

	delete (data);
	data = NULL;

	return ret;
}

int CEyedeaInterface::Calibration_Add(float robot_x, float robot_y)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_CALIBRATION_ADD;
	int len = 8;
	unsigned char* data = new unsigned char[len];

	int i_robot_x = robot_x * 10000.0 ;
	int i_robot_y = robot_y * 10000.0 ;

	//robot_x
	data[0] = (i_robot_x & 0xFF000000) >> 24;
	data[1] = (i_robot_x & 0x00FF0000) >> 16;
	data[2] = (i_robot_x & 0x0000FF00) >> 8;
	data[3] = (i_robot_x & 0x000000FF);

	//robot_y
	data[4] = (i_robot_y & 0xFF000000) >> 24;
	data[5] = (i_robot_y & 0x00FF0000) >> 16;
	data[6] = (i_robot_y & 0x0000FF00) >> 8;
	data[7] = (i_robot_y & 0x000000FF);

	unsigned int scale_factor = 10000;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}

	if (data != NULL)
	{
		delete (data);
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::Calibration_GetCount(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_CALIBRATION_GET_COUNT;
	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int size = 0;
    size = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(size == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			size = m_cls_eth_client->Open(m_ip, m_port);
			if(size == 0){
				size = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return size;
				}
				continue;
			}
		}
	}
	if (size != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return size;
	}

	size = 0;

	if (len >= 4)
	{
		//w
		size = ((int)data[0] << 24) & 0xFF000000;
		size |= ((int)data[1] << 16) & 0x00FF0000;
		size |= ((int)data[2] << 8) & 0x0000FF00;
		size |= ((int)data[3]) & 0x000000FF;

	}

	delete (data);
	data = NULL;

	return size;
}

int CEyedeaInterface::Calibration_GetImage(int index, char** out_data, int* len)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_CALIBRATION_GET_IMAGE;

	//option
	(*out_data)[0] = (index & 0xFF000000) >> 24;
	(*out_data)[1] = (index & 0x00FF0000) >> 16;
	(*out_data)[2] = (index & 0x0000FF00) >> 8;
	(*out_data)[3] = (index & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)out_data, len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if(sec >= 60)
					return ret;
				continue;
			}
		}
	}
    return ret;
}

int CEyedeaInterface::Calibration_GetRobotInfo(int index, float *out_robot_x, float *out_robot_y)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_CALIBRATION_GET_INFO;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//index
	data[0] = (index & 0xFF000000) >> 24;
	data[1] = (index & 0x00FF0000) >> 16;
	data[2] = (index & 0x0000FF00) >> 8;
	data[3] = (index & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	int i_robot_x = 0;
	int i_robot_y = 0;

	if (len >= 8)
	{
		//i_robot_x
		i_robot_x = ((int)data[0] << 24) & 0xFF000000;
		i_robot_x |= ((int)data[1] << 16) & 0x00FF0000;
		i_robot_x |= ((int)data[2] << 8) & 0x0000FF00;
		i_robot_x |= ((int)data[3]) & 0x000000FF;

		//i_robot_y
		i_robot_y = ((int)data[4] << 24) & 0xFF000000;
		i_robot_y |= ((int)data[5] << 16) & 0x00FF0000;
		i_robot_y |= ((int)data[6] << 8) & 0x0000FF00;
		i_robot_y |= ((int)data[7]) & 0x000000FF;
	}

	(*out_robot_x) = (float)i_robot_x / (float)scale_factor;
	(*out_robot_y) = (float)i_robot_y / (float)scale_factor;

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::Calibration_Del(int index)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_CALIBRATION_DEL;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//index
	data[0] = (index & 0xFF000000) >> 24;
	data[1] = (index & 0x00FF0000) >> 16;
	data[2] = (index & 0x0000FF00) >> 8;
	data[3] = (index & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::Calibration_Clear(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_CALIBRATION_CLEAR;

	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::Calibration_Run(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_CALIBRATION_RUN;

	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::Calibration_GetPoint(const float in_px, const float in_py, float* out_rx, float* out_ry)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_CALIBRATION_GEPOINT;

	int len = 8;
	unsigned char* data = new unsigned char[8];

	int _x = in_px * 1000;
	int _y = in_py * 1000;

	//x
	data[0] = (_x & 0xFF000000) >> 24;
	data[1] = (_x & 0x00FF0000) >> 16;
	data[2] = (_x & 0x0000FF00) >> 8;
	data[3] = (_x & 0x000000FF);

	//y
	data[4] = (_y & 0xFF000000) >> 24;
	data[5] = (_y & 0x00FF0000) >> 16;
	data[6] = (_y & 0x0000FF00) >> 8;
	data[7] = (_y & 0x000000FF);

	unsigned int scale_factor = 1000;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	int i_robot_x = 0;
	int i_robot_y = 0;

	if (len >= 8)
	{
		//i_robot_x
		i_robot_x = ((int)data[0] << 24) & 0xFF000000;
		i_robot_x |= ((int)data[1] << 16) & 0x00FF0000;
		i_robot_x |= ((int)data[2] << 8) & 0x0000FF00;
		i_robot_x |= ((int)data[3]) & 0x000000FF;

		//i_robot_y
		i_robot_y = ((int)data[4] << 24) & 0xFF000000;
		i_robot_y |= ((int)data[5] << 16) & 0x00FF0000;
		i_robot_y |= ((int)data[6] << 8) & 0x0000FF00;
		i_robot_y |= ((int)data[7]) & 0x000000FF;
	}

	(*out_rx) = (float)i_robot_x / (float)scale_factor;
	(*out_ry) = (float)i_robot_y / (float)scale_factor;

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::Calibration_GetChessPoint(const int index, float* out_rx, float* out_ry)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//printf("SetSearchArea - %d %d %d %d\n", x, y, w, h);

	char command = COMMAND_CALIBRATION_GETCHESSPOINT;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//index
	data[0] = (index & 0xFF000000) >> 24;
	data[1] = (index & 0x00FF0000) >> 16;
	data[2] = (index & 0x0000FF00) >> 8;
	data[3] = (index & 0x000000FF);

	unsigned int scale_factor = 1000;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while (1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if (ret == 0) {
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	int i_robot_x = 0;
	int i_robot_y = 0;

	if (len >= 8)
	{
		//i_robot_x
		i_robot_x = ((int)data[0] << 24) & 0xFF000000;
		i_robot_x |= ((int)data[1] << 16) & 0x00FF0000;
		i_robot_x |= ((int)data[2] << 8) & 0x0000FF00;
		i_robot_x |= ((int)data[3]) & 0x000000FF;

		//i_robot_y
		i_robot_y = ((int)data[4] << 24) & 0xFF000000;
		i_robot_y |= ((int)data[5] << 16) & 0x00FF0000;
		i_robot_y |= ((int)data[6] << 8) & 0x0000FF00;
		i_robot_y |= ((int)data[7]) & 0x000000FF;
	}

	(*out_rx) = (float)i_robot_x / (float)scale_factor;
	(*out_ry) = (float)i_robot_y / (float)scale_factor;

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::GetFindObjectCount(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_FIND_OBJECT_COUNT;

	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int count = 0;
    count = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(count == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			count = m_cls_eth_client->Open(m_ip, m_port);
			if(count == 0){
				count = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return count;
				}
				continue;
			}
		}
	}
	if (count != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return count;
	}

	count = 0;

	if (len >= 4)
	{
		//count
		count = ((int)data[0] << 24) & 0xFF000000;
		count |= ((int)data[1] << 16) & 0x00FF0000;
		count |= ((int)data[2] << 8) & 0x0000FF00;
		count |= ((int)data[3]) & 0x000000FF;
	}

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return count;
}

int CEyedeaInterface::GetFindObjectResultInfo(int base_index, int sub_index, float* out_id, float* out_cx, float* out_cy, float* out_rx, float* out_ry, float* out_angle, float* out_type, float* out_score, float** out_histogram, float** out_histogram_b, float** out_histogram_g, float** out_histogram_r, float* out_histogram_size)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_FIND_OBJECT_INFO_RESULT;

	int len = 8;
	unsigned char* data = new unsigned char[len];

	//index
	int data_index = 0;
	data[data_index++] = (base_index & 0xFF000000) >> 24;
	data[data_index++] = (base_index & 0x00FF0000) >> 16;
	data[data_index++] = (base_index & 0x0000FF00) >> 8;
	data[data_index++] = (base_index & 0x000000FF);

	//size
	data[data_index++] = (sub_index & 0xFF000000) >> 24;
	data[data_index++] = (sub_index & 0x00FF0000) >> 16;
	data[data_index++] = (sub_index & 0x0000FF00) >> 8;
	data[data_index++] = (sub_index & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while (1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if (ret == 0) {
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{

		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	int i_id = 0;
	int i_camera_x = 0;
	int i_camera_y = 0;
	int i_robot_x = 0;
	int i_robot_y = 0;
	int i_angle = 0;
	int i_type = 0;
	int i_score = 0;
	int i_histogram_size = 0;
	int i_histogram_data = 0;

	int index = 0;

	if (len >= 4)
	{
		//i_id
		i_id = ((int)data[index++] << 24) & 0xFF000000;
		i_id |= ((int)data[index++] << 16) & 0x00FF0000;
		i_id |= ((int)data[index++] << 8) & 0x0000FF00;
		i_id |= ((int)data[index++]) & 0x000000FF;

		//i_camera_x
		i_camera_x = ((int)data[index++] << 24) & 0xFF000000;
		i_camera_x |= ((int)data[index++] << 16) & 0x00FF0000;
		i_camera_x |= ((int)data[index++] << 8) & 0x0000FF00;
		i_camera_x |= ((int)data[index++]) & 0x000000FF;

		//i_camera_y
		i_camera_y = ((int)data[index++] << 24) & 0xFF000000;
		i_camera_y |= ((int)data[index++] << 16) & 0x00FF0000;
		i_camera_y |= ((int)data[index++] << 8) & 0x0000FF00;
		i_camera_y |= ((int)data[index++]) & 0x000000FF;

		//i_robot_x
		i_robot_x = ((int)data[index++] << 24) & 0xFF000000;
		i_robot_x |= ((int)data[index++] << 16) & 0x00FF0000;
		i_robot_x |= ((int)data[index++] << 8) & 0x0000FF00;
		i_robot_x |= ((int)data[index++]) & 0x000000FF;

		//i_robot_y
		i_robot_y = ((int)data[index++] << 24) & 0xFF000000;
		i_robot_y |= ((int)data[index++] << 16) & 0x00FF0000;
		i_robot_y |= ((int)data[index++] << 8) & 0x0000FF00;
		i_robot_y |= ((int)data[index++]) & 0x000000FF;

		//i_angle
		i_angle = ((int)data[index++] << 24) & 0xFF000000;
		i_angle |= ((int)data[index++] << 16) & 0x00FF0000;
		i_angle |= ((int)data[index++] << 8) & 0x0000FF00;
		i_angle |= ((int)data[index++]) & 0x000000FF;

		//i_type
		i_type = ((int)data[index++] << 24) & 0xFF000000;
		i_type |= ((int)data[index++] << 16) & 0x00FF0000;
		i_type |= ((int)data[index++] << 8) & 0x0000FF00;
		i_type |= ((int)data[index++]) & 0x000000FF;

		//i_score
		i_score = ((int)data[index++] << 24) & 0xFF000000;
		i_score |= ((int)data[index++] << 16) & 0x00FF0000;
		i_score |= ((int)data[index++] << 8) & 0x0000FF00;
		i_score |= ((int)data[index++]) & 0x000000FF;

		//i_histogram_size
		i_histogram_size = ((int)data[index++] << 24) & 0xFF000000;
		i_histogram_size |= ((int)data[index++] << 16) & 0x00FF0000;
		i_histogram_size |= ((int)data[index++] << 8) & 0x0000FF00;
		i_histogram_size |= ((int)data[index++]) & 0x000000FF;

		(*out_id) = (float)i_id / (float)scale_factor;
		(*out_cx) = (float)i_camera_x / (float)scale_factor;
		(*out_cy) = (float)i_camera_y / (float)scale_factor;
		(*out_rx) = (float)i_robot_x / (float)scale_factor;
		(*out_ry) = (float)i_robot_y / (float)scale_factor;
		(*out_angle) = (float)i_angle / (float)scale_factor;
		(*out_type) = (float)i_type / (float)scale_factor;
		(*out_score) = (float)i_score / (float)scale_factor;
		(*out_histogram_size) = (float)i_histogram_size / (float)scale_factor;

		int histogram_size = (int)(*out_histogram_size);
		if (histogram_size > 0)
		{
			//gray
			if ((*out_histogram) != NULL)	free((*out_histogram));
			(*out_histogram) = (float *)malloc(sizeof(float)*histogram_size);

			for (int i = 0; i < histogram_size; i++)
			{
				//i_score
				i_histogram_data = ((int)data[index++] << 24) & 0xFF000000;
				i_histogram_data |= ((int)data[index++] << 16) & 0x00FF0000;
				i_histogram_data |= ((int)data[index++] << 8) & 0x0000FF00;
				i_histogram_data |= ((int)data[index++]) & 0x000000FF;

				(*out_histogram)[i] = (float)i_histogram_data / (float)scale_factor;
			}

			//b
			if ((*out_histogram_b) != NULL)	free((*out_histogram_b));
			(*out_histogram_b) = (float *)malloc(sizeof(float)*histogram_size);

			for (int i = 0; i < histogram_size; i++)
			{
				//i_score
				i_histogram_data = ((int)data[index++] << 24) & 0xFF000000;
				i_histogram_data |= ((int)data[index++] << 16) & 0x00FF0000;
				i_histogram_data |= ((int)data[index++] << 8) & 0x0000FF00;
				i_histogram_data |= ((int)data[index++]) & 0x000000FF;

				(*out_histogram_b)[i] = (float)i_histogram_data / (float)scale_factor;
			}

			//g
			if ((*out_histogram_g) != NULL)	free((*out_histogram_g));
			(*out_histogram_g) = (float *)malloc(sizeof(float)*histogram_size);

			for (int i = 0; i < histogram_size; i++)
			{
				//i_score
				i_histogram_data = ((int)data[index++] << 24) & 0xFF000000;
				i_histogram_data |= ((int)data[index++] << 16) & 0x00FF0000;
				i_histogram_data |= ((int)data[index++] << 8) & 0x0000FF00;
				i_histogram_data |= ((int)data[index++]) & 0x000000FF;

				(*out_histogram_g)[i] = (float)i_histogram_data / (float)scale_factor;
			}

			//r
			if ((*out_histogram_r) != NULL)	free((*out_histogram_r));
			(*out_histogram_r) = (float *)malloc(sizeof(float)*histogram_size);

			for (int i = 0; i < histogram_size; i++)
			{
				//i_score
				i_histogram_data = ((int)data[index++] << 24) & 0xFF000000;
				i_histogram_data |= ((int)data[index++] << 16) & 0x00FF0000;
				i_histogram_data |= ((int)data[index++] << 8) & 0x0000FF00;
				i_histogram_data |= ((int)data[index++]) & 0x000000FF;

				(*out_histogram_r)[i] = (float)i_histogram_data / (float)scale_factor;
			}
		}
	}


	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return i_histogram_size;
}

int CEyedeaInterface::GetFindObjectInfo(int index, int max_objects_count, int option, float** out_id, float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry, float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry, float** out_circle_rx, float** out_circle_ry, float** out_line1_x, float** out_line1_y, float** out_line2_x, float** out_line2_y, float** out_angle, float** out_type, float** out_score, float** out_pass)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_FIND_OBJECT_INFO;

	int len = 4 + 4 + 4;
	unsigned char* data = new unsigned char[len];

	//index
	int data_index = 0;
	data[data_index++] = (index & 0xFF000000) >> 24;
	data[data_index++] = (index & 0x00FF0000) >> 16;
	data[data_index++] = (index & 0x0000FF00) >> 8;
	data[data_index++] = (index & 0x000000FF);

	//max_objects_count
	data[data_index++] = (max_objects_count & 0xFF000000) >> 24;
	data[data_index++] = (max_objects_count & 0x00FF0000) >> 16;
	data[data_index++] = (max_objects_count & 0x0000FF00) >> 8;
	data[data_index++] = (max_objects_count & 0x000000FF);

	//option
	data[data_index++] = (option & 0xFF000000) >> 24;
	data[data_index++] = (option & 0x00FF0000) >> 16;
	data[data_index++] = (option & 0x0000FF00) >> 8;
	data[data_index++] = (option & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}
		return ret;
	}

	int i_id = 0;
	int i_camera_x = 0;
	int i_camera_y = 0;
	int i_robot_x = 0;
	int i_robot_y = 0;
	int i_camera_bound_x = 0;
	int i_camera_bound_y = 0;
	int i_robot_bound_x = 0;
	int i_robot_bound_y = 0;
	int i_camera_mass_x = 0;
	int i_camera_mass_y = 0;
	int i_robot_mass_x = 0;
	int i_robot_mass_y = 0;
	int i_circle_rx = 0;
	int i_circle_ry = 0;
	int i_line1_x = 0;
	int i_line1_y = 0;
	int i_line2_x = 0;
	int i_line2_y = 0;
	int i_angle = 0;
	int i_type = 0;
	int i_score = 0;
	int i_pass = 0;

	int nObject = 0;
	//int index = 0;
	index = 0;

	if (len >= 4)
	{
		//nObject
		nObject = ((int)data[index++] << 24) & 0xFF000000;
		nObject |= ((int)data[index++] << 16) & 0x00FF0000;
		nObject |= ((int)data[index++] << 8) & 0x0000FF00;
		nObject |= ((int)data[index++]) & 0x000000FF;

		if (nObject > 0 && len >= 4 + ((23*4)* nObject))
		{
			if ((*out_id) != NULL)	free((*out_id));
			if ((*out_cx) != NULL)	free((*out_cx));
			if ((*out_cy) != NULL)	free((*out_cy));
			if ((*out_rx) != NULL)	free((*out_rx));
			if ((*out_ry) != NULL)	free((*out_ry));
			if ((*out_bound_cx) != NULL)	free((*out_bound_cx));
			if ((*out_bound_cy) != NULL)	free((*out_bound_cy));
			if ((*out_bound_rx) != NULL)	free((*out_bound_rx));
			if ((*out_bound_ry) != NULL)	free((*out_bound_ry));
			if ((*out_mass_cx) != NULL)	free((*out_mass_cx));
			if ((*out_mass_cy) != NULL)	free((*out_mass_cy));
			if ((*out_mass_rx) != NULL)	free((*out_mass_rx));
			if ((*out_mass_ry) != NULL)	free((*out_mass_ry));
			if ((*out_circle_rx) != NULL)	free((*out_circle_rx));
			if ((*out_circle_ry) != NULL)	free((*out_circle_ry));
			if ((*out_line1_x) != NULL)	free((*out_line1_x));
			if ((*out_line1_y) != NULL)	free((*out_line1_y));
			if ((*out_line2_x) != NULL)	free((*out_line2_x));
			if ((*out_line2_y) != NULL)	free((*out_line2_y));
			if ((*out_angle) != NULL)	free((*out_angle));
			if ((*out_type) != NULL)	free((*out_type));
			if ((*out_score) != NULL)	free((*out_score));
			if ((*out_pass) != NULL)	free((*out_pass));
			//if ((*out_index) != NULL)	free((*out_index));

			(*out_id) = (float *)malloc(sizeof(float)*nObject);
			(*out_cx) = (float *)malloc(sizeof(float)*nObject);
			(*out_cy) = (float *)malloc(sizeof(float)*nObject);
			(*out_rx) = (float *)malloc(sizeof(float)*nObject);
			(*out_ry) = (float *)malloc(sizeof(float)*nObject);
			(*out_bound_cx) = (float *)malloc(sizeof(float)*nObject);
			(*out_bound_cy) = (float *)malloc(sizeof(float)*nObject);
			(*out_bound_rx) = (float *)malloc(sizeof(float)*nObject);
			(*out_bound_ry) = (float *)malloc(sizeof(float)*nObject);
			(*out_mass_cx) = (float *)malloc(sizeof(float)*nObject);
			(*out_mass_cy) = (float *)malloc(sizeof(float)*nObject);
			(*out_mass_rx) = (float *)malloc(sizeof(float)*nObject);
			(*out_mass_ry) = (float *)malloc(sizeof(float)*nObject);
			(*out_circle_rx) = (float *)malloc(sizeof(float)*nObject);
			(*out_circle_ry) = (float *)malloc(sizeof(float)*nObject);
			(*out_line1_x) = (float *)malloc(sizeof(float)*nObject);
			(*out_line1_y) = (float *)malloc(sizeof(float)*nObject);
			(*out_line2_x) = (float *)malloc(sizeof(float)*nObject);
			(*out_line2_y) = (float *)malloc(sizeof(float)*nObject);
			(*out_angle) = (float *)malloc(sizeof(float)*nObject);
			(*out_type) = (float *)malloc(sizeof(float)*nObject);
			(*out_score) = (float *)malloc(sizeof(float)*nObject);
			(*out_pass) = (float *)malloc(sizeof(float)*nObject);
			//(*out_index) = (float *)malloc(sizeof(float)*nObject);

			for (int i = 0; i < nObject; i++)
			{
				//i_id
				i_id = ((int)data[index++] << 24) & 0xFF000000;
				i_id |= ((int)data[index++] << 16) & 0x00FF0000;
				i_id |= ((int)data[index++] << 8) & 0x0000FF00;
				i_id |= ((int)data[index++]) & 0x000000FF;

				//i_camera_x
				i_camera_x = ((int)data[index++] << 24) & 0xFF000000;
				i_camera_x |= ((int)data[index++] << 16) & 0x00FF0000;
				i_camera_x |= ((int)data[index++] << 8) & 0x0000FF00;
				i_camera_x |= ((int)data[index++]) & 0x000000FF;

				//i_camera_y
				i_camera_y = ((int)data[index++] << 24) & 0xFF000000;
				i_camera_y |= ((int)data[index++] << 16) & 0x00FF0000;
				i_camera_y |= ((int)data[index++] << 8) & 0x0000FF00;
				i_camera_y |= ((int)data[index++]) & 0x000000FF;

				//i_robot_x
				i_robot_x = ((int)data[index++] << 24) & 0xFF000000;
				i_robot_x |= ((int)data[index++] << 16) & 0x00FF0000;
				i_robot_x |= ((int)data[index++] << 8) & 0x0000FF00;
				i_robot_x |= ((int)data[index++]) & 0x000000FF;

				//i_robot_y
				i_robot_y = ((int)data[index++] << 24) & 0xFF000000;
				i_robot_y |= ((int)data[index++] << 16) & 0x00FF0000;
				i_robot_y |= ((int)data[index++] << 8) & 0x0000FF00;
				i_robot_y |= ((int)data[index++]) & 0x000000FF;

				//bound center
				//i_camera_x
				i_camera_bound_x = ((int)data[index++] << 24) & 0xFF000000;
				i_camera_bound_x |= ((int)data[index++] << 16) & 0x00FF0000;
				i_camera_bound_x |= ((int)data[index++] << 8) & 0x0000FF00;
				i_camera_bound_x |= ((int)data[index++]) & 0x000000FF;

				//i_camera_y
				i_camera_bound_y = ((int)data[index++] << 24) & 0xFF000000;
				i_camera_bound_y |= ((int)data[index++] << 16) & 0x00FF0000;
				i_camera_bound_y |= ((int)data[index++] << 8) & 0x0000FF00;
				i_camera_bound_y |= ((int)data[index++]) & 0x000000FF;

				//i_robot_x
				i_robot_bound_x = ((int)data[index++] << 24) & 0xFF000000;
				i_robot_bound_x |= ((int)data[index++] << 16) & 0x00FF0000;
				i_robot_bound_x |= ((int)data[index++] << 8) & 0x0000FF00;
				i_robot_bound_x |= ((int)data[index++]) & 0x000000FF;

				//i_robot_y
				i_robot_bound_y = ((int)data[index++] << 24) & 0xFF000000;
				i_robot_bound_y |= ((int)data[index++] << 16) & 0x00FF0000;
				i_robot_bound_y |= ((int)data[index++] << 8) & 0x0000FF00;
				i_robot_bound_y |= ((int)data[index++]) & 0x000000FF;

				//center of mass
				//i_camera_x
				i_camera_mass_x = ((int)data[index++] << 24) & 0xFF000000;
				i_camera_mass_x |= ((int)data[index++] << 16) & 0x00FF0000;
				i_camera_mass_x |= ((int)data[index++] << 8) & 0x0000FF00;
				i_camera_mass_x |= ((int)data[index++]) & 0x000000FF;

				//i_camera_y
				i_camera_mass_y = ((int)data[index++] << 24) & 0xFF000000;
				i_camera_mass_y |= ((int)data[index++] << 16) & 0x00FF0000;
				i_camera_mass_y |= ((int)data[index++] << 8) & 0x0000FF00;
				i_camera_mass_y |= ((int)data[index++]) & 0x000000FF;

				//i_robot_x
				i_robot_mass_x = ((int)data[index++] << 24) & 0xFF000000;
				i_robot_mass_x |= ((int)data[index++] << 16) & 0x00FF0000;
				i_robot_mass_x |= ((int)data[index++] << 8) & 0x0000FF00;
				i_robot_mass_x |= ((int)data[index++]) & 0x000000FF;

				//i_robot_y
				i_robot_mass_y = ((int)data[index++] << 24) & 0xFF000000;
				i_robot_mass_y |= ((int)data[index++] << 16) & 0x00FF0000;
				i_robot_mass_y |= ((int)data[index++] << 8) & 0x0000FF00;
				i_robot_mass_y |= ((int)data[index++]) & 0x000000FF;

				//i_circle_rx
				i_circle_rx = ((int)data[index++] << 24) & 0xFF000000;
				i_circle_rx |= ((int)data[index++] << 16) & 0x00FF0000;
				i_circle_rx |= ((int)data[index++] << 8) & 0x0000FF00;
				i_circle_rx |= ((int)data[index++]) & 0x000000FF;

				//i_circle_ry
				i_circle_ry = ((int)data[index++] << 24) & 0xFF000000;
				i_circle_ry |= ((int)data[index++] << 16) & 0x00FF0000;
				i_circle_ry |= ((int)data[index++] << 8) & 0x0000FF00;
				i_circle_ry |= ((int)data[index++]) & 0x000000FF;

				//i_line1_x
				i_line1_x = ((int)data[index++] << 24) & 0xFF000000;
				i_line1_x |= ((int)data[index++] << 16) & 0x00FF0000;
				i_line1_x |= ((int)data[index++] << 8) & 0x0000FF00;
				i_line1_x |= ((int)data[index++]) & 0x000000FF;

				//i_line1_y
				i_line1_y = ((int)data[index++] << 24) & 0xFF000000;
				i_line1_y |= ((int)data[index++] << 16) & 0x00FF0000;
				i_line1_y |= ((int)data[index++] << 8) & 0x0000FF00;
				i_line1_y |= ((int)data[index++]) & 0x000000FF;

				//i_line2_x
				i_line2_x = ((int)data[index++] << 24) & 0xFF000000;
				i_line2_x |= ((int)data[index++] << 16) & 0x00FF0000;
				i_line2_x |= ((int)data[index++] << 8) & 0x0000FF00;
				i_line2_x |= ((int)data[index++]) & 0x000000FF;

				//i_line2_y
				i_line2_y = ((int)data[index++] << 24) & 0xFF000000;
				i_line2_y |= ((int)data[index++] << 16) & 0x00FF0000;
				i_line2_y |= ((int)data[index++] << 8) & 0x0000FF00;
				i_line2_y |= ((int)data[index++]) & 0x000000FF;

				//i_angle
				i_angle = ((int)data[index++] << 24) & 0xFF000000;
				i_angle |= ((int)data[index++] << 16) & 0x00FF0000;
				i_angle |= ((int)data[index++] << 8) & 0x0000FF00;
				i_angle |= ((int)data[index++]) & 0x000000FF;

				//i_type
				i_type = ((int)data[index++] << 24) & 0xFF000000;
				i_type |= ((int)data[index++] << 16) & 0x00FF0000;
				i_type |= ((int)data[index++] << 8) & 0x0000FF00;
				i_type |= ((int)data[index++]) & 0x000000FF;

				//i_score
				i_score = ((int)data[index++] << 24) & 0xFF000000;
				i_score |= ((int)data[index++] << 16) & 0x00FF0000;
				i_score |= ((int)data[index++] << 8) & 0x0000FF00;
				i_score |= ((int)data[index++]) & 0x000000FF;

				//i_pass
				i_pass = ((int)data[index++] << 24) & 0xFF000000;
				i_pass |= ((int)data[index++] << 16) & 0x00FF0000;
				i_pass |= ((int)data[index++] << 8) & 0x0000FF00;
				i_pass |= ((int)data[index++]) & 0x000000FF;

				/*
				//i_index
				i_index = ((int)data[index++] << 24) & 0xFF000000;
				i_index |= ((int)data[index++] << 16) & 0x00FF0000;
				i_index |= ((int)data[index++] << 8) & 0x0000FF00;
				i_index |= ((int)data[index++]) & 0x000000FF;
				*/

				(*out_id)[i] = (float)i_id / (float)scale_factor;
				(*out_cx)[i] = (float)i_camera_x / (float)scale_factor;
				(*out_cy)[i] = (float)i_camera_y / (float)scale_factor;
				(*out_rx)[i] = (float)i_robot_x / (float)scale_factor;
				(*out_ry)[i] = (float)i_robot_y / (float)scale_factor;
				(*out_bound_cx)[i] = (float)i_camera_bound_x / (float)scale_factor;
				(*out_bound_cy)[i] = (float)i_camera_bound_y / (float)scale_factor;
				(*out_bound_rx)[i] = (float)i_robot_bound_x / (float)scale_factor;
				(*out_bound_ry)[i] = (float)i_robot_bound_y / (float)scale_factor;
				(*out_mass_cx)[i] = (float)i_camera_mass_x / (float)scale_factor;
				(*out_mass_cy)[i] = (float)i_camera_mass_y / (float)scale_factor;
				(*out_mass_rx)[i] = (float)i_robot_mass_x / (float)scale_factor;
				(*out_mass_ry)[i] = (float)i_robot_mass_y / (float)scale_factor;
				(*out_circle_rx)[i] = (float)i_circle_rx / (float)scale_factor;
				(*out_circle_ry)[i] = (float)i_circle_ry / (float)scale_factor;
				(*out_line1_x)[i] = (float)i_line1_x / (float)scale_factor;
				(*out_line1_y)[i] = (float)i_line1_y / (float)scale_factor;
				(*out_line2_x)[i] = (float)i_line2_x / (float)scale_factor;
				(*out_line2_y)[i] = (float)i_line2_y / (float)scale_factor;
				(*out_angle)[i] = (float)i_angle / (float)scale_factor;
				(*out_type)[i] = (float)i_type / (float)scale_factor;
				(*out_score)[i] = (float)i_score / (float)scale_factor;
				(*out_pass)[i] = (float)i_pass / (float)scale_factor;
				//(*out_index)[i] = (float)i_index / (float)scale_factor;
			}
		}
	}

	
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	ret = nObject;

    return ret;
}

int CEyedeaInterface::GetFindObjectInfo2(int index, float* out_cx, float* out_cy, float* out_rx, float* out_ry, float* out_angle, float* out_type, float* out_score)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_FIND_OBJECT_INFO2;

	printf("command = %d\n", command);

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//index
	data[0] = (index & 0xFF000000) >> 24;
	data[1] = (index & 0x00FF0000) >> 16;
	data[2] = (index & 0x0000FF00) >> 8;
	data[3] = (index & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	int i_camera_x = 0;
	int i_camera_y = 0;
	int i_robot_x = 0;
	int i_robot_y = 0;
	int i_angle = 0;
	int i_type = 0;
	int i_score = 0;

	if (len >= 28)
	{
		//i_camera_x
		i_camera_x = ((int)data[0] << 24) & 0xFF000000;
		i_camera_x |= ((int)data[1] << 16) & 0x00FF0000;
		i_camera_x |= ((int)data[2] << 8) & 0x0000FF00;
		i_camera_x |= ((int)data[3]) & 0x000000FF;

		//i_camera_y
		i_camera_y = ((int)data[4] << 24) & 0xFF000000;
		i_camera_y |= ((int)data[5] << 16) & 0x00FF0000;
		i_camera_y |= ((int)data[6] << 8) & 0x0000FF00;
		i_camera_y |= ((int)data[7]) & 0x000000FF;

		//i_robot_x
		i_robot_x = ((int)data[8] << 24) & 0xFF000000;
		i_robot_x |= ((int)data[9] << 16) & 0x00FF0000;
		i_robot_x |= ((int)data[10] << 8) & 0x0000FF00;
		i_robot_x |= ((int)data[11]) & 0x000000FF;

		//i_robot_y
		i_robot_y = ((int)data[12] << 24) & 0xFF000000;
		i_robot_y |= ((int)data[13] << 16) & 0x00FF0000;
		i_robot_y |= ((int)data[14] << 8) & 0x0000FF00;
		i_robot_y |= ((int)data[15]) & 0x000000FF;

		//i_angle
		i_angle = ((int)data[16] << 24) & 0xFF000000;
		i_angle |= ((int)data[17] << 16) & 0x00FF0000;
		i_angle |= ((int)data[18] << 8) & 0x0000FF00;
		i_angle |= ((int)data[19]) & 0x000000FF;

		//i_type
		i_type = ((int)data[20] << 24) & 0xFF000000;
		i_type |= ((int)data[21] << 16) & 0x00FF0000;
		i_type |= ((int)data[22] << 8) & 0x0000FF00;
		i_type |= ((int)data[23]) & 0x000000FF;

		//i_score
		i_score = ((int)data[24] << 24) & 0xFF000000;
		i_score |= ((int)data[25] << 16) & 0x00FF0000;
		i_score |= ((int)data[26] << 8) & 0x0000FF00;
		i_score |= ((int)data[27]) & 0x000000FF;
	}

	//printf(" - i_camera_x  = %d\n", i_camera_x);
	//printf(" - i_camera_y  = %d\n", i_camera_y);
	//printf(" - i_robot_x  = %d\n", i_robot_x);
	//printf(" - i_robot_y  = %d\n", i_robot_y);

	(*out_cx) = (float)i_camera_x / (float)scale_factor;
	(*out_cy) = (float)i_camera_y / (float)scale_factor;
	(*out_rx) = (float)i_robot_x / (float)scale_factor;
	(*out_ry) = (float)i_robot_y / (float)scale_factor;
	(*out_angle) = (float)i_angle / (float)scale_factor;
	(*out_type) = (float)i_type / (float)scale_factor;
	(*out_score) = (float)i_score / (float)scale_factor;

	//printf(" - (*out_cx)  = %f\n", (*out_cx));
	//printf(" - (*out_cy)  = %f\n", (*out_cy));
	//printf(" - (*out_rx)  = %f\n", (*out_rx));
	//printf(" - (*out_ry)  = %f\n", (*out_ry));

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::GetFindObjectPose(int index, float* out_cx, float* out_cy, float* out_rx, float* out_ry, float* out_angle)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GET_FIND_OBJECT_POSE;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//index
	data[0] = (index & 0xFF000000) >> 24;
	data[1] = (index & 0x00FF0000) >> 16;
	data[2] = (index & 0x0000FF00) >> 8;
	data[3] = (index & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	int i_camera_x = 0;
	int i_camera_y = 0;
	int i_robot_x = 0;
	int i_robot_y = 0;
	int i_angle = 0;

	if (len >= 20)
	{
		//i_camera_x
		i_camera_x = ((int)data[0] << 24) & 0xFF000000;
		i_camera_x |= ((int)data[1] << 16) & 0x00FF0000;
		i_camera_x |= ((int)data[2] << 8) & 0x0000FF00;
		i_camera_x |= ((int)data[3]) & 0x000000FF;

		//i_camera_y
		i_camera_y = ((int)data[4] << 24) & 0xFF000000;
		i_camera_y |= ((int)data[5] << 16) & 0x00FF0000;
		i_camera_y |= ((int)data[6] << 8) & 0x0000FF00;
		i_camera_y |= ((int)data[7]) & 0x000000FF;

		//i_robot_x
		i_robot_x = ((int)data[8] << 24) & 0xFF000000;
		i_robot_x |= ((int)data[9] << 16) & 0x00FF0000;
		i_robot_x |= ((int)data[10] << 8) & 0x0000FF00;
		i_robot_x |= ((int)data[11]) & 0x000000FF;

		//i_robot_y
		i_robot_y = ((int)data[12] << 24) & 0xFF000000;
		i_robot_y |= ((int)data[13] << 16) & 0x00FF0000;
		i_robot_y |= ((int)data[14] << 8) & 0x0000FF00;
		i_robot_y |= ((int)data[15]) & 0x000000FF;

		//i_angle
		i_angle = ((int)data[16] << 24) & 0xFF000000;
		i_angle |= ((int)data[17] << 16) & 0x00FF0000;
		i_angle |= ((int)data[18] << 8) & 0x0000FF00;
		i_angle |= ((int)data[19]) & 0x000000FF;
	}

	//printf(" - i_camera_x  = %d\n", i_camera_x);
	//printf(" - i_camera_y  = %d\n", i_camera_y);
	//printf(" - i_robot_x  = %d\n", i_robot_x);
	//printf(" - i_robot_y  = %d\n", i_robot_y);

	(*out_cx) = (float)i_camera_x / (float)scale_factor;
	(*out_cy) = (float)i_camera_y / (float)scale_factor;
	(*out_rx) = (float)i_robot_x / (float)scale_factor;
	(*out_ry) = (float)i_robot_y / (float)scale_factor;
	(*out_angle) = (float)i_angle / (float)scale_factor;

	//printf(" - (*out_cx)  = %f\n", (*out_cx));
	//printf(" - (*out_cy)  = %f\n", (*out_cy));
	//printf(" - (*out_rx)  = %f\n", (*out_rx));
	//printf(" - (*out_ry)  = %f\n", (*out_ry));

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::SetLog(int logoption)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_SET_LOG;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//index
	data[0] = (logoption & 0xFF000000) >> 24;
	data[1] = (logoption & 0x00FF0000) >> 16;
	data[2] = (logoption & 0x0000FF00) >> 8;
	data[3] = (logoption & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
    
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::VisionConfigFileSave(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_VISION_CONFIG_FILE_SAVE;

	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
   
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::VisionConfigFileLoad(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_VISION_CONFIG_FILE_LOAD;

	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
   
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

char* CEyedeaInterface::DB_Get_Mode(int id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return NULL;
	}

	char command = COMMAND_DB_GET_MODE;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//index
	data[0] = (id & 0xFF000000) >> 24;
	data[1] = (id & 0x00FF0000) >> 16;
	data[2] = (id & 0x0000FF00) >> 8;
	data[3] = (id & 0x000000FF);

	unsigned int scale_factor = 1;
	m_cls_eth_client->Send(command, &scale_factor, &data, &len);

	char* mode = NULL;

	if (len > 0)
	{
		mode = new char[len];
		memcpy(mode, data, len);
	}

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return mode;
}

char* CEyedeaInterface::GetVersion(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return NULL;
	}

	char command = COMMAND_GET_VERSION;

	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;

    m_cls_eth_client->Send(command, &scale_factor, &data, &len);

	char* version = NULL;
	
	if (len > 0)
	{
		version = new char[len];
		memcpy(version, data, len);
	}

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return version;
}

int CEyedeaInterface::Calibration_Save(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_CALIBRATION_SAVE;

	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::Calibration_Load(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_CALIBRATION_LOAD;

	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if(ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while(1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if(ret == 0){
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::Calibration_Copy(const int id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_CALIBRATION_COPY;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//index
	data[0] = (id & 0xFF000000) >> 24;
	data[1] = (id & 0x00FF0000) >> 16;
	data[2] = (id & 0x0000FF00) >> 8;
	data[3] = (id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while (1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if (ret == 0) {
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::ApplyAndMakeBaseGlobalInfo(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_BASE_SET_GLOBAL_CONFIG;

	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::ApplyAndMakeBaseLocalInfo(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_BASE_SET_LOCAL_CONFIG;

	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::ApplyAndMakeSearchAreaLocalInfo(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_SEARCH_AREA_SET_LOCAL_CONFIG;

	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

#if 1
int CEyedeaInterface::SetCameraConfig_Default()
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_CAMERA_CONFIG_SET_DEFAULT;

	int len = 0;
	unsigned char* data = NULL; // new char[len];
	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while (1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if (ret == 0) {
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::SetCameraConfig_Save()
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_CAMERA_CONFIG_SAVE;

	int len = 0;
	unsigned char* data = NULL; // new char[len];
	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while (1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if (ret == 0) {
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::SetCameraConfig_Load()
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_CAMERA_CONFIG_LOAD;
	unsigned char* data = NULL; // new char[len];
	int len = 0;

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while (1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if (ret == 0) {
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::GetCameraConfig(int type)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_CAMERA_CONFIG_GET;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//type
	data[0] = (type & 0xFF000000) >> 24;
	data[1] = (type & 0x00FF0000) >> 16;
	data[2] = (type & 0x0000FF00) >> 8;
	data[3] = (type & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
	if (ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while (1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if (ret == 0) {
				ret = m_cls_eth_client->Send(command, &scale_factor, (unsigned char **)&data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}
					return ret;
				}
				continue;
			}
		}
	}
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	ret = 0;

	if (len >= 4)
	{
		//x
		int val = ((int)data[0] << 24) & 0xFF000000;
		val |= ((int)data[1] << 16) & 0x00FF0000;
		val |= ((int)data[2] << 8) & 0x0000FF00;
		val |= ((int)data[3]) & 0x000000FF;
		ret = val;
	}
	//	printf("command val ( 0x%x / 0x%x )\n", type, *retval);
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}
#endif

int CEyedeaInterface::SetCameraConfig(int type, int value, int value2)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	//char command = COMMAND_SET_CAMERA_CONFIG;
	char command = COMMAND_CAMERA_CONFIG_SET;

	int len = 12;
	unsigned char* data = new unsigned char[len];

	//type
	data[0] = (type & 0xFF000000) >> 24;
	data[1] = (type & 0x00FF0000) >> 16;
	data[2] = (type & 0x0000FF00) >> 8;
	data[3] = (type & 0x000000FF);

	//value
	data[4] = (value & 0xFF000000) >> 24;
	data[5] = (value & 0x00FF0000) >> 16;
	data[6] = (value & 0x0000FF00) >> 8;
	data[7] = (value & 0x000000FF);

	//value
	data[8] = (value2 & 0xFF000000) >> 24;
	data[9] = (value2 & 0x00FF0000) >> 16;
	data[10] = (value2 & 0x0000FF00) >> 8;
	data[11] = (value2 & 0x000000FF);


	unsigned int scale_factor = 1;
	int ret = 0;
    ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	
	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

    return ret;
}

int CEyedeaInterface::BackgroundLearning(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_BACKGROUND_LEARN;

	int len = 0;
	unsigned char* data = NULL;

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::FindSearchArea(int level)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_FIND_SEARCH_AREA;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//type
	data[0] = (level & 0xFF000000) >> 24;
	data[1] = (level & 0x00FF0000) >> 16;
	data[2] = (level & 0x0000FF00) >> 8;
	data[3] = (level & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::Geometry_Distance(const int base_id, const int target_id, const float base_info, const float tol, float *out_value)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GEOMETRY_DISTANCE;

	int len = 4 * 4;
	unsigned char* data = new unsigned char[len];

	unsigned int scale_factor = 10000;

	int index = 0;

	//base_id
	data[index++] = (base_id & 0xFF000000) >> 24;
	data[index++] = (base_id & 0x00FF0000) >> 16;
	data[index++] = (base_id & 0x0000FF00) >> 8;
	data[index++] = (base_id & 0x000000FF);

	//target_id
	data[index++] = (target_id & 0xFF000000) >> 24;
	data[index++] = (target_id & 0x00FF0000) >> 16;
	data[index++] = (target_id & 0x0000FF00) >> 8;
	data[index++] = (target_id & 0x000000FF);

	//base_info
	int i_base_info = base_info * scale_factor;
	data[index++] = (i_base_info & 0xFF000000) >> 24;
	data[index++] = (i_base_info & 0x00FF0000) >> 16;
	data[index++] = (i_base_info & 0x0000FF00) >> 8;
	data[index++] = (i_base_info & 0x000000FF);

	//tol
	int i_tol = tol * scale_factor;
	data[index++] = (i_tol & 0xFF000000) >> 24;
	data[index++] = (i_tol & 0x00FF0000) >> 16;
	data[index++] = (i_tol & 0x0000FF00) >> 8;
	data[index++] = (i_tol & 0x000000FF);
	
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);

	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	int i_value = 0;
	if (len >= 4)
	{
		//i_value
		i_value = ((int)data[0] << 24) & 0xFF000000;
		i_value |= ((int)data[1] << 16) & 0x00FF0000;
		i_value |= ((int)data[2] << 8) & 0x0000FF00;
		i_value |= ((int)data[3]) & 0x000000FF;
	}

	(*out_value) = (float)i_value / (float)scale_factor;

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::Geometry_Angle(const int base_id, const int target_id, const float base_info, const float tol, float *out_value)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GEOMETRY_ANGLE;

	int len = 4 * 4;
	unsigned char* data = new unsigned char[len];

	unsigned int scale_factor = 10000;

	int index = 0;

	//base_id
	data[index++] = (base_id & 0xFF000000) >> 24;
	data[index++] = (base_id & 0x00FF0000) >> 16;
	data[index++] = (base_id & 0x0000FF00) >> 8;
	data[index++] = (base_id & 0x000000FF);

	//target_id
	data[index++] = (target_id & 0xFF000000) >> 24;
	data[index++] = (target_id & 0x00FF0000) >> 16;
	data[index++] = (target_id & 0x0000FF00) >> 8;
	data[index++] = (target_id & 0x000000FF);

	//base_info
	int i_base_info = base_info * scale_factor;
	data[index++] = (i_base_info & 0xFF000000) >> 24;
	data[index++] = (i_base_info & 0x00FF0000) >> 16;
	data[index++] = (i_base_info & 0x0000FF00) >> 8;
	data[index++] = (i_base_info & 0x000000FF);

	//tol
	int i_tol = tol * scale_factor;
	data[index++] = (i_tol & 0xFF000000) >> 24;
	data[index++] = (i_tol & 0x00FF0000) >> 16;
	data[index++] = (i_tol & 0x0000FF00) >> 8;
	data[index++] = (i_tol & 0x000000FF);

	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);

	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	int i_value = 0;
	if (len >= 4)
	{
		//i_value
		i_value = ((int)data[0] << 24) & 0xFF000000;
		i_value |= ((int)data[1] << 16) & 0x00FF0000;
		i_value |= ((int)data[2] << 8) & 0x0000FF00;
		i_value |= ((int)data[3]) & 0x000000FF;
	}

	(*out_value) = (float)i_value / (float)scale_factor;

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::Geometry_Clear(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_GEOMETRY_CLEAR;

	int len = 0;
	unsigned char* data = new unsigned char[len];
	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::Histogram_Set_Range(const int id, const int option, const int min_value, const int max_value)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_HISTOGRAM_SET_RANGE;

	int len = 4 * 4;
	unsigned char* data = new unsigned char[len];

	unsigned int scale_factor = 10000;

	int index = 0;

	//id
	data[index++] = (id & 0xFF000000) >> 24;
	data[index++] = (id & 0x00FF0000) >> 16;
	data[index++] = (id & 0x0000FF00) >> 8;
	data[index++] = (id & 0x000000FF);

	//option
	data[index++] = (option & 0xFF000000) >> 24;
	data[index++] = (option & 0x00FF0000) >> 16;
	data[index++] = (option & 0x0000FF00) >> 8;
	data[index++] = (option & 0x000000FF);

	//min value
	data[index++] = (min_value & 0xFF000000) >> 24;
	data[index++] = (min_value & 0x00FF0000) >> 16;
	data[index++] = (min_value & 0x0000FF00) >> 8;
	data[index++] = (min_value & 0x000000FF);

	//max value
	data[index++] = (max_value & 0xFF000000) >> 24;
	data[index++] = (max_value & 0x00FF0000) >> 16;
	data[index++] = (max_value & 0x0000FF00) >> 8;
	data[index++] = (max_value & 0x000000FF);

	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::Histogram_Get_Range(const int id, const int option, int *out_min_value, int *out_max_value)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_HISTOGRAM_GET_RANGE;

	int len = 4 * 2;
	unsigned char* data = new unsigned char[len];

	unsigned int scale_factor = 10000;

	int index = 0;

	//id
	data[index++] = (id & 0xFF000000) >> 24;
	data[index++] = (id & 0x00FF0000) >> 16;
	data[index++] = (id & 0x0000FF00) >> 8;
	data[index++] = (id & 0x000000FF);

	//option
	data[index++] = (option & 0xFF000000) >> 24;
	data[index++] = (option & 0x00FF0000) >> 16;
	data[index++] = (option & 0x0000FF00) >> 8;
	data[index++] = (option & 0x000000FF);


	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);

	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	index = 0;
	int i_min_value = -1;
	int i_max_value = -1;
	if (len >= 8)
	{
		//i_value
		i_min_value = ((int)data[index++] << 24) & 0xFF000000;
		i_min_value |= ((int)data[index++] << 16) & 0x00FF0000;
		i_min_value |= ((int)data[index++] << 8) & 0x0000FF00;
		i_min_value |= ((int)data[index++]) & 0x000000FF;

		//i_value
		i_max_value = ((int)data[index++] << 24) & 0xFF000000;
		i_max_value |= ((int)data[index++] << 16) & 0x00FF0000;
		i_max_value |= ((int)data[index++] << 8) & 0x0000FF00;
		i_max_value |= ((int)data[index++]) & 0x000000FF;
	}

	(*out_min_value) = i_min_value;
	(*out_max_value) = i_max_value;

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::Histogram_Get_Graph(const int id, float** out_histogram, float** out_histogram_b, float** out_histogram_g, float** out_histogram_r, float* out_histogram_size)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_HISTOGRAM_GET_GRAPH;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	//index
	int data_index = 0;
	data[data_index++] = (id & 0xFF000000) >> 24;
	data[data_index++] = (id & 0x00FF0000) >> 16;
	data[data_index++] = (id & 0x0000FF00) >> 8;
	data[data_index++] = (id & 0x000000FF);

	unsigned int scale_factor = 1;
	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
	if (ret == EYEDEA_ERROR_INVALID_MEMORY)
	{
		int sec = 0;
		while (1)
		{
			ret = m_cls_eth_client->Open(m_ip, m_port);
			if (ret == 0) {
				ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);
				break;
			}
			else
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
				sec++;
				if (sec >= 60)
				{
					if (data != NULL)
					{
						delete data;
						data = NULL;
					}

					return ret;
				}
				continue;
			}
		}
	}
	
	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	int i_histogram_size = 0;
	int i_histogram_data = 0;

	int index = 0;

	//printf("len=%d\n", len);

	if (len >= 4)
	{
		//i_histogram_size
		i_histogram_size = ((int)data[index++] << 24) & 0xFF000000;
		i_histogram_size |= ((int)data[index++] << 16) & 0x00FF0000;
		i_histogram_size |= ((int)data[index++] << 8) & 0x0000FF00;
		i_histogram_size |= ((int)data[index++]) & 0x000000FF;

		printf("i_histogram_size=%d, scale_factor=%d\n", i_histogram_size, scale_factor);

		(*out_histogram_size) = (float)i_histogram_size / (float)scale_factor;

		int histogram_size = (int)(*out_histogram_size);
		if (histogram_size > 0)
		{
			//gray
			if ((*out_histogram) != NULL)	free((*out_histogram));
			(*out_histogram) = (float *)malloc(sizeof(float)*histogram_size);

			for (int i = 0; i < histogram_size; i++)
			{
				//i_score
				i_histogram_data = ((int)data[index++] << 24) & 0xFF000000;
				i_histogram_data |= ((int)data[index++] << 16) & 0x00FF0000;
				i_histogram_data |= ((int)data[index++] << 8) & 0x0000FF00;
				i_histogram_data |= ((int)data[index++]) & 0x000000FF;

				(*out_histogram)[i] = (float)i_histogram_data / (float)scale_factor;
			}

			//b
			if ((*out_histogram_b) != NULL)	free((*out_histogram_b));
			(*out_histogram_b) = (float *)malloc(sizeof(float)*histogram_size);

			for (int i = 0; i < histogram_size; i++)
			{
				//i_score
				i_histogram_data = ((int)data[index++] << 24) & 0xFF000000;
				i_histogram_data |= ((int)data[index++] << 16) & 0x00FF0000;
				i_histogram_data |= ((int)data[index++] << 8) & 0x0000FF00;
				i_histogram_data |= ((int)data[index++]) & 0x000000FF;

				(*out_histogram_b)[i] = (float)i_histogram_data / (float)scale_factor;
			}

			//g
			if ((*out_histogram_g) != NULL)	free((*out_histogram_g));
			(*out_histogram_g) = (float *)malloc(sizeof(float)*histogram_size);

			for (int i = 0; i < histogram_size; i++)
			{
				//i_score
				i_histogram_data = ((int)data[index++] << 24) & 0xFF000000;
				i_histogram_data |= ((int)data[index++] << 16) & 0x00FF0000;
				i_histogram_data |= ((int)data[index++] << 8) & 0x0000FF00;
				i_histogram_data |= ((int)data[index++]) & 0x000000FF;

				(*out_histogram_g)[i] = (float)i_histogram_data / (float)scale_factor;
			}

			//r
			if ((*out_histogram_r) != NULL)	free((*out_histogram_r));
			(*out_histogram_r) = (float *)malloc(sizeof(float)*histogram_size);

			for (int i = 0; i < histogram_size; i++)
			{
				//i_score
				i_histogram_data = ((int)data[index++] << 24) & 0xFF000000;
				i_histogram_data |= ((int)data[index++] << 16) & 0x00FF0000;
				i_histogram_data |= ((int)data[index++] << 8) & 0x0000FF00;
				i_histogram_data |= ((int)data[index++]) & 0x000000FF;

				(*out_histogram_r)[i] = (float)i_histogram_data / (float)scale_factor;
			}
		}
	}


	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return i_histogram_size;
}

int CEyedeaInterface::Histogram_Set_Use_Element(const int id, const int option)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_HISTOGRAM_SET_USE_ELEMENT;

	int len = 4 * 2;
	unsigned char* data = new unsigned char[len];

	unsigned int scale_factor = 10000;

	int index = 0;

	//id
	data[index++] = (id & 0xFF000000) >> 24;
	data[index++] = (id & 0x00FF0000) >> 16;
	data[index++] = (id & 0x0000FF00) >> 8;
	data[index++] = (id & 0x000000FF);

	//option
	data[index++] = (option & 0xFF000000) >> 24;
	data[index++] = (option & 0x00FF0000) >> 16;
	data[index++] = (option & 0x0000FF00) >> 8;
	data[index++] = (option & 0x000000FF);


	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::Histogram_Get_Use_Element(const int id, int *out_option)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_HISTOGRAM_GET_USE_ELEMENT;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	unsigned int scale_factor = 10000;

	int index = 0;

	//id
	data[index++] = (id & 0xFF000000) >> 24;
	data[index++] = (id & 0x00FF0000) >> 16;
	data[index++] = (id & 0x0000FF00) >> 8;
	data[index++] = (id & 0x000000FF);


	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);

	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	index = 0;
	int i_option = 0;
	if (len >= 4)
	{
		//i_value
		i_option = ((int)data[index++] << 24) & 0xFF000000;
		i_option |= ((int)data[index++] << 16) & 0x00FF0000;
		i_option |= ((int)data[index++] << 8) & 0x0000FF00;
		i_option |= ((int)data[index++]) & 0x000000FF;
	}

	(*out_option) = i_option;

	return ret;
}

int CEyedeaInterface::Histogram_Get_Pixel_Count(const int index1, const int index2, int *out_count)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_HISTOGRAM_GET_PIXEL_COUNT_RESULT;

	int len = 4*2;
	unsigned char* data = new unsigned char[len];

	unsigned int scale_factor = 10000;

	int index = 0;

	//id
	data[index++] = (index1 & 0xFF000000) >> 24;
	data[index++] = (index1 & 0x00FF0000) >> 16;
	data[index++] = (index1 & 0x0000FF00) >> 8;
	data[index++] = (index1 & 0x000000FF);

	data[index++] = (index2 & 0xFF000000) >> 24;
	data[index++] = (index2 & 0x00FF0000) >> 16;
	data[index++] = (index2 & 0x0000FF00) >> 8;
	data[index++] = (index2 & 0x000000FF);


	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);

	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	index = 0;
	int i_count = 0;
	if (len >= 4)
	{
		//i_value
		i_count = ((int)data[index++] << 24) & 0xFF000000;
		i_count |= ((int)data[index++] << 16) & 0x00FF0000;
		i_count |= ((int)data[index++] << 8) & 0x0000FF00;
		i_count |= ((int)data[index++]) & 0x000000FF;
	}

	(*out_count) = i_count;

	return ret;
}

int CEyedeaInterface::Histogram_Get_Pixel_Count(const int id, int *out_count)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_HISTOGRAM_GET_PIXEL_COUNT_ID;

	int len = 4 * 2;
	unsigned char* data = new unsigned char[len];

	unsigned int scale_factor = 10000;

	int index = 0;

	//id
	data[index++] = (id & 0xFF000000) >> 24;
	data[index++] = (id & 0x00FF0000) >> 16;
	data[index++] = (id & 0x0000FF00) >> 8;
	data[index++] = (id & 0x000000FF);

	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);

	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	index = 0;
	int i_count = 0;
	if (len >= 4)
	{
		//i_value
		i_count = ((int)data[index++] << 24) & 0xFF000000;
		i_count |= ((int)data[index++] << 16) & 0x00FF0000;
		i_count |= ((int)data[index++] << 8) & 0x0000FF00;
		i_count |= ((int)data[index++]) & 0x000000FF;
	}

	(*out_count) = i_count;

	return ret;
}

int CEyedeaInterface::Histogram_Set_Inspection_Pixel_Count(const int id, const int count)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_HISTOGRAM_SET_INSPECTION_PIXEL_COUNT;

	int len = 4 * 2;
	unsigned char* data = new unsigned char[len];

	unsigned int scale_factor = 10000;

	int index = 0;

	//id
	data[index++] = (id & 0xFF000000) >> 24;
	data[index++] = (id & 0x00FF0000) >> 16;
	data[index++] = (id & 0x0000FF00) >> 8;
	data[index++] = (id & 0x000000FF);

	data[index++] = (count & 0xFF000000) >> 24;
	data[index++] = (count & 0x00FF0000) >> 16;
	data[index++] = (count & 0x0000FF00) >> 8;
	data[index++] = (count & 0x000000FF);


	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::Histogram_Get_Inspection_Pixel_Count(const int id, int *out_count)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_HISTOGRAM_GET_INSPECTION_PIXEL_COUNT;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	unsigned int scale_factor = 10000;

	int index = 0;

	//id
	data[index++] = (id & 0xFF000000) >> 24;
	data[index++] = (id & 0x00FF0000) >> 16;
	data[index++] = (id & 0x0000FF00) >> 8;
	data[index++] = (id & 0x000000FF);

	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);

	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	index = 0;
	int i_count = 0;
	if (len >= 4)
	{
		//i_value
		i_count = ((int)data[index++] << 24) & 0xFF000000;
		i_count |= ((int)data[index++] << 16) & 0x00FF0000;
		i_count |= ((int)data[index++] << 8) & 0x0000FF00;
		i_count |= ((int)data[index++]) & 0x000000FF;
	}

	(*out_count) = i_count;

	return ret;
}

int CEyedeaInterface::Histogram_Set_Inspection_Pixel_Count_Tolerance_Rate(const int id, const float rate)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_HISTOGRAM_SET_INSPECTION_PIXEL_COUNT_TOL_RATE;

	int len = 4 * 2;
	unsigned char* data = new unsigned char[len];

	unsigned int scale_factor = 10000;

	int i_rate = rate * scale_factor;

	int index = 0;

	//id
	data[index++] = (id & 0xFF000000) >> 24;
	data[index++] = (id & 0x00FF0000) >> 16;
	data[index++] = (id & 0x0000FF00) >> 8;
	data[index++] = (id & 0x000000FF);

	data[index++] = (i_rate & 0xFF000000) >> 24;
	data[index++] = (i_rate & 0x00FF0000) >> 16;
	data[index++] = (i_rate & 0x0000FF00) >> 8;
	data[index++] = (i_rate & 0x000000FF);


	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);

	if (data != NULL)
	{
		delete data;
		data = NULL;
	}

	return ret;
}

int CEyedeaInterface::Histogram_Get_Inspection_Pixel_Count_Tolerance_Rate(const int id, float *out_rate)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the ERVS\n");
		return EYEDEA_ERROR_INVALID_MEMORY;
	}

	char command = COMMAND_HISTOGRAM_GET_INSPECTION_PIXEL_COUNT_TOL_RATE;

	int len = 4;
	unsigned char* data = new unsigned char[len];

	unsigned int scale_factor = 10000;

	int index = 0;

	//id
	data[index++] = (id & 0xFF000000) >> 24;
	data[index++] = (id & 0x00FF0000) >> 16;
	data[index++] = (id & 0x0000FF00) >> 8;
	data[index++] = (id & 0x000000FF);

	int ret = 0;
	ret = m_cls_eth_client->Send(command, &scale_factor, &data, &len);

	if (ret != 0)
	{
		if (data != NULL)
		{
			delete data;
			data = NULL;
		}

		return ret;
	}

	index = 0;
	int i_count = 0;
	if (len >= 4)
	{
		//i_value
		i_count = ((int)data[index++] << 24) & 0xFF000000;
		i_count |= ((int)data[index++] << 16) & 0x00FF0000;
		i_count |= ((int)data[index++] << 8) & 0x0000FF00;
		i_count |= ((int)data[index++]) & 0x000000FF;
}

	(*out_rate) = (float)i_count / (float)scale_factor;

	return ret;
}

#if 0
int CEyedeaInterface::ThreadFunctionNetwork(void)
{
	int length;
	char* recv_data;
	char command = 0;

	while (m_run_thread_net)												//thread loop
	{
		//printf("\033[2J");
		//printf("\033[1;1H");

		char data = COMMAND_GET_IMAGE;
		recv_data = m_cls_eth_client->Send(data, &length);

#if 0
		if (data == COMMAND_GET_IMAGE)
		{
			{
				boost::lock_guard<boost::recursive_mutex> lock(m_guard);

				if (m_display.empty())
				{
					m_display = cv::Mat::zeros(cv::Size(640, 480), CV_8UC3); //cv::imread("base.png");		//opencv mat for display
				}

				memcpy(m_display.data, recv_data, length);

				delete (recv_data);
				recv_data = NULL;
			}
		}
#endif

#if 0
		if (*recv_data == (unsigned char)'n')
			cout << "wrong data" << endl;
		else
			cout << "data : " << recv_data << " data_length : " << length << endl;
#endif

		boost::this_thread::sleep(boost::posix_time::millisec(1000));		//1 msec sleep
	};
}
#endif

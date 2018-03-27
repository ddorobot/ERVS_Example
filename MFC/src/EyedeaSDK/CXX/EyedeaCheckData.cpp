#include "EyedeaCheckData.h"

CEyedeaCheckData::CEyedeaCheckData(void) :
	m_tmp_size(0)
	,m_tmp_size2(0)
	,m_tmp_buf(NULL)
	,m_tmp_buf2(NULL)
	,m_tmp_index(0)
	, m_head_find_count(0)
	,m_tail_find_count(0)
{
	m_tmp_size = (640 * 480 * 3) + 15 + 1;
	m_tmp_size2 = (640 * 480 * 3) + 15 + 1;
	m_tmp_buf = (unsigned char *)malloc(sizeof(unsigned char) * m_tmp_size);
	m_tmp_buf2 = (unsigned char *)malloc(sizeof(unsigned char) * m_tmp_size2);

	memset(m_tmp_buf, 0, m_tmp_size);
	memset(m_tmp_buf2, 0, m_tmp_size2);

	m_tmp_index = 0;

	m_head_string[0] = 'e';
	m_head_string[1] = 'y';
	m_head_string[2] = 'e';
	m_head_string[3] = 'd';
	m_head_string[4] = 'e';
	m_head_string[5] = 'a';

	m_tail_string[0] = 'E';
	m_tail_string[1] = 'R';
	m_tail_string[2] = 'V';
	m_tail_string[3] = 'S';
}

CEyedeaCheckData::~CEyedeaCheckData(void)
{
	if (m_tmp_buf != NULL) free(m_tmp_buf);
	if (m_tmp_buf2 != NULL) free(m_tmp_buf2);
}

unsigned char* CEyedeaCheckData::FindData(char* input_buf, int input_size, int* out_size)
{
	for (int i = 0; i < input_size; i++)
	{
		//find head
		if (m_head_find_count < 6)
		{
			if (input_buf[i] == m_head_string[m_head_find_count])
			{
				m_head_find_count++;
			}
			else
			{
				m_head_find_count = 0;		//fail
				m_tmp_index = 0;
			}
		}
		else
		{
			memset(m_tmp_buf + m_tmp_index, 0, input_size - i);

			memcpy(m_tmp_buf + m_tmp_index, input_buf+i, input_size-i);
			m_tmp_index += (input_size - i);

			/*
			printf("m_tmp_buf[0] = %d\n", m_tmp_buf[0]);
			printf("m_tmp_buf[1] = %d\n", m_tmp_buf[1]);
			printf("m_tmp_buf[2] = %d\n", m_tmp_buf[2]);
			printf("m_tmp_buf[3] = %d\n", m_tmp_buf[3]);
			printf("m_tmp_buf[4] = %d\n", m_tmp_buf[4]);
			if (m_tmp_buf[0] == 13)
			{
				printf("test");
			}
			*/

			//find tail
			if (m_tmp_index > 4)
			{
				if (m_tmp_buf[m_tmp_index - 1] == 'S' && m_tmp_buf[m_tmp_index - 2] == 'V' && 
					m_tmp_buf[m_tmp_index - 3] == 'R' && m_tmp_buf[m_tmp_index - 4] == 'E')
				{
					//ok
					(*out_size) = m_tmp_index;

					m_head_find_count = 0;
					m_tmp_index = 0;

					return m_tmp_buf;
				}
			}
			break;
		}
	}

	return NULL;
}

void CEyedeaCheckData::init_variable()
{
	m_tmp_index = 0;
	m_head_find_count = 0;
	m_tail_find_count = 0;
}

#ifndef _EYEDEA_CHECKDATA_H_
#define _EYEDEA_CHECKDATA_H_

#include <string>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdint.h>

class  CEyedeaCheckData
{
public:
	CEyedeaCheckData(void);
	~CEyedeaCheckData(void);

public:
	unsigned char* FindData(char* input_buf, int input_size, int* out_size);
	void init_variable();

private:
	int m_tmp_size;
	int m_tmp_size2;
	unsigned char* m_tmp_buf;
	unsigned char* m_tmp_buf2;
	int m_tmp_index;

	int m_head_find_count;
	unsigned char m_head_string[6];
	int m_tail_find_count ;
	unsigned char m_tail_string[4] ;
};

#endif

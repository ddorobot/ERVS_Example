#ifndef _EYEDEA_DEF_H_
#define _EYEDEA_DEF_H_

#define DISTANCE_A_B	1
#define DISTANCE_B_A	2

enum VisionConfigOption
{
	VISION_CONFIG_CALIBRATION_CHESS_NUM_COLS = 101,
	VISION_CONFIG_CALIBRATION_CHESS_NUM_ROWS,
	VISION_CONFIG_CALIBRATION_CHESS_SIZE ,
	VISION_CONFIG_BLUR,
	VISION_CONFIG_DENOISING,
	VISION_CONFIG_EDGE_LOW_THRESHOLD,
	VISION_CONFIG_EDGE_MAX_LOW_THRESHOLD,
	VISION_CONFIG_EDGE_KERNEL_SIZE,
	VISION_CONFIG_MATCHING_THRESHOLD,
	VISION_CONFIG_CIRCLE_DETECTION_INLIER_RATE,
	VISION_CONFIG_CIRCLE_DETECTION_MAX_ITERATION,
	VISION_CONFIG_L_MIN_ANGLE,
	VISION_CONFIG_L_MAX_ANGLE,
	VISION_CONFIG_EDGE_MATCHING_MARGIN,
	VISION_CONFIG_FIND_OBJECT_MASKING_OPTION,
	VISION_CONFIG_FIND_OBJECT_MASKING_OPTION_THRESHOLD,
	VISION_CONFIG_USE_CONVEXHULL,
	VISION_CONFIG_USE_BGSUB,
	VISION_CONFIG_ONLY_ONE_OBJECT,
	VISION_CONFIG_FIND_OBJECT_LEVEL,
	VISION_CONFIG_USE_CALIBRATION_IMAGE,
	VISION_CONFIG_USE_HISTOGRAM,
	VISION_CONFIG_IMAGE_MORPH_SIZE,
	VISION_CONFIG_POSITIVE_RATE ,
	VISION_CONFIG_FIND_ONE_OF_SUBS,
	VISION_CONFIG_DETECT_RETRY
};

enum GetImageOption
{
	GET_IMAGE_INPUT = 201,
	GET_IMAGE_BASE,
	GET_IMAGE_BASE_WITH_INFO,
	GET_IMAGE_BASE_ROI,
	GET_IMAGE_CALIBRATION_FEATURE,
	GET_IMAGE_BASE_HISTORY_MASK
};

enum DrawResultOption
{
	RESULT_DRAW_OPTION_SEARCH_FEAT	= 0x0001,
	RESULT_DRAW_OPTION_SEARCH_BOX	= 0x0002,
	RESULT_DRAW_OPTION_SEARCH_ARROW	= 0x0004,
	RESULT_DRAW_OPTION_MASTER_FEAT	= 0x0008,
	RESULT_DRAW_OPTION_MASTER_BOX	= 0x0010,
	RESULT_DRAW_OPTION_MASTER_TEXT	= 0x0020,
	RESULT_DRAW_OPTION_OBJECT		= 0x0040,
	RESULT_DRAW_OPTION_OBJECT_TEXT	= 0x0080,
	WITH_DRAW_OPTION_FEATURE		= 0x0100,
	WITH_DRAW_SEARCH_AREA_RANGE		= 0x0200,
	RESULT_DRAW_OPTION_ALL = 0xFFFF
};

enum SetCameraConfigOption
{
	SET_CAMERA_AUTO_EXPOSURE = 701,
	SET_CAMERA_AUTO_EXPOSURE_RANGE_GO_OUT,
	SET_CAMERA_AUTO_EXPOSURE_RANGE_ENTER,
	SET_CAMERA_MANUAL_EXPOSURE,
	SET_CAMERA_MANUAL_EXPOSURE_EXPOSURE,
	SET_CAMERA_MANUAL_EXPOSURE_GAIN,
	SET_CAMERA_TAKE_PIC,
	SET_CAMERA_LED_BRIGHTNESS,
	SET_CAMERA_LED_TIMER_ON,
};

enum GetCameraConfigOption
{
	GET_CAMERA_AUTO_EXPOSURE = 801,
	GET_CAMERA_AUTO_EXPOSURE_RANGE_GO_OUT,
	GET_CAMERA_AUTO_EXPOSURE_RANGE_ENTER,
	GET_CAMERA_MANUAL_EXPOSURE,
	GET_CAMERA_MANUAL_EXPOSURE_EXPOSURE,
	GET_CAMERA_MANUAL_EXPOSURE_GAIN,
	GET_CAMERA_MANUAL_EXPOSURE_EXPOSURE_MAX,
	GET_CAMERA_MANUAL_EXPOSURE_GAIN_MAX,
	GET_CAMERA_MANUAL_EXPOSURE_EXPOSURE_MIN,
	GET_CAMERA_MANUAL_EXPOSURE_GAIN_MIN,
	GET_CAMERA_LED_BRIGHTNESS
};

enum HistogramUseOption
{
	HISTOGRAM_USE_GRAY = 0x0001,
	HISTOGRAM_USE_RED = 0x0002,
	HISTOGRAM_USE_GREEN = 0x0004,
	HISTOGRAM_USE_BLUE = 0x0008,
	HISTOGRAM_USE_ALL = 0xFFFF
};

#endif
#ifndef _EYEDEA_INTERFACE_H_
#define _EYEDEA_INTERFACE_H_

#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread.hpp>														//eyedea - using thread on boost.
#include "EyedeaEthernetClient.h"

//boost::mutex io_mutex; // The iostreams are not guaranteed to be thread-safe!

#define TRANS_IAMGE_WIDTH		640
#define TRANS_IAMGE_HEIGHT		480

class  CEyedeaInterface
{
private:
	char* m_ip;
	int m_port;
public:
	CEyedeaInterface(void);
	~CEyedeaInterface(void);

	//void Connect(char* ip, char* port);
	//void ThreadFunctionNetwork(void);	//eyedea - thread function
	void Close(void);	//eyedea - function
	int GetImage(int option, int option2, char** out_data, int* len);
	int GetResultImage(int option, int option2, char** out_data, int* len);
	int SetSelectBaseObject(float x, float y, float w, float h);
	int GetSelectBaseObject(float *out_x, float *out_y, float *out_w, float *out_h, float *out_roi_center_x, float *out_roi_center_y, float *out_bound_center_x, float *out_bound_center_y, float *out_mass_center_x, float *out_mass_center_y);
	int SetZoomArea(float x, float y, float w, float h);
	int ResetZoomArea(void);
	int SetMaskArea(float x, float y, float w, float h, bool inverse);
	int UndoMaskArea(void);
	int DelMaskArea(void);
	int GetMaskArea(int *out_count, float **out_x, float **out_y, float **out_w, float **out_h, bool **out_inverse);
	int SetObjectCircle(float x, float y, float r1, float r2);
	int SetObjectCircle(const float x, const float y, const float r1, const float r2, const float min_r1, const float min_r2, const float max_r1, const float max_r2);
	int GetObjectCircle(float *out_x, float *out_y, float *out_r1, float *out_r2, float *out_min_r1, float *out_min_r2, float *out_max_r1, float *out_max_r2, float *out_user_x, float *out_user_y, float *out_user_r1, float *out_user_r2);
	int SetObjectCircleBaseDiameter(const int id, const int diameter);
	int GetObjectCircleBaseDiameter(const int id);
	int SetObjectCircleDiameterTolerance(const int id, const int min_value, const int max_value);
	int GetObjectCircleDiameterTolerance(const int id, int *out_min_value, int *out_max_value);
	int SetObjectCircleDiameterInspection(const int id, const bool use);
	int GetObjectCircleDiameterInspection(const int id);
	float GetObjectCircleCalcDiameter(const int id);
	int SetObjectLine(float x, float y, float w, float h);
	int SetObjectLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	int GetObjectLine(int *out_count, float **out_x1, float **out_y1, float **out_x2, float **out_y2, float **out_x3, float **out_y3, float **out_x4, float **out_y4, float **out_line1_x, float **out_line1_y, float **out_line2_x, float **out_line2_y);
	int DeleteObjectLine(void);
	int ClearObjectLine(void);
	int SetObjectTwoLine(const int id, float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
	int SetObjectTwoLineBaseDistance(const int id, const int dist);
	int GetObjectTwoLineBaseDistance(const int id);
	
	float GetObjectTwoLineCalcDistance(const int id);
	float GetObjectTwoLineCalcAngle(const int id);
	int SetObjectTwoLineDistanceTolerance(const int id, const int min_value, const int max_value);
	int GetObjectTwoLineDistanceTolerance(const int id, int *out_min_value, int *out_max_value);
	int SetObjectTwoLineAngleTolerance(const int id, const int min_value, const int max_value);
	int GetObjectTwoLineAngleTolerance(const int id, int *out_min_value, int *out_max_value);
	int SetObjectTwoLineDistanceType(const int id, const int type);
	int GetObjectTwoLineDistanceType(const int id);
	int SetObjectTwoLineDistanceInspection(const int id, const bool use);
	int GetObjectTwoLineDistanceInspection(const int id);
	int SetObjectTwoLineAngleInspection(const int id, const bool use);
	int GetObjectTwoLineAngleInspection(const int id);
	int SetObjectTwoLineBaseAngle(const int id, const int angle);
	int GetObjectTwoLineBaseAngle(const int id);

	int SetBase(int dep_id);
	int SetBaseTemp(void);
	int SetNextImage(void);
	int OptionFixSearchAreaOn(void);
	int OptionFixSearchAreaOff(void);
	int GetOptionFixSearchArea(void);
	int FileSaveObjectListInfo(std::string path, const int id);
	int FileLoadObjectListInfo(std::string path, const int id);
	int SetVisionConfigOption(int option, float value);
	float GetVisionConfigOption(int option);

	int CreateSocket(char* ip, int port);
	void DeleteSocket();

	int DBAddObject(void);
	int GetDBCount(void);
	int GetDB_Info_Id(int index);
	int GetDB_Select_ID(void);
	int SetObject(int id=-1);
	int DB_Del_ID(int id = -1);
	char* DB_Get_Mode(int id);

	int SetJobName(const int id, const std::string name);
	std::string GetJobName(const int id);
	int SetToolName(const int id, const std::string name);
	std::string GetToolName(const int id);
	int SetToolType(const int id, const int type);
	int GetToolType(const int id);
	int SetToolState(const int id, const int state);
	int GetToolState(const int id);
	int SetRobotPose(const int id, double* posj, int posj_size);
	double*  GetRobotPose(const int id, int* posj_size);

	
	int GetFindObjectInfo(int index, int max_objects_count, int option, float** out_id, float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry, float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry, float** out_circle_rx, float** out_circle_ry, float** out_line1_x, float** out_line1_y, float** out_line2_x, float** out_line2_y, float** out_angle, float** out_type, float** out_score, float** out_pass);
	int GetFindObjectInfo(int index, int max_objects_count, int option, float** out_id,
							float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_rz,
							float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry,
							float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry,
							float** out_circle_rx, float** out_circle_ry, float ** out_circle_diameter, float** out_circle_pass,
							float** out_line_distance, float** out_line_distance_pass,
							float** out_line_angle, float** out_line_angle_pass,
							float** out_histogram, float** out_histogram_pass,
							float** out_angle, float** out_type, float** out_score, float** out_tool_type);
	int GetDetectData(const int id, float** out_id,
							float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_rz,
							float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry,
							float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry,
							float** out_circle_rx, float** out_circle_ry, float ** out_circle_diameter, float** out_circle_pass,
							float** out_line_distance, float** out_line_distance_pass,
							float** out_line_angle, float** out_line_angle_pass,
							float** out_histogram, float** out_histogram_pass,
							float** out_angle, float** out_type, float** out_score, float** out_tool_type);
	int GetDetectData_Init(const int id, float** out_id,
		float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_rz,
		float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry,
		float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry,
		float** out_circle_rx, float** out_circle_ry, float ** out_circle_diameter, float** out_circle_pass,
		float** out_line_distance, float** out_line_distance_pass,
		float** out_line_angle, float** out_line_angle_pass,
		float** out_histogram, float** out_histogram_pass,
		float** out_angle, float** out_type, float** out_score, float** out_tool_type);
	int SetDetectData_Init(const int id);

	int GetFindObjectResultInfo(int base_index, int sub_index, float* out_id, float* out_cx, float* out_cy, float* out_rx, float* out_ry, float* out_angle, float* out_type, float* out_score, float** out_histogram, float** out_histogram_b, float** out_histogram_g, float** out_histogram_r, float* out_histogram_size);

	int Calibration_Add(float robot_x, float robot_y);
	int Calibration_GetCount(void);
	int Calibration_GetImage(int index, char** out_data, int* len);
	int Calibration_GetRobotInfo(int index, float *out_robot_x, float *out_robot_y);
	int Calibration_Del(int index);
	int Calibration_Clear(void);
	int Calibration_Run(void);
	int Calibration_StandAlone_Init(void);
	int Calibration_StandAlone_Run(void);
	int Calibration_StandAlone_Get_Image_Count(void);
	int Calibration_StandAlone_Get_Feature_Pos(int index,float posA[3], float posB[3], float posC[3], float posD[3]);
	int Calibration_StandAlone_Set_Matrix(float matrix[12]);
	int Calibration_StandAlone_Get_Matrix(float matrix[12]);
	int Calibration_StandAlone_Calc_Calib_Matrix(float cposA[3], float cposB[3], float cposC[3], float cposD[3],
		float rposA[3], float rposB[3], float rposC[3], float rposD[3],
		float ret_Matrix[12]);
	int Calibration_GetPoint(const float in_px, const float in_py, float* out_rx, float* out_ry);
	int Calibration_GetChessPoint(const int index, float* out_rx, float* out_ry);
	int Calibration_isOK(void);
	int Calibration_GetID(void);
	int Calibration_Save(void);
	int Calibration_Load(void);
	int Calibration_Copy(const int id);

	char* GetVersion(void);
	int SetCameraConfig(int type, int value,int value2);
	int GetCameraConfig(int type);

	int SetCameraConfig_Default();
	int SetCameraConfig_Save();
	int SetCameraConfig_Load();

	int SetCameraConfig_Save_With_ID(int ConfigID);
	int SetCameraConfig_Load_With_ID(int ConfigID);

	int BackgroundLearning(void);

	//Geometry
	int Geometry_Get_Distance(const int base_id, const int target_id, float *out_value);
	int Geometry_Distance(const int base_id, const int target_id, float *out_value, int *out_pass);
	int Geometry_Set_Inspection_Distance(const int base_id, const int target_id, const float value);
	int Geometry_Get_Inspection_Distance(const int base_id, const int target_id, float *out_value);
	int Geometry_Set_Inspection_Distance_Tolerance_Rate(const int base_id, const int target_id, const float value);
	int Geometry_Get_Inspection_Distance_Tolerance_Rate(const int base_id, const int target_id, float *out_value);
	int Geometry_Angle(const int base_id, const int target_id, float *out_value, int* out_pass);
	int Geometry_Get_Angle(const int base_id, const int target_id, float *out_value);
	int Geometry_Set_Inspection_Angle(const int base_id, const int target_id, const float value);
	int Geometry_Get_Inspection_Angle(const int base_id, const int target_id, float *out_value);
	int Geometry_Set_Inspection_Angle_Tolerance_Rate(const int base_id, const int target_id, const float value);
	int Geometry_Get_Inspection_Angle_Tolerance_Rate(const int base_id, const int target_id, float *out_value);
	int Geometry_MeetPoint(const int base_id, const int target_id, float *out_value_x, float *out_value_y);
	int Geometry_Clear(void);

	int Histogram_Set_Range(const int id, const int option, const int min_value, const int max_value);
	int Histogram_Get_Range(const int id, const int option, int *out_min_value, int *out_max_value);
	int Histogram_Get_Graph(const int id, float** out_histogram, float** out_histogram_b, float** out_histogram_g, float** out_histogram_r, float* out_histogram_size);
	int Histogram_Set_Use_Element(const int id, const int option);
	int Histogram_Get_Use_Element(const int id, int *out_option);
	int Histogram_Get_Pixel_Count(const int index1, const int index2, int *out_count);
	int Histogram_Get_Pixel_Count(const int id, int *out_count);
	int Histogram_Set_Inspection_Pixel_Count(const int id, const int count);
	int Histogram_Get_Inspection_Pixel_Count(const int id, int *out_count);
	int Histogram_Set_Inspection_Pixel_Count_Tolerance_Rate(const int id, const float rate);
	int Histogram_Get_Inspection_Pixel_Count_Tolerance_Rate(const int id, float *out_rate);
	int Histogram_Set_Inspection_Pixel_Count_Tolerance(const int id, const int min_value, const int max_value);
	int Histogram_Get_Inspection_Pixel_Count_Tolerance(const int id, int *out_min_value, int *out_max_value);

	int CalcFocusRate(const int id);
	int SetFocusRate(const int id, const int rate);
	int GetFocusRate(const int id);

	int CalcContrastRate(const int id);
	int SetContrastRate(const int id, const int rate);
	int GetContrastRate(const int id);

private:
	//bool m_run_thread_net;			//eyedea - boost thread exit value
	//boost::thread m_thread_net;		//eyedea - network thread
	boost::mutex mutex;

	CEyedeaEthernetClient *m_cls_eth_client;
};

#endif

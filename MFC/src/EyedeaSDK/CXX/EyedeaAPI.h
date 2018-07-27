#ifndef _EYEDEA_API_H_
#define _EYEDEA_API_H_

#include "EyedeaDef.h"
#include <string>

//[0] Connect
int ERVS_Connect(char* ip, int port);
void ERVS_Disconnect(void);

//[1] System
char* ERVS_GetVersion(void);
int ERVS_SetNextImage(void);
//[1] System : LED Control / Camera Control
int ERVS_SetCameraConfig(int type, int value, int value2);
int ERVS_GetCameraConfig(int type);
int ERVS_SetCameraConfig_Default();
int ERVS_SetCameraConfig_Save();
int ERVS_SetCameraConfig_Load();
int ERVS_SetCameraConfig_Save_With_ID(int ConfigID);
int ERVS_SetCameraConfig_Load_With_ID(int ConfigID);

//[2] Get Image Stream
int ERVS_GetImage(int option, int option2, char** data, int* len);
int ERVS_GetFindObjectResultImage(int option, int option2, char** data, int* len);

//[3] Job Management
int ERVS_DBAddObject(void);
int ERVS_DB_Del_ID(int id);
int ERVS_SetObject(int id = -1);
int ERVS_DB_Get_Count(void);
int ERVS_DB_Get_Select_ID(void);
int ERVS_DB_Get_Info_Id(int index);
char* ERVS_DB_Get_Mode(int id);
//DB Save/Load
int ERVS_DB_Get_SaveList(std::string path, int **out_arr_id_list, std::string **out_arr_jobname_list, std::string **out_arr_toolname_list);
int ERVS_FileSaveObjectDBList(std::string path, const int id, const bool use_image_file);
int ERVS_FileLoadObjectDBList(std::string path, const int id);
int ERVS_FileDeleteObjectDBList(std::string path, const int id);

//[4] Job Setting
//Base Image
int ERVS_SetBase(int dep_id);
int ERVS_SetBaseTemp(void);
//Name
int ERVS_SetJobName(const int id, const std::string name);
std::string ERVS_GetJobName(const int id);
int ERVS_SetToolName(const int id, const std::string name);
std::string ERVS_GetToolName(const int id);
//Tool Status
int ERVS_SetToolType(const int id, const int type);
int ERVS_GetToolType(const int id);
int ERVS_SetToolState(const int id, const int state);
int ERVS_GetToolState(const int id);
//Robot Pose Information
int ERVS_SetRobotPose(const int id, double* posj, int posj_size);
double* ERVS_GetRobotPose(const int id, int* posj_size);
//[4] Job Setting : Vision Config
int ERVS_SetVisionConfigOption(int option, float value);
float ERVS_GetVisionConfigOption(int option);
//[4] Job Setting : Zoom
int ERVS_SetZoomArea(float x, float y, float w, float h);
int ERVS_ResetZoomArea(void);
//[4] Job Setting : Fixed Area
int ERVS_OptionFixAreaOn(void);
int ERVS_OptionFixAreaOff(void);
int ERVS_GetOptionFixArea(void);
//[4] Job Setting : Mask Area
int ERVS_SetMaskArea(float x, float y, float w, float h, bool inverse);
int ERVS_UndoMaskArea(void);
int ERVS_DelMaskArea(void);
int ERVS_GetMaskArea(int *out_count, float **out_x, float **out_y, float **out_w, float **out_h, bool **out_inverse);
//[4] Job Setting : Object Setting : Object(Region)
int ERVS_SetSelectBaseObject(float x, float y, float w, float h);
int ERVS_GetSelectBaseObject(float *out_x, float *out_y, float *out_w, float *out_h, float *out_roi_center_x, float *out_roi_center_y, float *out_bound_center_x, float *out_bound_center_y, float *out_mass_center_x, float *out_mass_center_y);
//Histogram 
int ERVS_Histogram_Get_Graph(const int id, float** out_histogram, float** out_histogram_b, float** out_histogram_g, float** out_histogram_r, float* out_histogram_size);
int ERVS_Histogram_Set_Range(const int id, const int option, const int min_value, const int max_value);
int ERVS_Histogram_Get_Range(const int id, const int option, int *out_min_value, int *out_max_value);
int ERVS_Histogram_Set_Use_Element(const int id, const int option);
int ERVS_Histogram_Get_Use_Element(const int id, int *out_option);
int ERVS_Histogram_Set_Inspection_Pixel_Count(const int id, const int count);
int ERVS_Histogram_Get_Inspection_Pixel_Count(const int id, int *out_count);
int ERVS_Histogram_Set_Inspection_Pixel_Count_Tolerance_Rate(const int id, const float rate);
int ERVS_Histogram_Get_Inspection_Pixel_Count_Tolerance_Rate(const int id, float *out_rate);
int ERVS_Histogram_Set_Inspection_Pixel_Count_Tolerance(const int id, const int min_value, const int max_value);
int ERVS_Histogram_Get_Inspection_Pixel_Count_Tolerance(const int id, int *out_min_value, int *out_max_value);
int ERVS_Histogram_Get_Pixel_Count(const int id, int *out_count);
int ERVS_Histogram_Get_Pixel_Count(const int index1, const int index2, int *out_count);
int ERVS_Histogram_Set_Inspection(const int id, const bool use);
int ERVS_Histogram_Get_Inspection(const int id);
//[4] Job Setting : Object Setting : Object(Circle)
int ERVS_SetObjectCircle(float x, float y, float r1, float r2);
int ERVS_SetObjectCircle(const float x, const float y, const float r1, const float r2, const float min_r1, const float min_r2, const float max_r1, const float max_r2);
int ERVS_GetObjectCircle(float *out_x, float *out_y, float *out_r1, float *out_r2, float *out_min_r1, float *out_min_r2, float *out_max_r1, float *out_max_r2, float *out_user_x, float *out_user_y, float *out_user_r1, float *out_user_r2);
int ERVS_SetObjectCircleBaseDiameter(const int id, const int diameter);
int ERVS_GetObjectCircleBaseDiameter(const int id);
int ERVS_SetObjectCircleDiameterTolerance(const int id, const int min_value, const int max_value);
int ERVS_GetObjectCircleDiameterTolerance(const int id, int *out_min_value, int *out_max_value);
int ERVS_SetObjectCircleDiameterInspection(const int id, const bool use);
int ERVS_GetObjectCircleDiameterInspection(const int id);
float ERVS_GetObjectCircleCalcDiameter(const int id);
//[4] Job Setting : Object Setting : Object(Tow Line)
int ERVS_SetObjectLine(float x, float y, float w, float h);
int ERVS_SetObjectLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
int ERVS_GetObjectLine(int *out_count, float **out_x1, float **out_y1, float **out_x2, float **out_y2, float **out_x3, float **out_y3, float **out_x4, float **out_y4, float **out_line1_x, float **out_line1_y, float **out_line2_x, float **out_line2_y);
int ERVS_DelObjectLine(void);
int ERVS_ClrObjectLine(void);
int ERVS_SetObjectTwoLine(const int id, float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
//Two Line Distance
int ERVS_SetObjectTwoLineBaseDistance(const int id, const int dist);
int ERVS_GetObjectTwoLineBaseDistance(const int id);
float ERVS_GetObjectTwoLineCalcDistance(const int id);
int ERVS_SetObjectTwoLineDistanceTolerance(const int id, const int min_value, const int max_value);
int ERVS_GetObjectTwoLineDistanceTolerance(const int id, int *out_min_value, int *out_max_value);
int ERVS_SetObjectTwoLineDistanceType(const int id, const int type);
int ERVS_GetObjectTwoLineDistanceType(const int id);
int ERVS_SetObjectTwoLineDistanceInspection(const int id, const bool use);
int ERVS_GetObjectTwoLineDistanceInspection(const int id);
//Two Line Angle
int ERVS_SetObjectTwoLineBaseAngle(const int id, const int angle);
int ERVS_GetObjectTwoLineBaseAngle(const int id);
float ERVS_GetObjectTwoLineCalcAngle(const int id);
int ERVS_SetObjectTwoLineAngleTolerance(const int id, const int min_value, const int max_value);
int ERVS_GetObjectTwoLineAngleTolerance(const int id, int *out_min_value, int *out_max_value);
int ERVS_SetObjectTwoLineAngleInspection(const int id, const bool use);
int ERVS_GetObjectTwoLineAngleInspection(const int id);

//[5] Calibration
//Calibration
int ERVS_Calibration_Add(float robot_x, float robot_y);
int ERVS_Calibration_GetCount(void);
int ERVS_Calibration_GetImage(int index, char** data, int* len);
int ERVS_Calibration_GetRobotInfo(int index, float *out_robot_x, float *out_robot_y);
int ERVS_Calibration_Del(int index);
int ERVS_Calibration_Clear(void);
int ERVS_Calibration_Run(void);
int ERVS_Calibration_StandAlone_Init(void);
int ERVS_Calibration_StandAlone_Run(void);
int ERVS_Calibration_StandAlone_Get_Image_Count(void);
int ERVS_Calibration_StandAlone_Get_Feature_Pos(int index, float posA[3], float posB[3], float posC[3], float posD[3]);
int ERVS_Calibration_StandAlone_Set_Matrix(float matrix[12]);
int ERVS_Calibration_StandAlone_Get_Matrix(float matrix[12]);
int ERVS_Calibration_StandAlone_Calc_Calib_Matrix(float cposA[3], float cposB[3], float cposC[3], float cposD[3],
	float rposA[3], float rposB[3], float rposC[3], float rposD[3],
	float ret_Matrix[12]);
int ERVS_Calibration_StandAlone_Y_Direction(int Direction);
int ERVS_Calibration_GetPoint(const float in_px, const float in_py, float* out_rx, float* out_ry);
int ERVS_Calibration_GetChessPoint(const int index, float* out_rx, float* out_ry);
int ERVS_Calibration_isOK(void);
int ERVS_Calibration_Save(void);
int ERVS_Calibration_Load(void);
int ERVS_Calibration_Copy(const int id);
int ERVS_Calibration_GetID(void);

//[6] Background Train and Subtraction
int ERVS_BackgroundLearning(void);

//[7] Find Object
int ERVS_SetMainJobDetectRetry(const int id, int nRetryCount);
int ERVS_GetMainJobDetectRetry(const int id);
int ERVS_DetectWithGrab(int index, int max_objects_count, float** out_id, float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry, float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry, float** out_circle_rx, float** out_circle_ry, float** out_line1_x, float** out_line1_y, float** out_line2_x, float** out_line2_y, float** out_angle, float** out_type, float** out_score, float** out_pass);
int ERVS_DetectWithGrab(int index, int max_objects_count, float** out_id, 
						float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_rz,
						float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry, 
						float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry, 
						float** out_circle_rx, float** out_circle_ry, float ** out_circle_diameter, float** out_circle_pass, 
						float** out_line_distance, float** out_line_distance_pass,
						float** out_line_angle, float** out_line_angle_pass,
						float** out_histogram, float** out_histogram_pass,
						float** out_angle, float** out_type, float** out_score, float** out_tool_type);
int ERVS_DetectWithPrevImage(int index, int max_objects_count, float** out_id, float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry, float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry, float** out_circle_rx, float** out_circle_ry, float** out_line1_x, float** out_line1_y, float** out_line2_x, float** out_line2_y, float** out_angle, float** out_type, float** out_score, float** out_pass);
int ERVS_GetFindObjectResultInfo(int base_index, int sub_index, float* out_id, float* out_cx, float* out_cy, float* out_rx, float* out_ry, float* out_angle, float* out_type, float* out_score, float** out_histogram, float** out_histogram_b, float** out_histogram_g, float** out_histogram_r, float* out_histogram_size);
int ERVS_GetDetectData(const int id, float** out_id,
						float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_rz,
						float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry,
						float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry,
						float** out_circle_rx, float** out_circle_ry, float ** out_circle_diameter, float** out_circle_pass,
						float** out_line_distance, float** out_line_distance_pass,
						float** out_line_angle, float** out_line_angle_pass,
						float** out_histogram, float** out_histogram_pass,
						float** out_angle, float** out_type, float** out_score, float** out_tool_type);
int ERVS_SetDetectData_Init(const int id);
int ERVS_GetDetectData_Init(const int id, float** out_id,
						float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_rz,
						float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry,
						float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry,
						float** out_circle_rx, float** out_circle_ry, float ** out_circle_diameter, float** out_circle_pass,
						float** out_line_distance, float** out_line_distance_pass,
						float** out_line_angle, float** out_line_angle_pass,
						float** out_histogram, float** out_histogram_pass,
						float** out_angle, float** out_type, float** out_score, float** out_tool_type);

//[8] Result Geometry & Inspection
int ERVS_Geometry_Get_Distance(const int base_id, const int target_id, float *out_value);
int ERVS_Geometry_Set_Inspection_Distance(const int base_id, const int target_id, const float value);
int ERVS_Geometry_Get_Inspection_Distance(const int base_id, const int target_id, float * out_value);
int ERVS_Geometry_Set_Inspection_Distance_Tolerance_Rate(const int base_id, const int target_id, const float value);
int ERVS_Geometry_Get_Inspection_Distance_Tolerance_Rate(const int base_id, const int target_id, float * out_value);
int ERVS_Geometry_Get_Angle(const int base_id, const int target_id, float *out_value);
int ERVS_Geometry_Set_Inspection_Angle(const int base_id, const int target_id, const float value);
int ERVS_Geometry_Get_Inspection_Angle(const int base_id, const int target_id, float * out_value);
int ERVS_Geometry_Set_Inspection_Angle_Tolerance_Rate(const int base_id, const int target_id, const float value);
int ERVS_Geometry_Get_Inspection_Angle_Tolerance_Rate(const int base_id, const int target_id, float * out_value);
int ERVS_Geometry_Distance(const int base_id, const int target_id, float *out_value, int* out_pass);
int ERVS_Geometry_Angle(const int base_id, const int target_id, float *out_value, int *out_pass);
int ERVS_Geometry_MeetPoint(const int base_id, const int target_id, float *out_value_x, float *out_value_y);
int ERVS_Geometry_Clear(void);

//[9] Check Image
//[9] Check Image : Image Focus Rate
int ERVS_CalcFocusRate(const int id);
int ERVS_SetFocusRate(const int id, const int rate);
int ERVS_GetFocusRate(const int id);
//[9] Check Image : Image Contrast Rate
int ERVS_CalcContrastRate(const int id);
int ERVS_SetContrastRate(const int id, const int rate);
int ERVS_GetContrastRate(const int id);
#endif

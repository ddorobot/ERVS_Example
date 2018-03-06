#ifndef _EYEDEA_API_H_
#define _EYEDEA_API_H_

#include "EyedeaDef.h"
#include <string>

//Server Connect
int ERVS_Connect(char* ip, int port);
void ERVS_Disconnect(void);

//System
char* ERVS_GetVersion(void);
int ERVS_SetNextImage(void);

//Get Image from ERVS to Client
int ERVS_GetImage(int option, int option2, char** data, int* len);
int ERVS_GetFindObjectResultImage(int option, int option2, char** data, int* len);

//Job Management
int ERVS_DBAddObject(void);
int ERVS_DB_Get_Count(void);
int ERVS_DB_Get_Info_Id(int index);
int ERVS_DB_Get_Select_ID(void);
int ERVS_DB_Del_ID(int id);
char* ERVS_DB_Get_Mode(int id);
int ERVS_SetObject(int id = -1);

int ERVS_SetJobName(const int id, const std::string name);
std::string ERVS_GetJobName(const int id);
int ERVS_SetToolName(const int id, const std::string name);
std::string ERVS_GetToolName(const int id);
int ERVS_SetToolType(const int id, const int type);
int ERVS_GetToolType(const int id);
int ERVS_SetToolState(const int id, const int state);
int ERVS_GetToolState(const int id);
int ERVS_SetRobotPose(const int id, double* posj, int posj_size);
double* ERVS_GetRobotPose(const int id, int* posj_size);

//DB Save/Load
int ERVS_FileSaveObjectDBList(std::string path);
int ERVS_FileLoadObjectDBList(std::string path);

//Option
int ERVS_OptionFixAreaOn(void);
int ERVS_OptionFixAreaOff(void);
int ERVS_GetOptionFixArea(void);

//Zoom
int ERVS_SetZoomArea(float x, float y, float w, float h);
int ERVS_ResetZoomArea(void);

//Mask Area
int ERVS_SetMaskArea(float x, float y, float w, float h, bool inverse);
int ERVS_UndoMaskArea(void);
int ERVS_DelMaskArea(void);

//Vision Config Option
int ERVS_SetVisionConfigOption(int option, float value);
float ERVS_GetVisionConfigOption(int option);

//Set Job
int ERVS_SetBase(int dep_id);
//Circle Object
int ERVS_SetObjectCircle(float x, float y, float r1, float r2);
int ERVS_SetObjectCircle(const float x, const float y, const float r1, const float r2, const float min_r1, const float min_r2, const float max_r1, const float max_r2);
int ERVS_SetObjectCircleBaseDiameter(const int id, const int diameter);
int ERVS_GetObjectCircleBaseDiameter(const int id);
int ERVS_SetObjectCircleDiameterTolerance(const int id, const int min_value, const int max_value);
int ERVS_GetObjectCircleDiameterTolerance(const int id, int *out_min_value, int *out_max_value);
int ERVS_SetObjectCircleDiameterInspection(const int id, const bool use);
int ERVS_GetObjectCircleDiameterInspection(const int id);
float ERVS_GetObjectCircleCalcDiameter(const int id);
int ERVS_GetObjectCircle(float *out_x, float *out_y, float *out_r1, float *out_r2);

//Line Object
int ERVS_SetObjectLine(float x, float y, float w, float h);
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

//Region Object
int ERVS_SetSelectBaseObject(float x, float y, float w, float h);

//Detect
int ERVS_DetectWithGrab(int index, int max_objects_count, float** out_id, float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry, float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry, float** out_circle_rx, float** out_circle_ry, float** out_line1_x, float** out_line1_y, float** out_line2_x, float** out_line2_y, float** out_angle, float** out_type, float** out_score, float** out_pass);
int ERVS_DetectWithPrevImage(int index, int max_objects_count, float** out_id, float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry, float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry, float** out_circle_rx, float** out_circle_ry, float** out_line1_x, float** out_line1_y, float** out_line2_x, float** out_line2_y, float** out_angle, float** out_type, float** out_score, float** out_pass);
//Detect Result
int ERVS_GetFindObjectResultInfo(int base_index, int sub_index,float* out_id, float* out_cx, float* out_cy, float* out_rx, float* out_ry, float* out_angle, float* out_type, float* out_score, float** out_histogram, float** out_histogram_b, float** out_histogram_g, float** out_histogram_r, float* out_histogram_size);

//Calibration
int ERVS_Calibration_Add(float robot_x, float robot_y);
int ERVS_Calibration_GetCount(void);
int ERVS_Calibration_GetImage(int index, char** data, int* len);
int ERVS_Calibration_GetRobotInfo(int index, float *out_robot_x, float *out_robot_y);
int ERVS_Calibration_Del(int index);
int ERVS_Calibration_Clear(void);
int ERVS_Calibration_Run(void);
int ERVS_Calibration_GetPoint(const float in_px, const float in_py, float* out_rx, float* out_ry);
int ERVS_Calibration_GetChessPoint(const int index, float* out_rx, float* out_ry);
int ERVS_Calibration_isOK(void);
int ERVS_Calibration_Save(void);
int ERVS_Calibration_Load(void);
int ERVS_Calibration_Copy(const int id);
int ERVS_Calibration_GetID(void);

//Camera Setting
int ERVS_SetCameraConfig(int type, int value, int value2);
int ERVS_GetCameraConfig(int type);
int ERVS_SetCameraConfig_Default();
int ERVS_SetCameraConfig_Save();
int ERVS_SetCameraConfig_Load();

//Background Learning
int ERVS_BackgroundLearning(void);

//Geometry
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

//Histogram 
int ERVS_Histogram_Set_Range(const int id, const int option, const int min_value, const int max_value);
int ERVS_Histogram_Get_Range(const int id, const int option, int *out_min_value, int *out_max_value);
int ERVS_Histogram_Get_Graph(const int id, float** out_histogram, float** out_histogram_b, float** out_histogram_g, float** out_histogram_r, float* out_histogram_size);
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

#endif

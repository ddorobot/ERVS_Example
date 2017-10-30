#include "EyedeaAPI.h"
#include "EyedeaInterface.h"

CEyedeaInterface g_cls_interface;

int ERVS_Connect(char* ip, int port)
{
	return g_cls_interface.CreateSocket(ip, port);
}

void ERVS_Disconnect()
{
	g_cls_interface.DeleteSocket();
}

int ERVS_GetImage(int option, int option2, char** data, int* len)
{
	return g_cls_interface.GetImage(option, option2, data, len);
}

int ERVS_GetFindObjectResultImage(int option, int option2, char** data, int* len)
{
	return g_cls_interface.GetResultImage(option, option2, data, len);
}

int ERVS_SetSelectBaseObject(float x, float y, float w, float h)
{
	//printf("ERVS_SetSelectBaseObject\n");

	return g_cls_interface.SetSelectBaseObject(x, y, w, h);
}

int ERVS_SetZoomArea(float x, float y, float w, float h)
{
	//printf("ERVS_SetSelectBaseObject\n");

	return g_cls_interface.SetZoomArea(x, y, w, h);
}

int ERVS_SetMaskArea(float x, float y, float w, float h, bool inverse)
{
	return g_cls_interface.SetMaskArea(x, y, w, h, inverse);
}

int ERVS_UndoMaskArea(void)
{
	return g_cls_interface.UndoMaskArea();
}

int ERVS_DelMaskArea(void)
{
	return g_cls_interface.DelMaskArea();
}

int ERVS_ResetZoomArea(void)
{
	//printf("ERVS_SetSelectBaseObject\n");

	return g_cls_interface.ResetZoomArea();
}

int ERVS_GetObjectCircle(float *out_x, float *out_y, float *out_r1, float *out_r2)
{
	return g_cls_interface.GetObjectCircle(out_x, out_y, out_r1, out_r2);
}

int ERVS_SetObjectCircle(float x, float y, float r1, float r2)
{
	return g_cls_interface.SetObjectCircle(x, y, r1, r2);
}

int ERVS_SetObjectLine(float x, float y, float w, float h)
{
	return g_cls_interface.SetObjectLine(x, y, w, h);
}

int ERVS_OptionFixAreaOn(void)
{
	return g_cls_interface.OptionFixSearchAreaOn();
}

int ERVS_OptionFixAreaOff(void)
{
	return g_cls_interface.OptionFixSearchAreaOff();
}

int ERVS_GetOptionFixArea(void)
{
	return g_cls_interface.GetOptionFixSearchArea();
}

int ERVS_SetBase(int dep_id)
{
	return g_cls_interface.SetBase(dep_id);
}

int ERVS_SetNextImage(void)
{
	return g_cls_interface.SetNextImage();
}

int ERVS_FileSaveObjectDBList(std::string path)
{
	return g_cls_interface.FileSaveObjectListInfo(path);
}

int ERVS_FileLoadObjectDBList(std::string path)
{
	return g_cls_interface.FileLoadObjectListInfo(path);
}

int ERVS_SetVisionConfigOption(int option, float value)
{
	return g_cls_interface.SetVisionConfigOption(option, value);
}

float ERVS_GetVisionConfigOption(int option)
{
	return g_cls_interface.GetVisionConfigOption(option);
}

int ERVS_DBAddObject(void)
{
	return g_cls_interface.DBAddObject();
}

int ERVS_DB_Get_Count(void)
{
	return g_cls_interface.GetDBCount();
}

int ERVS_DB_Get_Info_Id(int index)
{
	return g_cls_interface.GetDB_Info_Id(index);
}

int ERVS_DB_Get_Select_ID(void)
{
	return g_cls_interface.GetDB_Select_ID();
}

int ERVS_DB_Del_ID(int id)
{
	return g_cls_interface.DB_Del_ID(id);
}

int ERVS_SetObject(int id)
{
	return g_cls_interface.SetObject(id);
}

int ERVS_Calibration_Add(float robot_x, float robot_y)
{
	return g_cls_interface.Calibration_Add(robot_x, robot_y);
}

int ERVS_Calibration_GetCount(void)
{
	return g_cls_interface.Calibration_GetCount();
}

int ERVS_Calibration_GetImage(int index, char** data, int* len)
{
	return g_cls_interface.Calibration_GetImage(index, data, len);
}

int ERVS_Calibration_GetRobotInfo(int index, float *out_robot_x, float *out_robot_y)
{
	return g_cls_interface.Calibration_GetRobotInfo(index, out_robot_x, out_robot_y);
}

int ERVS_Calibration_Del(int index)
{
	return g_cls_interface.Calibration_Del(index);
}

int ERVS_Calibration_Clear(void)
{
	return g_cls_interface.Calibration_Clear();
}

int ERVS_Calibration_Run(void)
{
	return g_cls_interface.Calibration_Run();
}

int ERVS_Calibration_GetPoint(const float in_px, const float in_py, float* out_rx, float* out_ry)
{
	return g_cls_interface.Calibration_GetPoint(in_px, in_py, out_rx, out_ry);
}

int ERVS_Calibration_GetChessPoint(const int index, float* out_rx, float* out_ry)
{
	return g_cls_interface.Calibration_GetChessPoint(index, out_rx, out_ry);
}

int ERVS_Calibration_Copy(const int id)
{
	return g_cls_interface.Calibration_Copy(id);
}

int ERVS_GetFindObjectResultInfo(int base_index, int sub_index, float* out_id, float* out_cx, float* out_cy, float* out_rx, float* out_ry, float* out_angle, float* out_type, float* out_score, float** out_histogram, float** out_histogram_b, float** out_histogram_g, float** out_histogram_r, float* out_histogram_size)
{
	return g_cls_interface.GetFindObjectResultInfo(base_index, sub_index, out_id, out_cx, out_cy, out_rx, out_ry, out_angle, out_type, out_score, out_histogram, out_histogram_b, out_histogram_g, out_histogram_r, out_histogram_size);
}

int ERVS_DetectWithGrab(int index, int max_objects_count, float** out_id, float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry, float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry, float** out_circle_rx, float** out_circle_ry, float** out_line1_x, float** out_line1_y, float** out_line2_x, float** out_line2_y, float** out_angle, float** out_type, float** out_score, float** out_pass)
{
	return g_cls_interface.GetFindObjectInfo(index, max_objects_count, 0/*grab*/, out_id, out_cx, out_cy, out_rx, out_ry, out_bound_cx, out_bound_cy, out_bound_rx, out_bound_ry, out_mass_cx, out_mass_cy, out_mass_rx, out_mass_ry, out_circle_rx, out_circle_ry, out_line1_x, out_line1_y, out_line2_x, out_line2_y, out_angle, out_type, out_score, out_pass);
}

int ERVS_DetectWithPrevImage(int index, int max_objects_count, float** out_id, float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry, float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry, float** out_circle_rx, float** out_circle_ry, float** out_line1_x, float** out_line1_y, float** out_line2_x, float** out_line2_y, float** out_angle, float** out_type, float** out_score, float** out_pass)
{
	return g_cls_interface.GetFindObjectInfo(index, max_objects_count, 1/*prev*/, out_id, out_cx, out_cy, out_rx, out_ry, out_bound_cx, out_bound_cy, out_bound_rx, out_bound_ry, out_mass_cx, out_mass_cy, out_mass_rx, out_mass_ry, out_circle_rx, out_circle_ry, out_line1_x, out_line1_y, out_line2_x, out_line2_y, out_angle, out_type, out_score, out_pass);
}

int ERVS_Calibration_isOK(void)
{
	return g_cls_interface.Calibration_isOK();
}

int ERVS_Calibration_GetID(void)
{
	return g_cls_interface.Calibration_GetID();
}

char* ERVS_GetVersion(void)
{
	return g_cls_interface.GetVersion();
}

char* ERVS_DB_Get_Mode(int id)
{
	return g_cls_interface.DB_Get_Mode(id);
}

int ERVS_Calibration_Save(void)
{
	return g_cls_interface.Calibration_Save();
}

int ERVS_Calibration_Load(void)
{
	return g_cls_interface.Calibration_Load();
}

int ERVS_SetCameraConfig(int type, int value, int value2)
{
	return g_cls_interface.SetCameraConfig(type,value,value2);
}

int ERVS_GetCameraConfig(int type)
{
	return g_cls_interface.GetCameraConfig(type);
}

int ERVS_SetCameraConfig_Default()
{
	return g_cls_interface.SetCameraConfig_Default();
}

int ERVS_SetCameraConfig_Save()
{
	return g_cls_interface.SetCameraConfig_Save();
}

int ERVS_SetCameraConfig_Load()
{
	return g_cls_interface.SetCameraConfig_Load();
}

//Background Learning
int ERVS_BackgroundLearning(void)
{
	return g_cls_interface.BackgroundLearning();
}

//Geometry
int ERVS_Geometry_Get_Distance(const int base_id, const int target_id, float *out_value)
{
	return g_cls_interface.Geometry_Get_Distance(base_id, target_id, out_value);
}

int ERVS_Geometry_Set_Inspection_Distance(const int base_id, const int target_id, const float value)
{
	return g_cls_interface.Geometry_Set_Inspection_Distance(base_id, target_id, value);
}

int ERVS_Geometry_Get_Inspection_Distance(const int base_id, const int target_id, float * out_value)
{
	return g_cls_interface.Geometry_Get_Inspection_Distance(base_id, target_id, out_value);
}

int ERVS_Geometry_Set_Inspection_Distance_Tolerance_Rate(const int base_id, const int target_id, const float value)
{
	return g_cls_interface.Geometry_Set_Inspection_Distance_Tolerance_Rate(base_id, target_id, value);
}

int ERVS_Geometry_Get_Inspection_Distance_Tolerance_Rate(const int base_id, const int target_id, float * out_value)
{
	return g_cls_interface.Geometry_Get_Inspection_Distance_Tolerance_Rate(base_id, target_id, out_value);
}

int ERVS_Geometry_Get_Angle(const int base_id, const int target_id, float *out_value)
{
	return g_cls_interface.Geometry_Get_Angle(base_id, target_id, out_value);
}

int ERVS_Geometry_Set_Inspection_Angle(const int base_id, const int target_id, const float value)
{
	return g_cls_interface.Geometry_Set_Inspection_Angle(base_id, target_id, value);
}

int ERVS_Geometry_Get_Inspection_Angle(const int base_id, const int target_id, float * out_value)
{
	return g_cls_interface.Geometry_Get_Inspection_Angle(base_id, target_id, out_value);
}

int ERVS_Geometry_Set_Inspection_Angle_Tolerance_Rate(const int base_id, const int target_id, const float value)
{
	return g_cls_interface.Geometry_Set_Inspection_Angle_Tolerance_Rate(base_id, target_id, value);
}

int ERVS_Geometry_Get_Inspection_Angle_Tolerance_Rate(const int base_id, const int target_id, float * out_value)
{
	return g_cls_interface.Geometry_Get_Inspection_Angle_Tolerance_Rate(base_id, target_id, out_value);
}

int ERVS_Geometry_Distance(const int base_id, const int target_id, float *out_value, int* out_pass)
{
	return g_cls_interface.Geometry_Distance(base_id, target_id, out_value, out_pass);
}

int ERVS_Geometry_MeetPoint(const int base_id, const int target_id, float *out_value_x, float *out_value_y)
{
	return g_cls_interface.Geometry_MeetPoint(base_id, target_id, out_value_x, out_value_y);
}

int ERVS_Geometry_Angle(const int base_id, const int target_id, float *out_value, int *out_pass)
{
	return g_cls_interface.Geometry_Angle(base_id, target_id, out_value, out_pass);
}

int ERVS_Geometry_Clear(void)
{
	return g_cls_interface.Geometry_Clear();
}

int ERVS_Histogram_Set_Range(const int id, const int option, const int min_value, const int max_value)
{
	return g_cls_interface.Histogram_Set_Range(id, option, min_value, max_value);
}

int ERVS_Histogram_Get_Range(const int id, const int option, int *out_min_value, int *out_max_value)
{
	return g_cls_interface.Histogram_Get_Range(id, option, out_min_value, out_max_value);
}

int ERVS_Histogram_Get_Graph(const int id, float** out_histogram, float** out_histogram_b, float** out_histogram_g, float** out_histogram_r, float* out_histogram_size)
{
	return g_cls_interface.Histogram_Get_Graph(id, out_histogram, out_histogram_b, out_histogram_g, out_histogram_r, out_histogram_size);
}

int ERVS_Histogram_Set_Use_Element(const int id, const int option)
{
	return g_cls_interface.Histogram_Set_Use_Element(id, option);
}

int ERVS_Histogram_Get_Use_Element(const int id, int *out_option)
{
	return g_cls_interface.Histogram_Get_Use_Element(id, out_option);
}

int ERVS_Histogram_Get_Pixel_Count(const int index1, const int index2, int *out_count)
{
	return g_cls_interface.Histogram_Get_Pixel_Count(index1, index2, out_count);
}

int ERVS_Histogram_Get_Pixel_Count(const int id, int *out_count)
{
	return g_cls_interface.Histogram_Get_Pixel_Count(id, out_count);
}

int ERVS_Histogram_Set_Inspection_Pixel_Count(const int id, const int count)
{
	return g_cls_interface.Histogram_Set_Inspection_Pixel_Count(id, count);
}

int ERVS_Histogram_Get_Inspection_Pixel_Count(const int id, int *out_count)
{
	return g_cls_interface.Histogram_Get_Inspection_Pixel_Count(id, out_count);
}

int ERVS_Histogram_Set_Inspection_Pixel_Count_Tolerance_Rate(const int id, const float rate)
{
	return g_cls_interface.Histogram_Set_Inspection_Pixel_Count_Tolerance_Rate(id, rate);
}

int ERVS_Histogram_Get_Inspection_Pixel_Count_Tolerance_Rate(const int id, float *out_rate)
{
	return g_cls_interface.Histogram_Get_Inspection_Pixel_Count_Tolerance_Rate(id, out_rate);
}
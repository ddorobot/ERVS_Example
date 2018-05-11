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

int ERVS_GetSelectBaseObject(float *out_x, float *out_y, float *out_w, float *out_h, float *out_roi_center_x, float *out_roi_center_y, float *out_bound_center_x, float *out_bound_center_y, float *out_mass_center_x, float *out_mass_center_y)
{
	return g_cls_interface.GetSelectBaseObject(out_x, out_y, out_w, out_h, out_roi_center_x, out_roi_center_y, out_bound_center_x, out_bound_center_y, out_mass_center_x, out_mass_center_y);
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

int ERVS_GetMaskArea(int *out_count, float **out_x, float **out_y, float **out_w, float **out_h, bool **out_inverse)
{
	return g_cls_interface.GetMaskArea(out_count, out_x, out_y, out_w, out_h, out_inverse);
}

int ERVS_ResetZoomArea(void)
{
	//printf("ERVS_SetSelectBaseObject\n");

	return g_cls_interface.ResetZoomArea();
}

int ERVS_SetObjectCircle(float x, float y, float r1, float r2)
{
	return g_cls_interface.SetObjectCircle(x, y, r1, r2);
}

int ERVS_SetObjectCircle(const float x, const float y, const float r1, const float r2, const float min_r1, const float min_r2, const float max_r1, const float max_r2)
{
	return g_cls_interface.SetObjectCircle(x, y, r1, r2, min_r1, min_r2, max_r1, max_r2);
}

int ERVS_GetObjectCircle(float *out_x, float *out_y, float *out_r1, float *out_r2, float *out_min_r1, float *out_min_r2, float *out_max_r1, float *out_max_r2)
{
	return g_cls_interface.GetObjectCircle(out_x, out_y, out_r1, out_r2, out_min_r1, out_min_r2, out_max_r1, out_max_r2);
}

int ERVS_SetObjectLine(float x, float y, float w, float h)
{
	return g_cls_interface.SetObjectLine(x, y, w, h);
}

int ERVS_SetObjectLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	return g_cls_interface.SetObjectLine(x1, y1, x2, y2, x3, y3, x4, y4);
}

int ERVS_GetObjectLine(int *out_count, float **out_x1, float **out_y1, float **out_x2, float **out_y2, float **out_x3, float **out_y3, float **out_x4, float **out_y4, float **out_line1_x, float **out_line1_y, float **out_line2_x, float **out_line2_y)
{
	return g_cls_interface.GetObjectLine(out_count, out_x1, out_y1, out_x2, out_y2, out_x3, out_y3, out_x4, out_y4, out_line1_x, out_line1_y, out_line2_x, out_line2_y);
}

int ERVS_DelObjectLine(void)
{
	return g_cls_interface.DeleteObjectLine();
}

int ERVS_ClrObjectLine(void)
{
	return g_cls_interface.ClearObjectLine();
}

int ERVS_SetObjectTwoLine(const int id, float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	return g_cls_interface.SetObjectTwoLine(id, x1, y1, w1, h1, x2, y2, w2, h2);
}

int ERVS_SetObjectTwoLineBaseDistance(const int id, const int dist)
{
	return g_cls_interface.SetObjectTwoLineBaseDistance(id, dist);
}

int ERVS_GetObjectTwoLineBaseDistance(const int id)
{
	return g_cls_interface.GetObjectTwoLineBaseDistance(id);
}

int ERVS_GetObjectCircleBaseDiameter(const int id)
{
	return g_cls_interface.GetObjectCircleBaseDiameter(id);
}

int ERVS_SetObjectTwoLineBaseAngle(const int id, const int angle)
{
	return g_cls_interface.SetObjectTwoLineBaseAngle(id, angle);
}

int ERVS_SetObjectCircleBaseDiameter(const int id, const int diameter)
{
	return g_cls_interface.SetObjectCircleBaseDiameter(id, diameter);
}

int ERVS_GetObjectTwoLineBaseAngle(const int id)
{
	return g_cls_interface.GetObjectTwoLineBaseAngle(id);
}

float ERVS_GetObjectTwoLineCalcDistance(const int id)
{
	return g_cls_interface.GetObjectTwoLineCalcDistance(id);
}

float ERVS_GetObjectTwoLineCalcAngle(const int id)
{
	return g_cls_interface.GetObjectTwoLineCalcAngle(id);
}

float ERVS_GetObjectCircleCalcDiameter(const int id)
{
	return g_cls_interface.GetObjectCircleCalcDiameter(id);
}

int ERVS_SetObjectTwoLineDistanceTolerance(const int id, const int min_value, const int max_value)
{
	return g_cls_interface.SetObjectTwoLineDistanceTolerance(id, min_value, max_value);
}

int ERVS_GetObjectTwoLineDistanceTolerance(const int id, int *out_min_value, int *out_max_value)
{
	return g_cls_interface.GetObjectTwoLineDistanceTolerance(id, out_min_value, out_max_value);
}

int ERVS_SetObjectTwoLineAngleTolerance(const int id, const int min_value, const int max_value)
{
	return g_cls_interface.SetObjectTwoLineAngleTolerance(id, min_value, max_value);
}

int ERVS_GetObjectTwoLineAngleTolerance(const int id, int *out_min_value, int *out_max_value)
{
	return g_cls_interface.GetObjectTwoLineAngleTolerance(id, out_min_value, out_max_value);
}

int ERVS_SetObjectCircleDiameterTolerance(const int id, const int min_value, const int max_value)
{
	return g_cls_interface.SetObjectCircleDiameterTolerance(id, min_value, max_value);
}

int ERVS_GetObjectCircleDiameterTolerance(const int id, int *out_min_value, int *out_max_value)
{
	return g_cls_interface.GetObjectCircleDiameterTolerance(id, out_min_value, out_max_value);
}

int ERVS_SetObjectTwoLineDistanceType(const int id, const int type)
{
	return g_cls_interface.SetObjectTwoLineDistanceType(id, type);
}

int ERVS_GetObjectTwoLineDistanceType(const int id)
{
	return g_cls_interface.GetObjectTwoLineDistanceType(id);
}

int ERVS_SetObjectTwoLineDistanceInspection(const int id, const bool use)
{
	return g_cls_interface.SetObjectTwoLineDistanceInspection(id, use);
}

int ERVS_GetObjectTwoLineDistanceInspection(const int id)
{
	return g_cls_interface.GetObjectTwoLineDistanceInspection(id);
}

int ERVS_SetObjectTwoLineAngleInspection(const int id, const bool use)
{
	return g_cls_interface.SetObjectTwoLineAngleInspection(id, use);
}

int ERVS_GetObjectTwoLineAngleInspection(const int id)
{
	return g_cls_interface.GetObjectTwoLineAngleInspection(id);
}

int ERVS_SetObjectCircleDiameterInspection(const int id, const bool use)
{
	return g_cls_interface.SetObjectCircleDiameterInspection(id, use);
}

int ERVS_GetObjectCircleDiameterInspection(const int id)
{
	return g_cls_interface.GetObjectCircleDiameterInspection(id);
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

int ERVS_SetJobName(const int id, const std::string name)
{
	return g_cls_interface.SetJobName(id, name);
}

std::string ERVS_GetJobName(const int id)
{
	return g_cls_interface.GetJobName(id);
}

int ERVS_SetToolName(const int id, const std::string name)
{
	return g_cls_interface.SetToolName(id, name);
}

std::string ERVS_GetToolName(const int id)
{
	return g_cls_interface.GetToolName(id);
}

int ERVS_SetToolType(const int id, const int type)
{
	return g_cls_interface.SetToolType(id, type);
}

int ERVS_GetToolType(const int id)
{
	return g_cls_interface.GetToolType(id);
}

int ERVS_SetToolState(const int id, const int state)
{
	return g_cls_interface.SetToolState(id, state);
}

int ERVS_GetToolState(const int id)
{
	return g_cls_interface.GetToolState(id);
}

int ERVS_SetRobotPose(const int id, double* posj, int posj_size)
{
	return g_cls_interface.SetRobotPose(id, posj, posj_size);
}

double* ERVS_GetRobotPose(const int id, int* posj_size)
{
	return g_cls_interface.GetRobotPose(id, posj_size);
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

int ERVS_Calibration_StandAlone_Run(void)
{
	return g_cls_interface.Calibration_StandAlone_Run();
}

int ERVS_Calibration_StandAlone_Get_Feature_Pos(int index,float posA[3], float posB[3], float posC[3], float posD[3])
{
	return g_cls_interface.Calibration_StandAlone_Get_Feature_Pos(index,posA, posB, posC, posD);
}

int ERVS_Calibration_StandAlone_Set_Matrix(float matrix[12])
{
	return g_cls_interface.Calibration_StandAlone_Set_Matrix(matrix);	
}
int ERVS_Calibration_StandAlone_Get_Matrix(float matrix[12])
{
	return g_cls_interface.Calibration_StandAlone_Get_Matrix(matrix);
}

int ERVS_Calibration_StandAlone_Calc_Calib_Matrix(float cposA[3], float cposB[3], float cposC[3], float cposD[3],
	float rposA[3], float rposB[3], float rposC[3], float rposD[3],
	float ret_Matrix[12])
{
	return g_cls_interface.Calibration_StandAlone_Calc_Calib_Matrix(cposA, cposB, cposC, cposD, rposA, rposB, rposC, rposD, ret_Matrix);
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
	int base_id = index / 1000;
	base_id *= 1000;

	int retry = 0;
	if (base_id >= 1000)
	{
		retry = ERVS_GetDetectRetry(base_id);
	}

	int ret = 0;
	int run_count = 0;
	do
	{
		ret = g_cls_interface.GetFindObjectInfo(index, max_objects_count, 0/*grab*/, out_id, out_cx, out_cy, out_rx, out_ry, out_bound_cx, out_bound_cy, out_bound_rx, out_bound_ry, out_mass_cx, out_mass_cy, out_mass_rx, out_mass_ry, out_circle_rx, out_circle_ry, out_line1_x, out_line1_y, out_line2_x, out_line2_y, out_angle, out_type, out_score, out_pass);

		run_count++;

		if (retry>0)
		{
			if (ret == 0)
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
			}
		}
	} while (retry > run_count);

	return ret;
}

int ERVS_DetectWithGrab(int index, int max_objects_count, float** out_id,
	float** out_cx, float** out_cy, float** out_rx, float** out_ry,
	float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry,
	float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry,
	float** out_circle_rx, float** out_circle_ry, float ** out_circle_diameter, float** out_circle_pass,
	float** out_line_distance, float** out_line_distance_pass,
	float** out_line_angle, float** out_line_angle_pass,
	float** out_histogram, float** out_histogram_pass,
	float** out_angle, float** out_type, float** out_score, float** out_tool_type)
{
	int base_id = index / 1000;
	base_id *= 1000;

	int retry = 0;
	if (base_id >= 1000)
	{
		retry = ERVS_GetDetectRetry(base_id);
	}

	int ret = 0;
	int run_count = 0;
	do
	{
		ret = g_cls_interface.GetFindObjectInfo(index, max_objects_count, 0/*grab*/, out_id, out_cx, out_cy, out_rx, out_ry, out_bound_cx, out_bound_cy, out_bound_rx, out_bound_ry, out_mass_cx, out_mass_cy, out_mass_rx, out_mass_ry, out_circle_rx, out_circle_ry, out_circle_diameter, out_circle_pass, out_line_distance, out_line_distance_pass, out_line_angle, out_line_angle_pass, out_histogram, out_histogram_pass, out_angle, out_type, out_score, out_tool_type);

		run_count++;

		if (retry > 0)
		{
			if (ret == 0)
			{
				boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
			}
		}
	} while (retry > run_count);

	return ret;
}

int ERVS_GetDetectData(const int id, float** out_id,
	float** out_cx, float** out_cy, float** out_rx, float** out_ry,
	float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry,
	float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry,
	float** out_circle_rx, float** out_circle_ry, float ** out_circle_diameter, float** out_circle_pass,
	float** out_line_distance, float** out_line_distance_pass,
	float** out_line_angle, float** out_line_angle_pass,
	float** out_histogram, float** out_histogram_pass,
	float** out_angle, float** out_type, float** out_score, float** out_tool_type)
{
	return g_cls_interface.GetDetectData(id, out_id, out_cx, out_cy, out_rx, out_ry, out_bound_cx, out_bound_cy, out_bound_rx, out_bound_ry, out_mass_cx, out_mass_cy, out_mass_rx, out_mass_ry, out_circle_rx, out_circle_ry, out_circle_diameter, out_circle_pass, out_line_distance, out_line_distance_pass, out_line_angle, out_line_angle_pass, out_histogram, out_histogram_pass, out_angle, out_type, out_score, out_tool_type);
}

int ERVS_GetDetectData_Init(const int id, float** out_id,
	float** out_cx, float** out_cy, float** out_rx, float** out_ry,
	float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry,
	float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry,
	float** out_circle_rx, float** out_circle_ry, float ** out_circle_diameter, float** out_circle_pass,
	float** out_line_distance, float** out_line_distance_pass,
	float** out_line_angle, float** out_line_angle_pass,
	float** out_histogram, float** out_histogram_pass,
	float** out_angle, float** out_type, float** out_score, float** out_tool_type)
{
	return g_cls_interface.GetDetectData_Init(id, out_id, out_cx, out_cy, out_rx, out_ry, out_bound_cx, out_bound_cy, out_bound_rx, out_bound_ry, out_mass_cx, out_mass_cy, out_mass_rx, out_mass_ry, out_circle_rx, out_circle_ry, out_circle_diameter, out_circle_pass, out_line_distance, out_line_distance_pass, out_line_angle, out_line_angle_pass, out_histogram, out_histogram_pass, out_angle, out_type, out_score, out_tool_type);
}

int ERVS_SetDetectData_Init(const int id)
{
	return g_cls_interface.SetDetectData_Init(id);
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

int ERVS_SetCameraConfig_Save_With_ID(int ConfigID)
{
	return g_cls_interface.SetCameraConfig_Save_With_ID(ConfigID);
}
int ERVS_SetCameraConfig_Load_With_ID(int ConfigID)
{
	return g_cls_interface.SetCameraConfig_Load_With_ID(ConfigID);
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

int ERVS_Histogram_Set_Inspection_Pixel_Count_Tolerance(const int id, const int min_value, const int max_value)
{
	return g_cls_interface.Histogram_Set_Inspection_Pixel_Count_Tolerance(id, min_value, max_value);
}

int ERVS_Histogram_Get_Inspection_Pixel_Count_Tolerance(const int id, int *out_min_value, int *out_max_value)
{
	return g_cls_interface.Histogram_Get_Inspection_Pixel_Count_Tolerance(id, out_min_value, out_max_value);
}

int ERVS_Histogram_Set_Inspection(const int id, const bool use)
{
	int bak_id = ERVS_DB_Get_Select_ID();

	ERVS_SetObject(id);

	ERVS_SetVisionConfigOption(VISION_CONFIG_USE_HISTOGRAM, (int)use);

	return ERVS_SetObject(bak_id);
}

int ERVS_Histogram_Get_Inspection(const int id)
{
	int bak_id = ERVS_DB_Get_Select_ID();

	ERVS_SetObject(id);

	float use_histogram = ERVS_GetVisionConfigOption(VISION_CONFIG_USE_HISTOGRAM);

	ERVS_SetObject(bak_id);

	if (use_histogram)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int ERVS_CalcFocusRate(const int id)
{
	return g_cls_interface.CalcFocusRate(id);
}

int ERVS_SetFocusRate(const int id, const int rate)
{
	return g_cls_interface.SetFocusRate(id, rate);
}

int ERVS_GetFocusRate(const int id)
{
	return g_cls_interface.GetFocusRate(id);
}

int ERVS_CalcContrastRate(const int id)
{
	return g_cls_interface.CalcContrastRate(id);
}

int ERVS_SetContrastRate(const int id, const int rate)
{
	return g_cls_interface.SetContrastRate(id, rate);
}

int ERVS_GetContrastRate(const int id)
{
	return g_cls_interface.GetContrastRate(id);
}

int ERVS_SetDetectRetry(const int id, int nRetryCount)
{
	int bak_id = ERVS_DB_Get_Select_ID();

	ERVS_SetObject(id);

	int ret = ERVS_SetVisionConfigOption(VISION_CONFIG_DETECT_RETRY, nRetryCount);

	ERVS_SetObject(bak_id);

	return 0;
}

int ERVS_GetDetectRetry(const int id)
{
	int bak_id = ERVS_DB_Get_Select_ID();

	ERVS_SetObject(id);

	float value = ERVS_GetVisionConfigOption(VISION_CONFIG_DETECT_RETRY);

	ERVS_SetObject(bak_id);

	int retry = (int)value;

	return retry;
}
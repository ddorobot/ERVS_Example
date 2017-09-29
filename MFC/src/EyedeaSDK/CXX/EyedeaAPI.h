#ifndef _EYEDEA_API_H_
#define _EYEDEA_API_H_

#include "EyedeaDef.h"
#include <string>

//Server Connect
int ERVS_Connect(char* ip, int port);
void ERVS_Disconnect(void);

int ERVS_SetMode(int option);
int ERVS_GetMode(void);

//Get Image from ERVS to Client
int ERVS_GetImage(int option, int option2, char** data, int* len);
int ERVS_GetFindObjectResultImage(int option, int option2, char** data, int* len);

int ERVS_GetImage(char** data, int* len);
int ERVS_GetObjectImage(char** data, int* len);
int ERVS_GetZoomImage(char** data, int* len);
int ERVS_GetBaseImage(char** data, int* len);
int ERVS_GetResultImage(char** data, int* len);
int ERVS_GetResultImageGlobal(char** data, int* len);
int ERVS_GetResultImageLocal(char** data, int* len, int id = -1);
int ERVS_GetImageWithUserArea(char** data, int* len);

//Option
int ERVS_SetOptionPCAOn(void);
int ERVS_SetOptionPCAOff(void);
int ERVS_GetOptionPCA(void);
int ERVS_SetOptionFindWithCheckDefectOn(void);
int ERVS_SetOptionFindWithCheckDefectOff(void);
int ERVS_GetOptionFindWithCheckDefect(void);
int ERVS_OptionFixAreaOn(void);
int ERVS_OptionFixAreaOff(void);
int ERVS_GetOptionFixArea(void);
int ERVS_OptionFixSearchUserRoiOn(void);
int ERVS_OptionFixSearchUserRoiOff(void);
int ERVS_GetOptionFixSearchUserRoi(void);
unsigned int ERVS_GetNewID(void);
int ERVS_SetZoomArea(float x, float y, float w, float h);
int ERVS_ResetZoomArea(void);

//Vision Config Option
int ERVS_SetVisionConfigOption(int option, float value);
float ERVS_GetVisionConfigOption(int option);
int ERVS_ApplyAndMakeBaseGlobalInfo(void);
int ERVS_ApplyAndMakeBaseLocalInfo(void);
int ERVS_ApplyAndMakeSearchAreaLocalInfo(void);

//Check Defection API
int ERVS_FindObject(int id = -1);
int ERVS_FindObjectWithoutPCA(int id = -1);
int ERVS_CheckDefect(float threshold);
int ERVS_CheckDefectUserOption(bool checkoption1, float optionscore1, bool checkoption2, float optionscore2, int OptionAndOr);
int ERVS_CheckDefectList(int id);
int ERVS_SetCheckDefectDBList(int id, bool fixarea, bool checkoption1, float optionscore1, bool checkoption2, float optionscore2, int OptionAndOr);
unsigned int ERVS_GetCheckDefectDBListNum(void);
int ERVS_GetCheckDefectDBList(const int index, bool *fixarea, int *id, bool *checkoption1, float *optionscore1, bool *checkoption2, float *optionscore2, int *OptionAndOr);
int ERVS_DelCheckDefectDBList(int id);
int ERVS_FileSaveCheckDefectDBList(void);
int ERVS_FileLoadCheckDefectDBList(void);

//Object(Circle) Detection API
int ERVS_FindObjectWithPCA(void);
int ERVS_FindAllObject(void);
int ERVS_SetObjectDBList(int id=-1);
unsigned int ERVS_GetObjectDBListNum(void);
int ERVS_GetObjectDBList(const int index, int *id, int *type);
int ERVS_DelObjectDBList(int id);
int ERVS_FileSaveObjectDBList(std::string path);
int ERVS_FileLoadObjectDBList(std::string path);
int ERVS_GetResultCircleInfoCameraBase(float* out_x, float* out_y, float* out_r, int id = -1);
int ERVS_GetResultCircleInfoRobotBase(float* out_x, float* out_y, float* out_r, int id = -1);
int ERVS_GetResultCircleInfoImageBase(float* out_x, float* out_y, float* out_r, int id = -1);
int ERVS_GetMainObjectInfo(float* out_x, float* out_y, float* out_a);
int ERVS_SetObjectCircle(float x, float y, float r1, float r2);
int ERVS_SetObjectLine(float x, float y, float w, float h);
int ERVS_GetObjectCircle(float *out_x, float *out_y, float *out_r1, float *out_r2);
int ERVS_SetSelectROI(float x, float y, int width=-1, int height=-1);
int ERVS_GetSelectROI(float *out_x, float *out_y, int *out_width, int *out_height);

int ERVS_GetResultFindSearchAreaCameraBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle);
int ERVS_GetResultFindSearchAreaRobotBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle);
int ERVS_GetResultFindSearchAreaImageBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle);
int ERVS_GetResultFindMasterAreaCameraBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle);
int ERVS_GetResultFindMasterAreaRobotBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle);
int ERVS_GetResultFindMasterAreaImageBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle);
float ERVS_GetResultFindScale(void);
float ERVS_GetResultFindScore(void);

int ERVS_SetMode(int option);
int ERVS_GetMode(void);

int ERVS_ResetObject(void);
int ERVS_DBAddObject(void);
int ERVS_DB_Get_Count(void);
int ERVS_DB_Get_Info_Id(int index);
int ERVS_DB_Get_Select_ID(void);
int ERVS_DB_Del_ID(int id);
char* ERVS_DB_Get_Mode(int id);

int ERVS_SetObject(int id = -1);
int ERVS_DBAddSubObject(int id);
int ERVS_GetSubObjectCount(int id);
int ERVS_GetFindObjectCount(void);
int ERVS_GetFindObjectInfo(int index, int max_objects_count, float** out_id, float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry, float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry, float** out_circle_rx, float** out_circle_ry, float** out_line1_x, float** out_line1_y, float** out_line2_x, float** out_line2_y, float** out_angle, float** out_type, float** out_score);
int ERVS_DetectWithGrab(int index, int max_objects_count, float** out_id, float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry, float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry, float** out_circle_rx, float** out_circle_ry, float** out_line1_x, float** out_line1_y, float** out_line2_x, float** out_line2_y, float** out_angle, float** out_type, float** out_score);
int ERVS_DetectWithPrevImage(int index, int max_objects_count, float** out_id, float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry, float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry, float** out_circle_rx, float** out_circle_ry, float** out_line1_x, float** out_line1_y, float** out_line2_x, float** out_line2_y, float** out_angle, float** out_type, float** out_score);
int ERVS_GetFindObjectResultInfo(int base_index, int sub_index,float* out_id, float* out_cx, float* out_cy, float* out_rx, float* out_ry, float* out_angle, float* out_type, float* out_score, float** out_histogram, float** out_histogram_b, float** out_histogram_g, float** out_histogram_r, float* out_histogram_size);
int ERVS_GetFindObjectInfo2(int index, float* out_cx, float* out_cy, float* out_rx, float* out_ry, float* out_angle, float* out_type, float* out_score);
int ERVS_GetFindObjectPose(int index, float* out_cx, float* out_cy, float* out_rx, float* out_ry, float* out_angle);
int ERVS_GetFindObjectImage(int index, char** data, int* len);

unsigned int ERVS_GetSubObjectID(int host_id, int index);
int ERVS_GetSubObjectSearchAreaByIdIndex(const int host_id, const int index, float* out_search_area_x, float* out_search_area_y, float* out_search_area_w, float* out_search_area_h);
int ERVS_GetSubObjectSearchAreaByIdId(const int host_id, const int sub_id, float* out_search_area_x, float* out_search_area_y, float* out_search_area_w, float* out_search_area_h);
int ERVS_GetSubObjectMasterAreaByIdIndex(const int host_id, const int index, float* out_master_area_x, float* out_master_area_y, float* out_master_area_w, float* out_master_area_h);
int ERVS_GetSubObjectMasterAreaByIdId(const int host_id, const int sub_id, float* out_master_area_x, float* out_master_area_y, float* out_master_area_w, float* out_master_area_h);
int ERVS_GetSubObjectUseInspectionByIdIndex(const int host_id, const int index);
int ERVS_GetSubObjectUseInspectionByIdId(const int host_id, const int sub_id);
int ERVS_GetSubObjectCircleByIdIndex(const int host_id, const int index, float* out_circle_x, float* out_circle_y, float* out_circle_rx, float* out_circle_ry);
int ERVS_GetSubObjectCircleByIdId(const int host_id, const int sub_id, float* out_circle_x, float* out_circle_y, float* out_circle_rx, float* out_circle_ry);

//Search Area
int ERVS_GetSearchArea(float* out_x, float* out_y, float* out_w, float* out_h);
int ERVS_SetSearchArea(float x, float y, float w, float h);
int ERVS_SetSearchAreaColor(int r, int g, int b);
int ERVS_GetSearchAreaColor(int* out_r, int* out_g, int* out_b);
int ERVS_SetSearchAreaWidth(int width);
int ERVS_GetSearchAreaWidth(void);
int ERVS_GetMasterArea(float* out_x, float* out_y, float* out_w, float* out_h);
int ERVS_SetMasterArea(float x, float y, float w, float h);
int ERVS_SetMasterAreaColor(int r, int g, int b);
int ERVS_GetMasterAreaColor(int* out_r, int* out_g, int* out_b);
int ERVS_SetMasterAreaWidth(int width);
int ERVS_GetMasterAreaWidth(void);
int ERVS_SetSelectBaseObject(float x, float y, float w, float h);
int ERVS_FindSearchArea(int level);

//Set Display
int ERVS_SetObjectColor(int object, int r, int g, int b);
int ERVS_GetObjectColor(int object, int* out_r, int* out_g, int* out_b);
int ERVS_SetObjectWidth(int object, int width);
int ERVS_GetObjectWidth(int object);
int ERVS_GetObjectFeatureUse(void);
int ERVS_GetObjectFeatureColor(int* out_r, int* out_g, int* out_b);
int ERVS_GetObjectFeatureWidth(void);
int ERVS_SetObjectFeatureUse(int use);
int ERVS_SetObjectFeatureColor(int r, int g, int b);
int ERVS_SetObjectFeatureWidth(int width);
int ERVS_GetObjectOutlineUse(void);
int ERVS_GetObjectOutlineColor(int* out_r, int* out_g, int* out_b);
int ERVS_GetObjectOutlineWidth(void);
int ERVS_SetObjectOutlineUse(int use);
int ERVS_SetObjectOutlineColor(int r, int g, int b);
int ERVS_SetObjectOutlineWidth(int width);
///
int ERVS_GetObjectRectUse(void);
int ERVS_GetObjectRectColor(int* out_r, int* out_g, int* out_b);
int ERVS_GetObjectRectWidth(void);
int ERVS_SetObjectRectUse(int use);
int ERVS_SetObjectRectColor(int r, int g, int b);
int ERVS_SetObjectRectWidth(int width);
///
int ERVS_GetObjectCenterUse(void);
int ERVS_GetObjectCenterColor(int* out_r, int* out_g, int* out_b);
int ERVS_GetObjectCenterWidth(void);
int ERVS_SetObjectCenterUse(int use);
int ERVS_SetObjectCenterColor(int r, int g, int b);
int ERVS_SetObjectCenterWidth(int width);
///
int ERVS_GetObjectAngleUse(void);
int ERVS_GetObjectAngleColor(int* out_r, int* out_g, int* out_b);
int ERVS_GetObjectAngleWidth(void);
int ERVS_SetObjectAngleUse(int use);
int ERVS_SetObjectAngleColor(int r, int g, int b);
int ERVS_SetObjectAngleWidth(int width);

//Base
int ERVS_SetBase(int dep_id);
int ERVS_SetNextImage(void);
int ERVS_SaveInformation(void);
int ERVS_LoadInformation(void);
float ERVS_GetBaseInfo(int option);


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

int ERVS_SetLog(int logoption);

int ERVS_VisionConfigFileSave(void);
int ERVS_VisionConfigFileLoad(void);

char* ERVS_GetVersion(void);

//Camera Setting
int ERVS_SetCameraConfig(int type, int value, int value2);

//Background Learning
int ERVS_BackgroundLearning(void);

//Geometry
int ERVS_Geometry_Distance(const int base_id, const int target_id, const float base_info, const float tol, float *out_value);
int ERVS_Geometry_Angle(const int base_id, const int target_id, const float base_info, const float tol, float *out_value);

#endif

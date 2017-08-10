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


#if 0
void ERVS_Connect(char* ip, char* port)
{
	g_cls_interface.Connect(ip, port);
}
#endif

int ERVS_SetObjectDBList(int id)
{
	return g_cls_interface.SetObjectInformation(id);
}

int ERVS_GetImage(char** data, int* len)
{
	return g_cls_interface.GetImage(data, len);	
}

int ERVS_GetObjectImage(char** data, int* len)
{
	return g_cls_interface.GetObjectImage(data, len);
}

int ERVS_GetFindObjectImage(int index, char** data, int* len)
{
	return g_cls_interface.GetFindObjectImage(index, data, len);
}

int ERVS_GetZoomImage(char** data, int* len)
{
	return g_cls_interface.GetZoomImage(data, len);
}

int ERVS_GetBaseImage(char** data, int* len)
{
	return g_cls_interface.GetBaseImage(data, len);
}

int ERVS_GetResultImage(char** data, int* len)
{
	return g_cls_interface.GetResultImage(data, len);
}

int ERVS_GetResultImageGlobal(char** data, int* len)
{
	return g_cls_interface.GetResultImageGlobal(data, len);
}

int ERVS_GetResultImageLocal(char** data, int* len, int id)
{
	return g_cls_interface.GetResultImageLocal(data, len, id);
}

int ERVS_GetImageWithUserArea(char** data, int* len)
{
	return g_cls_interface.GetImageWidthUserArea(data, len);
}

int ERVS_GetSearchArea(float* out_x, float* out_y, float* out_w, float* out_h)
{
	return g_cls_interface.GetSearchArea(out_x, out_y, out_w, out_h);
}

int ERVS_SetSearchArea(float x, float y, float w, float h)
{
	return g_cls_interface.SetSearchArea(x, y, w, h);
}

int ERVS_SetSearchAreaColor(int r, int g, int b)
{
	return g_cls_interface.SetSearchAreaColor(r,g,b);
}

int ERVS_GetSearchAreaColor(int* out_r, int* out_g, int* out_b)
{
	return g_cls_interface.GetSearchAreaColor(out_r, out_g, out_b);
}

int ERVS_SetSearchAreaWidth(int width)
{
	return g_cls_interface.SetSearchAreaWidth(width);
}

int ERVS_GetSearchAreaWidth(void)
{
	return g_cls_interface.GetSearchAreaWidth() ;
}

int ERVS_SetMasterAreaColor(int r, int g, int b)
{
	return g_cls_interface.SetMasterAreaColor(r, g, b);
}

int ERVS_GetMasterAreaColor(int* out_r, int* out_g, int* out_b)
{
	return g_cls_interface.GetMasterAreaColor(out_r, out_g, out_b);
}

int ERVS_SetMasterAreaWidth(int width)
{
	return g_cls_interface.SetMasterAreaWidth(width);
}

int ERVS_GetMasterAreaWidth(void)
{
	return g_cls_interface.GetMasterAreaWidth();
}

int ERVS_SetObjectColor(int object, int r, int g, int b)
{
	return g_cls_interface.SetObjectColor(object, r, g, b);
}

int ERVS_GetObjectColor(int object, int* out_r, int* out_g, int* out_b)
{
	return g_cls_interface.GetObjectColor(object, out_r, out_g, out_b);
}

int ERVS_SetObjectWidth(int object, int width)
{
	return g_cls_interface.SetObjectWidth(object, width);
}

int ERVS_GetObjectWidth(int object)
{
	return g_cls_interface.GetObjectWidth(object);
}

int ERVS_GetMasterArea(float* out_x, float* out_y, float* out_w, float* out_h)
{
	return g_cls_interface.GetMasterArea(out_x, out_y, out_w, out_h);
}

int ERVS_GetResultCircleInfoCameraBase(float* out_x, float* out_y, float* out_r, int id)
{
	return g_cls_interface.GetCircleInfoCameraBase(out_x, out_y, out_r, id);
}

int ERVS_GetResultCircleInfoRobotBase(float* out_x, float* out_y, float* out_r, int id)
{
	return g_cls_interface.GetCircleInfoRobotBase(out_x, out_y, out_r, id);
}

int ERVS_GetResultCircleInfoImageBase(float* out_x, float* out_y, float* out_r, int id)
{
	return g_cls_interface.GetCircleInfoImageBase(out_x, out_y, out_r, id);
}

int ERVS_GetMainObjectInfo(float* out_x, float* out_y, float* out_a)
{
	return g_cls_interface.GetMainObjectInfo(out_x, out_y, out_a);
}

int ERVS_SetMasterArea(float x, float y, float w, float h)
{
	return g_cls_interface.SetMasterArea(x, y, w, h);
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

int ERVS_SaveInformation(void)
{
	return g_cls_interface.SaveInformation();
}

int ERVS_LoadInformation(void)
{
	return g_cls_interface.LoadInformation();
}

float ERVS_GetBaseInfo(int option)
{
	return g_cls_interface.GetBaseInfo(option);
}

int ERVS_SetOptionPCAOn(void)
{
	return g_cls_interface.OptionPCAOn();
}

int ERVS_SetOptionPCAOff(void)
{
	return g_cls_interface.OptionPCAOff();
}

int ERVS_GetOptionPCA(void)
{
	return g_cls_interface.GetOptionPCA();
}

int ERVS_SetOptionFindWithCheckDefectOn(void)
{
	return g_cls_interface.SetOptionFindWithCheckDefectOn();
}

int ERVS_SetOptionFindWithCheckDefectOff(void)
{
	return g_cls_interface.SetOptionFindWithCheckDefectOff();
}

int ERVS_GetOptionFindWithCheckDefect(void)
{
	return g_cls_interface.GetOptionFindWithCheckDefect();
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

int ERVS_OptionFixSearchUserRoiOn(void)
{
	return g_cls_interface.OptionFixSearchUserRoiOn();
}

int ERVS_OptionFixSearchUserRoiOff(void)
{
	return g_cls_interface.OptionFixSearchUserRoiOff();
}

int ERVS_GetOptionFixSearchUserRoi(void)
{
	return g_cls_interface.GetOptionFixSearchUserRoi();
}

unsigned int ERVS_GetNewID(void)
{
	return g_cls_interface.GetNewID();
}

int ERVS_FindObject(int id)
{
	return g_cls_interface.FindObject(id);
}

int ERVS_FindObjectWithoutPCA(int id)
{
	return g_cls_interface.FindObjectWithoutPCA(id);
}

int ERVS_FindObjectWithPCA(void)
{
	return g_cls_interface.FindObjectWithPCA();
}

int ERVS_FindAllObject(void)
{
	return g_cls_interface.FindAllObjectWithPCA();
}

int ERVS_SetBase(int dep_id)
{
	return g_cls_interface.SetBase(dep_id);
}

int ERVS_SetNextImage(void)
{
	return g_cls_interface.SetNextImage();
}

int ERVS_SetSelectROI(float x, float y, int width, int height)
{
	return g_cls_interface.SetSelectObject(x, y, width, height);
}

int ERVS_GetSelectROI(float *out_x, float *out_y, int *out_width, int *out_height)
{
	return g_cls_interface.GetSelectObject(out_x, out_y, out_width, out_height);
}

int ERVS_CheckDefect(float threshold)
{
	return g_cls_interface.CheckDefect(threshold);
}

int ERVS_CheckDefectUserOption(bool checkoption1, float optionscore1, bool checkoption2, float optionscore2, int OptionAndOr)
{
	return g_cls_interface.CheckDefectUserOption(checkoption1, optionscore1, checkoption2, optionscore2, OptionAndOr);
}

int ERVS_CheckDefectList(int id)
{
	return g_cls_interface.CheckDefectList(id);
}

int ERVS_SetCheckDefectDBList(int id, bool fixarea, bool checkoption1, float optionscore1, bool checkoption2, float optionscore2, int OptionAndOr)
{
	return g_cls_interface.SetCheckDefect(id, fixarea, checkoption1, optionscore1, checkoption2, optionscore2, OptionAndOr);
}

unsigned int ERVS_GetCheckDefectDBListNum(void)
{
	return g_cls_interface.GetCheckDefectLinstNum();
}

unsigned int ERVS_GetObjectDBListNum(void)
{
	return g_cls_interface.GetObjectLinstNum();
}

int ERVS_GetCheckDefectDBList(const int index, bool *fixarea, int *id, bool *checkoption1, float *optionscore1, bool *checkoption2, float *optionscore2, int *OptionAndOr)
{
	return g_cls_interface.GetCheckDefectListInfo(index, id, fixarea, checkoption1, optionscore1, checkoption2, optionscore2, OptionAndOr);
}

int ERVS_GetObjectDBList(const int index, int *id, int *type)
{
	return g_cls_interface.GetObjectListInfo(index, id, type);
}

int ERVS_DelObjectDBList(int id)
{
	return g_cls_interface.DelObjectListInfo(id);
}

int ERVS_DelCheckDefectDBList(int id)
{
	return g_cls_interface.DelCheckDefectListInfo(id);
}

int ERVS_FileSaveCheckDefectDBList(void)
{
	return g_cls_interface.FileSaveCheckDefectListInfo();
}

int ERVS_FileLoadCheckDefectDBList(void)
{
	return g_cls_interface.FileLoadCheckDefectListInfo();
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

int ERVS_GetResultFindSearchAreaCameraBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle)
{
	return g_cls_interface.GetResultFindSearchAreaCameraBase(out_x1, out_y1, out_x2, out_y2, out_x3, out_y3, out_x4, out_y4, out_angle);
}

int ERVS_GetResultFindMasterAreaCameraBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle)
{
	return g_cls_interface.GetResultFindMasterAreaCameraBase(out_x1, out_y1, out_x2, out_y2, out_x3, out_y3, out_x4, out_y4, out_angle);
}

int ERVS_GetResultFindSearchAreaRobotBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle)
{
	return g_cls_interface.GetResultFindSearchAreaRobotBase(out_x1, out_y1, out_x2, out_y2, out_x3, out_y3, out_x4, out_y4, out_angle);
}

int ERVS_GetResultFindMasterAreaRobotBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle)
{
	return g_cls_interface.GetResultFindMasterAreaRobotBase(out_x1, out_y1, out_x2, out_y2, out_x3, out_y3, out_x4, out_y4, out_angle);
}

int ERVS_GetResultFindSearchAreaImageBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle)
{
	return g_cls_interface.GetResultFindSearchAreaImageBase(out_x1, out_y1, out_x2, out_y2, out_x3, out_y3, out_x4, out_y4, out_angle);
}

int ERVS_GetResultFindMasterAreaImageBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle)
{
	return g_cls_interface.GetResultFindMasterAreaImageBase(out_x1, out_y1, out_x2, out_y2, out_x3, out_y3, out_x4, out_y4, out_angle);
}

float ERVS_GetResultFindScale(void)
{
	return g_cls_interface.GetResultFindScale();
}

float ERVS_GetResultFindScore(void)
{
	return g_cls_interface.GetResultFindScore();
}

int ERVS_SetMode(int option)
{
	return g_cls_interface.SetMode(option);
}

int ERVS_GetMode(void)
{
	return g_cls_interface.GetMode();
}

int ERVS_ResetObject(void)
{
	return g_cls_interface.ResetObject();
}

int ERVS_DBAddObject(void)
{
	return g_cls_interface.DBAddObject();
}

int ERVS_DBAddSubObject(int id)
{
	return g_cls_interface.ERVS_DBAddSubObject(id);
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

int ERVS_GetSubObjectCount(int id)
{
	return g_cls_interface.GetSubObjectCount(id);
}

int ERVS_GetSubObjectSearchAreaByIdIndex(const int host_id, const int index, float* out_search_area_x, float* out_search_area_y, float* out_search_area_w, float* out_search_area_h)
{
	return g_cls_interface.GetSubObjectSearchAreaByIdIndex(host_id, index, out_search_area_x, out_search_area_y, out_search_area_w, out_search_area_h);
}

int ERVS_GetSubObjectSearchAreaByIdId(const int host_id, const int sub_id, float* out_search_area_x, float* out_search_area_y, float* out_search_area_w, float* out_search_area_h)
{
	return g_cls_interface.GetSubObjectSearchAreaByIdId(host_id, sub_id, out_search_area_x, out_search_area_y, out_search_area_w, out_search_area_h);
}

int ERVS_GetSubObjectMasterAreaByIdIndex(const int host_id, const int index, float* out_master_area_x, float* out_master_area_y, float* out_master_area_w, float* out_master_area_h)
{
	return g_cls_interface.GetSubObjectMasterAreaByIdIndex(host_id, index, out_master_area_x, out_master_area_y, out_master_area_w, out_master_area_h);
}

int ERVS_GetSubObjectMasterAreaByIdId(const int host_id, const int sub_id, float* out_master_area_x, float* out_master_area_y, float* out_master_area_w, float* out_master_area_h)
{
	return g_cls_interface.GetSubObjectMasterAreaByIdId(host_id, sub_id, out_master_area_x, out_master_area_y, out_master_area_w, out_master_area_h);
}

int ERVS_GetSubObjectCircleByIdIndex(const int host_id, const int index, float* out_circle_x, float* out_circle_y, float* out_circle_rx, float* out_circle_ry)
{
	return g_cls_interface.GetSubObjectCircleByIdIndex(host_id, index, out_circle_x, out_circle_y, out_circle_rx, out_circle_ry);
}

int ERVS_GetSubObjectCircleByIdId(const int host_id, const int sub_id, float* out_circle_x, float* out_circle_y, float* out_circle_rx, float* out_circle_ry)
{
	return g_cls_interface.GetSubObjectCircleByIdId(host_id, sub_id, out_circle_x, out_circle_y, out_circle_rx, out_circle_ry);
}


int ERVS_GetSubObjectUseInspectionByIdIndex(const int host_id, const int index)
{
	return g_cls_interface.GetSubObjectUseInspectionByIdIndex(host_id, index);
}

int ERVS_GetSubObjectUseInspectionByIdId(const int host_id, const int sub_id)
{
	return g_cls_interface.GetSubObjectUseInspectionByIdId(host_id, sub_id);
}

unsigned int ERVS_GetSubObjectID(int host_id, int idex)
{
	return g_cls_interface.GetSubObjectID(host_id, idex);
}

int ERVS_GetObjectFeatureUse(void)
{
	return g_cls_interface.GetObjectFeatureUse();
}

int ERVS_GetObjectFeatureColor(int* out_r, int* out_g, int* out_b)
{
	return g_cls_interface.GetObjectFeatureColor(out_r, out_g, out_b);
}

int ERVS_GetObjectFeatureWidth(void)
{
	return g_cls_interface.GetObjectFeatureWidth();
}

int ERVS_SetObjectFeatureUse(int use)
{
	return g_cls_interface.SetObjectFeatureUse(use);
}

int ERVS_SetObjectFeatureColor(int r, int g, int b)
{
	return g_cls_interface.SetObjectFeatureColor(r, g, b);
}

int ERVS_SetObjectFeatureWidth(int width)
{
	return g_cls_interface.SetObjectFeatureWidth(width);
}

int ERVS_GetObjectOutlineUse(void)
{
	return g_cls_interface.GetObjectOutlineUse();
}

int ERVS_GetObjectOutlineColor(int* out_r, int* out_g, int* out_b)
{
	return g_cls_interface.GetObjectOutlineColor(out_r, out_g, out_b);
}

int ERVS_GetObjectOutlineWidth(void)
{
	return g_cls_interface.GetObjectOutlineWidth();
}

int ERVS_SetObjectOutlineUse(int use)
{
	return g_cls_interface.SetObjectOutlineUse(use);
}

int ERVS_SetObjectOutlineColor(int r, int g, int b)
{
	return g_cls_interface.SetObjectOutlineColor(r, g, b);
}

int ERVS_SetObjectOutlineWidth(int width)
{
	return g_cls_interface.SetObjectOutlineWidth(width);
}

int ERVS_GetObjectRectUse(void)
{
	return g_cls_interface.GetObjectRectUse();
}

int ERVS_GetObjectRectColor(int* out_r, int* out_g, int* out_b)
{
	return g_cls_interface.GetObjectRectColor(out_r, out_g, out_b);
}

int ERVS_GetObjectRectWidth(void)
{
	return g_cls_interface.GetObjectRectWidth();
}

int ERVS_SetObjectRectUse(int use)
{
	return g_cls_interface.SetObjectRectUse(use);
}

int ERVS_SetObjectRectColor(int r, int g, int b)
{
	return g_cls_interface.SetObjectRectColor(r, g, b);
}

int ERVS_SetObjectRectWidth(int width)
{
	return g_cls_interface.SetObjectRectWidth(width);
}
///
int ERVS_GetObjectCenterUse(void)
{
	return g_cls_interface.GetObjectCenterUse();
}

int ERVS_GetObjectCenterColor(int* out_r, int* out_g, int* out_b)
{
	return g_cls_interface.GetObjectCenterColor(out_r, out_g, out_b);
}

int ERVS_GetObjectCenterWidth(void)
{
	return g_cls_interface.GetObjectCenterWidth();
}

int ERVS_SetObjectCenterUse(int use)
{
	return g_cls_interface.SetObjectCenterUse(use);
}

int ERVS_SetObjectCenterColor(int r, int g, int b)
{
	return g_cls_interface.SetObjectCenterColor(r, g, b);
}

int ERVS_SetObjectCenterWidth(int width)
{
	return g_cls_interface.SetObjectCenterWidth(width);
}
///
int ERVS_GetObjectAngleUse(void)
{
	return g_cls_interface.GetObjectAngleUse();
}

int ERVS_GetObjectAngleColor(int* out_r, int* out_g, int* out_b)
{
	return g_cls_interface.GetObjectAngleColor(out_r, out_g, out_b);
}

int ERVS_GetObjectAngleWidth(void)
{
	return g_cls_interface.GetObjectAngleWidth();
}

int ERVS_SetObjectAngleUse(int use)
{
	return g_cls_interface.SetObjectAngleUse(use);
}

int ERVS_SetObjectAngleColor(int r, int g, int b)
{
	return g_cls_interface.SetObjectAngleColor(r, g, b);
}

int ERVS_SetObjectAngleWidth(int width)
{
	return g_cls_interface.SetObjectAngleWidth(width);
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

int ERVS_GetFindObjectCount(void)
{
	return g_cls_interface.GetFindObjectCount();
}

int ERVS_GetFindObjectResultInfo(int base_index, int sub_index, float* out_id, float* out_cx, float* out_cy, float* out_rx, float* out_ry, float* out_angle, float* out_type, float* out_score, float** out_histogram, float* out_histogram_size)
{
	return g_cls_interface.GetFindObjectResultInfo(base_index, sub_index, out_id, out_cx, out_cy, out_rx, out_ry, out_angle, out_type, out_score, out_histogram, out_histogram_size);
}

int ERVS_GetFindObjectInfo(int index, int* id_range, unsigned int id_range_size, float** out_id, float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_angle, float** out_type, float** out_score)
{
	return g_cls_interface.GetFindObjectInfo(index, id_range, id_range_size, out_id, out_cx, out_cy, out_rx, out_ry, out_angle, out_type, out_score) ;
}

int ERVS_GetFindObjectInfo2(int index, float* out_cx, float* out_cy, float* out_rx, float* out_ry, float* out_angle, float* out_type, float* out_score)
{
	return g_cls_interface.GetFindObjectInfo2(index, out_cx, out_cy, out_rx, out_ry, out_angle, out_type, out_score);
}

int ERVS_GetFindObjectPose(int index, float* out_cx, float* out_cy, float* out_rx, float* out_ry, float* out_angle)
{
	return g_cls_interface.GetFindObjectPose(index, out_cx, out_cy, out_rx, out_ry, out_angle);
}

int ERVS_Calibration_isOK(void)
{
	return g_cls_interface.Calibration_isOK();
}

int ERVS_SetLog(int logoption)
{
	return g_cls_interface.SetLog(logoption);
}

int ERVS_VisionConfigFileSave(void)
{
	return g_cls_interface.VisionConfigFileSave();
}

int ERVS_VisionConfigFileLoad(void)
{
	return g_cls_interface.VisionConfigFileLoad();
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

int ERVS_ApplyAndMakeBaseGlobalInfo(void)
{
	return g_cls_interface.ApplyAndMakeBaseGlobalInfo();
}

int ERVS_ApplyAndMakeBaseLocalInfo(void)
{
	return g_cls_interface.ApplyAndMakeBaseLocalInfo();
}

int ERVS_ApplyAndMakeSearchAreaLocalInfo(void)
{
	return g_cls_interface.ApplyAndMakeSearchAreaLocalInfo();
}

int ERVS_SetCameraConfig(int type, int value, int value2)
{
	return g_cls_interface.SetCameraConfig(type,value,value2);
}

//Background Learning
int ERVS_BackgroundLearning(void)
{
	return g_cls_interface.BackgroundLearning();
}

//Find Search Area
int ERVS_FindSearchArea(int level)
{
	return g_cls_interface.FindSearchArea(level);
}
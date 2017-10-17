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
	int GetImage(char** out_data, int* len);
	int GetObjectImage(char** out_data, int* len);
	int GetFindObjectImage(int index, char** data, int* len);
	int GetZoomImage(char** out_data, int* len);
	int GetBaseImage(char** out_data, int* len);
	int GetResultImage(char** out_data, int* len);
	int GetResultImageGlobal(char** out_data, int* len);
	int GetResultImageLocal(char** out_data, int* len, int id);
	int GetImageWidthUserArea(char** out_data, int* len);
	int GetSearchArea(float* out_x, float* out_y, float* out_w, float* out_h);
	int SetSearchArea(float x, float y, float w, float h);
	int GetMasterArea(float* out_x, float* out_y, float* out_w, float* out_h);
	int SetMasterArea(float x, float y, float w, float h);
	int SetSelectBaseObject(float x, float y, float w, float h);
	int SetZoomArea(float x, float y, float w, float h);
	int ResetZoomArea(void);
	int SetMaskArea(float x, float y, float w, float h, bool inverse);
	int UndoMaskArea(void);
	int DelMaskArea(void);
	int SetObjectCircle(float x, float y, float r1, float r2);
	int GetObjectCircle(float *out_x, float *out_y, float *out_r1, float *out_r2);
	int SetObjectLine(float x, float y, float w, float h);
	int OptionPCAOn(void);
	int OptionPCAOff(void);
	int GetOptionPCA(void);
	int SetOptionFindWithCheckDefectOn(void);
	int SetOptionFindWithCheckDefectOff(void);
	int GetOptionFindWithCheckDefect(void);

	int FindObjectWithoutPCA(int id=-1);
	int FindObjectWithPCA(void);
	int FindAllObjectWithPCA(void);
	int SetBase(int dep_id);
	int SetNextImage(void);
	int SetSelectObject(float x, float y, int width=-1, int height=-1);
	int GetSelectObject(float* out_x, float* out_y, int* out_width, int* out_height);
	int GetCircleInfoCameraBase(float* out_x, float* out_y, float* out_r, int id=-1);
	int GetCircleInfoRobotBase(float* out_x, float* out_y, float* out_r, int id = -1);
	int GetCircleInfoImageBase(float* out_x, float* out_y, float* out_r, int id = -1);
	int GetMainObjectInfo(float* out_x, float* out_y, float* out_a);
	int SaveInformation(void);
	int LoadInformation(void);
	int OptionFixSearchAreaOn(void);
	int OptionFixSearchAreaOff(void);
	int GetOptionFixSearchArea(void);
	int OptionFixSearchUserRoiOn(void);
	int OptionFixSearchUserRoiOff(void);
	int GetOptionFixSearchUserRoi(void);
	unsigned int GetNewID(void);
	int CheckDefectUserOption(bool checkoption1, float optionscore1, bool checkoption2, float optionscore2, int OptionAndOr);
	int CheckDefect(float threshold);
	int CheckDefectList(int id);
	int SetCheckDefect(int id, bool fixarea, bool checkoption1, float optionscore1, bool checkoption2, float optionscore2, int OptionAndOr);
	unsigned int GetCheckDefectLinstNum(void);
	int GetCheckDefectListInfo(const int index, int *id, bool *fixarea, bool *checkoption1, float *optionscore1, bool *checkoption2, float *optionscore2, int *OptionAndOr);
	int DelCheckDefectListInfo(int id);
	int FileSaveCheckDefectListInfo(void);
	int FileLoadCheckDefectListInfo(void);
	int SetObjectInformation(int id=-1);
	unsigned int GetObjectLinstNum(void);
	int GetObjectListInfo(const int index, int *id, int *type);
	int DelObjectListInfo(int id);
	int FileSaveObjectListInfo(std::string path);
	int FileLoadObjectListInfo(std::string path);
	int SetVisionConfigOption(int option, float value);
	float GetVisionConfigOption(int option);

	int ApplyAndMakeBaseGlobalInfo(void);
	int ApplyAndMakeBaseLocalInfo(void);
	int ApplyAndMakeSearchAreaLocalInfo(void);

	int FindObject(int id=-1);

	int CreateSocket(char* ip, int port);
	void DeleteSocket();
	float GetBaseInfo(int option);

	int SetSearchAreaColor(int r, int g, int b);
	int GetSearchAreaColor(int* out_r, int* out_g, int* out_b);
	int SetSearchAreaWidth(int width);
	int GetSearchAreaWidth(void);

	int SetMasterAreaColor(int r, int g, int b);
	int GetMasterAreaColor(int* out_r, int* out_g, int* out_b);
	int SetMasterAreaWidth(int width);
	int GetMasterAreaWidth(void);

	int SetObjectColor(int object, int r, int g, int b);
	int GetObjectColor(int object, int* out_r, int* out_g, int* out_b);
	int SetObjectWidth(int object, int width);
	int GetObjectWidth(int object);

	int GetResultFindSearchAreaCameraBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle);
	int GetResultFindMasterAreaCameraBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle);
	int GetResultFindSearchAreaRobotBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle);
	int GetResultFindMasterAreaRobotBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle);
	int GetResultFindSearchAreaImageBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle);
	int GetResultFindMasterAreaImageBase(float *out_x1, float *out_y1, float *out_x2, float *out_y2, float *out_x3, float *out_y3, float *out_x4, float *out_y4, float *out_angle);

	float GetResultFindScale(void);
	float GetResultFindScore(void);

	int SetMode(int option);
	int GetMode(void);

	int DBAddObject(void);
	int ERVS_DBAddSubObject(int id);
	int ResetObject(void);
	int GetDBCount(void);
	int GetDB_Info_Id(int index);
	int GetDB_Select_ID(void);
	int SetObject(int id=-1);
	int DB_Del_ID(int id = -1);
	char* DB_Get_Mode(int id);

	int GetSubObjectCount(int id);
	unsigned int GetSubObjectID(int host_id, int index);
	int GetSubObjectSearchAreaByIdIndex(const int host_id, const int index, float* out_search_area_x, float* out_search_area_y, float* out_search_area_w, float* out_search_area_h);
	int GetSubObjectSearchAreaByIdId(const int host_id, const int sub_id, float* out_search_area_x, float* out_search_area_y, float* out_search_area_w, float* out_search_area_h);
	int GetSubObjectMasterAreaByIdIndex(const int host_id, const int index, float* out_master_area_x, float* out_master_area_y, float* out_master_area_w, float* out_master_area_h);
	int GetSubObjectMasterAreaByIdId(const int host_id, const int subi_id, float* out_master_area_x, float* out_master_area_y, float* out_master_area_w, float* out_master_area_h);
	int GetSubObjectUseInspectionByIdIndex(const int host_id, const int index);
	int GetSubObjectUseInspectionByIdId(const int host_id, const int sub_id);
	int GetSubObjectCircleByIdIndex(const int host_id, const int index, float* out_circle_x, float* out_circle_y, float* out_circle_rx, float* out_circle_ry);
	int GetSubObjectCircleByIdId(const int host_id, const int sub_id, float* out_circle_x, float* out_circle_y, float* out_circle_rx, float* out_circle_ry);
	int GetFindObjectCount(void);
	int GetFindObjectInfo(int index, int max_objects_count, int option, float** out_id, float** out_cx, float** out_cy, float** out_rx, float** out_ry, float** out_bound_cx, float** out_bound_cy, float** out_bound_rx, float** out_bound_ry, float** out_mass_cx, float** out_mass_cy, float** out_mass_rx, float** out_mass_ry, float** out_circle_rx, float** out_circle_ry, float** out_line1_x, float** out_line1_y, float** out_line2_x, float** out_line2_y, float** out_angle, float** out_type, float** out_score);
	int GetFindObjectResultInfo(int base_index, int sub_index, float* out_id, float* out_cx, float* out_cy, float* out_rx, float* out_ry, float* out_angle, float* out_type, float* out_score, float** out_histogram, float** out_histogram_b, float** out_histogram_g, float** out_histogram_r, float* out_histogram_size);
	int GetFindObjectInfo2(int index, float* out_cx, float* out_cy, float* out_rx, float* out_ry, float* out_angle, float* out_type, float* out_score);
	int GetFindObjectPose(int index, float* out_cx, float* out_cy, float* out_rx, float* out_ry, float* out_angle);

	int GetObjectFeatureUse(void);
	int GetObjectFeatureColor(int* out_r, int* out_g, int* out_b);
	int GetObjectFeatureWidth(void);
	int SetObjectFeatureUse(int use);
	int SetObjectFeatureColor(int r, int g, int b);
	int SetObjectFeatureWidth(int width);

	int GetObjectOutlineUse(void);
	int GetObjectOutlineColor(int* out_r, int* out_g, int* out_b);
	int GetObjectOutlineWidth(void);
	int SetObjectOutlineUse(int use);
	int SetObjectOutlineColor(int r, int g, int b);
	int SetObjectOutlineWidth(int width);

	int GetObjectRectUse(void);
	int GetObjectRectColor(int* out_r, int* out_g, int* out_b);
	int GetObjectRectWidth(void);
	int SetObjectRectUse(int use);
	int SetObjectRectColor(int r, int g, int b);
	int SetObjectRectWidth(int width);

	int GetObjectCenterUse(void);
	int GetObjectCenterColor(int* out_r, int* out_g, int* out_b);
	int GetObjectCenterWidth(void);
	int SetObjectCenterUse(int use);
	int SetObjectCenterColor(int r, int g, int b);
	int SetObjectCenterWidth(int width);

	int GetObjectAngleUse(void);
	int GetObjectAngleColor(int* out_r, int* out_g, int* out_b);
	int GetObjectAngleWidth(void);
	int SetObjectAngleUse(int use);
	int SetObjectAngleColor(int r, int g, int b);
	int SetObjectAngleWidth(int width);

	int Calibration_Add(float robot_x, float robot_y);
	int Calibration_GetCount(void);
	int Calibration_GetImage(int index, char** out_data, int* len);
	int Calibration_GetRobotInfo(int index, float *out_robot_x, float *out_robot_y);
	int Calibration_Del(int index);
	int Calibration_Clear(void);
	int Calibration_Run(void);
	int Calibration_GetPoint(const float in_px, const float in_py, float* out_rx, float* out_ry);
	int Calibration_GetChessPoint(const int index, float* out_rx, float* out_ry);
	int Calibration_isOK(void);
	int Calibration_GetID(void);
	int Calibration_Save(void);
	int Calibration_Load(void);
	int Calibration_Copy(const int id);

	int SetLog(int logoption);

	int VisionConfigFileSave(void);
	int VisionConfigFileLoad(void);

	char* GetVersion(void);
	int SetCameraConfig(int type, int value,int value2);
	int GetCameraConfig(int type);

	int SetCameraConfig_Default();
	int SetCameraConfig_Save();
	int SetCameraConfig_Load();

	int BackgroundLearning(void);

	int FindSearchArea(int level);

	//Geometry
	int Geometry_Distance(const int base_id, const int target_id, const float base_info, const float tol, float *out_value);
	int Geometry_Angle(const int base_id, const int target_id, const float base_info, const float tol, float *out_value);
	int Geometry_Clear(void);

	int Histogram_Set_Range(const int id, const int option, const int min_value, const int max_value);
	int Histogram_Get_Range(const int id, const int option, int *out_min_value, int *out_max_value);
	int Histogram_Get_Graph(const int id, float** out_histogram, float** out_histogram_b, float** out_histogram_g, float** out_histogram_r, float* out_histogram_size);
	int Histogram_Set_Use_Element(const int id, const int option);
	int Histogram_Get_Use_Element(const int id, int *out_option);

private:
	//bool m_run_thread_net;			//eyedea - boost thread exit value
	//boost::thread m_thread_net;		//eyedea - network thread
	boost::mutex mutex;

	CEyedeaEthernetClient *m_cls_eth_client;
};

#endif

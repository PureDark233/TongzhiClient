#include "stdafx.h"
#include <iostream>
#include <vector>
#include "DBUtil.h"
#include "Events.h"

using namespace Config;
using namespace Events;
using std::stringstream;
using std::cout;
using std::endl;
using std::cerr;

const char* DBHelper::dbVideo = "video";

const char* DBHelper::collecUser = "user";
const char* DBHelper::collecCam = "config";
const char* DBHelper::collecArea = "area";

const mongocxx::instance DBHelper::inst = mongocxx::instance{};

#define TEST_ON_MY_CLUSTER

//��ȡ���ӵ����ݿ��url
string getURL() {
	auto server = getServerInfo();
	stringstream ss;

#ifndef TEST_ON_MY_CLUSTER
	if (!server.load)
		throw std::exception("������������δ����/��ʼ��");
	ss << "mongodb://" << server.url << ":" << server.dbport;
	return ss.str();
#else
	return "mongodb://gakongren:7100040k@cluster0-shard-00-00-gdswx.mongodb.net:27017,"
		"cluster0-shard-00-01-gdswx.mongodb.net:27017,"
		"cluster0-shard-00-02-gdswx.mongodb.net:27017/"
		"?ssl=true&replicaSet=Cluster0-shard-0&authSource=admin";
#endif // !TEST_ON_MY_CLUSTER

}

//��ȡ���Ӻ�̨�û�������
UserType DBHelper::login()
{
	auto coll = db[collecUser];
	auto serverInfo = getServerInfo();
	auto result = coll.find_one(docBuilder{} << "user" << serverInfo.loginUser << "passwd" << serverInfo.loginPass << finalize);
	string json = bsoncxx::to_json(*result);
	ptree pt;
	read_json<ptree>(std::stringstream(json), pt);
	return User::getType(pt.get<int>("type"));
}

DBHelper::DBHelper() :conn(mongocxx::client{ mongocxx::uri{
	getURL().c_str()
} }), db(conn[dbVideo]) {}

//��ȡ��������ͷ��Ϣ
void DBHelper::pullCamInfo() {
	auto &collection = db[collecCam];
	auto &camInfo = getCamInfo();
	camInfo.clear();
	mongocxx::pipeline pipe;
	//��cid��������
	pipe.sort(docBuilder{} << "cid" << 1 << finalize);
	auto cursor = collection.aggregate(pipe);
	for (auto&& ele : cursor) {
		ptree pt;
		read_json(std::stringstream(bsoncxx::to_json(ele)), pt);
		try {
			CameraConfig cam;
			parseToCamInfo(pt, cam);
			camInfo.push_back(cam);
		}
		catch (std::exception e) {
			cerr << e.what() << endl;
#ifdef _DEBUG
			cout << e.what() << endl;
#endif
		}
	}
	CamListUpdate _event;
	EventBus::dispatch(&_event);
}

void DBHelper::parseToCamInfo(ptree &pt, CameraConfig &cam) {
	cam.active = pt.get<bool>("active");
	cam.mode = pt.get<short>("mode");
	cam.name = pt.get<string>("name");
	cam.url = pt.get<string>("address");
	cam.cam_user = pt.get<string>("camUser");
	cam.cam_passwd = pt.get<string>("camPasswd");

	ptree subt = pt.get_child("timeSel");
	cam.timeSel.timeing = subt.get<bool>("timing");
	cam.timeSel.start = subt.get<int>("start");
	cam.timeSel.end = subt.get<int>("end");
}

//����ȫ������ͷ��Ϣ
void DBHelper::saveCamInfo() {
	auto camInfo = getCamInfo();
	unsigned index = 0;
	std::vector<doc> docs;
	for (auto &&itor : camInfo) {
		try {
			docs.push_back(parseFromCamInfo(index, itor));
			//��Ҫ��index++�Ƴ�try��
			//��һ��tryʧ��ʱindexҲӦ���ֲ�����
			//ά��index��������������ÿ����Ч��Cam����
			index++;
		}
		catch (std::exception e) {
			cerr << e.what() << endl;
#ifdef _DEBUG
			cout << e.what() << endl;
#endif
		}
	}
	auto &collection = this->db[collecCam];
	collection.delete_many({});
	collection.insert_many(docs);
}

//����ĳһ������ͷ����Ϣ
//����ûɶ��
void DBHelper::updateCamInfo(int index) {
	auto &collection = db[collecCam];
	collection.replace_one(docBuilder{}
		<< "cid" << index
		<< finalize,
		parseFromCamInfo(index, getCamByIndex(index)));
}

void DBHelper::updateCamArea(int index, CRect area)
{
	auto &collec = db[collecArea];
	collec.find_one_and_replace(docBuilder{}
		<< "cid" << index
		<< finalize, parseAreaInfo(index, area));
}

//����cam�����ù��������ݿ��ڲ�����ĵ�����
doc DBHelper::parseFromCamInfo(int index, const CameraConfig& info) {
	return docBuilder{}
		<< "cid" << index
		<< "active" << info.active
		<< "mode" << info.mode
		<< "address" << info.url
		<< "name" << info.name
		<< "camUser" << info.cam_user
		<< "camPasswd" << info.cam_passwd
		<< "timeSel" << open_document
			<< "timing" << info.timeSel.timeing
			<< "start" << info.timeSel.start
			<< "end" << info.timeSel.end
		<< close_document
		<< finalize;
}

doc DBHelper::parseAreaInfo(int index, CRect area)
{
	return docBuilder{}
		<< "cid" << index
		<< "area" << open_document
			<< "left" << area.left
			<< "right" << area.right
			<< "top" << area.top
			<< "buttom" << area.bottom
		<< close_document
		<< finalize;
}

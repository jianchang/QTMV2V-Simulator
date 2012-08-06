/*
 * File Name: GenerateSimFile.h
 * Written by: Cong Liao
 * Email: liaocong@seas.upenn.edu
 * Description:
 *
 */

#ifndef GENERATESIMFILE_H
#define GENERATESIMFILE_H

#include <fstream>
#include <time.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <map>

#include "randomc.h"
#include "stocc.h"
#include "xmlParser.h"

#include "StringHelp.h"

#define _XMLPARSER_NO_MESSAGEBOX_
#define PROJECT "QTMV2V"

// New York
#define topLeftCoord "-73994245, 40755435"
#define bottomRightCoord "-73980293, 40742635"

// Boston

// Pittsburgh

// Detroit

// San Francisco


// default values
#define defaultDetectThreshMean 0.6
#define defaultDetectThreshStdev 0.2
#define defaultForwardThreshMean 0.7
#define defaultForwardThreshStdev 0.2
#define defaultLieFreqMean 10.0
#define defaultLieFreqStdev 5.0
#define defaultLieThreshMean 0.4
#define defaultLieThreshStdev 0.2
#define defaultTrustLowMean 0.4
#define defaultTrustLowStdev 0.1
#define defaultTrustUpMean 0.7
#define defaultTrustUpStdev 0.1


typedef enum ModelListEnum
{
    mVehicle = 0,
    mInfrastructure = 1,
    mIncident = 2,
    mMap = 3,
    mCarlist = 4,
    mIncidentlist = 5,
    mRole = 6,
    mComm = 7,
    mLink = 8,
    mPhys = 9,
    mTrip = 10,
    mMobility = 11,
}ModelList;

typedef enum VehicleParamEnum
{
    VehicleID = 0,
    DetectRange = 1,
    VehicleStartTime = 2,
    VehicleDelay = 3,
    Log = 4,
    TrackSpeed = 5,
}VehicleParam;

typedef enum InfrastructureParamEnum
{
    InfrastructureDelay = 0,
    InfrastructureID = 1,
    InfrastructurePosition = 2,
}InfrastructureParam;

typedef enum IncidentParamEnum
{
    IncidentDelay = 0,
    Description = 1,
    Duration= 2,
    IncidentID = 3,
    IncidentPosition = 4,
    Severity = 5,
    IncidentStartTime = 6,
    Visibility = 7,
}IncidentParam;

typedef enum MapListParamEnum
{
    MapDelay = 0,
    ListDelay = 1,
    Follow = 2,
    Height = 3, 
    Width = 4,
    StartPos = 5,
    Caption = 6,
    Zoom = 7,
}MapListParam;
/*
typedef enum CarListParamEnum
{

}CarListParam;

typedef enum IncidentListParamEnum
{

}IncidentListParam;
*/
typedef enum RoleParamEnum
{
    //RoleType = 0,
    DetectThresh = 0,
    ForwardThresh = 1,
    LieFreq = 2,
    LieThresh = 3,
    TrustLow = 4,
    TrustUp = 5,
}RoleParam;

typedef enum CommParamEnum
{
    //CommType = 0,
    GateWay = 0,
    RbxJitter = 1,
    Rbx = 2,
    RbxInterval = 3,
}CommParam;

typedef enum LinkParamEnum
{
    //LinkType = 0,
}LinkParam;

typedef enum PhysParamEnum
{
    //PhysType = 0,
    MaxDistance = 0,
    MultiChannel = 1,
}PhysParam;

typedef enum TripParamEnum
{
    //TripType = 0,
    StartAddress = 0,
}TripParam;

typedef enum MobilityParamEnum
{
    //MobilityType = 0,
    MultiLane = 0,
}MobilityParam;

typedef enum DistrParamEnum
{
    Mean = 0,
    StdDev =1,
} DistrParam;

typedef enum DistrTypeEnum
{
    Normal= 0,
    Poisson = 1,
    Uniform = 2,
    Bernouli = 3,
    Binomial = 4,
} DistrType;

float GenRandNum_NormalDtr(float mean, float stdev);

float GenRandNum_PossionDtr(float mean);

float GenRandNum(float minNum, float maxNum);

std::string IntToString(int num);

std::string FloatToString(float num);

float StringToFloat(std::string str);

std::string GenDetectThresh(int type = 0, float mean = defaultDetectThreshMean, float stdev = defaultDetectThreshStdev);

std::string GenForwardThresh(int type = 0, float mean = defaultForwardThreshMean, float stdev = defaultForwardThreshStdev);

std::string GenLieThresh(int type = 0, float mean = defaultLieThreshMean, float stdev = defaultLieThreshStdev);

std::string GenLieFreq(int type = 0, float mean = defaultLieFreqMean, float stdev = defaultLieFreqStdev);

std::string GenTrustLowBound(int type = 0, float mean = defaultTrustLowMean, float stdev = defaultTrustLowStdev);

std::string GenTrustUpBound(int type = 0, float mean = defaultTrustUpMean, float stdev = defaultTrustUpStdev);

std::string GenDetectRange();

std::string GenDelay();

std::string GenStartTime();

std::string GenAddress();

std::string GenMaxDistance();

std::string GenRbxInterval();

std::string GenRbx();

std::string GenRbxJitter();

std::string GenGateWay();

std::string GenMultiLane();

std::string GenMultiChannel();

std::string GenTrackSpeed();

std::string GenDoLog();

std::string GenDescription();

std::string GenDuration();

std::string GenSeverity();

std::string GenVisibility();

bool GenSimFile(int AttackerNum, int AuthorityNum, int DefaultNum, int IncidentNum, int rsuNum);

std::string ReadParamFromFile(std::string param, XMLNode node, std::string type, std::map<std::string, int> mapTypeList);

bool GenSimFile(const char * filename);

#endif //GENERATESIMFILE_H
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
#define defaultDetectThreshMean 6.0
#define defaultDetectThreshStdev 2.0
#define defaultForwardThreshMean 7.0
#define defaultForwardThreshStdev 2.0
#define defaultLieFreqMean 10.0
#define defaultLieFreqStdev 5.0
#define defaultLieThreshMean 4.0
#define defaultLieThreshStdev 2.0
#define defaultTrustLowMean 4.0
#define defaultTrustLowStdev 1.0
#define defaultTrustUpMean 7.0
#define defaultTrustUpStdev 1.0

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
    StdDev = 1,
    Prob = 2,
    UpperBound = 3,
} DistrParam;

typedef enum DistrTypeEnum
{
    Normal= 0,
    Poisson = 1,
    Bernoulli = 2,
    Binomial = 3,
    Uniform = 4,
    // add other type of distribution
} DistrType;

typedef struct DtrParamStruct
{
    float mean_Normal;
    float stdev_Normal;
    float mean_Poisson;
    float prob_Bernoulli;
    int upperBound_Binomial;
    float prob_Binomial;
    float upperBound_Uniform;
    float lowerBound_Uniform;
    int dtrType;
    bool flag;
}DtrParam;

const DtrParam defaultDetectThreshDtrParam = {defaultDetectThreshMean, defaultDetectThreshStdev, 0.5, 0.5, 10, 0.5, 0.0, 2.0, 0, 1}; 
const DtrParam defaultForwardThresDtrParam = {defaultForwardThreshMean, defaultForwardThreshStdev, 0.5, 0.5, 10, 0.5, 0.0, 2.0, 0, 1};
const DtrParam defaultLieFreqDtrParam = {defaultLieFreqMean, defaultLieFreqStdev, 0.5, 0.5, 10, 0.5, 0.0, 2.0, 0, 1};
const DtrParam defaultLieThreshDtrParam = {defaultLieThreshMean, defaultLieThreshStdev, 0.5, 0.5, 10, 0.5, 0.0, 2.0, 0, 1};
const DtrParam defaultTrustLowDtrParam = {defaultTrustLowMean, defaultTrustLowStdev, 0.5, 0.5, 10, 0.5, 0.0, 2.0, 0, 1};
const DtrParam defaultTrustUpDtrParam = {defaultTrustUpMean, defaultTrustUpStdev, 0.5, 0.5, 10, 0.5, 0.0, 2.0, 0, 1};

int factorial(int num);

float pdfOfNormal(float x, float mean, float stdev);

float pdfOfPoisson(float mean, int32_t i);

float pdfOfBernoulli(float p, int b);

float pdfOfBinomial(int t, float p, int i);

float pdfOfUniform(float a, float b);

float GenRand(DtrParam param);

float GenRandNum_NormalDtr(float mean, float stdev);

float GenRandNum_PoissonDtr(float mean);

float GenRandNum_BernoulliDtr(float prob);

float GenRandNum_BinomialDtr(int upperBound, float prob);

float GenRandNum_UniformDtr(float lowerBound, float upperBound); // (0, 1)

float GenRandNum(float minNum, float maxNum);

std::string IntToString(int num);

std::string FloatToString(float num);

float StringToFloat(std::string str);

int StringToInt(std::string str);

//std::string GenDetectThresh(int type = 0, float mean = defaultDetectThreshMean, float stdev = defaultDetectThreshStdev);
std::string GenDetectThresh(int type = 0, DtrParam param = defaultDetectThreshDtrParam);
//std::string GenForwardThresh(int type = 0, float mean = defaultForwardThreshMean, float stdev = defaultForwardThreshStdev);
std::string GenForwardThresh(int type = 0, DtrParam param = defaultForwardThresDtrParam);
//std::string GenLieThresh(int type = 0, float mean = defaultLieThreshMean, float stdev = defaultLieThreshStdev);
std::string GenLieThresh(int type = 0, DtrParam param = defaultLieThreshDtrParam);
//std::string GenLieFreq(int type = 0, float mean = defaultLieFreqMean, float stdev = defaultLieFreqStdev);
std::string GenLieFreq(int type = 0, DtrParam param = defaultLieFreqDtrParam);
//std::string GenTrustLowBound(int type = 0, float mean = defaultTrustLowMean, float stdev = defaultTrustLowStdev);
std::string GenTrustLowBound(int type = 0, DtrParam param = defaultTrustLowDtrParam);
//std::string GenTrustUpBound(int type = 0, float mean = defaultTrustUpMean, float stdev = defaultTrustUpStdev);
std::string GenTrustUpBound(int type = 0, DtrParam param = defaultTrustUpDtrParam);

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

DtrParam ReadParam(XMLNode node, std::string type, std::map<std::string, int> mapTypeList);

std::string ReadParamFromFile(std::string param, XMLNode node, std::string type, std::map<std::string, int> mapTypeList);

bool GenSimFile(const char * filename);

void SimFile(const char* filename);

#endif //GENERATESIMFILE_H
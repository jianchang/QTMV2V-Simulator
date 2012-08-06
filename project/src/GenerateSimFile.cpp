/*
 * File Name: GenerateSimFile.cpp
 * Written by: Cong Liao
 * Email: liaocong@seas.upenn.edu
 * Description:
 *
 */

#include "GenerateSimFile.h"
#include "MapDB.h"

#define defaultDelay "0.2"
#define defaultStartTime "0"
#define defaultDetectRange "50.0"
#define defaultCommMaxDistance "200.0"
#define defaultMultiLane "NO"
#define defaultMultiChannel "NO"
#define defaultTrackSpeed "NO"
#define defaultDoLog "YES"
#define defaultGateWay "NO"
#define defaultRbxJitter "YES"
#define defaultRbx "YES"
#define defaultRbxInterval "1"
#define defaultDescription "Car Crash!"
#define defaultCaption "GrooveNet Widget"
#define defaultHeight "373"
#define defaultWidth "529"
#define defaultZoom "6"
#define defaultStartPos "0, 0"
#define defaultFollow ""
#define defaultDuration "60.0"

#define baseID "192.168.0."


float GenRandNum_NormalDtr(float mean, float stdev)
{ 
    int seed = (int)time(0);
    StochasticLib1 sto(seed);
    double randNum = sto.Normal(mean, stdev);
    
    return randNum; 
}

float GenRandNum_PossionDtr(float mean)
{
    int seed = (int)time(0);
    StochasticLib1 sto(seed);
    double randNum = sto.Poisson(mean);
    
    return randNum;
}

float GenRandNum(float minNum, float maxNum)
{
    float ret = ((float)rand()) / RAND_MAX;
    if (maxNum > minNum)
	    return (ret * (maxNum - minNum)) + minNum;
    else
	    return minNum;
}

std::string IntToString(int num)
{
    std::string result;
    std::ostringstream convert;
    convert << num;
    result = convert.str();
    
    return result;
}

std::string FloatToString(float num)
{
    std::string result;    
    std::ostringstream convert;    
    convert.precision(1);   
    convert << num;   
    result = convert.str();
    
    return result;
}

float StringToFloat(std::string str)
{
    QString s(str);
    float f = (float)StringToNumber(s);
    return f;
}

std::string GenDetectThresh(int type, float mean, float stdev)
{
    float val;
    std::string detectThresh;
    
    switch ((DistrType)type)
    {
      case Normal:
      {
	  val = GenRandNum_NormalDtr(mean, stdev);
      }
      case Poisson:
      {
	  val = GenRandNum_PossionDtr(mean);
      }
      case Uniform:
      {
	  // to be added
      }
      case Bernouli:
      {
	 // to be added
      }
      case Binomial:
      {
        // to be added
      }
      default:
      {
	  val = GenRandNum_NormalDtr(mean, stdev);
      }
    }
    detectThresh = FloatToString(val);
    
    return detectThresh;
}

std::string GenForwardThresh(int type, float mean, float stdev)
{
    float val;
    std::string forwardThresh;
    
    switch ((DistrType)type)
    {
      case Normal:
      {
	  val = GenRandNum_NormalDtr(mean, stdev);
      }
      case Poisson:
      {
	  val = GenRandNum_PossionDtr(mean);
      }
      case Uniform:
      {
	  // to be added
      }
      case Bernouli:
      {
	 // to be added
      }
      case Binomial:
      {
        // to be added
      }
      default:
      {
	  val = GenRandNum_NormalDtr(mean, stdev);
      }
    }
    
    forwardThresh= FloatToString(val);
    
    return forwardThresh;
}

std::string GenLieThresh(int type, float mean, float stdev)
{
    float val;   
    std::string lieThresh;
    
    switch ((DistrType)type)
    {
      case Normal:
      {
	  val = GenRandNum_NormalDtr(mean, stdev);
      }
      case Poisson:
      {
	  val = GenRandNum_PossionDtr(mean);
      }
      case Uniform:
      {
	  // to be added
      }
      case Bernouli:
      {
	 // to be added
      }
      case Binomial:
      {
        // to be added
      }
      default:
      {
	  val = GenRandNum_NormalDtr(mean, stdev);
      }
    }
    
    lieThresh= FloatToString(val);
    
    return lieThresh;
}

std::string GenLieFreq(int type, float mean, float stdev)
{
    float val;    
    std::string lieFreq;
    
    switch ((DistrType)type)
    {
      case Normal:
      {
	  val = GenRandNum_NormalDtr(mean, stdev);
      }
      case Poisson:
      {
	  val = GenRandNum_PossionDtr(mean);
      }
      case Uniform:
      {
	  // to be added
      }
      case Bernouli:
      {
	 // to be added
      }
      case Binomial:
      {
        // to be added
      }
      default:
      {
	  val = GenRandNum_NormalDtr(mean, stdev);
      }
    }
    
    lieFreq = FloatToString(val);
    
    return lieFreq;
}

std::string GenTrustLowBound(int type, float mean, float stdev)
{
    float val;   
    std::string trustLowBound;
    
    switch ((DistrType)type)
    {
      case Normal:
      {
	  val = GenRandNum_NormalDtr(mean, stdev);
      }
      case Poisson:
      {
	  val = GenRandNum_PossionDtr(mean);
      }
      case Uniform:
      {
	  // to be added
      }
      case Bernouli:
      {
	 // to be added
      }
      case Binomial:
      {
        // to be added
      }
      default:
      {
	  val = GenRandNum_NormalDtr(mean, stdev);
      }
    }
    
    trustLowBound = FloatToString(val);
    
    return trustLowBound;
}

std::string GenTrustUpBound(int type, float mean, float stdev)
{
    float val;   
    std::string trustUpBound;
    
    switch ((DistrType)type)
    {
      case Normal:
      {
	  val = GenRandNum_NormalDtr(mean, stdev);
      }
      case Poisson:
      {
	  val = GenRandNum_PossionDtr(mean);
      }
      case Uniform:
      {
	  // to be added
      }
      case Bernouli:
      {
	 // to be added
      }
      case Binomial:
      {
        // to be added
      }
      default:
      {
	  val = GenRandNum_NormalDtr(mean, stdev);
      }
    }
    
    trustUpBound = FloatToString(val);
    
    return trustUpBound;
}

std::string GenDetectRange()
{
    return defaultDetectRange;
}

std::string GenDelay()
{
    return defaultDelay;
}

std::string GenStartTime()
{
    return defaultStartTime;
}

std::string GenAddress()
{
    std::string address = "";   
    Address sAddress;
    QString coord1 = QString::fromAscii(topLeftCoord);
    QString coord2 = QString::fromAscii(bottomRightCoord);
    Coords topLeft;
    Coords bottomRight;
    if (bottomRight.FromString(coord2) && topLeft.FromString(coord1))
    {
	Rect r(topLeft, bottomRight);
	g_pMapDB->GetRandomAddress(&sAddress, r);
	address = AddressToString(&sAddress).ascii();
    }
    else
	std::cout << "generate random address fail\n";
    
    return address;
}

std::string GenMaxDistance()
{
    return defaultCommMaxDistance;
}

std::string GenRbxInterval()
{
    return defaultRbxInterval;
}

std::string GenRbx()
{
    return defaultRbx;
}

std::string GenRbxJitter()
{
    return defaultRbxJitter;
}

std::string GenGateWay()
{
    return defaultGateWay;
}

std::string GenMultiLane()
{
    return defaultMultiLane;
}

std::string GenMultiChannel()
{
    return defaultMultiChannel;
}

std::string GenTrackSpeed()
{
    return defaultTrackSpeed;
}

std::string GenDoLog()
{
    return defaultDoLog;
}

std::string GenDescription()
{
     return defaultDescription;
}

std::string GenDuration()
{
    float mean = 60;
    float stdev = 5;
    float num = GenRandNum_NormalDtr(mean, stdev);
    
    std::string duration = FloatToString(num);
    
    return duration;
}

std::string GenSeverity()
{   
    int level;
    
    srand(time(0));
    
    level = rand() % 6;
    
    switch (level)
    {
      case 0:
	return "Level 0";
      case 1:
	return "Level 1";
      case 2:
	return "Level 2";
      case 3:
	return "Level 3";
      case 4:
	return "Level 4";
      case 5:
	return "Level 5";
      default:
	return "Level 5";
    }
}

std::string GenVisibility()
{
    float mean = 60;
    float stdev = 10;
    float num = GenRandNum_NormalDtr(mean, stdev);
    
    std::string visibility = FloatToString(num);
    
    return visibility;
}

// input arguments from command line
bool GenSimFile(int AttackerNum, int AuthorityNum, int DefaultNum, int IncidentNum, int rsuNum)
{
	// create a output stream
	std::ofstream simFile;
	
	// open the simulatio file
	simFile.open("test.sim");
	
	if (simFile.is_open())
	{
	    int i;
	    int j;
	    //std::string baseID = "192.168.0.";
	    int totalNum = AttackerNum + AuthorityNum + DefaultNum;
	    
	    /* start writing data to the file */
	    // get time
	    time_t currentTime;
	    struct tm * timeInfo;
	    
	    time(&currentTime);
	    timeInfo = localtime(&currentTime);
	    
	    // write time
	    simFile << "% Created by QTMV2V Simulator on " + std::string(asctime(timeInfo));
	    
	    simFile << "\n";
	    // map
	    simFile << "MODEL=\"MapVisual0\" TYPE=\"MapVisual\"\n";
	    simFile << "CAPTION=\"GrooveNet Widget\" DELAY=\"0.2\" FOLLOW=\"\" HEIGHT=\"373\" START_POS=\"0, 0\" WIDTH=\"529\" ZOOM=\"6\"\n";
	    
	    simFile << "\n";
	    // car list
	    simFile << "MODEL=\"CarListVisual0\" TYPE=\"CarListVisual\"\n";
	    simFile << "CAPTION=\"GrooveNet Widget\" DELAY=\"0.2\" HEIGHT=\"175\" WIDTH=\"529\"\n";
	    
	    simFile << "\n";
	    // incident list
	    simFile << "MODEL=\"IncidentListVIsual0\" TYPE=\"IncidentListVisual\"\n";
	    simFile << "CAPTION=\"GrooveNet Widget\" DELAY=\"0.2\" HEIGHT=\"175\" WIDTH=\"529\"\n";
	    
	    // role model parameters
	    std::string roleModel;
	    std::string roleModelName;
	    std::string detectThresh;
	    std::string forwardThresh;
	    std::string lieFreq;
	    std::string lieThresh;
	    std::string trustLowerBound;
	    std::string trustUpperBound;
	    
	    // other model parameters
	    // vehicles with different roles have the same communication, mobility, etc. models
	    std::string tripModel;
	    std::string mobilityModel;
	    std::string startAddress;
	    std::string multiLane;
	    std::string commModel;
	    std::string gateWay;
	    std::string rbxJitter;
	    std::string rbx;
	    std::string rbxInterval;
	    std::string linkModel;
	    std::string physModel;
	    std::string maxDistance;
	    std::string multiChannel;
	    std::string vehicleModel;
	    std::string delay;
	    std::string detectRange;
	    std::string trackSpeed;
	    std::string doLog;
	    std::string startTime;
	    std::string vehicleID;
	    
	    for (i = 0; i < totalNum; i++)
	    {
		simFile << "\n";
	      
		// attacker role
		if (i < AttackerNum)
		{
		    j = i;
		    roleModelName =  "AttackerRoleModel";
		    roleModel = roleModelName + IntToString(j);
		    lieFreq = "LIE FREQUENCY=\"" + GenLieFreq() + "\" ";
		}
		// authority role
		else if ((i >= AttackerNum) && (i < AuthorityNum + AttackerNum))
		{
		    j = i - AttackerNum;
		    roleModelName = "AuthorityRoleModel";
		    roleModel = roleModelName + IntToString(j);
		    lieFreq = " ";
		}
		// default role
		else
		{
		    j = i - AttackerNum - AuthorityNum;
		    roleModelName = "DefaultRoleModel";
		    roleModel = roleModelName + IntToString(j);
		    lieFreq = " ";
		}
		
		// role model
		simFile << "MODEL=\"" + roleModel + "\" " + "TYPE=\"" + roleModelName + "\"\n"; 
		
		detectThresh = "DETECTION THRESHOLD=\"" + GenDetectThresh() + "\" ";
		forwardThresh = "FORWARD THRESHOLD=\"" + GenForwardThresh() + "\" ";
		lieThresh = "LIE THRESHOLD=\"" + GenLieThresh() + "\" ";
		trustLowerBound = "TRUST LOWER BOUND=\"" + GenTrustLowBound() + "\" ";
		trustUpperBound = "TRUST UPPER BOUND=\"" + GenTrustUpBound() + "\"\n";
		
		simFile << detectThresh + forwardThresh + lieFreq + lieThresh + trustLowerBound + trustUpperBound;
		
		simFile << "\n";
		
		// trip model
		std::string tripModelName = "RandomWalkModel";
		tripModel = tripModelName + IntToString(i);
		simFile << "MODEL=\"" + tripModel + "\" " + "TYPE=\"" + tripModelName + "\"\n";
		startAddress = GenAddress();
		simFile << "START=\"" + startAddress + "\"\n";
		
		simFile << "\n";
		
		// mobility model
		std::string mobilityModelName = "StreetSpeedModel";
		mobilityModel = mobilityModelName + IntToString(i);
		simFile << "MODEL=\"" + mobilityModel + "\" " + "TYPE=\"" + mobilityModelName + "\" " + "DEPENDS=\"" + tripModel + "\"\n";
		multiLane = GenMultiLane();
		simFile << "MULTILANE=\"" + multiLane + "\" " + "TRIP=\"" + tripModel + "\"\n";
		
		simFile << "\n";
		
		// communication layer model
		std::string commModelName = "SimpleCommModel";
		commModel = commModelName + IntToString(i);
		simFile << "MODEL=\"" + commModel + "\" " + "TYPE=\"" + commModelName + "\"\n";
		gateWay = GenGateWay();
		rbxJitter = GenRbxJitter();
		rbx = GenRbx();
		rbxInterval = GenRbxInterval();
		simFile << "GATEWAY=\"" + gateWay + "\" " + "RBXJITTER=\"" + rbxJitter + "\" " + "REBROADCAST=\"" + rbx + "\" " + "REBROADCASTINTERVAL=\"" + rbxInterval + "\"\n";
		
		simFile << "\n";
		
		// link layer model
		std::string linkModelName = "SimpleLinkModel";
		linkModel = linkModelName + IntToString(i);
		simFile << "MODEL=\"" + linkModel + "\" " + "TYPE=\"" + linkModelName + "\"\n";
		
		simFile << "\n";
		
		// physical layer model
		std::string physModelName = "SimplePhysModel";
		physModel = physModelName + IntToString(i);
		simFile << "MODEL=\"" + physModel + "\" " + "TYPE=\"" + physModelName + "\"\n";
		maxDistance = GenMaxDistance();
		multiChannel = GenMultiChannel();
		simFile << "MAXDISTANCE=\"" + maxDistance + "\" " + "MULTICHANNEL=\"" + multiChannel + "\"\n";
		
		simFile << "\n";
		
		// vehicle model
		std::string vehicleModelName = "VehicleModel";
		vehicleModel = vehicleModelName + IntToString(i);
		delay = GenDelay();
		detectRange = GenDetectRange();
		trackSpeed = GenTrackSpeed();
		doLog = GenDoLog();
		startTime = GenStartTime();
		vehicleID = baseID + IntToString(i+1);
		
		simFile << "MODEL=\"" + vehicleModel + "\" " + "TYPE=\"" + vehicleModelName + "\" ";
		simFile << "DEPENDS=\"" + physModel + ";" + linkModel + ";" + commModel + ";" + roleModel + ";" + tripModel + ";" + mobilityModel + "\"\n";
		simFile << "COMM=\"" + commModel + "\" " + "DELAY=\"" + delay + "\" " + "DETECTION RANGE=\"" + detectRange + "\" " + "DOLOG=\"" + doLog + "\" " + "ID=\"" + vehicleID + "\" " + "LINK=\"" + linkModel + "\" " + "MOBILITY=\"" + mobilityModel + "\" " + "PHYS=\"" + physModel + "\" " + "ROLE=\"" + roleModel + "\" " + "START=\"" + startTime + "\" " + "TRACKSPEED=\"" + trackSpeed + "\" " + "TRIP=\"" + tripModel + "\"\n";
		
	    }
	    
	    // road side unit model
	    j = i;
	    std::string rsuModelName;
	    std::string rsuModel;
	    std::string rsuID;
	    std::string position;
	    for (i = 0; i < rsuNum; i++)
	    {
		simFile << "\n";
		
		// communication layer model
		std::string commModelName = "SimpleCommModel";
		commModel = commModelName + IntToString(i+j);
		simFile << "MODEL=\"" + commModel + "\" " + "TYPE=\"" + commModelName + "\"\n";
		gateWay = GenGateWay();
		rbxJitter = GenRbxJitter();
		rbx = GenRbx();
		rbxInterval = GenRbxInterval();
		simFile << "GATEWAY=\"" + gateWay + "\" " + "RBXJITTER=\"" + rbxJitter + "\" " + "REBROADCAST=\"" + rbx + "\" " + "REBROADCASTINTERVAL=\"" + rbxInterval + "\"\n";
		
		simFile << "\n";
		
		// link layer model
		std::string linkModelName = "SimpleLinkModel";
		linkModel = linkModelName + IntToString(i+j);
		simFile << "MODEL=\"" + linkModel + "\" " + "TYPE=\"" + linkModelName + "\"\n";
		
		simFile << "\n";
		
		// physical layer model
		std::string physModelName = "SimplePhysModel";
		physModel = physModelName + IntToString(i+j);
		simFile << "MODEL=\"" + physModel + "\" " + "TYPE=\"" + physModelName + "\"\n";
		maxDistance = GenMaxDistance();
		multiChannel = GenMultiChannel();
		simFile << "MAXDISTANCE=\"" + maxDistance + "\" " + "MULTICHANNEL=\"" + multiChannel + "\"\n";
		
		simFile << "\n";
		
		// infrastructure
		rsuModelName = "InfrastructureNodeModel";
		rsuModel = rsuModelName + IntToString(i);
		delay = GenDelay();
		position = GenAddress();
		rsuID = baseID + IntToString(i+j+1);
		
		simFile << "MODEL=\"" + rsuModel + "\" " + "TYPE=\"" + rsuModelName + "\" " + "DEPENDS=\"" + commModel + ";" + linkModel + ";" + physModel + "\"\n";
		simFile << "COMM=\"" + commModel + "\" " + "DELAY=\"" + delay + "\" " + "ID=\"" + rsuID + "\" " + "LINK=\"" + linkModel + "\" " + "PHYS=\"" + physModel + "\" " + "POSITION=\"" + position + "\"\n"; 
		
	    }
	    
	    
	    // incident model
	    std::string incidentModelName;
	    std::string incidentModel;
	    std::string description;
	    std::string incidentID;
	    std::string duration;
	    std::string severity;
	    std::string visibility;
	    for (i = 0; i < IncidentNum; i++)
	    {
		simFile << "\n";
		
		incidentModelName = "IncidentModel";
		incidentModel = incidentModelName + IntToString(i) + "(ID" + IntToString(i+1) + ")";
		description = GenDescription();
		duration = GenDuration();
		severity = GenSeverity();
		visibility = GenVisibility();
		incidentID = IntToString(i+1);
		startTime = GenStartTime();
		position = GenAddress();
		
		simFile << "MODEL=\"" + incidentModel + "\" " + "TYPE=\"" + incidentModelName + "\"\n";;
		simFile << "DELAY=\"" + delay + "\" " + "DESCRIPTION=\"" + description + "\" " + "DURATION=\"" + duration + "\" " + "INCIDENT ID=\"" + incidentID + "\" " + "POSITION=\"" + position + "\" " + "SEVERITY=\"" +severity + "\" " + "START=\"" + startTime + "\" " + "VISIBILITY=\"" + visibility + "\"\n";
		
	    }
	    
	    simFile.close(); 
	    
	    return true;
	}
	else
	{
	    return false;
	}
}

std::string ReadParamFromFile(std::string param, XMLNode node, std::string type, std::map<std::string, int> mapTypeList)
{
    if (param == "DetectThresh")
    {
	std::string detectThresh, mean, stdev;
	switch((DistrType)mapTypeList.find(type)->second)
	{
	  case Normal:
	  {
	      mean = node.getChildNodeWithAttribute("param", "name", "Mean").getText() != NULL ? node.getChildNodeWithAttribute("param","name","Mean").getText() : "";
	      stdev = node.getChildNodeWithAttribute("param", "name", "Stdev").getText() != NULL ? node.getChildNodeWithAttribute("param","name","Stdev").getText() : "";
	      if (mean != "" && stdev != "")
		  detectThresh = GenDetectThresh(0, StringToFloat(mean), StringToFloat(stdev));
	      else if (mean != "" && stdev == "")
		  detectThresh = GenDetectThresh(0, StringToFloat(mean), defaultDetectThreshStdev);
	      else if (mean == "" && stdev != "")
		  detectThresh = GenDetectThresh(0, defaultDetectThreshMean, StringToFloat(stdev));
	      else
		  detectThresh = GenDetectThresh();
	      break;
	  }
	  case Poisson:
	  {
	      
	      break;
	  }
	  case Uniform:
	  {
	      
	      break;
	  }
	  case Bernouli:
	  {
	      
	      break;
	  }
	  case Binomial:
	  {
	      
	      break;
	  }
	  default:
	  {
	      detectThresh = GenDetectThresh();
	      break;
	  }
	}
	
	return detectThresh;
    }
    
    if (param == "ForwardThresh")
    {
	std::string forwardThresh, mean, stdev;
	switch((DistrType)mapTypeList.find(type)->second)
	{
	  case Normal:
	  {
	      mean = node.getChildNodeWithAttribute("param", "name", "Mean").getText() != NULL ? node.getChildNodeWithAttribute("param","name","Mean").getText() : "";
	      stdev = node.getChildNodeWithAttribute("param", "name", "Stdev").getText() != NULL ? node.getChildNodeWithAttribute("param","name","Stdev").getText() : "";
	      if (mean != "" && stdev != "")
		  forwardThresh = GenForwardThresh(0, StringToFloat(mean), StringToFloat(stdev));
	      else if (mean != "" && stdev == "")
		  forwardThresh = GenForwardThresh(0, StringToFloat(mean), defaultForwardThreshStdev);
	      else if (mean == "" && stdev != "")
		  forwardThresh = GenForwardThresh(0, defaultForwardThreshMean, StringToFloat(stdev));
	      else
		  forwardThresh = GenForwardThresh();
	      break;
	  }
	  case Poisson:
	  {
	      
	      break;
	  }
	  case Uniform:
	  {
	      
	      break;
	  }
	  case Bernouli:
	  {
	      
	      break;
	  }
	  case Binomial:
	  {
	      
	      break;
	  }
	  default:
	  {
	      forwardThresh = GenForwardThresh();
	      break;
	  }
	}
	
	return forwardThresh;
    }
    
    if (param == "LieFreq")
    {
	std::string lieFreg, mean, stdev;
	switch((DistrType)mapTypeList.find(type)->second)
	{
	  case Normal:
	  {
	      mean = node.getChildNodeWithAttribute("param", "name", "Mean").getText() != NULL ? node.getChildNodeWithAttribute("param","name","Mean").getText() : "";
	      stdev = node.getChildNodeWithAttribute("param", "name", "Stdev").getText() != NULL ? node.getChildNodeWithAttribute("param","name","Stdev").getText() : "";
	      if (mean != "" && stdev != "")
		  lieFreg = GenLieFreq(0, StringToFloat(mean), StringToFloat(stdev));
	      else if (mean != "" && stdev == "")
		  lieFreg = GenLieFreq(0, StringToFloat(mean), defaultLieFreqStdev);
	      else if (mean == "" && stdev != "")
		  lieFreg = GenLieFreq(0, defaultLieFreqMean, StringToFloat(stdev));
	      else
		  lieFreg = GenLieFreq();
	      break;
	  }
	  case Poisson:
	  {
	      
	      break;
	  }
	  case Uniform:
	  {
	      
	      break;
	  }
	  case Bernouli:
	  {
	      
	      break;
	  }
	  case Binomial:
	  {
	      
	      break;
	  }
	  default:
	  {
	      lieFreg = GenLieFreq();
	      break;
	  }
	}
	
	return lieFreg;
    }
    
    if (param == "LieThresh")
    {
	std::string lieThresh, mean, stdev;
	switch((DistrType)mapTypeList.find(type)->second)
	{
	  case Normal:
	  {
	      mean = node.getChildNodeWithAttribute("param", "name", "Mean").getText() != NULL ? node.getChildNodeWithAttribute("param","name","Mean").getText() : "";
	      stdev = node.getChildNodeWithAttribute("param", "name", "Stdev").getText() != NULL ? node.getChildNodeWithAttribute("param","name","Stdev").getText() : "";
	      if (mean != "" && stdev != "")
		  lieThresh = GenLieThresh(0, StringToFloat(mean), StringToFloat(stdev));
	      else if (mean != "" && stdev == "")
		  lieThresh = GenLieThresh(0, StringToFloat(mean), defaultLieThreshStdev);
	      else if (mean == "" && stdev != "")
		  lieThresh = GenLieThresh(0, defaultLieThreshMean, StringToFloat(stdev));
	      else
		  lieThresh = GenLieThresh();
	      break;
	  }
	  case Poisson:
	  {
	      
	      break;
	  }
	  case Uniform:
	  {
	      
	      break;
	  }
	  case Bernouli:
	  {
	      
	      break;
	  }
	  case Binomial:
	  {
	      
	      break;
	  }
	  default:
	  {
	      lieThresh = GenLieThresh();
	      break;
	  }
	}
	
	return lieThresh;
    }
    
    if (param == "TrustLow")
    {
	std::string trustLowBound, mean, stdev;
	switch((DistrType)mapTypeList.find(type)->second)
	{
	  case Normal:
	  {
	      mean = node.getChildNodeWithAttribute("param", "name", "Mean").getText() != NULL ? node.getChildNodeWithAttribute("param","name","Mean").getText() : "";
	      stdev = node.getChildNodeWithAttribute("param", "name", "Stdev").getText() != NULL ? node.getChildNodeWithAttribute("param","name","Stdev").getText() : "";
	      if (mean != "" && stdev != "")
		  trustLowBound = GenTrustLowBound(0, StringToFloat(mean), StringToFloat(stdev));
	      else if (mean != "" && stdev == "")
		  trustLowBound = GenTrustLowBound(0, StringToFloat(mean), defaultTrustLowStdev);
	      else if (mean == "" && stdev != "")
		  trustLowBound = GenTrustLowBound(0, defaultTrustLowMean, StringToFloat(stdev));
	      else
		  trustLowBound = GenTrustLowBound();
	      break;
	  }
	  case Poisson:
	  {
	      
	      break;
	  }
	  case Uniform:
	  {
	      
	      break;
	  }
	  case Bernouli:
	  {
	      
	      break;
	  }
	  case Binomial:
	  {
	      
	      break;
	  }
	  default:
	  {
	      trustLowBound = GenTrustLowBound();
	      break;
	  }
	}
	
	return trustLowBound;
    }
    
    if (param == "TrusUp")
    {
	std::string trustUpBound, mean, stdev;
	switch((DistrType)mapTypeList.find(type)->second)
	{
	  case Normal:
	  {
	      mean = node.getChildNodeWithAttribute("param", "name", "Mean").getText() != NULL ? node.getChildNodeWithAttribute("param","name","Mean").getText() : "";
	      stdev = node.getChildNodeWithAttribute("param", "name", "Stdev").getText() != NULL ? node.getChildNodeWithAttribute("param","name","Stdev").getText() : "";
	      if (mean != "" && stdev != "")
		  trustUpBound = GenTrustUpBound(0, StringToFloat(mean), StringToFloat(stdev));
	      else if (mean != "" && stdev == "")
		  trustUpBound = GenTrustUpBound(0, StringToFloat(mean), defaultTrustUpStdev);
	      else if (mean == "" && stdev != "")
		  trustUpBound = GenTrustUpBound(0, defaultTrustUpMean, StringToFloat(stdev));
	      else
		  trustUpBound = GenTrustUpBound();
	      break;
	  }
	  case Poisson:
	  {
	      
	      break;
	  }
	  case Uniform:
	  {
	      
	      break;
	  }
	  case Bernouli:
	  {
	      
	      break;
	  }
	  case Binomial:
	  {
	      
	      break;
	  }
	  default:
	  {
	      trustUpBound = GenTrustUpBound();
	      break;
	  }
	}
	
	return trustUpBound;
    }
    
    // TODO: add conditions of other parameters
}

bool GenSimFile(const char * filename)
{
    // open the xml file
    XMLNode mainNode = XMLNode::openFileHelper(filename, "simulation");
     
    // create a output stream
    std::ofstream simFile;
	
    // open the simulation file
    simFile.open("simtest.sim");
    
    // get time
    time_t currentTime;
    struct tm * timeInfo;
    time(&currentTime);
    timeInfo = localtime(&currentTime);
    
    // initialize string<->enum map
    //--------------------------------------
    std::map<std::string, int> mapModelList;
    mapModelList["mVehicle"] = 0;
    mapModelList["mInfrastructure"] = 1;
    mapModelList["mIncident"] = 2;
    mapModelList["mMap"] = 3;
    mapModelList["mCarlist"] = 4;
    mapModelList["mIncidentlist"] = 5;
    mapModelList["mRole"] = 6;
    mapModelList["mComm"] = 7;
    mapModelList["mLink"] = 8;
    mapModelList["mPhys"] = 9;
    mapModelList["mTrip"] = 10;
    mapModelList["mMobility"] = 11;
    
    std::map<std::string, int> mapVehicleParamList;
    mapVehicleParamList["VehicleID"] = 0;
    mapVehicleParamList["DetectRange"] = 1;
    mapVehicleParamList["VehicleStartTime"] = 2;
    mapVehicleParamList["VehicleDelay"] = 3;
    mapVehicleParamList["Log"] = 4;
    mapVehicleParamList["TrackSpeed"] = 5;
    
    std::map<std::string, int> mapInfrastructureParamList;
    mapInfrastructureParamList["InfrastructureDelay"] = 0;
    mapInfrastructureParamList["InfrastructureID"] = 1;
    mapInfrastructureParamList["InfrastructurePosition"] = 2;
    
    std::map<std::string, int> mapIncidentParamList;
    mapIncidentParamList["IncidentDelay"] = 0;
    mapIncidentParamList["Description"] = 1;
    mapIncidentParamList["Duration"] = 2;
    mapIncidentParamList["IncidentID"] = 3;
    mapIncidentParamList["IncidentPosition"] = 4;
    mapIncidentParamList["Severity"] = 5;
    mapIncidentParamList["IncidentStartTime"] = 6;
    mapIncidentParamList["Visibility"] = 7;
    
    std::map<std::string, int> mapMapListParamList;
    mapMapListParamList["MapDelay"] = 0;
    mapMapListParamList["ListDelay"] = 1;
    mapMapListParamList["Follow"] = 2;
    mapMapListParamList["Height"] = 3;
    mapMapListParamList["Width"] = 4;
    mapMapListParamList["StartPos"] = 5;
    mapMapListParamList["Caption"] = 6;
    mapMapListParamList["Zoom"] = 7;
    
    std::map<std::string, int> mapRoleParamList;
    //mapRoleParamList["RoleType"] = 0;
    mapRoleParamList["DetectThresh"] = 0;
    mapRoleParamList["ForwardThresh"] = 1;
    mapRoleParamList["LieFreq"] = 2;
    mapRoleParamList["LieThresh"] = 3;
    mapRoleParamList["TrustLow"] = 4;
    mapRoleParamList["TrustUp"] = 5;
    
    std::map<std::string, int> mapCommParamList;
    //mapCommParamList["CommType"] = 0;
    mapCommParamList["GateWay"] = 0;
    mapCommParamList["RbxJitter"] = 1;
    mapCommParamList["Rbx"] = 2;
    mapCommParamList["RbxInterval"] = 3;
    
    std::map<std::string, int> mapLinkParamList;
    //mapLinkParamList["LinkType"] = 0;
    
    std::map<std::string, int> mapPhysParamList;
    //mapPhysParamList["PhysType"] = 0;
    mapPhysParamList["MaxDistance"] = 0;
    mapPhysParamList["MultiChannel"] = 1;
    
    std::map<std::string, int> mapTripParamList;
    //mapTripParamList["TripType"] = 0;
    mapTripParamList["StartAddress"] = 0;
    
    std::map<std::string, int> mapMobilityParamList;
    //mapMobilityParamList["MobilityType"] = 0;
    mapMobilityParamList["MultiLane"] = 0;
    
    std::map<std::string, int> mapDtrParamList;
    mapDtrParamList["Mean"] = 0;
    mapDtrParamList["StdDev"] = 1;
    
    std::map<std::string, int> mapDtrTypeList;
    mapDtrTypeList["Normal"] = 0;
    mapDtrTypeList["Poisson"] = 1;
    mapDtrTypeList["Uniform"] = 2;
    mapDtrTypeList["Bernouli"] = 3;
    mapDtrTypeList["Binomial"] = 4;
    
    //-----------------------------------------------
    
    // comm model
    std::string commType;
    std::string vehicleGateWay;
    std::string vehicleRbxJitter;
    std::string vehicleRbx;
    std::string vehicleRbxInterval;
    std::string rsuGateWay;
    std::string rsuRbxJitter;
    std::string rsuRbx;
    std::string rsuRbxInterval;
    
    // link model
    std::string linkType;
    
    // phys model
    std::string physType;
    std::string vehicleMaxDistance;
    std::string vehicleMultiChannel;
    std::string rsuMaxDistance;
    std::string rsuMultiChannel;
    
    // trip model
    std::string tripType;
    std::string startAddress;
    
    // mobility model
    std::string mobilityType;
    std::string multiLane;
    
    // role model parameters
    std::string roleType;
    std::string detectThresh;
    std::string forwardThresh;
    std::string lieFreq;
    std::string lieThresh;
    std::string trustLowerBound;
    std::string trustUpperBound;
    
    // vehicle model parameters
    std::string vehicleID;
    std::string detectRange;
    std::string vehicleStartTime;
    std::string vehicleDelay;
    std::string log;
    std::string trackSpeed;
    std::string vehicleComm;
    std::string vehicleLink;
    std::string vehiclePhys;
    std::string vehicleRole;
    std::string vehicleTrip;
    std::string vehicleMobility;
    
    // road side unit model parameters
    std::string rsuDelay;
    std::string rsuComm;
    std::string rsuLink;
    std::string rsuPhys;
    std::string rsuID;
    std::string rsuPosition;
    
    // incident model parameters
    std::string incidentDelay;
    std::string description;
    std::string duration;
    std::string incidentID;
    std::string incidentPosition;
    std::string severity;
    std::string incidentStartTime;
    std::string visibility;
    
    // map, car/incident list parameters
    std::string mapCaption;
    std::string mapDelay;
    std::string mapHeight;
    std::string mapWidth;
    std::string carListCaption;
    std::string carListDelay;
    std::string carListHeight;
    std::string carListWidth;
    std::string incidentListCaption;
    std::string incidentListDelay;
    std::string incidentListHeight;
    std::string incidentListWidth;
    std::string follow;
    std::string startPos;
    std::string zoom;
    
    std::string distributionType;
    std::string meanVal;
    std::string stdDevVal;
    
    int vehicleNum = 0, rsuNum = 0, incidentNum = 0, mapNum, carListNum, incidentListNum; 
    int simCommNum = 0, simLinkNum = 0, simPhysNum = 0;
    int randWalkNum = 0, strtSpdNum = 0;
    int attNum = 0, authNum = 0, deftNum = 0;
    int i, j, k, m, n;
    
    if (simFile.is_open())
    {
	 // write time
	simFile << "% Created by QTMV2V Simulator on " + std::string(asctime(timeInfo)) + "\n";
	
	if (std::string(mainNode.getAttribute("project")) == PROJECT)
	{
	    // parse models
	    int modelNum = mainNode.nChildNode("model");
	    for (i = 0; i < modelNum; i++)
	    {
		XMLNode subNode = mainNode.getChildNode(i);
		std::string modelStr (subNode.getAttribute("name"));
		if (modelStr != NULL)
		{
		    switch((ModelList)mapModelList.find(modelStr)->second)
		    {
		      case mVehicle:
		      {
			  int vecNum = 0;
			  if (subNode.isAttributeSet("number") == TRUE)
			  {
			      if (subNode.getAttribute("number") != NULL && subNode.getAttribute("number") != "0")
			      {
				  vecNum = atoi(subNode.getAttribute("number"));
			      }
			      else
			      {
				  vecNum = 1;
			      }
			  }
			  else
			  {
			      vecNum = 1;
			  }
			  
			  for (j = 0; j < vecNum; j++)
			  {
			      int vehicleParamNum = subNode.nChildNode("param");
			      for (k = 0; k < vehicleParamNum; k++)
			      {
				  XMLNode subNodeParamOfVehicle = subNode.getChildNode("param", k);
				  std::string vehicleParamStr = subNodeParamOfVehicle.getAttribute("name");
				  if ( vehicleParamStr != NULL)
				  {
				      switch((VehicleParam)mapVehicleParamList.find(vehicleParamStr)->second)
				      {
					case VehicleID:
					{
					    if (subNodeParamOfVehicle.getText() != NULL)
						vehicleID = subNodeParamOfVehicle.getText();
					    else
						vehicleID = baseID + IntToString(j+1);
					    break;
					}
					case DetectRange:
					{
					    if (subNodeParamOfVehicle.getText() != NULL)
						detectRange = subNodeParamOfVehicle.getText();
					    else
						detectRange = GenDetectRange();
					    break;
					}
					case VehicleStartTime:
					{
					    if (subNodeParamOfVehicle.getText() != NULL)
						vehicleStartTime = subNodeParamOfVehicle.getText();
					    else
						vehicleStartTime = GenStartTime();
					    break;
					}
					case VehicleDelay:
					{
					    if (subNodeParamOfVehicle.getText() != NULL)
						vehicleDelay = subNodeParamOfVehicle.getText();
					    else
						vehicleDelay = GenDelay();
					    break;
					}
					case Log:
					{
					    if (subNodeParamOfVehicle.getText() != NULL)
						log = subNodeParamOfVehicle.getText();
					    else
						log = GenDoLog();
					    break;
					}
					case TrackSpeed:
					{
					    if (subNodeParamOfVehicle.getText() != NULL)
						trackSpeed = subNodeParamOfVehicle.getText();
					    else
						trackSpeed = GenTrackSpeed();
					    break;
					}
					default:
					{
					    std::cout << "Invalid vehicle parameter!\n";
					    break;
					}
				      }
				  }
			      }
			      
			      int vehicleModelNum = subNode.nChildNode("model");
			      for (m = 0; m < vehicleModelNum; m++)
			      {
				  XMLNode subNodeModelOfVehicle = subNode.getChildNode("model", m);
				  std::string vehicleModelStr = subNodeModelOfVehicle.getAttribute("name");
				  if (vehicleModelStr != NULL)
				  {
				      switch((ModelList)mapModelList.find(vehicleModelStr)->second)
				      {
					case mComm:
					{
					    commType = subNodeModelOfVehicle.getAttribute("type");
					    int vehicleModelParamNum = subNodeModelOfVehicle.nChildNode("param");
					    for (n = 0; n < vehicleModelParamNum; n++)
					    {
						XMLNode subNodeModelParamOfVehicle = subNodeModelOfVehicle.getChildNode(n);
						std::string vehicleModelParamStr = subNodeModelParamOfVehicle.getAttribute("name");
						if (vehicleModelParamStr != NULL)
						{
						    switch ((CommParam)mapCommParamList.find(vehicleModelParamStr)->second)
						    {
						      case GateWay:
						      {
							  if (subNodeModelParamOfVehicle.getText() != NULL)
							      vehicleGateWay = subNodeModelParamOfVehicle.getText();
							  else
							      vehicleGateWay = GenGateWay();
							  break;
						      }
						      case RbxJitter:
						      {
							  if (subNodeModelParamOfVehicle.getText() != NULL)
							      vehicleRbxJitter = subNodeModelParamOfVehicle.getText();
							  else
							      vehicleRbxJitter = GenRbxJitter();
							  break;
						      }
						      case Rbx:
						      {
							  if (subNodeModelParamOfVehicle.getText() != NULL)
							      vehicleRbx = subNodeModelParamOfVehicle.getText();
							  else
							      vehicleRbx = GenRbx();
							  break;
						      }
						      case RbxInterval:
						      {
							  if (subNodeModelParamOfVehicle.getText() != NULL)
							      vehicleRbxInterval = subNodeModelParamOfVehicle.getText();
							  else
							      vehicleRbxInterval = GenRbxInterval();
							  break;
						      }
						      //TODO:add cases of parameters for other comm model
						      default:
						      {
							  std::cout << "Invalid comm parameter!\n";
							  break;
						      }
						    }
						}
					    }
					    break;
					}
					case mLink:
					{
					    linkType = subNodeModelOfVehicle.getAttribute("type");
					    int vehicleModelParamNum = subNodeModelOfVehicle.nChildNode("param");
					    for (n = 0; n < vehicleModelParamNum; n++)
					    {
						XMLNode subNodeModelParamOfVehicle = subNodeModelOfVehicle.getChildNode(n);
						std::string vehicleModelParamStr = subNodeModelParamOfVehicle.getAttribute("name");
						if (vehicleModelParamStr != NULL)
						{
						    switch ((LinkParam)mapLinkParamList.find(vehicleModelParamStr)->second)
						    {
						      default:
						      {
							  std::cout << "Invalid link parameter!\n";
							  break;
						      }
						    }
						}
					    }
					    break;
					}
					case mPhys:
					{
					    physType = subNodeModelOfVehicle.getAttribute("type");
					    int vehicleModelParamNum = subNodeModelOfVehicle.nChildNode("param");
					    for (n = 0; n < vehicleModelParamNum; n++)
					    {
						XMLNode subNodeModelParamOfVehicle = subNodeModelOfVehicle.getChildNode(n);
						std::string vehicleModelParamStr = subNodeModelParamOfVehicle.getAttribute("name");
						if (vehicleModelParamStr != NULL)
						{
						    switch ((PhysParam)mapPhysParamList.find(vehicleModelParamStr)->second)
						    {
						      case MaxDistance:
						      {
							  if (subNodeModelParamOfVehicle.getText() != NULL)
							      vehicleMaxDistance = subNodeModelParamOfVehicle.getText();
							  else
							      vehicleMaxDistance = GenMaxDistance();
							  break;
						      }
						      case MultiChannel:
						      {
							  if (subNodeModelParamOfVehicle.getText() != NULL)
							      vehicleMultiChannel = subNodeModelParamOfVehicle.getText();
							  else
							      vehicleMultiChannel = GenMultiChannel();
							  break;
						      }
						      //TODO: add cases of parameter for other phys model
						      default:
						      {
							  std::cout << "Invalid phys parameter!\n";
							  break;
						      }
						    }
						}
					    }
					    break;
					}
					case mRole:
					{
					    roleType = subNodeModelOfVehicle.getAttribute("type");
					    int vehicleModelParamNum = subNodeModelOfVehicle.nChildNode("param");
					    for (n = 0; n < vehicleModelParamNum; n++)
					    {
						XMLNode subNodeModelParamOfVehicle = subNodeModelOfVehicle.getChildNode(n);
						std::string vehicleModelParamStr = subNodeModelParamOfVehicle.getAttribute("name");
						if (vehicleModelParamStr != NULL)
						{
						    switch ((RoleParam)mapRoleParamList.find(vehicleModelParamStr)->second)
						    {
						      case DetectThresh:
						      {
							  /*if (subNodeModelParamOfVehicle.getText() != NULL)
							      detectThresh = subNodeModelParamOfVehicle.getText();
							  else
							      detectThresh = GenDetectThresh();
							  */
							  if ((vehicleModelParamStr = subNodeModelParamOfVehicle.getAttribute("type")) != NULL)
							  {
							      detectThresh = ReadParamFromFile("DetectThresh", subNodeModelParamOfVehicle, vehicleModelParamStr, mapDtrTypeList);
							  }
							  else
							  {
							      detectThresh = GenDetectThresh();
							  }
							  
							  break;
						      }
						      case ForwardThresh:
						      {
							  if (subNodeModelParamOfVehicle.getText() != NULL)
							      forwardThresh = subNodeModelParamOfVehicle.getText();
							  else
							      forwardThresh = GenForwardThresh();
							  break;
						      }
						      case LieFreq:
						      {
							  if (subNodeModelParamOfVehicle.getText() != NULL)
							      lieFreq = subNodeModelParamOfVehicle.getText();
							  else
							      lieFreq = GenLieFreq();
							  break;
						      }
						      case LieThresh:
						      {
							  if (subNodeModelParamOfVehicle.getText() != NULL)
							      lieThresh = subNodeModelParamOfVehicle.getText();
							  else
							      lieThresh = GenLieThresh();
							  break;
						      }
						      case TrustLow:
						      {
							  if (subNodeModelParamOfVehicle.getText() != NULL)
							      trustLowerBound = subNodeModelParamOfVehicle.getText();
							  else
							      trustLowerBound = GenTrustLowBound();
							  break;
						      }
						      case TrustUp:
						      {
							  if (subNodeModelParamOfVehicle.getText() != NULL)
							      trustUpperBound = subNodeModelParamOfVehicle.getText();
							  else
							      trustUpperBound = GenTrustUpBound();
							  break;
						      }
						      default:
						      {
							  std::cout << "Invalid role parameter!\n";
							  break;
						      }
						    }
						}
					    }
					    break;
					}
					case mTrip:
					{
					    tripType = subNodeModelOfVehicle.getAttribute("type");
					    int vehicleModelParamNum = subNodeModelOfVehicle.nChildNode("param");
					    for (n = 0; n < vehicleModelParamNum; n++)
					    {
						XMLNode subNodeModelParamOfVehicle = subNodeModelOfVehicle.getChildNode(n);
						std::string vehicleModelParamStr = subNodeModelParamOfVehicle.getAttribute("name");
						if (vehicleModelParamStr != NULL)
						{
						    switch ((TripParam)mapTripParamList.find(vehicleModelParamStr)->second)
						    {
						      case StartAddress:
						      {
							  if (subNodeModelParamOfVehicle.getText() != NULL)
							      startAddress = subNodeModelParamOfVehicle.getText();
							  else
							      startAddress = GenAddress();
							  break;
						      }
						      //TODO: add cases of parameters for other trip models
						      default:
						      {
							  std::cout << "Invalid trip parameters!\n";
							  break;
						      }
						    }
						}
					    }
					    break;
					}
					case mMobility:
					{
					    mobilityType = subNodeModelOfVehicle.getAttribute("type");
					    int vehicleModelParamNum = subNodeModelOfVehicle.nChildNode("param");
					    for (n = 0; n < vehicleModelParamNum; n++)
					    {
						XMLNode subNodeModelParamOfVehicle = subNodeModelOfVehicle.getChildNode(n);
						std::string vehicleModelParamStr = subNodeModelParamOfVehicle.getAttribute("name");
						if (vehicleModelParamStr != NULL)
						{
						    switch ((MobilityParam)mapMobilityParamList.find(vehicleModelParamStr)->second)
						    {
						      case MultiLane:
						      {
							  if (subNodeModelParamOfVehicle.getText() != NULL)
							      multiLane = subNodeModelParamOfVehicle.getText();
							  else
							      multiLane = GenMultiLane();
							  break;
						      }
						      //TODO: add cases of parameters for other mobility models
						      default:
						      {
							  std::cout << "Invalid mobility parameter!\n";
							  break;
						      }
						    }
						}
					    }
					    break;
					}
					default:
					{
					    std::cout << "Invalid vehicle model!\n";
					    break;
					}
				      }
				  }
			      }
			      
			      if (commType == "SimpleComm")
			      {
				  vehicleComm = "SimpleCommModel" + IntToString(j+simCommNum);
				  simFile << "MODEL=\"" + vehicleComm + "\" " + "TYPE=\"SimpleCommModel\n";
				  simFile << "GATEWAY=\"" + vehicleGateWay + "\" " + "RBXJITTER=\"" + vehicleRbxJitter + "\" " + "REBROADCAST=\"" + vehicleRbx + "\" " + "REBROADCASTINTERVAL=\"" + vehicleRbxInterval + "\"\n\n";
			      }
			      
			      if (linkType == "SimpleLink")
			      { 
				  vehicleLink = "SimpleLinkModel" + IntToString(j+simLinkNum);
				  simFile << "MODEL=\"" + vehicleLink + "\" " + "TYPE=\"SimpleLinkModel\"\n\n";
			      }
			      
			      if (physType == "SimplePhys")
			      {
				  vehiclePhys = "SimplePhysModel" + IntToString(j+simPhysNum);
				  simFile << "MODEL=\"" + vehiclePhys + "\" " + "TYPE=\"SimplePhysModel\"\n";
				  simFile << "MAXDISTANCE=\"" + vehicleMaxDistance + "\" " + "MULTICHANNEL=\"" + vehicleMultiChannel + "\"\n\n";
			      }
			      
			      if (roleType == "Attacker")
			      {
				  vehicleRole = "AttackerRoleModel" + IntToString(j+attNum);
				  simFile << "MODEL=\"" + vehicleRole + "\" " + "TYPE=\"AttackerRoleModel\"\n";
				  simFile << "DETECTION THRESHOLD=\"" + detectThresh + "\" " + "FORWARD THRESHOLD=\"" + forwardThresh + "\" " + "LIE FREQUENCY=\"" + lieFreq + "\" " + "LIE THRESHOLD=\"" + lieThresh + "\" " + "TRUST LOWER BOUND=\"" + trustLowerBound + "\" " + "TRUST UPPER BOUND=\"" + trustUpperBound + "\"\n\n";
			      }
			      
			      if (tripType == "RandomWalk")
			      {
				  vehicleTrip = "RandomWalkModel" + IntToString(j+randWalkNum);
				  simFile << "MODEL=\"" + vehicleTrip + "\" " + "TYPE=\"RandomWalkModel\"\n";
				  simFile << "START=\"" + startAddress + "\"\n\n";
			      }
			      
			      if (mobilityType == "StreetSpeed")
			      {
				  vehicleMobility = "StreetSpeedModel" + IntToString(j+strtSpdNum);
				  simFile << "MODEL=\"" + vehicleMobility + "\" " + "TYPE=\"StreetSpeedModel\" " + "DEPENDS=\"" + vehicleTrip + "\"\n";
				  simFile << "MULTILANE=\"" + multiLane + "\" " + "TRIP=\"" + vehicleTrip + "\"\n\n";
			      }
			      
			      simFile << "MODEL=\"VehicleModel" + IntToString(j) + "\" " + "TYPE=\"VehicleModel\" ";
			      simFile << "DEPENDS=\"" + vehiclePhys + ";" + vehicleLink + ";" + vehicleComm + ";" + vehicleRole + ";" + vehicleTrip + ";" + vehicleMobility + "\"\n";
			      simFile << "COMM=\"" + vehicleComm + "\" " + "DELAY=\"" + vehicleDelay + "\" " + "DETECTION RANGE=\"" + detectRange + "\" " + "DOLOG=\"" + log + "\" " + "ID=\"" + vehicleID + "\" " + "LINK=\"" + vehicleLink + "\" " + "MOBILITY=\"" + vehicleMobility + "\" " + "PHYS=\"" + vehiclePhys + "\" " + "ROLE=\"" + vehicleRole + "\" " + "START=\"" + vehicleStartTime + "\" " + "TRACKSPEED=\"" + trackSpeed + "\" " + "TRIP=\"" + vehicleTrip + "\"\n\n";
			  }
			  
			  simCommNum += vecNum;
			  simLinkNum += vecNum;
			  simPhysNum += vecNum;
			  attNum += vecNum;
			  randWalkNum += vecNum;
			  strtSpdNum += vecNum;
			  vehicleNum += vecNum;
			  
			  break;
		      }
		      case mInfrastructure:
		      {
			  int infNum = 0;
			  if (subNode.isAttributeSet("number") == TRUE)
			  {
			      if (subNode.getAttribute("number") != NULL && subNode.getAttribute("number") != "0")
			      {
				  infNum = atoi(subNode.getAttribute("number"));
			      }
			      else
			      {
				  infNum = 1;
			      }
			  }
			  else
			  {
			      infNum = 1;
			  }
			  
 			  for (j = 0; j < infNum; j++)
			  {
			      int rsuParamNum = subNode.nChildNode("param");
			      for (k = 0; k < rsuParamNum; k++)
			      {
				  XMLNode subNodeParamOfRSU = subNode.getChildNode("param", k);
				  std::string rsuParamStr = subNodeParamOfRSU.getAttribute("name");
				  if ( rsuParamStr != NULL)
				  {
				      switch((InfrastructureParam)mapInfrastructureParamList.find(rsuParamStr)->second)
				      {
					case InfrastructureDelay:
					{
					    if (subNodeParamOfRSU.getText() != NULL)
						rsuDelay = subNodeParamOfRSU.getText();
					    else
						rsuDelay = GenDelay();
					    break;
					}
					case InfrastructureID:
					{
					    if (subNodeParamOfRSU.getText() != NULL)
						rsuID = subNodeParamOfRSU.getText();
					    else
						rsuID = baseID + IntToString(vehicleNum + j + 1);
					    break;
					}
					case InfrastructurePosition:
					{
					    if (subNodeParamOfRSU.getText() != NULL)
						rsuPosition = subNodeParamOfRSU.getText();
					    else
						rsuPosition = GenAddress();
					    break;
					}
					default:
					{
					    std::cout << "Invalid infrastructure parameter!\n";
					    break;
					}
				      }
				  }
			      }
			      
			      int rsuModelNum = subNode.nChildNode("model");
			      for (m = 0; m < rsuModelNum; m++)
			      {
				  XMLNode subNodeModelOfRSU = subNode.getChildNode("model", m);
				  std::string rsuModelStr = subNodeModelOfRSU.getAttribute("name");
				  if ( rsuModelStr != NULL)
				  {
				      switch((ModelList)mapModelList.find(rsuModelStr)->second)
				      {
					case mComm:
					{
					    commType = subNodeModelOfRSU.getAttribute("type");
					    int rsuModelParamNum = subNodeModelOfRSU.nChildNode("param");
					    for (n = 0; n < rsuModelParamNum; n++)
					    {
						XMLNode subNodeModelParamOfRSU = subNodeModelOfRSU.getChildNode(n);
						std::string rsuModelParamStr = subNodeModelParamOfRSU.getAttribute("name");
						if (rsuModelParamStr != NULL)
						{
						    switch ((CommParam)mapCommParamList.find(rsuModelParamStr)->second)
						    {
						      case GateWay:
						      {
							  if (subNodeModelParamOfRSU.getText() != NULL)
							      rsuGateWay = subNodeModelParamOfRSU.getText();
							  else
							      rsuGateWay = GenGateWay();
							  break;
						      }
						      case RbxJitter:
						      {
							  if (subNodeModelParamOfRSU.getText() != NULL)
							      rsuRbxJitter = subNodeModelParamOfRSU.getText();
							  else
							      rsuRbxJitter = GenRbxJitter();
							  break;
						      }
						      case Rbx:
						      {
							  if (subNodeModelParamOfRSU.getText() != NULL)
							      rsuRbx = subNodeModelParamOfRSU.getText();
							  else
							      rsuRbx = GenRbx();
							  break;
						      }
						      case RbxInterval:
						      {
							  if (subNodeModelParamOfRSU.getText() != NULL)
							      rsuRbxInterval = subNodeModelParamOfRSU.getText();
							  else
							      rsuRbxInterval = GenRbxInterval();
							  break;
						      }
						      //TODO:add cases of parameters for other comm model
						      default:
						      {
							  std::cout << "Invalid comm parameter!\n";
							  break;
						      }
						    }
						}
					    }
					    break;
					}
					case mLink:
					{
					    linkType = subNodeModelOfRSU.getAttribute("type");
					    int rsuModelParamNum = subNodeModelOfRSU.nChildNode("param");
					    for (n = 0; n < rsuModelParamNum; n++)
					    {
						XMLNode subNodeModelParamOfRSU = subNodeModelOfRSU.getChildNode(n);
						std::string rsuModelParamStr = subNodeModelParamOfRSU.getAttribute("name");
						if (rsuModelParamStr != NULL)
						{
						    switch ((LinkParam)mapLinkParamList.find(rsuModelParamStr)->second)
						    {
						      default:
						      {
							  std::cout << "Invalid link parameter!\n";
							  break;
						      }
						    }
						}
					    }
					    break;
					}
					case mPhys:
					{
					    physType = subNodeModelOfRSU.getAttribute("type");
					    int rsuModelParamNum = subNodeModelOfRSU.nChildNode("param");
					    for (n = 0; n < rsuModelParamNum; n++)
					    {
						XMLNode subNodeModelParamOfRSU = subNodeModelOfRSU.getChildNode(n);
						std::string rsuModelParamStr = subNodeModelParamOfRSU.getAttribute("name");
						if (rsuModelParamStr != NULL)
						{
						    switch ((PhysParam)mapPhysParamList.find(rsuModelParamStr)->second)
						    {
						      case MaxDistance:
						      {
							  if (subNodeModelParamOfRSU.getText() != NULL)
							      rsuMaxDistance = subNodeModelParamOfRSU.getText();
							  else
							      rsuMaxDistance = GenMaxDistance();
							  break;
						      }
						      case MultiChannel:
						      {
							  if (subNodeModelParamOfRSU.getText() != NULL)
							      rsuMultiChannel = subNodeModelParamOfRSU.getText();
							  else
							      rsuMultiChannel = GenMultiChannel();
							  break;
						      }
						      //TODO: add cases of parameters for other phys models
						      default:
						      {
							  std::cout << "Invalid phys parameter!\n";
							  break;
						      }
						    }
						}
					    }
					    break;
					}
					default:
					{
					    std::cout << "Invalid infrastructure model!\n";
					    break;
					}
				      }
				  }
			      }
			      
			      if (commType == "SimpleComm")
			      {
				  rsuComm = "SimpleCommModel" + IntToString(j+simCommNum);
				  simFile << "MODEL=\"" + rsuComm + "\" " + "TYPE=\"SimpleCommModel\n";
				  simFile << "GATEWAY=\"" + rsuGateWay + "\" " + "RBXJITTER=\"" + rsuRbxJitter + "\" " + "REBROADCAST=\"" + rsuRbx + "\" " + "REBROADCASTINTERVAL=\"" + rsuRbxInterval + "\"\n\n";
			      }
			      
			      if (linkType == "SimpleLink")
			      { 
				  rsuLink = "SimpleLinkModel" + IntToString(j+simLinkNum);
				  simFile << "MODEL=\"" + rsuLink + "\" " + "TYPE=\"SimpleLinkModel\"\n\n";
			      }
			      
			      if (physType == "SimplePhys")
			      {
				  rsuPhys = "SimplePhysModel" + IntToString(j+simPhysNum);
				  simFile << "MODEL=\"" + rsuPhys + "\" " + "TYPE=\"SimplePhysModel\"\n";
				  simFile << "MAXDISTANCE=\"" + rsuMaxDistance + "\" " + "MULTICHANNEL=\"" + rsuMultiChannel + "\"\n\n";
			      }
			      //TODO: add conditions for other types of comm/link/phys model
			      
			      simFile << "MODEL=\"InfrastructureNodeModel" + IntToString(j+rsuNum) + "\" " + "TYPE=\"InfrastructureNodeModel\" " + "DEPENDS=\"" + rsuComm + ";" + rsuLink + ";" + rsuPhys + "\"\n";
			      simFile << "COMM=\"" + rsuComm + "\" " + "DELAY=\"" + rsuDelay + "\" " + "ID=\"" + rsuID + "\" " + "LINK=\"" + rsuLink + "\" " + "PHYS=\"" + rsuPhys + "\" " + "POSITION=\"" + rsuPosition + "\"\n\n";
			  } 
			  
			  simCommNum += infNum;
			  simLinkNum += infNum;
			  simPhysNum += infNum;
			  rsuNum += infNum;
			  
			  break;
		      }
		      case mIncident:
		      {
			  int incNum = 0;
			  if (subNode.isAttributeSet("number") == TRUE)
			  {
			      if (subNode.getAttribute("number") != NULL && subNode.getAttribute("number") != "0")
			      {
				  incNum = atoi(subNode.getAttribute("number"));
			      }
			      else
			      {
				  incNum = 1;
			      }
			  }
			  else
			  {
			      incNum = 1;
			  }
			  
			  int incidentParamNum = subNode.nChildNode("param");
			  for (j = 0; j < incNum; j++)
			  {
			      for (k = 0; k < incidentParamNum; k++)
			      {
				  XMLNode subNodeOfIncident = subNode.getChildNode(k);
				  std::string incidentParamStr = subNodeOfIncident.getAttribute("name");
				  if ( incidentParamStr != NULL)
				  {
				      switch((IncidentParam)mapIncidentParamList.find(incidentParamStr)->second)
				      {
					case IncidentDelay:
					{
					    if (subNodeOfIncident.getText() != NULL)
						incidentDelay = subNodeOfIncident.getText();
					    else
						incidentDelay = GenDelay();
					    break;
					}
					case Description:
					{
					    if (subNodeOfIncident.getText() != NULL)
						description = subNodeOfIncident.getText();
					    else
						description = GenDescription();
					    break;
					}
					case Duration:
					{
					    if (subNodeOfIncident.getText() != NULL)
						duration = subNodeOfIncident.getText();
					    else
						duration = GenDuration();
					    break;
					}
					case IncidentID:
					{
					    if (subNodeOfIncident.getText() != NULL)
						incidentID = subNodeOfIncident.getText();
					    else
						incidentID = IntToString(j+1);
					    break;
					}
					case IncidentPosition:
					{
					    if (subNodeOfIncident.getText() != NULL)
						incidentPosition = subNodeOfIncident.getText();
					    else
						incidentPosition = GenAddress();
					    break;
					}
					case Severity:
					{
					    if (subNodeOfIncident.getText() != NULL)
						severity = subNodeOfIncident.getText();
					    else
						severity = GenSeverity();
					    break;
					}
					case IncidentStartTime:
					{
					    if (subNodeOfIncident.getText() != NULL)
						incidentStartTime = subNodeOfIncident.getText();
					    else
						incidentStartTime = GenStartTime();
					    break;
					}
					case Visibility:
					{
					    if (subNodeOfIncident.getText() != NULL)
						visibility = subNodeOfIncident.getText();
					    else
						visibility = GenVisibility();
					    break;
					}
					default:
					{
					    std::cout << "Invalid incident parameter!\n";
					    break;
					}
				      }
				  }
			      }
			      
			      simFile << "MODEL=\"IncidentModel" + IntToString(j+incidentNum) + "\" " + "TYPE=\"IncidentModel" + "\"\n";;
			      simFile << "DELAY=\"" + incidentDelay + "\" " + "DESCRIPTION=\"" + description + "\" " + "DURATION=\"" + duration + "\" " + "INCIDENT ID=\"" + incidentID + "\" " + "POSITION=\"" + incidentPosition + "\" " + "SEVERITY=\"" + severity + "\" " + "START=\"" + incidentStartTime + "\" " + "VISIBILITY=\"" + visibility + "\"\n\n";
			  }
			  incidentNum += incNum;
			  break;
		      }
		      case mMap:
		      {
			  if (subNode.isAttributeSet("number") == TRUE)
			  {
			      if (subNode.getAttribute("number") != NULL)
			      {
				  mapNum = atoi(subNode.getAttribute("number"));
				  if (mapNum != 1)
				  {
				      std::cout << "Only one map model is needed!\n";
				      mapNum = 1;
				  }
			      }
			      else
			      {
				  mapNum = 1;
			      }
			  }
			  else
			  {
			      mapNum = 1;
			  }
			  
			  int mapParamNum = subNode.nChildNode("param");
			  for (j = 0; j< mapParamNum; j++)
			  {
			      XMLNode subNodeOfMap = subNode.getChildNode(j);
			      std::string mapParamStr = subNodeOfMap.getAttribute("name");
			      if ( mapParamStr != NULL)
			      {
				  switch((MapListParam)mapMapListParamList.find(mapParamStr)->second)
				  {
				    case Caption:
				    {
					if (subNodeOfMap.getText() != NULL)
					    mapCaption = subNodeOfMap.getText();
					else
					    mapCaption = defaultCaption;
					break;
				    }
				    case MapDelay:
				    {
					if (subNodeOfMap.getText() != NULL)
					    mapDelay = subNodeOfMap.getText();
					else
					    mapDelay = defaultDelay;
					break;
				    }
				    case Follow:
				    {
					if (subNodeOfMap.getText() != NULL)
					    follow = subNodeOfMap.getText();
					else
					    follow = defaultFollow;
					break;
				    }
				    case Height:
				    {
					if (subNodeOfMap.getText() != NULL)
					    mapHeight = subNodeOfMap.getText();
					else
					    mapHeight = defaultHeight;
					break;
				    }
				    case Width:
				    {
					if (subNodeOfMap.getText() != NULL)
					    mapWidth = subNodeOfMap.getText();
					else
					    mapWidth = defaultWidth;
					break;
				    }
				    case StartPos:
				    {
					if (subNodeOfMap.getText() != NULL)
					    startPos = subNodeOfMap.getText();
					else
					    startPos = defaultStartPos;
					break;
				    }
				    case Zoom:
				    {
					if (subNodeOfMap.getText() != NULL)
					    zoom = subNodeOfMap.getText();
					else
					    zoom = defaultZoom;
					break;
				    }
				    default:
				    {
					std::cout << "Invalid map parameter!\n";
					break;
				    }
				  }
			      }
			  }
			  simFile << "MODEL=\"MapVisual0\" TYPE=\"MapVisual\"\n";
			  simFile << "CAPTION=\"" + mapCaption + "\" " + "DELAY=\"" + mapDelay + "\" " + "FOLLOW=\"" + follow + "\" " + "HEIGHT=\"" + mapHeight + "\" " +  "START_POS=\"" + startPos + "\" " + "WIDTH=\"" + mapWidth + "\" " + "ZOOM=\"" + zoom + "\"\n\n";
			  break;
		      }
		      case mCarlist:
		      {
			  if (subNode.isAttributeSet("number") == TRUE)
			  {
			      if (subNode.getAttribute("number") != NULL)
			      {
				  carListNum = atoi(subNode.getAttribute("number"));
				  if (carListNum != 1)
				  {
				      std::cout << "Only one car list is needed!\n";
				      carListNum = 1;
				  }
			      }
			      else
			      {
				  carListNum = 1;
			      }
			  }
			  else
			  {
			      carListNum = 1;
			  }
			  
			  int carListParamNum = subNode.nChildNode("param");
			  for (j = 0; j< carListParamNum; j++)
			  {
			      XMLNode subNodeOfCarList = subNode.getChildNode(j);
			      std::string carListParamStr = subNodeOfCarList.getAttribute("name");
			      if ( carListParamStr != NULL)
			      {
				  switch((MapListParam)mapMapListParamList.find(carListParamStr)->second)
				  {
				    case Caption:
				    {
					if (subNodeOfCarList.getText() != NULL)
					    carListCaption = subNodeOfCarList.getText();
					else
					    carListCaption = defaultCaption;
					break;
				    }
				    case ListDelay:
				    {
					if (subNodeOfCarList.getText() != NULL)
					    carListDelay = subNodeOfCarList.getText();
					else
					    carListDelay = defaultDelay;
					break;
				    }
				    case Height:
				    {
					if (subNodeOfCarList.getText() != NULL)
					    carListHeight = subNodeOfCarList.getText();
					else
					    carListHeight = defaultHeight;
					break;
				    }
				    case Width:
				    {
					if (subNodeOfCarList.getText() != NULL)
					    carListWidth = subNodeOfCarList.getText();
					else
					    carListWidth = defaultWidth;
					break;
				    }
				    default:
				    {
					std::cout << "Invalid car list parameter!\n";
					break;
				    }
				  }
			      }
			  }
			  simFile << "MODEL=\"CarListVisual0\" TYPE=\"CarListVisual\"\n";
			  simFile << "CAPTION=\"" + carListCaption + "\" " + "DELAY=\"" + carListDelay + "\"" + "HEIGHT=\"" + carListHeight + "\" " + "WIDTH=\"" + carListWidth + "\"\n\n";
			  break;
		      }
		      case mIncidentlist:
		      {
			  if (subNode.isAttributeSet("number") == TRUE)
			  {
			      if (subNode.getAttribute("number") != NULL)
			      {
				  incidentListNum = atoi(subNode.getAttribute("number"));
				  if (incidentListNum != 1)
				  {
				      std::cout << "Only one incident list is needed!\n";
				      incidentListNum = 1;
				  }
			      }
			      else
			      {
				  incidentListNum = 1;
			      }
			  }
			  else
			  {
			      incidentListNum = 1;
			  }
			  
			  int incidentListParamNum = subNode.nChildNode("param");
			  for (j = 0; j< incidentListParamNum; j++)
			  {
			      XMLNode subNodeOfIncidentList = subNode.getChildNode(j);
			      std::string incidentListParamStr = subNodeOfIncidentList.getAttribute("name");
			      if ( incidentListParamStr != NULL)
			      {
				  switch((MapListParam)mapMapListParamList.find(incidentListParamStr)->second)
				  {
				    case Caption:
				    {
					if (subNodeOfIncidentList.getText() != NULL)
					    incidentListCaption = subNodeOfIncidentList.getText();
					else
					    incidentListCaption = defaultCaption;
					break;
				    }
				    case ListDelay:
				    {
					if (subNodeOfIncidentList.getText() != NULL)
					    incidentListDelay = subNodeOfIncidentList.getText();
					else
					    incidentListDelay = defaultDelay;
					break;
				    }
				    case Height:
				    {
					if (subNodeOfIncidentList.getText() != NULL)
					    incidentListHeight = subNodeOfIncidentList.getText();
					else
					    incidentListHeight = defaultHeight;
					break;
				    }
				    case Width:
				    {
					if (subNodeOfIncidentList.getText() != NULL)
					    incidentListWidth = subNodeOfIncidentList.getText();
					else
					    incidentListWidth = defaultWidth;
					break;
				    }
				    default:
				    {
					std::cout << "Invalid incident list parameter!\n";
					break;
				    }
				  }
			      }
			  }
			  simFile << "MODEL=\"IncidentListVisual0\" TYPE=\"IncidentListVisual\"\n";
			  simFile << "CAPTION=\"" + incidentListCaption + "\" " + "DELAY=\"" + incidentListDelay + "\" " + "HEIGHT=\"" + incidentListHeight + "\" " + "WIDTH=\"" + incidentListWidth + "\"\n\n";
			  break;
		      }
		      default:
		      {
			  std::cout << "Unknown model!\n";
			  break;
		      }
		    }
		}
		else
		{
		    std::cout << "Unknown model!\n";
		}
	    }
	}
	else
	{
	  std::cout << "Invalid simulation xml file!\n";
	  return false;
	}
	simFile.close();   
	return true;
    }
    else
    {
	std::cout << "Can't open simulation file\n";
	return false;
    }
    
}

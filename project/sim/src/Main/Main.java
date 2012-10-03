package Main;

import source.*;

import java.io.*;
import java.util.*;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.Unmarshaller;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;

import org.apache.commons.math3.distribution.*;
import org.xml.sax.SAXException;

public class Main {
			
	private static DetectThresh paramDetectThresh;
	private static ForwardThresh paramForwardThresh;
	private static LieFreq paramLieFreq;
	private static LieThresh paramLieThresh;
	private static TrustLow paramTrustLow;
	private static TrustUp paramTrustUp;
	
	public static float genParam(String paramType, String distributionType)
	{
		float val = 0;
		
		if (paramType.equals("DetectThresh")){
			if (distributionType.equals("Normal")){
				float mean = paramDetectThresh.getNormalMean();
				float stdev = paramDetectThresh.getNormalStdev();
				double num = StdRandom.gaussian(mean, stdev);
				NormalDistribution nd = new NormalDistribution(mean, stdev);
				val = (float)nd.probability(num);
			}else if (distributionType.equals("Poisson")){
				float mean = paramDetectThresh.getPoissonMean();
				int num = StdRandom.poisson(mean);
				PoissonDistribution pd = new PoissonDistribution(mean);
				val = (float)pd.probability(num);
			}else if (distributionType.equals("Bernoulli")){
				float prob = paramDetectThresh.getBernoulliProb();
				if (StdRandom.bernoulli(prob))
					val = prob;
				else
					val = 1 - prob;
			}else if (distributionType.equals("Binomial")){
				float prob = paramDetectThresh.getBinomialProb();
				int upBound = paramDetectThresh.getBinomialUpBound();
				int num = StdRandom.getBinomial(upBound, prob);
				BinomialDistribution bd = new BinomialDistribution(upBound, prob);
				val = (float)bd.probability(num);
			}else if (distributionType.equals("Uniform")){
				float upBound = paramDetectThresh.getUniformUpBound();
				float lowBound = paramDetectThresh.getUniformLowBound();
				val = 1 / (upBound - lowBound);
			}else if (distributionType.equals("UserDefine")){
				val = paramDetectThresh.getUserDefineValue();
			}
		}else if (paramType.equals("ForwardThresh")){
			if (distributionType.equals("Normal")){
				float mean = paramForwardThresh.getNormalMean();
				float stdev = paramForwardThresh.getNormalStdev();
				double num = StdRandom.gaussian(mean, stdev);
				NormalDistribution nd = new NormalDistribution(mean, stdev);
				val = (float)nd.probability(num);
			}else if (distributionType.equals("Poisson")){
				float mean = paramForwardThresh.getPoissonMean();
				int num = StdRandom.poisson(mean);
				PoissonDistribution pd = new PoissonDistribution(mean);
				val = (float)pd.probability(num);
			}else if (distributionType.equals("Bernoulli")){
				float prob = paramForwardThresh.getBernoulliProb();
				if (StdRandom.bernoulli(prob))
					val = prob;
				else
					val = 1 - prob;
			}else if (distributionType.equals("Binomial")){
				float prob = paramForwardThresh.getBinomialProb();
				int upBound = paramForwardThresh.getBinomialUpBound();
				int num = StdRandom.getBinomial(upBound, prob);
				BinomialDistribution bd = new BinomialDistribution(upBound, prob);
				val = (float)bd.probability(num);
			}else if (distributionType.equals("Uniform")){
				float upBound = paramForwardThresh.getUniformUpBound();
				float lowBound = paramForwardThresh.getUniformLowBound();
				val = 1 / (upBound - lowBound);
			}else if (distributionType.equals("UserDefine")){
				val = paramForwardThresh.getUserDefineValue();
			}
		}else if (paramType.equals("LieFreq")){
			if (distributionType.equals("Normal")){
				float mean = paramLieFreq.getNormalMean();
				float stdev = paramLieFreq.getNormalStdev();
				double num = StdRandom.gaussian(mean, stdev);
				NormalDistribution nd = new NormalDistribution(mean, stdev);
				val = (float)nd.probability(num);
			}else if (distributionType.equals("Poisson")){
				float mean = paramLieFreq.getPoissonMean();
				int num = StdRandom.poisson(mean);
				PoissonDistribution pd = new PoissonDistribution(mean);
				val = (float)pd.probability(num);
			}else if (distributionType.equals("Bernoulli")){
				float prob = paramLieFreq.getBernoulliProb();
				if (StdRandom.bernoulli(prob))
					val = prob;
				else
					val = 1 - prob;
			}else if (distributionType.equals("Binomial")){
				float prob = paramLieFreq.getBinomialProb();
				int upBound = paramLieFreq.getBinomialUpBound();
				int num = StdRandom.getBinomial(upBound, prob);
				BinomialDistribution bd = new BinomialDistribution(upBound, prob);
				val = (float)bd.probability(num);
			}else if (distributionType.equals("Uniform")){
				float upBound = paramLieFreq.getUniformUpBound();
				float lowBound = paramLieFreq.getUniformLowBound();
				val = 1 / (upBound - lowBound);
			}else if (distributionType.equals("UserDefine")){
				val = paramLieFreq.getUserDefineValue();
			}
		}else if (paramType.equals("LieThresh")){
			if (distributionType.equals("Normal")){
				float mean = paramLieThresh.getNormalMean();
				float stdev = paramLieThresh.getNormalStdev();
				double num = StdRandom.gaussian(mean, stdev);
				NormalDistribution nd = new NormalDistribution(mean, stdev);
				val = (float)nd.probability(num);
			}else if (distributionType.equals("Poisson")){
				float mean = paramLieThresh.getPoissonMean();
				int num = StdRandom.poisson(mean);
				PoissonDistribution pd = new PoissonDistribution(mean);
				val = (float)pd.probability(num);
			}else if (distributionType.equals("Bernoulli")){
				float prob = paramLieThresh.getBernoulliProb();
				if (StdRandom.bernoulli(prob))
					val = prob;
				else
					val = 1 - prob;
			}else if (distributionType.equals("Binomial")){
				float prob = paramLieThresh.getBinomialProb();
				int upBound = paramLieThresh.getBinomialUpBound();
				int num = StdRandom.getBinomial(upBound, prob);
				BinomialDistribution bd2 = new BinomialDistribution(upBound, prob);
				val = (float)bd2.probability(num);
			}else if (distributionType.equals("Uniform")){
				float upBound = paramLieThresh.getUniformUpBound();
				float lowBound = paramLieThresh.getUniformLowBound();
				val = 1 / (upBound - lowBound);
			}else if (distributionType.equals("UserDefine")){
				val = paramLieThresh.getUserDefineValue();
			}
		}else if (paramType.equals("TrustLow")){
			if (distributionType.equals("Normal")){
				float mean = paramTrustLow.getNormalMean();
				float stdev = paramTrustLow.getNormalStdev();
				double num = StdRandom.gaussian(mean, stdev);
				NormalDistribution nd = new NormalDistribution(mean, stdev);
				val = (float)nd.probability(num);
			}else if (distributionType.equals("Poisson")){
				float mean = paramTrustLow.getPoissonMean();
				int num = StdRandom.poisson(mean);
				PoissonDistribution pd = new PoissonDistribution(mean);
				val = (float)pd.probability(num);
			}else if (distributionType.equals("Bernoulli")){
				float prob = paramTrustLow.getBernoulliProb();
				if (StdRandom.bernoulli(prob))
					val = prob;
				else
					val = 1 - prob;
			}else if (distributionType.equals("Binomial")){
				float prob = paramTrustLow.getBinomialProb();
				int upBound = paramTrustLow.getBinomialUpBound();
				int num = StdRandom.getBinomial(upBound, prob);
				BinomialDistribution bd = new BinomialDistribution(upBound, prob);
				val = (float)bd.probability(num);
			}else if (distributionType.equals("Uniform")){
				float upBound = paramTrustLow.getUniformUpBound();
				float lowBound = paramTrustLow.getUniformLowBound();
				val = 1 / (upBound - lowBound);
			}else if (distributionType.equals("UserDefine")){
				val = paramTrustLow.getUserDefineValue();
			}
		}else if (paramType.equals("TrustUp")){
			if (distributionType.equals("Normal")){
				float mean = paramTrustUp.getNormalMean();
				float stdev = paramTrustUp.getNormalStdev();
				double num = StdRandom.gaussian(mean, stdev);
				NormalDistribution nd = new NormalDistribution(mean, stdev);
				val = (float)nd.probability(num);
			}else if (distributionType.equals("Poisson")){
				float mean = paramTrustUp.getPoissonMean();
				int num = StdRandom.poisson(mean);
				PoissonDistribution pd = new PoissonDistribution(mean);
				val = (float)pd.probability(num);
			}else if (distributionType.equals("Bernoulli")){
				float prob = paramTrustUp.getBernoulliProb();
				if (StdRandom.bernoulli(prob))
					val = prob;
				else
					val = 1 - prob;
			}else if (distributionType.equals("Binomial")){
				float prob = paramTrustUp.getBinomialProb();
				int upBound = paramTrustUp.getBinomialUpBound();
				int num = StdRandom.getBinomial(upBound, prob);
				BinomialDistribution bd = new BinomialDistribution(upBound, prob);
				val = (float)bd.probability(num);
			}else if (distributionType.equals("Uniform")){
				float upBound = paramTrustUp.getUniformUpBound();
				float lowBound = paramTrustUp.getUniformLowBound();
				val = (float) (1.0 / (upBound - lowBound));
			}else if (distributionType.equals("UserDefine")){
				val = paramTrustUp.getUserDefineValue();
			}
		}
		
		return val;
	}

	public static void main(String[] args) {
		try {
			// validate the XML file first
			String xmlFile = "simfile.xml";
			String xsdFile = "simfile.xsd";
			
		    String schemaLang = "http://www.w3.org/2001/XMLSchema";
		    SchemaFactory factory = SchemaFactory.newInstance(schemaLang);
		    Schema schema = factory.newSchema(new StreamSource(xsdFile));
		    Validator validator = schema.newValidator();
		    validator.validate(new StreamSource(xmlFile));
		    
		    // simulation file to be created
		    BufferedWriter bw = new BufferedWriter(new FileWriter("../simfile.sim"));
		    bw.write("% Created by GrooveNet\n\n");
		    
		    int totalVehicleNum = 0;
		    int totalIncidentNum = 0;
		    int totalRSUNum = 0;
		    String baseIP = "192.168.0.";
		    
		    // parse the XML file
		    JAXBContext jc = JAXBContext.newInstance("source");
			Unmarshaller unmarshaller = jc.createUnmarshaller();
			
			// entry element of the XML file
			Simulation simulation = (Simulation)unmarshaller.unmarshal(new File(xmlFile));
			
			// parse vehicle model
			List<VehicleModel> vehicleModels = simulation.getVehicleModel();
			int attackerNum = 0, authorityNum = 0, defaultNum = 0;
			for (VehicleModel vehicles : vehicleModels)
			{
				int vehicleNum = vehicles.getVehicleNum();
				
				// get parameters
				float vehicleDetectRange = vehicles.getDetectRange();
				float vehicleStartTime = vehicles.getVehicleStartTime();
				float vehicleDelay = vehicles.getVehicleDelay();
				String vehicleLog = vehicles.getLog();
				String vehicleTrackSpeed = vehicles.getTrackSpeed();
				
				// Role
				int totalRole = 0;
				RoleModel vehicleRole = vehicles.getRoleModel();
				String roleType = vehicleRole.getRoleType();
				if (roleType == "Attacker")
				{
					totalRole = attackerNum;
					attackerNum += vehicleNum;
				}else if (roleType == "Authority"){
					totalRole = authorityNum;
					authorityNum += vehicleNum;
				}else if (roleType == "Default"){
					totalRole = defaultNum;
					defaultNum += vehicleNum;
				}
				String vehicleRoleModel = roleType + "RoleModel";
				String distributionType = "";
				paramDetectThresh = vehicleRole.getDetectThresh();
				distributionType = paramDetectThresh.getDistributionType();
				float detectThresh = genParam("DetectThresh", distributionType);
				paramForwardThresh = vehicleRole.getForwardThresh();
				distributionType = paramForwardThresh.getDistributionType();
				float forwardThresh = genParam("ForwardThresh", distributionType);
				paramLieFreq = vehicleRole.getLieFreq();
				distributionType = paramLieFreq.getDistributionType();
				float lieFreq = genParam("LieFreq", distributionType);
				paramLieThresh = vehicleRole.getLieThresh();
				distributionType = paramLieThresh.getDistributionType();
				float lieThresh = genParam("LieThresh", distributionType);
				paramTrustLow = vehicleRole.getTrustLow();
				distributionType = paramTrustLow.getDistributionType();
				float trustLow = genParam("TrustLow", distributionType);
				paramTrustUp = vehicleRole.getTrustUp();
				distributionType = paramTrustUp.getDistributionType();
				float trustUp = genParam("TrustUp", distributionType);
				
				// SimpleComm
				String vehicleCommModel = "SimpleCommModel";
				SimpleCommModel vehicleComm = vehicles.getSimpleCommModel();
				String vehicleGateWay = vehicleComm.getGateWay();
				String vehicleRbxJitter = vehicleComm.getRbxJitter();
				String vehicleRbx = vehicleComm.getRbx();
				int vehicleRbxInterval = vehicleComm.getRbxInterval();
				
				// SimpleLink
				String vehicleLinkModel = "SimpleLinkModel";
				String vehicleLink = vehicles.getSimpleLinkModel();
				
				// SimplePhys
				String vehiclePhysModel = "SimplePhysModel";
				SimplePhysModel vehiclePhys = vehicles.getSimplePhysModel();
				float vehicleMaxDistance = vehiclePhys.getMaxDistance();
				String vehicleMultiChannel = vehiclePhys.getMultiChannel();
				
				// RanddomWalk
				String vehicleTripModel = "RandomWalkModel";
				RandomWalkModel vehicleTrip = vehicles.getRandomWalkModel();
				String vehicleStartAddress = vehicleTrip.getStartAddress();
				
				// StreetSpeed
				String vehicleMobilityModel = "StreetSpeedModel";
				StreetSpeedModel vehicleMobility = vehicles.getStreetSpeedModel();
				String vehicleMultiLane = vehicleMobility.getMultiLane();
				
				int vehicleCount = 0;
				for (int i = 0; i < vehicleNum; i++)
				{
					vehicleCount = i + totalVehicleNum;
					String vehicleIP = baseIP + vehicleCount + 1;
					
					bw.write("MODEL=\"" + vehicleCommModel + vehicleCount + "\"" + "TYPE=\"" + vehicleCommModel + "\"\n");
					bw.write("GATEWAY=\"" + vehicleGateWay + "\" " + "RBXJITTER=\"" + vehicleRbxJitter + "\" " + "REBROADCAST=\"" + vehicleRbx + "\" " + "REBROADCASTINTERVAL=\"" + vehicleRbxInterval + "\"\n\n");
					
					bw.write("MODEL=\"" + vehicleLinkModel + vehicleCount + "\" " + "TYPE=\"" + vehicleLinkModel + "\"\n\n");
					
					bw.write("MODEL=\"" + vehiclePhysModel + vehicleCount + "\" " + "TYPE=\"" + vehiclePhysModel + "\"\n");
					bw.write("MAXDISTANCE=\"" + vehicleMaxDistance + "\" " + "MULTICHANNEL=\"" + vehicleMultiChannel + "\"\n\n");
				
					bw.write("MODEL=\"" + vehicleRoleModel + (i + totalRole) + "\" " + "TYPE=\"" + vehicleRoleModel + "\"\n");
					bw.write("DETECTION THRESHOLD=\"" + detectThresh + "\" " + "FORWARD THRESHOLD=\"" + forwardThresh + "\" " + "LIE FREQUENCY=\"" + lieFreq + "\" " + "LIE THRESHOLD=\"" + lieThresh + "\" " + "TRUST LOWER BOUND=\"" + trustLow + "\" " + "TRUST UPPER BOUND=\"" + trustUp + "\"\n\n");
					
					bw.write("MODEL=\"" + vehicleTripModel + vehicleCount + "\" " + "TYPE=\"" + vehicleTripModel + "\"\n");
					bw.write("START=\"" + vehicleStartAddress + "\"\n\n");
					//bw.write("START=\"\"\n\n");
					
					bw.write("MODEL=\"" + vehicleMobilityModel + vehicleCount + "\" " + "TYPE=\"" + vehicleMobilityModel + "\" " + "DEPENDS=\"" + vehicleTripModel + vehicleCount + "\"\n");
					bw.write("MULTILANE=\"" + vehicleMultiLane + "\" " + "TRIP=\"" + vehicleTripModel + vehicleCount + "\"\n\n");
					
					bw.write("MODEL=\"VehicleModel" + vehicleCount + "\" " + "TYPE=\"VehicleModel\" ");
					bw.write("DEPENDS=\"" + vehiclePhysModel + vehicleCount + ";" 
							+ vehicleLinkModel + vehicleCount + ";"
							+ vehicleCommModel + vehicleCount + ";"
							+ vehicleRoleModel + vehicleCount + ";"
							+ vehicleTripModel + vehicleCount + ";"
							+ vehicleMobilityModel + vehicleCount + "\"\n");
					bw.write("COMM=\"" + vehicleCommModel + vehicleCount + "\" "
							+ "DELAY=\"" + vehicleDelay + "\" "
							+ "DETECTION RANGE=\"" + vehicleDetectRange + "\" "
							+ "DOLOG=\"" + vehicleLog + "\" "
							+ "ID=\"" + vehicleIP + "\" "
							+ "LINK=\"" + vehicleLinkModel + vehicleCount + "\" "
							+ "MOBILITY=\"" + vehicleMobilityModel + vehicleCount + "\" "
							+ "PHYS=\"" + vehiclePhysModel + vehicleCount + "\" "
							+ "ROLE=\"" + vehicleRoleModel + vehicleCount + "\" "
							+ "START=\"" + vehicleStartTime + "\" "
							+ "TRACKSPEED=\"" + vehicleTrackSpeed + "\" "
							+ "TRIP=\"" + vehicleTripModel + vehicleCount + "\"\n\n");
				}
				
				totalVehicleNum += vehicleNum;
			}
			
			// parse incident model
			List<IncidentModel> incidentModels = simulation.getIncidentModel();
			for (IncidentModel incidents : incidentModels)
			{
				int incidentNum = incidents.getIncidentNum();
				
				float incidentDelay = incidents.getIncidentDelay();
				String description = incidents.getDescription();
				float duration = incidents.getDuration();
				String incidentPosition = incidents.getIncidentPosition();
				String severity = incidents.getSeverity();
				float incidentStartTime = incidents.getIncidentStartTime();
				float visibility = incidents.getVisibility();
				
				int incidentCount = 0;
				for (int i = 0; i < incidentNum; i++)
				{
					incidentCount = i + totalIncidentNum;
					String incidentID = Integer.toString(incidentCount);
					
					bw.write("MODEL=\"IncidentModel" + incidentID + "\" " + "TYPE=\"IncidentModel" + "\"\n");
					bw.write("DELAY=\"" + incidentDelay + "\" " + "DESCRIPTION=\"" + description + "\" " + "DURATION=\"" + duration + "\" " + "INCIDENT ID=\"" + incidentID + "\" " + "POSITION=\"" + incidentPosition + "\" " + "SEVERITY=\"" + severity + "\" " + "START=\"" + incidentStartTime + "\" " + "VISIBILITY=\"" + visibility + "\"\n\n");
				}
				
				totalIncidentNum += incidentNum;
			}
			
			// parse road side unit model
			List<RSUModel> rsuModels = simulation.getRSUModel();
			for (RSUModel RSUs : rsuModels)
			{
				int rsuNum = RSUs.getRSUNum();
				
				float rsuDelay = RSUs.getRSUDelay();
				String rsuPosition = RSUs.getRSUPosition();
				
				// SimpleComm
				String rsuCommModel = "SimpleCommModel";
				SimpleCommModel rsuComm = RSUs.getSimpleCommModel();
				String rsuGateWay = rsuComm.getGateWay();
				String rsuRbxJitter = rsuComm.getRbxJitter();
				String rsuRbx = rsuComm.getRbx();
				int rsuRbxInterval = rsuComm.getRbxInterval();
				
				// SimpleLink
				String rsuLinkModel = "SimpleLinkModel";
				String rsuLink = RSUs.getSimpleLinkModel();
				
				// SimiplePhys
				String rsuPhysModel = "SimplePhysModel";
				SimplePhysModel rsuPhys = RSUs.getSimplePhysModel();
				float rsuMaxDistance = rsuPhys.getMaxDistance();
				String rsuMultiChannel = rsuPhys.getMultiChannel();
				
				int rsuCount = 0;
				for (int i = 0; i < rsuNum; i++)
				{
					rsuCount = i + totalRSUNum + totalVehicleNum;
					String rsuIP = baseIP + rsuCount + 1;
					
					bw.write("MODEL=\"SimpleCommModel" + rsuCount + "\" " + "TYPE=\"SimpleCommModel\n");
					bw.write("GATEWAY=\"" + rsuGateWay + "\" " + "RBXJITTER=\"" + rsuRbxJitter + "\" " + "REBROADCAST=\"" + rsuRbx + "\" " + "REBROADCASTINTERVAL=\"" + rsuRbxInterval + "\"\n\n");
					bw.write("MODEL=\"SimpleLinkModel" + rsuCount + "\" " + "TYPE=\"SimpleLinkModel\"\n\n");
					bw.write("MODEL=\"SimplePhysModel" + rsuCount + "\" " + "TYPE=\"SimplePhysModel\"\n");
					bw.write("MAXDISTANCE=\"" + rsuMaxDistance + "\" " + "MULTICHANNEL=\"" + rsuMultiChannel + "\"\n\n");
					bw.write("MODEL=\"InfrastructureNodeModel" + rsuCount + "\" " + "TYPE=\"InfrastructureNodeModel\" " + "DEPENDS=\"" + rsuCommModel + rsuCount + ";" + rsuLinkModel + rsuCount + ";" + rsuPhysModel + rsuCount + "\"\n");
					bw.write("COMM=\"" + rsuCommModel + rsuCount + "\" " + "DELAY=\"" + rsuDelay + "\" " + "ID=\"" + rsuIP + "\" " + "LINK=\"" + rsuLinkModel + rsuCount + "\" " + "PHYS=\"" + rsuPhysModel + rsuCount + "\" " + "POSITION=\"" + rsuPosition + "\"\n\n");
				}
				
				totalRSUNum += rsuNum;
			}
			
			// parse map model
			MapModel map = simulation.getMapModel();
			String mapCaption = map.getCaption();
			String follow = map.getFollow();
			float mapDelay = map.getMapDelay();
			int mapHeight = map.getHeight();
			int mapWidth = map.getWidth();
			int zoom = map.getZoom();
			String startPos = map.getStartPos();
			bw.write("MODEL=\"MapVisual0\" TYPE=\"MapVisual\"\n");
			bw.write("CAPTION=\"" + mapCaption + "\" " + "DELAY=\"" + mapDelay + "\" " + "FOLLOW=\"" + follow + "\" " + "HEIGHT=\"" + mapHeight + "\" " +  "START_POS=\"" + startPos + "\" " + "WIDTH=\"" + mapWidth + "\" " + "ZOOM=\"" + zoom + "\"\n\n");
			
			// parse car list model
			CarList carList = simulation.getCarList();
			String carListCaption = carList.getCaption();
			float carListDelay = carList.getListDelay();
			int carListHeight = carList.getHeight();
			int carListWidth = carList.getWidth();
			bw.write("MODEL=\"CarListVisual0\" TYPE=\"CarListVisual\"\n");
			bw.write("CAPTION=\"" + carListCaption + "\" " + "DELAY=\"" + carListDelay + "\"" + "HEIGHT=\"" + carListHeight + "\" " + "WIDTH=\"" + carListWidth + "\"\n\n");
			
			// parse incident list model
			IncidentList incidentList = simulation.getIncidentList();
			String incidentListCaption = incidentList.getCaption();
			float incidentListDelay = incidentList.getListDelay();
			int incidentListHeight = incidentList.getHeight();
			int incidentListWidth = incidentList.getWidth();
			bw.write("MODEL=\"IncidentListVisual0\" TYPE=\"IncidentListVisual\"\n");
			bw.write("CAPTION=\"" + incidentListCaption + "\" " + "DELAY=\"" + incidentListDelay + "\" " + "HEIGHT=\"" + incidentListHeight + "\" " + "WIDTH=\"" + incidentListWidth + "\"\n\n");
			
			bw.close();
			
		} catch (SAXException e) {
		    System.out.println(" sax exception :" + e.getMessage());
		} catch (Exception ex) {
		    System.out.println("excep :" + ex.getMessage());
		}
	
	}

}

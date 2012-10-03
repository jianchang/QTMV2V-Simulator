//
// This file was generated by the JavaTM Architecture for XML Binding(JAXB) Reference Implementation, vJAXB 2.1.10 
// See <a href="http://java.sun.com/xml/jaxb">http://java.sun.com/xml/jaxb</a> 
// Any modifications to this file will be lost upon recompilation of the source schema. 
// Generated on: 2012.09.28 at 03:23:37 PM EDT 
//


package source;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for anonymous complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType>
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;all>
 *         &lt;element ref="{}DetectRange"/>
 *         &lt;element ref="{}VehicleStartTime"/>
 *         &lt;element ref="{}VehicleDelay"/>
 *         &lt;element ref="{}Log"/>
 *         &lt;element ref="{}TrackSpeed"/>
 *         &lt;element ref="{}RoleModel"/>
 *         &lt;element ref="{}SimpleCommModel"/>
 *         &lt;element ref="{}SimpleLinkModel"/>
 *         &lt;element ref="{}SimplePhysModel"/>
 *         &lt;element ref="{}RandomWalkModel"/>
 *         &lt;element ref="{}StreetSpeedModel"/>
 *       &lt;/all>
 *       &lt;attribute ref="{}VehicleNum use="required""/>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "", propOrder = {

})
@XmlRootElement(name = "VehicleModel")
public class VehicleModel {

    @XmlElement(name = "DetectRange")
    protected float detectRange;
    @XmlElement(name = "VehicleStartTime", defaultValue = "0")
    protected float vehicleStartTime;
    @XmlElement(name = "VehicleDelay", defaultValue = "0.2")
    protected float vehicleDelay;
    @XmlElement(name = "Log", required = true, defaultValue = "NO")
    protected String log;
    @XmlElement(name = "TrackSpeed", required = true, defaultValue = "NO")
    protected String trackSpeed;
    @XmlElement(name = "RoleModel", required = true)
    protected RoleModel roleModel;
    @XmlElement(name = "SimpleCommModel", required = true)
    protected SimpleCommModel simpleCommModel;
    @XmlElement(name = "SimpleLinkModel", required = true)
    protected String simpleLinkModel;
    @XmlElement(name = "SimplePhysModel", required = true)
    protected SimplePhysModel simplePhysModel;
    @XmlElement(name = "RandomWalkModel", required = true)
    protected RandomWalkModel randomWalkModel;
    @XmlElement(name = "StreetSpeedModel", required = true)
    protected StreetSpeedModel streetSpeedModel;
    @XmlAttribute(name = "VehicleNum", required = true)
    protected int vehicleNum;

    /**
     * Gets the value of the detectRange property.
     * 
     */
    public float getDetectRange() {
        return detectRange;
    }

    /**
     * Sets the value of the detectRange property.
     * 
     */
    public void setDetectRange(float value) {
        this.detectRange = value;
    }

    /**
     * Gets the value of the vehicleStartTime property.
     * 
     */
    public float getVehicleStartTime() {
        return vehicleStartTime;
    }

    /**
     * Sets the value of the vehicleStartTime property.
     * 
     */
    public void setVehicleStartTime(float value) {
        this.vehicleStartTime = value;
    }

    /**
     * Gets the value of the vehicleDelay property.
     * 
     */
    public float getVehicleDelay() {
        return vehicleDelay;
    }

    /**
     * Sets the value of the vehicleDelay property.
     * 
     */
    public void setVehicleDelay(float value) {
        this.vehicleDelay = value;
    }

    /**
     * Gets the value of the log property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getLog() {
        return log;
    }

    /**
     * Sets the value of the log property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setLog(String value) {
        this.log = value;
    }

    /**
     * Gets the value of the trackSpeed property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getTrackSpeed() {
        return trackSpeed;
    }

    /**
     * Sets the value of the trackSpeed property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setTrackSpeed(String value) {
        this.trackSpeed = value;
    }

    /**
     * Gets the value of the roleModel property.
     * 
     * @return
     *     possible object is
     *     {@link RoleModel }
     *     
     */
    public RoleModel getRoleModel() {
        return roleModel;
    }

    /**
     * Sets the value of the roleModel property.
     * 
     * @param value
     *     allowed object is
     *     {@link RoleModel }
     *     
     */
    public void setRoleModel(RoleModel value) {
        this.roleModel = value;
    }

    /**
     * Gets the value of the simpleCommModel property.
     * 
     * @return
     *     possible object is
     *     {@link SimpleCommModel }
     *     
     */
    public SimpleCommModel getSimpleCommModel() {
        return simpleCommModel;
    }

    /**
     * Sets the value of the simpleCommModel property.
     * 
     * @param value
     *     allowed object is
     *     {@link SimpleCommModel }
     *     
     */
    public void setSimpleCommModel(SimpleCommModel value) {
        this.simpleCommModel = value;
    }

    /**
     * Gets the value of the simpleLinkModel property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSimpleLinkModel() {
        return simpleLinkModel;
    }

    /**
     * Sets the value of the simpleLinkModel property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSimpleLinkModel(String value) {
        this.simpleLinkModel = value;
    }

    /**
     * Gets the value of the simplePhysModel property.
     * 
     * @return
     *     possible object is
     *     {@link SimplePhysModel }
     *     
     */
    public SimplePhysModel getSimplePhysModel() {
        return simplePhysModel;
    }

    /**
     * Sets the value of the simplePhysModel property.
     * 
     * @param value
     *     allowed object is
     *     {@link SimplePhysModel }
     *     
     */
    public void setSimplePhysModel(SimplePhysModel value) {
        this.simplePhysModel = value;
    }

    /**
     * Gets the value of the randomWalkModel property.
     * 
     * @return
     *     possible object is
     *     {@link RandomWalkModel }
     *     
     */
    public RandomWalkModel getRandomWalkModel() {
        return randomWalkModel;
    }

    /**
     * Sets the value of the randomWalkModel property.
     * 
     * @param value
     *     allowed object is
     *     {@link RandomWalkModel }
     *     
     */
    public void setRandomWalkModel(RandomWalkModel value) {
        this.randomWalkModel = value;
    }

    /**
     * Gets the value of the streetSpeedModel property.
     * 
     * @return
     *     possible object is
     *     {@link StreetSpeedModel }
     *     
     */
    public StreetSpeedModel getStreetSpeedModel() {
        return streetSpeedModel;
    }

    /**
     * Sets the value of the streetSpeedModel property.
     * 
     * @param value
     *     allowed object is
     *     {@link StreetSpeedModel }
     *     
     */
    public void setStreetSpeedModel(StreetSpeedModel value) {
        this.streetSpeedModel = value;
    }

    /**
     * Gets the value of the vehicleNum property.
     * 
     */
    public int getVehicleNum() {
        return vehicleNum;
    }

    /**
     * Sets the value of the vehicleNum property.
     * 
     */
    public void setVehicleNum(int value) {
        this.vehicleNum = value;
    }

}
